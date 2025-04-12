#include "tabela_simbolos.h"
#include <iostream>

// Implementação dos métodos da classe TabelaSimbolos

TabelaSimbolos::TabelaSimbolos() {}

std::shared_ptr<EntradaTabela> TabelaSimbolos::inserir(const std::string& nome, std::shared_ptr<EntradaTabela> entrada) {
    tabela[nome] = entrada;
    return entrada;
}

std::shared_ptr<EntradaTabela> TabelaSimbolos::buscar(const std::string& nome) {
    auto it = tabela.find(nome);
    if (it != tabela.end()) {
        return it->second;
    }
    return nullptr;
}

// Implementação dos métodos da classe PilhaTabelaSimbolos

PilhaTabelaSimbolos::PilhaTabelaSimbolos() {
    iniciar();
}

void PilhaTabelaSimbolos::iniciar() {
    pilha.clear();
    // Cria o escopo global inicial
    criarEscopo();
}

void PilhaTabelaSimbolos::criarEscopo() {
    pilha.push_back(TabelaSimbolos());
}

std::shared_ptr<EntradaTabela> PilhaTabelaSimbolos::buscarSimbolo(const std::string& nome) {
    // Busca do topo para a base da pilha
    for (int i = pilha.size() - 1; i >= 0; i--) {
        std::shared_ptr<EntradaTabela> entrada = pilha[i].buscar(nome);
        if (entrada != nullptr) {
            return entrada;
        }
    }
    return nullptr;
}

void PilhaTabelaSimbolos::removerEscopoAtual() {
    if (!pilha.empty()) {
        pilha.pop_back();
    }
}

std::shared_ptr<EntradaTabela> PilhaTabelaSimbolos::inserirFuncao(const std::string& nome, TipoVar tipo, int numParams) {
    auto entrada = std::make_shared<EntradaTabela>(nome, tipo, numParams);
    return topoTabela().inserir(nome, entrada);
}

std::shared_ptr<EntradaTabela> PilhaTabelaSimbolos::inserirVariavel(const std::string& nome, TipoVar tipo, int posicao) {
    auto entrada = std::make_shared<EntradaTabela>(nome, tipo, posicao);
    return topoTabela().inserir(nome, entrada);
}

std::shared_ptr<EntradaTabela> PilhaTabelaSimbolos::inserirParametro(const std::string& nome, TipoVar tipo, int posicao, std::shared_ptr<EntradaTabela> funcao) {
    auto entrada = std::make_shared<EntradaTabela>(nome, tipo, posicao, funcao.get());
    return topoTabela().inserir(nome, entrada);
}

void PilhaTabelaSimbolos::eliminar() {
    pilha.clear();
}

TabelaSimbolos& PilhaTabelaSimbolos::topoTabela() {
    if (pilha.empty()) {
        throw std::runtime_error("Tentativa de acessar tabela em pilha vazia.");
    }
    return pilha.back();
}

bool PilhaTabelaSimbolos::vazia() const {
    return pilha.empty();
}