#include <iostream>
using namespace std;
int * create_array(int size)
{
    int * arr = new int[size]; //给数组的地址直接进行分配，避免在函数返回后内存被释放
    for(int i = 0; i < size; i++)
        arr[i] = i * 10;
    return arr;
}
int main()
{
    int len = 16;
    int *ptr = create_array(len);
    for(int i = 0; i < len; i++)
        cout << ptr[i] << " ";
    return 0;
}
//warning: address of stack memory associated with local variable 'arr' returned [-Wreturn-stack-address]
//8 |     return arr;
//  |            ^~~
// 0 1 -112972712 1 -112972712 1 13483780 1 1863479248 1 13480961 1 -112973912 1 1 0