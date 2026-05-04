#include <stdio.h>
#include <stdlib.h>
#include "helpers/printers.h"
int main(int argc, char* argv[]) { 
    if (argc == 1) {
        // No arguments = print all info
        print_user_info();
        print_os_info();
        print_kernel_info();
        print_uptime_info();
        print_hw_model_info();
        print_cpu_info();
        print_gpu_info();
        print_memory_info();
        print_shell_info();
    } else {
        // Parse flags from arguments like -m, -mo, -mog, etc.
        for (int i = 1; i < argc; i++) {
            if (argv[i][0] == '-') {
                // Process each character after the dash
                for (int j = 1; argv[i][j] != '\0'; j++) {
                    char flag = argv[i][j];
                    switch (flag) {
                        case 'u':
                            print_user_info();
                            break;
                        case 'c':
                            print_cpu_info();
                            break;
                        case 'g':
                            print_gpu_info();
                            break;
                        case 'm':
                            print_memory_info();
                            break;
                        case 'o':
                            print_os_info();
                            break;
                        case 's':
                            print_shell_info();
                            break;
                        case 't':
                            print_uptime_info();
                            break;
                        case 'k':
                            print_kernel_info();
                            break;
                        case 'w':
                            print_hw_model_info();
                            break;
                        case 'h':
                            printf("Usage: %s [-options]\n", argv[0]);
                            printf("Options:\n");
                            printf("  u - Print username and hostname\n");
                            printf("  c - Print CPU information\n");
                            printf("  g - Print GPU information\n");
                            printf("  m - Print memory information\n");
                            printf("  o - Print OS information\n");
                            printf("  s - Print shell information\n");
                            printf("  w - Print machine model information\n");
                            printf("  k - Print kernel information\n");
                            printf("  t - Print uptime information\n");
                            printf("  h - Show this help message\n");
                            break;
                        default:
                            fprintf(stderr, "Unknown option: %c\n", flag);
                    }
                }
            }
        }
    }
    
    return 0;
}
