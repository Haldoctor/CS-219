#include<stdio.h>
int main() 
{ 
int a[]={2,4,6,8,10},y=1,*p;
p=&a[1];
printf("a = %p\np = %p\n",a, p); // a是a[0]的地址，p是a[1]的地址
for(int i = 0; i < 3; i++) 
y += *(p+i); //1+4+6+8 = y
printf("y = %d\n\n",y);
int b[5]={1,2,3,4,5};
int *ptr=(int*)(&b+1); //跳到末尾
printf("b = %p\nb+4 = %p\nptr = %p\n",b,b+4,ptr); //b是b数组的首地址，b+4是b数组的首地址往后偏移了四个单位，ptr是直接跳过b数组的下一个地址
printf("%d,%d\n",*(b+1),*(ptr-1));// 输出b[1], 输出数组最后一个元素
return 0;
}