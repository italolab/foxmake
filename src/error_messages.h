#ifndef ERROR_MESSAGE_H
#define ERROR_MESSAGE_H

#include <string>

using std::string;

namespace errors {

    const string VALUE_IN_QUOTES_NOT_CLOSED = "Valor com aspas duplas sem fechar.";
    const string START_OF_BLOCK_WITH_UNNECESSARY_TOKEN = "Início de bloco com caracter(es) desnecessário(s).";
    const string END_OF_BLOCK_WITH_UNNECESSARY_TOKEN = "Fim de bloco com caracter(es) desnecessário(s).";
    const string END_OF_SHELL_BLOCK_NOT_FOUND = "Fim de bloco de shell \"endshell\" não encontrado.";
    const string END_OF_TASK_BLOCK_NOT_FOUND = "Fim de bloco de tarefa \"endtask\" não encontrado.";
    const string PROP_OR_VAR_NOT_FOUND = "Propriedade ou variável não encontrada: $($1).";
    const string UNRECOGNIZED_LINE = "Linha não reconhecida como instrução válida.";

    const string TASK_NAME_NOT_FOUND = "Nome de tarefa não encontrado.";
    const string INVALID_TASK_FLAG = "Flag de tarefa inválido: \"$1\"";
    const string IS_NOT_A_DEFAULT_TASK = "A tarefa \"$1\" não e uma tarefa default. Logo, não pode ser configurada assim.";

    const string INVALID_NUMBER_OF_ARGS = "Número de argumentos esperado igual a $1, encontrado $2.";

    const string INVALID_VAR_DEF = "Definicao de variável inválida: \"$1\"";

    const string WORKDIR_VAR_NOT_FOUND = "Não foi encontrada a variável de diretório de trabalho.";
    const string INFORMED_PATH_IS_NOT_A_DIRECTORY = "O caminho informado não é um diretório.";
    const string CURRENT_DIRECTORY_NOT_CHANGED = "Não foi possível alterar o diretório corrente.";
    const string CURRENT_DIRECTORY_NOT_GET = "Não foi possível capturar o diretório corrente.";

    const string DIRECTORY_NOT_FOUND = "Diretório não encontrado.";
    const string DIRECTORY_NOT_CREATED = "Não foi possível criar o diretório: \"$1\"";
    const string DIRECTORY_NOT_CREATED_2 = "Não foi possível criar o diretório. \nVerifique se o diretório onde quer criar o novo diretório existe.";
    const string DIRECTORIES_NOT_CREATED = "Não foi possível criar os diretórios do caminho informado.";

    const string FOLDER_ALREADY_EXISTS = "Pasta já existe: \"$1\"";

    const string FILE_OR_DIRECTORY_NOT_CREATED = "Não foi possível criar o diretório: \"$1\"";
    const string FILE_OR_DIRECTORY_NOT_COPIED_FOR_BUILD_FOLDER = "não foi possível cópiar o arquivo ou pasta: \"$1\" para a pasta de build.";
    const string FILE_OR_FOLDER_NOT_FOUND = "Arquivo ou diretório não encontrado: \"$1\"";
    const string FILE_OR_FOLDER_NOT_DELETED = "Arquivo ou pasta não deletado: \"$1\"\nSe o arquivo e um diretório, verifique se está vasio ou tente remover recursivamente.";
    const string FILE_OR_FOLDER_DELETION_IS_NOT_POSSIBLE = "Não foi possível deletar o arquivo ou pasta: \"$1\"";
    const string RECURSIVE_FILE_OR_FOLDER_NOT_DELETED = "Arquivo ou pasta não deletado: \"$1\"";

    const string VERIFY_THE_PROPERTY = "Verifique a propriedade: \"$1\"";

    const string DEST_DIRECTORY_NOT_EXISTS = "O diretório de destino não existe: \"$1\"";
    const string TRY_RECURSIVE_COPY_OF_NOT_EMPTY_FOLDER = "Tentativa de cópiar não recursivamente uma pasta não vazia.";
    const string ERROR_IN_FILES_COPY = "Houve erro na cópia do(s) arquivo(s).\nVerifique os caminhos da origem e do destino, \nse a cópia é recursiva e com ou sem sobrescrita, \ne se tem permissoes necessarias para está operacao";

    const string COMPILATION_FAILED = "Falha na compilacao!";
    const string LINKING_FAILED = "Falha na linkagem!";

    const string PROPERTY_NOT_DEFINED_FOR_LINKING = "A propriedade \"$1\" deve ter valor definido para linkagem.";
    const string PROPERTY_NOT_DEFINED_FOR_ARCHIVING = "A propriedade \"$1\" deve ter valor definido para o empacotamento da biblioteca estática.";
    const string RESOURCE_FILE_NOT_EXISTS = "O arquivo de recursos de ícone: \"$1\" não foi encontrado.";

    const string NOTHING_TASK_INFORMED = "E necessario informar ao menos uma tarefa como argumento.";
    const string CONFIGURATION_FILE_NOT_FOUND = "Arquivo de configuração não encontrado: \"$1\"";

    const string SRC_DIRECTORY_NOT_FOUND = "Diretório de códigos fonte não encontrado: \"$1\"\nVerifique a propriedade \"$2\"";
    const string BASE_DIRECTORY_NOT_FOUND = "Diretório base não encontrado: \"$1\"\nVerifique a propriedade \"$2\"";
    const string NO_SETTINGS_AND_NO_WORKING_DIR = "Como o arquivo de settings não foi encontrado ou informado, é necessario definir o argumento --working-dir";
    const string ERROR_IN_READING_SRC_FILES = "Houve algum erro na leitura dos arquivos de código fonte.";

    const string SHELL_CMD_NOT_EXECUTED = "Não foi possível executar o comando.\nVerifique se ele existe e sua sintáxe!\nO comando retornou o código: $1";

    const string TASK_NOT_RECOGNIZED = "Tarefa não reconhecida.";
    const string TASK_BEFORE_ALREADY_DEFINED = "Já foi definida antes a tarefa \"$1\" como before.";
    const string TASK_AFTER_ALREADY_DEFINED = "Já foi definida antes a tarefa \"$1\" como after.";
    const string BEFORE_AND_AFTER_TASK = "A tarefa \"$1\" está sendo definida como before e after.";
    const string DEFAULT_USER_TASK_DEFINED_HOW_NORMAL = "A tarefa \"$1\" é default. Por isso, não pode ser definida sem before ou after";

    const string ERROR_IN_MAIN_CMD = "Erro: $1";

    namespace runtime {
        
        const string INVALID_STATUS_OF_TASK_CONFIG_INTER = "Status de TaskConfigInter não reconhecido.";
        const string TASK_EXECUTOR_NOT_FOUND = "Executor de tarefa não encontrado pelo nome: \"$1\"";
        const string CMD_EXECUTOR_NOT_FOUND = "Executor de comando não encontrado pelo nome: \"$1\"";
        const string INVALID_STATEMENT_TYPE = "Instrução de tipo inválido.\nLinha=\"$1\"\nTipo=\"$2\"";

    }

}

#endif
