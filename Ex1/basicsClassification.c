
#include <math.h>
#include "NumClass.h"

int factorial(int s){
	if (s==0){
		return 1;
	}else{
		return s*factorial(s-1);
	}
}

int isPrime(int p){
	if(p==2||p==1){ 
	    return true;
	}else if(p%2==0){
		return false;
	}else{
		for(int i=3; i<=sqrt(p) ;i=i+1){
			if(p%i==0)return false;
		}//for
		return true;
	}
}

int isStrong(int s){
	int numberOfDigits = floor(log10((s))) + 1;
	int sum=0;
	for(int i=0;i<numberOfDigits;i++){
		// t is the i'th digit
        int t= (s/((int)pow(10,i))%10);
		sum=sum+factorial(t);
	}
	if(sum==s){
	    return true;
	}else{
		return false;
	}
	
}



