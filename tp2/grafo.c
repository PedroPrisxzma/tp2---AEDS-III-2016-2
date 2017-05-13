#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"
/////////////////////////////////////Funções para os Vertices//////////////////
//Aloca a matriz de entrada
void aloca_entrada(TipoVertice **entrada, int n, int m){
  int i,j;
  for(i = 0;i < n;i++){
    entrada[i] = (TipoVertice*)calloc(m, sizeof(TipoVertice));
    for(j = 0;j < m;j++){
      entrada[i][j].e_worm = 0;
      entrada[i][j].wormx = 0;
      entrada[i][j].wormy = 0;
    }
  }
}

//Confere se n foi lido um indicador de buraco de minhoca
int check_aux(char a){
  if(a == '0' || a == '1' || a == '2' || a == '3' || a == '4' || a == '5' || a == '6' || a == '7' || a == '8' || a == '9')
    return 1;
  else
    return 0;
}

//Configura o vertice caso seja buraco
void define_worm(char aux, char aux2, TipoVertice *v){
  v->caracter = 'w';
  v->e_worm = 1;
  v->wormx = aux - '0';
  v->wormy = aux2 - '0';
}

//Determina o caracter de um vertice
void define_vertice(char aux, TipoVertice *v){
  v->caracter = aux;
}

//Libera a matriz de entrada
void libera_entrada(TipoVertice **entrada, int n){
  int i;
  for(i = 0;i < n;i++){
    free(entrada[i]);
  }
}
/////////////////////////////////Funçoes para a Lista//////////////////////////
//Faz a lista vazia
void faz_lista_vazia(TipoLista *lista){
  lista->primeiro = (TipoApontador)malloc(sizeof(TipoCelula));
  lista->ultimo = lista->primeiro;
  lista->primeiro->prox = NULL;
}

//Confere se a lista està vazia
int check_vazia(TipoLista lista){
  return(lista.primeiro == lista.ultimo);
}

//Insere um novo elemento na lista de adjacencia
void insere(TipoVertice v, TipoLista *lista){
  lista->ultimo->prox = (TipoApontador)malloc(sizeof(TipoCelula));
  lista->ultimo = lista->ultimo->prox;
  lista->ultimo->vertice = v;
  lista->ultimo->prox = NULL;
}

//Insere um inteiro na lista, usada para lista da saida E
void insere_int(int a, TipoLista *lista){
  lista->ultimo->prox = (TipoApontador)malloc(sizeof(TipoCelula));
  lista->ultimo = lista->ultimo->prox;
  lista->ultimo->e = a;
  lista->ultimo->prox = NULL;
}

//Imprime uma determinada lista recebida como parâmetro
void imprime(TipoLista lista){
  TipoApontador aux;
  aux = lista.primeiro->prox;
  while(aux!=NULL){
    printf("%d\n", aux->vertice.caracter);
  }
}

//Imprime a saida do programa
void imprime_resp(TipoLista lista){
  TipoApontador aux;
  int menor;
  if(check_vazia(lista)){
    printf("-1\n");
  }
  else{
    aux = lista.primeiro->prox;
    menor = aux->e;
    while(aux!=NULL){
      if(menor > aux->e){
        menor = aux->e;
      }
      aux = aux->prox;
    }
    printf("%d\n", menor);
  }
}

//Libera a lista
void libera_lista(TipoLista lista){
  TipoApontador anterior, aux;
  aux = lista.primeiro->prox;
  free(lista.primeiro);
  lista.primeiro = NULL;
  while(aux!=NULL){
    anterior = aux;
    aux = aux->prox;
    free(anterior);
  }
}
/////////////////////////////////Funções para o grafo em si////////////////////

void monta_grafo_vazio(TipoGrafo *G, int n, int m){
  int i;
  G->v = n*m;
  for(i = 0;i < (n*m);i++){
    faz_lista_vazia(&G->adj[i]);
  }
}

void insere_aresta(int v1, TipoVertice v2, TipoGrafo *G){
  if(v2.caracter != '#'){
    insere(v2, &G->adj[v1]);
  }
}

//administra insercao de arestas
void arestas(TipoVertice **entrada, TipoGrafo *G, int n, int m){
  int i, j;
  int a, b;
  for(i = 0;i < n;i++){
    for(j = 0;j < m;j++){
      if(entrada[i][j].e_worm){
        a = entrada[i][j].wormx;
        b = entrada[i][j].wormy;
        insere_aresta(entrada[i][j].valor, entrada[a][b], G);
      }
      if(entrada[i][j].caracter != '#'){
        if(i == 0){
          if(i+1 < n){
            insere_aresta(entrada[i][j].valor, entrada[i+1][j], G);
          }
          if(j == 0 && j+1 < m){
            insere_aresta(entrada[i][j].valor, entrada[i][j+1], G);
          }
          else if(j == m-1 && j-1 > -1){
            insere_aresta(entrada[i][j].valor, entrada[i][j-1], G);
          }
          else if(j > 0 && j < m-1){
            insere_aresta(entrada[i][j].valor, entrada[i][j+1], G);
            insere_aresta(entrada[i][j].valor, entrada[i][j-1], G);
          }
        }
        else if(i == n-1){
          if(i-1 > -1){
            insere_aresta(entrada[i][j].valor, entrada[i-1][j], G);
          }
          if(j == 0 && j+1 < m){
            insere_aresta(entrada[i][j].valor, entrada[i][j+1], G);
          }
          else if(j == m-1 && j-1 > -1){
            insere_aresta(entrada[i][j].valor, entrada[i][j-1], G);
          }
          else if(j > 0 && j < m-1){
            insere_aresta(entrada[i][j].valor, entrada[i][j+1], G);
            insere_aresta(entrada[i][j].valor, entrada[i][j-1], G);
          }
        }
        else if(j == 0 && i > 0 && i < n-1){
          if(j+1 < m){
          insere_aresta(entrada[i][j].valor, entrada[i][j+1], G);
          }
          insere_aresta(entrada[i][j].valor, entrada[i+1][j], G);
          insere_aresta(entrada[i][j].valor, entrada[i-1][j], G);
        }
        else if(j == m-1 && i > 0 && i < n-1){
          if(j-1 > -1){
          insere_aresta(entrada[i][j].valor, entrada[i][j-1], G);
          }
          insere_aresta(entrada[i][j].valor, entrada[i+1][j], G);
          insere_aresta(entrada[i][j].valor, entrada[i-1][j], G);
        }
        else if(j > 0 && j < m-1 && i > 0 && i < n-1){
          insere_aresta(entrada[i][j].valor, entrada[i][j+1], G);
          insere_aresta(entrada[i][j].valor, entrada[i][j-1], G);
          insere_aresta(entrada[i][j].valor, entrada[i+1][j], G);
          insere_aresta(entrada[i][j].valor, entrada[i-1][j], G);
        }
      }
    }
  }
}


//Libera o espaço do grafo
void libera_grafo(TipoGrafo *G){
  int i;
  TipoApontador anterior, aux;
  for(i = 0;i < G->v;i++){
    aux = G->adj[i].primeiro->prox;
    free(G->adj[i].primeiro);
    G->adj[i].primeiro = NULL;
    while(aux!=NULL){
      anterior = aux;
      aux = aux->prox;
      free(anterior);
    }
  }
  G->v = 0;
}
