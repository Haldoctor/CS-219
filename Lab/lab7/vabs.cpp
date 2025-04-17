#include "vabs.h"
#include <cmath>   
#include <cstdlib>  
#include <cstddef>  
#include <iostream>

void vabs(int *p , size_t n){
  if (p != nullptr) 
  {
    std::cout << "int vabs" << std::endl;
    for (size_t i = 0; i < n; ++i) {
      p[i] = std::abs(p[i]);
    }
  }
}

void vabs(float *p , size_t n){
  if (p != nullptr)
  {
    std::cout << "float vabs" << std::endl;
    for (size_t i = 0; i < n; i++)
    {
      p[i] = std::fabs(p[i]);
    }
  }
}

void vabs(double *p , size_t n){
  if (p != nullptr)
  {
    std::cout << "double vabs" << std::endl;
    for (size_t i = 0; i < n; i++)
    {
      p[i] = std::fabs(p[i]);
    }
  }
}