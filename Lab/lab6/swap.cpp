#include "swap.h"

void swap(int * a , int * b){
  if (a != nullptr && b != nullptr) {
    int temp = *a;
    *a = *b;
    *b = temp;
  }
}