/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2016-7-25
 *
 * @file   Property.h
 *
 * @remark
 *
 */

#ifndef __PROPERTY_H__
#define __PROPERTY_H__

#include "tiny_base.h"
#include "api/iot_api.h"
#include "unit/Unit.h"
#include "urn/Urn.h"
#include "data/Data.h"
#include "device/access/Access.h"
#include <device/handler/PropertyOnControl.h>
#include <operation/PropertyOperation.h>
#include <JsonValue.h>
#include <device/format/Format.h>
#include <device/constraint/ValueList.h>
#include <device/constraint/ValueRange.h>

TINY_BEGIN_DECLS


typedef struct _Property
{
    uint16_t            iid;
    Urn                 type;
    Format              format;
    Access              access;
    ValueList         * valueList;
    ValueRange        * valueRange;
    PropertyOnGet       onGet;
    PropertyOnSet       onSet;

    //    Unit                unit;
    //    Data                data;
    //    bool                changed;
    //    int                 status;
    //    uint8_t             operation;
} Property;

IOT_API
TINY_LOR
Property* Property_New(void);

IOT_API
TINY_LOR
void Property_Delete(Property *thiz);

IOT_API
TINY_LOR
void Property_TryRead(Property *thiz, PropertyOperation *o);

IOT_API
TINY_LOR
void Property_TryWrite(Property *thiz, PropertyOperation *o);

IOT_API
TINY_LOR
bool Property_CheckValue(Property *thiz, JsonValue* value);



TINY_END_DECLS

#endif /* __PROPERTY_H__ */
