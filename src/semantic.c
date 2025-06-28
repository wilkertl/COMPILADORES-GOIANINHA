#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "semantic.h"

static SymbolTable* symbol_table;
static int semantic_errors = 0;
static DataType current_function_return_type = TYPE_VOID;

static void semantic_error(const char* message) {
    fprintf(stderr, "Erro semântico: %s\n", message);
    semantic_errors++;
}

static DataType analyze_expression(ASTNode* node);
static void analyze_statement(ASTNode* node);
static void analyze_declaration(ASTNode* node);

static void analyze_var_decl(ASTNode* node) {
    ASTNode* id_list = node->data.var_decl.id_list;
    DataType var_type = node->data.var_decl.var_type;
    
    ASTNode* current = id_list;
    while (current) {
        ASTNode* id_node = current->data.list.item;
        char* var_name = id_node->data.id.name;
        
        if (!insert_symbol(symbol_table, var_name, SYMBOL_VAR, var_type)) {
            char error_msg[256];
            sprintf(error_msg, "Variável '%s' já declarada neste escopo", var_name);
            semantic_error(error_msg);
        }
        
        current = current->data.list.next;
    }
}

static void analyze_func_decl(ASTNode* node) {
    char* func_name = node->data.func_decl.name;
    DataType return_type = node->data.func_decl.return_type;
    
    if (!insert_symbol(symbol_table, func_name, SYMBOL_FUNC, return_type)) {
        char error_msg[256];
        sprintf(error_msg, "Função '%s' já declarada", func_name);
        semantic_error(error_msg);
        return;
    }
    
    // Entra no escopo da função
    enter_scope(symbol_table);
    
    // Define o tipo de retorno da função atual
    DataType previous_return_type = current_function_return_type;
    current_function_return_type = return_type;
    
    // Analisa parâmetros
    ASTNode* params = node->data.func_decl.params;
    ASTNode* current = params;
    while (current) {
        ASTNode* param = current->data.list.item;
        char* param_name = param->data.param.name;
        DataType param_type = param->data.param.param_type;
        
        if (!insert_symbol(symbol_table, param_name, SYMBOL_PARAM, param_type)) {
            char error_msg[256];
            sprintf(error_msg, "Parâmetro '%s' já declarado", param_name);
            semantic_error(error_msg);
        }
        
        current = current->data.list.next;
    }
    
    // Analisa corpo da função
    analyze_statement(node->data.func_decl.body);
    
    // Restaura o tipo de retorno anterior
    current_function_return_type = previous_return_type;
    
    // Sai do escopo da função
    exit_scope(symbol_table);
}

static void analyze_declaration(ASTNode* node) {
    switch (node->type) {
        case NODE_VAR_DECL:
            analyze_var_decl(node);
            break;
        case NODE_FUNC_DECL:
            analyze_func_decl(node);
            break;
        default:
            semantic_error("Tipo de declaração desconhecido");
    }
}

static void analyze_assign(ASTNode* node) {
    char* var_name = node->data.assign.var;
    Symbol* symbol = lookup_symbol(symbol_table, var_name);
    
    if (!symbol) {
        char error_msg[256];
        sprintf(error_msg, "Variável '%s' não declarada", var_name);
        semantic_error(error_msg);
        return;
    }
    
    if (symbol->kind != SYMBOL_VAR && symbol->kind != SYMBOL_PARAM) {
        char error_msg[256];
        sprintf(error_msg, "'%s' não é uma variável", var_name);
        semantic_error(error_msg);
        return;
    }
    
    DataType expr_type = analyze_expression(node->data.assign.expr);
    if (expr_type != TYPE_VOID && symbol->type != expr_type) {
        semantic_error("Tipos incompatíveis na atribuição");
    }
}

static void analyze_if(ASTNode* node) {
    DataType cond_type = analyze_expression(node->data.if_stmt.condition);
    if (cond_type != TYPE_INT && cond_type != TYPE_VOID) {
        semantic_error("Condição deve ser do tipo inteiro");
    }
    
    analyze_statement(node->data.if_stmt.then_stmt);
    
    if (node->data.if_stmt.else_stmt) {
        analyze_statement(node->data.if_stmt.else_stmt);
    }
}

static void analyze_while(ASTNode* node) {
    DataType cond_type = analyze_expression(node->data.while_stmt.condition);
    if (cond_type != TYPE_INT && cond_type != TYPE_VOID) {
        semantic_error("Condição deve ser do tipo inteiro");
    }
    
    analyze_statement(node->data.while_stmt.body);
}

static void analyze_return(ASTNode* node) {
    if (node->data.return_stmt.expr) {
        DataType expr_type = analyze_expression(node->data.return_stmt.expr);
        if (current_function_return_type != TYPE_VOID && 
            expr_type != TYPE_VOID && 
            current_function_return_type != expr_type) {
            semantic_error("Tipo de retorno incompatível com declaração da função");
        }
    }
}

