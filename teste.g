/* 
   Arquivo de teste para o analisador léxico de Goianinha
   Este arquivo contém exemplos de todos os tipos de tokens
*/

/* Declaração de variáveis e funções globais */
int n;
car c;

/* Função para calcular o fatorial */
int fatorial(int n) {
    /* Implementação recursiva do fatorial */
    se (n <= 1) entao
        retorne 1;
    senao
        retorne n * fatorial(n - 1);
}

/* Função para verificar se um número é par */
int ehPar(int num) {
    retorne (num / 2) * 2 == num;
}

/* Função para encontrar o máximo entre dois números */
int max(int a, int b) {
    se (a > b) entao
        retorne a;
    senao
        retorne b;
}

/* Programa principal */
programa {
    int i, resultado, valor;
    
    /* Solicita um valor ao usuário */
    escreva "Digite um numero inteiro: ";
    leia valor;
    novalinha;
    
    /* Calcula e exibe o fatorial */
    resultado = fatorial(valor);
    escreva "O fatorial de ";
    escreva valor;
    escreva " eh ";
    escreva resultado;
    novalinha;
    
    /* Verifica se o número é par ou ímpar */
    se (ehPar(valor)) entao {
        escreva "O numero eh par!";
    } senao {
        escreva "O numero eh impar!";
    }
    novalinha;
    
    /* Exibe todos os números até valor */
    i = 1;
    enquanto (i <= valor) execute {
        escreva i;
        escreva " ";
        i = i + 1;
    }
    novalinha;
    
    /* Testa operadores lógicos */
    se ((valor > 10) e (valor < 20)) entao {
        escreva "Valor entre 10 e 20";
    } senao se ((valor <= 10) ou (valor >= 20)) entao {
        escreva "Valor fora do intervalo 10-20";
    }
    novalinha;
    
    /* Testa operador de negação */
    se (!ehPar(valor)) entao {
        escreva "Negacao funciona!";
    }
    
    retorne 0;
}