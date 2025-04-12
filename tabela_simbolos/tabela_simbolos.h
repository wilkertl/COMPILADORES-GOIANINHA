#ifndef TABELA_SIMBOLOS_H
#define TABELA_SIMBOLOS_H

#include <string>
#include <vector>
#include <unordered_map>
#include <memory>

// Definição dos tipos possíveis em Goianinha
enum class TipoVar {
    INTEIRO,
    CARACTERE
};

// Definição dos tipos de entradas na tabela de símbolos
enum class TipoEntrada {
    VARIAVEL,
    FUNCAO,
    PARAMETRO
};

// Estrutura para representar uma entrada na tabela de símbolos
struct EntradaTabela {
    std::string nome;         // Nome do símbolo
    TipoEntrada tipoEntrada;  // Tipo da entrada (variável, função ou parâmetro)
    TipoVar tipo;             // Tipo do símbolo (int ou car)
    int posicao;              // Posição na declaração (para variáveis e parâmetros)
    int numParams;            // Número de parâmetros (para funções)
    EntradaTabela* funcao;    // Ponteiro para a função à qual o parâmetro pertence
    
    // Construtor para variáveis
    EntradaTabela(const std::string& nome, TipoVar tipo, int posicao)
        : nome(nome), tipoEntrada(TipoEntrada::VARIAVEL), tipo(tipo), posicao(posicao), numParams(0), funcao(nullptr) {}
    
    // Construtor para funções
    EntradaTabela(const std::string& nome, TipoVar tipoRetorno, int numParams)
        : nome(nome), tipoEntrada(TipoEntrada::FUNCAO), tipo(tipoRetorno), posicao(0), numParams(numParams), funcao(nullptr) {}
    
    // Construtor para parâmetros
    EntradaTabela(const std::string& nome, TipoVar tipo, int posicao, EntradaTabela* funcao)
        : nome(nome), tipoEntrada(TipoEntrada::PARAMETRO), tipo(tipo), posicao(posicao), numParams(0), funcao(funcao) {}
};

// Representação de uma tabela de símbolos (um escopo)
class TabelaSimbolos {
private:
    std::unordered_map<std::string, std::shared_ptr<EntradaTabela>> tabela;

public:
    TabelaSimbolos();
    
    // Insere um símbolo na tabela e retorna um ponteiro para a entrada
    std::shared_ptr<EntradaTabela> inserir(const std::string& nome, std::shared_ptr<EntradaTabela> entrada);
    
    // Busca um símbolo na tabela pelo nome
    std::shared_ptr<EntradaTabela> buscar(const std::string& nome);
};

// Pilha de tabelas de símbolos para gerenciar os escopos
class PilhaTabelaSimbolos {
private:
    std::vector<TabelaSimbolos> pilha;

public:
    PilhaTabelaSimbolos();
    
    // Inicializa a pilha de tabelas
    void iniciar();
    
    // Cria um novo escopo e o empilha
    void criarEscopo();
    
    // Busca um símbolo na pilha de tabelas, começando pelo topo
    std::shared_ptr<EntradaTabela> buscarSimbolo(const std::string& nome);
    
    // Remove o escopo atual
    void removerEscopoAtual();
    
    // Insere uma função na tabela de símbolos atual
    std::shared_ptr<EntradaTabela> inserirFuncao(const std::string& nome, TipoVar tipo, int numParams);
    
    // Insere uma variável na tabela de símbolos atual
    std::shared_ptr<EntradaTabela> inserirVariavel(const std::string& nome, TipoVar tipo, int posicao);
    
    // Insere um parâmetro na tabela de símbolos atual
    std::shared_ptr<EntradaTabela> inserirParametro(const std::string& nome, TipoVar tipo, int posicao, std::shared_ptr<EntradaTabela> funcao);
    
    // Elimina a pilha de tabelas de símbolos
    void eliminar();
    
    // Retorna a tabela atual (no topo da pilha)
    TabelaSimbolos& topoTabela();
    
    // Verifica se a pilha está vazia
    bool vazia() const;
};

#endif // TABELA_SIMBOLOS_H