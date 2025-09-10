
CXX=g++
CXXFLAGS=-Wall -g
TARGET=cbuild

.PHONY: all

all: $(TARGET)

$(TARGET): src/exec/MainCMDArgManager.o src/exec/shcmd/ShellCMDLineExec.o src/exec/stexcept.o src/exec/main/TaskExec.o src/exec/main/MainExec.o src/exec/main/task/CompileTaskExec.o src/exec/main/task/TestTaskExec.o src/exec/main/task/ArchiveTaskExec.o src/exec/main/task/LinkOrArchiveTaskExec.o src/exec/main/task/ExeLinkTaskExec.o src/exec/main/task/CleanTaskExec.o src/exec/main/task/DynamicLibraryLinkTaskExec.o src/exec/main/task/CopyTaskExec.o src/exec/main/MainCMDInterpreter.o src/exec/call/CallExec.o src/exec/ScriptPropertyManager.o src/exec/ExecManager.o src/exec/cmd/echo/EchoExec.o src/exec/cmd/CMDExec.o src/exec/cmd/mkdir/MKDirExec.o src/exec/cmd/cd/CDExec.o src/exec/cmd/rm/RMExec.o src/exec/cmd/cp/CPExec.o src/exec/if/IFExec.o src/exec/varattr/VarAttrExec.o src/main.o src/darv/Prop.o src/darv/IFCondition.o src/darv/GenericCMD.o src/darv/Task.o src/darv/ShellCMDLine.o src/darv/Statement.o src/darv/DefaultTaskConfig.o src/darv/IF.o src/darv/CMD.o src/darv/MainScript.o src/darv/Block.o src/darv/Var.o src/darv/VarAttr.o src/darv/CallCMD.o src/darv/Proc.o src/util/hashutil.o src/util/strutil.o src/sourcecode/SourceCodeManager.o src/sourcecode/FilesToCompileManager.o src/sourcecode/IncludesSCInterpreter.o src/sourcecode/ClassesSCInterpreter.o src/sourcecode/LWTimesFileIO.o src/sourcecode/DependenciesSCLoader.o src/shell/shell.o src/shell/output/OutputThread.o src/shell/output/OutputController.o src/compiler/Archiver.o src/compiler/Linker.o src/compiler/DynamicLibraryLinker.o src/compiler/Compiler.o src/output/output.o src/io/io.o src/io/filter/ByNameFileFilter.o src/msg/messagebuilder.o src/inter/PropInter.o src/inter/ProcInter.o src/inter/InterManager.o src/inter/BlockInter.o src/inter/VarInter.o src/inter/preproc/PreProcessor.o src/inter/ConcreteBlockInter.o src/inter/ShellCMDLineInter.o src/inter/if/IFConditionInter.o src/inter/InterResult.o src/inter/block/BlockInterResult.o src/inter/MainScriptInter.o src/inter/TaskInter.o src/inter/CMDInter.o src/inter/taskdef/TaskDefinitionInter.o src/inter/taskdef/TaskDefinitionResult.o src/inter/IFInter.o src/inter/PropsAndVarsReplacer.o src/inter/it/StringIterator.o src/inter/it/FileIterator.o src/inter/VarAttrInter.o src/inter/DefaultTaskConfigInter.o
	$(CXX) -o $(TARGET) obj/Release/src/exec/MainCMDArgManager.o obj/Release/src/exec/shcmd/ShellCMDLineExec.o obj/Release/src/exec/stexcept.o obj/Release/src/exec/main/TaskExec.o obj/Release/src/exec/main/MainExec.o obj/Release/src/exec/main/task/CompileTaskExec.o obj/Release/src/exec/main/task/TestTaskExec.o obj/Release/src/exec/main/task/ArchiveTaskExec.o obj/Release/src/exec/main/task/LinkOrArchiveTaskExec.o obj/Release/src/exec/main/task/ExeLinkTaskExec.o obj/Release/src/exec/main/task/CleanTaskExec.o obj/Release/src/exec/main/task/DynamicLibraryLinkTaskExec.o obj/Release/src/exec/main/task/CopyTaskExec.o obj/Release/src/exec/main/MainCMDInterpreter.o obj/Release/src/exec/call/CallExec.o obj/Release/src/exec/ScriptPropertyManager.o obj/Release/src/exec/ExecManager.o obj/Release/src/exec/cmd/echo/EchoExec.o obj/Release/src/exec/cmd/CMDExec.o obj/Release/src/exec/cmd/mkdir/MKDirExec.o obj/Release/src/exec/cmd/cd/CDExec.o obj/Release/src/exec/cmd/rm/RMExec.o obj/Release/src/exec/cmd/cp/CPExec.o obj/Release/src/exec/if/IFExec.o obj/Release/src/exec/varattr/VarAttrExec.o obj/Release/src/main.o obj/Release/src/darv/Prop.o obj/Release/src/darv/IFCondition.o obj/Release/src/darv/GenericCMD.o obj/Release/src/darv/Task.o obj/Release/src/darv/ShellCMDLine.o obj/Release/src/darv/Statement.o obj/Release/src/darv/DefaultTaskConfig.o obj/Release/src/darv/IF.o obj/Release/src/darv/CMD.o obj/Release/src/darv/MainScript.o obj/Release/src/darv/Block.o obj/Release/src/darv/Var.o obj/Release/src/darv/VarAttr.o obj/Release/src/darv/CallCMD.o obj/Release/src/darv/Proc.o obj/Release/src/util/hashutil.o obj/Release/src/util/strutil.o obj/Release/src/sourcecode/SourceCodeManager.o obj/Release/src/sourcecode/FilesToCompileManager.o obj/Release/src/sourcecode/IncludesSCInterpreter.o obj/Release/src/sourcecode/ClassesSCInterpreter.o obj/Release/src/sourcecode/LWTimesFileIO.o obj/Release/src/sourcecode/DependenciesSCLoader.o obj/Release/src/shell/shell.o obj/Release/src/shell/output/OutputThread.o obj/Release/src/shell/output/OutputController.o obj/Release/src/compiler/Archiver.o obj/Release/src/compiler/Linker.o obj/Release/src/compiler/DynamicLibraryLinker.o obj/Release/src/compiler/Compiler.o obj/Release/src/output/output.o obj/Release/src/io/io.o obj/Release/src/io/filter/ByNameFileFilter.o obj/Release/src/msg/messagebuilder.o obj/Release/src/inter/PropInter.o obj/Release/src/inter/ProcInter.o obj/Release/src/inter/InterManager.o obj/Release/src/inter/BlockInter.o obj/Release/src/inter/VarInter.o obj/Release/src/inter/preproc/PreProcessor.o obj/Release/src/inter/ConcreteBlockInter.o obj/Release/src/inter/ShellCMDLineInter.o obj/Release/src/inter/if/IFConditionInter.o obj/Release/src/inter/InterResult.o obj/Release/src/inter/block/BlockInterResult.o obj/Release/src/inter/MainScriptInter.o obj/Release/src/inter/TaskInter.o obj/Release/src/inter/CMDInter.o obj/Release/src/inter/taskdef/TaskDefinitionInter.o obj/Release/src/inter/taskdef/TaskDefinitionResult.o obj/Release/src/inter/IFInter.o obj/Release/src/inter/PropsAndVarsReplacer.o obj/Release/src/inter/it/StringIterator.o obj/Release/src/inter/it/FileIterator.o obj/Release/src/inter/VarAttrInter.o obj/Release/src/inter/DefaultTaskConfigInter.o 

