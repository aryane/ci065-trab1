#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <graphviz/cgraph.h>
#include "grafo.h"

//struct vert;

typedef struct vertice {
    char nome[32];
    int n;
    struct vertice *vizinhos;
    double *pesos;
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
    char *nome;
    vertice *nos;
};

// lê um grafo no formato dot de input, usando as rotinas de libcgraph
// desconsidera todos os atributos do grafo lido
// exceto o atributo "peso" nas arestas onde ocorra
// num grafo com pesos nas arestas todas as arestas tem peso, que é um double
// o peso default de uma aresta num grafo com pesos é 0.0
// devolve o grafo lido ou
//         NULL em caso de erro
// TODO tratamento de erro
grafo le_grafo(FILE *input) {
    Agraph_t *g = agread(input, NULL);
    if ( !g )
        return NULL;

    grafo grf = malloc(sizeof(grafo));

    // Cria vetor de vértices
    int n_vertices = agnnodes(g);
    grf->nos = (vertice*)
        malloc((sizeof(vertice)*(long unsigned int)n_vertices));

    vertice *vrtc = grf->nos;

    for (Agnode_t *v=agfstnode(g); v; v=agnxtnode(g,v)) {
        strcpy( vrtc->nome, agnameof(v) );
        //printf("%s\n", vrtc->nome);
        vrtc++;
    }

    for (int i=0; i<n_vertices; i++) {
        printf("%s\n", grf->nos[i].nome);
    }


    // Cria listas de arestas
    int n_arestas = agnedges(g);

    return grf;
}

// desaloca toda a memória utilizada em g
// devolve 1 em caso de sucesso ou
//         0 em caso de erro

int destroi_grafo(grafo g) {

}

// escreve o grafo g em output usando o formato dot, de forma que
// 1. todos os vértices são escritos antes de todas as arestas/arcos
// 2. se uma aresta tem peso, este deve ser escrito como um atributo
// devolve o grafo escrito ou
//         NULL em caso de erro

grafo escreve_grafo(FILE *output, grafo g) {

}
