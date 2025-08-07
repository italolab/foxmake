#ifndef CPP_IO_H
#define CPP_IO_H

#include <string>
#include <vector>

using namespace std;

typedef struct TCPPFile {
    string fileName;
    string objFileName;
} CPPFile;

namespace cppio {

    bool recursiveProcSrcFiles( string basedir, vector<CPPFile*>& cppFiles );
    CPPFile* getCPPFileByFileName( vector<CPPFile*>& cppFiles, string fileName );

}

#endif
