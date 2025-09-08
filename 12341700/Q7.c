#include <stdio.h>
#include <stdlib.h>

int main() {
    int *data = (int *)malloc(100 * sizeof(int));
    if (data == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    }

    free(&data[28]);

    return 0;
}
