#include "headers/custom_unistd.h"

typedef struct mem_block *mem_block_ptr;
/* A linked list */
struct mem_block {
        custom_size_t           size;
        mem_block_ptr           next;
        custom_bool             is_free;        /* 1 byte unsigned char boolean */
        /*unsigned char           is_free : 1;     1 bit boolean, just for an example */
        /* Use 1 byte for a boolean instead of 1 bit primarily for efficiency in memory access and alignment.
           Accessing single bits would require additional operations, slowing down computation, while using bytes simplifies implementation and ensures compatibility with modern hardware.
           https://stackoverflow.com/questions/4626815/why-is-a-boolean-1-byte-and-not-1-bit-of-size - also the comments under the answer have useful information */
};


/*
When the compiler sees an access to struct field
example: mem_block.is_free or mem_block_ptr->is_free
it translates to the base address of the struct
plus the sum of the length of the previous field
mem_block_ptr->is_free == *((char*)p + 8)  8bytes/32bits
mem_block.is_free == *((char*)&s + 8)  8bytes/32bits

Example of using mem_block without malloc
mem_block_ptr         block_ptr;
Save the old break in block_ptr
block_ptr = sbrk(0);    // sbrk returns void*
add the needed space
size is the parameter of malloc
sbrk(sizeof(struct mem_block) + size);
*mem_block_ptr->size = size;
*/
