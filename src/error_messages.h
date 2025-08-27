#ifndef ERROR_MESSAGE_H
#define ERROR_MESSAGE_H

#include <string>

using std::string;

namespace errors {

    const string VALUE_IN_QUOTES_NOT_CLOSED = "Valor com aspas duplas sem fechar.";
    const string START_OF_BLOCK_WITH_UNNECESSARY_TOKEN = "Inicio de bloco com caracter(es) desnecessario(s).";
    const string END_OF_BLOCK_WITH_UNNECESSARY_TOKEN = "Fim de bloco com caracter(es) desnecessario(s).";
    const string END_OF_SHELL_BLOCK_NOT_FOUND = "Fim de bloco de shell nao encontrado.";
    const string END_OF_TASK_BLOCK_NOT_FOUND = "Fim de bloco de tarefa nao encontrado.";
    const string PROP_OR_VAR_NOT_FOUND = "Propriedade ou variavel nao encontrada: $($1).";
    const string UNRECOGNIZED_LINE = "Linha nao reconhecida como instrucao valida.";

    const string TASK_NAME_NOT_FOUND = "Nome de tarefa nao encontrado.";
    const string INVALID_TASK_FLAG = "Flag de tarefa invalido: \"$1\"";
    const string IS_NOT_A_DEFAULT_TASK = "A tarefa \"$1\" nao e uma tarefa default. Logo, nao pode ser configurada assim.";

    const string INVALID_NUMBER_OF_ARGS = "Numero de argumentos esperado igual a $1, encontrado $2.";

    const string INVALID_VAR_DEF = "Definicao de variavel invalida: \"$1\"";

    const string WORKDIR_VAR_NOT_FOUND = "Nao foi encontrada a variavel de diretorio de trabalho.";
    const string INFORMED_PATH_IS_NOT_A_DIRECTORY = "O caminho informado nao e um diretorio.";
    const string CURRENT_DIRECTORY_NOT_CHANGED = "Nao foi possivel alterar o diretorio corrente.";
    const string CURRENT_DIRECTORY_NOT_GET = "Nao foi possivel capturar o diretorio corrente.";

    const string DIRECTORY_NOT_FOUND = "Diretorio nao encontrado.";
    const string DIRECTORY_NOT_CREATED = "Nao foi possivel criar o diretorio: \"$1\"";
    const string DIRECTORY_NOT_CREATED_2 = "Nao foi possivel criar o diretorio. \nVerifique se o diretorio onde quer criar o novo diretorio existe.";
    const string DIRECTORIES_NOT_CREATED = "Nao foi possivel criar os diretorios do caminho informado.";

    const string FOLDER_ALREADY_EXISTS = "Pasta ja existe: \"$1\"";

    const string FILE_OR_DIRECTORY_NOT_CREATED = "Nao foi possivel criar o diretorio: \"$1\"";
    const string FILE_OR_DIRECTORY_NOT_COPIED_FOR_BUILD_FOLDER = "Nao foi possivel copiar o arquivo ou pasta: \"$1\" para a pasta de build.";
    const string FILE_OR_FOLDER_NOT_FOUND = "Arquivo ou diretorio nao encontrado: \"$1\"";
    const string FILE_OR_FOLDER_NOT_DELETED = "Arquivo ou pasta nao deletado: \"$1\"\nSe o arquivo e um diretorio, verifique se esta vasio ou tente remover recursivamente.";
    const string FILE_OR_FOLDER_DELETION_IS_NOT_POSSIBLE = "Nao foi possivel deletar o arquivo ou pasta: \"$1\"";
    const string RECURSIVE_FILE_OR_FOLDER_NOT_DELETED = "Arquivo ou pasta nao deletado: \"$1\"";

    const string VERIFY_THE_PROPERTY = "Verifique a propriedade: \"$1\"";

    const string DEST_DIRECTORY_NOT_EXISTS = "O diretorio de destino nao existe: \"$1\"";
    const string TRY_RECURSIVE_COPY_OF_NOT_EMPTY_FOLDER = "Tentativa de copiar nao recursivamente uma pasta nao vazia.";
    const string ERROR_IN_FILES_COPY = "Houve erro na copia do(s) arquivo(s).\nVerifique os caminhos da origem e do destino, \nse a copia e recursiva e com ou sem sobrescrita, \ne se tem permissoes necessarias para esta operacao";

    const string COMPILER_NOT_INFORMED = "Nenhum compilador informado. \nDefina a propriedade: \"$1\"";
    const string COMPILATION_FAILED = "Falha na compilacao!";
    const string LINKING_FAILED = "Falha na linkagem!";

    const string PROPERTY_NOT_DEFINED_FOR_LINKING = "A propriedade \"$1\" deve ter valor definido para linkagem.";
    const string RESOURCE_FILE_NOT_EXISTS = "O arquivo de recursos de icone: \"$1\" nao foi encontrado.";

    const string NOTHING_TASK_INFORMED = "E necessario informar ao menos uma tarefa como argumento.";
    const string CONFIGURATION_FILE_NOT_FOUND = "Arquivo de configuracao nao encontrado: \"$1\"";

    const string SRC_DIRECTORY_NOT_FOUND = "Diretorio de codigos fonte nao encontrado: \"$1\"\nVerifique a propriedade \"$2\"";
    const string BASE_DIRECTORY_NOT_FOUND = "Diretorio base nao encontrado: \"$1\"\nVerifique a propriedade \"$2\"";
    const string ERROR_IN_READING_SRC_FILES = "Houve algum erro na leitura dos arquivos de codigo fonte.";

    const string SHELL_CMD_NOT_EXECUTED = "Nao foi possivel executar o comando.\nVerifique se ele existe e sua sintaxe!\nO comando retornou o codigo: $1";

    const string TASK_NOT_RECOGNIZED = "Tarefa nao reconhecida.";
    const string TASK_BEFORE_ALREADY_DEFINED = "Ja foi definida antes a tarefa \"$1\" como before.";
    const string TASK_AFTER_ALREADY_DEFINED = "Ja foi definida antes a tarefa \"$1\" como after.";
    const string BEFORE_AND_AFTER_TASK = "A tarefa \"$1\" esta sendo definida como before e after.";
    const string DEFAULT_USER_TASK_DEFINED_HOW_NORMAL = "A tarefa \"$1\" e default. Por isso, nao pode ser definida sem before ou after";

    const string ERROR_IN_MAIN_CMD = "Erro: $1";

    namespace runtime {
        
        const string INVALID_STATUS_OF_TASK_CONFIG_INTER = "Status de TaskConfigInter nao reconhecido.";

    }

}

#endif
