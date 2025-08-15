#ifndef SOURCE_CODE_INFO_H
#define SOURCE_CODE_INFO_H

#include <string>
#include <vector>

using std::string;
using std::vector;

typedef struct TSourceCodeInfo {
    string filePath;
    string objFilePath;
    vector<string> extendedClasses;
    vector<string> dependencies;
} SourceCodeInfo;

#endif
