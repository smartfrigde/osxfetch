#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <unistd.h>
#include <sys/param.h>
#include <sys/types.h>
#include <string.h>
#include <sys/sysctl.h>
#include <CoreServices/CoreServices.h>
#include "helpers/gpu.h"

char* get_cpu_info(void)
{
    static char buffer[1024];
    size_t size=sizeof(buffer);
    if (sysctlbyname("machdep.cpu.brand_string", &buffer, &size, NULL, 0) < 0) {
        perror("sysctl");
    }
    return buffer;
}
char* get_hostname(void) {
    static char hostname[255];
    gethostname(hostname, sizeof(hostname));
    return hostname;
}

char* get_username(void) {
    static char username[MAXLOGNAME];
    strcpy(username, getenv("USER")); // NOTE: getenv is not the securest way to get the username, but getlogin is not reliable and returns root for some reason
    return username;
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

char* get_os(void) {
    int majorVersion,minorVersion,bugFixVersion;

    Gestalt(gestaltSystemVersionMajor, &majorVersion);
    Gestalt(gestaltSystemVersionMinor, &minorVersion);
    Gestalt(gestaltSystemVersionBugFix, &bugFixVersion);

    static char os_info[256];
    static char os_name[256];
    if (majorVersion == 10 && minorVersion > 12) {
        strcpy(os_name, "Mac OS X");
    } else {
        strcpy(os_name, "macOS");
    }
    snprintf(os_info, sizeof(os_info), "%s %d.%d.%d", os_name, majorVersion, minorVersion, bugFixVersion);
    return os_info;
}

int main() { 
    printf(" %s@%s\n", get_username(), get_hostname());
    printf("CPU: %s\n", get_cpu_info());
    printf("GPU: %s\n", get_gpu_info());
    printf("Memory: %s GB\n", get_memory_info());
    printf("OS: %s\n", get_os());
    printf("Shell: %s\n", getenv("SHELL"));

    return 0;
}
