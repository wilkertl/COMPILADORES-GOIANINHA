# Compilador Goianinha

Um compilador completo para a linguagem de programação **Goianinha**, implementado em C usando Flex/Lex e Bison/Yacc.

## 📋 Visão Geral

Este projeto implementa todas as fases de um compilador clássico:
- **Análise Léxica** (Tokenização com detecção avançada de erros)
- **Análise Sintática** (Parsing com AST e mensagens específicas de erro)
- **Análise Semântica** (Verificação completa de tipos, escopo e parâmetros)
- **Geração de Código** (Assembly MIPS com gerenciamento de variáveis locais)

## 🏗️ Estrutura do Projeto

```
COMPILADORES-GOIANINHA/
├── src/                    # Código fonte
│   ├── goianinha.l        # Especificação léxica (Flex)
│   ├── goianinha.y        # Especificação sintática (Bison)
│   ├── ast.c              # Implementação da AST
│   ├── tabela_simbolos.c  # Implementação da tabela de símbolos
│   ├── semantico.c        # Analisador semântico
│   └── mips_gerador.c     # Gerador de código MIPS
├── include/               # Arquivos de cabeçalho
│   ├── ast.h
│   ├── tabela_simbolos.h
│   ├── semantico.h
│   └── mips_gerador.h
├── examples/              # Programas de exemplo
│   ├── exemplo_basico.g
│   ├── exemplo_expressoes.g
│   ├── exemplo_funcao.g
│   └── exemplo_simples.g
├── testes/                # Suíte completa de testes
│   ├── lexico/           # Testes de análise léxica
│   ├── sintatico/        # Testes de análise sintática
│   └── semantico/        # Testes de análise semântica
├── Makefile              # Sistema de build
└── README.md             # Este arquivo
```

## 🚀 Como Usar

### Pré-requisitos

- GCC (GNU Compiler Collection)
- Flex (Fast Lexical Analyzer)
- Bison (GNU Parser Generator)
- Make

### Instalação no Ubuntu/Debian

```bash
sudo apt update
sudo apt install gcc flex bison make
```

### Compilação

```bash
# Compilar o compilador
make

# Limpar arquivos gerados
make clean
```

### Execução

```bash
# Compilar um programa Goianinha
./goianinha programa.g

# O compilador gera automaticamente:
# - Relatório das fases de compilação
# - Arquivo saida.asm (código MIPS)
# - Mensagens de erro específicas (se houver)
```

## 📝 Sintaxe da Linguagem Goianinha

### Tipos de Dados
- `int` - Números inteiros
- `car` - Caracteres

### Declaração de Variáveis
```goianinha
int x, y, z;
car c;
```

### Programa Principal
```goianinha
programa {
    // comandos aqui
}
```

### Operadores
- **Aritméticos**: `+`, `-`, `*`, `/`
- **Relacionais**: `==`, `!=`, `<`, `>`, `<=`, `>=`
- **Lógicos**: `e` (AND), `ou` (OR), `!` (NOT)

### Estruturas de Controle
```goianinha
// Condicional
se (condicao) entao comando;
se (condicao) entao comando senao comando;

// Laço
enquanto (condicao) execute comando;
```

### Funções
```goianinha
int funcao(int param1, car param2) {
    // corpo da função
    retorne valor;
}
```

### Entrada e Saída
```goianinha
leia variavel;           // Lê um valor
escreva expressao;       // Escreve um valor
escreva "texto";         // Escreve uma string
novalinha;               // Nova linha
```

## 📚 Exemplos

### Exemplo Básico
```goianinha
int x;

programa {
    x = 42;
    escreva x;
    novalinha;
}
```

### Exemplo com Expressões
```goianinha
int a, b, resultado;

programa {
    a = 10;
    b = 5;
    resultado = a + b * 2;
    escreva resultado;    // Saída: 20
    novalinha;
}
```

### Exemplo com Função
```goianinha
int soma(int x, int y) {
    retorne x + y;
}

int resultado;

programa {
    resultado = soma(15, 25);
    escreva resultado;    // Saída: 40
    novalinha;
}
```

## 🔧 Arquitetura do Compilador

### 1. Análise Léxica (`goianinha.l`)
- Reconhece tokens da linguagem
- Detecta caracteres inválidos
- Identifica strings e comentários não terminados
- **Mensagens de erro específicas com linha**

### 2. Análise Sintática (`goianinha.y`)
- Verifica a estrutura sintática do programa
- Constrói a Árvore Sintática Abstrata (AST) com números de linha
- Detecta erros sintáticos específicos (ponto e vírgula ausente, operadores inválidos)
- **Mensagens de erro contextuais**

### 3. Tabela de Símbolos (`tabela_simbolos.c`)
- Gerencia escopo de variáveis e funções
- Armazena informações de tipo, declaração e parâmetros
- Suporte a escopos aninhados
- **Controle completo de escopo local/global**

### 4. Análise Semântica (`semantico.c`)
- Verificação rigorosa de tipos
- Verificação de declaração de variáveis
- Validação completa de chamadas de função (número e tipos de parâmetros)
- Detecção de redefinições
- **Relatório de erros com linha específica**

### 5. Geração de Código (`mips_gerador.c`)
- Gera código assembly MIPS otimizado
- Implementa todas as expressões aritméticas e lógicas
- Gerencia registradores temporários
- **Suporte completo a variáveis locais em stack**
- Estruturas de controle e chamadas de função

## 🧪 Sistema de Testes

### Estrutura de Testes

