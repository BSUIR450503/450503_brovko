#include <unistd.h>

int has_initialized = 0;

void *managed_memory_start;

void *last_valid_address;

struct mem_control_block {
    int is_available;
    int size;
};

void malloc_init()
{
    last_valid_address = sbrk(0);
    managed_memory_start = last_valid_address;
    has_initialized = 1;
}

void free(void*first_byte) 
{
    struct mem_control_block *mcb;
    mcb = (mem_control_block *)(first_byte - sizeof(struct mem_control_block));
    mcb->is_available = 1;
    return;
}

void *_malloc(long numbytes) 
{
    void *current_location;
    struct mem_control_block* current_location_mcb;
    void *memory_location;

    if(! has_initialized) {
        malloc_init();
    }

    numbytes = numbytes + sizeof(struct mem_control_block);
    memory_location = 0;
    current_location = managed_memory_start;

    while(current_location != last_valid_address)
    {
        current_location_mcb = (struct mem_control_block *)current_location;
        if(current_location_mcb->is_available)
        {
            if(current_location_mcb->size >= numbytes)у
            {
                current_location_mcb->is_available = 0;
                memory_location = current_location;
                break;
            }
        }
        current_location = current_location + current_location_mcb->size;
    }

    if(! memory_location)
    {

        if (sbrk(numbytes) == (void*)-1) return 0;
        memory_location = last_valid_address;
        last_valid_address = last_valid_address + numbytes;
        current_location_mcb =(mem_control_block *) memory_location;
        current_location_mcb->is_available = 0;
        current_location_mcb->size = numbytes;
    }

    memory_location = memory_location + sizeof(struct mem_control_block);

return memory_location;
}

void * _realloc (void * memory_location,long numbytes)
{
    void * control_block_location = memory_location - sizeof(struct mem_control_block);
    mem_control_block * control_block = (struct mem_control_block *) control_block_location;

    if (numbytes < control_block->size) 
        return 0;

    void * new_memory = _malloc(numbytes);

    for (int i=0;i<control_block->size;i++)
        ((char*)new_memory)[i]=((char*)memory_location)[i];

    free(memory_location);
    return new_memory;
}
