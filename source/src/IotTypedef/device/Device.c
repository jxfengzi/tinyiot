/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2016-7-25
 *
 * @file   Device.c
 *
 * @remark
 *
 */

#include <tiny_malloc.h>
#include <tiny_log.h>
#include <operation/PropertyOperation.h>
#include <status/IotStatus.h>
#include "Property.h"
#include "Device.h"
#include "Service.h"
#include "Action.h"

#define TAG     "Device"

TINY_LOR
static TinyRet Device_Construct(Device *thiz);

TINY_LOR
static void Device_Dispose(Device *thiz);

TINY_LOR
static void service_release_handler(void *data, void *ctx)
{
    Service_Delete((Service *)data);
}

TINY_LOR
Device* Device_New(void)
{
    Device *thiz = NULL;

    do
    {
        thiz = (Device *)tiny_malloc(sizeof(Device));
        if (thiz == NULL)
        {
            LOG_D(TAG, "tiny_malloc FAILED");
            break;
        }

        if (RET_FAILED(Device_Construct(thiz)))
        {
            Device_Delete(thiz);
            thiz = NULL;
            break;
        }
    } while (false);

    return thiz;
}

TINY_LOR
static TinyRet Device_Construct(Device *thiz)
{
    TinyRet ret = TINY_RET_OK;

    RETURN_VAL_IF_FAIL(thiz, TINY_RET_E_ARG_NULL);

    do
    {
        memset(thiz, 0, sizeof(Device));

        ret = TinyList_Construct(&thiz->services, service_release_handler, thiz);
        if (RET_FAILED(ret))
        {
            LOG_D(TAG, "TinyList_Construct FAILED: %s", tiny_ret_to_str( ret));
            break;
        }
        thiz->services.context = thiz;
    } while (false);

    return ret;
}

TINY_LOR
static void Device_Dispose(Device *thiz)
{
    RETURN_IF_FAIL(thiz);

    TinyList_Dispose(&thiz->services);
}

TINY_LOR
void Device_Delete(Device *thiz)
{
    RETURN_IF_FAIL(thiz);

    Device_Dispose(thiz);
    tiny_free(thiz);
}

TINY_LOR
bool Device_CheckHandler(Device *thiz)
{
    RETURN_VAL_IF_FAIL(thiz, false);

    LOG_D(TAG, "Device_CheckHandler");

    if (thiz->onSet == NULL)
    {
        LOG_E(TAG, "Property Setter is null");
        return false;
    }

    if (thiz->onGet == NULL)
    {
        LOG_E(TAG, "Property Getter is null");
        return false;
    }

    if (thiz->onInvoke == NULL)
    {
        LOG_E(TAG, "Action Invocation is null");
    }

    return true;
}