src/exec/MainCMDArgManager.o:
	$(CXX) $(CXXFLAGS) -o obj/Release/src/exec/MainCMDArgManager.o -c src/exec/MainCMDArgManager.cpp

src/exec/shcmd/ShellCMDLineExec.o:
	$(CXX) $(CXXFLAGS) -o obj/Release/src/exec/shcmd/ShellCMDLineExec.o -c src/exec/shcmd/ShellCMDLineExec.cpp

src/exec/stexcept.o:
	$(CXX) $(CXXFLAGS) -o obj/Release/src/exec/stexcept.o -c src/exec/stexcept.cpp

src/exec/main/TaskExec.o:
	$(CXX) $(CXXFLAGS) -o obj/Release/src/exec/main/TaskExec.o -c src/exec/main/TaskExec.cpp

src/exec/main/MainExec.o:
	$(CXX) $(CXXFLAGS) -o obj/Release/src/exec/main/MainExec.o -c src/exec/main/MainExec.cpp

src/exec/main/task/CompileTaskExec.o:
	$(CXX) $(CXXFLAGS) -o obj/Release/src/exec/main/task/CompileTaskExec.o -c src/exec/main/task/CompileTaskExec.cpp

src/exec/main/task/TestTaskExec.o:
	$(CXX) $(CXXFLAGS) -o obj/Release/src/exec/main/task/TestTaskExec.o -c src/exec/main/task/TestTaskExec.cpp

