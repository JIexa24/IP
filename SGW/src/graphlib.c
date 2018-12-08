#include "../include/graphlib.h"

void graph_save_graphviz(int vertex_amount, int edge_amount) {
  FILE* graph_file;
  char* filename = "graph.dot";
  char* out = "graph.png";
  char cmd[256] = "dot -Tpng ";
  graph_file = fopen(filename,"w+");
  if (graph_file == NULL) {
    fprintf(stderr,"%s[ERROR]%s\tCan't open file:\t<%s>\n", RED, RESET, filename);
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
static int flag_two_vertex = 0;
int vertex_check_connection(struct EDGE generated_edge, int vertex_amount)
{ 
  int c = 0;
  int i = 0;
  count_disconnect_vertex = 0;
 // printf("chk %d-%d\n", generated_edge.l_vertex->number,generated_edge.r_vertex->number);
 // return 0;
  if (connect_vertex[generated_edge.l_vertex->number - 1] == 0){
    c |= 0x1;
//    connect_vertex[generated_edge.l_vertex->number - 1] = 1;
  }

  if (connect_vertex[generated_edge.r_vertex->number - 1] == 0){
    c |= 0x2;
//    connect_vertex[generated_edge.r_vertex->number - 1] = 1;
  }
//  printf("%d %d\n",c, flag_two_vertex);
  for (i = 0; i < vertex_amount; ++i)
    if (connect_vertex[i] == 0)
      ++count_disconnect_vertex;
  if (c == 0x3) {
    if (flag_two_vertex == 0) flag_two_vertex = 1;
    else {  printf("return 2!!!!!\n");return 2;}
  }
  if (c == 0x0 && count_disconnect_vertex > 0)
    return 1;
  if ((c & 0x1) > 0) connect_vertex[generated_edge.l_vertex->number - 1] = 1;
  if ((c & 0x2) > 0) connect_vertex[generated_edge.r_vertex->number - 1] = 1;
  return 0;
}

int vertex_check_connection_s(int curr_v, int edge_amount, int vertex_amount)
{ 
  int i = 0;
  count_disconnect_vertex = 0;
  for (i = 0; i < edge_amount; ++i) {
    if (GRAPH.g_edge[i].l_vertex->number == GRAPH.g_vertex[curr_v].number) {
      connect_vertex[GRAPH.g_edge[i].l_vertex->number - 1] = 1;
      connect_vertex[GRAPH.g_edge[i].r_vertex->number - 1] = 1;
      vertex_check_connection_s(GRAPH.g_edge[i].r_vertex->number - 1, edge_amount, vertex_amount);
    }
  }
  for (i = 0; i < vertex_amount; ++i) {
    if (connect_vertex[i] == 0)
      ++count_disconnect_vertex;
  }
  return count_disconnect_vertex;
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
      
    } while(edge_uniqueness(i) || (GRAPH.g_edge[i].l_vertex->number == GRAPH.g_edge[i].r_vertex->number) || (vertex_check_connection(GRAPH.g_edge[i], vertex_amount) > 0));


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

int init_check_connect(int vertex_amount)
{
  count_disconnect_vertex = vertex_amount;
  connect_vertex = (int*)malloc(vertex_amount * sizeof(int));
  for (int i = 0; i < vertex_amount; ++i) {
    connect_vertex[i] = 0;
  } 

  return 0;
}

void graph_samples(int graph_choice, int* vertex_amount, int* edge_amount)
{
  switch (graph_choice) {
    case 1:
      *vertex_amount = 5;
      *edge_amount = 4;
      init_check_connect(*vertex_amount);
      init_graph(*edge_amount, *vertex_amount);
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
      init_check_connect(*vertex_amount);
      init_graph(*edge_amount, *vertex_amount);
      edge_generation(*vertex_amount, *edge_amount);
      graph_sort(*edge_amount);
      for (int i = 0; i < *edge_amount; ++i) {
        printf("%sEDGE #%d:%s\t%s%d--%d%s\n", YELLOW, i, RESET, WHITE,GRAPH.g_edge[i].l_vertex->number, GRAPH.g_edge[i].r_vertex->number, RESET);
      }
      return;
    case 3:
      *vertex_amount = 10;
      *edge_amount = 15;
      init_check_connect(*vertex_amount);
      read_graph(edge_amount, vertex_amount, "graph.txt");
      graph_sort(*edge_amount);
      for (int i = 0; i < *edge_amount; ++i) {
        printf("%sEDGE #%d:%s\t%s%d--%d%s\n", YELLOW, i, RESET, WHITE,GRAPH.g_edge[i].l_vertex->number, GRAPH.g_edge[i].r_vertex->number, RESET);
      }
      return;
  }
}

void read_graph(int* edge_amount, int* vertex_amount, char* filename) {
  FILE* graph_file;
  graph_file = fopen(filename,"r");
  int _vertex_amount = 0; 
  int _edge_amount = 0;
  int l = 0;
  int r = 0;
  int i = 0;
  if (graph_file == NULL) {
    fprintf(stderr,"%s[ERROR]%s\tCan't open file:\t<%s>\n", RED, RESET, filename);
    exit(EXIT_FAILURE);
  }
  fscanf(graph_file, "%d", &_vertex_amount);
  fscanf(graph_file, "%d", &_edge_amount);
  if (_vertex_amount > MAXVERTEX) {
    fprintf(stderr, "%s[ERROR]%s\tVertexes overflow!\n", RED, RESET);
    exit(EXIT_FAILURE);
  } else if (_edge_amount > _MAXEDGE(_vertex_amount)) {
    fprintf(stderr, "%s[ERROR]%s\tEdges overflow!\n", RED, RESET);
    exit(EXIT_FAILURE);
  } else if (_edge_amount > _vertex_amount*_vertex_amount) {
    fprintf(stderr, "%s[ERROR]%s\tAmount of edges must be less than vertexes^2!\n", RED, RESET);
    exit(EXIT_FAILURE);
  }
  init_graph(_edge_amount, _vertex_amount);
  for (i = 0; i < _edge_amount; ++i) {

    fscanf(graph_file, "%d", &l);
    fscanf(graph_file, "%d", &r);
    GRAPH.g_edge[i].l_vertex = &GRAPH.g_vertex[search_vertex(l, _vertex_amount)];
    GRAPH.g_edge[i].r_vertex = &GRAPH.g_vertex[search_vertex(r, _vertex_amount)]; 

    if(edge_uniqueness(i) || (GRAPH.g_edge[i].l_vertex->number == GRAPH.g_edge[i].r_vertex->number)) {
      fprintf(stderr,"%s[ERROR]%s\tEdge %d -- %d\n", RED, RESET, l,r);
      exit(EXIT_FAILURE);
    }
  }
     
  if (vertex_check_connection_s(0, _edge_amount, _vertex_amount) == 1) {
    printf("%s[ERROR]%s:\t GRAPH is invalid!\n", RED, RESET);
    exit(EXIT_FAILURE);
  }
  *vertex_amount = _vertex_amount;
  *edge_amount = _edge_amount;
}

int search_vertex(int v, int vertex_amount) {
int i = 0;
  for (i = 0; i < vertex_amount; ++i) {
    if (GRAPH.g_vertex[i].number == v)
      return i;
  }
  fprintf(stderr,"%s[ERROR]%s\tVertex %d not found!\n", RED, RESET, v);
  exit(EXIT_FAILURE);
}

void init_graph(int edge_amount, int vertex_amount) {
  int i = 0;
  for (i = 0; i < edge_amount; ++i) {
    GRAPH.g_edge[i].l_vertex = NULL;
    GRAPH.g_edge[i].r_vertex = NULL;
  }
  for (i = 0; i < vertex_amount; ++i) {
    GRAPH.g_vertex[i].number = i + 1;
    GRAPH.g_vertex[i].gcolor[0] = '\0';
    GRAPH.g_vertex[i].color = 3;//black
  }
}

static int count_not_colored_vertex = 0;
static int* colored_vertex = NULL;
int init_color(int vertex_amount)
{
  count_not_colored_vertex = vertex_amount;
  colored_vertex = (int*)malloc(vertex_amount * sizeof(int));
  for (int i = 0; i < vertex_amount; ++i) {
    colored_vertex[i] = 0;
  } 

  return 0;
}
char* color_array[4] = {RED, GREEN, BLUE, RESET};
int graph_coloring(int vertex_amount,int edge_amount, int cur_vertex)
{
  int i = 0;
  int j = 0;
  int color_mask = 0x7; // 111
  count_disconnect_vertex = 0;
  int error = 0;
  int result_coloring = 1;
  for (i = cur_vertex; i < vertex_amount; ++i) {
    color_mask = 0x7;
    for (j = 0; j < edge_amount; ++j) { 
      if (GRAPH.g_edge[j].l_vertex->number == GRAPH.g_vertex[i].number) {
        if (GRAPH.g_edge[j].r_vertex->color == 0) { // red
          color_mask = color_mask & 0x6;
        } else if (GRAPH.g_edge[j].r_vertex->color == 1) { // green
          color_mask = color_mask & 0x5;
        } else if (GRAPH.g_edge[j].r_vertex->color == 2) { // blue
          color_mask = color_mask & 0x3;
        } else { // black
          color_mask = color_mask & 0x7;
        }
      }
      if (GRAPH.g_edge[j].r_vertex->number == GRAPH.g_vertex[i].number) {
        if (GRAPH.g_edge[j].l_vertex->color == 0) { // red
          color_mask = color_mask & 0x6;
        } else if (GRAPH.g_edge[j].l_vertex->color == 1) { // green
          color_mask = color_mask & 0x5;
        } else if (GRAPH.g_edge[j].l_vertex->color == 2) { // blue
          color_mask = color_mask & 0x3;
        } else { // black
          color_mask = color_mask & 0x7;
        }

      }
    }
    switch(color_mask) {
      case 0x1: // 001
        GRAPH.g_vertex[i].color = 0;
      break;

      case 0x2: // 010
        GRAPH.g_vertex[i].color = 1;
      break;

      case 0x4: // 100
        GRAPH.g_vertex[i].color = 2;
      break;

      case 0x3: // 011
        GRAPH.g_vertex[i].color = 0;
        result_coloring &= graph_coloring(vertex_amount,  edge_amount, i + 1);
        if (!result_coloring)  break;
        GRAPH.g_vertex[i].color = 1;
        result_coloring &= graph_coloring(vertex_amount,  edge_amount, i + 1);
        if (!result_coloring)  break;
        error = error | 1;
      break;

      case 0x5: // 101
        GRAPH.g_vertex[i].color = 0;
        result_coloring &= graph_coloring(vertex_amount,  edge_amount, i + 1);
        if (!result_coloring) break;
        GRAPH.g_vertex[i].color = 2;
        result_coloring &= graph_coloring(vertex_amount,  edge_amount, i + 1);
        if (!result_coloring) break;
        error = error | 1;
      break;

      case 0x6: // 110
        GRAPH.g_vertex[i].color = 1;
        result_coloring &= graph_coloring(vertex_amount,  edge_amount, i + 1);
        if (!result_coloring) break;
        GRAPH.g_vertex[i].color = 2;
        result_coloring &= graph_coloring(vertex_amount,  edge_amount, i + 1);
        if (!result_coloring) break;
        error = error | 1;
      break;

      case 0x7: // 111
        GRAPH.g_vertex[i].color = 0;
        result_coloring &= graph_coloring(vertex_amount,  edge_amount, i + 1);
        if (!result_coloring) break;
        GRAPH.g_vertex[i].color = 1;
        result_coloring &= graph_coloring(vertex_amount,  edge_amount, i + 1);
        if (!result_coloring) break;
        GRAPH.g_vertex[i].color = 2;
        result_coloring &= graph_coloring(vertex_amount,  edge_amount, i + 1);
        if (!result_coloring) break;
        error = error | 1;
      break;
      default: error = error | 1; break;
    }
    if (GRAPH.g_vertex[i].color == 0) {
      strcpy(GRAPH.g_vertex[i].gcolor, "red");
    } else if (GRAPH.g_vertex[i].color == 1) {
      strcpy(GRAPH.g_vertex[i].gcolor, "green");
    } else if (GRAPH.g_vertex[i].color == 2) {
      strcpy(GRAPH.g_vertex[i].gcolor, "blue");
    } else {
      strcpy(GRAPH.g_vertex[i].gcolor, "black");
    }
  }
  return error;
}

void graph_generation(int graph_choice)
{

  int vertex_amount, edge_amount;
  printf("\t%sCOLORLESS GRAPH:%s\n", CYAN, RESET);
  graph_samples(graph_choice, &vertex_amount, &edge_amount);
//  init_color(vertex_amount,edge_amount);
  if (graph_coloring(vertex_amount,edge_amount, 0) == 1) {
    printf("%s[ERROR]%s:\t GRAPH is invalid!\n", RED, RESET);
    graph_save(vertex_amount, edge_amount);
    exit(EXIT_FAILURE);
  }

  printf("\t%sCOLORLED GRAPH:%s\n", CYAN, RESET);
  for (int i = 0; i < edge_amount; ++i) {
    printf("%sEDGE #%d:%s\t%s%d%s--%s%d%s\n", YELLOW, i, RESET, color_array[GRAPH.g_edge[i].l_vertex->color], GRAPH.g_edge[i].l_vertex->number, RESET,  color_array[GRAPH.g_edge[i].r_vertex->color], GRAPH.g_edge[i].r_vertex->number, RESET);
  }
  graph_save(vertex_amount, edge_amount);
}
