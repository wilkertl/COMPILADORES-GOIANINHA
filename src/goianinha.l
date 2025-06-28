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
STRING      \"[^\"]*\"

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

"/*"         { BEGIN(COMENTARIO); }
<COMENTARIO>[^*\n]*        { }
<COMENTARIO>"*"+[^*/\n]*   { }
<COMENTARIO>\n             { }
<COMENTARIO>"*"+"/"        { BEGIN(INITIAL); }

[ \t\r\n]+   { }
.            { yyerror("Caractere inválido"); }

%% 