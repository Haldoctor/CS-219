#include <iostream>
using namespace std;

int main()
{
    unsigned int n = 5;  
    int sum;
    while(n >0){
        sum += n;
        cout << "n = " << (n-=2) <<endl;
        cout << "sum = " << sum << "  ";
    }
    return 0;
}

