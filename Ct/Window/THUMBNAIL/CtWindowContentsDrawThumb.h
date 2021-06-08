#ifndef __CtWindowContentsDrawThumb_H__
#define __CtWindowContentsDrawThumb_H__

#include "CtWindowContentsThumbCommon.h"
#include "CtWindowContentsThumb.h"

class CtWindowContentsDrawThumb : public CtWindowContentsThumb {
public :
	CtWindowContentsDrawThumb(const CtWindowID WindowID);
	CtWindowContentsDrawThumb(CtWindowContentsDrawThumb& ContentsDrawThumb);
	~CtWindowContentsDrawThumb();
	
	ContentsThumbInfo getDrawThumbInfo();
	void setDrawThumbInfo(ContentsThumbInfo& info);
	
private :
	ContentsThumbInfo m_DrawThumbInfo;
	
};

#endif
