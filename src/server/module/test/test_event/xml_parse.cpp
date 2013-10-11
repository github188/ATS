/*
 * cat_test.h
 *
 * Copyright (C) TuoAn
 *
 */


#include "xml_parse.h"
#include "data.h"
#include "_log.h"
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
        TP_LogError("Failed to load xml: %s\n", xmlfile);
        return NULL;
    }

    if ((root = doc->RootElement())==NULL)
    {
        TP_LogError("Failed to get xml root: %s\n", xmlfile);
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
osa_err_t   dummyTestParse(ATS_TestEvent *tp, osa_char_t *cf)
{
    osa_uint32_t    i;

    strcpy(dummy[0].dummyIn, "hello");
    strcpy(dummy[0].dummyExpOut, "world");

    strcpy(dummy[1].dummyIn, "test");
    strcpy(dummy[1].dummyExpOut, "first");

    tp->testCaseBox.caseNum = 2;
    tp->testCaseBox.caseSize = sizeof(TEST_Dummy);
    tp->testCaseBox.privData = dummy;

    return OSA_ERR_OK;
}


#ifdef __cplusplus
}
#endif
