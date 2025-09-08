#include <stdio.h>
#include <stdlib.h>

int main() {
    int *data = (int *)malloc(100 * sizeof(int));
    if (data == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    }
    // out of bounds 
    data[100] = 0;

    printf("value of data[100] = %d\n", data[100]);

    free(data);
    return 0;
}
