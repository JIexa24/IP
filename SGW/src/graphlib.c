#include "../include/graphlib.h"

void graph_save(int vertex_amount, int edge_amount)
{
  FILE* graph_file;
  char* filename = "graph.txt";
  graph_file = fopen(filename,"w+");
  if (graph_file == NULL) {
    fprintf(stderr,"%s[ERROR]%s\tCan't open file:\t<%s>\n", RED, RESET, filename);
    fclose(graph_file);
    exit(EXIT_FAILURE);
  }
  fprintf(graph_file, "%d %d\n", vertex_amount, edge_amount);
  for (int i = 0; i < edge_amount; ++i)
    fprintf(graph_file, "%d %d\n", GRAPH.g_edge[i].l_vertex->number, GRAPH.g_edge[i].r_vertex->number);

  fclose(graph_file);
}

void vertex_swap(int position)
{
  printf("A: %d -- %d\n", GRAPH.g_edge[position].l_vertex->number, GRAPH.g_edge[position].r_vertex->number);
  struct EDGE temporal_edge = GRAPH.g_edge[position];
  GRAPH.g_edge[position].l_vertex = GRAPH.g_edge[position].r_vertex;
  GRAPH.g_edge[position].r_vertex = temporal_edge.l_vertex;
  printf("B:  %d -- %d\n", GRAPH.g_edge[position].l_vertex->number, GRAPH.g_edge[position].r_vertex->number);
}

void edge_swap(int a, int b)
{
  struct VERTEX temporal_l_vertex;
  struct VERTEX temporal_r_vertex;
  temporal_l_vertex.number = GRAPH.g_edge[a].l_vertex->number;
  temporal_r_vertex.number = GRAPH.g_edge[a].r_vertex->number;
  GRAPH.g_edge[a].l_vertex->number = GRAPH.g_edge[b].l_vertex->number;
  GRAPH.g_edge[a].r_vertex->number = GRAPH.g_edge[b].r_vertex->number;
  GRAPH.g_edge[b].l_vertex->number = temporal_l_vertex.number;
  GRAPH.g_edge[b].r_vertex->number = temporal_r_vertex.number;
}

void graph_sort(int edge_amount)
{
  for (int i = 0; i < edge_amount; ++i)
    if (GRAPH.g_edge[i].l_vertex->number > GRAPH.g_edge[i].r_vertex->number)
      vertex_swap(i);

  for (int i = 0; i < edge_amount; ++i)
    for (int j = 0; j < edge_amount; ++j)
      if (GRAPH.g_edge[i].l_vertex->number < GRAPH.g_edge[j].l_vertex->number)
        edge_swap(i, j);
      else if (GRAPH.g_edge[i].l_vertex->number == GRAPH.g_edge[j].l_vertex->number)
        if (GRAPH.g_edge[i].r_vertex->number < GRAPH.g_edge[j].r_vertex->number)
          edge_swap(i, j);
}

int edge_uniqueness(int generated_edge)
{
  for (int i = 0; i <= generated_edge; ++i)
    for (int j = i + 1; j <= generated_edge; ++j)
      if (GRAPH.g_edge[i].l_vertex->number == GRAPH.g_edge[j].l_vertex->number && GRAPH.g_edge[i].r_vertex->number == GRAPH.g_edge[j].r_vertex->number)
        return 1;
      else if (GRAPH.g_edge[i].l_vertex->number == GRAPH.g_edge[j].r_vertex->number && GRAPH.g_edge[i].r_vertex->number == GRAPH.g_edge[j].l_vertex->number)
        return 1;

  return 0;
}

int edge_generation(int vertex_amount, int edge_amount)
{
  for (int i = 0; i < edge_amount; ++i)
    do {
      GRAPH.g_edge[i].l_vertex = &GRAPH.g_vertex[rand() % vertex_amount];
      GRAPH.g_edge[i].r_vertex = &GRAPH.g_vertex[rand() % vertex_amount];
    } while(edge_uniqueness(i) || (GRAPH.g_edge[i].l_vertex->number == GRAPH.g_edge[i].r_vertex->number));

  return 0;
}