```
testes/
├── lexico/           # Testes de análise léxica
│   ├── *Correto.txt     # Casos que devem passar
│   └── *Erro*.txt       # Casos que devem falhar
├── sintatico/        # Testes de análise sintática
│   ├── *Correto.txt     # Casos que devem passar
│   └── *Erro*.txt       # Casos que devem falhar
└── semantico/        # Testes de análise semântica
    ├── 01_*.txt         # Casos de sucesso
    └── erro_*.txt       # Casos de erro
```

### Executando Testes

**Testes Léxicos:**
```bash
./goianinha testes/lexico/fatorialCorreto.txt
./goianinha testes/lexico/erroLin6Caractereinvalido%.txt
```

**Testes Sintáticos:**
```bash
./goianinha testes/sintatico/fatorialCorreto.txt
./goianinha testes/sintatico/erroLin6AsteriscoAmais.txt
```

**Testes Semânticos:**

*Casos de Sucesso:*
```bash
./goianinha testes/semantico/01_variaveis_basicas.txt
./goianinha testes/semantico/02_funcoes_simples.txt
./goianinha testes/semantico/03_estruturas_controle.txt
./goianinha testes/semantico/04_expressoes_complexas.txt
./goianinha testes/semantico/05_recursao.txt
./goianinha testes/semantico/06_entrada_saida.txt
./goianinha testes/semantico/07_escopos.txt
./goianinha testes/semantico/08_tipos_char.txt
```

*Casos de Erro:*
```bash
./goianinha testes/semantico/erro_01_variavel_nao_declarada.txt
./goianinha testes/semantico/erro_02_redeclaracao.txt
./goianinha testes/semantico/erro_03_tipos_incompativeis.txt
./goianinha testes/semantico/erro_04_funcao_nao_declarada.txt
./goianinha testes/semantico/erro_05_parametros_incorretos.txt
./goianinha testes/semantico/erro_06_condicao_tipo_errado.txt
./goianinha testes/semantico/erro_07_tipos_parametros_incorretos.txt
```

## 📊 Mensagens de Erro Avançadas

### Erros Léxicos
```
Erro léxico na linha 6: Caractere inválido '%'
Erro léxico na linha 27: Comentário não terminado
Erro léxico na linha 4: String não terminada
```

### Erros Sintáticos
```
ERRO: falta ponto e vírgula ';' antes de 'escreva' na linha 4
ERRO: operador '*' inesperado na linha 6
ERRO: esperado chave de fechamento '}' na linha 10
```

### Erros Semânticos
```
Erro semântico na linha 4: Variável 'y' não declarada
Erro semântico na linha 21: Tipo do argumento 1 incompatível na chamada de 'soma'
Erro semântico na linha 15: Redefinição da variável 'x' no mesmo escopo
```

### Saída de Sucesso
```
Análise sintática concluída com sucesso!
Análise semântica concluída com sucesso!
Código MIPS gerado em saida.asm
```

## 🔍 Funcionalidades Implementadas

- ✅ **Análise Léxica Avançada**
  - Reconhecimento de todos os tokens
  - Detecção específica de erros (caracteres inválidos, strings/comentários não terminados)
  - Números de linha precisos

- ✅ **Análise Sintática com AST Completa**
  - Gramática completa da linguagem
  - Construção de árvore sintática com números de linha
  - Detecção inteligente de erros (ponto e vírgula ausente, operadores duplos)
  - Mensagens de erro contextuais

- ✅ **Análise Semântica Robusta**
  - Verificação completa de tipos
  - Controle rigoroso de escopo (local/global)
  - Validação completa de parâmetros de função
  - Detecção de redefinições e variáveis não declaradas

- ✅ **Geração de Código MIPS Completa**
  - Todas as expressões aritméticas e lógicas
  - Estruturas de controle (if/else, while)
  - Chamadas de função com parâmetros
  - Gerenciamento de variáveis locais em stack
  - Entrada/saída completa

- ✅ **Sistema de Testes Abrangente**
  - Mais de 30 casos de teste
  - Cobertura de todos os aspectos da linguagem
  - Casos de sucesso e falha bem definidos

## 🛠️ Desenvolvimento

### Estrutura dos Arquivos Fonte

- **`goianinha.l`**: Define tokens e regras léxicas com tratamento de erro
- **`goianinha.y`**: Define gramática e ações semânticas com AST
- **`ast.h/c`**: Estruturas e funções da AST com números de linha
- **`tabela_simbolos.h/c`**: Gerenciamento completo de símbolos e escopo
- **`semantico.h/c`**: Verificações semânticas com validação de parâmetros
- **`mips_gerador.h/c`**: Geração completa de código assembly

### Recursos Avançados Implementados

1. **Detecção Inteligente de Erros**: O compilador identifica a causa real dos erros (ex: ponto e vírgula ausente vs token inesperado)

2. **Gerenciamento de Variáveis Locais**: Implementação completa de stack para variáveis locais de função

3. **Validação de Parâmetros**: Verificação rigorosa de número e tipos de parâmetros em chamadas de função

4. **Números de Linha Precisos**: Todos os erros reportam a linha exata onde ocorrem

5. **Operadores Lógicos Completos**: Implementação de `e` (AND) e `ou` (OR) com conversão booleana

## 📄 Licença

Este projeto foi desenvolvido para fins educacionais como parte de um curso de Compiladores.

## 👥 Contribuição

Para contribuir com o projeto:
1. Faça um fork do repositório
2. Crie uma branch para sua feature
3. Implemente as mudanças
4. **Execute todos os testes** para garantir compatibilidade
5. Submeta um pull request

## 📞 Suporte

Para dúvidas ou problemas:
- Verifique se todas as dependências estão instaladas
- Execute `make clean` antes de recompilar
- Consulte os exemplos na pasta `examples/`
- Use os testes em `testes/` para verificar funcionalidade
- Verifique as mensagens de erro específicas para debugging 
