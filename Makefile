# Makefile principal para compilar ambas as partes do projeto

.PHONY: all tabela_simbolos analisador_lexico clean

all: tabela_simbolos analisador_lexico

tabela_simbolos:
	$(MAKE) -C tabela_simbolos

analisador_lexico:
	$(MAKE) -C analisador_lexico

clean:
	$(MAKE) -C tabela_simbolos clean
	$(MAKE) -C analisador_lexico clean