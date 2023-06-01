#include <math.h>
#include "NumClass.h"



  int isArmstrong(int a){
	 int numberOfDigits = (int)log10(a) + 1;
	 int sum=0;
	 for(int i=0;i<numberOfDigits;i++){
		 // t is the i'th digit
		 int t= (a/((int)pow(10,i))%10);
		 sum = sum + (int)pow(t,numberOfDigits);
	 }
	 if(sum == a){
		 return true;
	 }else{
		 return false;
	 } 
  }
  
  int isPalindrome(int pali){
	  int j = (int)log10(pali) + 1; // number of digits in pali
	  int i;
	  for(i=0; i<j/2 ;i++){
		  if((pali/((int)pow(10,i))%10) != (pali/((int)pow(10,j-i-1))%10)){
			  return false;
		  }
	  }
	  return true;  
  }