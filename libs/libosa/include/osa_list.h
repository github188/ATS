/**
 *  osa_list.h
 *
 */


#ifndef __OSA_LIST_H__
#define __OSA_LIST_H__


#include "osa_types.h"


#ifdef __cplusplus
extern "C"
{
#endif


typedef struct _LIST_NODE
{
    struct _LIST_NODE *prev;
    struct _LIST_NODE *next;
} osa_list_t;


static osa_inline void osa_list_init(osa_list_t *l)
{
    l->next = l->prev = l;
}

static osa_inline void osa_list_insert_after(osa_list_t *l, osa_list_t *n)
{
    l->next->prev = n;
    n->next = l->next;

    l->next = n;
    n->prev = l;
}

static osa_inline void osa_list_insert_before(osa_list_t *l, osa_list_t *n)
{
    l->prev->next = n;
    n->prev = l->prev;

    l->prev = n;
    n->next = l;
}

static osa_inline void osa_list_remove(osa_list_t *n)
{
    n->next->prev = n->prev;
    n->prev->next = n->next;

    n->next = n->prev = n;
}

static osa_inline int osa_list_is_empty(const osa_list_t *l)
{
    return l->next == l;
}


#define osa_list_entry(node, type, member) \
    ((type *)((char *)(node) - (unsigned long)(&((type *)0)->member)))


#ifdef __cplusplus
}
#endif

#endif