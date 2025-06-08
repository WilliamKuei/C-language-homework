#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
int Add(int a, int b) { return a + b; }
int main(){
    int(*MathMethod)(int, int)=Add;

}