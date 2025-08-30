#ifndef SOURCE_CODE_INFO_H
#define SOURCE_CODE_INFO_H

#include <string>
#include <vector>

using std::string;
using std::vector;

typedef struct TCodeInfo {
    string filePath;
    string srcFilePath;
    string objFilePath;
    vector<string> extendedClasses;
    vector<string> dependencies;
} CodeInfo;

#endif
