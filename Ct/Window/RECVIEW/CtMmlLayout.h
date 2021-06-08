/**
 *  Copyright(c) 2018 Persol AVC Technology.
 *  Element:			CtMmlLayout
 */

// MML��pLayout
// @brief MML���쒆�̃t���O�Ǘ�
// @brief MML����Ώێ���Color�ύX

#ifndef __CtMmlLayout_H__
#define __CtMmlLayout_H__

#include "CtLayout.h"
#include "CtColor.h"

class CtMmlLayout : public CtLayout {
public:
	CtMmlLayout();
	
	bool setMmlAct(bool bMmlAct);
	bool getMmlAct();
private:
	CtFontSet m_Fset;
	bool m_bMmlAct;
};
#endif
