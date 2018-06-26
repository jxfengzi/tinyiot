/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2016-7-25
 *
 * @file   Device.h
 *
 * @remark
 *
 */

#ifndef __DEVICE_H__
#define __DEVICE_H__

#include "tiny_base.h"
#include "api/iot_api.h"
#include "urn/Urn.h"
#include "constraint/typedef_constraint.h"
#include <TinyList.h>
#include <device/handler/PropertyOnControl.h>
#include <device/handler/ActionOnInvoke.h>
#include <device/handler/DeviceIdentifyListener.h>
#include <operation/PropertyOperations.h>
#include <operation/ActionOperation.h>

TINY_BEGIN_DECLS


struct _Device
{
    char                        did[DEVICE_ID_LENGTH + 1];
    char                        ltsk[DEVICE_LTSK_LENGTH + 1];
    TinyList                    services;
    TinyList                    children;
    TinyList                    changedObservers;
    DeviceIdentifyListener      identifyListener;
    void                      * context;
};

typedef struct _Device Device;

IOT_API
TINY_LOR
Device* Device_New(void);

IOT_API
TINY_LOR
void Device_Delete(Device *thiz);

IOT_API
TINY_LOR
void Device_SetLtsk(Device *thiz, const char *ltsk);

IOT_API
TINY_LOR
void Device_InitializeIID(Device *thiz, uint16_t iid);

IOT_API
TINY_LOR
void Device_SetHandler(Device *thiz, PropertyOnGet onGet, PropertyOnSet onSet, ActionOnInvoke onInvoke);

IOT_API
TINY_LOR
bool Device_CheckHandler(Device *thiz);

IOT_API
TINY_LOR
void Device_TryReadProperties(Device *thiz, PropertyOperations *operations);

IOT_API
TINY_LOR
void Device_TryWriteProperties(Device *thiz, PropertyOperations *operations);

IOT_API
TINY_LOR
void Device_TryInvokeAction(Device *thiz, ActionOperation *operation);


TINY_END_DECLS

#endif /* __DEVICE_H__ */