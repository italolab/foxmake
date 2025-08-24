#ifndef INFO_MESSAGES_H
#define INFO_MESSAGES_H

#include <string>

using std::string;

namespace infos {

    const string EXECUTING = "Executando";
    const string EXECUTING_STATEMENTS = "Executando instrucoes...";

    const string SUCCESS_IN_CLEAN = "Limpesa efetuada com sucesso.";
    const string SUCCESS_IN_COMPILATION = "Compilacao executada com sucesso.";
    const string SUCCESS_IN_LINKING = "Linkagem efetuada com sucesso.";
    const string SUCCESS_IN_COPY = "Copia dos arquivos de build efetuada com sucesso.";
    const string SUCCESS_IN_EXECUTING_STATEMENTS = "Instrucoes executadas com sucesso.";

    const string FINISH = "Concluido!";

    const string CURRENT_DIRECTORY = "Diretorio corrente: \"$1\"";
    const string NEW_CURRENT_DIRECTORY = "Novo diretorio corrente: \"$1\".";
    const string EXECUTED_CMD = "Executado: \"$1\"";

    const string FILE_OR_DIRECTORY_DELETED = "Deleted: \"$1\"";
    const string FILE_OR_DIRECTORY_COPIED = "Copiado: \"$1\"";
    const string FILES_AND_FOLDERS_DELETED = "$1 arquivo(s) e pasta(s) deletado(s)";

    const string CLEAN_UP_TO_DATE = "Nao foi necessario remover algum arquivo. Limpesa atualizada.";
    const string COMPILATION_UP_TO_DATE = "Nao foi necessario compilar algum arquivo.\nCompilacao atualizada!";

    const string CONFIGURATION_FILE = "Arquivo de configuracao: \"$1\"";
    const string SRC_DIRECTORY = "Src dir=\"$1\"";

}

#endif
