/* First fit algorithm used for basic understanding of malloc */

#include "headers/custom_unistd.h"

/* CUSTOM_ALIGN comes from custom_types header
   8 byte alignment for 64 bit architectures
   4 byte alignment for 32 bit architectures */

void *base_global_ptr = custom_NULL;

struct mem_block {
        custom_size_t           size;
        struct mem_block        *next;
        struct mem_block        *prev;
        custom_bool             is_free;
        void                    *ptr_to_mem_block;   /* A pointer to the allocated block */
        char                    data[1];
};
typedef struct mem_block *mem_block_ptr;


static struct mem_block dummy_block;
#define BLOCK_SIZE ((custom_size_t)((char*)&dummy_block.data - (char*)&dummy_block))
/* Using the above workaround because Clang doesn't like the code below
#define BLOCK_SIZE ((custom_size_t)((char*)(&((mem_block_ptr)0)->data) - (char*)0)) */


/* base_global_ptr is a global pointer to the starting point of our heap */
mem_block_ptr custom_find_block(mem_block_ptr *last, custom_size_t size) {
        mem_block_ptr base = base_global_ptr;

        while (base && !(base->is_free && base->size >= size)) {
                *last = base;
                base = base->next;
        }

        return (base);
}
/* The function returns a fitting chunk or NULL if none were found.
   After the execution, the argument 'last' points to the last visited chunk. */


/* Add a new block at the end of the heap
   return NULL if it fails */
mem_block_ptr custom_extend_heap(mem_block_ptr last_block, custom_size_t new_block_size) {
        void            *sbrk_call;
        custom_size_t   sbrk_call_increment;
        mem_block_ptr   new_block;

        new_block = custom_sbrk(0);
        sbrk_call_increment = BLOCK_SIZE + new_block_size;
        if (sbrk_call_increment > (custom_size_t)CUSTOM_INTPTR_MAX) {
                /* Handle overflow case */
                return custom_NULL;
        }
        sbrk_call = custom_sbrk((custom_intptr_t)sbrk_call_increment);

        if (sbrk_call == (void*)-1)
                /* sbrk fails */
                return custom_NULL;

        new_block->size             = new_block_size;
        new_block->next             = custom_NULL;
        new_block->prev             = last_block;
        new_block->ptr_to_mem_block = new_block->data;

        if (last_block)
                last_block->next = new_block;
        
        new_block->is_free = custom_bool_FALSE;
        return (new_block);
}


void custom_split_block(mem_block_ptr current_block, custom_size_t new_block_size) {
        mem_block_ptr new_block;
        new_block = (mem_block_ptr)((custom_uintptr_t)current_block + BLOCK_SIZE + new_block_size);
        
        new_block->size               = current_block->size - new_block_size - BLOCK_SIZE;
        new_block->next               = current_block->next;
        new_block->prev               = current_block;
        new_block->is_free            = custom_bool_TRUE;
        new_block->ptr_to_mem_block   = new_block->data;
        current_block->size           = new_block_size;
        current_block->next           = new_block;

        if (new_block->next)
                new_block->next->prev = new_block;
}


mem_block_ptr custom_fusion(mem_block_ptr block) {
        if (block->next && block->next->is_free) {
                block->size += BLOCK_SIZE + block->next->size;
                block->next = block->next->next;
                if (block->next)
                        block->next->prev = block;
        }
        return (block);
}


mem_block_ptr custom_get_block(void *ptr) {
        char *temp_ptr;
        temp_ptr = ptr;
        return (ptr = temp_ptr -= BLOCK_SIZE);
}


/* Valid address for free */
int custom_valid_addr(void *addr) {
        if (base_global_ptr)
                if (addr > base_global_ptr && addr < custom_sbrk(0))
                        return (addr == (custom_get_block(addr)->ptr_to_mem_block));

        return (0);
}


void custom_copy_block(mem_block_ptr source, mem_block_ptr destination) {
        char             *source_data, *destination_data;
        custom_size_t    index, copy_size;
        
        source_data = (char*)source->ptr_to_mem_block;
        destination_data = (char*)destination->ptr_to_mem_block;

        /* Copy the smaller of the two sizes to avoid copying more data than either block can hold */
        copy_size = (source->size < destination->size) ? source->size : destination->size;

        for (index = 0; index < copy_size; index++)
                destination_data[index] = source_data[index];
}


