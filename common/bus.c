/**
 *  bus.c 
 *
 */
 
#include "osa.h"
#include "core.h"


static osa_list_t   bus_list_head = OSA_LIST_HEAD(bus_list_head);


ats_bus_t *ats_bus_find(const osa_char_t *bus_name)
{
    osa_assert(bus_name != NULL);

    ats_bus_t   *node   = NULL;
    osa_list_t  *l      = NULL;

    for (l = bus_list_head.next; l != &bus_list_head; l = l->next)
    {
        node = osa_list_entry(l, ats_bus_t, list);
        if (!strcmp(node->name, bus_name))
        {
            return node;
        }
    }
    
    return NULL;
}

osa_err_t ats_bus_register(ats_bus_t *bus, const osa_char_t *bus_name, ats_bus_ops_t *ops)
{
    osa_assert(bus_name != NULL);
    
    strncpy(bus->name, bus_name, OSA_NAME_MAX-1);
    osa_list_init(&bus->list);
    osa_list_init(&bus->ele_list_head);
    bus->ops = ops;
    
    ats_bus_t   *p = NULL;
    
    if ((p = ats_bus_find(bus_name)) != NULL)
    {
        ats_log_warn("Replace Device : name(%s)\n", bus->name);
        p = bus;
    }
    else
    {
        ats_log_info("Register new bus : name(%s)\n", bus->name);
        osa_list_insert_before(&bus_list_head, &bus->list);
    }
    
    return OSA_ERR_OK;
}


osa_err_t ats_bus_unregister(const osa_char_t *bus_name)
{
    osa_assert(bus_name != NULL);
    
    ats_bus_t *p = NULL;
    
    if ((p = ats_bus_find(bus_name)) != NULL)
    {
        osa_list_remove(&p->list);
        if (p->ops && p->ops->remove)
        {
            p->ops->remove(p);
        }
        ats_log_info("Unregister bus : name(%s)\n", p->name);
    }
    
    return OSA_ERR_OK;
}
