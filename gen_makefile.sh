#!/bin/bash
CXX="g++"
CXXFLAGS="-Wall -g"
LINKERFLAGS=""
SRC_DIR="src"
OBJ_DIR="obj/Release"
BIN_DIR="bin/Release"
TARGET="cbuild"

mkdir -p $OBJ_DIR
mkdir -p $BIN_DIR

if [ ! -e "Makefile" ]; then
    touch Makefile
fi

echo "" > Makefile

printf "CXX=$CXX\n" >> Makefile
printf "CXXFLAGS=$CXXFLAGS\n" >> Makefile
printf "TARGET=$TARGET\n\n" >> Makefile

touch __temp
touch __temp2
OBJS=""
OBJS_PATHS=""
find $SRC_DIR -type f -name "*.cpp" -printf '%p\n' | while read -r file; do
    cpp_file_path="$file"
    obj_file_path=$(echo "$cpp_file_path" | awk '{gsub(".cpp", ".o", $0); print $0}')

    obj_file_path2="$OBJ_DIR/$obj_file_path"

    obj_dir2=$(dirname "$obj_file_path2")

    mkdir -p $obj_dir2
    
    OBJS+=" $obj_file_path"
    OBJS_PATHS+=" $obj_file_path2"
    echo $OBJS > __temp
    echo $OBJS_PATHS > __temp2
done

OBJS=$(cat __temp)
OBJS_PATHS=$(cat __temp2)

rm __temp __temp2

printf ".PHONY: all\n\n" >> Makefile

printf "all: \$(TARGET)\n\n" >> Makefile

printf "\$(TARGET): $OBJS\n" >> Makefile
printf "\t\$(CXX) -o \$(TARGET) $OBJS_PATHS $LINKERFLAGS\n\n" >> Makefile

find $SRC_DIR -type f -name "*.cpp" -printf '%p\n' | while read -r file; do
    cpp_file_path="$file"

    obj_file_path=$(echo "$cpp_file_path" | awk '{gsub(".cpp", ".o", $0); print $0}')

    printf "$obj_file_path:\n" >> Makefile

    obj_file_path="$OBJ_DIR/$obj_file_path"

    printf "\t\$(CXX) \$(CXXFLAGS) -o $obj_file_path -c $cpp_file_path\n\n" >> Makefile
done