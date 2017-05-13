#include <stdio.h>
#include <stdlib.h>
#include "bfs.h"
#include "grafo.h"
#define branco 0
#define cinza 1
#define preto 2
#define infinito 100000000


///////////////////////Parte da Fila///////////////////////////////////////////

//monta fila vazia
void faz_fila_vazia(TipoFila *fila){
  fila->frente = (TipoApontador)calloc(1, sizeof(TipoCelula));
  fila->tras = fila->frente;
  fila->frente->prox = NULL;
}

//olha se a fila está vazia
int fila_check_vazia(TipoFila fila){
  return(fila.frente == fila.tras);
}

//enfileira novo elemento
void enfileira(TipoVertice v, TipoFila *fila){
  fila->tras->prox = (TipoApontador)calloc(1, sizeof(TipoCelula));
  fila->tras = fila->tras->prox;
  fila->tras->vertice = v;
  fila->tras->prox = NULL;
}

//desenfileira um elemento
int desenfileira(TipoFila *fila, TipoVertice *v){
  TipoApontador aux;
  int i;
  if(fila_check_vazia(*fila)){
    printf("Fila ja esta vazia\n");
    return -1;
  }
  aux = fila->frente;
  fila->frente = fila->frente->prox;
  v = &fila->frente->vertice;
  i = v->valor;
  free(aux);
  return (i);
}

//imprime a fila, foi usada para visualizar a execução do programa
void imprime_fila(TipoFila *fila){
  TipoApontador aux;
  aux = fila->frente->prox;
  while(aux != NULL){
    printf("%d\n", aux->vertice.valor);
    aux = aux->prox;
  }
}
///////////////////////Busca em Largura////////////////////////////////////////

//função que administra o inicio da busca em largura
void Bfs(TipoGrafo *G, int t, int origem){
  int i;
  TipoLista E_lista;
  TipoCor cor[(G->v)+1];
  int dist[(G->v)+1];
  int antecessor[(G->v)+1];
  faz_lista_vazia(&E_lista);
  for(i = 0;i < G->v;i++){
    cor[i] = branco;
    dist[i] = infinito;
    antecessor[i] = -1;
  }
  if(cor[origem] == branco){
    cor[origem] = cinza;
    dist[origem] = 0;
    visitabfs(origem, 0, G, cor, dist, antecessor, &E_lista, 0, 0, 0, 0, t, 0);
  }
  imprime_resp(E_lista);
  libera_lista(E_lista);
}

//Realiza As visitas em largura
void visitabfs(int w, int dis, TipoGrafo *G, TipoCor *cor, int *dist, int *antecessor, TipoLista *E_lista, int c, int d, int h, int s, int t, int k){
  TipoFila fila;
  TipoVertice vert;
  vert.valor = w;
  dist[w] = dis;
  int keys = k;//num de chaves carregadas atualmente
  int key[4];
  key[0] = c;
  key[1] = d;
  key[2] = h;
  key[3] = s;

  faz_fila_vazia(&fila);
  enfileira(vert, &fila);

  while(!fila_check_vazia(fila)){
    w = desenfileira(&fila, &vert);
    if(w == -1){
      continue;
    }
    adj_check(G, cor, dist, antecessor, w, &fila, E_lista, key[0], key[1], key[2], key[3], t, keys);
    cor[w] = preto;
  }
  free(fila.frente);
}

