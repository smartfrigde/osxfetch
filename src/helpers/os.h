#ifndef OS_H
#define OS_H

#ifdef __cplusplus
extern "C" {
#endif

// Returns "macOS/Mac OS X Major.Minor.BugFix"
char* get_os(void);

// Returns the hostname
char* get_hostname(void);

// Returns the username
char* get_username(void);

// Returns the major version of the OS
int get_os_major_version(void);

// Returns the minor version of the OS
int get_os_minor_version(void);

// Returns the bugfix version of the OS
int get_os_bugfix_version(void);

// Returns the uptime of the system in seconds
int get_uptime(void);

// Returns the kernel information
char* get_kernel_info(void);

#ifdef __cplusplus
}
#endif

#endif