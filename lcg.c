#include <stdio.h>
#include <stdint.h>

uint64_t lcg(uint64_t mod, uint64_t a, uint64_t c, uint64_t seed);

int
main() {
    /* these values are wrong, in a subtle way. an interesting idea would
     * be to fix them, and know _why_ they are wrong.
     * then, think about how much trust you place in numbers in other people's
     * code
     */
    uint64_t seed = 2592, a = 25214903917, c = 11, tmp = 0, mod = 0xDEADBEEF54;

    printf("%s\n", (a < mod ? "yes" : "no"));

    for(int idx = 0; idx < 20000; idx++) {
        tmp = lcg(mod, a, c, seed);
        printf("%llu\n", tmp);
        seed = tmp;
    }

    return 0;
}

uint64_t
lcg(uint64_t mod, uint64_t a, uint64_t c, uint64_t seed) {
    return ((a * seed) + c) % mod;
}
