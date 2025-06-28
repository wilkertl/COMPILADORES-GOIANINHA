CC = gcc
CFLAGS = -Wall -g -Iinclude
LEX = flex
YACC = bison

# Diretórios
SRCDIR = src
INCDIR = include
EXAMPLEDIR = examples

# Arquivos fonte
SOURCES = $(SRCDIR)/goianinha.tab.c $(SRCDIR)/lex.yy.c $(SRCDIR)/ast.c $(SRCDIR)/tabela_simbolos.c $(SRCDIR)/semantico.c $(SRCDIR)/mips_gerador.c
OBJECTS = $(SOURCES:.c=.o)
TARGET = goianinha

# Regra principal
all: $(TARGET)

# Gerar o executável
$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJECTS) -lfl

# Gerar código do analisador sintático
$(SRCDIR)/goianinha.tab.c $(SRCDIR)/goianinha.tab.h: $(SRCDIR)/goianinha.y
	cd $(SRCDIR) && $(YACC) -d goianinha.y

# Gerar código do analisador léxico
$(SRCDIR)/lex.yy.c: $(SRCDIR)/goianinha.l $(SRCDIR)/goianinha.tab.h
	cd $(SRCDIR) && $(LEX) goianinha.l

# Compilar arquivos objeto
$(SRCDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Limpeza
clean:
	rm -f $(SRCDIR)/*.o $(TARGET) $(SRCDIR)/goianinha.tab.c $(SRCDIR)/goianinha.tab.h $(SRCDIR)/lex.yy.c *.asm

# Criar exemplo simples
create-example:
	echo "int x, y, resultado;" > $(EXAMPLEDIR)/exemplo_simples.g
	echo "" >> $(EXAMPLEDIR)/exemplo_simples.g
	echo "programa {" >> $(EXAMPLEDIR)/exemplo_simples.g
	echo "    x = 10;" >> $(EXAMPLEDIR)/exemplo_simples.g
	echo "    y = 5;" >> $(EXAMPLEDIR)/exemplo_simples.g
	echo "    resultado = x + y * 2;" >> $(EXAMPLEDIR)/exemplo_simples.g
	echo "    escreva resultado;" >> $(EXAMPLEDIR)/exemplo_simples.g
	echo "    novalinha;" >> $(EXAMPLEDIR)/exemplo_simples.g
	echo "}" >> $(EXAMPLEDIR)/exemplo_simples.g

# Teste com arquivo de exemplo
test: $(TARGET) create-example
	./$(TARGET) $(EXAMPLEDIR)/exemplo_simples.g

# Executar testes semânticos
test-semantic: $(TARGET)
	./run_semantic_tests.sh

# Executar teste individual
test-file: $(TARGET)
	@if [ -z "$(FILE)" ]; then \
		echo "Uso: make test-file FILE=semantico_testes/arquivo.txt"; \
	else \
		echo "Testando arquivo: $(FILE)"; \
		./$(TARGET) $(FILE); \
	fi

.PHONY: all clean test test-semantic test-file create-example 