src/exec/main/task/ArchiveTaskExec.o:
	$(CXX) $(CXXFLAGS) -o obj/Release/src/exec/main/task/ArchiveTaskExec.o -c src/exec/main/task/ArchiveTaskExec.cpp

src/exec/main/task/LinkOrArchiveTaskExec.o:
	$(CXX) $(CXXFLAGS) -o obj/Release/src/exec/main/task/LinkOrArchiveTaskExec.o -c src/exec/main/task/LinkOrArchiveTaskExec.cpp

src/exec/main/task/ExeLinkTaskExec.o:
	$(CXX) $(CXXFLAGS) -o obj/Release/src/exec/main/task/ExeLinkTaskExec.o -c src/exec/main/task/ExeLinkTaskExec.cpp

src/exec/main/task/CleanTaskExec.o:
	$(CXX) $(CXXFLAGS) -o obj/Release/src/exec/main/task/CleanTaskExec.o -c src/exec/main/task/CleanTaskExec.cpp

src/exec/main/task/DynamicLibraryLinkTaskExec.o:
	$(CXX) $(CXXFLAGS) -o obj/Release/src/exec/main/task/DynamicLibraryLinkTaskExec.o -c src/exec/main/task/DynamicLibraryLinkTaskExec.cpp

src/exec/main/task/CopyTaskExec.o:
	$(CXX) $(CXXFLAGS) -o obj/Release/src/exec/main/task/CopyTaskExec.o -c src/exec/main/task/CopyTaskExec.cpp

src/exec/main/MainCMDInterpreter.o:
	$(CXX) $(CXXFLAGS) -o obj/Release/src/exec/main/MainCMDInterpreter.o -c src/exec/main/MainCMDInterpreter.cpp

src/exec/call/CallExec.o:
	$(CXX) $(CXXFLAGS) -o obj/Release/src/exec/call/CallExec.o -c src/exec/call/CallExec.cpp

src/exec/ScriptPropertyManager.o:
	$(CXX) $(CXXFLAGS) -o obj/Release/src/exec/ScriptPropertyManager.o -c src/exec/ScriptPropertyManager.cpp

src/exec/ExecManager.o:
	$(CXX) $(CXXFLAGS) -o obj/Release/src/exec/ExecManager.o -c src/exec/ExecManager.cpp

src/exec/cmd/echo/EchoExec.o:
	$(CXX) $(CXXFLAGS) -o obj/Release/src/exec/cmd/echo/EchoExec.o -c src/exec/cmd/echo/EchoExec.cpp

src/exec/cmd/CMDExec.o:
	$(CXX) $(CXXFLAGS) -o obj/Release/src/exec/cmd/CMDExec.o -c src/exec/cmd/CMDExec.cpp

