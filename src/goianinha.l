%{
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "ast.h"
#include "goianinha.tab.h"

void yyerror(const char* msg);
%}

%option noyywrap
%option yylineno

DIGITO      [0-9]
LETRA       [a-zA-Z]
ID          ({LETRA}|_)({LETRA}|{DIGITO}|_)*
INT_CONST   {DIGITO}+
CHAR_CONST  '.'
STRING      \"[^\"\n]*\"
UNTERMINATED_STRING \"[^\"\n]*\n

%x COMENTARIO

%%

"programa"   { return PROGRAMA; }
"int"        { return INT; }
"car"        { return CAR; }
"se"         { return SE; }
"entao"      { return ENTAO; }
"senao"      { return SENAO; }
"enquanto"   { return ENQUANTO; }
"execute"    { return EXECUTE; }
"retorne"    { return RETORNE; }
"leia"       { return LEIA; }
"escreva"    { return ESCREVA; }
"novalinha"  { return NOVALINHA; }

"="          { return IGUAL; }
"=="         { return IGUAL_IGUAL; }
"!="         { return DIFERENTE; }
"<"          { return MENOR; }
">"          { return MAIOR; }
"<="         { return MENOR_IGUAL; }
">="         { return MAIOR_IGUAL; }
"+"          { return MAIS; }
"-"          { return MENOS; }
"*"          { return MULTIPLICA; }
"/"          { return DIVIDE; }
"!"          { return NEGACAO; }
"e"          { return E; }
"ou"         { return OU; }

";"          { return PONTO_VIRGULA; }
","          { return VIRGULA; }
"("          { return ABRE_PAREN; }
")"          { return FECHA_PAREN; }
"{"          { return ABRE_CHAVE; }
"}"          { return FECHA_CHAVE; }

{ID}         { yylval.str = strdup(yytext); return ID; }
{INT_CONST}  { yylval.num = atoi(yytext); return INT_CONST; }
{CHAR_CONST} { yylval.chr = yytext[1]; return CHAR_CONST; }
{STRING}     { yylval.str = strdup(yytext); return STRING_CONST; }
{UNTERMINATED_STRING} { 
    fprintf(stderr, "Erro léxico na linha %d: String não terminada\n", yylineno-1); 
    exit(1); 
}

"/*"         { BEGIN(COMENTARIO); }
<COMENTARIO>[^*\n]*        { }
<COMENTARIO>"*"+[^*/\n]*   { }
<COMENTARIO>\n             { }
<COMENTARIO>"*"+"/"        { BEGIN(INITIAL); }
<COMENTARIO><<EOF>>        { 
    fprintf(stderr, "Erro léxico na linha %d: Comentário não terminado\n", yylineno); 
    exit(1); 
}

[ \t\r\n]+   { }
.            { 
    fprintf(stderr, "Erro léxico na linha %d: Caractere inválido '%c'\n", yylineno, yytext[0]); 
    exit(1); 
}

%% 