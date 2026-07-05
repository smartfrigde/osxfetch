#ifndef HW_H
#define HW_H

#ifdef __cplusplus
extern "C" {
#endif

// Returns current CPU
char* get_cpu_info(void);

// Returns machine model (e.g. MacBookPro15,1)
char* get_hw_model_info(void);

// Returns RAM in GB
char* get_memory_info(void);

#ifdef __cplusplus
}
#endif

#endif