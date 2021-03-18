#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 1000

typedef struct Graph {
    int mat[MAX_N][MAX_N];
    int n;
} Graph;

void init(Graph *g, int n) {
    g->n = n;
    memset(g->mat, 0, sizeof(g->mat));
}

void insert(Graph *g, int x, int y) {
	if (x < 0 || x >= g->n || y < 0 || y >= g->n) {
        return ;
    }
    g->mat[x][y] = 1;
}

void output(Graph *g) {
	for (int i = 0; i < g->n; i++) {
        for (int j = 0; j < g->n; j++) {
            printf("%d ",g->mat[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int n, m, x, y;
    scanf("%d %d", &n, &m);
    Graph *graph = (Graph *)malloc(sizeof(Graph));
    init(graph, n);
    for (int i = 0; i < m; ++i) {
        scanf("%d %d", &x, &y);
        insert(graph, x, y);
    }
   // output(graph);
    for (int i = 0; i < graph->n; i++) {
        int count = 0;
        for (int j = 0; j < graph->n; j++) {
            count += graph->mat[i][j];
        }
        int outc = 0;
        for (int j = 0; j < graph->n; j++) {
            outc += graph->mat[j][i];
        }
        printf("%d\n",outc - count);
    }
    free(graph);
    return 0;
}