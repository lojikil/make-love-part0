#include <stdio.h>
#include <stdlib.h>

int
main() {
    int idx = 0;
    uint64_t res = 0;
    for(; idx < 20000; idx++) {
        res = arc4random();
        printf("%llu\n", res);
    }
}
