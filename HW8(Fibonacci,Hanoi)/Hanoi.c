#include <stdio.h>
//from:起始 to:終點 aux:經過
void hanoi(char from, char to, char aux, int n) {
    if (n == 1) {
        printf("Move disk 1 from %c to %c\n", from, to);
    } else {
        hanoi(from, aux, to, n - 1);
        printf("Move disk %d from %c to %c\n", n, from, to);
        hanoi(aux, to, from, n - 1);
    }
}
int main() {
    int n;
    printf("Enter the number of disks: ");
    scanf("%d", &n);
    hanoi('A', 'C', 'B', n); 
    return 0;
}
