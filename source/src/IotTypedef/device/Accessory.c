/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2016-7-25
 *
 * @file   Accessory.c
 *
 * @remark
 *
 */

#include <tiny_malloc.h>
#include <tiny_log.h>
#include "Property.h"
#include "Accessory.h"
#include "Service.h"


#define TAG     "Accessory"

TINY_LOR
static TinyRet Accessory_Construct(Accessory *thiz);

TINY_LOR
static void Accessory_Dispose(Accessory *thiz);

TINY_LOR
static void service_release_handler(void *data, void *ctx)
{
    Service *p = (Service *)data;
    Service_Delete(p);
}

TINY_LOR
Accessory* Accessory_New(void)
{
    Accessory *thiz = NULL;

    do
    {
        thiz = (Accessory *)tiny_malloc(sizeof(Accessory));
        if (thiz == NULL)
        {
            LOG_D(TAG, "tiny_malloc FAILED");
            break;
        }

        if (RET_FAILED(Accessory_Construct(thiz)))
        {
            Accessory_Delete(thiz);
            thiz = NULL;
            break;
        }
    } while (false);

    return thiz;
}

TINY_LOR
static TinyRet Accessory_Construct(Accessory *thiz)
{
    TinyRet ret = TINY_RET_OK;

    RETURN_VAL_IF_FAIL(thiz, TINY_RET_E_ARG_NULL);

    do
    {
        memset(thiz, 0, sizeof(Accessory));

        ret = TinyList_Construct(&thiz->services);
        if (RET_FAILED(ret))
        {
            LOG_D(TAG, "TinyList_Construct FAILED: %s", tiny_ret_to_str( ret));
            break;
        }

        thiz->services.additionalData = thiz;
        TinyList_SetDeleteListener(&thiz->services, service_release_handler, thiz);
    } while (false);

    return ret;
}

TINY_LOR
static void Accessory_Dispose(Accessory *thiz)
{
    RETURN_IF_FAIL(thiz);

    TinyList_Dispose(&thiz->services);
}

TINY_LOR
void Accessory_Delete(Accessory *thiz)
{
    RETURN_IF_FAIL(thiz);

    Accessory_Dispose(thiz);
    tiny_free(thiz);
}

TINY_LOR
void Accessory_InitializeInstanceID(Accessory *thiz, uint16_t aid)
{
    uint16_t iid = 1;
    thiz->iid = aid;

    for (uint32_t j = 0; j < thiz->services.size; ++j)
    {
        Service *s = (Service *) TinyList_GetAt(&thiz->services, j);
        s->iid = iid++;
        s->aiid = thiz->iid;

        for (uint32_t k = 0; k < s->properties.size; ++k)
        {
            Property *p = (Property * )TinyList_GetAt(&s->properties, k);
            p->aiid = thiz->iid;
            p->siid = s->iid;
            p->iid = iid++;
        }
    }
}