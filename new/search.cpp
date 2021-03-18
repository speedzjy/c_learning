#include<iostream>
#include<stack>
#include<queue>

using namespace std;

typedef char vertextype;
typedef int edgetype;

#define MAXVEX 100       // 最大顶点数
#define IFINITY 65535    // 无穷

/************************无向图的邻接矩阵表示法**************************/

typedef struct {
    vertextype vexs[MAXVEX];        // 顶点表
    edgetype arc[MAXVEX][MAXVEX];   // 边表，邻接矩阵
    int num_vexs, num_edges;        // 顶点数和边数
}MGraph;

/************************无向图的邻接表表示法**************************/

typedef struct EdgeNode {       // 边表结点
    int adjvex;                 // 邻接点域
    edgetype weight;            // 权值域
    struct EdgeNode *next;      // 链域，指向下一个节点
}EdgeNode;

typedef struct VertexNode {     // 顶点表结点
    vertextype data;            // 顶点域，存储顶点信息
    EdgeNode *firstedge;        // 边表头指针
}VertexNode, AdjList[MAXVEX];

typedef struct {
    AdjList adjList;
    int num_vexs, num_edges;    // 图中当前顶点和边界
}GraphAdjList;

/*********************************************************************/

/***************深度优先搜索(DFS)*****************************/

bool visited[MAXVEX];

// 邻接矩阵
void DFS(MGraph *G, int i) {     // 在图 G 中以 i 为起点进行DFS
    visited[i] = true;
    for(int j = 0; j < G->num_vexs; j++) {
        if (G->arc[i][j] == 1 && !visited[j])
            DFS(G, j);
    }
    return ;
}

// 邻接表
void DFS_GL(GraphAdjList *GL, int i) {
    visited[i] = true;
    EdgeNode *p;
    p = GL->adjList[i].firstedge;    // p置为当前结点边表头指针
    while (p) {
        if (!visited[p->adjvex]) 
            DFS_GL(GL, p->adjvex);
        p = p->next;
    }
    return ;
}

/***************************************************************************/

/***************广度优先搜索(BFS)*****************************/
// 邻接矩阵
void BFS(MGraph *G) {
    queue<int> q;
    for (int i = 0; i < G->num_vexs; i++) {
        if (!visited[i]) {
            visited[i] = true;
            q.push(i);
            while (!q.empty()) {
                int j = q.front();
                q.pop();
                for (int k = 0; k < G->num_vexs; k++) {
                    if (G->arc[j][k] == 1 && !visited[k]) {
                        visited[k] = true;
                        q.push(k);
                    }
                }
            }
        }
    }
    return ;
}

// 邻接表
void BFS_GL(GraphAdjList *GL) {
    queue<int> q;
    EdgeNode *p;
    for (int i = 0; i < GL->num_vexs; i++) {
        if (!visited[i]) {
            visited[i] = true;
            q.push(i);
            while (!q.empty()) {
                int j = q.front();
                q.pop();
                p = GL->adjList[i].firstedge;
                while (p) {
                    if (!visited[p->adjvex]) {
                        visited[p->adjvex] = true;
                        q.push(p->adjvex);
                    }
                    p = p->next;
                }
            }
        }
    }
}
