src/exec/cmd/mkdir/MKDirExec.o:
	$(CXX) $(CXXFLAGS) -o obj/Release/src/exec/cmd/mkdir/MKDirExec.o -c src/exec/cmd/mkdir/MKDirExec.cpp

src/exec/cmd/cd/CDExec.o:
	$(CXX) $(CXXFLAGS) -o obj/Release/src/exec/cmd/cd/CDExec.o -c src/exec/cmd/cd/CDExec.cpp

src/exec/cmd/rm/RMExec.o:
	$(CXX) $(CXXFLAGS) -o obj/Release/src/exec/cmd/rm/RMExec.o -c src/exec/cmd/rm/RMExec.cpp

src/exec/cmd/cp/CPExec.o:
	$(CXX) $(CXXFLAGS) -o obj/Release/src/exec/cmd/cp/CPExec.o -c src/exec/cmd/cp/CPExec.cpp

src/exec/if/IFExec.o:
	$(CXX) $(CXXFLAGS) -o obj/Release/src/exec/if/IFExec.o -c src/exec/if/IFExec.cpp

src/exec/varattr/VarAttrExec.o:
	$(CXX) $(CXXFLAGS) -o obj/Release/src/exec/varattr/VarAttrExec.o -c src/exec/varattr/VarAttrExec.cpp

src/main.o:
	$(CXX) $(CXXFLAGS) -o obj/Release/src/main.o -c src/main.cpp

src/darv/Prop.o:
	$(CXX) $(CXXFLAGS) -o obj/Release/src/darv/Prop.o -c src/darv/Prop.cpp

src/darv/IFCondition.o:
	$(CXX) $(CXXFLAGS) -o obj/Release/src/darv/IFCondition.o -c src/darv/IFCondition.cpp

src/darv/GenericCMD.o:
	$(CXX) $(CXXFLAGS) -o obj/Release/src/darv/GenericCMD.o -c src/darv/GenericCMD.cpp

src/darv/Task.o:
	$(CXX) $(CXXFLAGS) -o obj/Release/src/darv/Task.o -c src/darv/Task.cpp

src/darv/ShellCMDLine.o:
	$(CXX) $(CXXFLAGS) -o obj/Release/src/darv/ShellCMDLine.o -c src/darv/ShellCMDLine.cpp

src/darv/Statement.o:
	$(CXX) $(CXXFLAGS) -o obj/Release/src/darv/Statement.o -c src/darv/Statement.cpp

src/darv/DefaultTaskConfig.o:
	$(CXX) $(CXXFLAGS) -o obj/Release/src/darv/DefaultTaskConfig.o -c src/darv/DefaultTaskConfig.cpp

src/darv/IF.o:
	$(CXX) $(CXXFLAGS) -o obj/Release/src/darv/IF.o -c src/darv/IF.cpp

src/darv/CMD.o:
	$(CXX) $(CXXFLAGS) -o obj/Release/src/darv/CMD.o -c src/darv/CMD.cpp

src/darv/MainScript.o:
	$(CXX) $(CXXFLAGS) -o obj/Release/src/darv/MainScript.o -c src/darv/MainScript.cpp

src/darv/Block.o:
	$(CXX) $(CXXFLAGS) -o obj/Release/src/darv/Block.o -c src/darv/Block.cpp

src/darv/Var.o:
	$(CXX) $(CXXFLAGS) -o obj/Release/src/darv/Var.o -c src/darv/Var.cpp

src/darv/VarAttr.o:
	$(CXX) $(CXXFLAGS) -o obj/Release/src/darv/VarAttr.o -c src/darv/VarAttr.cpp

src/darv/CallCMD.o:
	$(CXX) $(CXXFLAGS) -o obj/Release/src/darv/CallCMD.o -c src/darv/CallCMD.cpp

src/darv/Proc.o:
	$(CXX) $(CXXFLAGS) -o obj/Release/src/darv/Proc.o -c src/darv/Proc.cpp

