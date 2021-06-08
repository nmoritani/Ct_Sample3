/**
 *  Copyright(c) 2018 Persol AVC Technology.
 *  Element:			CtMmlLayout
 */

// MML専用Layout
// @brief MML動作中のフラグ管理
// @brief MML動作対象時のColor変更

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
