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
#define MAXEDGE MAXVERTEX*MAXVERTEX

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

void graph_save(int vertex_amount, int edge_amount);
int edge_uniqueness(int vertex_amount, int edge_amount);
int edge_generation(int vertex_amount, int edge_amount);
int graph_generation(int vertex_amount, int edge_amount);

#endif
