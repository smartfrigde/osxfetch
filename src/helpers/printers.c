#include <stdio.h>
#include <stdlib.h>
#include "gpu.h"
#include "hw.h"
#include "os.h"
void print_os_info(void) {
    printf("OS: %s\n", get_os());
}
void print_cpu_info(void) {
    printf("CPU: %s\n", get_cpu_info());
}
void print_gpu_info(void) {
    printf("GPU: %s\n", get_gpu_info());
}
void print_memory_info(void) {
    printf("Memory: %s GB\n", get_memory_info());
}
void print_user_info(void) {
    printf(" %s@%s\n", get_username(), get_hostname());
}
void print_shell_info(void) {
    printf("Shell: %s\n", getenv("SHELL"));
}
