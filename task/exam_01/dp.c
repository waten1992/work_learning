#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <stdint.h>

int 
main(){
    freopen("data.in", "r", stdin);
    freopen("data.out", "w", stdout);
    uint32_t Num, Total_Weight, Cur_Weight = 0, Cur_Value = 0;

    while(scanf("%d %d", &Num, &Total_Weight) != EOF){
		
        uint32_t * dir = (uint32_t*)malloc((Total_Weight+1)*sizeof(uint32_t));
        memset(dir, 0, (Total_Weight+1)*sizeof(uint32_t));
        
        for(int i = 0; i <= Num; ++i) {
            if (i > 0) {
			   scanf("%d %d", &Cur_Weight, &Cur_Value);
			}
            
			for(int j = Total_Weight; j >= 0; --j) {
                if(j >= Cur_Weight && i > 0) {
					uint32_t head_stat = dir[j-Cur_Weight] + Cur_Value;
					dir[j] =( dir[j] > head_stat) ? dir[j] : head_stat;
					printf("The middle stat %d ,%d \n",j,dir[j]);
				}
            }
        }

        printf("The Best Value is : %d\n", dir[Total_Weight]);
        free(dir);
    }
    fclose(stdin);
    fclose(stdout);
    return 0;
}
