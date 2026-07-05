#ifndef GPU_H
#define GPU_H

#ifdef __cplusplus
extern "C" {
#endif

// Returns "Vendor - Renderer"
// Do NOT free the returned pointer
char* get_gpu_info(void);

#ifdef __cplusplus
}
#endif

#endif