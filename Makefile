
CXX=g++
CXXFLAGS=-Wall -g
TARGET=cbuild

.PHONY: all

all: $(TARGET)

$(TARGET): src/exec/TaskExec.o src/exec/shcmd/ShellCMDExec.o src/exec/stexcept.o src/exec/main/CompileTaskExec.o src/exec/main/LinkTaskExec.o src/exec/main/MainExec.o src/exec/main/ExeLinkTaskExec.o src/exec/main/CleanTaskExec.o src/exec/main/DynamicLibraryLinkTaskExec.o src/exec/main/CopyTaskExec.o src/exec/ExecManager.o src/exec/echo/EchoExec.o src/exec/mkdir/MKDirExec.o src/exec/cd/CDExec.o src/exec/rm/RMExec.o src/exec/ArgManager.o src/exec/Exec.o src/exec/cp/CPExec.o src/main.o src/darv/Prop.o src/darv/GenericCMD.o src/darv/Task.o src/darv/Statement.o src/darv/ShellCMD.o src/darv/DefaultTaskConfig.o src/darv/CMD.o src/darv/MainScript.o src/darv/Block.o src/darv/Var.o src/util/strutil.o src/shell/shell.o src/shell/output/OutputThread.o src/shell/output/OutputController.o src/io/SourceCodeManager.o src/io/FilesToCompileManager.o src/io/io.o src/io/filter/ByNameFileFilter.o src/msg/messagebuilder.o src/inter/PropInter.o src/inter/InterManager.o src/inter/VarInter.o src/inter/Inter.o src/inter/taskconfig/TaskConfigInter.o src/inter/taskconfig/TaskConfigResult.o src/inter/InterResult.o src/inter/MainScriptInter.o src/inter/TaskInter.o src/inter/CMDInter.o src/inter/ShellCMDInter.o src/inter/it/StringIterator.o src/inter/it/FileIterator.o src/inter/DefaultTaskConfigInter.o
	$(CXX) -o $(TARGET) obj/Debug/src/exec/TaskExec.o obj/Debug/src/exec/shcmd/ShellCMDExec.o obj/Debug/src/exec/stexcept.o obj/Debug/src/exec/main/CompileTaskExec.o obj/Debug/src/exec/main/LinkTaskExec.o obj/Debug/src/exec/main/MainExec.o obj/Debug/src/exec/main/ExeLinkTaskExec.o obj/Debug/src/exec/main/CleanTaskExec.o obj/Debug/src/exec/main/DynamicLibraryLinkTaskExec.o obj/Debug/src/exec/main/CopyTaskExec.o obj/Debug/src/exec/ExecManager.o obj/Debug/src/exec/echo/EchoExec.o obj/Debug/src/exec/mkdir/MKDirExec.o obj/Debug/src/exec/cd/CDExec.o obj/Debug/src/exec/rm/RMExec.o obj/Debug/src/exec/ArgManager.o obj/Debug/src/exec/Exec.o obj/Debug/src/exec/cp/CPExec.o obj/Debug/src/main.o obj/Debug/src/darv/Prop.o obj/Debug/src/darv/GenericCMD.o obj/Debug/src/darv/Task.o obj/Debug/src/darv/Statement.o obj/Debug/src/darv/ShellCMD.o obj/Debug/src/darv/DefaultTaskConfig.o obj/Debug/src/darv/CMD.o obj/Debug/src/darv/MainScript.o obj/Debug/src/darv/Block.o obj/Debug/src/darv/Var.o obj/Debug/src/util/strutil.o obj/Debug/src/shell/shell.o obj/Debug/src/shell/output/OutputThread.o obj/Debug/src/shell/output/OutputController.o obj/Debug/src/io/SourceCodeManager.o obj/Debug/src/io/FilesToCompileManager.o obj/Debug/src/io/io.o obj/Debug/src/io/filter/ByNameFileFilter.o obj/Debug/src/msg/messagebuilder.o obj/Debug/src/inter/PropInter.o obj/Debug/src/inter/InterManager.o obj/Debug/src/inter/VarInter.o obj/Debug/src/inter/Inter.o obj/Debug/src/inter/taskconfig/TaskConfigInter.o obj/Debug/src/inter/taskconfig/TaskConfigResult.o obj/Debug/src/inter/InterResult.o obj/Debug/src/inter/MainScriptInter.o obj/Debug/src/inter/TaskInter.o obj/Debug/src/inter/CMDInter.o obj/Debug/src/inter/ShellCMDInter.o obj/Debug/src/inter/it/StringIterator.o obj/Debug/src/inter/it/FileIterator.o obj/Debug/src/inter/DefaultTaskConfigInter.o

src/exec/TaskExec.o:
	$(CXX) $(CXXFLAGS) -o obj/Debug/src/exec/TaskExec.o -c src/exec/TaskExec.cpp