static void analyze_read(ASTNode* node) {
    char* var_name = node->data.read_stmt.var;
    Symbol* symbol = lookup_symbol(symbol_table, var_name);
    
    if (!symbol) {
        char error_msg[256];
        sprintf(error_msg, "Variável '%s' não declarada", var_name);
        semantic_error(error_msg);
    } else if (symbol->kind != SYMBOL_VAR && symbol->kind != SYMBOL_PARAM) {
        char error_msg[256];
        sprintf(error_msg, "'%s' não é uma variável", var_name);
        semantic_error(error_msg);
    }
}

static void analyze_write(ASTNode* node) {
    analyze_expression(node->data.write_stmt.expr);
}

static void analyze_func_call(ASTNode* node) {
    char* func_name = node->data.func_call.name;
    Symbol* symbol = lookup_symbol(symbol_table, func_name);
    
    if (!symbol) {
        char error_msg[256];
        sprintf(error_msg, "Função '%s' não declarada", func_name);
        semantic_error(error_msg);
        return;
    }
    
    if (symbol->kind != SYMBOL_FUNC) {
        char error_msg[256];
        sprintf(error_msg, "'%s' não é uma função", func_name);
        semantic_error(error_msg);
        return;
    }
    
    // Analisa argumentos
    ASTNode* args = node->data.func_call.args;
    ASTNode* current = args;
    while (current) {
        analyze_expression(current->data.list.item);
        current = current->data.list.next;
    }
}

static void analyze_statement(ASTNode* node) {
    if (!node) return;
    
    switch (node->type) {
        case NODE_ASSIGN:
            analyze_assign(node);
            break;
        case NODE_IF:
            analyze_if(node);
            break;
        case NODE_WHILE:
            analyze_while(node);
            break;
        case NODE_RETURN:
            analyze_return(node);
            break;
        case NODE_READ:
            analyze_read(node);
            break;
        case NODE_WRITE:
            analyze_write(node);
            break;
        case NODE_WRITE_STRING:
        case NODE_NEWLINE:
            // Nada a verificar
            break;
        case NODE_VAR_DECL:
            // Declarações de variáveis locais (dentro de blocos)
            analyze_var_decl(node);
            break;
        case NODE_FUNC_DECL:
            // Declarações de funções locais (não deveria acontecer, mas tratamos)
            analyze_func_decl(node);
            break;
        case NODE_BLOCK:
            enter_scope(symbol_table);
            analyze_statement(node->data.block.statements);
            exit_scope(symbol_table);
            break;
        case NODE_LIST:
            {
                ASTNode* current = node;
                while (current) {
                    analyze_statement(current->data.list.item);
                    current = current->data.list.next;
                }
            }
            break;
        default:
            analyze_expression(node);
    }
}

static DataType analyze_expression(ASTNode* node) {
    if (!node) return TYPE_VOID;
    
    switch (node->type) {
        case NODE_INT:
            return TYPE_INT;
        case NODE_CHAR:
            return TYPE_CHAR;
        case NODE_ID:
            {
                Symbol* symbol = lookup_symbol(symbol_table, node->data.id.name);
                if (!symbol) {
                    char error_msg[256];
                    sprintf(error_msg, "Identificador '%s' não declarado", node->data.id.name);
                    semantic_error(error_msg);
                    return TYPE_VOID;
                }
                return symbol->type;
            }
        case NODE_BINARY_OP:
            {
                DataType left_type = analyze_expression(node->data.binary_op.left);
                DataType right_type = analyze_expression(node->data.binary_op.right);
                
                if (left_type != TYPE_VOID && right_type != TYPE_VOID && left_type != right_type) {
                    semantic_error("Tipos incompatíveis em operação binária");
                }
                
                return (left_type != TYPE_VOID) ? left_type : right_type;
            }
        case NODE_UNARY_OP:
            return analyze_expression(node->data.unary_op.operand);
        case NODE_FUNC_CALL:
            analyze_func_call(node);
            {
                Symbol* symbol = lookup_symbol(symbol_table, node->data.func_call.name);
                return symbol ? symbol->type : TYPE_VOID;
            }
        default:
            return TYPE_VOID;
    }
}

int semantic_analyze(ASTNode* root) {
    if (!root) return 0;
    
    symbol_table = create_symbol_table();
    semantic_errors = 0;
    
    // Analisa declarações globais
    if (root->data.program.declarations) {
        ASTNode* current = root->data.program.declarations;
        while (current) {
            analyze_declaration(current->data.list.item);
            current = current->data.list.next;
        }
    }
    
    // Analisa bloco principal
    if (root->data.program.main_block) {
        analyze_statement(root->data.program.main_block);
    }
    
    destroy_symbol_table(symbol_table);
    
    return (semantic_errors == 0);
} 