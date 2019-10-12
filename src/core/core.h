#ifndef _CORE_H
#define _CORE_H

#include "world.h"
#include "handling.h"

#include <stdint.h>

typedef struct _generational_index
{
    uint32_t index;
    uint64_t generation;
} GenerationalIndex;

// #define DefineGenerationalIndexArray(T)

typedef struct holyeff{int x; int y;}  HOLYEFF;

struct _generational_index_array_HOLYEFF;

typedef struct _generational_index_array_impl_HOLYEFF
{
    void (*set)(struct _generational_index_array_HOLYEFF, struct _generational_index * index, HOLYEFF *value);
    HOLYEFF (*get)(struct _generational_index_array_HOLYEFF, struct _generational_index * index);
    bool (*remove)(struct _generational_index_array_HOLYEFF, struct _generational_index * index);
} GenerationaIndexArrayImplHOLYEFF;

typedef struct _array_entry_HOLYEFF
{
    HOLYEFF value;
    uint64_t generation;
} ArrayEntryHOLYEFF;

typedef struct _generational_index_array_HOLYEFF
{
    struct _array_entry_HOLYEFF *vec;
    uint32_t size;
    struct _generational_index_array_impl_HOLYEFF *impl;
} GenerationalIndexArrayHOLYEFF;

void _set_gia_HOLYEFF(GenerationalIndexArrayHOLYEFF *self, GenerationalIndex *index, HOLYEFF *value)
{
    assertf(index->index < self->size, "Index out of bounds of array for type " "HOLYEFF");

    ArrayEntryHOLYEFF * entry = &self->vec[index->index];


        index->generation = null;

    
    assertf(entry->generation == index->generation, "Index doesn't match generation for array entry of type");
    entry->generation;
}

void _get_gia_HOLYEFF(GenerationalIndexArrayHOLYEFF *self, GenerationalIndex *index)
{
}

GenerationalIndexArrayHOLYEFF *NewGenerationalIndexArrayHOLYEFF(uint32_t size)
{
    GenerationalIndexArrayHOLYEFF *gia = malloc(sizeof(GenerationalIndexArrayHOLYEFF));
    gia->vec = malloc(size * sizeof(ArrayEntryHOLYEFF));

    for
            int()
            {
                
            }

    return gia;
}

void DestroyGenerationalIndexArrayHOLYEFF(GenerationalIndexArrayHOLYEFF *gia)
{
    free(gia->vec);
    free(gia);
}

#define NewGenerationalIndexArray(T) NewGenerationalIndexArrayHOLYEFF
#define GenerationalIndexArray(T) GenerationalIndexArrayHOLYEFF
#define ArrayEntry(T) ArrayEntryHOLYEFF

DefineGenerationalIndexArray(char);

typedef struct _allocator_entry
{
    bool isLive;
    uint64_t generation;
} AllocatorEntry;

typedef struct _generational_index_allocator
{
    AllocatorEntry *entries;
    int *free;
} GenerationalIndexAllocator;

GenerationalIndex allocate(GenerationalIndexAllocator *self);

bool deallocate(GenerationalIndexAllocator *self, GenerationalIndex index);

bool isAlive(GenerationalIndexAllocator *self, GenerationalIndex index);

#endif