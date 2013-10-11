/**
 *  bus.h 
 *
 */
 
 
#ifndef __BUS_H__
#define __BUS_H__


#include "class.h"
#include "osa.h"


#ifdef __cplusplus
extern "C"
{
#endif


typedef struct _ATS_BUS_ATTR
{
    
}ats_busattr_t;

typedef struct _ATS_BUS_OPERAIONTS
{
    osa_bool_t  (*match)(void *bus_element, void *match_element);
    void        (*remove)();
}ats_bus_ops_t;


struct ATS_BUS_CLASS
{
    osa_char_t      name[OSA_NAME_MAX];
    ats_busattr_t   attr;
    
    osa_list_t      list;           // 总线链表节点
    osa_list_t      ele_list_head;       // 总线中保存的元素的链表头节点
    
    ats_bus_ops_t   *ops;
};


ATS_Bus     *ats_bus_find(const osa_char_t *name);
osa_err_t   ats_bus_register(ats_bus_t *bus, const osa_char_t *name, ats_bus_ops_t *ops);
osa_err_t   ats_bus_unregister(ats_bus_t *bus);

void        ats_bus_foreach(ats_bus_t *bus, void (*foreach)(void *ele));


#ifdef __cplusplus
}
#endif

#endif