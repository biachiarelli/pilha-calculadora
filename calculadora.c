#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include "calculadora.h"

/*---------------------------------------------*/
int topo(t_pilha* pilha){

    if(pilhaVazia(pilha)){
        printf("Ocorreu underflow na pilha!\n");
        liberaPilha(pilha);
        exit(1);
    }

    return pilha->item[pilha->topo];
}

/*---------------------------------------------*/
void imprimirPilha(t_pilha* pilha){
    int i;

    if(pilhaVazia(pilha)){
        printf("Pilha Vazia!\n");
        return;
    }

    printf("________________________________\n");
    for(i = pilha->topo; i > VAZIA; i--)
        printf("%d\n", pilha->item[i]);

}

/*---------------------------------------------*/
void push( t_pilha* pilha, int valor){

    if( pilhaCheia(pilha) ){
        printf("Ocorreu overflow na pilha!\n");
        liberaPilha(pilha);
        exit(1);
    }

    pilha->item[++pilha->topo] = valor;

}

/*---------------------------------------------*/
int  pop(t_pilha* pilha){

    if(pilhaVazia(pilha)){
        printf("Ocorreu underflow na pilha!\n");
        liberaPilha(pilha);
        exit(1);
    }

    return pilha->item[pilha->topo--];
}


/*---------------------------------------------*/
int pilhaVazia(t_pilha* pilha){
    return ( pilha->topo == VAZIA );
}

/*---------------------------------------------*/
int pilhaCheia(t_pilha* pilha){
    return ( pilha->topo == pilha->tamanho );
}

/*---------------------------------------------*/
t_pilha* getPilha(int tamanho){
    t_pilha* retorno = (t_pilha *) malloc(sizeof(t_pilha));
    retorno->item    = (int *) malloc(tamanho*sizeof(int));
    retorno->tamanho = tamanho;
    retorno->topo    = VAZIA;
    return retorno;
}

/*---------------------------------------------*/
void liberaPilha(t_pilha* pilha){
    free(pilha->item);
    free(pilha);

}

/*---------------------------------------------*/
int validacao_infixa(t_pilha* pilha, char expressao[]){
    int i=0, valida=1;
    char c;

    while((expressao[i] != '\0') && (valida != 0)){
        if(expressao[i] == '(' ){
            push(pilha, (int) expressao[i]);
        }

        if(expressao[i] == ')' ){
            if(pilhaVazia(pilha)){
                valida = 0;
            }
            else{
                c = (char) pop(pilha);

                if(expressao[i] == ')'){
                    if( c != '('){
                        valida = 0;
                       }
                }
            }
        }

        i++;
    }

    if( !pilhaVazia(pilha) ){
        valida=0;
    }

return valida;
}


/*---------------------------------------------*/

