#ifndef __CtWindowContentsPressLevel_H__
#define __CtWindowContentsPressLevel_H__

#include "CtWindowContents.h"

class CtWindowContentsPressLevel : public CtWindowContents {
public :
	typedef enum _ContentsPressLevel {
		Level1,
		Level2,
		Level3,
		Level4,
	} ContentsPressLevel;

	CtWindowContentsPressLevel(const CtWindowID WindowID);
	CtWindowContentsPressLevel(const CtWindowID WindowID, ContentsPressLevel level);
	CtWindowContentsPressLevel(CtWindowContentsPressLevel& contents);
	virtual ~CtWindowContentsPressLevel();

	void setLabel(ContentsPressLevel label);
	ContentsPressLevel getLabel();
	void setLevel(ContentsPressLevel level);
	ContentsPressLevel getLevel();

private:
	ContentsPressLevel m_Level;

};

#endif