src/exec/shcmd/ShellCMDExec.o:
	$(CXX) $(CXXFLAGS) -o obj/Debug/src/exec/shcmd/ShellCMDExec.o -c src/exec/shcmd/ShellCMDExec.cpp

src/exec/stexcept.o:
	$(CXX) $(CXXFLAGS) -o obj/Debug/src/exec/stexcept.o -c src/exec/stexcept.cpp

src/exec/main/CompileTaskExec.o:
	$(CXX) $(CXXFLAGS) -o obj/Debug/src/exec/main/CompileTaskExec.o -c src/exec/main/CompileTaskExec.cpp

src/exec/main/LinkTaskExec.o:
	$(CXX) $(CXXFLAGS) -o obj/Debug/src/exec/main/LinkTaskExec.o -c src/exec/main/LinkTaskExec.cpp

src/exec/main/MainExec.o:
	$(CXX) $(CXXFLAGS) -o obj/Debug/src/exec/main/MainExec.o -c src/exec/main/MainExec.cpp

src/exec/main/ExeLinkTaskExec.o:
	$(CXX) $(CXXFLAGS) -o obj/Debug/src/exec/main/ExeLinkTaskExec.o -c src/exec/main/ExeLinkTaskExec.cpp

src/exec/main/CleanTaskExec.o:
	$(CXX) $(CXXFLAGS) -o obj/Debug/src/exec/main/CleanTaskExec.o -c src/exec/main/CleanTaskExec.cpp

src/exec/main/DynamicLibraryLinkTaskExec.o:
	$(CXX) $(CXXFLAGS) -o obj/Debug/src/exec/main/DynamicLibraryLinkTaskExec.o -c src/exec/main/DynamicLibraryLinkTaskExec.cpp

src/exec/main/CopyTaskExec.o:
	$(CXX) $(CXXFLAGS) -o obj/Debug/src/exec/main/CopyTaskExec.o -c src/exec/main/CopyTaskExec.cpp

src/exec/ExecManager.o:
	$(CXX) $(CXXFLAGS) -o obj/Debug/src/exec/ExecManager.o -c src/exec/ExecManager.cpp

src/exec/echo/EchoExec.o:
	$(CXX) $(CXXFLAGS) -o obj/Debug/src/exec/echo/EchoExec.o -c src/exec/echo/EchoExec.cpp

src/exec/mkdir/MKDirExec.o:
	$(CXX) $(CXXFLAGS) -o obj/Debug/src/exec/mkdir/MKDirExec.o -c src/exec/mkdir/MKDirExec.cpp

src/exec/cd/CDExec.o:
	$(CXX) $(CXXFLAGS) -o obj/Debug/src/exec/cd/CDExec.o -c src/exec/cd/CDExec.cpp

src/exec/rm/RMExec.o:
	$(CXX) $(CXXFLAGS) -o obj/Debug/src/exec/rm/RMExec.o -c src/exec/rm/RMExec.cpp

src/exec/ArgManager.o:
	$(CXX) $(CXXFLAGS) -o obj/Debug/src/exec/ArgManager.o -c src/exec/ArgManager.cpp

src/exec/Exec.o:
	$(CXX) $(CXXFLAGS) -o obj/Debug/src/exec/Exec.o -c src/exec/Exec.cpp

src/exec/cp/CPExec.o:
	$(CXX) $(CXXFLAGS) -o obj/Debug/src/exec/cp/CPExec.o -c src/exec/cp/CPExec.cpp

src/main.o:
	$(CXX) $(CXXFLAGS) -o obj/Debug/src/main.o -c src/main.cpp

src/darv/Prop.o:
	$(CXX) $(CXXFLAGS) -o obj/Debug/src/darv/Prop.o -c src/darv/Prop.cpp

src/darv/GenericCMD.o:
	$(CXX) $(CXXFLAGS) -o obj/Debug/src/darv/GenericCMD.o -c src/darv/GenericCMD.cpp

src/darv/Task.o:
	$(CXX) $(CXXFLAGS) -o obj/Debug/src/darv/Task.o -c src/darv/Task.cpp

src/darv/Statement.o:
	$(CXX) $(CXXFLAGS) -o obj/Debug/src/darv/Statement.o -c src/darv/Statement.cpp

src/darv/ShellCMD.o:
	$(CXX) $(CXXFLAGS) -o obj/Debug/src/darv/ShellCMD.o -c src/darv/ShellCMD.cpp

src/darv/DefaultTaskConfig.o:
	$(CXX) $(CXXFLAGS) -o obj/Debug/src/darv/DefaultTaskConfig.o -c src/darv/DefaultTaskConfig.cpp

src/darv/CMD.o:
	$(CXX) $(CXXFLAGS) -o obj/Debug/src/darv/CMD.o -c src/darv/CMD.cpp

