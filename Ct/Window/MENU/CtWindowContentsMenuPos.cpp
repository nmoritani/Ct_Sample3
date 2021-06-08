#include "CtWindowContentsMenuPos.h"
#include "CtMenuInfo.h"

CtWindowContentsMenuPos::CtWindowContentsMenuPos(const CtWindowID WindowID, int width,int oldwidth) :
	CtWindowContents(WindowID),
	m_Width(126)
{
	short hierarchy = CtMenuInfo::getHierarchy(WindowID);
	if (hierarchy == 0) {
		m_Width = oldwidth;
	}
	else {
		m_Width += (hierarchy - 1) * 100;
	}

	m_Width += width;
}

CtWindowContentsMenuPos::~CtWindowContentsMenuPos() {
}

void CtWindowContentsMenuPos::setDate(int width)
{
	m_Width = width;
}
int CtWindowContentsMenuPos::getWidth() {
	return m_Width;
}
