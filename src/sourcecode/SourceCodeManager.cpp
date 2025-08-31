
#include "SourceCodeManager.h"
#include "../io/io.h"
#include "../util/strutil.h"

#include <filesystem>

using std::getline;

SourceCodeManager::SourceCodeManager( string sourceFileExtensions, string headerFileExtensions ) {
    this->filesToCompileManager = new FilesToCompileManager( sourceFileExtensions, headerFileExtensions );
    this->dependenciesSCLoader = new DependenciesSCLoader();
    this->lwTimesFileIO = new LWTimesFileIO();
    this->sourceFileExtensions = sourceFileExtensions;
    this->headerFileExtensions = headerFileExtensions;
}

SourceCodeManager::~SourceCodeManager() {
    delete filesToCompileManager;
    delete dependenciesSCLoader;
    delete lwTimesFileIO;
    for( const auto& pair : allCodeInfosMap )
        delete pair.second;
}

bool SourceCodeManager::recursiveProcFiles( string srcDir, string targetFolder ) {
    sourceCodeInfosMap.clear();
    allCodeInfosMap.clear();
    classToIncludeMap.clear();

    string src = io::makePreferred( srcDir );
    src = io::addSeparatorToDirIfNeed( src );

    try {
        for( const auto& entry : filesystem::recursive_directory_iterator( src ) ) {
            string filePath = entry.path().string();
            filePath = io::makePreferred( filePath );

            if ( !filesystem::is_directory( filePath ) ) {                
                string relativeFilePath = strutil::replace( filePath, src, "" );

                string ext = io::extension( filePath );

                string objFilePath = targetFolder;
                objFilePath = io::addSeparatorToDirIfNeed( objFilePath );
                objFilePath += strutil::replace( relativeFilePath, "."+ext, ".o" );
                
                string srcFilePath = filePath;

                vector<string> dependencies;
                vector<string> extendedClasses;
            
                CodeInfo* info = new CodeInfo;
                info->filePath = srcFilePath;
                info->objFilePath = objFilePath;
                info->dependencies = dependencies;
                info->extendedClasses = extendedClasses;

                if ( strutil::endsWithSome( filePath, sourceFileExtensions ) ) {
                    sourceCodeInfosMap[ filePath ] = info;
                    allCodeInfosMap[ filePath ] = info;
                } else if ( strutil::endsWithSome( filePath, headerFileExtensions ) ) {
                    allCodeInfosMap[ filePath ] = info;
                }
            }
        }

        return dependenciesSCLoader->loadDependencies( allCodeInfosMap, classToIncludeMap );
    } catch ( const filesystem::filesystem_error& error ) {
        return false;
    }
}

vector<string> SourceCodeManager::withHeaderObjectCodeFiles() {
    vector<string> objectCodeFiles;
    for( const auto& pair : allCodeInfosMap ) {
        string file = pair.first;

        if ( strutil::endsWithSome( file, headerFileExtensions ) )
            objectCodeFiles.push_back( pair.second->objFilePath );        
    }
    return objectCodeFiles;
}

CodeInfo* SourceCodeManager::getSourceCodeInfo( string filePath ) {
    return sourceCodeInfosMap[ filePath ];
}

vector<string> SourceCodeManager::sourceFilePaths() {
    vector<string> paths;
    for( const auto& pair : sourceCodeInfosMap )
        paths.push_back( pair.first );
    return paths;
}

vector<CodeInfo*> SourceCodeManager::sourceCodeInfos() {
    vector<CodeInfo*> infos;
    for( const auto& pair : sourceCodeInfosMap )
        infos.push_back( pair.second );
    return infos;
}

void SourceCodeManager::loadFilesToCompile( vector<CodeInfo*>& filesToCompile, string configFilePath ) {
    map<string, long> lwTimesMap;

    if ( io::fileExists( configFilePath ) )
        lwTimesFileIO->loadLastWriteTimesFromFile( lwTimesMap, configFilePath );

    filesToCompileManager->loadFilesToCompile( filesToCompile, allCodeInfosMap, lwTimesMap, configFilePath );
}

void SourceCodeManager::saveLastWriteTimesInFile( string configFilePath, bool isAppend ) {
    lwTimesFileIO->saveLastWriteTimesInFile( allCodeInfosMap, configFilePath, isAppend );
}
