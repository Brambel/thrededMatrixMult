
#include <pthread.h>

void *multMtx(int**, int**, int**, int);
void *addMtx(int**, int**, int);
int** newAry(int);

struct multArgs{
  int** c;
  int** a;
  int** b;
  int n;
  
};

int main()
{
    return 0;
}

void *multMtx(void* param){
	  multArgs* par = (multArgs*) param;
	if(par->n == 1){
	  par->c[1][1]=par->a[1][1] * par->b[1][1];
	}
	else{
	  int ** t = newAry(par->n); //create empty array
	   //multArgs parm1 = {par->c[1][1],par->a[1][1],par->b[1][1], par->n/2};
	    
	  pthread_t m1, m2, m3, m4, m5, m6, m7, m8;
	  //pthread_create(m1, NULL, multMtx, (void*) param1);
	 delete t; 
	}
	
	return 0;
}

void *addMtx(int** a, int** b, int n) {

	return 0;
}

int** newAry(int n){
  int** temp = new int*[n];
  for(int i=0;i<n;++i){
   temp[i]=new int[n]; 
  }
}
