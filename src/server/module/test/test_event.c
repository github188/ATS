/**
 * test_event.h
 *
 */

#include "osa.h"
#include "log.h"
#include "config.h"
#include "test_event.h"
#include "test_drv.h"


static osa_dll_t        dll;


osa_err_t ats_tevent_plugin_load(const osa_char_t *plugin_file)
{
#if 0
    if (osa_file_is_exist(plugin_file != OSA_TRUE))
    {
        ats_log_error("File not exist : %s\n", plugin_file);
        return OSA_ERR_ERR;
    }
#endif

    if (osa_dll_load(&dll, plugin_file) != OSA_ERR_OK)
    {
        ats_log_error("Failed to load %s!\n", plugin_file);
        return OSA_ERR_ERR;
    }

    return OSA_ERR_OK;
}


ats_tevent_t *ats_tevent_get(const osa_char_t *tevent_name)
{
    typedef void *(*beginItr)();
    typedef void *(*endItr)();
    typedef void *(*nextItr)(void *curr);
    typedef void ** iterator;

    beginItr    begin;
    endItr      end;
    nextItr     next;
    void *entry = NULL;

    if ((entry = osa_dll_sym(&dll, "tableGetBegin")) == NULL)
    {
        ats_log_error("Can not found tableGetBegin in file %s!\n", ATS_TEST_EVENT_PLUGIN);
        return OSA_ERR_ERR;
    }
    begin = (beginItr)entry;

    if ((entry = osa_dll_sym(&dll, "tableGetEnd")) == NULL)
    {
        ats_log_error("Can not found tableGetEnd in file %s!\n", ATS_TEST_EVENT_PLUGIN);
        return OSA_ERR_ERR;
    }
    end = (endItr)entry;

    if ((entry = osa_dll_sym(&dll, "tableGetNext")) == NULL)
    {
        ats_log_error("Can not found tableGetNext in file %s!\n", ATS_TEST_EVENT_PLUGIN);
        return OSA_ERR_ERR;
    }
    next = (nextItr)entry;

    iterator    itr = NULL;
    ats_tevent_t *node = NULL;

    for (itr = begin(); itr != end(); itr = next(itr))
    {
        node = ( ats_tevent_t *)*itr;
        if (!strcmp(node->name, tevent_name))
        {
            return node;
        }
    }

    return NULL;
}


void ats_tevent_plugin_unload()
{
    osa_dll_unload(&dll);
}


ats_tevent_t    *ats_tevent_find(ats_tdrv_t *drv, const osa_char_t *tevent_name)
{
    osa_assert(tevent_name != NULL);
    
    ats_tevent_t *node = NULL;
    osa_list_t   *l = NULL;
    
    for (l = drv->tevent_list_head.next; l != &drv->tevent_list_head; l=l->next)
    {
        node = osa_list_entry(l, ats_tevent_t, list);
        if (!strcmp(node->name, tevent_name))
        {
            return node;
        }
    }
    
    return NULL;
}

osa_err_t       ats_tevent_register(ats_tdrv_t *drv, ats_tevent_t *tevent)
{
    ats_tevent_t *p = NULL;
    
    if ((p = ats_tevent_find(drv, tevent)) != NULL)
    {
        p = tevent;
    }
    else
    {
        osa_list_insert_before(&drv->tevent_list_head, &tevent->list);
    }
    return OSA_ERR_OK;
}

osa_err_t       ats_tevent_unregister(ats_tdrv_t *drv, const osa_char_t *tevent_name)
{
    ats_tevent_t *p = NULL;
    
    if ((p = ats_tevent_find(drv, tevent_name)) != NULL)
    {
        osa_list_remove(&p->list);
    }
    
    return OSA_ERR_OK;
}
