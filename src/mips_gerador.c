#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mips_gerador.h"

static FILE* output;
static int label_counter = 0;
static int temp_counter = 0;

// Array para armazenar strings literais
#define MAX_STRINGS 100
static struct {
    char* text;
    int id;
} string_literals[MAX_STRINGS];
static int string_count = 0;

// Stack frame management for local variables
#define MAX_LOCAL_VARS 100
static struct {
    char* name;
    int stack_offset;
} local_vars[MAX_LOCAL_VARS];
static int local_var_count = 0;
static int current_stack_offset = 0;

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

// Functions for local variable management
static void add_local_var(const char* name) {
    if (local_var_count < MAX_LOCAL_VARS) {
        local_vars[local_var_count].name = strdup(name);
        local_vars[local_var_count].stack_offset = current_stack_offset;
        current_stack_offset += 4; // 4 bytes per word
        local_var_count++;
    }
}

static int get_local_var_offset(const char* name) {
    for (int i = 0; i < local_var_count; i++) {
        if (strcmp(local_vars[i].name, name) == 0) {
            return local_vars[i].stack_offset;
        }
    }
    return -1; // Not found
}

static void clear_local_vars() {
    for (int i = 0; i < local_var_count; i++) {
        free(local_vars[i].name);
    }
    local_var_count = 0;
    current_stack_offset = 0;
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
    
    // Remover hack das variáveis locais - elas devem ser tratadas no stack
    
    fprintf(output, "\n");
}

static void generate_string_literals() {
    // Gerar strings literais na seção .data
    for (int i = 0; i < string_count; i++) {
        fprintf(output, "str_%d: .asciiz %s\n", i, string_literals[i].text);
    }
    if (string_count > 0) {
        fprintf(output, "\n");
    }
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
        case OP_AND:
            // Operação lógica AND: resultado = (left != 0) && (right != 0)
            fprintf(output, "    sne %s, %s, $zero\n", left_reg, left_reg);   // left = (left != 0)
            fprintf(output, "    sne %s, %s, $zero\n", right_reg, right_reg); // right = (right != 0)
            fprintf(output, "    and %s, %s, %s\n", result_reg, left_reg, right_reg);
            break;
        case OP_OR:
            // Operação lógica OR: resultado = (left != 0) || (right != 0)
            fprintf(output, "    sne %s, %s, $zero\n", left_reg, left_reg);   // left = (left != 0)
            fprintf(output, "    sne %s, %s, $zero\n", right_reg, right_reg); // right = (right != 0)
            fprintf(output, "    or %s, %s, %s\n", result_reg, left_reg, right_reg);
            break;
        default:
            fprintf(stderr, "Operador binário não implementado: %d\n", node->data.binary_op.op);
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
            {
                int offset = get_local_var_offset(node->data.id.name);
                if (offset >= 0) {
                    // Variável local - carregar do stack
                    fprintf(output, "    lw %s, %d($sp)\n", result_reg, offset);
                } else {
                    // Variável global - carregar da memória
                    fprintf(output, "    lw %s, %s\n", result_reg, node->data.id.name);
                }
            }
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
            // Implementação básica de chamada de função
            fprintf(output, "    # Chamada de função: %s\n", node->data.func_call.name);
            
            // Salvar registradores na pilha (simplificado)
            fprintf(output, "    addi $sp, $sp, -4\n");
            fprintf(output, "    sw $ra, 0($sp)\n");
            
            // TODO: Passar argumentos (simplificado por enquanto)
            if (node->data.func_call.args) {
                fprintf(output, "    # Argumentos da função não implementados completamente\n");
            }
            
            // Chamar a função
            fprintf(output, "    jal %s\n", node->data.func_call.name);
            
            // Restaurar registradores
            fprintf(output, "    lw $ra, 0($sp)\n");
            fprintf(output, "    addi $sp, $sp, 4\n");
            
            // Resultado em $v0, mover para registrador desejado
            fprintf(output, "    move %s, $v0\n", result_reg);
            break;
        default:
            fprintf(stderr, "Tipo de expressão não implementado\n");
    }
}

static void generate_assign(ASTNode* node) {
    char* reg = new_temp();
    generate_expression(node->data.assign.expr, reg);
    
    int offset = get_local_var_offset(node->data.assign.var);
    if (offset >= 0) {
        // Variável local - armazenar no stack
        fprintf(output, "    sw %s, %d($sp)\n", reg, offset);
    } else {
        // Variável global - armazenar na memória
        fprintf(output, "    sw %s, %s\n", reg, node->data.assign.var);
    }
    
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
    // Por simplicidade, assumimos leitura de inteiro
    // TODO: Verificar tipo da variável para decidir entre leitura de int (5) ou char (12)
    fprintf(output, "    li $v0, 5\n");  // syscall para leitura de inteiro
    fprintf(output, "    syscall\n");
    
    int offset = get_local_var_offset(node->data.read_stmt.var);
    if (offset >= 0) {
        // Variável local - armazenar no stack
        fprintf(output, "    sw $v0, %d($sp)\n", offset);
    } else {
        // Variável global - armazenar na memória
        fprintf(output, "    sw $v0, %s\n", node->data.read_stmt.var);
    }
}

static void generate_write(ASTNode* node) {
    char* reg = new_temp();
    generate_expression(node->data.write_stmt.expr, reg);
    fprintf(output, "    move $a0, %s\n", reg);
    
    // Verificar se é um caractere (NODE_CHAR) ou inteiro
    if (node->data.write_stmt.expr && node->data.write_stmt.expr->type == NODE_CHAR) {
        fprintf(output, "    li $v0, 11\n");  // syscall para impressão de caractere
    } else {
        fprintf(output, "    li $v0, 1\n");   // syscall para impressão de inteiro
    }
    
    fprintf(output, "    syscall\n");
    free(reg);
}

