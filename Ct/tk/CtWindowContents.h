/**
 *  Copyright(c) 2018 Persol AVC Technology.
 *  Element:			CtWindowContents
 */


#ifndef __CtWindowContents_H__
#define __CtWindowContents_H__

#include "../Include/Ct.h"
#include "../ws/CtObject.h"

class CtWindowContents : public CtObject {
public :
	
protected :
  CtWindowContents(const CtWindowID WindowID) : m_WindowID(WindowID) {
	  setClassType(CtClassType_WindowContents);
  }

public :
    virtual ~CtWindowContents();
	CtWindowID getType() const {
		return m_WindowID;
	}

private :
    CtWindowID		m_WindowID;	
	
};

#endif
