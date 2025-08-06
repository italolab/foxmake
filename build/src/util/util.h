#ifndef UTIL_H
#define UTIL_H

#include <string>
#include <vector>

using namespace std;

vector<string> splitWithDoubleQuotes( string str );

bool endsWith( string str, string suffix );
string trim( string str );

#endif
