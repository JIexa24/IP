#include "../include/graphlib.h"

void graph_save_graphviz(int vertex_amount, int edge_amount) {
  FILE* graph_file;
  char* filename = "graph.dot";
  char* out = "graph.png";
  char cmd[256] = "dot -Tpng ";
  graph_file = fopen(filename,"w+");
  if (graph_file == NULL) {
    fprintf(stderr,"%s[ERROR]%s\tCan't open file:\t<%s>\n", RED, RESET, filename);
    fclose (graph_file);
    exit(EXIT_FAILURE);
  }
  fprintf(graph_file, "graph ipgraph {\n");
  // print vertex config
  for (int i = 1; i <= vertex_amount; ++i)
    fprintf(graph_file, "%d [label=\"%d\", color=\"%s\"];\n", i, i, "black"); 

  // print edges
  for (int i = 0; i < edge_amount; ++i)
    fprintf(graph_file, "%d -- %d [label=\"%d_%d\", color=\"%s\"]\n",
                        GRAPH.g_edge[i].l_vertex, GRAPH.g_edge[i].r_vertex, GRAPH.g_edge[i].l_vertex, GRAPH.g_edge[i].r_vertex, "blue"); 

  fprintf(graph_file, "}\n");
  fclose (graph_file);
  strcat(cmd, filename);
  strcat(cmd, " -o ");
  strcat(cmd, out);
  system (cmd);
}

void graph_save(int vertex_amount, int edge_amount)
{
  FILE* graph_file;
  char* filename = "graph.txt";
  graph_file = fopen(filename,"w+");
  if (graph_file == NULL) {
    fprintf(stderr,"%s[ERROR]%s\tCan't open file:\t<%s>\n", RED, RESET, filename);
    fclose (graph_file);
    exit(EXIT_FAILURE);
  }
  fprintf(graph_file, "%d %d\n", vertex_amount, edge_amount);
  for (int i = 0; i < edge_amount; ++i)
    fprintf(graph_file, "%d %d\n", GRAPH.g_edge[i].l_vertex, GRAPH.g_edge[i].r_vertex);

  fclose (graph_file);
  graph_save_graphviz(vertex_amount, edge_amount);
}

void vertex_swap(int* vertex_a, int* vertex_b)
{
  int vertex_buffer = *vertex_a;
  *vertex_a = *vertex_b;
  *vertex_b = vertex_buffer;
}

void edge_swap(int a, int b)
{
  struct EDGE temporal_edge;
  temporal_edge.l_vertex = GRAPH.g_edge[a].l_vertex;
  temporal_edge.r_vertex = GRAPH.g_edge[a].r_vertex;
  GRAPH.g_edge[a].l_vertex = GRAPH.g_edge[b].l_vertex;
  GRAPH.g_edge[a].r_vertex = GRAPH.g_edge[b].r_vertex;
  GRAPH.g_edge[b].l_vertex = temporal_edge.l_vertex;
  GRAPH.g_edge[b].r_vertex = temporal_edge.r_vertex;
}

void graph_sort(int edge_amount)
{
  for (int i = 0; i < edge_amount; ++i)
    if (GRAPH.g_edge[i].l_vertex > GRAPH.g_edge[i].r_vertex)
      vertex_swap(&GRAPH.g_edge[i].l_vertex, &GRAPH.g_edge[i].r_vertex);

  for (int i = 0; i < edge_amount; ++i)
    for (int j = 0; j < edge_amount; ++j)
      if (GRAPH.g_edge[i].l_vertex < GRAPH.g_edge[j].l_vertex)
        edge_swap(i, j);
      else if (GRAPH.g_edge[i].l_vertex == GRAPH.g_edge[j].l_vertex)
        if (GRAPH.g_edge[i].r_vertex < GRAPH.g_edge[j].r_vertex)
          edge_swap(i, j);
}

int edge_uniqueness(int generated_edge)
{
  for (int i = 0; i <= generated_edge; ++i)
    for (int j = i + 1; j <= generated_edge; ++j)
      if (GRAPH.g_edge[i].l_vertex == GRAPH.g_edge[j].l_vertex && GRAPH.g_edge[i].r_vertex == GRAPH.g_edge[j].r_vertex)
        return 1;
      else if (GRAPH.g_edge[i].l_vertex == GRAPH.g_edge[j].r_vertex && GRAPH.g_edge[i].r_vertex == GRAPH.g_edge[j].l_vertex)
        return 1;

  return 0;
}

int edge_generation(int vertex_amount, int edge_amount)
{
  for (int i = 0; i < edge_amount; ++i)
    do {
      GRAPH.g_edge[i].l_vertex = (rand() % vertex_amount) + 1;
      GRAPH.g_edge[i].r_vertex = (rand() % vertex_amount) + 1;
    } while(edge_uniqueness(i) || (GRAPH.g_edge[i].l_vertex == GRAPH.g_edge[i].r_vertex));

  return 0;
}

int graph_generation(int vertex_amount, int edge_amount)
{
  for (int i = 0; i < vertex_amount; ++i)
    GRAPH.g_vertex[i].number = i + 1;

  if(edge_generation(vertex_amount, edge_amount)) {
    fprintf(stderr, "%s[ERROR]%s\tCan't generate edges of the graph!\n", RED, RESET);
    exit(EXIT_FAILURE);
  }

  graph_sort(edge_amount);
  for (int i = 0; i < edge_amount; ++i)
    printf("%sEDGE #%d:%s\t%s%d -- %d%s\n", YELLOW, i, RESET, WHITE, GRAPH.g_edge[i].l_vertex, GRAPH.g_edge[i].r_vertex, RESET);

  graph_save(vertex_amount, edge_amount);

  return 0;
}
