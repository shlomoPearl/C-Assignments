#include <stdio.h>
#include <limits.h>
#include <math.h>
#include "my_mat.h"

int mat [10][10];

void getMat(){
    for(int i=0;i<10;i++){
	    for(int j=0;j<10;j++){
		    mat[i][j]= 0;
	    }
    }
    
    for(int i=0;i<10;i++){
        for(int j=0;j<10;j++){
            scanf("%d", &mat[i][j]);
        }
    }
    
}

int isPath(int i, int j){
    if(shortestPath(i,j)!=-1)return True;
    return False;
    
}

int min(int a,int b){
    if(a<b)return a;
    return b;
}

int shortestPath(int i, int j){
    if(i==j)return -1;
    int tmp[10][10];
    for(int i=0; i<10;i++){
        for(int j=0;j<10;j++){
            tmp[i][j]=mat[i][j];
        }
    }
    for(int k=0;k<10;k++){
        for(int i=0;i<10;i++){
            for(int j=0;j<10;j++){
                if(tmp[i][j]==0){
					if(tmp[i][k] == 0 || tmp[k][j] == 0){
						continue;
					}else{
						  tmp[i][j] = tmp[i][k] + tmp[k][j];
					}
				}else{
					if(tmp[i][k] == 0 || tmp[k][j] == 0){
						continue;
					}else{
						tmp[i][j] = min( tmp[i][j] , tmp[i][k] + tmp[k][j] );
					}
				}
            }
        }
    }
    if(tmp[i][j] == 0 )return -1;
    return tmp[i][j];
}

