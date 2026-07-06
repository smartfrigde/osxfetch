#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/param.h>
#include <string.h>
#include <sys/time.h>
#include <CoreServices/CoreServices.h>
#include <sys/sysctl.h>

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

int get_os_major_version(void) {
    int majorVersion;
    Gestalt(gestaltSystemVersionMajor, &majorVersion);
    return majorVersion;
}

int get_os_minor_version(void) {
    int minorVersion;
    Gestalt(gestaltSystemVersionMinor, &minorVersion);
    return minorVersion;
}

int get_os_bugfix_version(void) {
    int bugFixVersion;
    Gestalt(gestaltSystemVersionBugFix, &bugFixVersion);
    return bugFixVersion;
}

char* get_os(void) {
    int majorVersion = get_os_major_version();
    int minorVersion = get_os_minor_version();
    int bugFixVersion = get_os_bugfix_version();
    static char os_info[256];
    static char os_name[256];
    if (majorVersion == 10 && minorVersion < 12) {
        strcpy(os_name, "Mac OS X");
    } else {
        strcpy(os_name, "macOS");
    }
    snprintf(os_info, sizeof(os_info), "%s %d.%d.%d", os_name, majorVersion, minorVersion, bugFixVersion);
    return os_info;
}

int get_uptime(void)
{
    int mib[2];
    struct timeval boot_time;
    size_t length;
    mib[0] = CTL_KERN;
    mib[1] = KERN_BOOTTIME;
    length = sizeof(boot_time);
    sysctl(mib, 2, &boot_time, &length, NULL, 0);
    time_t now = time(NULL);
    return (int)(now - boot_time.tv_sec);
}

char* get_kernel_info(void)
{
    int mib[2];
    static char kern_version[1024];
    size_t length;
    mib[0] = CTL_KERN;
    mib[1] = KERN_VERSION;
    length = sizeof(kern_version);
    sysctl(mib, 2, kern_version, &length, NULL, 0);
    return kern_version;
}
