#include <stdio.h>
#include <stdint.h>
#include <sys/sysctl.h>
#include <sys/types.h>


// There's no CPU Brand string on PPC, so we just fill it out with generic cpu frequency info.
// TO-DO: detect G3, G4, G5 etc.
char* get_cpu_info(void)
{
	#if defined(__powerpc__) || defined(__ppc__) || defined(__PPC__)
    int mib[2];
    int cpu_freq;
    size_t length;
    mib[0] = CTL_HW;
    mib[1] = HW_CPU_FREQ;
    length = sizeof(int64_t);
    sysctl(mib, 2, &cpu_freq, &length, NULL, 0);
    static char cpu_frequency[256];
    snprintf(cpu_frequency, sizeof(cpu_frequency), "%.0f MHz", cpu_freq / 1000000.0);
    return cpu_frequency;
	#else
	static char buffer[1024];
    size_t size=sizeof(buffer);
    if (sysctlbyname("machdep.cpu.brand_string", &buffer, &size, NULL, 0) < 0) {
        perror("sysctl");
    }
    return buffer;
	#endif
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