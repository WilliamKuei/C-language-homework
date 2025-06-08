#include <stdio.h>
typedef union{
    struct {
        unsigned F:23;
        unsigned E:8;
        unsigned S:1;
    };
    float f;
}Float;
int main(){
    Float a;
    a.f=-3.7;
    printf("S=%d,E=%02XH,F=%061XH",a.S,a.E,a.F);
    
}