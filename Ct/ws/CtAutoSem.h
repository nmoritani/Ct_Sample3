/**
 *  Copyright(c) 2018 Persol AVC Technology.
 *  Element:			CtAutoSem
 */

#ifndef __CtAutoSem_H__
#define __CtAutoSem_H__

#include "kernel.h"

/* セマフォの取得、破棄を自動で行うクラス */
class CtAutoSem : public CtObject
{
public:
	CtAutoSem(ID SemId) : m_SemId(SemId) { wai_sem( m_SemId ); }
	virtual ~CtAutoSem(){ sig_sem( m_SemId ); }
private:
	ID m_SemId;
};

#endif	/* __CtAutoSem_H__ */
