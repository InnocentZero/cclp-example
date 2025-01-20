#include "container.h"
#include <stdio.h>
#include <stdlib.h>

#ifndef TYPE
#error "Template argument missing"
#define TYPE int
#endif // !TYPE

struct FN_CREATE(vec, TYPE) {
        size_t size;
        size_t capacity;
        TYPE *buffer;
};

static void FN_CREATE(double_capacity_vector,
                      TYPE)(struct FN_CREATE(vec, TYPE) * buf)
{
        TYPE *tmp =
            (TYPE *)realloc(buf->buffer, 2 * buf->capacity * sizeof(TYPE));
        BUFCHK(tmp);
        buf->buffer = tmp;
        buf->capacity = 2 * (buf->capacity);
};

static void FN_CREATE(halve_capacity_vector,
                      TYPE)(struct FN_CREATE(vec, TYPE) * buf)
{

        TYPE *tmp =
            (TYPE *)realloc(buf->buffer, buf->capacity / 2 * sizeof(TYPE));
        BUFCHK(tmp);
        buf->buffer = tmp;
        buf->capacity = buf->capacity / 2;
};

static struct FN_CREATE(vec, TYPE) FN_CREATE(vec_create, TYPE)(void)
{
        struct FN_CREATE(vec, TYPE) tmp = {
            .size = 0,
            .capacity = 32,
            .buffer = (TYPE *)malloc((32) * sizeof(TYPE)),
        };
        return tmp;
};

static void FN_CREATE(vec_push_back, TYPE)(struct FN_CREATE(vec, TYPE) * buf,
                                           TYPE value)
{
        if (buf->size == buf->capacity) {
                FN_CREATE(double_capacity_vector, TYPE)(buf);
        }
        buf->buffer[buf->size] = value;
        buf->size++;
};

static TYPE FN_CREATE(vec_pop_back, TYPE)(struct FN_CREATE(vec, TYPE) * buf)
{
        buf->size--;
        if (buf->capacity > 32 && buf->size == buf->capacity / 4) {
                FN_CREATE(halve_capacity_vector, TYPE)(buf);
        }
        return buf->buffer[buf->size];
};

static inline TYPE *FN_CREATE(vec_at, TYPE)(struct FN_CREATE(vec, TYPE) * buf,
                                            size_t index)
{
        return buf->buffer + index;
}

static inline void FN_CREATE(vec_free, TYPE)(struct FN_CREATE(vec, TYPE) * q)
{
        free(q->buffer);
};

#undef TYPE
