/**
 *  Copyright (c) 2009-2010 Panasonic Corporation
 *  Rhapsody Version:	7.5.1
 *  Element:			AplOid
 */


#ifndef Foundation_AplObject_H
#define Foundation_AplObject_H

#include <oxf.h>
#include "kernel.h"
#include "AplClassType.h"
typedef unsigned int AplOid;

//## package Foundation

//## class AplObject
///@brief 
/// アプリで作成する実体クラスの最上位クラス<br>
/// ■ 役割<br>
/// 　- クラス識別情報の生成[クラス型とオブジェクトID(=インスタンスID)]<br>
class AplObject {
    ////    Constructors and destructors    ////
    
protected :

    //## operation AplObject()
    AplObject();

public :

    //## operation ~AplObject()
    virtual ~AplObject();

private :

    ///@brief
    /// 【For Foundation Use Only】<br>
    /// オブジェクトID(=インスタンスID)を生成する
    //## operation generateOid()
    AplOid generateOid();

public :

    ///@brief
    /// オブジェクトID(=インスタンスID)を取得する
    //## operation getOid() const
    inline AplOid getOid() const;

protected :

    ///@brief
    /// クラス型を設定する。<br>
    /// AplObjectの全継承クラスのコンストラクタから呼ばれる事を想定。<br>
    //## operation setClassType(const AplClassType)
    void setClassType(const AplClassType ClassType);

public :

    ///@brief
    /// クラス型を取得する。
    //## operation getClassType() const
    inline AplClassType getClassType() const;

protected :

    ///@brief
    /// コピーコンストラクタ
    //## operation AplObject(AplObject)
    AplObject(const AplObject& Obj);
    
    ////    Operations    ////
    
    ////    Attributes    ////

private :

    ///クラス型
    AplClassType m_ClassType;		//## attribute m_ClassType
    
    ///オブジェクトID(=インスタンスID)
    const AplOid m_Oid;		//## attribute m_Oid
    
    static AplOid m_OidOrigin;		//## attribute m_OidOrigin

public :

    static const AplOid OidInvalid = 0;		//## attribute OidInvalid
};

inline AplOid AplObject::getOid() const {
    //#[ operation getOid() const
    return m_Oid;
    //#]
}

inline AplClassType AplObject::getClassType() const {
    //#[ operation getClassType() const
    return m_ClassType;
    //#]
}

#endif
