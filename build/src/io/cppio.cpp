
#include "cppio.h"
#include "io.h"
#include "../util/strutil.h"

#include <filesystem>

namespace cppio {

    bool recursiveProcSrcFiles( string basedir, vector<CPPFile*>& cppFiles ) {
        string prefBaseDir = io::makePreferred( basedir );
        try {
            for( const auto& entry : filesystem::recursive_directory_iterator( prefBaseDir ) ) {
                string fileName = io::relativePath( entry.path().string() );
                fileName = io::makePreferred( fileName );
                if ( !filesystem::is_directory( fileName ) && strutil::endsWith( fileName, ".cpp" ) ) {
                    string objFileName = fileName;
                    objFileName.replace( objFileName.length()-3, 3, "o" );

                    CPPFile* file = new CPPFile;
                    file->fileName = fileName;
                    file->objFileName = objFileName;
                    cppFiles.push_back( file );
                }
            }
            return true;
        } catch ( const filesystem::filesystem_error& error ) {
            return false;
        }
    }

    CPPFile* getCPPFileByFileName( vector<CPPFile*>& cppFiles, string fileName ) {
        for( CPPFile* file : cppFiles )
            if ( file->fileName == fileName )
                return file;
        return nullptr;
    }

}
