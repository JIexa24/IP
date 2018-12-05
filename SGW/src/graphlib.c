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
  for (int i = 0; i < vertex_amount; ++i)
    fprintf(graph_file, "%d [label=\"%d\", color=\"%s\"];\n", i+1, i+1, GRAPH.g_vertex[i].gcolor); 

  // print edges
  for (int i = 0; i < edge_amount; ++i)
    fprintf(graph_file, "%d -- %d [label=\"%d_%d\", color=\"%s\"]\n",
                        GRAPH.g_edge[i].l_vertex->number, GRAPH.g_edge[i].r_vertex->number, GRAPH.g_edge[i].l_vertex->number, GRAPH.g_edge[i].r_vertex->number, "orange"); 

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
    fclose(graph_file);
    exit(EXIT_FAILURE);
  }
  fprintf(graph_file, "%d %d\n", vertex_amount, edge_amount);
  for (int i = 0; i < edge_amount; ++i)
    fprintf(graph_file, "%d %d\n", GRAPH.g_edge[i].l_vertex->number, GRAPH.g_edge[i].r_vertex->number);

  fclose (graph_file);
  graph_save_graphviz(vertex_amount, edge_amount);
}

void vertex_swap(int position)
{
//  printf("A: %d -- %d\n", GRAPH.g_edge[position].l_vertex->number, GRAPH.g_edge[position].r_vertex->number);
  struct VERTEX* temporal_edge = GRAPH.g_edge[position].l_vertex;
  GRAPH.g_edge[position].l_vertex = GRAPH.g_edge[position].r_vertex;
  GRAPH.g_edge[position].r_vertex = temporal_edge;
//  printf("B:  %d -- %d\n", GRAPH.g_edge[position].l_vertex->number, GRAPH.g_edge[position].r_vertex->number);
}

void edge_swap(int a, int b)
{
  struct VERTEX* temporal_l_vertex;
  struct VERTEX* temporal_r_vertex;
  temporal_l_vertex = GRAPH.g_edge[a].l_vertex;
  temporal_r_vertex = GRAPH.g_edge[a].r_vertex;
  GRAPH.g_edge[a].l_vertex = GRAPH.g_edge[b].l_vertex;
  GRAPH.g_edge[a].r_vertex = GRAPH.g_edge[b].r_vertex;
  GRAPH.g_edge[b].l_vertex = temporal_l_vertex;
  GRAPH.g_edge[b].r_vertex = temporal_r_vertex;
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

static int count_disconnect_vertex = 0;
  
static int* connect_vertex = NULL;
int vertex_check_connection(struct EDGE generated_edge, int vertex_amount)
{ 
  int c = 0;
  int i = 0;
  count_disconnect_vertex = 0;
 // printf("chk %d-%d\n", generated_edge.l_vertex->number,generated_edge.r_vertex->number);
 // return 0;
  if (connect_vertex[generated_edge.l_vertex->number - 1] == 0){
    ++c;
    connect_vertex[generated_edge.l_vertex->number - 1] = 1;
  }

  if (connect_vertex[generated_edge.r_vertex->number - 1] == 0){
    ++c;
    connect_vertex[generated_edge.r_vertex->number - 1] = 1;
  }

  for (i = 0; i < vertex_amount; ++i)
    if (connect_vertex[i] == 0)
      ++count_disconnect_vertex;
  if (c == 0 && count_disconnect_vertex > 0)
    return 1;

  return 0;
}

int edge_generation(int vertex_amount, int edge_amount)
{
  int l;
  int r;
  for (int i = 0; i < edge_amount; ++i)
    do {
      l = (rand() % (vertex_amount));
      r = (rand() % (vertex_amount));

      GRAPH.g_edge[i].l_vertex = &GRAPH.g_vertex[l];
      GRAPH.g_edge[i].r_vertex = &GRAPH.g_vertex[r];
      
    } while(edge_uniqueness(i) || vertex_check_connection(GRAPH.g_edge[i], vertex_amount) || (GRAPH.g_edge[i].l_vertex->number == GRAPH.g_edge[i].r_vertex->number));


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
  count_disconnect_vertex = vertex_amount;
  connect_vertex = (int*)malloc(vertex_amount * sizeof(int));
  for (int i = 0; i < vertex_amount; ++i) {
    connect_vertex[i] = 0;
    GRAPH.g_vertex[i].number = i + 1;
  } 

  return 0;
}

void graph_samples(int graph_choice, int* vertex_amount, int* edge_amount)
{
  switch (graph_choice) {
    case 1:
      *vertex_amount = 5;
      *edge_amount = 4;
     color_uniqueness(*vertex_amount);
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
      color_uniqueness(*vertex_amount);
      edge_generation(*vertex_amount, *edge_amount);
      graph_sort(*edge_amount);
      for (int i = 0; i < *edge_amount; ++i) {
        printf("%sEDGE #%d:%s\t%s%d--%d%s\n", YELLOW, i, RESET, WHITE,GRAPH.g_edge[i].l_vertex->number, GRAPH.g_edge[i].r_vertex->number, RESET);
      }
      return;
  }
}

char* color_array[3] = {RED, GREEN, BLUE};
void graph_coloring(int vertex_amount)
{
  for (int i = 0; i < vertex_amount; ++i) {
    int coloring_epoch = i;
    int generate_color = 0;
    generate_color = coloring_epoch % 3;
    GRAPH.g_vertex[i].color = color_array[generate_color];
    if (generate_color == 0) {
      strcpy(GRAPH.g_vertex[i].gcolor, "red");
    } else if (generate_color == 1) {
      strcpy(GRAPH.g_vertex[i].gcolor, "green");
    } else if (generate_color == 2) {
      strcpy(GRAPH.g_vertex[i].gcolor, "blue");
    } else {
      strcpy(GRAPH.g_vertex[i].gcolor, "black");
    }
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

  graph_coloring(vertex_amount);

  printf("\t%sCOLORLED GRAPH:%s\n", CYAN, RESET);
  for (int i = 0; i < edge_amount; ++i) {
    printf("%sEDGE #%d:%s\t%s%d%s--%s%d%s\n", YELLOW, i, RESET, GRAPH.g_edge[i].l_vertex->color, GRAPH.g_edge[i].l_vertex->number, RESET, GRAPH.g_edge[i].r_vertex->color, GRAPH.g_edge[i].r_vertex->number, RESET);
  }
  graph_save(vertex_amount, edge_amount);
}
