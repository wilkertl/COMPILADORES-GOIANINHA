#include <iostream>
#include <fstream>
#include <string>
#include "tokens.h"
#include "FlexLexer.h"

int main(int argc, char* argv[]) {
    // Verificar se o nome do arquivo foi fornecido
    if (argc != 2) {
        std::cerr << "Uso: " << argv[0] << " arquivo.g" << std::endl;
        return 1;
    }

    // Abrir o arquivo de entrada
    std::ifstream arquivoEntrada(argv[1]);
    if (!arquivoEntrada) {
        std::cerr << "Erro ao abrir o arquivo '" << argv[1] << "'" << std::endl;
        return 1;
    }

    // Criar o analisador léxico
    yyFlexLexer analisador(&arquivoEntrada);
    
    int token;
    
    // Loop para ler todos os tokens do arquivo
    while ((token = analisador.yylex()) != Token::EOF_TOKEN) {
        std::cout << "Encontrado o lexema " << analisador.YYText() 
                  << " pertencente ao token de codigo " << token 
                  << " linha " << analisador.lineno() << std::endl;
    }

    return 0;
}