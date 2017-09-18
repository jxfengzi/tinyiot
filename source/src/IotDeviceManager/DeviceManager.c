/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-11-19
 *
 * @file   DeviceManager.c
 *
 * @remark
 *
 */

#include "DeviceManager.h"
#include <tiny_malloc.h>
#include <tiny_log.h>

#define TAG     "DeviceManager"

//TINY_LOR
//DeviceManager *DeviceManager_New(void)
//{
//    DeviceManager *thiz = NULL;
//
//    do
//    {
//        thiz = (DeviceManager *) tiny_malloc(sizeof(DeviceManager));
//        if (thiz == NULL)
//        {
//            LOG_D(TAG, "tiny_malloc FAILED.");
//            break;
//        }
//
//        if (RET_FAILED(DeviceManager_Construct(thiz)))
//        {
//            DeviceManager_Delete(thiz);
//            thiz = NULL;
//            break;
//        }
//    } while (false);
//
//    return thiz;
//}
//
//TINY_LOR
//void DeviceManager_Delete(DeviceManager *thiz)
//{
//    RETURN_IF_FAIL(thiz);
//
//    DeviceManager_Dispose(thiz);
//    tiny_free(thiz);
//}

TINY_LOR
TinyRet DeviceManager_Construct(DeviceManager *thiz)
{
    TinyRet ret = TINY_RET_OK;

    RETURN_VAL_IF_FAIL(thiz, TINY_RET_E_ARG_NULL);

    memset(thiz, 0, sizeof(DeviceManager));
    thiz->started = false;

    return ret;
}

TINY_LOR
void DeviceManager_Dispose(DeviceManager *thiz)
{
    RETURN_IF_FAIL(thiz);

    memset(thiz, 0, sizeof(DeviceManager));
}

TINY_LOR
TinyRet DeviceManager_SetRuntimeImpl(DeviceManager *thiz, DeviceRuntime *impl)
{
    RETURN_VAL_IF_FAIL(thiz, TINY_RET_E_ARG_NULL);
    RETURN_VAL_IF_FAIL(impl, TINY_RET_E_ARG_NULL);

    if (thiz->started)
    {
        return TINY_RET_E_STARTED;
    }

    DeviceRuntime_Copy(&thiz->runtime, impl);

    return TINY_RET_OK;
}

TINY_LOR
TinyRet DeviceManager_Stop(DeviceManager *thiz)
{
    RETURN_VAL_IF_FAIL(thiz, TINY_RET_E_ARG_NULL);

    if (! thiz->started)
    {
        return TINY_RET_E_STOPPED;
    }

    thiz->runtime.Stop(&thiz->runtime);
    thiz->runtime.Destroy(&thiz->runtime);
    thiz->started = false;

    return TINY_RET_OK;
}

TINY_LOR
TinyRet DeviceManager_Run(DeviceManager *thiz, DeviceHost *host)
{
    RETURN_VAL_IF_FAIL(thiz, TINY_RET_E_ARG_NULL);

    if (thiz->started)
    {
        return TINY_RET_E_STARTED;
    }

    thiz->started = true;
    thiz->runtime.Initialize(&thiz->runtime);

    return thiz->runtime.Run(&thiz->runtime, host);
}