#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tabela_simbolos.h"

SymbolTable* create_symbol_table() {
    SymbolTable* table = malloc(sizeof(SymbolTable));
    table->symbols = NULL;
    table->current_scope = 0;
    return table;
}

void destroy_symbol_table(SymbolTable* table) {
    Symbol* current = table->symbols;
    while (current) {
        Symbol* next = current->next;
        free(current->name);
        if (current->param_types) {
            free(current->param_types);
        }
        free(current);
        current = next;
    }
    free(table);
}

void enter_scope(SymbolTable* table) {
    table->current_scope++;
}

void exit_scope(SymbolTable* table) {
    // Remove símbolos do escopo atual
    Symbol* current = table->symbols;
    Symbol* prev = NULL;
    
    while (current) {
        if (current->scope_level == table->current_scope) {
            if (prev) {
                prev->next = current->next;
            } else {
                table->symbols = current->next;
            }
            Symbol* to_delete = current;
            current = current->next;
            free(to_delete->name);
            if (to_delete->param_types) {
                free(to_delete->param_types);
            }
            free(to_delete);
        } else {
            prev = current;
            current = current->next;
        }
    }
    
    table->current_scope--;
}

int insert_symbol(SymbolTable* table, char* name, SymbolKind kind, DataType type) {
    // Verifica se já existe no escopo atual
    if (lookup_symbol_current_scope(table, name)) {
        return 0; // Erro: símbolo já declarado
    }
    
    Symbol* symbol = malloc(sizeof(Symbol));
    symbol->name = strdup(name);
    symbol->kind = kind;
    symbol->type = type;
    symbol->scope_level = table->current_scope;
    symbol->param_count = 0;
    symbol->param_types = NULL;
    symbol->next = table->symbols;
    table->symbols = symbol;
    
    return 1; // Sucesso
}

int insert_function(SymbolTable* table, char* name, DataType return_type, int param_count, DataType* param_types) {
    // Verifica se já existe no escopo atual
    if (lookup_symbol_current_scope(table, name)) {
        return 0; // Erro: função já declarada
    }
    
    Symbol* symbol = malloc(sizeof(Symbol));
    symbol->name = strdup(name);
    symbol->kind = SYMBOL_FUNC;
    symbol->type = return_type;
    symbol->scope_level = table->current_scope;
    symbol->param_count = param_count;
    
    // Copiar tipos dos parâmetros
    if (param_count > 0) {
        symbol->param_types = malloc(param_count * sizeof(DataType));
        for (int i = 0; i < param_count; i++) {
            symbol->param_types[i] = param_types[i];
        }
    } else {
        symbol->param_types = NULL;
    }
    
    symbol->next = table->symbols;
    table->symbols = symbol;
    
    return 1; // Sucesso
}

Symbol* lookup_symbol(SymbolTable* table, char* name) {
    Symbol* current = table->symbols;
    while (current) {
        if (strcmp(current->name, name) == 0) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

Symbol* lookup_symbol_current_scope(SymbolTable* table, char* name) {
    Symbol* current = table->symbols;
    while (current) {
        if (current->scope_level == table->current_scope && 
            strcmp(current->name, name) == 0) {
            return current;
        }
        current = current->next;
    }
    return NULL;
} 