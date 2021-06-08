/**
 *  Copyright(c) 2018 Persol AVC Technology.
 *  Element:          CtMmlLayout
 */

#include "CtMmlLayout.h"

CtMmlLayout::CtMmlLayout() : CtLayout() , m_bMmlAct(false){
	setColor(CtColor::Trans);
}

bool CtMmlLayout::setMmlAct(bool bMmlAct) {
	if (bMmlAct == m_bMmlAct) return false;

	m_bMmlAct = bMmlAct;
	if (bMmlAct == true) {
		return this->setColor(CtColor::orange);
	}
	else {
		return this->setColor(CtColor::Trans);
	}
}

bool CtMmlLayout::getMmlAct() {
	return m_bMmlAct;
}
