#include "../include/main.h"

int main(int argc, char const *argv[])
{
  if (argc < 3) {
    fprintf(stderr, "%s[ERROR]%s\tNot enough arguments!\n", RED, RESET);
    exit(EXIT_FAILURE);
  }

  int vertex_amount = atoi(argv[1]);
  int edge_amount = atoi(argv[2]);

  if (vertex_amount > MAXVERTEX) {
    fprintf(stderr, "%s[ERROR]%s\tVertexes overflow!\n", RED, RESET);
    exit(EXIT_FAILURE);
  } else if (edge_amount > MAXEDGE) {
    fprintf(stderr, "%s[ERROR]%s\tEdges overflow!\n", RED, RESET);
    exit(EXIT_FAILURE);
  } else if (edge_amount > vertex_amount*vertex_amount) {
    fprintf(stderr, "%s[ERROR]%s\tAmount of edges must be less than vertexes^2!\n", RED, RESET);
    exit(EXIT_FAILURE);
  }

  if(graph_generation(vertex_amount, edge_amount)) {
    fprintf(stderr, "%s[ERROR]%s\tCan't generate graph with pointed values!\n", RED, RESET);
    exit(EXIT_FAILURE);
  }

  return EXIT_SUCCESS;
}
