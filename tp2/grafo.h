#ifndef _grafo_h_
#define _grafo_h_
///////////////////////////////////////////////////////////////
//Tipos de estruturas de dados usados no grafo

typedef struct TipoVertice{
  char caracter;
  int valor;
  int e_worm;
  int wormx;
  int wormy;
}TipoVertice; //Vertice do grafo

typedef struct TipoCelula *TipoApontador;

struct TipoCelula{
  int e;
  TipoVertice vertice;
  TipoApontador prox;
}TipoCelula;

typedef struct TipoLista{
  TipoApontador primeiro, ultimo;
}TipoLista;//A lista de adjacência

typedef struct TipoGrafo{
  TipoLista adj[70];
  int v;
  int arestas;
}TipoGrafo;//Representa o grafo

#endif
////////////Funçoes do vertice/////////

void aloca_entrada(TipoVertice **entrada, int n, int m);
//aloca a matriz contendo os vertices da entrada

int check_aux(char a);
//checa se foi lido o inicio de um buraco de minhoca

void define_worm(char aux, char aux2, TipoVertice *v);
//Atribui caracteristicas a um vertice buraco de minhoca

void define_vertice(char aux, TipoVertice *v);
//Atribui caracteristicas a um vertice

void libera_entrada(TipoVertice **entrada, int n);
//libera a matriz que guarda a entrada

////////////Funçoes da Lista///////////////////
//Lista, usado na concepção do grafo
//Lista por meio de apontadores

void faz_lista_vazia(TipoLista *lista);
//Cria lista

int check_vazia(TipoLista lista);
//Olha se a lista está vazia

void insere(TipoVertice v, TipoLista *lista);
//insere novo elemento

void insere_int(int a, TipoLista *lista);
//Insere um inteiro na lista, usada na lista que guardas as distâncias ate a saida, E

//void imprime(TipoLista lista);//imprime elementos

void imprime_resp(TipoLista lista);
//imprime a resposta do trabalho

void libera_lista(TipoLista lista);
//libera a lista alocada

////////////Funçoes do Grafo///////////
void monta_grafo_vazio(TipoGrafo *G, int n, int m);
//Monta o grafo

void insere_aresta(int v1, TipoVertice v2, TipoGrafo *G);
//insere uma aresta entre dois vertices

void arestas(TipoVertice **entrada, TipoGrafo *G, int n, int m);
//administra em mais alto nivel a insercao de arestas

void libera_grafo(TipoGrafo *G);
//Libera o espaço usado pelo grafo
