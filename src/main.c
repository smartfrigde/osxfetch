#include <stdio.h>
#include <limits.h>
#include <unistd.h>
int main() {
    char hostname[255];
    gethostname(hostname, sizeof(hostname));
    printf(" %s\n", hostname);
    return 0;
}
