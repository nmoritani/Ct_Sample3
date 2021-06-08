#ifndef __CtWindowContentsVersionDisp_H__
#define __CtWindowContentsVersionDisp_H__

#include "CtWindowContents.h"

class CtWindowContentsVersionDisp : public CtWindowContents {
public :
	#define Version_Size 5

	CtWindowContentsVersionDisp(const CtWindowID WindowID);
	virtual ~CtWindowContentsVersionDisp();

	void setNextVersion( unsigned char *version );
	unsigned char *getNextVersion();

private:
	unsigned char m_Version[Version_Size];
};

#endif
