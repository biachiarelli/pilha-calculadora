#ifndef CALCULADORA_H
#define CALCULADORA_H

#define VAZIA -1

typedef struct pilha{
    int topo;
    int *item;
    int tamanho;
} t_pilha;

t_pilha* getPilha(int tamanho);
void    liberaPilha(t_pilha* pilha);
int     pilhaVazia(t_pilha* pilha);
int     pilhaCheia(t_pilha* pilha);
void    push( t_pilha* pilha, int valor);
int     pop(t_pilha* pilha);
int     topo(t_pilha* pilha);
void    imprimirPilha(t_pilha* pilha);
void    modo_calculadora(t_pilha* pilha);
void    resolucao_expressao(t_pilha* pilha, char expressao[]);
int     validacao_infixa(t_pilha* pilha, char expressao[]);

#endif
