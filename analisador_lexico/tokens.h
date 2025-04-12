#ifndef TOKENS_H
#define TOKENS_H

// Enumeração dos tokens da linguagem Goianinha
namespace Token {
    enum TipoToken {
        // Palavras reservadas
        PROGRAMA = 256,
        CAR,
        INT,
        RETORNE,
        LEIA, 
        ESCREVA,
        NOVALINHA,
        SE,
        ENTAO,
        SENAO,
        ENQUANTO,
        EXECUTE,
        OU,
        E,
        
        // Operadores
        IGUAL,       // =
        IGUAL_IGUAL, // ==
        DIFERENTE,   // !=
        MENOR,       // <
        MAIOR,       // >
        MENOR_IGUAL, // <=
        MAIOR_IGUAL, // >=
        MAIS,        // +
        MENOS,       // -
        MULTIPLICA,  // *
        DIVIDE,      // /
        NEGACAO,     // !
        
        // Pontuação
        PONTO_VIRGULA, // ;
        VIRGULA,       // ,
        ABRE_PAREN,    // (
        FECHA_PAREN,   // )
        ABRE_CHAVE,    // {
        FECHA_CHAVE,   // }
        
        // Outros tokens
        ID,            // identificador
        INT_CONST,     // constante inteira
        CHAR_CONST,    // constante caractere
        STRING_CONST,  // constante string
        EOF_TOKEN = -1 // fim de arquivo
    };

    // Função para obter o nome de um token a partir do seu código
    inline const char* obterNomeToken(int token) {
        switch(token) {
            case PROGRAMA: return "PROGRAMA";
            case CAR: return "CAR";
            case INT: return "INT";
            case RETORNE: return "RETORNE";
            case LEIA: return "LEIA";
            case ESCREVA: return "ESCREVA";
            case NOVALINHA: return "NOVALINHA";
            case SE: return "SE";
            case ENTAO: return "ENTAO";
            case SENAO: return "SENAO";
            case ENQUANTO: return "ENQUANTO";
            case EXECUTE: return "EXECUTE";
            case OU: return "OU";
            case E: return "E";
            case IGUAL: return "IGUAL";
            case IGUAL_IGUAL: return "IGUAL_IGUAL";
            case DIFERENTE: return "DIFERENTE";
            case MENOR: return "MENOR";
            case MAIOR: return "MAIOR";
            case MENOR_IGUAL: return "MENOR_IGUAL";
            case MAIOR_IGUAL: return "MAIOR_IGUAL";
            case MAIS: return "MAIS";
            case MENOS: return "MENOS";
            case MULTIPLICA: return "MULTIPLICA";
            case DIVIDE: return "DIVIDE";
            case NEGACAO: return "NEGACAO";
            case PONTO_VIRGULA: return "PONTO_VIRGULA";
            case VIRGULA: return "VIRGULA";
            case ABRE_PAREN: return "ABRE_PAREN";
            case FECHA_PAREN: return "FECHA_PAREN";
            case ABRE_CHAVE: return "ABRE_CHAVE";
            case FECHA_CHAVE: return "FECHA_CHAVE";
            case ID: return "ID";
            case INT_CONST: return "INT_CONST";
            case CHAR_CONST: return "CHAR_CONST";
            case STRING_CONST: return "STRING_CONST";
            case EOF_TOKEN: return "EOF";
            default: return "DESCONHECIDO";
        }
    }
}

#endif // TOKENS_H