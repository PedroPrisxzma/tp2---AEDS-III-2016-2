#include <stdio.h>
#include <stdlib.h>
#include "bfs.h"
#include "grafo.h"

int main(){
  int n, m, t;
  int i, j;
  int count;
  int origem;
  char aux, aux2;
  char lixo;
  scanf("%d %d %d", &n, &m, &t);
  TipoVertice **entrada = (TipoVertice**)calloc(n, sizeof(TipoVertice*));
  aloca_entrada(entrada, n ,m);
  TipoGrafo *G = (TipoGrafo*)malloc(sizeof(TipoGrafo));
  monta_grafo_vazio(G, n, m);

  count = 0;
  for(i = n-1;i >= 0;i--){
    for(j = 0;j < m;j++){
      scanf("%c %c", &lixo, &aux);
      if(aux == 'V'){
        origem = count;
      }
      entrada[i][j].valor = count;
      count++;
      if(check_aux(aux)){
        scanf("%c", &aux2);
        define_worm(aux, aux2, &entrada[i][j]);
      }
      else
        define_vertice(aux, &entrada[i][j]);
    }
  }

  arestas(entrada, G, n, m);
  Bfs(G, t, origem);
  libera_grafo(G);
  free(G);
  libera_entrada(entrada, n);
  free(entrada);
  return 0;
}
