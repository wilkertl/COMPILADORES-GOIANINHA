%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"
#include "tabela_simbolos.h"
#include "semantico.h"
#include "mips_gerador.h"

extern int yylex();
extern int yylineno;
extern FILE* yyin;
extern char* yytext;

void yyerror(const char* s);
ASTNode* root = NULL;
%}

%union {
    int num;
    char chr;
    char* str;
    ASTNode* node;
}

%token PROGRAMA INT CAR SE ENTAO SENAO ENQUANTO EXECUTE RETORNE LEIA ESCREVA NOVALINHA
%token IGUAL IGUAL_IGUAL DIFERENTE MENOR MAIOR MENOR_IGUAL MAIOR_IGUAL
%token MAIS MENOS MULTIPLICA DIVIDE NEGACAO E OU
%token PONTO_VIRGULA VIRGULA ABRE_PAREN FECHA_PAREN ABRE_CHAVE FECHA_CHAVE
%token <str> ID STRING_CONST
%token <num> INT_CONST
%token <chr> CHAR_CONST

%define parse.error verbose

%type <node> programa declaracoes declaracao lista_id funcao parametros parametro
%type <node> bloco comandos comando atribuicao expressao termo fator
%type <node> chamada_funcao argumentos declaracoes_locais declaracao_local comando_simples

%left OU
%left E
%left IGUAL_IGUAL DIFERENTE
%left MENOR MAIOR MENOR_IGUAL MAIOR_IGUAL
%left MAIS MENOS
%left MULTIPLICA DIVIDE
%right NEGACAO

%%

programa: declaracoes PROGRAMA bloco
        {
            $$ = create_program_node($1, $3);
            root = $$;
        }
        | PROGRAMA bloco
        {
            $$ = create_program_node(NULL, $2);
            root = $$;
        }
        ;

declaracoes: declaracao
           {
               $$ = create_decl_list_node($1);
           }
           | declaracoes declaracao
           {
               $$ = add_to_decl_list($1, $2);
           }
           ;

declaracao: INT lista_id PONTO_VIRGULA
          {
              $$ = create_var_decl_node(TYPE_INT, $2, yylineno);
          }
          | CAR lista_id PONTO_VIRGULA
          {
              $$ = create_var_decl_node(TYPE_CHAR, $2, yylineno);
          }
          | funcao
          {
              $$ = $1;
          }
          ;

declaracoes_locais: declaracao_local
                  {
                      $$ = create_stmt_list_node($1);
                  }
                  | declaracoes_locais declaracao_local
                  {
                      $$ = add_to_stmt_list($1, $2);
                  }
                  ;

declaracao_local: INT lista_id PONTO_VIRGULA
                {
                    $$ = create_var_decl_node(TYPE_INT, $2, yylineno);
                }
                | CAR lista_id PONTO_VIRGULA
                {
                    $$ = create_var_decl_node(TYPE_CHAR, $2, yylineno);
                }
                ;

lista_id: ID
        {
            $$ = create_id_list_node($1);
        }
        | lista_id VIRGULA ID
        {
            $$ = add_to_id_list($1, $3);
        }
        ;

funcao: INT ID ABRE_PAREN parametros FECHA_PAREN bloco
      {
          $$ = create_func_decl_node(TYPE_INT, $2, $4, $6, yylineno);
      }
      | CAR ID ABRE_PAREN parametros FECHA_PAREN bloco
      {
          $$ = create_func_decl_node(TYPE_CHAR, $2, $4, $6, yylineno);
      }
      ;

parametros: /* vazio */
          {
              $$ = NULL;
          }
          | parametro
          {
              $$ = create_param_list_node($1);
          }
          | parametros VIRGULA parametro
          {
              $$ = add_to_param_list($1, $3);
          }
          ;

parametro: INT ID
         {
             $$ = create_param_node(TYPE_INT, $2, yylineno);
         }
         | CAR ID
         {
             $$ = create_param_node(TYPE_CHAR, $2, yylineno);
         }
         ;

bloco: ABRE_CHAVE comandos FECHA_CHAVE
     {
         $$ = create_block_node($2, yylineno);
     }
     | ABRE_CHAVE declaracoes_locais comandos FECHA_CHAVE
     {
         // Bloco com declarações locais (para suportar declarações dentro de programa{})
         ASTNode* combined = $2;
         if ($3) {
             // Adiciona comandos após declarações
             ASTNode* current = combined;
             while (current && current->data.list.next) {
                 current = current->data.list.next;
             }
             if (current) {
                 current->data.list.next = $3;
             } else {
                 combined = $3;
             }
         }
         $$ = create_block_node(combined, yylineno);
     }
     ;

