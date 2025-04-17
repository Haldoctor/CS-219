#include <stdio.h>
#include <stdlib.h>
int main(int argc, char*argv[]){
int A = 0x11223344; //Little Endian
if(argc==2){
if((*(argv[1])='H')){
int *B = malloc(sizeof(int)*1);
if(NULL!=B){
  char * a = (char*) &A;
  char * b = (char*) B;
  for (short i = 0; i < sizeof(int); i++)
  {
    b[i] = a[sizeof(int) - i - 1];
  }
  printf("%x\n", *B);
  free(B);
  return 0;
} 
else return 2;
}
else if((*(argv[1])='S')){
  int *B = NULL;
  char * a = (char*) &A;
  char * b = (char*) B;
  for (short i = 0; i < sizeof(int); i++)
  {
    b[i] = a[sizeof(int) - i - 1];
  }
  printf("%x\n", *B);
  return 0;
}
else return 1; 
}
else return 1;
}