#ifndef TABELA_SIMBOLOS_H
#define TABELA_SIMBOLOS_H

#include "ast.h"

typedef enum {
    SYMBOL_VAR,
    SYMBOL_FUNC,
    SYMBOL_PARAM
} SymbolKind;

typedef struct Symbol {
    char* name;
    SymbolKind kind;
    DataType type;
    int scope_level;
    struct Symbol* next;
} Symbol;

typedef struct SymbolTable {
    Symbol* symbols;
    int current_scope;
} SymbolTable;

// Funções da tabela de símbolos
SymbolTable* create_symbol_table();
void destroy_symbol_table(SymbolTable* table);
void enter_scope(SymbolTable* table);
void exit_scope(SymbolTable* table);
int insert_symbol(SymbolTable* table, char* name, SymbolKind kind, DataType type);
Symbol* lookup_symbol(SymbolTable* table, char* name);
Symbol* lookup_symbol_current_scope(SymbolTable* table, char* name);

#endif 