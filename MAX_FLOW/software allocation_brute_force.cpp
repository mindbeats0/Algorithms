#include <bits/stdc++.h>
using namespace std;

char s[100];
vector<int>tasks;
vector<int>task[300];
bool vis[15];
char ans[15];
bool solve(int idx=0){
    if(idx == tasks.size())return 1;

    char cur_task = tasks[idx];
    for(int i=0;i<task[cur_task].size();i++){
        int computer = task[cur_task][i];
        if(!vis[computer]){
            vis[computer]=1;
            ans[computer] = cur_task;
            if(solve(idx+1))return true;
            vis[computer]=0;
            ans[computer] = 0;
        }
    }

    return false;
}
int main(){

    //freopen("ib.in","r",stdin);

    while(gets(s)){

        tasks.clear();
        memset(task,0,sizeof task);


        for(int i=0;i<(s[1]-'0');i++)tasks.push_back(s[0]);
        for(int i=3;i<strlen(s)-1;i++)task[s[0]].push_back(s[i]-'0');

        while(gets(s)){
            if(strcmp(s,"") == 0)break;

            for(int i=0;i<(s[1]-'0');i++)tasks.push_back(s[0]);
            for(int i=3;i<strlen(s)-1;i++)task[s[0]].push_back(s[i]-'0');
        }




        memset(vis,0,sizeof vis);
        memset(ans,0,sizeof ans);
        if(tasks.size() <= 10 && solve()){
            for(int i=0;i<10;i++){
                if(!ans[i])printf("_");
                else printf("%c",ans[i]);
            }
            printf("\n");
        }
        else printf("!\n");
    }
    return 0;
}
