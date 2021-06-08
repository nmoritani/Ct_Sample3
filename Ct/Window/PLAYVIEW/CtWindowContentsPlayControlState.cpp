#include "CtWindowContentsPlayControlState.h"

CtWindowContentsPlayControlState::CtWindowContentsPlayControlState(const CtWindowID WindowID) : CtWindowContents(WindowID) {
	m_PressType = Invalid;
	m_Progres = 0;
}

CtWindowContentsPlayControlState::CtWindowContentsPlayControlState(const CtWindowContentsPlayControlState& contentsFile) : CtWindowContents(contentsFile.getType()) {
	m_PressType = contentsFile.m_PressType;
	m_Progres = contentsFile.m_Progres;
}

CtWindowContentsPlayControlState::~CtWindowContentsPlayControlState() {
}

void CtWindowContentsPlayControlState::setPressType( PressType type ) {
	m_PressType = type;
}

CtWindowContentsPlayControlState::PressType CtWindowContentsPlayControlState::getPressType() {
	return m_PressType;
}

void CtWindowContentsPlayControlState::setProgress( int seek ){
	m_Progres = seek;
}

int CtWindowContentsPlayControlState::getProgress(){
	return m_Progres;
}