// int graph_generation(int vertex_amount, int edge_amount)
// {
//   for (int i = 0; i < vertex_amount; ++i)
//     GRAPH.g_vertex[i].number = i + 1;
//
//   if(edge_generation(vertex_amount, edge_amount)) {
//     fprintf(stderr, "%s[ERROR]%s\tCan't generate edges of the graph!\n", RED, RESET);
//     exit(EXIT_FAILURE);
//   }
//
//   graph_sort(edge_amount);
//   for (int i = 0; i < edge_amount; ++i)
//     printf("%sEDGE #%d:%s\t%s%d -- %d%s\n", YELLOW, i, RESET, WHITE, GRAPH.g_edge[i].l_vertex->number, GRAPH.g_edge[i].r_vertex->number, RESET);
//
//   graph_save(vertex_amount, edge_amount);
//
//   return 0;
// }

int color_uniqueness(int vertex_amount)
{
//  char* color_array[3] = {RED, GREEN, BLUE};
  for (int i = 0; i < vertex_amount; ++i) {
    for (int j = 0; j < vertex_amount; ++j) {
    }
  }
  return 0;
}

void graph_samples(int graph_choice, int* vertex_amount, int* edge_amount)
{
  switch (graph_choice) {
    case 1:
      *vertex_amount = 5;
      *edge_amount = 4;
      for (int i = 0; i < *vertex_amount; ++i)
        GRAPH.g_vertex[i].number = i + 1;
      for (int j = 0; j < *edge_amount; ++j) {
        GRAPH.g_edge[j].l_vertex = &GRAPH.g_vertex[j];
        GRAPH.g_edge[j].r_vertex = &GRAPH.g_vertex[j + 1];
      }
      for (int i = 0; i < *edge_amount; ++i) {
        printf("%sEDGE #%d:%s\t%s%d--%d%s\n", YELLOW, i, RESET, WHITE,GRAPH.g_edge[i].l_vertex->number, GRAPH.g_edge[i].r_vertex->number, RESET);
      }
      return;
    case 2:
      *vertex_amount = 10;
      *edge_amount = 15;
      for (int i = 0; i < *vertex_amount; ++i)
        GRAPH.g_vertex[i].number = i + 1;
      edge_generation(*vertex_amount, *edge_amount);
      graph_sort(*edge_amount);
      for (int i = 0; i < *edge_amount; ++i) {
        printf("%sEDGE #%d:%s\t%s%d--%d%s\n", YELLOW, i, RESET, WHITE,GRAPH.g_edge[i].l_vertex->number, GRAPH.g_edge[i].r_vertex->number, RESET);
      }
      return;
  }
}

void graph_coloring(int vertex_amount)
{
  char* color_array[3] = {RED, GREEN, BLUE};
  for (int i = 0; i < vertex_amount; ++i) {
    int coloring_epoch = i;
    GRAPH.g_vertex[i].color = color_array[coloring_epoch % 3];
    ++coloring_epoch;
    if (coloring_epoch > 10) {
      fprintf(stderr, "%s[ERROR]%s Can't colorized generated graph with unique colors!\n", RED, RESET);
      return;
    }
  }
}

void graph_generation(int graph_choice)
{
  int vertex_amount, edge_amount;
  printf("\t%sCOLORLESS GRAPH:%s\n", CYAN, RESET);
  graph_samples(graph_choice, &vertex_amount, &edge_amount);

  do {
    graph_coloring(vertex_amount);
  } while(color_uniqueness(vertex_amount));

  printf("\t%sCOLORLED GRAPH:%s\n", CYAN, RESET);
  for (int i = 0; i < edge_amount; ++i) {
    printf("%sEDGE #%d:%s\t%s%d%s--%s%d%s\n", YELLOW, i, RESET, GRAPH.g_edge[i].l_vertex->color, GRAPH.g_edge[i].l_vertex->number, RESET, GRAPH.g_edge[i].r_vertex->color, GRAPH.g_edge[i].r_vertex->number, RESET);
  }
  graph_save(vertex_amount, edge_amount);
}
