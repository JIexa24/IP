#include "../include/main.h"

int main(int argc, char const *argv[])
{
  srand(time(NULL));
  if (argc < 3) {
    fprintf(stderr, "%s[ERROR]%s\tNot enough arguments!\n", RED, RESET);
    exit(EXIT_FAILURE);
  }

  int graph_choice = atoi(argv[1]);
  int proof_amount = atoi(argv[2]);

  if (graph_choice < 1 || graph_choice > 2) {
    fprintf(stderr, "%s[WARNING]%s\t %sChosen graph doesn't exist. Set default value:%s\t\t\t%s1%s\n", RED, RESET, WHITE, RESET, GREEN, RESET);
    graph_choice = 1;
  }

  if (proof_amount < 1 || proof_amount > 3) {
    fprintf(stderr, "%s[WARNING]%s\t %sCan't request specified amount of proofs. Set default value:%s\t%s3%s\n", RED, RESET, WHITE, RESET, GREEN, RESET);
    proof_amount = 3;
  }

  graph_generation(graph_choice);

  // int vertex_amount = atoi(argv[1]);
  // int edge_amount = atoi(argv[2]);
  //
  // if (vertex_amount > MAXVERTEX) {
  //   fprintf(stderr, "%s[ERROR]%s\tVertexes overflow!\n", RED, RESET);
  //   exit(EXIT_FAILURE);
  // } else if (edge_amount > _MAXEDGE(vertex_amount)) {
  //   fprintf(stderr, "%s[ERROR]%s\tEdges overflow!\n", RED, RESET);
  //   exit(EXIT_FAILURE);
  // } else if (edge_amount > vertex_amount*vertex_amount) {
  //   fprintf(stderr, "%s[ERROR]%s\tAmount of edges must be less than vertexes^2!\n", RED, RESET);
  //   exit(EXIT_FAILURE);
  // }
  //
  // if(graph_generation(vertex_amount, edge_amount)) {
  //   fprintf(stderr, "%s[ERROR]%s\tCan't generate graph with pointed values!\n", RED, RESET);
  //   exit(EXIT_FAILURE);
  // }

  return EXIT_SUCCESS;
}