void *custom_malloc(custom_size_t request_size) {
        mem_block_ptr         current_block, last_block;
        custom_size_t         current_block_size;

        current_block_size = CUSTOM_ALIGN(request_size);
        
        if (base_global_ptr) {
                /* First find a block */
                last_block = base_global_ptr;
                current_block = custom_find_block(&last_block, current_block_size);
                if (current_block) {
                        /* Can we split */
                        if ((current_block->size - current_block_size) >= (BLOCK_SIZE + CUSTOM_ALIGN(1)))
                                custom_split_block(current_block, current_block_size);
                        current_block->is_free = custom_bool_FALSE;
                }

                else {
                        /* No fitting block, extend the heap */
                        current_block = custom_extend_heap(last_block, current_block_size);
                        if (!current_block)
                                return custom_NULL;
                }
        }

        else {
                /* First time */
                current_block = custom_extend_heap(custom_NULL, current_block_size);
                if (!current_block)
                        return custom_NULL;
                base_global_ptr = current_block;
        }

        return(current_block->data);
}


void *custom_calloc(custom_size_t number, custom_size_t size) {
        char            *new;
        custom_size_t   size_aligned, index;
        
        new = custom_malloc(number * size);
        
        if (new) {
                size_aligned = CUSTOM_ALIGN(number * size);
                /* Clear the entire aligned memory region */
                for (index = 0; index < size_aligned; index++)
                        new[index] = 0;
        }

        return (new);
}


void custom_free(void *ptr) {
        mem_block_ptr block;

        if (custom_valid_addr(ptr)) {
                block = custom_get_block(ptr);
                block->is_free = custom_bool_TRUE;
                /* Fusion with previous if possible */
                if (block->prev && block->prev->is_free)
                        block = custom_fusion(block->prev);
                /* Then fusion with next */
                if (block->next)
                        custom_fusion(block);
                
                else {
                        /* Free the end of the heap */
                        if (block->prev)
                                block->prev->next = custom_NULL;
                        else
                                /* No more block! */
                                base_global_ptr = custom_NULL;
                        custom_brk(block);
                }
        }
}


void *custom_realloc(void *ptr, custom_size_t size) {
        custom_size_t   size_aligned;
        mem_block_ptr   current_block, new_block;
        void            *new_ptr;

        if (!ptr) return (custom_malloc(size));

        if (custom_valid_addr(ptr)) {
                size_aligned = CUSTOM_ALIGN(size);
                current_block = custom_get_block(ptr);

                if (current_block->size >= size_aligned) {
                        if (current_block->size - size_aligned >= (BLOCK_SIZE + CUSTOM_ALIGN(1)))
                                custom_split_block(current_block, size_aligned);
                }

                else {
                        /* Try fusion with next if possible */
                        if (current_block->next && current_block->next->is_free
                            && (current_block->size + BLOCK_SIZE + current_block->next->size) >= size_aligned)
                        {
                                custom_fusion(current_block);
                                if (current_block->size - size_aligned >= (BLOCK_SIZE + CUSTOM_ALIGN(1)))
                                        custom_split_block(current_block, size_aligned);
                        }

                        else {
                                /* Realloc with a new block */
                                new_ptr = custom_malloc(size_aligned);
                                if (!new_ptr)
                                        /* Fail */
                                        return (custom_NULL);
                                /* We assume this will work */
                                new_block = custom_get_block(new_ptr);
                                /* Copy data */
                                custom_copy_block(current_block, new_block);
                                /* Free the old one */
                                custom_free(ptr);
                                return (new_ptr);
                        }
                }
                return (ptr);
        }
        return (custom_NULL);
}


void *custom_bsd_reallocf(void *ptr, custom_size_t size) {
        void *new_ptr;
        new_ptr = custom_realloc(ptr, size);

        if (!new_ptr) custom_free(ptr);

        return (new_ptr);
}

