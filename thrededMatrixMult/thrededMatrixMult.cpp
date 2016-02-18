
#include <pthread.h>
#include <iostream>

struct subArys{
  int** ary11;
  int** ary12;
  int** ary21;
  int** ary22;
  int n;  
};

struct multArgs{
  int** c;
  int** a;
  int** b;
  int n;
  
  public:
    multArgs(int** c_, int** a_, int** b_, int n_){
      c=c_;
      a=a_;
      b=b_;
      n=n_;
    }
};

struct addArgs{
  int**c;
  int**t;
  int n;
  
  public:
    addArgs(int** c_, int** t_, int n_){
      c=c_;
      t=t_;
      n=n_;
    }
};



void *multMtx(void*);
void *addMtx(void*);
int** newAry(int);
subArys* split(int**, int);
void printAry(int**, int);

void testSplit(int);
void testAdd();

using namespace std;

int main(){
  testSplit(4);
  testAdd();
  
    return 0;
}

void *multMtx(void* param){
	  multArgs* par = (multArgs*) param;
	  int ** tt = newAry(par->n); //create empty array
	if(par->n == 1){
	  par->c[0][0] = par->a[0][0] * par->b[0][0];
	  //need to bundle for return here
	}
	else{
	  
	  subArys* a = split(par->a, par->n); //aplit arrays
	  subArys* b = split(par->b, par->n);
	  subArys* c = split(par->c, par->n);
	  subArys* t = split(tt, par->n);
	  //package all params
	  multArgs* param1 = new multArgs(c->ary11, a->ary11, b->ary11, t->n);
	  multArgs* param2 = new multArgs(c->ary12, a->ary11, b->ary12, t->n);
	  multArgs* param3 = new multArgs(c->ary21, a->ary21, b->ary11, t->n);
	  multArgs* param4 = new multArgs(c->ary22, a->ary21, b->ary12, t->n);
	  multArgs* param5 = new multArgs(t->ary11, a->ary12, b->ary22, t->n);
	  multArgs* param6 = new multArgs(t->ary12, a->ary12, b->ary22, t->n);
	  multArgs* param7 = new multArgs(t->ary21, a->ary22, b->ary21, t->n);
	  multArgs* param8 = new multArgs(t->ary22, a->ary22, b->ary22, t->n);
	  pthread_t m1, m2, m3, m4, m5, m6, m7, m8;
	  pthread_create(&m1, NULL, multMtx, (void*) param1);
	  //add and bundle for return here
	}
	
	delete tt;

}

void *addMtx(void* param) {
	addArgs* par = (addArgs*) param;
	
	if(par->n==1){
	  par->c[0][0]+=par->t[0][0];
	  
	}
	else{
	  subArys* c = split(par->c, par->n);
	  subArys* t = split(par->t, par->n);
	  
	  addArgs* param1 = new addArgs(c->ary11, t->ary11, t->n);
	  addArgs* param2 = new addArgs(c->ary12, t->ary12, t->n);
	  addArgs* param3 = new addArgs(c->ary21, t->ary21, t->n);
	  addArgs* param4 = new addArgs(c->ary22, t->ary22, t->n);
	  pthread_t m1,m2, m3, m4;
	  pthread_t threads[4]={m1, m2, m3, m4};
	   
	  pthread_create(&m1, NULL, addMtx, (void*) param1);
	  pthread_create(&m2, NULL, addMtx, (void*) param2);
	  pthread_create(&m3, NULL, addMtx, (void*) param3);
	  pthread_create(&m4, NULL, addMtx, (void*) param4);
	  
	  //thread syntax is all over the place and looks like a toddler threw up in my code
	  pthread_join(m1,NULL);
	  pthread_join(m2,NULL);
	  pthread_join(m3,NULL);
	  pthread_join(m4,NULL);
	}
}

int** newAry(int n){
  int** temp = new int*[n]; //outer array for poitners
  for(int i=0;i<n;++i){
   temp[i]=new int[n]; //inner 1d arrays of int*
   for(int j=0;j<n;++j){
     temp[i][j]= 0;
   }
  }
  return temp;
}

subArys* split(int** ary, int n){
 subArys* temp = new subArys;
 
 temp->ary11 = newAry(n/2); //define all initial vals
 temp->ary12 = newAry(n/2);
 temp->ary21 = newAry(n/2);
 temp->ary22 = newAry(n/2);
 temp->n = n/2;
 int shift=n/2;
 
 for(int i=0;i<n;++i){ //loop through original and push to correct quad

   if(i<n/2){
     temp->ary11[i]=&ary[i][0];
     temp->ary12[i]=&ary[i][n/shift];
   }
   else{
    temp->ary21[i%shift]=&ary[i][0];
    temp->ary22[i%shift]=&ary[i][n/shift];
   }
 }
  if(n==2){//shitty edge case
    temp->ary12[0]=&ary[0][1];
    temp->ary22[0]=&ary[1][1];
  }
   return temp;
}

void testSplit(int n){
  int** ptr=newAry(n);
  cout<<"*** Start Split Test ***\n";
  cout<<"parent matrix to be split\n";
  for(int i=0;i<n;++i){
    for(int j=0;j<n;++j){
      ptr[i][j]=(i*10)+j+1; //asign values to location pointed to 
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
  
  cout<<"bottom right quad, ary22\n";
  for(int i=0;i<n;++i){
    for(int j=0;j<n;++j){
      ptr[i][j]=(i*10)+j+1;
      cout<<test->ary22[i][j]<<" ";
    }
    cout<<endl;
  }
  cout<<"*** End Split Test ***\n";
}

void testAdd(){
  int n=2;
  int** subA = newAry(n);
  int** subB = newAry(n);
  
  cout<<"*** Start Add Test ***\n";
  for(int i=0;i<n;++i){
      for(int j=0;j<n;++j){
	subA[i][j]=(i*2)+j;
	subB[i][j]=(i*2)+j;
      }
    }
  printAry(subA, n);
  printAry(subB, n);
  
  addArgs* package = new addArgs(subA, subB, n);
  
  addMtx((void*)package);
  
  printAry(subA, 2);
  printAry(subB, 2);
  
  cout<<"*** End Add Test ***\n";
  
}

void printAry(int ** ary, int n){
    for(int i=0;i<n;++i){
      for(int j=0;j<n;++j){
	cout<<ary[i][j]<<" ";
      }
      cout<<endl;
    }
    cout<<endl;
}
