#include <stdio.h>
#include <stdint.h>
#include <time.h>

void encipher(uint32_t *, uint32_t *);
uint64_t xtea_rand();

int
main() {
    int idx = 0;
    uint64_t res = 0;
    for(; idx < 20000; idx++) {
        res = xtea_rand();
        printf("%llu\n", res);
    }
}

uint64_t
xtea_rand() {
    static uint32_t blocks_output = 0, key[4] = {0x00000000, 0x3b6e20c8, 0x76dc4190, 0x4db26158};
    static uint64_t ctr = 0;
    uint32_t vcounter[2] = {0};
    uint64_t res = 0;
    time_t t = 0;

    vcounter[0] = time(&t);
    vcounter[1] = t + ctr;

    if(blocks_output >= 21) {
        encipher(&vcounter[0], &key[0]);
        key[0] = vcounter[0];
        key[1] = vcounter[1];
        vcounter[0] = time(&t);
        vcounter[1] = ctr + 1;
        encipher(&vcounter[0], &key[0]);
        key[2] = vcounter[0];
        key[3] = vcounter[1];
        vcounter[0] = time(&t);
        vcounter[1] = ctr + 2;
        ctr += 2;
    }

    encipher(&vcounter[0], &key[0]);
    res = (vcounter[0] << 32) + vcounter[1];
    blocks_output += 1;
    ctr += 1;
    return res;
}

void encipher(uint32_t* v, uint32_t* k)
{
    uint32_t v0=v[0], v1=v[1], i;
    uint32_t sum=0, delta=0x9E3779B9;
    for(i=0; i < 64; i++)
    {
        v0 += (((v1 << 4) ^ (v1 >> 5)) + v1) ^ (sum + k[sum & 3]);
        sum += delta;
        v1 += (((v0 << 4) ^ (v0 >> 5)) + v0) ^ (sum + k[(sum>>11) & 3]);
    }
    v[0]=v0;
    v[1]=v1;
}
