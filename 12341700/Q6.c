#include <stdio.h>
#include <stdlib.h>

int main() {
    int *data = (int *)malloc(100 * sizeof(int));
    if (data == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    }

    // Initialize
    for (int i = 0; i < 100; i++) {
        data[i] = i;
    }

    free(data);

    printf("Value at index 0 : %d\n", data[0]);

    return 0;
}