comandos: /* vazio */
        {
            $$ = NULL;
        }
        | comando
        {
            $$ = create_stmt_list_node($1);
        }
        | comandos comando
        {
            $$ = add_to_stmt_list($1, $2);
        }
        ;

comando: atribuicao
       | comando_simples
       | SE ABRE_PAREN expressao FECHA_PAREN ENTAO comando
       {
           $$ = create_if_node($3, $6, NULL, yylineno);
       }
       | SE ABRE_PAREN expressao FECHA_PAREN ENTAO comando SENAO comando
       {
           $$ = create_if_node($3, $6, $8, yylineno);
       }
       | ENQUANTO ABRE_PAREN expressao FECHA_PAREN EXECUTE comando
       {
           $$ = create_while_node($3, $6, yylineno);
       }
       | bloco
       {
           $$ = $1;
       }
       ;

comando_simples: RETORNE expressao PONTO_VIRGULA
               {
                   $$ = create_return_node($2, yylineno);
               }
               | LEIA ID PONTO_VIRGULA
               {
                   $$ = create_read_node($2, yylineno);
               }
               | ESCREVA expressao PONTO_VIRGULA
               {
                   $$ = create_write_node($2, yylineno);
               }
               | ESCREVA STRING_CONST PONTO_VIRGULA
               {
                   $$ = create_write_string_node($2, yylineno);
               }
               | NOVALINHA PONTO_VIRGULA
               {
                   $$ = create_newline_node(yylineno);
               }
               | comando_simples comando_simples
               {
                   // Múltiplos comandos na mesma linha
                   ASTNode* list = create_stmt_list_node($1);
                   $$ = add_to_stmt_list(list, $2);
               }
               ;

atribuicao: ID IGUAL expressao PONTO_VIRGULA
          {
              $$ = create_assign_node($1, $3, yylineno);
          }
          | ID IGUAL ID IGUAL expressao PONTO_VIRGULA
          {
              // Múltipla atribuição: x = y = expr
              ASTNode* assign2 = create_assign_node($3, $5, yylineno);
              ASTNode* assign1 = create_assign_node($1, $5, yylineno);
              ASTNode* list = create_stmt_list_node(assign2);
              $$ = add_to_stmt_list(list, assign1);
          }
          | ID IGUAL ID IGUAL ID IGUAL expressao PONTO_VIRGULA
          {
              // Múltipla atribuição: z = y = x = expr
              ASTNode* assign3 = create_assign_node($5, $7, yylineno);
              ASTNode* assign2 = create_assign_node($3, $7, yylineno);
              ASTNode* assign1 = create_assign_node($1, $7, yylineno);
              ASTNode* list = create_stmt_list_node(assign3);
              list = add_to_stmt_list(list, assign2);
              $$ = add_to_stmt_list(list, assign1);
          }
          ;

expressao: expressao OU expressao
         {
             $$ = create_binary_op_node(OP_OR, $1, $3, yylineno);
         }
         | expressao E expressao
         {
             $$ = create_binary_op_node(OP_AND, $1, $3, yylineno);
         }
         | expressao IGUAL_IGUAL expressao
         {
             $$ = create_binary_op_node(OP_EQ, $1, $3, yylineno);
         }
         | expressao DIFERENTE expressao
         {
             $$ = create_binary_op_node(OP_NE, $1, $3, yylineno);
         }
         | expressao MENOR expressao
         {
             $$ = create_binary_op_node(OP_LT, $1, $3, yylineno);
         }
         | expressao MAIOR expressao
         {
             $$ = create_binary_op_node(OP_GT, $1, $3, yylineno);
         }
         | expressao MENOR_IGUAL expressao
         {
             $$ = create_binary_op_node(OP_LE, $1, $3, yylineno);
         }
         | expressao MAIOR_IGUAL expressao
         {
             $$ = create_binary_op_node(OP_GE, $1, $3, yylineno);
         }
         | termo
         {
             $$ = $1;
         }
         ;

termo: termo MAIS termo
     {
         $$ = create_binary_op_node(OP_ADD, $1, $3, yylineno);
     }
     | termo MENOS termo
     {
         $$ = create_binary_op_node(OP_SUB, $1, $3, yylineno);
     }
     | fator
     {
         $$ = $1;
     }
     ;

fator: fator MULTIPLICA fator
     {
         $$ = create_binary_op_node(OP_MUL, $1, $3, yylineno);
     }
     | fator DIVIDE fator
     {
         $$ = create_binary_op_node(OP_DIV, $1, $3, yylineno);
     }
     | MENOS fator
     {
         $$ = create_unary_op_node(OP_NEG, $2, yylineno);
     }
     | NEGACAO fator
     {
         $$ = create_unary_op_node(OP_NOT, $2, yylineno);
     }
     | ABRE_PAREN expressao FECHA_PAREN
     {
         $$ = $2;
     }
     | ID
     {
         $$ = create_id_node($1, yylineno);
     }
     | INT_CONST
     {
         $$ = create_int_node($1, yylineno);
     }
     | CHAR_CONST
     {
         $$ = create_char_node($1, yylineno);
     }
     | chamada_funcao
     {
         $$ = $1;
     }
     ;