src/util/hashutil.o:
	$(CXX) $(CXXFLAGS) -o obj/Release/src/util/hashutil.o -c src/util/hashutil.cpp

src/util/strutil.o:
	$(CXX) $(CXXFLAGS) -o obj/Release/src/util/strutil.o -c src/util/strutil.cpp

src/sourcecode/SourceCodeManager.o:
	$(CXX) $(CXXFLAGS) -o obj/Release/src/sourcecode/SourceCodeManager.o -c src/sourcecode/SourceCodeManager.cpp

src/sourcecode/FilesToCompileManager.o:
	$(CXX) $(CXXFLAGS) -o obj/Release/src/sourcecode/FilesToCompileManager.o -c src/sourcecode/FilesToCompileManager.cpp

src/sourcecode/IncludesSCInterpreter.o:
	$(CXX) $(CXXFLAGS) -o obj/Release/src/sourcecode/IncludesSCInterpreter.o -c src/sourcecode/IncludesSCInterpreter.cpp

src/sourcecode/ClassesSCInterpreter.o:
	$(CXX) $(CXXFLAGS) -o obj/Release/src/sourcecode/ClassesSCInterpreter.o -c src/sourcecode/ClassesSCInterpreter.cpp

src/sourcecode/LWTimesFileIO.o:
	$(CXX) $(CXXFLAGS) -o obj/Release/src/sourcecode/LWTimesFileIO.o -c src/sourcecode/LWTimesFileIO.cpp

src/sourcecode/DependenciesSCLoader.o:
	$(CXX) $(CXXFLAGS) -o obj/Release/src/sourcecode/DependenciesSCLoader.o -c src/sourcecode/DependenciesSCLoader.cpp

src/shell/shell.o:
	$(CXX) $(CXXFLAGS) -o obj/Release/src/shell/shell.o -c src/shell/shell.cpp

src/shell/output/OutputThread.o:
	$(CXX) $(CXXFLAGS) -o obj/Release/src/shell/output/OutputThread.o -c src/shell/output/OutputThread.cpp

src/shell/output/OutputController.o:
	$(CXX) $(CXXFLAGS) -o obj/Release/src/shell/output/OutputController.o -c src/shell/output/OutputController.cpp

src/compiler/Archiver.o:
	$(CXX) $(CXXFLAGS) -o obj/Release/src/compiler/Archiver.o -c src/compiler/Archiver.cpp

src/compiler/Linker.o:
	$(CXX) $(CXXFLAGS) -o obj/Release/src/compiler/Linker.o -c src/compiler/Linker.cpp

src/compiler/DynamicLibraryLinker.o:
	$(CXX) $(CXXFLAGS) -o obj/Release/src/compiler/DynamicLibraryLinker.o -c src/compiler/DynamicLibraryLinker.cpp

src/compiler/Compiler.o:
	$(CXX) $(CXXFLAGS) -o obj/Release/src/compiler/Compiler.o -c src/compiler/Compiler.cpp

src/output/output.o:
	$(CXX) $(CXXFLAGS) -o obj/Release/src/output/output.o -c src/output/output.cpp

src/io/io.o:
	$(CXX) $(CXXFLAGS) -o obj/Release/src/io/io.o -c src/io/io.cpp

src/io/filter/ByNameFileFilter.o:
	$(CXX) $(CXXFLAGS) -o obj/Release/src/io/filter/ByNameFileFilter.o -c src/io/filter/ByNameFileFilter.cpp

src/msg/messagebuilder.o:
	$(CXX) $(CXXFLAGS) -o obj/Release/src/msg/messagebuilder.o -c src/msg/messagebuilder.cpp

src/inter/PropInter.o:
	$(CXX) $(CXXFLAGS) -o obj/Release/src/inter/PropInter.o -c src/inter/PropInter.cpp

src/inter/ProcInter.o:
	$(CXX) $(CXXFLAGS) -o obj/Release/src/inter/ProcInter.o -c src/inter/ProcInter.cpp

