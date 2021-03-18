#include <stdio.h>
#include <memory.h>
#include <stdlib.h>
#include <stack>
#include <queue>

using namespace std;
int dx[4] = {-1,0,1,0}, dy[4] = {0,1,0,-1};//数组dx,dy表示当前位置下标向上下左右偏移

int bfs(int start_x, int start_y, int high, int width, int aim_x, int aim_y, int vis[][30], int dis[][30], int mat[][30]);

int main(){
    int time;
    int i, j;
    //用mat数组储存迷宫状态;用vis数组作访问标记；用dis标记当前位置离起点最短距离
    int mat[30][30], vis[30][30], dis[30][30];
    int high, width, timeline;
    char s[30];
    int start_x, start_y, aim_x, aim_y;
    scanf("%d %d %d", &high, &width, &timeline);

    memset(mat, 0, sizeof(mat));	    //清空迷宫状态及其访问状态
    memset(vis, 0, sizeof(vis));+
    for(i = 0; i < high; i++){
        scanf("%s", s);		    //按行输入迷宫地图，按行转化
        for(j = 0; j < width; j++){
            switch(s[j]){
                case 'S':mat[i][j] = 1; start_x = i; start_y = j; break;
                case 'P':mat[i][j] = 1; aim_x = i; aim_y = j; break;//注意！倘若公主所在位置不标记为1,永远都找不到公主
                case '.':mat[i][j] = 1; break;//走得通为1
                case '*':mat[i][j] = 0; break;//墙壁为0
            }
        }
    }
    time = bfs(start_x, start_y, high, width, aim_x, aim_y, vis, dis, mat);
    if(time == -1)
        printf("NO\n");
    else
        printf("%s\n", (time > timeline ? "NO" : "YES"));
    return 0;
}

int bfs(int start_x, int start_y,int high, int width, int aim_x, int aim_y, int vis[30][30], int dis[30][30], int mat[30][30]){
    queue<int> q;
    int fron = 0, rear = 0;                //fron表示队首，rear记录队尾
    int d, cur = start_x * width + start_y;                  //u记录当前位置下标（压缩状态）
    vis[start_x][start_y] = 1;
    dis[start_x][start_y] = 0;
    q.push(cur);			   //起点入队，队尾指针后移
    while(!q.empty()){ 
        //在队列为空之前，一直循环下去，直到完全遍历
        cur = q.front() ;
        q.pop();                 //u替换为当前队列首位元素
        start_x = cur / width;
        start_y = cur % width;                       
        for(d = 0; d < 4; d++){
            int nx = start_x + dx[d], ny =  start_y + dy[d];//当前位置偏移
            if(nx >= 0 && nx < high && ny >=0 && ny < width && mat[nx][ny] && !vis[nx][ny]){
                int v = nx * width + ny;        //判断偏移后的当前位置，未访问且为1，则储存位置
                q.push(v);            //当前位置进队
                vis[nx][ny] = 1;
                dis[nx][ny] = dis[start_x][start_y] + 1;//当前位置的最短距离比上次最短距离多1
                //printf("%d ",dis[nx][ny]);
                if(nx == aim_x && ny == aim_y)//走到终点，则返回终点位置的dis
                    return dis[nx][ny];
            }
        }
    }
    return -1;                              //找不到终点，返回负值
}