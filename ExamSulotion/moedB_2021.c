#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//Q1
int m()
{
 int x = 20, y = 80%60, i;
 for(i=1; i<20; i++)
    if(x != y);
 printf("%d) x = %d y = %d\n",i, x, y);
 return 0;
}

//Q2_a
int subUpSt(int a[], int len_a){
    int i=0;
    int counter = 1;
    int ans =1;
    while(i<len_a-1){
        if(a[i]<a[i+1]){
            counter++;
        }else{
            if(counter > ans){
                ans = counter;
                counter = 1;
            }
        }
        i++;
    }
    return ans> counter? ans:counter;
}
//Q2_b
void swap(int *a,int *b){
    int t = *a;
    *a = *b;
    *b = t;
}

int del_num(int *a, int len, int del){
    for(int i=0;i<len;i++){
        if(a[i] == del){
            int j = len-1;
            while(j>=0 && j>i && a[j] == del){
                j--;
            }
            if(j>=0 && a[j] != del){
                swap(&a[i],&a[j]);
            }
        }
    }
    int counter = 0;
    for(int i=0;i<len;i++){
        if(a[i] != del)counter++;
    }
    return counter;
}

int del_num2(int *a, int len, int del){
    for(int i=0;i<len-1;i++){
        for(int j=1;j<len; j++){
            if(a[j-1] == del){
                swap(&a[j-1],&a[j]);
            }
        }
    }
    int counter = 0;
    for(int i=0;i<len;i++){
        if(a[i] != del)counter++;
    }
    return counter;
}

//Q3_a
void revrese(char *str){
    for(int i=0;i<strlen(str)/2;i++){
        int len = strlen(str);
        char t = str[i];
        str[i] = str[len-1-i];
        str[len-1-i] = t;
    }
}

//Q3_b
char * changeIndex(char *a,char *b){
    char * ans = (char*)malloc(sizeof(char)*(strlen(a)+strlen(b)));
    if(ans == NULL)return;
    // char ans [(strlen(a)+strlen(b))];
    int i = 0;
    int k = 0;
    int j = 0;
    while(k<strlen(a)&& j<strlen(b)){
        if(i%2 == 0){
            ans[i] = a[k];
            k++;
            i++;
        }else{
            ans[i] = b[j];
            j++;
            i++;
        }
    }
    while(k<strlen(a)){
        ans[i] = a[k];
        i++;
        k++;
    }
    while(j<strlen(b)){
        ans[i] = a[j];
        i++;
        j++;
    }
    return ans;
    free(ans);
}

int main(){
    // m();
    int a[] = {1};
    int b[] = {1,2,4,6,4,5,9,4,7,4};
    printf("%d\n",subUpSt(a,sizeof(a)/sizeof(a[0])));
    printf("%d\n",del_num(b,10,4));
    // del_num(b,10,4);
    for(int i=0;i<10;i++){
        printf("%d",b[i]);
    }
    printf("\n");
    char c[] = "hi shlomo good luck";
    revrese(c);
    int size = strlen(c);
    printf("%s\n",c);
    char d[] = "aceg";
    char e[] = "bdf";
    printf("%s\n",(changeIndex(d,e)));
    // free(changeIndex(d,e));

    return 0;
}