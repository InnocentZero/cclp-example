#include "container.h"
#include <stdio.h>
#include <stdlib.h>

#ifndef TYPE
#error "Template argument missing"
#define TYPE int
#endif // !TYPE

struct FN_CREATE(deque, TYPE) {
        size_t size;
        size_t capacity;
        TYPE *buffer;
        size_t front;
        size_t back;
};

static void FN_CREATE(for_each_in_deque,
                      TYPE)(struct FN_CREATE(deque, TYPE) * buf,
                            void func(TYPE))
{

        for (size_t i = buf->front + 1; i < buf->capacity + buf->back + 1;
             i++) {
                func(buf->buffer[i % buf->capacity]);
        }
};

static void FN_CREATE(__double_capacity_deque,
                      TYPE)(struct FN_CREATE(deque, TYPE) * buf)
{
        TYPE *tmp = (TYPE *)malloc((2 * buf->capacity + 1) * sizeof(TYPE));
        BUFCHK(tmp);
        for (size_t i = buf->front + 1, j = 1;
             i < buf->capacity + buf->back && j < buf->size + 1; i++, j++) {
                tmp[j] = buf->buffer[i % buf->capacity];
        }
        free(buf->buffer);
        buf->buffer = tmp;
        buf->capacity = 2 * buf->capacity + 1;
        buf->front = 0;
        buf->back = buf->size + 1;
};

static void FN_CREATE(__halve_capacity_vector,
                      TYPE)(struct FN_CREATE(deque, TYPE) * buf)
{
        TYPE *tmp = (TYPE *)malloc(buf->capacity / 2 * sizeof(TYPE));
        BUFCHK(tmp);
        for (size_t i = buf->front + 1, j = 1;
             i < buf->capacity + buf->back && j < buf->size + 1; i++, j++) {
                tmp[j] = buf->buffer[i % buf->capacity];
        }
        free(buf->buffer);
        buf->buffer = tmp;
        buf->capacity = buf->capacity / 2;
        buf->front = 0;
        buf->back = buf->size + 1;
};

static struct FN_CREATE(deque, TYPE) FN_CREATE(deque_create, TYPE)(void)
{
        struct FN_CREATE(deque, TYPE) tmp = {
            .size = 0,
            .capacity = 2 * 16 + 1,
            .buffer = (TYPE *)malloc((2 * 16 + 1) * sizeof(TYPE)),
            .front = 0,
            .back = 1,
        };
        return tmp;
};

static void FN_CREATE(deque_push_back,
                      TYPE)(struct FN_CREATE(deque, TYPE) * buf, TYPE value)
{
        if (buf->size == buf->capacity) {
                FN_CREATE(__double_capacity_deque, TYPE)(buf);
        }
        buf->buffer[buf->back] = value;
        buf->back = buf->capacity == buf->back + 1 ? 0 : buf->back + 1;
        buf->size++;
};

static void FN_CREATE(deque_push_front,
                      TYPE)(struct FN_CREATE(deque, TYPE) * buf, TYPE value)
{
        if (buf->size == buf->capacity) {
                FN_CREATE(__double_capacity_deque, TYPE)(buf);
        }
        buf->buffer[buf->front] = value;
        buf->front = buf->front == 0 ? buf->capacity - 1 : buf->front - 1;
        buf->size++;
};

static TYPE FN_CREATE(deque_pop_front,
                      TYPE)(struct FN_CREATE(deque, TYPE) * buf)
{
        if (buf->capacity > 33 && buf->size < buf->capacity / 4) {
                FN_CREATE(__halve_capacity_vector, TYPE)(buf);
        }
        buf->front = buf->front + 1 == buf->capacity ? 0 : buf->front + 1;
        buf->size--;
        return buf->buffer[buf->front];
};
static TYPE FN_CREATE(deque_pop_back, TYPE)(struct FN_CREATE(deque, TYPE) * buf)
{
        if (buf->capacity > 33 && buf->size < buf->capacity / 4) {
                FN_CREATE(__halve_capacity_vector, TYPE)(buf);
        }
        buf->back = buf->back == 0 ? buf->capacity - 1 : buf->back - 1;
        buf->size--;
        return buf->buffer[buf->back];
};

static inline TYPE *FN_CREATE(deque_peek_front,
                              TYPE)(struct FN_CREATE(deque, TYPE) * buf)
{
        return buf->buffer +
               (buf->front + 1 == buf->capacity ? 0 : buf->front + 1);
}

static inline TYPE *FN_CREATE(deque_peek_back,
                              TYPE)(struct FN_CREATE(deque, TYPE) * buf)
{
        return buf->buffer +
               (buf->back == 0 ? buf->capacity - 1 : buf->back - 1);
}

static inline void FN_CREATE(deque_free,
                             TYPE)(struct FN_CREATE(deque, TYPE) * q)
{
        free(q->buffer);
};

#undef TYPE
