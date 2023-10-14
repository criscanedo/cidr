#include <limits.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#define IP4_BITS 32
#define IP4_LEN 15          /* xxx.xxx.xxx.xxx */
#define MAXLINE IP4_LEN + 4 /* xxx.xxx.xxx.xxx/xx + \n */

void iptostr(uint32_t ip, char *s)
{
    snprintf(s, IP4_LEN + 1, "%d.%d.%d.%d",
        ip >> 24, (ip >> 16) & 0xFF, (ip >> 8) & 0xFF, ip & 0xFF);
}

int iptoint(char *s, uint32_t *ip)
{
    unsigned short a, b, c, d;

    if (sscanf(s, "%3hu.%3hu.%3hu.%3hu", &a, &b, &c, &d) < 4)
        return -1;

    if (a > UCHAR_MAX || b > UCHAR_MAX || c > UCHAR_MAX || d > UCHAR_MAX)
        return -1;

    *ip = (a << 24) | (b << 16) | (c << 8) | d;
    return 0;
}

int torange(char *cidr, char *first, char *last)
{
    uint8_t bits;
    uint32_t start, end, mask;

    if (sscanf(cidr, "%15[0-9.]/%hhu", first, &bits) < 2 || bits > IP4_BITS)
        return -1;

    if (iptoint(first, &start) == -1)
        return -1;

    mask = (0xFFFFFFFF << (IP4_BITS - bits)) & 0xFFFFFFFF;
    end = (start & mask) | ~mask;
    iptostr(end, last);
    return 0;
}

void parse(char *cidr)
{
    char first[IP4_LEN + 1] = { 0 };
    char last[IP4_LEN + 1] = { 0 };

    if (torange(cidr, first, last) != -1)
        printf("%-*s - %-*s\n", IP4_LEN, first, IP4_LEN, last);
}

int main(int argc, char *argv[])
{
    if (argc > 1) {
        for (; *argv; argv++)
            parse(*argv);
    } else {
        char line[MAXLINE + 2];
        while (fgets(line, sizeof(line), stdin))
            parse(line);
    }

    return 0;
}
