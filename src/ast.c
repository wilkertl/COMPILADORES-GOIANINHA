#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"

static ASTNode* create_node(NodeType type, int line) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = type;
    node->data_type = TYPE_VOID;
    node->line_number = line;
    return node;
}

ASTNode* create_program_node(ASTNode* decls, ASTNode* main_block) {
    ASTNode* node = create_node(NODE_PROGRAM, 1);
    node->data.program.declarations = decls;
    node->data.program.main_block = main_block;
    return node;
}

ASTNode* create_var_decl_node(DataType type, ASTNode* id_list, int line) {
    ASTNode* node = create_node(NODE_VAR_DECL, line);
    node->data.var_decl.var_type = type;
    node->data.var_decl.id_list = id_list;
    return node;
}

ASTNode* create_func_decl_node(DataType type, char* name, ASTNode* params, ASTNode* body, int line) {
    ASTNode* node = create_node(NODE_FUNC_DECL, line);
    node->data.func_decl.return_type = type;
    node->data.func_decl.name = strdup(name);
    node->data.func_decl.params = params;
    node->data.func_decl.body = body;
    return node;
}

ASTNode* create_param_node(DataType type, char* name, int line) {
    ASTNode* node = create_node(NODE_PARAM, line);
    node->data.param.param_type = type;
    node->data.param.name = strdup(name);
    return node;
}

ASTNode* create_block_node(ASTNode* stmts, int line) {
    ASTNode* node = create_node(NODE_BLOCK, line);
    node->data.block.statements = stmts;
    return node;
}

ASTNode* create_assign_node(char* var, ASTNode* expr, int line) {
    ASTNode* node = create_node(NODE_ASSIGN, line);
    node->data.assign.var = strdup(var);
    node->data.assign.expr = expr;
    return node;
}

ASTNode* create_if_node(ASTNode* cond, ASTNode* then_stmt, ASTNode* else_stmt, int line) {
    ASTNode* node = create_node(NODE_IF, line);
    node->data.if_stmt.condition = cond;
    node->data.if_stmt.then_stmt = then_stmt;
    node->data.if_stmt.else_stmt = else_stmt;
    return node;
}

ASTNode* create_while_node(ASTNode* cond, ASTNode* body, int line) {
    ASTNode* node = create_node(NODE_WHILE, line);
    node->data.while_stmt.condition = cond;
    node->data.while_stmt.body = body;
    return node;
}

ASTNode* create_return_node(ASTNode* expr, int line) {
    ASTNode* node = create_node(NODE_RETURN, line);
    node->data.return_stmt.expr = expr;
    return node;
}

ASTNode* create_read_node(char* var, int line) {
    ASTNode* node = create_node(NODE_READ, line);
    node->data.read_stmt.var = strdup(var);
    return node;
}

ASTNode* create_write_node(ASTNode* expr, int line) {
    ASTNode* node = create_node(NODE_WRITE, line);
    node->data.write_stmt.expr = expr;
    return node;
}

ASTNode* create_write_string_node(char* text, int line) {
    ASTNode* node = create_node(NODE_WRITE_STRING, line);
    node->data.write_string.text = strdup(text);
    return node;
}

ASTNode* create_newline_node(int line) {
    return create_node(NODE_NEWLINE, line);
}

ASTNode* create_binary_op_node(Operator op, ASTNode* left, ASTNode* right, int line) {
    ASTNode* node = create_node(NODE_BINARY_OP, line);
    node->data.binary_op.op = op;
    node->data.binary_op.left = left;
    node->data.binary_op.right = right;
    return node;
}

ASTNode* create_unary_op_node(Operator op, ASTNode* operand, int line) {
    ASTNode* node = create_node(NODE_UNARY_OP, line);
    node->data.unary_op.op = op;
    node->data.unary_op.operand = operand;
    return node;
}

ASTNode* create_func_call_node(char* name, ASTNode* args, int line) {
    ASTNode* node = create_node(NODE_FUNC_CALL, line);
    node->data.func_call.name = strdup(name);
    node->data.func_call.args = args;
    return node;
}

ASTNode* create_id_node(char* name, int line) {
    ASTNode* node = create_node(NODE_ID, line);
    node->data.id.name = strdup(name);
    return node;
}

ASTNode* create_int_node(int value, int line) {
    ASTNode* node = create_node(NODE_INT, line);
    node->data.int_val.value = value;
    node->data_type = TYPE_INT;
    return node;
}

ASTNode* create_char_node(char value, int line) {
    ASTNode* node = create_node(NODE_CHAR, line);
    node->data.char_val.value = value;
    node->data_type = TYPE_CHAR;
    return node;
}

// Funções para listas
ASTNode* create_list_node(ASTNode* item) {
    ASTNode* node = create_node(NODE_LIST, item ? item->line_number : 1);
    node->data.list.item = item;
    node->data.list.next = NULL;
    return node;
}

ASTNode* create_decl_list_node(ASTNode* item) {
    return create_list_node(item);
}

ASTNode* create_id_list_node(char* id) {
    ASTNode* id_node = create_id_node(id, 1);
    return create_list_node(id_node);
}

ASTNode* create_param_list_node(ASTNode* item) {
    return create_list_node(item);
}

ASTNode* create_stmt_list_node(ASTNode* item) {
    return create_list_node(item);
}

ASTNode* create_arg_list_node(ASTNode* item) {
    return create_list_node(item);
}

static ASTNode* add_to_list(ASTNode* list, ASTNode* item) {
    if (!list) return create_list_node(item);
    
    ASTNode* current = list;
    while (current->data.list.next) {
        current = current->data.list.next;
    }
    current->data.list.next = create_list_node(item);
    return list;
}

ASTNode* add_to_decl_list(ASTNode* list, ASTNode* item) {
    return add_to_list(list, item);
}

ASTNode* add_to_id_list(ASTNode* list, char* id) {
    ASTNode* id_node = create_id_node(id, 1);
    return add_to_list(list, id_node);
}

ASTNode* add_to_param_list(ASTNode* list, ASTNode* item) {
    return add_to_list(list, item);
}

ASTNode* add_to_stmt_list(ASTNode* list, ASTNode* item) {
    return add_to_list(list, item);
}

ASTNode* add_to_arg_list(ASTNode* list, ASTNode* item) {
    return add_to_list(list, item);
} 