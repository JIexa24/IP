#ifndef GRAPHLIB_H
#define  GRAPHLIB_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <sys/time.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdbool.h>

#include "../include/colorlib.h"
#include "../include/graphlib.h"
#include "../include/extralib.h"
#include "../include/cryptolib.h"
#include "../include/hashtab.h"

#define MAXVERTEX 1000
#define MAXEDGE (((MAXVERTEX - 1)/2) * MAXVERTEX)
#define _MAXEDGE(X) (((X - 1)/2) * X)

struct EDGE {
  int l_vertex;
  int r_vertex;
} EDGE;

struct VERTEX {
  int number;
  char* color;
} VERTEX;

struct GRAPH {
  struct VERTEX g_vertex[MAXVERTEX];
  struct EDGE g_edge[MAXEDGE];
} GRAPH;

int vertex_check_connection(struct EDGE generated_edge, int vertex_amount);
void graph_save_graphviz(int vertex_amount, int edge_amount);
void graph_save(int vertex_amount, int edge_amount);
void graph_sort(int edge_amount);
void edge_swap(int a, int b);
void vertex_swap(int* vertex_a, int* vertex_b);
int edge_uniqueness(int generated_edge);
int edge_generation(int vertex_amount, int edge_amount);
int graph_generation(int vertex_amount, int edge_amount);

#endif