static void generate_write_string(ASTNode* node) {
    // Encontrar o índice da string nos literais coletados
    int string_index = -1;
    for (int i = 0; i < string_count; i++) {
        if (string_literals[i].text && strcmp(string_literals[i].text, node->data.write_string.text) == 0) {
            string_index = i;
            break;
        }
    }
    
    // Gerar código para imprimir a string
    fprintf(output, "    li $v0, 4\n");  // syscall para impressão de string
    if (string_index >= 0) {
        fprintf(output, "    la $a0, str_%d\n", string_index);
    } else {
        fprintf(output, "    # String não encontrada: %s\n", node->data.write_string.text);
    }
    fprintf(output, "    syscall\n");
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
        case NODE_VAR_DECL:
            // Processar declarações de variáveis locais
            fprintf(output, "    # Declaracao de variavel local\n");
            if (node->data.var_decl.id_list) {
                ASTNode* id_current = node->data.var_decl.id_list;
                while (id_current) {
                    ASTNode* id_node = id_current->data.list.item;
                    if (id_node && id_node->type == NODE_ID) {
                        add_local_var(id_node->data.id.name);
                        fprintf(output, "    # Variavel local: %s (offset: %d)\n", 
                                id_node->data.id.name, get_local_var_offset(id_node->data.id.name));
                    }
                    id_current = id_current->data.list.next;
                }
            }
            break;
        case NODE_FUNC_DECL:
            // Declarações de função são tratadas separadamente
            fprintf(output, "    # Declaracao de funcao: %s\n", node->data.func_decl.name);
            break;
        default:
            fprintf(stderr, "Tipo de comando não implementado: %d\n", node->type);
    }
}

// Função para coletar variáveis locais em uma primeira passada
static void collect_local_vars(ASTNode* node) {
    if (!node) return;
    
    switch (node->type) {
        case NODE_VAR_DECL:
            if (node->data.var_decl.id_list) {
                ASTNode* id_current = node->data.var_decl.id_list;
                while (id_current) {
                    ASTNode* id_node = id_current->data.list.item;
                    if (id_node && id_node->type == NODE_ID) {
                        add_local_var(id_node->data.id.name);
                    }
                    id_current = id_current->data.list.next;
                }
            }
            break;
        case NODE_LIST:
            {
                ASTNode* current = node;
                while (current) {
                    collect_local_vars(current->data.list.item);
                    current = current->data.list.next;
                }
            }
            break;
        case NODE_BLOCK:
            collect_local_vars(node->data.block.statements);
            break;
        case NODE_IF:
            collect_local_vars(node->data.if_stmt.then_stmt);
            collect_local_vars(node->data.if_stmt.else_stmt);
            break;
        case NODE_WHILE:
            collect_local_vars(node->data.while_stmt.body);
            break;
        default:
            break;
    }
}

// Função para coletar strings em uma primeira passada
static void collect_strings(ASTNode* node) {
    if (!node) return;
    
    switch (node->type) {
        case NODE_WRITE_STRING:
            if (string_count < MAX_STRINGS) {
                string_literals[string_count].text = strdup(node->data.write_string.text);
                string_literals[string_count].id = string_count;
                string_count++;
            }
            break;
        case NODE_LIST:
            {
                ASTNode* current = node;
                while (current) {
                    collect_strings(current->data.list.item);
                    current = current->data.list.next;
                }
            }
            break;
        case NODE_BLOCK:
            collect_strings(node->data.block.statements);
            break;
        case NODE_IF:
            collect_strings(node->data.if_stmt.then_stmt);
            collect_strings(node->data.if_stmt.else_stmt);
            break;
        case NODE_WHILE:
            collect_strings(node->data.while_stmt.body);
            break;
        default:
            break;
    }
}

void generate_mips_code(ASTNode* root, const char* output_file) {
    if (!root) return;
    
    // Reset global counters
    string_count = 0;
    label_counter = 0;
    temp_counter = 0;
    
    // Primeira passada: coletar strings literais
    if (root->data.program.main_block) {
        collect_strings(root->data.program.main_block);
    }
    
    output = fopen(output_file, "w");
    if (!output) {
        fprintf(stderr, "Erro ao criar arquivo de saída: %s\n", output_file);
        return;
    }
    
    // Seção de dados
    generate_data_section(root);
    generate_string_literals();
    
    // Seção de texto
    fprintf(output, ".text\n");
    fprintf(output, ".globl main\n\n");
    fprintf(output, "main:\n");
    
    // Gera código para o bloco principal
    if (root->data.program.main_block) {
        // Primeiro, processar declarações para contar variáveis locais
        clear_local_vars();
        collect_local_vars(root->data.program.main_block);
        
        // Alocar espaço no stack para variáveis locais
        if (current_stack_offset > 0) {
            fprintf(output, "    # Alocar espaço para %d bytes de variáveis locais\n", current_stack_offset);
            fprintf(output, "    addi $sp, $sp, -%d\n", current_stack_offset);
        }
        
        generate_statement(root->data.program.main_block);
        
        // Liberar espaço do stack
        if (current_stack_offset > 0) {
            fprintf(output, "    # Liberar espaço das variáveis locais\n");
            fprintf(output, "    addi $sp, $sp, %d\n", current_stack_offset);
        }
    }
    
    // Finaliza o programa
    fprintf(output, "    li $v0, 10\n");  // syscall para saída
    fprintf(output, "    syscall\n");
    
    fclose(output);
    
    // Limpar strings literais
    for (int i = 0; i < string_count; i++) {
        if (string_literals[i].text) {
            free(string_literals[i].text);
        }
    }
    
    // Limpar variáveis locais
    clear_local_vars();
} 