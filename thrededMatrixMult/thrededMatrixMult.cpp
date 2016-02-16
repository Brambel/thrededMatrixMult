
#include <pthread.h>

int ** addMtx(int**, int**, int**, int);
int** multMtx(int**, int**, int);
int** newAry(int);

int main()
{
    return 0;
}

int** addMtx(int** c, int** a, int** b, int n){
	if(n == 1){
	  c[1][1]=a[1][1] * b[1][1];
	}
	else{
	  int ** t = newAry(n);
	  
	 delete t; 
	}
	
	return 0;
}

int** multMtx(int** a, int** b, int n) {

	return 0;
}

int** newAry(int n){
  int** temp = new int*[n];
  for(int i=0;i<n;++i){
   temp[i]=new int[n]; 
  }
}