src/darv/MainScript.o:
	$(CXX) $(CXXFLAGS) -o obj/Debug/src/darv/MainScript.o -c src/darv/MainScript.cpp

src/darv/Block.o:
	$(CXX) $(CXXFLAGS) -o obj/Debug/src/darv/Block.o -c src/darv/Block.cpp

src/darv/Var.o:
	$(CXX) $(CXXFLAGS) -o obj/Debug/src/darv/Var.o -c src/darv/Var.cpp

src/util/strutil.o:
	$(CXX) $(CXXFLAGS) -o obj/Debug/src/util/strutil.o -c src/util/strutil.cpp

src/shell/shell.o:
	$(CXX) $(CXXFLAGS) -o obj/Debug/src/shell/shell.o -c src/shell/shell.cpp

src/shell/output/OutputThread.o:
	$(CXX) $(CXXFLAGS) -o obj/Debug/src/shell/output/OutputThread.o -c src/shell/output/OutputThread.cpp

src/shell/output/OutputController.o:
	$(CXX) $(CXXFLAGS) -o obj/Debug/src/shell/output/OutputController.o -c src/shell/output/OutputController.cpp

src/io/SourceCodeManager.o:
	$(CXX) $(CXXFLAGS) -o obj/Debug/src/io/SourceCodeManager.o -c src/io/SourceCodeManager.cpp

src/io/FilesToCompileManager.o:
	$(CXX) $(CXXFLAGS) -o obj/Debug/src/io/FilesToCompileManager.o -c src/io/FilesToCompileManager.cpp

src/io/io.o:
	$(CXX) $(CXXFLAGS) -o obj/Debug/src/io/io.o -c src/io/io.cpp

src/io/filter/ByNameFileFilter.o:
	$(CXX) $(CXXFLAGS) -o obj/Debug/src/io/filter/ByNameFileFilter.o -c src/io/filter/ByNameFileFilter.cpp

src/msg/messagebuilder.o:
	$(CXX) $(CXXFLAGS) -o obj/Debug/src/msg/messagebuilder.o -c src/msg/messagebuilder.cpp

src/inter/PropInter.o:
	$(CXX) $(CXXFLAGS) -o obj/Debug/src/inter/PropInter.o -c src/inter/PropInter.cpp

src/inter/InterManager.o:
	$(CXX) $(CXXFLAGS) -o obj/Debug/src/inter/InterManager.o -c src/inter/InterManager.cpp

src/inter/VarInter.o:
	$(CXX) $(CXXFLAGS) -o obj/Debug/src/inter/VarInter.o -c src/inter/VarInter.cpp

src/inter/Inter.o:
	$(CXX) $(CXXFLAGS) -o obj/Debug/src/inter/Inter.o -c src/inter/Inter.cpp

src/inter/taskconfig/TaskConfigInter.o:
	$(CXX) $(CXXFLAGS) -o obj/Debug/src/inter/taskconfig/TaskConfigInter.o -c src/inter/taskconfig/TaskConfigInter.cpp

src/inter/taskconfig/TaskConfigResult.o:
	$(CXX) $(CXXFLAGS) -o obj/Debug/src/inter/taskconfig/TaskConfigResult.o -c src/inter/taskconfig/TaskConfigResult.cpp

src/inter/InterResult.o:
	$(CXX) $(CXXFLAGS) -o obj/Debug/src/inter/InterResult.o -c src/inter/InterResult.cpp

src/inter/MainScriptInter.o:
	$(CXX) $(CXXFLAGS) -o obj/Debug/src/inter/MainScriptInter.o -c src/inter/MainScriptInter.cpp

src/inter/TaskInter.o:
	$(CXX) $(CXXFLAGS) -o obj/Debug/src/inter/TaskInter.o -c src/inter/TaskInter.cpp

src/inter/CMDInter.o:
	$(CXX) $(CXXFLAGS) -o obj/Debug/src/inter/CMDInter.o -c src/inter/CMDInter.cpp

src/inter/ShellCMDInter.o:
	$(CXX) $(CXXFLAGS) -o obj/Debug/src/inter/ShellCMDInter.o -c src/inter/ShellCMDInter.cpp

src/inter/it/StringIterator.o:
	$(CXX) $(CXXFLAGS) -o obj/Debug/src/inter/it/StringIterator.o -c src/inter/it/StringIterator.cpp

src/inter/it/FileIterator.o:
	$(CXX) $(CXXFLAGS) -o obj/Debug/src/inter/it/FileIterator.o -c src/inter/it/FileIterator.cpp

src/inter/DefaultTaskConfigInter.o:
	$(CXX) $(CXXFLAGS) -o obj/Debug/src/inter/DefaultTaskConfigInter.o -c src/inter/DefaultTaskConfigInter.cpp

