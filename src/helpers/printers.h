#ifndef PRINTERS_H
#define PRINTERS_H

#ifdef __cplusplus
extern "C" {
#endif

// Prints OS information to the terminal
void print_os_info(void);

// Prints CPU information to the terminal
void print_cpu_info(void);

// Prints GPU information to the terminal
void print_gpu_info(void);

// Prints memory information to the terminal
void print_memory_info(void);

// Prints username and hostname to the terminal
void print_user_info(void);

// Prints the current shell to the terminal
void print_shell_info(void);

// Prints the uptime of the system to the terminal
void print_uptime_info(void);

// Prints the kernel information to the terminal
void print_kernel_info(void);

// Prints the machine model information to the terminal
void print_hw_model_info(void);
#ifdef __cplusplus
}
#endif

#endif