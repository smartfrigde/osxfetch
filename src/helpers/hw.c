#include <stdio.h>
#include <stdint.h>
#include <sys/sysctl.h>

char* get_cpu_info(void)
{
    static char buffer[1024];
    size_t size=sizeof(buffer);
    if (sysctlbyname("machdep.cpu.brand_string", &buffer, &size, NULL, 0) < 0) {
        perror("sysctl");
    }
    return buffer;
}

char* get_hw_model_info(void)
{
    static char buffer[1024];
    size_t size=sizeof(buffer);
    if (sysctlbyname("hw.model", &buffer, &size, NULL, 0) < 0) {
        perror("sysctl");
    }
    return buffer;
}

char* get_memory_info(void) {
    int mib[2];
    int64_t physical_memory;
    size_t length;
    mib[0] = CTL_HW;
    mib[1] = HW_MEMSIZE;
    length = sizeof(int64_t);
    sysctl(mib, 2, &physical_memory, &length, NULL, 0);
    static char memory_info[256];
    snprintf(memory_info, sizeof(memory_info), "%.2f", (double)physical_memory / (1024 * 1024 * 1024));
    return memory_info;
}