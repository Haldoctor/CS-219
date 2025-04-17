#include <stdio.h> 
int main()
{
    signed char a = 127;
    unsigned char b = 0x7f; 
    char c = 0x7f; //没有明确是否有符号

    a=a<<1; //左移一位之后第一位原本是七位的移到了第八位，因为a是有符号类型，所以会出现符号位置的错误
    b=b<<1;
    c=c<<1;            
    printf("a=%x\nb=%x\nc=%x\n",a,b,c);
    printf("a=%d\nb=%d\nc=%d\n",a,b,c);
    a=a>>1;
    b=b>>1;
    c=c>>1;
printf("a=%x\nb=%x\nc=%x\n",a,b,c);
    printf("a=%d\nb=%d\nc=%d\n",a,b,c);

    return 0;
}
