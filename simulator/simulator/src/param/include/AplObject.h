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
/// �A�v���ō쐬������̃N���X�̍ŏ�ʃN���X<br>
/// �� ����<br>
/// �@- �N���X���ʏ��̐���[�N���X�^�ƃI�u�W�F�N�gID(=�C���X�^���XID)]<br>
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
    /// �yFor Foundation Use Only�z<br>
    /// �I�u�W�F�N�gID(=�C���X�^���XID)�𐶐�����
    //## operation generateOid()
    AplOid generateOid();

public :

    ///@brief
    /// �I�u�W�F�N�gID(=�C���X�^���XID)���擾����
    //## operation getOid() const
    inline AplOid getOid() const;

protected :

    ///@brief
    /// �N���X�^��ݒ肷��B<br>
    /// AplObject�̑S�p���N���X�̃R���X�g���N�^����Ă΂�鎖��z��B<br>
    //## operation setClassType(const AplClassType)
    void setClassType(const AplClassType ClassType);

public :

    ///@brief
    /// �N���X�^���擾����B
    //## operation getClassType() const
    inline AplClassType getClassType() const;

protected :

    ///@brief
    /// �R�s�[�R���X�g���N�^
    //## operation AplObject(AplObject)
    AplObject(const AplObject& Obj);
    
    ////    Operations    ////
    
    ////    Attributes    ////

private :

    ///�N���X�^
    AplClassType m_ClassType;		//## attribute m_ClassType
    
    ///�I�u�W�F�N�gID(=�C���X�^���XID)
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
