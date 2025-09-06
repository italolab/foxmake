#ifndef HELP_MESSAGES_H
#define HELP_MESSAGES_H

#include <string>

using std::string;

namespace helpmessage {

    const string PROJ_NAME = "cbuild";
    const string PROJ_NAME_UPCASE = "CBUILD";

    string helpMessage() {
        stringstream ss;
        ss << "\n"
        << "===============================================================\n"
        << "                      AJUDA DO " << PROJ_NAME_UPCASE << "\n"
        << "       Copyright (c) 2025 Ítalo Herbert Siqueira Gabriel\n"
        << "===============================================================\n\n"

        << "O " << PROJ_NAME << " pode ser utilizado para automatizar o processo \n"
        << "de build de projetos C/C++, permitindo configurar tarefas e \n"
        << "executá-las, para ter como resultado final um executável linkado, \n"
        << "uma shared library, uma static library, execução de testes \n"
        << "unitários, etc.\n\n"

        << "---------------------------------------------------------------\n"
        << "    SINTAXE\n"
        << "---------------------------------------------------------------\n\n"

        << PROJ_NAME << " [opções] [chave=valor] [-prop,...] [-var,...]\n\n"

        << ",... significa que pode ser informado zero ou várias vezes e \n"
        << "[] significa opcional\n\n"

        << "---------------------------------------------------------------\n"
        << "    OPÇÕES\n"
        << "---------------------------------------------------------------\n\n"

        << "    -h ou --help            Imprimem esta ajuda\n"
        << "    -v ou --verbose         Imprimem informações detalhadas\n"
        << "    --no-resume             Não imprime o resumo das tarefas\n"
        << "    --script=valor          Especifica o arquivo de script\n"
        << "    --working-dir=valor     Especifica o diretório de trabalho\n"
        << "    -prop chave=valor       Especifica uma propriedade\n"
        << "    -var chave=valor        Especifica uma variável\n\n"

        << "---------------------------------------------------------------\n"
        << "    TAREFAS PADRÃO\n"
        << "---------------------------------------------------------------\n\n"

        << "O " << PROJ_NAME << " tem as seguintes tarefas por padrão: \n\n"

        << "    clean\n"
        << "    compile\n"
        << "    compileall\n"
        << "    archive\n"
        << "    link\n"
        << "    test\n"
        << "    copy\n"
        << "    build\n"
        << "    archivebuild\n"
        << "    testbuild\n"
        << "    buildall\n"
        << "    archivebuildall\n"
        << "    testbuildall\n\n"

        << "Você tambem pode especificar mais de uma tarefa como no exemplo \n"
        << "à seguir:\n\n"

        << "    " << PROJ_NAME << " clean compile link\n\n"

        << "Você pode buscar ajuda sobre uma tarefa específica conforme os \n"
        << "exemplos abaixo:\n\n"

        << "    " << PROJ_NAME << " -h build\n"
        << "    " << PROJ_NAME << " -h compileall\n\n"

        << "---------------------------------------------------------------\n"
        << "    ARQUIVO DE SCRIPT\n"
        << "---------------------------------------------------------------\n\n"

        << "Para informar o arquivo de script, faça conforme o exemplo à \n"
        << "seguir:\n\n"

        << "    " << PROJ_NAME << " --script=CBuildFile\n\n"

        << "Caso o caminho do arquivo contenha espacos, utilize aspas duplas,\n"
        << "conforme a seguir:\n\n"

        << "    " << PROJ_NAME << " --script=\"arquivos de script/CBuildFile\"\n\n"

        << "Se a propriedade --script não for informada, o " + PROJ_NAME + " \n"
        << "tenta localizar o arquivo de nome CBuildFile no mesmo diretório \n"
        << "onde o executável do " + PROJ_NAME + " estiver.\n\n"

        << "---------------------------------------------------------------\n"
        << "    DIRETÓRIO DE TRABALHO\n"
        << "---------------------------------------------------------------\n\n"

        << "O diretório de trabalho, se o arquivo de script for carregado, \n"
        << "passa a ser o mesmo direrório onde o script for encontrado. O \n"
        << "diretório de trabalho pode ser alterado, também, pela opção: \n"
        << "--working-dir conforme a seguir:\n\n"

        << "    " << PROJ_NAME << " --working-dir=\"C:/Meu Projeto\"\n\n"

        << "---------------------------------------------------------------\n"
        << "    PROPRIEDADES E VARIÁVEIS\n"
        << "---------------------------------------------------------------\n\n"

        << "É possível informar propriedades utilizando a opção -prop e \n"
        << "variáveis, utilizando a opção -var. Veja os exemplos abaixo: \n\n"

        << "    " << PROJ_NAME << " -prop output.file.name=proj.exe -var target=release\n\n"

        << "===============================================================\n"
        << "       Copyright (c) 2025 Ítalo Herbert Siqueira Gabriel\n"
        << "===============================================================\n\n";

        return ss.str();
    }