void resolucao_expressao(t_pilha* pilha, char expressao[]){
    int i=0, j=0, valida;
    char saida[100], operador1, operador2, resposta, aux;

    if( !validacao_infixa(pilha, expressao) ){
        printf("A expressao nao e valida\n\n");
        return ;
    }

    else{

    i=0;
        while(expressao[i] != '\0'){
            if(expressao[i] == '(' )
                push(pilha, expressao[i]);

            else if(expressao[i] == '+' || expressao[i] == '-'){
                if(( !pilhaVazia(pilha)) && (topo(pilha) == '+' || topo(pilha) == '-' || topo(pilha) == '*' || topo(pilha) == '/')){
                     saida[j] = pop(pilha);
                     push(pilha, expressao[i]);
                     j++;
                }
                else{
                    push(pilha,  expressao[i]);
                }
            }
            else if(expressao[i] == '*' || expressao[i] == '/'){
                if( !pilhaVazia(pilha)  && (topo(pilha) == '*' || topo(pilha) == '/')){
                     saida[j] = pop(pilha);
                     push(pilha, expressao[i]);
                     j++;
                }
                else{
                    push(pilha, expressao[i]);
                }
            }

            else if(expressao[i] == ')' ){
                while((!pilhaVazia(pilha)) && (valida != 0)){
                    if(topo(pilha) == '(' ){
                        pop(pilha);
                        valida = 0;
                    }
                    else{
                        saida[j] = pop(pilha);
                        j++;
                    }
                }
            }
            else {
                saida[j] = expressao[i];
                j++;
            }
            i++;
    }

        while(!pilhaVazia(pilha)){
        saida[j] = pop(pilha);
        j++;
        }

    }

    for(i=0; i<j; i++){
        if( isdigit(saida[i]) ){
            aux = saida[i] - 48;
            push(pilha, aux);

        }
        else{
            switch (saida[i]){

                case '+':
                operador1 = pop(pilha);
                operador2 = pop(pilha);
                resposta = operador1  + operador2;
                push(pilha, resposta);
                break;

                case '-':
                operador1 = pop(pilha);
                operador2 = pop(pilha);
                resposta = operador2  - operador1;
                push(pilha, resposta);
                break;

                case '*':
                operador1 = pop(pilha);
                operador2 = pop(pilha);
                resposta = operador1  * operador2;
                push(pilha, resposta);
                break;

                case '/':
                operador1 = pop(pilha);
                operador2 = pop(pilha);
                resposta = operador2  / operador1;
                push(pilha, resposta);
                break;
                }
        }
    }

    imprimirPilha(pilha);
    printf("\n");
    liberaPilha(pilha);

    }


/*---------------------------------------------*/
 void modo_calculadora(t_pilha* pilha){
    int i=0, j;
    char valor[100], operador1, operador2, resposta;

    while(valor[0] != 's' ){

        printf("-> ");
        scanf("%s", valor);
        getchar();

        if( isdigit (valor[0])) {
            push(pilha, atoi(valor) );
            i++;
            imprimirPilha(pilha);
        }

        else if(valor[0] == 's'){
            return;
        }

        else{
            if ((i<2) && (valor[0] != 's') ){
                printf("Numero de operadores insuficiente\n\n");
                return;
            }

            switch(valor[0]){
                case '+':
                    operador1 = pop(pilha);
                    operador2 = pop(pilha);
                    resposta = (operador1) + (operador2);
                    push(pilha, resposta);
                    i--;
                break;

                case '-':
                    operador1 = pop(pilha);
                    operador2 = pop(pilha);
                    resposta = (operador1) - (operador2 );
                    push(pilha, resposta);
                    i--;
                break;

                case '*':
                    operador1 = pop(pilha);
                    operador2 = pop(pilha);
                    resposta = (operador1) * (operador2 );
                    push(pilha, resposta);
                    i--;
                break;

                case '/':
                    operador1 = pop(pilha);
                    operador2 = pop(pilha);
                    resposta = (operador1) / (operador2 );
                    push(pilha, resposta);
                    i--;
                break;

                case 'c':
                    operador1 = pop(pilha);
                    operador2 = pop(pilha);
                    i=i-2;
                        for(j=0; j<operador1; j++){
                            push(pilha, operador2);
                            i++;
                        }
                break;

                case '!':
                    switch(valor[1]){

                        resposta = 0;

                        case '+':
                            while(!pilhaVazia(pilha)){
                                operador1 = pop(pilha);
                                resposta = operador1 + resposta;
                                i--;
                            }
                            push(pilha, resposta);
                        break;

                        case '-':
                            while(!pilhaVazia(pilha)){
                                operador1 = pop(pilha);
                                resposta = operador1 - resposta;
                                i--;
                            }
                            push(pilha, resposta);
                        break;

                        case '*':
                            while(!pilhaVazia(pilha)){
                                operador1 = pop(pilha);
                                resposta = operador1 * resposta;
                                i--;
                            }
                            push(pilha, resposta);
                        break;

                        case '/':
                            while(!pilhaVazia(pilha)){
                                operador1 = pop(pilha);
                                resposta = operador1 / resposta;
                                i--;
                            }
                            push(pilha, resposta);
                        break;
                    }
                break;

            }

        imprimirPilha(pilha);
        }
    }
    liberaPilha(pilha);
 }
