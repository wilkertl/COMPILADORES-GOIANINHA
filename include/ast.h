#ifndef AST_H
#define AST_H

typedef enum {
    TYPE_INT,
    TYPE_CHAR,
    TYPE_VOID
} DataType;

typedef enum {
    OP_ADD, OP_SUB, OP_MUL, OP_DIV,
    OP_EQ, OP_NE, OP_LT, OP_GT, OP_LE, OP_GE,
    OP_AND, OP_OR, OP_NEG, OP_NOT
} Operator;

typedef enum {
    NODE_PROGRAM, NODE_VAR_DECL, NODE_FUNC_DECL, NODE_PARAM,
    NODE_BLOCK, NODE_ASSIGN, NODE_IF, NODE_WHILE, NODE_RETURN,
    NODE_READ, NODE_WRITE, NODE_WRITE_STRING, NODE_NEWLINE,
    NODE_BINARY_OP, NODE_UNARY_OP, NODE_FUNC_CALL,
    NODE_ID, NODE_INT, NODE_CHAR, NODE_LIST
} NodeType;

typedef struct ASTNode {
    NodeType type;
    DataType data_type;
    union {
        struct {
            struct ASTNode* declarations;
            struct ASTNode* main_block;
        } program;
        
        struct {
            DataType var_type;
            struct ASTNode* id_list;
        } var_decl;
        
        struct {
            DataType return_type;
            char* name;
            struct ASTNode* params;
            struct ASTNode* body;
        } func_decl;
        
        struct {
            DataType param_type;
            char* name;
        } param;
        
        struct {
            struct ASTNode* statements;
        } block;
        
        struct {
            char* var;
            struct ASTNode* expr;
        } assign;
        
        struct {
            struct ASTNode* condition;
            struct ASTNode* then_stmt;
            struct ASTNode* else_stmt;
        } if_stmt;
        
        struct {
            struct ASTNode* condition;
            struct ASTNode* body;
        } while_stmt;
        
        struct {
            struct ASTNode* expr;
        } return_stmt;
        
        struct {
            char* var;
        } read_stmt;
        
        struct {
            struct ASTNode* expr;
        } write_stmt;
        
        struct {
            char* text;
        } write_string;
        
        struct {
            Operator op;
            struct ASTNode* left;
            struct ASTNode* right;
        } binary_op;
        
        struct {
            Operator op;
            struct ASTNode* operand;
        } unary_op;
        
        struct {
            char* name;
            struct ASTNode* args;
        } func_call;
        
        struct {
            char* name;
        } id;
        
        struct {
            int value;
        } int_val;
        
        struct {
            char value;
        } char_val;
        
        struct {
            struct ASTNode* item;
            struct ASTNode* next;
        } list;
    } data;
} ASTNode;

// Funções para criação de nós
ASTNode* create_program_node(ASTNode* decls, ASTNode* main_block);
ASTNode* create_var_decl_node(DataType type, ASTNode* id_list);
ASTNode* create_func_decl_node(DataType type, char* name, ASTNode* params, ASTNode* body);
ASTNode* create_param_node(DataType type, char* name);
ASTNode* create_block_node(ASTNode* stmts);
ASTNode* create_assign_node(char* var, ASTNode* expr);
ASTNode* create_if_node(ASTNode* cond, ASTNode* then_stmt, ASTNode* else_stmt);
ASTNode* create_while_node(ASTNode* cond, ASTNode* body);
ASTNode* create_return_node(ASTNode* expr);
ASTNode* create_read_node(char* var);
ASTNode* create_write_node(ASTNode* expr);
ASTNode* create_write_string_node(char* text);
ASTNode* create_newline_node();
ASTNode* create_binary_op_node(Operator op, ASTNode* left, ASTNode* right);
ASTNode* create_unary_op_node(Operator op, ASTNode* operand);
ASTNode* create_func_call_node(char* name, ASTNode* args);
ASTNode* create_id_node(char* name);
ASTNode* create_int_node(int value);
ASTNode* create_char_node(char value);

// Funções para listas
ASTNode* create_decl_list_node(ASTNode* item);
ASTNode* create_id_list_node(char* id);
ASTNode* create_param_list_node(ASTNode* item);
ASTNode* create_stmt_list_node(ASTNode* item);
ASTNode* create_arg_list_node(ASTNode* item);
ASTNode* add_to_decl_list(ASTNode* list, ASTNode* item);
ASTNode* add_to_id_list(ASTNode* list, char* id);
ASTNode* add_to_param_list(ASTNode* list, ASTNode* item);
ASTNode* add_to_stmt_list(ASTNode* list, ASTNode* item);
ASTNode* add_to_arg_list(ASTNode* list, ASTNode* item);

#endif 