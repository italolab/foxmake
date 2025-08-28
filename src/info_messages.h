#ifndef INFO_MESSAGES_H
#define INFO_MESSAGES_H

#include <string>

using std::string;

namespace infos {

    const string EXECUTING = "Executando";
    const string EXECUTING_STATEMENTS = "Executando instruções...";

    const string SUCCESS_IN_CLEAN = "Limpesa efetuada com sucesso.";
    const string SUCCESS_IN_COMPILATION = "Compilacao executada com sucesso.";
    const string SUCCESS_IN_LINKING = "Linkagem efetuada com sucesso.";
    const string SUCCESS_IN_ARCHIVING = "Biblioteca estática criada com sucesso.";
    const string SUCCESS_IN_COPY = "Cópia dos arquivos de build efetuada com sucesso.";
    const string SUCCESS_IN_EXECUTING_STATEMENTS = "Instruções executadas com sucesso.";

    const string FINISH = "Concluído!";

    const string CURRENT_DIRECTORY = "Diretório corrente: \"$1\"";
    const string NEW_CURRENT_DIRECTORY = "Novo diretório corrente: \"$1\".";

    const string FILE_OR_DIRECTORY_DELETED = "Deletado: \"$1\"";
    const string FILE_OR_DIRECTORY_COPIED = "Copiado para pasta de build: \"$1\".";
    const string FILES_AND_FOLDERS_DELETED = "$1 arquivo(s) ou pasta(s) deletado(s)";

    const string CLEAN_UP_TO_DATE = "Não foi necessário remover algum arquivo. Limpesa atualizada.";
    const string COMPILATION_UP_TO_DATE = "Não foi necessário compilar algum arquivo.\nCompilação atualizada!";

    const string CONFIGURATION_FILE = "Arquivo de configuração: \"$1\"";
    const string SRC_DIRECTORY = "Src dir=\"$1\"";

}

#endif