src/inter/InterManager.o:
	$(CXX) $(CXXFLAGS) -o obj/Release/src/inter/InterManager.o -c src/inter/InterManager.cpp

src/inter/BlockInter.o:
	$(CXX) $(CXXFLAGS) -o obj/Release/src/inter/BlockInter.o -c src/inter/BlockInter.cpp

src/inter/VarInter.o:
	$(CXX) $(CXXFLAGS) -o obj/Release/src/inter/VarInter.o -c src/inter/VarInter.cpp

src/inter/preproc/PreProcessor.o:
	$(CXX) $(CXXFLAGS) -o obj/Release/src/inter/preproc/PreProcessor.o -c src/inter/preproc/PreProcessor.cpp

src/inter/ConcreteBlockInter.o:
	$(CXX) $(CXXFLAGS) -o obj/Release/src/inter/ConcreteBlockInter.o -c src/inter/ConcreteBlockInter.cpp

src/inter/ShellCMDLineInter.o:
	$(CXX) $(CXXFLAGS) -o obj/Release/src/inter/ShellCMDLineInter.o -c src/inter/ShellCMDLineInter.cpp

src/inter/if/IFConditionInter.o:
	$(CXX) $(CXXFLAGS) -o obj/Release/src/inter/if/IFConditionInter.o -c src/inter/if/IFConditionInter.cpp

src/inter/InterResult.o:
	$(CXX) $(CXXFLAGS) -o obj/Release/src/inter/InterResult.o -c src/inter/InterResult.cpp

src/inter/block/BlockInterResult.o:
	$(CXX) $(CXXFLAGS) -o obj/Release/src/inter/block/BlockInterResult.o -c src/inter/block/BlockInterResult.cpp

src/inter/MainScriptInter.o:
	$(CXX) $(CXXFLAGS) -o obj/Release/src/inter/MainScriptInter.o -c src/inter/MainScriptInter.cpp

src/inter/TaskInter.o:
	$(CXX) $(CXXFLAGS) -o obj/Release/src/inter/TaskInter.o -c src/inter/TaskInter.cpp

src/inter/CMDInter.o:
	$(CXX) $(CXXFLAGS) -o obj/Release/src/inter/CMDInter.o -c src/inter/CMDInter.cpp

src/inter/taskdef/TaskDefinitionInter.o:
	$(CXX) $(CXXFLAGS) -o obj/Release/src/inter/taskdef/TaskDefinitionInter.o -c src/inter/taskdef/TaskDefinitionInter.cpp

src/inter/taskdef/TaskDefinitionResult.o:
	$(CXX) $(CXXFLAGS) -o obj/Release/src/inter/taskdef/TaskDefinitionResult.o -c src/inter/taskdef/TaskDefinitionResult.cpp

src/inter/IFInter.o:
	$(CXX) $(CXXFLAGS) -o obj/Release/src/inter/IFInter.o -c src/inter/IFInter.cpp

src/inter/PropsAndVarsReplacer.o:
	$(CXX) $(CXXFLAGS) -o obj/Release/src/inter/PropsAndVarsReplacer.o -c src/inter/PropsAndVarsReplacer.cpp

src/inter/it/StringIterator.o:
	$(CXX) $(CXXFLAGS) -o obj/Release/src/inter/it/StringIterator.o -c src/inter/it/StringIterator.cpp

src/inter/it/FileIterator.o:
	$(CXX) $(CXXFLAGS) -o obj/Release/src/inter/it/FileIterator.o -c src/inter/it/FileIterator.cpp

src/inter/VarAttrInter.o:
	$(CXX) $(CXXFLAGS) -o obj/Release/src/inter/VarAttrInter.o -c src/inter/VarAttrInter.cpp

src/inter/DefaultTaskConfigInter.o:
	$(CXX) $(CXXFLAGS) -o obj/Release/src/inter/DefaultTaskConfigInter.o -c src/inter/DefaultTaskConfigInter.cpp

