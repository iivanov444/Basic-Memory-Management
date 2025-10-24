/* bad dummy malloc */

#include "headers/custom_unistd.h"

void *dummy_malloc(custom_size_t size)
{
        void *ptr;
        ptr = custom_sbrk(0);
        /* If sbrk fails, we return NULL */
        if (custom_sbrk(size) == (void*)-1)
                return custom_NULL;

        return ptr;
}       
