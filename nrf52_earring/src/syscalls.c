// syscalls.c
#include "sdk_config.h"

#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>

int _close(int file) { return -1; }
int _fstat(int file, struct stat *st) { st->st_mode = S_IFCHR; return 0; }
int _isatty(int file) { return 1; }
int _lseek(int file, int ptr, int dir) { return 0; }
int _read(int file, char *ptr, int len) { return 0; }
int _write(int file, char *ptr, int len) { return len; }

void *_sbrk(ptrdiff_t incr) {
    extern char __HeapBase;
    extern char __HeapLimit;
    static char *heap_end;
    char *prev_heap_end;

    if (heap_end == 0) {
        heap_end = &__HeapBase;
    }

    prev_heap_end = heap_end;
    if (heap_end + incr > &__HeapLimit) {
        errno = ENOMEM;
        return (void *)-1;
    }

    heap_end += incr;
    return (void *)prev_heap_end;
}

void _exit(int status) {
    while (1) {}
}