#include <stdio.h>
#include <memory.h>
int mat[30][30], vis[30][30], dis[30][30];//用mat数组储存迷宫状态;用vis数组作访问标记；用dis标记当前位置离起点最短距离
int que[900], l, r, sx, sy, ox, oy;        //用que建立队列，该队列每次进入一个已访问位置
int dx[4] = {-1,0,1,0}, dy[4] = {0,1,0,-1};//数组dx,dy表示当前位置下标向上下左右偏移
char s[30];
int bfs(int x, int y){
    int fron = 0, rear = 0;                //fron表示队首，rear记录队尾
    int d, u = x * r + y;                  //u记录当前位置下标（压缩状态）
    vis[x][y] = 1;
    dis[x][y] = 0;
    que[rear++] = u;			   //起点入队，队尾指针后移
    while(fron < rear){                    //在队列为空之前，一直循环下去，直到完全遍历
        u = que[fron++] ;                  //u替换为当前队列首位元素
        x = u / r;
        y = u % r;                              
        for(d = 0; d < 4; d++){
            int nx = x + dx[d], ny =  y + dy[d];//当前位置偏移
            if(nx >= 0 && nx < l && ny >=0 && ny < r && mat[nx][ny] && !vis[nx][ny]){
                int v = nx * r + ny;        //判断偏移后的当前位置，未访问且为1，则储存位置
                que[rear++] = v;            //当前位置进队
                vis[nx][ny] = 1;
                dis[nx][ny] = dis[x][y] + 1;//当前位置的最短距离比上次最短距离多1
                printf("%d ",dis[nx][ny]);
                if(nx == ox&&ny == oy)//走到终点，则返回终点位置的dis
                    return dis[nx][ny];
            }
        }
    }
    return -1;                              //找不到终点，返回负值
}
int main(){
    int ti, tim_li;
    int i, j;
    while(scanf("%d%d%d", &r, &l, &tim_li) != EOF&&(l||r||tim_li)){
        memset(mat, 0, sizeof(mat));	    //清空迷宫状态及其访问状态
        memset(vis, 0, sizeof(vis));
        for(i = 0; i < l; i++){
            scanf("%s", s);		    //按行输入迷宫地图，按行转化
            for(j = 0; j < r; j++){
                switch(s[j]){
                    case 'S':mat[i][j] = 1;sx = i; sy = j; break;
                    case 'P':mat[i][j] = 1;ox = i; oy = j; break;//注意！倘若公主所在位置不标记为1,永远都找不到公主
                    case '.':mat[i][j] = 1; break;//走得通为1
                    case '*':mat[i][j] = 0; break;//墙壁为0
                }
            }
        }
        ti = bfs(sx, sy);
        if(ti == -1)
        printf("NO\n");
        else
        printf("%s\n", (ti > tim_li ? "NO" : "YES"));
    }
    return 0;
}