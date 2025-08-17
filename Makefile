
CXX=g++
CXXFLAGS=-Wall -g
TARGET=cbuild

.PHONY: all

all: $(TARGET)

$(TARGET): src/io/io.o src/io/SourceCodeManager.o src/io/filter/AllFileFilter.o src/io/filter/ByExtFileFilter.o src/io/FilesToCompileManager.o src/msg/messagebuilder.o src/darv/Task.o src/darv/Block.o src/darv/ShellCMD.o src/darv/MainScript.o src/darv/Var.o src/darv/Prop.o src/darv/CMD.o src/darv/Statement.o src/shell/shell.o src/inter/InterResult.o src/inter/VarInter.o src/inter/TaskInter.o src/inter/PropInter.o src/inter/CMDInter.o src/inter/Inter.o src/inter/InterManager.o src/inter/it/FileIterator.o src/inter/it/StringIterator.o src/inter/MainScriptInter.o src/inter/ShellCMDInter.o src/util/strutil.o src/exec/rm/RMExec.o src/exec/main/MainExec.o src/exec/main/CompileTaskExec.o src/exec/main/CopyTaskExec.o src/exec/main/LinkTaskExec.o src/exec/main/CleanTaskExec.o src/exec/ExecManager.o src/exec/cd/CDExec.o src/exec/Exec.o src/exec/shcmd/ShellCMDExec.o src/exec/cp/CPExec.o src/exec/echo/EchoExec.o src/exec/mkdir/MKDirExec.o src/exec/TaskExec.o src/exec/stexcept.o src/main.o
	$(CXX) -o $(TARGET) obj/Debug/src/io/io.o obj/Debug/src/io/SourceCodeManager.o obj/Debug/src/io/filter/AllFileFilter.o obj/Debug/src/io/filter/ByExtFileFilter.o obj/Debug/src/io/FilesToCompileManager.o obj/Debug/src/msg/messagebuilder.o obj/Debug/src/darv/Task.o obj/Debug/src/darv/Block.o obj/Debug/src/darv/ShellCMD.o obj/Debug/src/darv/MainScript.o obj/Debug/src/darv/Var.o obj/Debug/src/darv/Prop.o obj/Debug/src/darv/CMD.o obj/Debug/src/darv/Statement.o obj/Debug/src/shell/shell.o obj/Debug/src/inter/InterResult.o obj/Debug/src/inter/VarInter.o obj/Debug/src/inter/TaskInter.o obj/Debug/src/inter/PropInter.o obj/Debug/src/inter/CMDInter.o obj/Debug/src/inter/Inter.o obj/Debug/src/inter/InterManager.o obj/Debug/src/inter/it/FileIterator.o obj/Debug/src/inter/it/StringIterator.o obj/Debug/src/inter/MainScriptInter.o obj/Debug/src/inter/ShellCMDInter.o obj/Debug/src/util/strutil.o obj/Debug/src/exec/rm/RMExec.o obj/Debug/src/exec/main/MainExec.o obj/Debug/src/exec/main/CompileTaskExec.o obj/Debug/src/exec/main/CopyTaskExec.o obj/Debug/src/exec/main/LinkTaskExec.o obj/Debug/src/exec/main/CleanTaskExec.o obj/Debug/src/exec/ExecManager.o obj/Debug/src/exec/cd/CDExec.o obj/Debug/src/exec/Exec.o obj/Debug/src/exec/shcmd/ShellCMDExec.o obj/Debug/src/exec/cp/CPExec.o obj/Debug/src/exec/echo/EchoExec.o obj/Debug/src/exec/mkdir/MKDirExec.o obj/Debug/src/exec/TaskExec.o obj/Debug/src/exec/stexcept.o obj/Debug/src/main.o

src/io/io.o:
	$(CXX) $(CXXFLAGS) -o obj/Debug/src/io/io.o -c src/io/io.cpp

src/io/SourceCodeManager.o:
	$(CXX) $(CXXFLAGS) -o obj/Debug/src/io/SourceCodeManager.o -c src/io/SourceCodeManager.cpp

src/io/filter/AllFileFilter.o:
	$(CXX) $(CXXFLAGS) -o obj/Debug/src/io/filter/AllFileFilter.o -c src/io/filter/AllFileFilter.cpp

src/io/filter/ByExtFileFilter.o:
	$(CXX) $(CXXFLAGS) -o obj/Debug/src/io/filter/ByExtFileFilter.o -c src/io/filter/ByExtFileFilter.cpp

src/io/FilesToCompileManager.o:
	$(CXX) $(CXXFLAGS) -o obj/Debug/src/io/FilesToCompileManager.o -c src/io/FilesToCompileManager.cpp

src/msg/messagebuilder.o:
	$(CXX) $(CXXFLAGS) -o obj/Debug/src/msg/messagebuilder.o -c src/msg/messagebuilder.cpp

src/darv/Task.o:
	$(CXX) $(CXXFLAGS) -o obj/Debug/src/darv/Task.o -c src/darv/Task.cpp

src/darv/Block.o:
	$(CXX) $(CXXFLAGS) -o obj/Debug/src/darv/Block.o -c src/darv/Block.cpp

src/darv/ShellCMD.o:
	$(CXX) $(CXXFLAGS) -o obj/Debug/src/darv/ShellCMD.o -c src/darv/ShellCMD.cpp

src/darv/MainScript.o:
	$(CXX) $(CXXFLAGS) -o obj/Debug/src/darv/MainScript.o -c src/darv/MainScript.cpp

src/darv/Var.o:
	$(CXX) $(CXXFLAGS) -o obj/Debug/src/darv/Var.o -c src/darv/Var.cpp

