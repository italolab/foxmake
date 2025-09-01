# CBuild

O cbuild é um software que permite automatizar o processo de build de compilação, linkagem (criação de executável ou shared library), archiving (criação de static library) e testes de unidade com outro framework que desenvolvi: O CBTest. Também é possível executar comandos de cópia, deleção de arquivos e pastas, bem como, criação de pastas, impressão de texto, variável ou propriedade na saída padrão, alteração do diretório corrente e execução 
de comandos do shell. Também é possível executar um bloco de comandos do shell.

## Tarefas

O programa cbuild permite a automação de build através da execução de tarefas que podem ser especificadas na linha de comandos. Exemplo:

```
cbuild clean compile link copy
```

O comando acima executa as quatro tarefas: clean, compile, link e copy. A tarefa "build" inclue a execução de todas essas quatro tarefas. Exemplo:

```
cbuild build
```

A tarefa "buildall" executa as quatro tarefas, substituíndo "compile" por "compileall".

## A interpretação do script

O script a ser interpretado pelo cbuild com as propriedades, definições, configurações de tarefas, e comandos e tem, por padrão, o nome settings.txt. Ao encontrar esse arquivo o cbuild muda o diretório padrão (workingDir) para o diretório onde o arquivo de settings está. Com exceção se a propriedade "--working-dir=path" for informada no comando conforme o exemplo abaixo ilustra:

```
cbuild buildall --working-dir=/home/joao/cbuild-workingdir
```

### Classes interpreters

As classes interpreters são executadas para criação da arvore de derivação que corresponde a configuração do script representado na arvore. Essa arvore é executada pelos executores.

Exemplo:
```
    Classe interpreter: CMDInter
    Classes executoras: MainExec, CPExec
```

As classes executoras executam um comando, que pode ser o comando principal (o cbuild build, por exemplo) ou algum comando especificado no arquivo de settings.

As classes interpreters, mantêm um controle sobre uma variável compartilhada e alterada entre elas que é o número de linhas lidas. Logo, o número da linha onde ocorreu um erro de interpretação no script é o número de linhas lidas mais um. Isto é, se o erro está na linha 11, foram lidas com sucesso 10 linhas.

As classes nós da arvore de derivação ficam na pasta "darv" e as classes interpretadoras ficam na pasta "inter". Os executores de comandos ficam na pasta "exec". Os executores de tarefas ficam na pasta "exec/main/task".

## A execução de comandos do shell

A execução de comandos do shell utiliza a classe "Shell" da pasta "shell". Essa classe permite a adição de um lote de comandos para serem executados concorrentemente. Como exemplo, a compilação concorrente dos arquivo de código fonte de implementação. Esses comandos são executados concorrentemente, logo, suas saídas devem ser gerenciadas e a leitura delas, sincronizada.

A classe "OutputThread" da pasta "shell/output" é responsável por fazer a leitura da saída dos comandos e armazenar em um buffer (scringstream) que é lido concorrentemente pela classe "OutputController". Enquanto "OutputThread" está escrevendo no buffer, "OutputController" está lendo do buffer e escrevendo na saída padrão.

Os comandos são executados utilizando-se a biblioteca "popen".

## A classe SourceCodeManager

A classe SourceCodeManager fica na pasta "sourcecode" e carrega estruturas com informações sobre os arquivos de código da pasta passada como parâmetro para o método de leitura e carregamento das estruturas.

É mantida uma "map" das informações do arquivo (struct CodeInfo). A chave desse map é 
o "filePath", o caminho absoluto do arquivo. Exemplo de chave: "/home/joao/projetos/projeto/src/main.cpp". E o valor desse map é um ponteiro da instância de CodeInfo.

Há dois maps, um com apenas informações dos arquivos de código fonte de implementação (.cpp, .c, .cc) e um com todos os arquivos de código fonte, incluíndo os headers (.h, .hpp, .tpp, .ipp).

Geralmente, são passados como parâmetro para o método carregador dessas estruturas os valores das propriedades "src.dir" e "test.dir". 

È mantida uma instância de SourceCodeManager para informações dos arquivos de "src.dir" e outra instância para informações dos arquivos de "test.dir".

## A compilação inteligente

O núcleo da compilação inteligente fica na classe "FilesToCompileManager" da pasta "sourcecode". Outras classes envolvidas são as demais classes dessa mesma pasta.

Durante o carregamento das estruturas de informação dos arquivos de código fonte que acontece na classe "SourceCodeManager", são carregadas também as dependências entre esses arquivos. Um arquivo tem como dependências todos os arquivos que o incluem e todos os arquivos com classes herdadas por alguma classe presente no arquivo.

Exemplo:

```
A classe "A" está definida no caminho: "a/A.h"
A classe "B" está definida no caminho: "b/B.h"
A classe "C" está definida no caminho: "c/C.h"
A classe "C" está definida no caminho: "d/D.h"

A classe "A" inclue "b/B.h" e herda de "D", então:
    - "a/A.h" é adicionado a lista de dependências de "b/B.h"
    - "a/A.h" é adicionado a lista de dependências de "c/C.h"
    - "d/D.h" é adicionado a lista de dependências de "a/A.h"
```

### O arquivo __lwtimes.txt

Na compilação inteligente, são lidas as datas de última alteração dos arquivos com informações mapeadas em SourceCodeManager. Essas datas são armazenadas num arquivo chamado "__lwtimes.txt". Esse arquivo é um arquivo texto de chave/valor, onde a chave é o path do arquivo e o valor é um long que representa a data/time da última compilação do arquivo.

Exemplo de conteúdo do arquivo "__lwtimes.txt":

```
/home/joao/projeto/src/main.cpp=1756631881
/home/joao/projeto/src/math/math.h=1756315215
/home/joao/projeto/src/math/math.cpp=1756316257
```

A cada compilação, o arquivo "__lwtimes.txt" é atualizado com as datas de última alteração nos arquivos de código fonte das pastas de src e de testes.

### A classe FilesToCompileManager

Também a cada compilação, antes do arquivo "__lwtimes.txt" ser atualizado, é carregado um vector com os "CodeInfos" dos arquivos a serem compilados. Isso utilizando um método da classe "FilesToCompileManager" através da classe "SourceCodeManager".

Na classe "FilesToCompileManager", o método de carregamento de informações dos arquivos a serem compilados (FilesToCompileManager::loadFilesToCompile) faz um percorrimento em todos os arquivos de código fonte carregados e compara sua data de última alteração com a sua data de compilação presente no arquivo "__lwtimes.txt". Se a data de última alteração for mais recente que a data de última compilação, então, as dependências de implementação desse arquivos são adicionados ao vector de arquivos a serem compilados.

Um arquivo pode depender de outros arquivos que o inclúem e seus arquivos que o incluem podem depender, ainda, de outros arquivos que os inclúem. Assim, essa busca por arquivos para compilar é recursiva.









