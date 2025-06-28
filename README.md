# Compilador Goianinha

Um compilador completo para a linguagem de programação **Goianinha**, implementado em C usando Flex/Lex e Bison/Yacc.

## 📋 Visão Geral

Este projeto implementa todas as fases de um compilador clássico:
- **Análise Léxica** (Tokenização)
- **Análise Sintática** (Parsing com AST)
- **Análise Semântica** (Verificação de tipos e escopo)
- **Geração de Código** (Assembly MIPS)

## 🏗️ Estrutura do Projeto

```
COMPILADORES-GOIANINHA/
├── src/                    # Código fonte
│   ├── goianinha.l        # Especificação léxica (Flex)
│   ├── goianinha.y        # Especificação sintática (Bison)
│   ├── ast.c              # Implementação da AST
│   ├── tabela_simbolos.c  # Implementação da tabela de símbolos
│   ├── semantic.c         # Analisador semântico
│   └── mips_generator.c   # Gerador de código MIPS
├── include/               # Arquivos de cabeçalho
│   ├── ast.h
│   ├── tabela_simbolos.h
│   ├── semantic.h
│   └── mips_generator.h
├── examples/              # Programas de exemplo
│   ├── exemplo_basico.g
│   ├── exemplo_expressoes.g
│   └── exemplo_funcao.g
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

# Executar teste automático
make test
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
- Remove comentários e espaços em branco
- Gera sequência de tokens para o parser

### 2. Análise Sintática (`goianinha.y`)
- Verifica a estrutura sintática do programa
- Constrói a Árvore Sintática Abstrata (AST)
- Implementa a gramática da linguagem

### 3. Tabela de Símbolos (`tabela_simbolos.c`)
- Gerencia escopo de variáveis e funções
- Armazena informações de tipo e declaração
- Suporte a escopos aninhados

### 4. Análise Semântica (`semantic.c`)
- Verificação de tipos
- Verificação de declaração de variáveis
- Validação de chamadas de função
- Detecção de redefinições

### 5. Geração de Código (`mips_generator.c`)
- Gera código assembly MIPS
- Implementa expressões aritméticas
- Gerencia registradores temporários
- Suporte a estruturas de controle

## 🧪 Testes

Execute os testes automáticos:
```bash
make test
```

Teste programas específicos:
```bash
./goianinha examples/exemplo_basico.g
./goianinha examples/exemplo_expressoes.g
./goianinha examples/exemplo_funcao.g
```

## 📊 Saída do Compilador

O compilador gera:
1. **Relatório de compilação** - Status de cada fase
2. **Arquivo assembly** (`saida.asm`) - Código MIPS gerado
3. **Mensagens de erro** - Em caso de erros léxicos, sintáticos ou semânticos

### Exemplo de Saída
```
Análise sintática concluída com sucesso!
Análise semântica concluída com sucesso!
Código MIPS gerado em saida.asm
```

## 🔍 Funcionalidades Implementadas

- ✅ **Análise Léxica Completa**
  - Reconhecimento de todos os tokens
  - Tratamento de comentários
  - Números, identificadores, strings

- ✅ **Análise Sintática com AST**
  - Gramática completa da linguagem
  - Construção de árvore sintática
  - Tratamento de precedência de operadores

- ✅ **Análise Semântica Robusta**
  - Verificação de tipos
  - Controle de escopo
  - Validação de declarações

- ✅ **Geração de Código MIPS**
  - Expressões aritméticas
  - Estruturas de controle
  - Chamadas de função
  - Entrada/saída

## 🛠️ Desenvolvimento

### Estrutura dos Arquivos Fonte

- **`goianinha.l`**: Define tokens e regras léxicas
- **`goianinha.y`**: Define gramática e ações semânticas
- **`ast.h/c`**: Estruturas e funções da AST
- **`tabela_simbolos.h/c`**: Gerenciamento de símbolos
- **`semantic.h/c`**: Verificações semânticas
- **`mips_generator.h/c`**: Geração de código assembly

### Adicionando Novas Funcionalidades

1. **Novos tokens**: Adicione em `goianinha.l`
2. **Nova sintaxe**: Modifique `goianinha.y`
3. **Novos tipos de nó**: Atualize `ast.h`
4. **Novas verificações**: Implemente em `semantic.c`
5. **Nova geração**: Adicione em `mips_generator.c`

## 📄 Licença

Este projeto foi desenvolvido para fins educacionais como parte de um curso de Compiladores.

## 👥 Contribuição

Para contribuir com o projeto:
1. Faça um fork do repositório
2. Crie uma branch para sua feature
3. Implemente as mudanças
4. Teste thoroughly
5. Submeta um pull request

## 📞 Suporte

Para dúvidas ou problemas:
- Verifique se todas as dependências estão instaladas
- Execute `make clean` antes de recompilar
- Consulte os exemplos na pasta `examples/` 