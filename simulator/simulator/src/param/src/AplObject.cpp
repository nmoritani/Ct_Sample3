/**
 *  Copyright (c) 2009-2010 Panasonic Corporation
 *  Rhapsody Version: 7.5.1
 *  Element:          AplObject
 */


#include "AplObject.h"
//## package Foundation

//## class AplObject
AplOid AplObject::m_OidOrigin(0);

AplObject::AplObject() : m_Oid(0) {
    //#[ operation AplObject()
    //#]
}

AplObject::~AplObject() {
    //#[ operation ~AplObject()
    //#]
}


void AplObject::setClassType(const AplClassType ClassType) {
    //#[ operation setClassType(const AplClassType)
    m_ClassType = ClassType;
    return;
    //#]
}

AplObject::AplObject(const AplObject& Obj) : m_Oid(0), m_ClassType(Obj.getClassType()) {
    //#[ operation AplObject(AplObject)
    //#]
}