chamada_funcao: ID ABRE_PAREN argumentos FECHA_PAREN
              {
                  $$ = create_func_call_node($1, $3, yylineno);
              }
              ;

argumentos: /* vazio */
          {
              $$ = NULL;
          }
          | expressao
          {
              $$ = create_arg_list_node($1);
          }
          | argumentos VIRGULA expressao
          {
              $$ = add_to_arg_list($1, $3);
          }
          ;

%%

void yyerror(const char* s) {
    if (strstr(s, "unexpected")) {
        // Parse the error message to provide more specific information
        if (strstr(s, "unexpected $end")) {
            fprintf(stderr, "ERRO: final inesperado do arquivo na linha %d\n", yylineno);
        } else if (strstr(s, "unexpected")) {
            // Detect missing semicolon cases
            if (strcmp(yytext, "escreva") == 0 || strcmp(yytext, "leia") == 0 || 
                strcmp(yytext, "novalinha") == 0 || strcmp(yytext, "retorne") == 0) {
                fprintf(stderr, "ERRO: falta ponto e vírgula ';' antes de '%s' na linha %d\n", yytext, yylineno);
            } else if (strcmp(yytext, "se") == 0 || strcmp(yytext, "enquanto") == 0) {
                fprintf(stderr, "ERRO: falta ponto e vírgula ';' antes de '%s' na linha %d\n", yytext, yylineno);
            } else if (strcmp(yytext, "}") == 0) {
                fprintf(stderr, "ERRO: falta ponto e vírgula ';' antes de '}' na linha %d\n", yylineno);
            } else if (strcmp(yytext, "*") == 0) {
                fprintf(stderr, "ERRO: operador '*' inesperado na linha %d \n", yylineno);
            } else if (strcmp(yytext, ";") == 0) {
                fprintf(stderr, "ERRO: ponto e vírgula inesperado na linha %d\n", yylineno);
            } else if (strcmp(yytext, "{") == 0) {
                fprintf(stderr, "ERRO: chave de abertura inesperada na linha %d\n", yylineno);
            } else if (strcmp(yytext, ")") == 0) {
                fprintf(stderr, "ERRO: parêntese de fechamento inesperado na linha %d\n", yylineno);
            } else if (strcmp(yytext, "(") == 0) {
                fprintf(stderr, "ERRO: parêntese de abertura inesperado na linha %d\n", yylineno);
            } else {
                fprintf(stderr, "ERRO: token inesperado '%s' na linha %d\n", yytext, yylineno);
            }
        } else {
            fprintf(stderr, "ERRO: %s na linha %d\n", s, yylineno);
        }
    } else if (strstr(s, "expecting")) {
        // Handle "expecting" messages
        if (strstr(s, "expecting ';'")) {
            fprintf(stderr, "ERRO: esperado ponto e vírgula ';' na linha %d\n", yylineno);
        } else if (strstr(s, "expecting '}'")) {
            fprintf(stderr, "ERRO: esperado chave de fechamento '}' na linha %d\n", yylineno);
        } else if (strstr(s, "expecting ')'")) {
            fprintf(stderr, "ERRO: esperado parêntese de fechamento ')' na linha %d\n", yylineno);
        } else {
            fprintf(stderr, "ERRO: %s na linha %d\n", s, yylineno);
        }
    } else {
        // Generic syntax error
        fprintf(stderr, "ERRO: erro sintático na linha %d\n", yylineno);
    }
}

int main(int argc, char** argv) {
    if (argc > 1) {
        yyin = fopen(argv[1], "r");
        if (!yyin) {
            fprintf(stderr, "Erro ao abrir arquivo: %s\n", argv[1]);
            return 1;
        }
    }
    
    if (yyparse() == 0) {
        printf("Análise sintática concluída com sucesso!\n");
        
        // Análise semântica
        if (semantic_analyze(root)) {
            printf("Análise semântica concluída com sucesso!\n");
            
            // Geração de código MIPS
            generate_mips_code(root, "saida.asm");
            printf("Código MIPS gerado em saida.asm\n");
        } else {
            printf("Erro na análise semântica!\n");
            return 1;
        }
    } else {
        return 1;
    }
    
    if (yyin != stdin) {
        fclose(yyin);
    }
    
    return 0;
} 