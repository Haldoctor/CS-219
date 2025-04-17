#include <iostream>

//option A
int add2_1(int*x,int*y){
  int sum= ((*x)++)+((*y)++);
  return sum;
  x=NULL;
  y=NULL;
}

  //option B
int add2_2(int*x,int*y){
  int sum= ((*x)++)+((*y)++);
  return sum;
  x=NULL;
  y=NULL;
}

 //option C
int add3_x(int &c,int &d){
  int sum= (c++)+(d++);
  int *e= (int*)malloc(sizeof(int));
  *e = 1;
  c=*e;
  d=*e;
  sum= (++c)+(++d);
  free(e);
  return sum;
}

int main(){
  int a = 10;
  int b = 20;
  int * ptr_a = &a;
  int * ptr_b = &b;
  int result_1 = add2_1(ptr_a , ptr_b);
  int result_2 = add2_2(ptr_a , ptr_b);
  int result_3 = add3_x(a , b);
  std::cout << result_1 << ' ' << result_2 << ' ' << result_3 << std::endl;
}


    