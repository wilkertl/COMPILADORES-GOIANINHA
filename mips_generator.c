#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mips_generator.h"

static FILE* output;
static int label_counter = 0;
static int temp_counter = 0;

static char* new_label() {
    static char label[32];
    sprintf(label, "L%d", label_counter++);
    return strdup(label);
}

static char* new_temp() {
    static char temp[32];
    sprintf(temp, "$t%d", temp_counter % 8);
    temp_counter++;
    return strdup(temp);
}

static void generate_expression(ASTNode* node, char* result_reg);
static void generate_statement(ASTNode* node);

static void generate_data_section(ASTNode* node) {
    fprintf(output, ".data\n");
    
    // Percorre declarações globais para gerar variáveis
    if (node->data.program.declarations) {
        ASTNode* current = node->data.program.declarations;
        while (current) {
            ASTNode* decl = current->data.list.item;
            if (decl->type == NODE_VAR_DECL) {
                ASTNode* id_list = decl->data.var_decl.id_list;
                ASTNode* id_current = id_list;
                while (id_current) {
                    ASTNode* id_node = id_current->data.list.item;
                    fprintf(output, "%s: .word 0\n", id_node->data.id.name);
                    id_current = id_current->data.list.next;
                }
            }
            current = current->data.list.next;
        }
    }
    
    fprintf(output, "\n");
}

static void generate_binary_op(ASTNode* node, char* result_reg) {
    char* left_reg = new_temp();
    char* right_reg = new_temp();
    
    generate_expression(node->data.binary_op.left, left_reg);
    generate_expression(node->data.binary_op.right, right_reg);
    
    switch (node->data.binary_op.op) {
        case OP_ADD:
            fprintf(output, "    add %s, %s, %s\n", result_reg, left_reg, right_reg);
            break;
        case OP_SUB:
            fprintf(output, "    sub %s, %s, %s\n", result_reg, left_reg, right_reg);
            break;
        case OP_MUL:
            fprintf(output, "    mul %s, %s, %s\n", result_reg, left_reg, right_reg);
            break;
        case OP_DIV:
            fprintf(output, "    div %s, %s\n", left_reg, right_reg);
            fprintf(output, "    mflo %s\n", result_reg);
            break;
        case OP_EQ:
            fprintf(output, "    seq %s, %s, %s\n", result_reg, left_reg, right_reg);
            break;
        case OP_NE:
            fprintf(output, "    sne %s, %s, %s\n", result_reg, left_reg, right_reg);
            break;
        case OP_LT:
            fprintf(output, "    slt %s, %s, %s\n", result_reg, left_reg, right_reg);
            break;
        case OP_GT:
            fprintf(output, "    sgt %s, %s, %s\n", result_reg, left_reg, right_reg);
            break;
        case OP_LE:
            fprintf(output, "    sle %s, %s, %s\n", result_reg, left_reg, right_reg);
            break;
        case OP_GE:
            fprintf(output, "    sge %s, %s, %s\n", result_reg, left_reg, right_reg);
            break;
        default:
            fprintf(stderr, "Operador binário não implementado\n");
    }
    
    free(left_reg);
    free(right_reg);
}

static void generate_expression(ASTNode* node, char* result_reg) {
    if (!node) return;
    
    switch (node->type) {
        case NODE_INT:
            fprintf(output, "    li %s, %d\n", result_reg, node->data.int_val.value);
            break;
        case NODE_CHAR:
            fprintf(output, "    li %s, %d\n", result_reg, (int)node->data.char_val.value);
            break;
        case NODE_ID:
            fprintf(output, "    lw %s, %s\n", result_reg, node->data.id.name);
            break;
        case NODE_BINARY_OP:
            generate_binary_op(node, result_reg);
            break;
        case NODE_UNARY_OP:
            {
                char* operand_reg = new_temp();
                generate_expression(node->data.unary_op.operand, operand_reg);
                
                switch (node->data.unary_op.op) {
                    case OP_NEG:
                        fprintf(output, "    neg %s, %s\n", result_reg, operand_reg);
                        break;
                    case OP_NOT:
                        fprintf(output, "    seq %s, %s, $zero\n", result_reg, operand_reg);
                        break;
                    default:
                        fprintf(stderr, "Operador unário não implementado\n");
                }
                
                free(operand_reg);
            }
            break;
        case NODE_FUNC_CALL:
            // Simplificado - não implementa chamadas de função completas
            fprintf(output, "    # Chamada de função %s não implementada\n", 
                    node->data.func_call.name);
            fprintf(output, "    li %s, 0\n", result_reg);
            break;
        default:
            fprintf(stderr, "Tipo de expressão não implementado\n");
    }
}

