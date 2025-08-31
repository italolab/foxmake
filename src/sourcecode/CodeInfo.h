#ifndef SOURCE_CODE_INFO_H
#define SOURCE_CODE_INFO_H

#include <string>
#include <vector>

using std::string;
using std::vector;

typedef struct TClassInfo {
    string name;
    vector<string> extendedClasses;
} ClassInfo;

typedef struct TCodeInfo {
    string filePath;
    string objFilePath;
    vector<string> includes;
    vector<ClassInfo*> classes;
    vector<string> dependencies;
} CodeInfo;

#endif
