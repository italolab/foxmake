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
        << "==================================================\n"
        << "                AJUDA DO " << PROJ_NAME_UPCASE << "\n"
        << "==================================================\n\n"

        << "--------------------------------------------------\n"
        << "    TAREFAS PADRÃO\n"
        << "--------------------------------------------------\n\n"

        << "O " << PROJ_NAME << " tem as seguintes tarefas por padrão: \n\n"

        << "    clean\n"
        << "    compile\n"
        << "    link\n"
        << "    copy\n"
        << "    build\n"
        << "    compileall\n"
        << "    buildall\n\n"

        << "Você pode buscar ajuda sobre uma tarefa específica conforme os exemplos abaixo:\n\n"

        << "    " << PROJ_NAME << " -h build\n"
        << "    " << PROJ_NAME << " -h compileall\n\n"

        << "Você tambem pode especificar mais de uma tarefa como no exemplo à seguir:\n\n"

        << "    " << PROJ_NAME << " clean compile link\n\n"

        << "--------------------------------------------------\n"
        << "    ARQUIVO DE CONFIGURAÇÃO\n"
        << "--------------------------------------------------\n\n"

        << "Para informar o arquivo de configurações, faça conforme o exemplo à seguir:\n\n"

        << "    " << PROJ_NAME << " --settings-file=settings.txt\n\n"

        << "Caso o caminho do arquivo contenha espacos, utilize aspas duplas, conforme a seguir:\n\n"

        << "    " << PROJ_NAME << " --settings-file=\"arquivos de configuracao/settings.txt\"\n\n"

        << "Se a propriedade --settings-file não for informada, o " + PROJ_NAME + " tenta localizar o arquivo de nome\n"
        << "settings.txt no mesmo diretório onde o executável do " + PROJ_NAME + " estiver.\n\n"

        << "==================================================\n\n";

        return ss.str();
    }

    string cleanHelpMessage() {
        stringstream ss;

        ss << "\n"
        << "--------------------------------------------------\n"
        << "    A TAREFA CLEAN\n"
        << "--------------------------------------------------\n\n"

        << "    A tarefa clean pode ser utilizada para remover os arquivos e diretórios construídos com a execução\n"
        << "    das outras tarefas. Exemplo:\n\n"

        << "    " << PROJ_NAME << " clean\n\n";

        return ss.str();
    }

    string compileHelpMessage() {
        stringstream ss;

        ss << "\n"
        << "--------------------------------------------------\n"
        << "    A TAREFA COMPILE\n"
        << "--------------------------------------------------\n\n"

        << "    A tarefa compile pode ser utilizada para compilar os arquivos de codigo fonte de forma inteligente\n"
        << "    e gerar os arquivos objetos correspondentes. Esse comando só compila os arquivos alterados desde a\n"
        << "    última compilação. Exemplo:\n\n"

        << "    " << PROJ_NAME << " compile\n\n";

        return ss.str();
    }

    string compileAllHelpMessage() {
        stringstream ss;

        ss << "\n"
        << "--------------------------------------------------\n"
        << "    A TAREFA COMPILEALL\n"
        << "--------------------------------------------------\n\n"

        << "    A tarefa compileall pode ser utilizada para compilar todos os arquivos de codigo fonte e gerar os arquivos\n"
        << "    objetos correspondentes. Exemplo:\n\n"

        << "    " << PROJ_NAME << " compileall\n\n";

        return ss.str();
    }

    string linkHelpMessage() {
        stringstream ss;

        ss << "\n"
        << "--------------------------------------------------\n"
        << "    A TAREFA LINK\n"
        << "--------------------------------------------------\n\n"

        << "    A tarefa link pode ser utilizada para gerar o executável conforme os arquivos objeto resultantes da\n"
        << "    compilação. Exemplo:\n\n"

        << "    " << PROJ_NAME << " link\n\n";

        return ss.str();
    }

    string copyHelpMessage() {
        stringstream ss;

        ss << "\n"
        << "--------------------------------------------------\n"
        << "    A TAREFA COPY\n"
        << "--------------------------------------------------\n\n"

        << "    A tarefa copy pode ser utilizada para copiar os arquivos gerados na compilação e linkagem, bem como\n"
        << "    outros arquivos, para a pasta de build configurada. Exemplo:\n\n"

        << "    " << PROJ_NAME << " copy\n\n";

        return ss.str();
    }

    string buildHelpMessage() {
        stringstream ss;

        ss << "\n"
        << "--------------------------------------------------\n"
        << "    A TAREFA BUILD\n"
        << "--------------------------------------------------\n\n"

        << "    A tarefa build pode ser utilizada para executar as tarefas:\n\n"

        << "        clean, compile, link, copy\n\n"

        << "    Exemplo:\n\n"

        << "    " << PROJ_NAME << " build\n\n";

        return ss.str();
    }

    string buildAllHelpMessage() {
        stringstream ss;

        ss << "\n"
        << "--------------------------------------------------\n"
        << "    A TAREFA BUILDALL\n"
        << "--------------------------------------------------\n\n"

        << "    A tarefa buildall pode ser utilizada para executar as tarefas:\n\n"

        << "        clean, compileall, link, copy\n\n"

        << "    Exemplo:\n\n"

        << "    " << PROJ_NAME << " buildall\n\n";

        return ss.str();
    }

}

#endif