    string cleanHelpMessage() {
        stringstream ss;

        ss << "\n"
        << "---------------------------------------------------------------\n"
        << "    A TAREFA CLEAN\n"
        << "---------------------------------------------------------------\n\n"

        << "    A tarefa clean pode ser utilizada para remover os arquivos \n"
        << "    e diretórios construídos com a execução das outras tarefas.\n"
        << "    Exemplo:\n\n"

        << "    " << PROJ_NAME << " clean\n\n";

        return ss.str();
    }

    string compileHelpMessage() {
        stringstream ss;

        ss << "\n"
        << "---------------------------------------------------------------\n"
        << "    A TAREFA COMPILE\n"
        << "---------------------------------------------------------------\n\n"

        << "    A tarefa compile pode ser utilizada para compilar os arquivos \n"
        << "    de codigo fonte de forma inteligente e gerar os arquivos \n" 
        << "    objetos correspondentes. Esse comando só compila os arquivos \n"
        << "    alterados desde a última compilação. Exemplo:\n\n"

        << "    " << PROJ_NAME << " compile\n\n";

        return ss.str();
    }

    string compileAllHelpMessage() {
        stringstream ss;

        ss << "\n"
        << "---------------------------------------------------------------\n"
        << "    A TAREFA COMPILEALL\n"
        << "---------------------------------------------------------------\n\n"

        << "    A tarefa compileall pode ser utilizada para compilar todos os \n"
        << "    arquivos de codigo fonte e gerar os arquivos objetos \n"
        << "    correspondentes. Exemplo:\n\n"

        << "    " << PROJ_NAME << " compileall\n\n";

        return ss.str();
    }

    string archiveHelpMessage() {
        stringstream ss;

        ss << "\n"
        << "---------------------------------------------------------------\n"
        << "    A TAREFA ARCHIVE\n"
        << "---------------------------------------------------------------\n\n"

        << "    A tarefa archive pode ser utilizada para criar uma shared \n"
        << "    library. Exemplo:\n\n"

        << "    " << PROJ_NAME << " archive\n\n";

        return ss.str();
    }

    string testHelpMessage() {
        stringstream ss;

        ss << "\n"
        << "---------------------------------------------------------------\n"
        << "    A TAREFA TEST\n"
        << "---------------------------------------------------------------\n\n"

        << "    A tarefa test pode ser utilizada para executar testes, caso \n"
        << "    tenham sido configurados no arquivo de script. Exemplo:\n\n"

        << "    " << PROJ_NAME << " test\n\n";

        return ss.str();
    }

    string linkHelpMessage() {
        stringstream ss;

        ss << "\n"
        << "---------------------------------------------------------------\n"
        << "    A TAREFA LINK\n"
        << "---------------------------------------------------------------\n\n"

        << "    A tarefa link pode ser utilizada para gerar o executável \n"
        << "    conforme os arquivos objeto resultantes da compilação. \n"
        << "    Exemplo:\n\n"

        << "    " << PROJ_NAME << " link\n\n";

        return ss.str();
    }

