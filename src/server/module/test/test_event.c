/**
 * test_event.h
 *
 */

#include "osa.h"
#include "test_event.h"
#include "log.h"


static osa_dll_t        dll;


osa_err_t ats_tevent_plugin_load(const osa_char_t *plugin_file)
{
    
}

void ats_tevent_plugin_unload()
{
    
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
        ats_log_error("Can not found tableGetBegin in file %s!\n", TEST_POINT_PLUGIN);
        return OSA_ERR_ERR;
    }
    begin = (beginItr)entry;

    if ((entry = osa_dll_sym(&dll, "tableGetEnd")) == NULL)
    {
        ats_log_error("Can not found tableGetEnd in file %s!\n", TEST_POINT_PLUGIN);
        return OSA_ERR_ERR;
    }
    end = (endItr)entry;

    if ((entry = osa_dll_sym(&dll, "tableGetNext")) == NULL)
    {
        ats_log_error("Can not found tableGetNext in file %s!\n", TEST_POINT_PLUGIN);
        return OSA_ERR_ERR;
    }
    next = (nextItr)entry;

    iterator    itr = NULL;
    ats_tevent_t *node = NULL;

    for (itr = begin(); itr != end(); itr = next(itr))
    {
        node = ( ats_tevent_t *)*itr;
        if (!strcmp(node->name, name))
        {
            return node;
        }
    }

    return NULL;
}

osa_err_t ats_tevent_plugin_load(const osa_char_t *plugin_file)
{
    if (osa_file_is_exist(plugin_file != OSA_TRUE)
    {
        ats_log_error("File not exist : %s\n", plugin_file);
        return OSA_ERR_ERR;
    }

    if (osa_dll_load(&dll, plugin_file) != OSA_ERR_OK)
    {
        ats_log_error("Failed to load %s!\n", plugin_file);
        return OSA_ERR_ERR;
    }

    return OSA_ERR_OK;
}

void ats_tevent_plugin_unload()
{
    osa_dll_load(&dll);
}
 
