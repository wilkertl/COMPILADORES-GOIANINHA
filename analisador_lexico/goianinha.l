%{
#include <iostream>
#include <string>
#include "tokens.h"

// Função para reportar erros léxicos
void erroLexico(const char* msg) {
    std::cerr << "ERRO: " << msg << " " << yylineno << std::endl;
}

%}

%option noyywrap
%option yylineno
%option c++

/* Definição de padrões regulares */
DIGITO      [0-9]
LETRA       [a-zA-Z]
ID          ({LETRA}|_)({LETRA}|{DIGITO}|_)*
ESPACO      [ \t\r\n]
INT_CONST   {DIGITO}+
CHAR_CONST  '.'

%x COMENTARIO
%x STRING

%%

 /* Palavras reservadas */
"programa"   { return Token::PROGRAMA; }
"car"        { return Token::CAR; }
"int"        { return Token::INT; }
"retorne"    { return Token::RETORNE; }
"leia"       { return Token::LEIA; }
"escreva"    { return Token::ESCREVA; }
"novalinha"  { return Token::NOVALINHA; }
"se"         { return Token::SE; }
"entao"      { return Token::ENTAO; }
"senao"      { return Token::SENAO; }
"enquanto"   { return Token::ENQUANTO; }
"execute"    { return Token::EXECUTE; }
"ou"         { return Token::OU; }
"e"          { return Token::E; }

 /* Operadores */
"="          { return Token::IGUAL; }
"=="         { return Token::IGUAL_IGUAL; }
"!="         { return Token::DIFERENTE; }
"<"          { return Token::MENOR; }
">"          { return Token::MAIOR; }
"<="         { return Token::MENOR_IGUAL; }
">="         { return Token::MAIOR_IGUAL; }
"+"          { return Token::MAIS; }
"-"          { return Token::MENOS; }
"*"          { return Token::MULTIPLICA; }
"/"          { return Token::DIVIDE; }
"!"          { return Token::NEGACAO; }

 /* Pontuação */
";"          { return Token::PONTO_VIRGULA; }
","          { return Token::VIRGULA; }
"("          { return Token::ABRE_PAREN; }
")"          { return Token::FECHA_PAREN; }
"{"          { return Token::ABRE_CHAVE; }
"}"          { return Token::FECHA_CHAVE; }

 /* Identificadores e constantes */
{ID}         { return Token::ID; }
{INT_CONST}  { return Token::INT_CONST; }
{CHAR_CONST} { return Token::CHAR_CONST; }

 /* Tratamento de strings */
"\""         { BEGIN(STRING); }
<STRING>[^\"\n]* {
                 /* Armazena o conteúdo da string em yytext */
                 return Token::STRING_CONST;
                }
<STRING>\n   { erroLexico("CADEIA DE CARACTERES OCUPA MAIS DE UMA LINHA"); BEGIN(INITIAL); }
<STRING>\"   { BEGIN(INITIAL); }

 /* Tratamento de comentários */
"/*"         { BEGIN(COMENTARIO); }
<COMENTARIO>[^*\n]*        { /* ignora tudo que não é '*' */ }
<COMENTARIO>"*"+[^*/\n]*   { /* ignora '*' não seguido de '/' */ }
<COMENTARIO>\n             { /* ignora quebras de linha */ }
<COMENTARIO>"*"+"/"        { BEGIN(INITIAL); }
<COMENTARIO><<EOF>>        { erroLexico("COMENTARIO NAO TERMINA"); return Token::EOF_TOKEN; }

 /* Espaços em branco e caracteres irrelevantes */
{ESPACO}+    { /* ignora espaços em branco */ }

 /* Qualquer outro caractere é inválido */
.            { erroLexico("CARACTERE INVALIDO"); }

 /* Fim de arquivo */
<<EOF>>      { return Token::EOF_TOKEN; }

%%