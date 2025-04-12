# Compilador para a linguagem Goianinha

Este projeto implementa a primeira etapa de um compilador para a linguagem Goianinha, que consiste em:

1. Uma implementação da tabela de símbolos
2. Um analisador léxico

## Estrutura do Projeto

```
.
├── Makefile                      # Makefile principal
├── README.md                     # Este arquivo
├── tabela_simbolos/              # Implementação da tabela de símbolos
│   ├── Makefile                  # Makefile da tabela de símbolos
│   ├── tabela_simbolos.h         # Cabeçalho com definições da tabela
│   ├── tabela_simbolos.cpp       # Implementação da tabela
│   └── teste_tabela_simbolos.cpp # Programa de teste
├── analisador_lexico/            # Implementação do analisador léxico
│   ├── Makefile                  # Makefile do analisador léxico
│   ├── tokens.h                  # Definição dos tokens
│   ├── goianinha.l               # Arquivo de entrada para o Flex
│   └── analisador_lexico.cpp     # Programa principal
├── teste.g                       # Exemplo de código Goianinha
└── teste_erros.g                 # Exemplo com erros léxicos
```

## Requisitos

Para compilar e executar este projeto, você precisará:

- g++ para compilar o código C++
- flex para gerar o analisador léxico
- make para facilitar a compilação

Em sistemas baseados em Debian/Ubuntu, você pode instalar estes requisitos com:

```bash
sudo apt-get install g++ flex make
```

## Compilação

Para compilar todo o projeto, execute na pasta raiz:

```bash
make
```

Isso irá compilar tanto a tabela de símbolos quanto o analisador léxico.

Para compilar apenas partes específicas:

```bash
# Apenas a tabela de símbolos
make tabela_simbolos

# Apenas o analisador léxico
make analisador_lexico
```

## Executando

### Teste da Tabela de Símbolos

Para executar o teste da tabela de símbolos:

```bash
cd tabela_simbolos
./teste_tabela_simbolos
```

Este teste demonstrará todas as operações implementadas na pilha de tabela de símbolos.

### Analisador Léxico

Para executar o analisador léxico em um arquivo de exemplo:

```bash
cd analisador_lexico
./goianinha ../teste.g
```

Isso mostrará todos os tokens identificados no arquivo de entrada, junto com seus lexemas e linhas.

Para testar a detecção de erros léxicos:

```bash
cd analisador_lexico
./goianinha ../teste_erros.g
```

Este arquivo contém exemplos de erros léxicos como caracteres inválidos, comentários não terminados e strings multi-linha.

## Descrição das Funcionalidades

### Tabela de Símbolos

A implementação da tabela de símbolos inclui:

- Uma estrutura de dados para representar entradas na tabela (variáveis, funções e parâmetros)
- Uma implementação de tabela de símbolos usando hash map
- Uma pilha de tabelas de símbolos para gerenciar escopos
- Operações para manipular a tabela (inserir, buscar, criar escopo, remover escopo)

#### Funções Implementadas

1. `void iniciar()` - Inicializa a pilha de tabelas de símbolos
2. `void criarEscopo()` - Cria uma nova tabela de símbolos e a empilha
3. `std::shared_ptr<EntradaTabela> buscarSimbolo(const std::string& nome)` - Busca um símbolo na pilha de tabelas
4. `void removerEscopoAtual()` - Remove a tabela de símbolos do topo da pilha
5. `std::shared_ptr<EntradaTabela> inserirFuncao(const std::string& nome, TipoVar tipo, int numParams)` - Insere uma função na tabela atual
6. `std::shared_ptr<EntradaTabela> inserirVariavel(const std::string& nome, TipoVar tipo, int posicao)` - Insere uma variável na tabela atual
7. `std::shared_ptr<EntradaTabela> inserirParametro(const std::string& nome, TipoVar tipo, int posicao, std::shared_ptr<EntradaTabela> funcao)` - Insere um parâmetro na tabela atual
8. `void eliminar()` - Elimina a pilha de tabelas de símbolos

### Analisador Léxico

O analisador léxico reconhece:

- Palavras reservadas da linguagem Goianinha (programa, car, int, retorne, leia, escreva, novalinha, se, entao, senao, enquanto, execute, ou, e)
- Identificadores (começam com letra ou underscore, seguidos de letras, dígitos ou underscores)
- Constantes (inteiros, caracteres, strings)
- Operadores (=, ==, !=, <, >, <=, >=, +, -, *, /, !)
- Pontuação (;, ,, (, ), {, })
- Comentários (/* ... */)

#### Tratamento de Erros Léxicos

O analisador identifica e reporta os seguintes erros:
- `CARACTERE INVALIDO` - Quando um caractere que não faz parte da linguagem é encontrado
- `COMENTARIO NAO TERMINA` - Quando um comentário é aberto com /* mas não é fechado com */
- `CADEIA DE CARACTERES OCUPA MAIS DE UMA LINHA` - Quando uma string contém quebras de linha

Ao encontrar um erro, uma mensagem é exibida no formato:
```
ERRO: [TIPO DE ERRO] [NÚMERO DA LINHA]
```