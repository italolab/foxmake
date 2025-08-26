#ifndef CONSTS_H
#define CONSTS_H

#include <string>
#include <vector>

using std::string;
using std::vector;

namespace consts {

    const string DEFAULT_SETTINGS_FILE_NAME = "settings.txt";

    const string LAST_WRITE_TIMES_FILE = "__lwtimes.txt";
    const string TEMP_BAT_FILE = "__temp.bat";

    const string SOURCE_FILE_EXTENSIONS = ".c .cpp .cc";
    const string HEADER_FILE_EXTENSIONS = ".h .hpp .tpp .ipp";

    const bool DEFAULT_SHOW_CMD_OUTPUT = true;

    const string WINDOWS_CMD_EXE = "cmd.exe /c";

}

namespace tasks {

    const string INIT = "init";
    const string FINISH = "finish";
    const string CLEAN = "clean";
    const string COMPILE = "compile";
    const string COMPILEALL = "compileall";
    const string LINK = "link";
    const string COPY = "copy";
    const string BUILD = "build";
    const string BUILDALL = "buildall";

    const vector<string> DEFAULT_TASKS = {
        INIT,
        FINISH,
        CLEAN,
        COMPILE,
        COMPILEALL,
        LINK,
        COPY,
        BUILD,
        BUILDALL
    };

}

namespace cmds {

    const string CP = "cp";
    const string CD = "cd";
    const string RM = "rm";
    const string MKDIR = "mkdir";
    const string ECHO = "echo";

}

namespace props {

    const string IS_DLL = "is.dll";

    const string COMPILER = "compiler";
    const string COMPILER_PARAMS = "compiler.params";
    const string LINKER_PARAMS = "linker.params";

    const string EXE_FILE_NAME = "exe.file.name";
    const string DLL_FILE_NAME = "dll.file.name";

    const string SRC_DIR = "src.dir";
    const string OBJ_DIR = "obj.dir";
    const string BIN_DIR = "bin.dir";
    const string BUILD_DIR = "build.dir";

    const string BUILD_FILES = "build.files";
    const string RESOURCE_FILE = "resource.file";

    const string LIB_DIRS = "lib.dirs";
    const string INCLUDE_DIRS = "include.dirs";
    const string LIBS = "libs";

    const string DEFINES = "defines";

    const string OUTPUT_DEF_FILE = "output.def.file";
    const string OUT_IMPLIB_FILE = "out.implib.file";

    const vector<string> VALID_NAMES = {
        IS_DLL,

        COMPILER,
        COMPILER_PARAMS,
        LINKER_PARAMS,

        EXE_FILE_NAME,
        DLL_FILE_NAME,

        SRC_DIR,
        OBJ_DIR,
        BIN_DIR,
        BUILD_DIR,

        BUILD_FILES,
        RESOURCE_FILE,

        LIB_DIRS,
        INCLUDE_DIRS,
        LIBS,

        DEFINES,

        OUTPUT_DEF_FILE,
        OUT_IMPLIB_FILE
    };

}

#endif