src/darv/Prop.o:
	$(CXX) $(CXXFLAGS) -o obj/Debug/src/darv/Prop.o -c src/darv/Prop.cpp

src/darv/CMD.o:
	$(CXX) $(CXXFLAGS) -o obj/Debug/src/darv/CMD.o -c src/darv/CMD.cpp

src/darv/Statement.o:
	$(CXX) $(CXXFLAGS) -o obj/Debug/src/darv/Statement.o -c src/darv/Statement.cpp

src/shell/shell.o:
	$(CXX) $(CXXFLAGS) -o obj/Debug/src/shell/shell.o -c src/shell/shell.cpp

src/inter/InterResult.o:
	$(CXX) $(CXXFLAGS) -o obj/Debug/src/inter/InterResult.o -c src/inter/InterResult.cpp

src/inter/VarInter.o:
	$(CXX) $(CXXFLAGS) -o obj/Debug/src/inter/VarInter.o -c src/inter/VarInter.cpp

src/inter/TaskInter.o:
	$(CXX) $(CXXFLAGS) -o obj/Debug/src/inter/TaskInter.o -c src/inter/TaskInter.cpp

src/inter/PropInter.o:
	$(CXX) $(CXXFLAGS) -o obj/Debug/src/inter/PropInter.o -c src/inter/PropInter.cpp

src/inter/CMDInter.o:
	$(CXX) $(CXXFLAGS) -o obj/Debug/src/inter/CMDInter.o -c src/inter/CMDInter.cpp

src/inter/Inter.o:
	$(CXX) $(CXXFLAGS) -o obj/Debug/src/inter/Inter.o -c src/inter/Inter.cpp

src/inter/InterManager.o:
	$(CXX) $(CXXFLAGS) -o obj/Debug/src/inter/InterManager.o -c src/inter/InterManager.cpp

src/inter/it/FileIterator.o:
	$(CXX) $(CXXFLAGS) -o obj/Debug/src/inter/it/FileIterator.o -c src/inter/it/FileIterator.cpp

src/inter/it/StringIterator.o:
	$(CXX) $(CXXFLAGS) -o obj/Debug/src/inter/it/StringIterator.o -c src/inter/it/StringIterator.cpp

src/inter/MainScriptInter.o:
	$(CXX) $(CXXFLAGS) -o obj/Debug/src/inter/MainScriptInter.o -c src/inter/MainScriptInter.cpp

src/inter/ShellCMDInter.o:
	$(CXX) $(CXXFLAGS) -o obj/Debug/src/inter/ShellCMDInter.o -c src/inter/ShellCMDInter.cpp

src/util/strutil.o:
	$(CXX) $(CXXFLAGS) -o obj/Debug/src/util/strutil.o -c src/util/strutil.cpp

src/exec/rm/RMExec.o:
	$(CXX) $(CXXFLAGS) -o obj/Debug/src/exec/rm/RMExec.o -c src/exec/rm/RMExec.cpp

src/exec/main/MainExec.o:
	$(CXX) $(CXXFLAGS) -o obj/Debug/src/exec/main/MainExec.o -c src/exec/main/MainExec.cpp

src/exec/main/CompileTaskExec.o:
	$(CXX) $(CXXFLAGS) -o obj/Debug/src/exec/main/CompileTaskExec.o -c src/exec/main/CompileTaskExec.cpp

src/exec/main/CopyTaskExec.o:
	$(CXX) $(CXXFLAGS) -o obj/Debug/src/exec/main/CopyTaskExec.o -c src/exec/main/CopyTaskExec.cpp

src/exec/main/LinkTaskExec.o:
	$(CXX) $(CXXFLAGS) -o obj/Debug/src/exec/main/LinkTaskExec.o -c src/exec/main/LinkTaskExec.cpp

src/exec/main/CleanTaskExec.o:
	$(CXX) $(CXXFLAGS) -o obj/Debug/src/exec/main/CleanTaskExec.o -c src/exec/main/CleanTaskExec.cpp

src/exec/ExecManager.o:
	$(CXX) $(CXXFLAGS) -o obj/Debug/src/exec/ExecManager.o -c src/exec/ExecManager.cpp

src/exec/cd/CDExec.o:
	$(CXX) $(CXXFLAGS) -o obj/Debug/src/exec/cd/CDExec.o -c src/exec/cd/CDExec.cpp

src/exec/Exec.o:
	$(CXX) $(CXXFLAGS) -o obj/Debug/src/exec/Exec.o -c src/exec/Exec.cpp

src/exec/shcmd/ShellCMDExec.o:
	$(CXX) $(CXXFLAGS) -o obj/Debug/src/exec/shcmd/ShellCMDExec.o -c src/exec/shcmd/ShellCMDExec.cpp

src/exec/cp/CPExec.o:
	$(CXX) $(CXXFLAGS) -o obj/Debug/src/exec/cp/CPExec.o -c src/exec/cp/CPExec.cpp

src/exec/echo/EchoExec.o:
	$(CXX) $(CXXFLAGS) -o obj/Debug/src/exec/echo/EchoExec.o -c src/exec/echo/EchoExec.cpp

src/exec/mkdir/MKDirExec.o:
	$(CXX) $(CXXFLAGS) -o obj/Debug/src/exec/mkdir/MKDirExec.o -c src/exec/mkdir/MKDirExec.cpp

src/exec/TaskExec.o:
	$(CXX) $(CXXFLAGS) -o obj/Debug/src/exec/TaskExec.o -c src/exec/TaskExec.cpp

src/exec/stexcept.o:
	$(CXX) $(CXXFLAGS) -o obj/Debug/src/exec/stexcept.o -c src/exec/stexcept.cpp

src/main.o:
	$(CXX) $(CXXFLAGS) -o obj/Debug/src/main.o -c src/main.cpp