static void generate_assign(ASTNode* node) {
    char* reg = new_temp();
    generate_expression(node->data.assign.expr, reg);
    fprintf(output, "    sw %s, %s\n", reg, node->data.assign.var);
    free(reg);
}

static void generate_if(ASTNode* node) {
    char* cond_reg = new_temp();
    char* else_label = new_label();
    char* end_label = new_label();
    
    generate_expression(node->data.if_stmt.condition, cond_reg);
    fprintf(output, "    beq %s, $zero, %s\n", cond_reg, else_label);
    
    generate_statement(node->data.if_stmt.then_stmt);
    
    if (node->data.if_stmt.else_stmt) {
        fprintf(output, "    j %s\n", end_label);
        fprintf(output, "%s:\n", else_label);
        generate_statement(node->data.if_stmt.else_stmt);
        fprintf(output, "%s:\n", end_label);
    } else {
        fprintf(output, "%s:\n", else_label);
    }
    
    free(cond_reg);
    free(else_label);
    free(end_label);
}

static void generate_while(ASTNode* node) {
    char* loop_label = new_label();
    char* end_label = new_label();
    char* cond_reg = new_temp();
    
    fprintf(output, "%s:\n", loop_label);
    generate_expression(node->data.while_stmt.condition, cond_reg);
    fprintf(output, "    beq %s, $zero, %s\n", cond_reg, end_label);
    
    generate_statement(node->data.while_stmt.body);
    
    fprintf(output, "    j %s\n", loop_label);
    fprintf(output, "%s:\n", end_label);
    
    free(loop_label);
    free(end_label);
    free(cond_reg);
}

static void generate_read(ASTNode* node) {
    fprintf(output, "    li $v0, 5\n");  // syscall para leitura de inteiro
    fprintf(output, "    syscall\n");
    fprintf(output, "    sw $v0, %s\n", node->data.read_stmt.var);
}

static void generate_write(ASTNode* node) {
    char* reg = new_temp();
    generate_expression(node->data.write_stmt.expr, reg);
    fprintf(output, "    move $a0, %s\n", reg);
    fprintf(output, "    li $v0, 1\n");  // syscall para impressão de inteiro
    fprintf(output, "    syscall\n");
    free(reg);
}

static void generate_write_string(ASTNode* node) {
    // Simplificado - apenas imprime uma nova linha
    fprintf(output, "    li $v0, 4\n");  // syscall para impressão de string
    fprintf(output, "    la $a0, msg_%d\n", label_counter);
    fprintf(output, "    syscall\n");
    // TODO: Adicionar string na seção .data
}

static void generate_newline() {
    fprintf(output, "    li $v0, 11\n"); // syscall para impressão de caractere
    fprintf(output, "    li $a0, 10\n"); // código ASCII para nova linha
    fprintf(output, "    syscall\n");
}

static void generate_statement(ASTNode* node) {
    if (!node) return;
    
    switch (node->type) {
        case NODE_ASSIGN:
            generate_assign(node);
            break;
        case NODE_IF:
            generate_if(node);
            break;
        case NODE_WHILE:
            generate_while(node);
            break;
        case NODE_READ:
            generate_read(node);
            break;
        case NODE_WRITE:
            generate_write(node);
            break;
        case NODE_WRITE_STRING:
            generate_write_string(node);
            break;
        case NODE_NEWLINE:
            generate_newline();
            break;
        case NODE_BLOCK:
            generate_statement(node->data.block.statements);
            break;
        case NODE_LIST:
            {
                ASTNode* current = node;
                while (current) {
                    generate_statement(current->data.list.item);
                    current = current->data.list.next;
                }
            }
            break;
        case NODE_RETURN:
            // Simplificado
            if (node->data.return_stmt.expr) {
                char* reg = new_temp();
                generate_expression(node->data.return_stmt.expr, reg);
                fprintf(output, "    move $v0, %s\n", reg);
                free(reg);
            }
            fprintf(output, "    jr $ra\n");
            break;
        default:
            fprintf(stderr, "Tipo de comando não implementado\n");
    }
}

void generate_mips_code(ASTNode* root, const char* output_file) {
    if (!root) return;
    
    output = fopen(output_file, "w");
    if (!output) {
        fprintf(stderr, "Erro ao criar arquivo de saída: %s\n", output_file);
        return;
    }
    
    // Seção de dados
    generate_data_section(root);
    
    // Seção de texto
    fprintf(output, ".text\n");
    fprintf(output, ".globl main\n\n");
    fprintf(output, "main:\n");
    
    // Gera código para o bloco principal
    if (root->data.program.main_block) {
        generate_statement(root->data.program.main_block);
    }
    
    // Finaliza o programa
    fprintf(output, "    li $v0, 10\n");  // syscall para saída
    fprintf(output, "    syscall\n");
    
    fclose(output);
} 