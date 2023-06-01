#include <stdio.h>
#include "NumClass.h"

int main(){
	int a;
	int b;
	//printf("enter 2 numbers:\n");
	scanf("%d%d",&a,&b);
	printf("The Armstrong numbers are:");
	for(int i=a;i<=b;i++){
		int ans1 = isArmstrong(i);
		if(ans1 !=0){
			printf(" %d",i);
		}
	}
	printf("\n");
	printf("The Palindromes are:");
	for(int i=a;i<=b;i++){
		int ans2 = isPalindrome(i);
		if(ans2 !=0){
			printf(" %d",i);
		}
	}
	printf("\n");
	printf("The Prime numbers are:");
	for(int i=a;i<=b;i++){
		int ans3 = isPrime(i);
		if(ans3 !=0){
			printf(" %d",i);
		}
	}
	printf("\n");
	printf("The Strong numbers are:");
	for(int i=a;i<=b;i++){
		int ans4 = isStrong(i);
		if(ans4 !=0){
			printf(" %d",i);
		}
	}
	printf("\n");
	//printf("\n");
	return 0;
}




