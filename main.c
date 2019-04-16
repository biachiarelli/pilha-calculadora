#include <stdio.h>
#include "calculadora.h"

int main(){
    int escolha=0;
    char expressao[100];

    while(escolha != 3){

    printf("1.Resolucao de expressao\n2.Calculadora\n3.Sair\n=");
    scanf("%d", &escolha);

        if(escolha == 1){
            printf("\nResolucao de expressao\n\nDigite a expressao: \n");
            scanf("%s", expressao);
            getchar();

            t_pilha* pilha = getPilha(20);
            resolucao_expressao(pilha, expressao);
        }
        else if(escolha == 2){
            printf("\nModo Calculadora\n");
            t_pilha* pilha = getPilha(20);
            modo_calculadora(pilha);
        }
        else if(escolha == 3){
            printf("\nSair\n");
        }
    }

return 0;
}
