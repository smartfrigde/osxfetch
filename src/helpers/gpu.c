#include "gpu.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char cached[256];
static int initialized = 0;

char* get_gpu_info(void) {
    if (initialized) return cached;
    initialized = 1;
    strcpy(cached, "Unknown GPU");

    FILE *fp = popen("system_profiler SPDisplaysDataType 2>/dev/null | awk -F': ' '/Chipset Model/ {print $2; exit}'", "r");
    if (!fp) return cached;
    if (fgets(cached, sizeof(cached), fp) != NULL) {
        size_t len = strlen(cached);
        if (len > 0 && cached[len-1] == '\n') cached[len-1] = '\0';
    } else {
        strcpy(cached, "Unknown GPU");
    }
    pclose(fp);
    return cached;
}