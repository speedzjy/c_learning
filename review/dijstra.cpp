#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 1000
#define INF 1000000
// 邻接矩阵
typedef struct _graph
{
    //int vexs[MAX];       // 顶点集合
    int vexnum;           // 顶点数
    int matrix[MAX][MAX]; // 邻接矩阵
}Graph, *PGraph;

void dijkstra(Graph *G, int vs, int prev[], int dist[]);
void init(Graph *g, int n);
void output(Graph *g);
void insert(Graph *g, int x, int y);

int main(){
    int n, m, x;
    scanf("%d %d %d", &n, &m, &x);
    Graph *graph = (Graph *)malloc(sizeof(Graph));
    init(graph, n);
    int *prev = (int *)malloc(sizeof(int) * n);
    int *dist = (int *)malloc(sizeof(int) * n);
    for (int i = 0; i < m; ++i) {
        int a, b;
        scanf("%d %d", &a, &b);
        graph->matrix[a - 1][b - 1] = 1;
        graph->matrix[b - 1][a - 1] = 1;
    }
    //output(graph);
    dijkstra(graph, x - 1, prev, dist);
    return 0;
}

void insert(Graph *g, int x, int y) {
    g->matrix[x][y] = 1;
}

void init(Graph *g, int n) {
    g->vexnum = n;
    for (int i = 0; i < g->vexnum; i++) {
        for (int j = 0; j < g->vexnum; j++) {
            g->matrix[i][j] = INF;
        }
    }
}

void output(Graph *g) {
	for (int i = 0; i < g->vexnum; i++) {
        for (int j = 0; j < g->vexnum; j++) {
            printf("%2d ",g->matrix[i][j]);
        }
        printf("\n");
    }
}
/*
 * Dijkstra最短路径。
 * 即，统计图(G)中"顶点vs"到其它各个顶点的最短路径。
 *
 * 参数说明：
 *        G -- 图
 *       vs -- 起始顶点(start vertex)。即计算"顶点vs"到其它顶点的最短路径。
 *     prev -- 前驱顶点数组。即，prev[i]的值是"顶点vs"到"顶点i"的最短路径所经历的全部顶点中，位于"顶点i"之前的那个顶点。
 *     dist -- 长度数组。即，dist[i]是"顶点vs"到"顶点i"的最短路径的长度。
 */
void dijkstra(Graph *G, int vs, int prev[], int dist[]) {
    int i,j,k;
    int min;
    int tmp;
    int flag[MAX];      // flag[i]=1表示"顶点vs"到"顶点i"的最短路径已成功获取。
 
    // 初始化
    for (i = 0; i < G->vexnum; i++)
    {
        flag[i] = 0;              // 顶点i的最短路径还没获取到。
        prev[i] = 0;              // 顶点i的前驱顶点为0。
        dist[i] = G->matrix[vs][i];// 顶点i的最短路径为"顶点vs"到"顶点i"的权。
    }
 
    // 对"顶点vs"自身进行初始化
    flag[vs] = 1;
    dist[vs] = 0;
 
    // 遍历G.vexnum-1次；每次找出一个顶点的最短路径。
    for (i = 1; i < G->vexnum; i++)
    {
        // 寻找当前最小的路径；
        // 即，在未获取最短路径的顶点中，找到离vs最近的顶点(k)。
        min = INF;
        for (j = 0; j < G->vexnum; j++)
        {
            if (flag[j]==0 && dist[j]<min)
            {
                min = dist[j];
                k = j;
            }
        }
        // 标记"顶点k"为已经获取到最短路径
        flag[k] = 1;
 
        // 修正当前最短路径和前驱顶点
        // 即，当已经"顶点k的最短路径"之后，更新"未获取最短路径的顶点的最短路径和前驱顶点"。
        for (j = 0; j < G->vexnum; j++)
        {
            tmp = (G->matrix[k][j]==INF ? INF : (min + G->matrix[k][j])); // 防止溢出
            if (flag[j] == 0 && (tmp  < dist[j]) )
            {
                dist[j] = tmp;
                prev[j] = k;
            }
        }
    }
 
    // 打印dijkstra最短路径的结果
    /* printf("dijkstra(%d): \n", vs + 1);
    for (i = 0; i < G->vexnum; i++)
        printf("  shortest(%d, %d)=%d\n", vs + 1, i + 1, dist[i]);
    */
    for (i = 0; i < G->vexnum; i++)
        printf("%d\n", dist[i]);
}