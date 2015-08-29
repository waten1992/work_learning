#include<cstdio>
#include<cstdlib>
#include<cstring>
using namespace std;

int main(){
    freopen("data.in", "r", stdin);
    freopen("data.out", "w", stdout);
    int n, C, V = 0, W = 0;
    while(scanf("%d %d", &n, &C) != EOF){
        int* d = (int*)malloc((C+1)*sizeof(int));
        memset(d, 0, (C+1)*sizeof(int));
        
        for(int i=0; i<=n; ++i){
            if(i>0)   scanf("%d %d", &V, &W);
            for(int j=C; j>=0; --j){
                if(j>=V && i>0)    d[j] >?= d[j-V]+W;
            }
        }
        printf("%d\n", d[C]);
        free(d);
    }
    fclose(stdin);
    fclose(stdout);
    return 0;
}
