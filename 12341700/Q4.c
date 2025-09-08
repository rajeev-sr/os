#include <stdio.h>
#include <stdlib.h>


int main() {
    int *a = (int *)malloc(10 * sizeof(int));
    if (a == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    }
    for (int i = 0; i < 10; i++) {
        a[i] = i;
    }

    printf("first element = %d\n", a[0]);
    return 0;
}
