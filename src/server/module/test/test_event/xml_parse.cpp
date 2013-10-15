/*
 * cat_test.h
 *
 * Copyright (C) TuoAn
 *
 */


#include "xml_parse.h"
#include "data.h"
#include "log.h"
#include "tinyxml.h"


#ifdef __cplusplus
extern "C" {
#endif


TiXmlElement *_getTestPointRoot(osa_char_t *xmlfile, char *node_name)
{
    TiXmlElement    *root = NULL;
    TiXmlDocument   *doc = new TiXmlDocument(xmlfile);

    if (doc->LoadFile()!=true)
    {
        ats_log_error("Failed to load xml: %s\n", xmlfile);
        return NULL;
    }

    if ((root = doc->RootElement())==NULL)
    {
        ats_log_error("Failed to get xml root: %s\n", xmlfile);
        return NULL;
    }

    TiXmlElement    *tmp = root->FirstChildElement("test_point");
    TiXmlAttribute  *attr = NULL;

    while (tmp)
    {
        attr = tmp->FirstAttribute();
        if (!strcmp(attr->Value(), node_name))
        {
            return tmp;
        }
        tmp = tmp->NextSiblingElement("test_point");
    }

    return NULL;
}



static TEST_Dummy  dummy[2];
osa_err_t   dummyTestParse(ats_tevent_t *tp, osa_char_t *cf)
{
    strcpy(dummy[0].dummyIn, "hello");
    strcpy(dummy[0].dummyExpOut, "world");

    strcpy(dummy[1].dummyIn, "test");
    strcpy(dummy[1].dummyExpOut, "first");

    tp->attr.tcb.tc_num = 2;
    tp->attr.tcb.tc_size = sizeof(TEST_Dummy);
    tp->attr.tcb.tc_cases = dummy;

    return OSA_ERR_OK;
}


#ifdef __cplusplus
}
#endif
