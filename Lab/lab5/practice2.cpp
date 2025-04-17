#include <iostream>
using namespace std;
int main()
{
int a[][4]={1,3,5,7,9,11,13,15,17,19}; 
int *p=*(a+1); //指向9
p += 3; //指向15
cout << "*p++ = " << *p++ << ",*p = " << *p << endl; //先输出15，输出15之后进行++操作，指向17
const char *pc = "Welcome to programming.", *r;
long *q = (long *)pc;
q++; //指向t
r = (char *)q; 
cout << r << endl; // 输出to programming
unsigned int m = 0x3E56AF67;
unsigned short *pm = (unsigned short *) &m; // short只保留后两位
cout << "*pm = " << hex << *pm << endl;
return 0;
}