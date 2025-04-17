#include <iostream>
#include <string.h>
using namespace std;
int main()
{
  union data {
    char ch;
    double d;
    int i;
  };
int cards[4] = {};
int hands[4];
data price[] = {{.d = 2.8},  {.d = 3.7}, {.i = 5}, {.i = 9}, {.ch = 'C'}, {.ch = 'D'}}; 
char direction[] = {'L',82,'U',68};
char title[] = "DeepSeek is an awesome tool."; 
cout << "sizeof(cards) = " << sizeof(cards) << ",sizeof of cards[0] = " << sizeof(cards[0]) << endl;
cout << "sizeof(price) = " << sizeof(price) << ",sizeof of price[0] = " << sizeof(price[0]) << endl;
cout << "sizeof(direction) = " << sizeof(direction) << ",length of direction = " << strlen(direction) << endl;
cout << "sizeof(title) = " << sizeof(title) << ",length of title = " << strlen(title) << endl;
return 0;
}