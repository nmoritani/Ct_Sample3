#ifndef __CtWindowContentsPlayControlState_H__
#define __CtWindowContentsPlayControlState_H__

#include "CtWindowContents.h"

class CtWindowContentsPlayControlState : public CtWindowContents {
public :
	typedef enum PressType {
		Invalid,
		Press,
		LongPress,
		Repeat,
		Release,
	}PressType;

	CtWindowContentsPlayControlState(const CtWindowID WindowID);
	CtWindowContentsPlayControlState(const CtWindowContentsPlayControlState& contentsFile);
	virtual ~CtWindowContentsPlayControlState();

	void setPressType( PressType type );
	PressType getPressType();

	void setProgress( int seek );
	int getProgress();

private:
	PressType m_PressType;

	int m_Progres;

};

#endif
