#include <stdio.h>

int main() {
    int *p = NULL;   

    // dereference NULL
    int value = *p;  
    printf("Value: %d\n", value);
    return 0;
}
