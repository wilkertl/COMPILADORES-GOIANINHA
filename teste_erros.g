/* 
   Arquivo de teste para erros léxicos em Goianinha
*/

/* Erro 1: Uso de caractere inválido */
int valor = 10@20;  // @ é um caractere inválido

/* Erro 2: Comentário não terminado 
   Este comentário não tem fechamento

/* Erro 3: String multi-linha */
escreva "Esta string começa aqui
e termina aqui";

/* Erro 4: Uso de caracteres não ASCII */
int variável;  // 'á' não é um caractere válido para identificadores

/* Teste com tokens válidos */
programa {
    int x, y;
    x = 10;
    y = 20;
    
    se (x > y) entao {
        escreva "x é maior";
    } senao {
        escreva "y é maior ou igual";
    }
}