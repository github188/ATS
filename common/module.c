/**
 *  module.c
 *
 */


#include "osa.h"
#include "core.h"


static osa_list_t   mod_list_head = OSA_LIST_HEAD(mod_list_head);


ats_module_t *ats_module_find(const char *name)
{
    osa_assert(name != NULL);

    ats_module_t    *node   = NULL;
    osa_list_t      *l      = NULL;

    for (l = mod_list_head.next; l != &mod_list_head; l = l->next)
    {
        node = osa_list_entry(l, ats_module_t, list);
        if (!strcmp(node->name, name))
        {
            return node;
        }
    }

    return NULL;
}


osa_err_t ats_module_register(ats_module_t      *m,
                              const osa_char_t  *name, 
                              ats_mops_t        *ops)
{
    osa_assert(name != NULL);

    strncpy(m->name, name, OSA_NAME_MAX-1);
    osa_list_init(&m->list);
    m->ops = ops;

    ats_module_t   *p = NULL;

    if ((p = ats_module_find(m->name)) != NULL)
    {
        ats_log_warn("The module existed: %s\n", m->name);
        return OSA_ERR_ERR;
    }

    ats_log_info("Register new module : name(%s)\n", m->name);
    osa_list_insert_before(&mod_list_head, &m->list);

    return OSA_ERR_OK;
}


osa_err_t ats_module_unregister(const osa_char_t *mod_name)
{
    osa_assert(mod_name != NULL);

    ats_module_t *p = NULL;

    if ((p = ats_module_find(mod_name)) != NULL)
    {
        p->ops->end(p);
        osa_list_remove(&p->list);
        ats_log_info("Unregister bus : name(%s)\n", p->name);
    }

    return OSA_ERR_OK;
}

void ats_module_all_init(int argc, char **argv)
{
    ats_module_t    *node   = NULL;
    osa_list_t      *l      = NULL;

    for (l = mod_list_head.next; l != &mod_list_head; l = l->next)
    {
        node = osa_list_entry(l, ats_module_t, list);

        if (node->ops->begin)
        {
            if (node->ops->begin(node, argc, argv) != OSA_ERR_OK)
            {
                ats_log_error("Failed to begin module (%s)!\n", node->name);
                continue;
            }
            ats_log_info("Succeed to start module: name(%s)\n", node->name);
        }
    }
}

void ats_module_all_fini()
{
    ats_module_t    *node   = NULL;
    osa_list_t      *l      = NULL;

    for (l = mod_list_head.next; l != &mod_list_head; l = l->next)
    {
        node = osa_list_entry(l, ats_module_t, list);
        
        ats_log_info("Finalize module : name(%s)\n", node->name);
        if (node->ops->end)
        {
            node->ops->end(node);
        }
    }
}
