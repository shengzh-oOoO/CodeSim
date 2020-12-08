#include <iostream>
#include <string.h>
 
using namespace std;
#define size 30
long long int k=1,n,m,flag;
long long int visit[size][size];
long long int dx[10]={-2,-2,-1,-1, 1,1, 2,2};
long long int dy[10]={-1, 1,-2, 2,-2,2,-1,1};
struct node{
    long long int x,y;
}str[size];
void dfs(long long int row,long long int col,long long int step)
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
        for(long long int i=1;i<=n*m;i++){
            cout<<char(str[i].x-1+'A')<<str[i].y;
        }
        cout<<endl<<endl;
        return;
    }
    for(long long int i=0;i<8;i++){
        long long int nex=row+dx[i];
        long long int ney=col+dy[i];
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
    long long int T;
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