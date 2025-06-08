#include <stdio.h>
int fab_num(int n);
int fab_num(int n){
    if(n==0){
        return 1;
    }
    else if(n==1){
        return 1;
    }
    else{
        return fab_num(n-1)+fab_num(n-2);
    }
}
int main(){
    int n;
    printf("Enter the number of terms: ");
    scanf("%d",&n);
    printf("Fibonacci series: ");
    for(int i=0;i<n;i++){
        printf("%d ",fab_num(i));
    }
    return 0;

}