    string copyHelpMessage() {
        stringstream ss;

        ss << "\n"
        << "---------------------------------------------------------------\n"
        << "    A TAREFA COPY\n"
        << "---------------------------------------------------------------\n\n"

        << "    A tarefa copy pode ser utilizada para copiar os arquivos \n"
        << "    gerados na compilação e linkagem, bem como outros arquivos, \n"
        << "    para a pasta de build configurada. Exemplo:\n\n"

        << "    " << PROJ_NAME << " copy\n\n";

        return ss.str();
    }

    string buildHelpMessage() {
        stringstream ss;

        ss << "\n"
        << "---------------------------------------------------------------\n"
        << "    A TAREFA BUILD\n"
        << "---------------------------------------------------------------\n\n"

        << "    A tarefa build pode ser utilizada para executar as tarefas:\n\n"

        << "        clean, compile, link, copy\n\n"

        << "    Exemplo:\n\n"

        << "    " << PROJ_NAME << " build\n\n";

        return ss.str();
    }

    string archiveBuildHelpMessage() {
        stringstream ss;

        ss << "\n"
        << "---------------------------------------------------------------\n"
        << "    A TAREFA ARCHIVEBUILD\n"
        << "---------------------------------------------------------------\n\n"

        << "    A tarefa archivebuild pode ser utilizada para executar as \n"
        << "    tarefas:\n\n"

        << "        clean, compile, archive, copy\n\n"

        << "    Exemplo:\n\n"

        << "    " << PROJ_NAME << " archivebuild\n\n";

        return ss.str();
    }

    string testBuildHelpMessage() {
        stringstream ss;

        ss << "\n"
        << "---------------------------------------------------------------\n"
        << "    A TAREFA TESTBUILD\n"
        << "---------------------------------------------------------------\n\n"

        << "    A tarefa testbuild pode ser utilizada para executar as \n"
        << "    tarefas:\n\n"

        << "        clean, compile, link, test, copy\n\n"

        << "    Exemplo:\n\n"

        << "    " << PROJ_NAME << " testbuild\n\n";

        return ss.str();
    }

    string buildAllHelpMessage() {
        stringstream ss;

        ss << "\n"
        << "---------------------------------------------------------------\n"
        << "    A TAREFA BUILDALL\n"
        << "---------------------------------------------------------------\n\n"

        << "    A tarefa buildall pode ser utilizada para executar as \n"
        << "    tarefas:\n\n"

        << "        clean, compileall, link, copy\n\n"

        << "    Exemplo:\n\n"

        << "    " << PROJ_NAME << " buildall\n\n";

        return ss.str();
    }

    string archiveBuildAllHelpMessage() {
        stringstream ss;

        ss << "\n"
        << "---------------------------------------------------------------\n"
        << "    A TAREFA ARCHIVEBUILDALL\n"
        << "---------------------------------------------------------------\n\n"

        << "    A tarefa archivebuildall pode ser utilizada para executar as \n"
        << "    tarefas:\n\n"

        << "        clean, compileall, archive, copy\n\n"

        << "    Exemplo:\n\n"

        << "    " << PROJ_NAME << " archivebuildall\n\n";

        return ss.str();
    }

    string testBuildAllHelpMessage() {
        stringstream ss;

        ss << "\n"
        << "---------------------------------------------------------------\n"
        << "    A TAREFA TESTBUILDALL\n"
        << "---------------------------------------------------------------\n\n"

        << "    A tarefa testbuildall pode ser utilizada para executar as \n"
        << "    tarefas:\n\n"

        << "        clean, compileall, link, test, copy\n\n"

        << "    Exemplo:\n\n"

        << "    " << PROJ_NAME << " testbuildall\n\n";

        return ss.str();
    }

}

#endif
