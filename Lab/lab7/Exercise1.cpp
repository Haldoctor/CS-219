#include <iostream>
#include "vabs.h"
using namespace std;

int main(){
  int arr[5] = {-1 , -2 , -3 , -4 , -5};
  float arrf[5] = {-1.0 , -2.0 , -3.0 , -4.0 , -5.0};
  double arrd[5] = {-1.0 , -2.0 , -3.0 , -4.0 , -5.0};
  vabs(arr , 5);
  vabs(arrf , 5);
  vabs(arrd , 5);
  for (size_t i = 0; i < 4; i++)
  {
    cout << arr[i] << " " ;
  }
  cout << arr[4] << endl;


  for (size_t i = 0; i < 4; i++)
  {
    cout << arrf[i] << " " ;
  }
  cout << arr[4] << endl;


  for (size_t i = 0; i < 4; i++)
  {
    cout << arrd[i] << " " ;
  }
  cout << arr[4] << endl;
}