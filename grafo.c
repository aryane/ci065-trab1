#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <graphviz/cgraph.h>
#include "grafo.h"

typedef struct vertice {
  struct vertice *vizinho; // lista ligada de vizinhos
  double *peso; // vetor de pesos de tamanho n
  char *nome;
  int n;
} vertice;

// estrutura de dados para representar um grafo simples
// o grafo pode ser
// - direcionado ou não
// - com pesos nas arestas ou não
// além dos vértices e arestas, o grafo tem um nome
// os vértices do grafo também tem nome
// os nomes do grafo e dos vértices são strings quaisquer
// num grafo com pesos nas arestas todas as arestas tem peso, que é um double
// o peso default de uma aresta é 0.0
struct grafo {
  int direcionado;
  char *nome;
  vertice *nos;
};

vertice *cria_vertice(Agedge_t *a);
vertice *insere_vertice(vertice *g, vertice *v);


static Agedge_t **arestas;
static int busca_aresta(Agedge_t *a, int n_arestas_visitadas){
  for ( int i=0; i < n_arestas_visitadas; ++i)
    if ( ageqedge(a, arestas[i]) )
      return 1;

  return 0;
}

vertice *cria_vertice(Agedge_t *a) {
  vertice *v = (vertice *) malloc(sizeof(vertice));
  v->vizinho = NULL;
  v->nome = (char *) malloc(sizeof(char)*32);
  strcpy(v->nome, (char *) agnameof(agtail(a)));

  char *peso = agget(a, (char *)"peso");
  if ( peso && *peso ) {
    v->peso = (double *) malloc(sizeof(double));
    v->peso[0] = atof(agget(a, (char *)"peso"));
    if (v->peso == NULL)
      v->n = 0;
    else
      v->n = 1;
  }
  else {
    v->peso = NULL;
    v->n = 0;
  }

  return v;
}

vertice *insere_vertice(vertice *g, vertice *v) {
  if (g->vizinho == NULL) {
    g->vizinho = v;
  }
  else {
    insere_vertice(g->vizinho, v);
  }

  return v;
}

// lê um grafo no formato dot de input, usando as rotinas de libcgraph
// desconsidera todos os atributos do grafo lido
// exceto o atributo "peso" nas arestas onde ocorra
// num grafo com pesos nas arestas todas as arestas tem peso, que é um double
// o peso default de uma aresta num grafo com pesos é 0.0
// devolve o grafo lido ou
//     NULL em caso de erro
// TODO tratamento de erro
grafo le_grafo(FILE *input) {
  Agraph_t *g = agread(input, NULL);
  if ( !g )
    return NULL;

  // Cria grafo
  grafo grf = malloc(sizeof(grafo));
  grf->direcionado = agisdirected(g);
  grf->nos = NULL;

  // Cria vetor de vértices
  int n_vertices = agnnodes(g);
  grf->nos = (vertice*)
    malloc((sizeof(vertice)*(long unsigned int)n_vertices));


  // Percorre vértices para encontrar as arestas ou arcos relacionados
  vertice *vrtc = grf->nos;
  for (Agnode_t *v=agfstnode(g); v; v=agnxtnode(g,v)) {
    vrtc->nome = (char *) malloc(sizeof(char)*32);
    strcpy( vrtc->nome, agnameof(v) );
    vrtc->n = 0;

    if (grf->direcionado) {
      // Guarda arcos
      for (Agedge_t *a=agfstout(g,v); a; a=agnxtout(g,a)) {
        vertice *aux = cria_vertice(a);
        insere_vertice(grf->nos, aux);
      }
    }
    else {
      // Guarda arestas
      for (Agedge_t *a=agfstedge(g,v); a; a=agnxtedge(g,a,v)) {
        // A comparação comentada a seguir retira a redundância do
        // armazenamento.
        //if (!strcmp(vrtc->nome, agnameof(agtail(a))))

        // Inserção de vértice
        vertice *aux = cria_vertice(a);
        insere_vertice(grf->nos, aux);
      }

      vrtc++;
    }
  }

  //for (int i=0; i<n_vertices; i++) {
  //  printf("%s\n", grf->nos[i].nome);
  //}

  // Cria listas de arestas
  int n_arestas = agnedges(g);

  return grf;
}

// desaloca toda a memória utilizada em g
// devolve 1 em caso de sucesso ou
//     0 em caso de erro

int destroi_grafo(grafo g) {

}

// escreve o grafo g em output usando o formato dot, de forma que
// 1. todos os vértices são escritos antes de todas as arestas/arcos
// 2. se uma aresta tem peso, este deve ser escrito como um atributo
// devolve o grafo escrito ou
//     NULL em caso de erro

grafo escreve_grafo(FILE *output, grafo g) {

}
