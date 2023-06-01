#include <math.h>
#include "NumClass.h"

int myArmstrongRecursive(int a, int num){
	if(a < 10) return (int)pow(a,num);
	int last = a % 10;
	int power = (int)pow(last,num);
	return power  + myArmstrongRecursive(a / 10,num);
}

int isArmstrong(int a){
	int numberOfDigit = (int)log10(a) + 1; // number of digits in a
	if(a == myArmstrongRecursive(a,numberOfDigit)) return true;
	return false;
	
}

  int reverse(int r){
	 int numberOfDigit = (int)log10(r) + 1; // number of digits in pali
     int power = (int)pow(10,numberOfDigit-1);
     int last = r % 10;
     if(numberOfDigit == 1) return r;
	 return last* power + reverse((r - last) / 10);
  }
  
  int isPalindrome(int pali){
	 if( pali == reverse(pali))return true;
	 return false;
	 } 
  
