#include "tests/lib.h"
#include "tests/str.h"

int
main(void) {
    char *heap;

    cout("Testing memlimit.\n");

    cout("-> getting current heap: ");
    heap = syscall_memlimit(0);
    if (heap) cout("OK.\n");
    else {
        cout("FAIL!\n");
        return 1;
    }

    cout("-> memlimit with address below heap start: ");
    heap = syscall_memlimit(heap - 1);
    if (heap) {
        cout("FAIL!\n");
        return 1;
    } else cout("OK.\n");

    cout("-> memlimit with maximum address: ");
    heap = syscall_memlimit((void *)((uint32_t)(-1)));
    if (heap) {
        cout("FAIL!\n");
        return 1;
    } else cout("OK.\n");

    cout("-> memlimit with under one page difference: ");
    heap = syscall_memlimit(0);
    heap = syscall_memlimit(heap + 8);
    if (heap) cout("OK.\n");
    else {
        cout("FAIL!\n");
        return 1;
    }

    cout("-> memlimit with over one page difference: ");
    heap = syscall_memlimit(heap + 4096);
    if (heap) cout("OK.\n");
    else {
        cout("FAIL!\n");
        return 1;
    }

    return 0;
}
