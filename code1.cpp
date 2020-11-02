#include <iostream>
#include <string.h>
 
using namespace std;
#define size 30
int k=1,n,m,flag;
int visit[size][size];
int dx[10]={-2,-2,-1,-1, 1,1, 2,2};
int dy[10]={-1, 1,-2, 2,-2,2,-1,1};
struct node{
    int x,y;
}str[size];
void dfs(int row,int col,int step)
{
    if(flag==1){
        return;
    }
    visit[row][col]=1;
    str[step].x=row;
    str[step].y=col;
    if(step==n*m){
        flag=1;
        cout<<"Scenario #"<<k++<<":"<<endl;
        for(int i=1;i<=n*m;i++){
            cout<<char(str[i].x-1+'A')<<str[i].y;
        }
        cout<<endl<<endl;
        return;
    }
    for(int i=0;i<8;i++){
        int nex=row+dx[i];
        int ney=col+dy[i];
        if(nex<=m&&nex>=1
           &&ney<=n&&ney>=1
           &&!visit[nex][ney]){
            dfs(nex,ney,step+1);
        }
    }
    visit[row][col]=0;
}
int main()
{
    int T;
    cin>>T;
    while(T--)
    {
        memset(visit,0,sizeof(visit));
        flag=0;
        cin>>n>>m;
        dfs(1,1,1);
        if(!flag){
            cout<<"Scenario #"<<k++<<":"<<endl;
            cout<<"impossible"<<endl<<endl;
        }
    }
    return 0;
}