//Função que olhas os vizinhos de um vertice para enfileirar, e checa casos especiais
void adj_check(TipoGrafo *G, TipoCor *cor, int *dist, int *antecessor, int w, TipoFila *fila, TipoLista *E_lista, int c, int d, int h, int s, int t, int keys){
  TipoApontador aux;
  int cc = 0, dd = 0, hh = 0, ss = 0;

  if(!check_vazia(G->adj[w])){
    aux = G->adj[w].primeiro->prox;
    while(aux != NULL){

      //Faz checagem caso encontre uma porta
      if(player_check_porta(c, d, h, s, aux->vertice.caracter) && cor[aux->vertice.valor] == branco){
        cor[aux->vertice.valor] = cinza;
        dist[aux->vertice.valor] = dist[w] + 1;
        antecessor[aux->vertice.valor] = w;
        enfileira(aux->vertice, fila);
      }

      //Faz checagem quando encontra chave
      else if(player_check_key(c, d ,h, s, aux->vertice.caracter, t, keys)){
        if(aux->vertice.caracter == 'c'){
          cc = 1;
        }
        else if(aux->vertice.caracter == 'd'){
          dd = 1;
        }
        else if(aux->vertice.caracter == 'h'){
          hh = 1;
        }
        else if(aux->vertice.caracter == 's'){
          ss = 1;
        }
        keys++;
        visitabfs(aux->vertice.valor, dist[w]+1, G, cor, dist, antecessor, E_lista, cc, dd, hh, ss, t, keys);
        keys--;
        if(aux->vertice.caracter == 'c'){
          cc = 0;
        }
        else if(aux->vertice.caracter == 'd'){
          dd = 0;
        }
        else if(aux->vertice.caracter == 'h'){
          hh = 0;
        }
        else if(aux->vertice.caracter == 's'){
          ss = 0;
        }
      }
      else if(aux->vertice.e_worm == 1){//Faz checagem caso encontre um buraco
        int buraco_num = aux->vertice.valor;
        int saida_buraco;
        TipoApontador aux2;
        saida_buraco = G->adj[buraco_num].primeiro->prox->vertice.valor;

        //checa se a saida do buraco é a saida E
        if(G->adj[buraco_num].primeiro->prox->vertice.caracter == 'E'){
          insere_int(dist[w]+1, E_lista);
        }
        said_buraco_arruma(G, w, buraco_num, 0);
        aux2 = G->adj[buraco_num].primeiro->prox;
        G->adj[buraco_num].primeiro->prox = aux2->prox;
        said_buraco_arruma(G, saida_buraco, buraco_num, 0);
        visitabfs(saida_buraco, dist[w]+1, G, cor, dist, antecessor, E_lista, c, d, h, s, t, keys);
        said_buraco_arruma(G, saida_buraco, buraco_num, 1);
        G->adj[buraco_num].primeiro->prox = aux2;
        said_buraco_arruma(G, w, buraco_num, 1);
      }

      else if(aux->vertice.caracter == 'E'){//Faz checagem da saída
        insere_int(dist[w]+1, E_lista);
      }

      //caso seja apenas um .
      else if(aux->vertice.caracter == '.' && cor[aux->vertice.valor] == branco){
        cor[aux->vertice.valor] = cinza;
        dist[aux->vertice.valor] = dist[w] + 1;
        antecessor[aux->vertice.valor] = w;

        enfileira(aux->vertice, fila);
      }
      aux = aux->prox;
    }
  }
}

//Checa se é uma porta e caso seha, se tem-se a chave
int player_check_porta(int c, int d, int h, int s, char a){
  if(a == 'C'){
    if(c == 1){
      return 1;
    }
  }
  else if(a == 'D'){
    if(d == 1){
      return 1;
    }
  }
  else if(a == 'H'){
    if(h == 1){
      return 1;
    }
  }
  else if(a == 'S'){
    if(s == 1){
      return 1;
    }
  }
  return 0;
}

//checa se é uma chave e caso seja, se é possível pegá-la
int player_check_key(int c, int d, int h, int s, char a, int t, int keys){
  if(a == 'c'){
    if(t > keys && c == 0){
      return 1;
    }
  }
  else if(a == 'd'){
    if(t > keys && d == 0){
      return 1;
    }
  }
  else if(a == 'h'){
    if(t > keys && h == 0){
      return 1;
    }
  }
  else if(a == 's'){
    if(t > keys && s == 0){
      return 1;
    }
  }
  return 0;
}

//Arruma e ajusta os casos em que se encontra um buraco
void said_buraco_arruma(TipoGrafo *G, int v, int w, int operacao){
  TipoApontador aux;
  if(!check_vazia(G->adj[v])){
    aux = G->adj[v].primeiro->prox;
    while(aux != NULL){
      if(aux->vertice.valor == w){
        if(operacao == 0){
          aux->vertice.e_worm = 0;
          aux->vertice.caracter = '.';
        }
        else{
          aux->vertice.e_worm = 1;
          aux->vertice.caracter = 'w';
        }
      }
      aux = aux->prox;
    }
  }
}
