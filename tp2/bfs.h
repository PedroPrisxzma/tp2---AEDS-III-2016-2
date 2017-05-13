#include "grafo.h"
////////Busca em Largura para achar menor caminho/////
//Estrura auxiliares
typedef int TipoCor;

typedef struct TipoFila{
TipoApontador frente, tras;
}TipoFila;

//////////////Funçoes da Fila/////////////
void faz_fila_vazia(TipoFila *fila);
//faz uma nova fila vazia

int fila_check_vazia(TipoFila fila);
//checa se a fila não está vazia

void enfileira(TipoVertice v, TipoFila *fila);
//enfileira um novo elemento

int desenfileira(TipoFila *fila, TipoVertice *v);
//desenfileira um elemento

////////////Funçoes busca em largura////
void Bfs(TipoGrafo *G, int t, int origem);
//A busca em largura inicial, inicia o processo de busa

void visitabfs(int w, int dis, TipoGrafo *G, TipoCor *cor, int *dist, int *antecessor, TipoLista *E_lista, int c, int d, int h, int s, int t, int k);
//Administra as busca em largura e suas checagens

int player_check_porta(int c, int d, int h, int s, char a);
//Checa se o vertice é uma porta

int player_check_key(int c, int d, int h, int s, char a, int t, int keys);
//Checa se o vertice é um chave

void adj_check(TipoGrafo *G, TipoCor *cor, int *dist, int *antecessor, int w, TipoFila *fila, TipoLista *E_lista, int c, int d, int h, int s, int t, int keys);
//Faz as checagens de vizinhos de um vertice dentro do bfs

void said_buraco_arruma(TipoGrafo *G, int v, int w, int operacao);
//Arruma as variações que devem ocorrer ao analisar casos de buraco
