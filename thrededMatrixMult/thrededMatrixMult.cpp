

#include <pthread.h>
#include <iostream>

struct multArgs{
  int** c;
  int** a;
  int** b;
  int n;
};

struct subArys{
  int** ary11;
  int** ary12;
  int** ary21;
  int** ary22;
  int n;  
};

void *multMtx(int**, int**, int**, int);
void *addMtx(int**, int**, int);
int** newAry(int);
subArys* split(int**, int);

void testSplit(int);

using namespace std;

int main()
{
  testSplit(8);
  
  
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
  return temp;
}

subArys* split(int** ary, int n){
 subArys* temp = new subArys;
 
 temp->ary11 = newAry(n/2);
 temp->ary12 = newAry(n/2);
 temp->ary21 = newAry(n/2);
 temp->ary22 = newAry(n/2);
 temp->n = n/2;
 int shift=n/2;
 for(int i=0;i<n;++i){
   for(int j=0;j<n;++j){
     if(i<n/2){
	if(j<n/2){
	  temp->ary11[i][j]=ary[i][j];
	}
	else{
	  temp->ary12[i][j%shift]=ary[i][j];
	}
     }
     else{
       if(j<n/2){
	  temp->ary21[i%shift][j]=ary[i][j];
	}
	else{
	  temp->ary22[i%shift][j%shift]=ary[i][j];
	}
     }
   }
 }
   return temp;
}

void testSplit(int n){
  int** ptr=newAry(n);
  
  cout<<"parent matrix to be split\n";
  for(int i=0;i<n;++i){
    for(int j=0;j<n;++j){
      ptr[i][j]=(i*10)+j+1;
      cout<<ptr[i][j]<<" ";
    }
    cout<<endl;
  }
  cout<<endl;
  
  subArys* test=split(ptr, n);
  n=test->n;
  
  cout<<"top left quad, ary11\n";
  for(int i=0;i<n;++i){
    for(int j=0;j<n;++j){
      ptr[i][j]=(i*10)+j+1;
      cout<<test->ary11[i][j]<<" ";
    }
    cout<<endl;
  }
  
  cout<<"top right quad, ary12\n";
  for(int i=0;i<n;++i){
    for(int j=0;j<n;++j){
      ptr[i][j]=(i*10)+j+1;
      cout<<test->ary12[i][j]<<" ";
    }
    cout<<endl;
  }
  
  cout<<"bottom left quad, ary21\n";
  for(int i=0;i<n;++i){
    for(int j=0;j<n;++j){
      ptr[i][j]=(i*10)+j+1;
      cout<<test->ary21[i][j]<<" ";
    }
    cout<<endl;
  }
  
  cout<<"bottom left quad, ary22\n";
  for(int i=0;i<n;++i){
    for(int j=0;j<n;++j){
      ptr[i][j]=(i*10)+j+1;
      cout<<test->ary22[i][j]<<" ";
    }
    cout<<endl;
  }
}
