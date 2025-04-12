#include "tabela_simbolos.h"
#include <iostream>
#include <string>

// Função auxiliar para imprimir o tipo de variável
std::string tipoVarParaString(TipoVar tipo) {
    switch (tipo) {
        case TipoVar::INTEIRO: return "inteiro";
        case TipoVar::CARACTERE: return "caractere";
        default: return "desconhecido";
    }
}

// Função auxiliar para imprimir o tipo de entrada
std::string tipoEntradaParaString(TipoEntrada tipo) {
    switch (tipo) {
        case TipoEntrada::VARIAVEL: return "variável";
        case TipoEntrada::FUNCAO: return "função";
        case TipoEntrada::PARAMETRO: return "parâmetro";
        default: return "desconhecido";
    }
}

// Função para imprimir informações sobre uma entrada da tabela de símbolos
void imprimirEntrada(std::shared_ptr<EntradaTabela> entrada) {
    if (entrada == nullptr) {
        std::cout << "Entrada não encontrada." << std::endl;
        return;
    }
    
    std::cout << "Nome: " << entrada->nome << std::endl;
    std::cout << "Tipo de entrada: " << tipoEntradaParaString(entrada->tipoEntrada) << std::endl;
    std::cout << "Tipo: " << tipoVarParaString(entrada->tipo) << std::endl;
    
    switch (entrada->tipoEntrada) {
        case TipoEntrada::VARIAVEL:
            std::cout << "Posição: " << entrada->posicao << std::endl;
            break;
        case TipoEntrada::FUNCAO:
            std::cout << "Número de parâmetros: " << entrada->numParams << std::endl;
            break;
        case TipoEntrada::PARAMETRO:
            std::cout << "Posição: " << entrada->posicao << std::endl;
            if (entrada->funcao) {
                std::cout << "Função associada: " << entrada->funcao->nome << std::endl;
            } else {
                std::cout << "Função associada: nenhuma" << std::endl;
            }
            break;
    }
    std::cout << std::endl;
}

int main() {
    std::cout << "===== Teste da Tabela de Símbolos =====" << std::endl;
    
    // Inicializa a pilha de tabelas de símbolos
    PilhaTabelaSimbolos pilha;
    
    std::cout << "1. Inserindo funções e variáveis no escopo global:" << std::endl;
    
    // Insere algumas funções no escopo global
    auto funcSoma = pilha.inserirFuncao("soma", TipoVar::INTEIRO, 2);
    auto funcMax = pilha.inserirFuncao("max", TipoVar::INTEIRO, 2);
    
    // Insere algumas variáveis no escopo global
    pilha.inserirVariavel("global1", TipoVar::INTEIRO, 0);
    pilha.inserirVariavel("global2", TipoVar::CARACTERE, 1);
    
    // Busca e imprime funções
    std::cout << "Busca por 'soma':" << std::endl;
    imprimirEntrada(pilha.buscarSimbolo("soma"));
    
    std::cout << "Busca por 'max':" << std::endl;
    imprimirEntrada(pilha.buscarSimbolo("max"));
    
    // Busca e imprime variáveis
    std::cout << "Busca por 'global1':" << std::endl;
    imprimirEntrada(pilha.buscarSimbolo("global1"));
    
    std::cout << "Busca por 'global2':" << std::endl;
    imprimirEntrada(pilha.buscarSimbolo("global2"));
    
    // Cria um novo escopo
    std::cout << "\n2. Criando um novo escopo e inserindo variáveis:" << std::endl;
    pilha.criarEscopo();
    
    // Insere variáveis no novo escopo
    pilha.inserirVariavel("local1", TipoVar::INTEIRO, 0);
    pilha.inserirVariavel("global1", TipoVar::CARACTERE, 1); // Sobrepõe global1
    
    // Busca e imprime variáveis do novo escopo
    std::cout << "Busca por 'local1':" << std::endl;
    imprimirEntrada(pilha.buscarSimbolo("local1"));
    
    std::cout << "Busca por 'global1' (deve retornar a variável do escopo local que sobrepõe a global):" << std::endl;
    imprimirEntrada(pilha.buscarSimbolo("global1"));
    
    std::cout << "Busca por 'global2' (deve retornar a variável do escopo global):" << std::endl;
    imprimirEntrada(pilha.buscarSimbolo("global2"));
    
    // Cria outro escopo para simular o escopo de uma função
    std::cout << "\n3. Criando escopo para função e inserindo parâmetros:" << std::endl;
    pilha.criarEscopo();
    
    // Insere parâmetros para a função soma
    pilha.inserirParametro("a", TipoVar::INTEIRO, 0, funcSoma);
    pilha.inserirParametro("b", TipoVar::INTEIRO, 1, funcSoma);
    
    // Insere variável local na função
    pilha.inserirVariavel("resultado", TipoVar::INTEIRO, 0);
    
    // Busca e imprime parâmetros
    std::cout << "Busca por 'a':" << std::endl;
    imprimirEntrada(pilha.buscarSimbolo("a"));
    
    std::cout << "Busca por 'b':" << std::endl;
    imprimirEntrada(pilha.buscarSimbolo("b"));
    
    std::cout << "Busca por 'resultado':" << std::endl;
    imprimirEntrada(pilha.buscarSimbolo("resultado"));
    
    // Remove o escopo da função
    std::cout << "\n4. Removendo o escopo da função:" << std::endl;
    pilha.removerEscopoAtual();
    
    // Tenta buscar variáveis do escopo removido
    std::cout << "Busca por 'a' (deve falhar):" << std::endl;
    imprimirEntrada(pilha.buscarSimbolo("a"));
    
    std::cout << "Busca por 'resultado' (deve falhar):" << std::endl;
    imprimirEntrada(pilha.buscarSimbolo("resultado"));
    
    // Busca variáveis dos escopos ainda presentes
    std::cout << "Busca por 'local1' (deve encontrar):" << std::endl;
    imprimirEntrada(pilha.buscarSimbolo("local1"));
    
    // Remove o segundo escopo
    std::cout << "\n5. Removendo o segundo escopo:" << std::endl;
    pilha.removerEscopoAtual();
    
    // Tenta buscar variáveis do escopo removido
    std::cout << "Busca por 'local1' (deve falhar):" << std::endl;
    imprimirEntrada(pilha.buscarSimbolo("local1"));
    
    // Verifica se global1 volta a ser a do escopo global
    std::cout << "Busca por 'global1' (deve retornar a variável do escopo global):" << std::endl;
    imprimirEntrada(pilha.buscarSimbolo("global1"));
    
    // Elimina a pilha
    std::cout << "\n6. Eliminando a pilha de tabelas de símbolos:" << std::endl;
    pilha.eliminar();
    
    if (pilha.vazia()) {
        std::cout << "Pilha de tabelas vazia após eliminação." << std::endl;
    } else {
        std::cout << "Erro: pilha de tabelas não está vazia após eliminação." << std::endl;
    }
    
    // Inicializa novamente a pilha para demonstrar que funciona após eliminação
    std::cout << "\n7. Reinicializando a pilha:" << std::endl;
    pilha.iniciar();
    
    pilha.inserirVariavel("nova_var", TipoVar::INTEIRO, 0);
    std::cout << "Busca por 'nova_var':" << std::endl;
    imprimirEntrada(pilha.buscarSimbolo("nova_var"));
    
    return 0;
}