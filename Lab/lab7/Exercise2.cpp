#include <iostream>
using namespace std;


struct stuinfo{
  string name;
   int age;
};

template <typename T>
int compare(T x , T y){
  cout << "Comparing type: " << typeid(T).name() << endl;
  if (x > y)
  {
    return 1;
  }
  else if (x < y)
  {
    return -1;
  }
  else if (x == y)
  {
    return 0;
  }
  else{
    return -2;
  }
}

template int compare<int>(int, int);
template int compare<double>(double, double);
template int compare<char>(char, char);

template <>
int compare<stuinfo>(const stuinfo a, const stuinfo b) {
  cout << "Comparing type: " << "stuinfo" << endl;
    if (a.age > b.age) 
    {
      return 1;
    }
    else if (a.age < b.age) 
    {
      return -1;
    }
    else 
    {
      return 0;
    }
}


int main (){
  cout << compare(5 , 3) << endl;
  cout << compare(5.0 , 3.0) << endl;
  cout << compare(3 , 5) << endl;
  cout << compare(3.0 , 5.0) << endl;
  cout << compare<char>('3' , '5') << endl;
  stuinfo a = {"Alice", 20};
  stuinfo b = {"Bob", 18};
  cout << compare<stuinfo>(a,b) << endl;
}
