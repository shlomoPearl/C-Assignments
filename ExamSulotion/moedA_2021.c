
#include <stdio.h>
#include <string.h>

#define true 1;
#define false 0;


//Q3-a&b
int mul_elements(int a[], int b[], int len_a, int len_b, int goal){	
    int i=0;
    int j= len_b -1;
	while(j>=0 && i<len_a){
        if(a[i]*b[j] == goal)return true;
        if(a[i]*b[j]<goal)i++;
        else{
            j--;
        }
    }
    return false;
} 


int main(){
    int a [] ={0,1,3,4,8,9,15};
    int b [] ={2,4,5,6,8,12,20};
    printf("%d\n",mul_elements(a,b,7,7,24));
    printf("%d\n",mul_elements(a,b,7,7,9));

  
return 0;
}


