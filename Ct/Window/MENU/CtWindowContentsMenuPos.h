#ifndef __CtWindowContentsMenuPos_H__
#define __CtWindowContentsMenuPos_H__

#include "CtWindowContents.h"

class CtWindowContentsMenuPos : public CtWindowContents {
public :
	
	CtWindowContentsMenuPos(const CtWindowID WindowID, int width, int oldwidth);
	virtual ~CtWindowContentsMenuPos();

	void setDate(int width);
	int getWidth();

private:
	int m_Width;

};

#endif
