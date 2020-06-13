#include <stdio.h>
#include <stdint.h>
#include <string.h>

uint8_t hexStr2arrBin(const char * str, uint8_t * bytes, size_t buflen)
{
    size_t   pos;
    uint8_t  idx0;
    uint8_t  idx1;

    /* A lightweigh map of ASCII characters to its hex values */
    const uint8_t hashmap[] =
    {
        0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, /** 01234567 */
        0x08, 0x09, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /** 89:;<=>? */
        0x00, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f, 0x00, /** @ABCDEFG */
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00  /** HIJKLMNO */
    };

    bzero(bytes, buflen);
    for (pos = 0; ((pos < (buflen*2)) && (pos < strlen(str))); pos += 2)
    {
        idx0 = ((uint8_t)str[pos+0] & 0x1F ) ^ 0x10;
        idx1 = ((uint8_t)str[pos+1] & 0x1F ) ^ 0x10;
        bytes[pos/2] = (uint8_t)((hashmap[idx0] << 4) | hashmap[idx1]);
    };

    return 0;
}

int main(int argc, char * argv[])
{
    /* Demostration */
    const char test_str[] = "000102030405060708090A0b0c0D0e0F";
    uint8_t arr_bytes[16];
    int i;

    printf("Input hex string:\n%s\n", test_str);
    hexStr2arrBin(test_str, arr_bytes, 16);
    printf("Converted to an array of bytes:\n");
    for (i = 0; i < 16 ;i++)
    {
        printf("0x%.2X ", arr_bytes[i]);
    }
    return 0;
}