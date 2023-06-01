#include <stdio.h>
#include <limits.h>
#include <math.h>
#include "my_mat.h"

int main(){
    char ch;
   
    while (ch != 'D'){
        scanf("%c",&ch);
        if(ch == 'A'){
            getMat();
        }
        if(ch == 'B'){
            int ans;
            int i;
            int j;
            scanf("%d%d",&i,&j);
            ans = isPath(i,j);
            if(ans == 0)printf("False\n");
            if(ans == 1)printf("True\n");
        }
        if(ch == 'C'){
            int ans;
            int i;
            int j;
            scanf("%d%d",&i,&j);
            ans = shortestPath(i,j);
            printf("%d\n",ans);
        }
     }
       
    return 0;
}


    // case A:
    //     getMat();
    // case B:
    //     int i;
    //     int j;
    //     scanf("%d%d",&i,&j);
    //     isPath(i,j);
    
    // case C:
    //     int i;
    //     int j;
    //     scanf("%d%d",&i,&j);
    //     shortestPath(i,j);
    // case D: