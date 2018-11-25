#include "../include/graphlib.h"

void graph_save(int vertex_amount, int edge_amount)
{

}

int edge_uniqueness(int vertex_amount, int edge_amount)
{
  for (int i = 0; i < edge_amount; ++i) {
    for (int j = 0; j < edge_amount; ++j) {
      if (GRAPH.g_edge[i].r_vertex == GRAPH.g_edge[j].r_vertex && i != j) {
        return 0;
      }
    }
  }

  return 0;
}

int edge_generation(int vertex_amount, int edge_amount)
{

  for (int i = 0; i < edge_amount; ++i) {
    do {
        GRAPH.g_edge[i].l_vertex = (rand() % vertex_amount) + 1;
        GRAPH.g_edge[i].r_vertex = (rand() % vertex_amount) + 1;
    } while(edge_uniqueness(vertex_amount, edge_amount) && GRAPH.g_edge[i].l_vertex == GRAPH.g_edge[i].r_vertex);

    printf("%sEDGE #%d:%s\t%s%d -- %d%s\n", YELLOW, i, RESET, WHITE, GRAPH.g_edge[i].l_vertex, GRAPH.g_edge[i].r_vertex, RESET);
  }

  return 0;
}

int graph_generation(int vertex_amount, int edge_amount)
{
  // printf("%sMAXVERTICEL:%s\t%d\n", YELLOW, RESET, MAXVERTICEL);
  // printf("%sMAXEDGE:%s\t%d\n", YELLOW, RESET, MAXEDGE);
  for (int i = 0; i < vertex_amount; ++i) {
    GRAPH.g_vertex[i].number = i + 1;
    printf("%sVERTEX #%d:%s\t%s%d%s\n", YELLOW, i, RESET, WHITE, GRAPH.g_vertex[i].number, RESET);
  }
  if(edge_generation(vertex_amount, edge_amount)) {
    fprintf(stderr, "%s[ERROR]%s\tCan't generate edges of the graph!\n", RED, RESET);
  }
  graph_save(vertex_amount, edge_amount);

  return 0;
}
