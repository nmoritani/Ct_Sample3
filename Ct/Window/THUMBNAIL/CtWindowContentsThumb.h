#ifndef __CtWindowContentsThumb_H__
#define __CtWindowContentsThumb_H__

#include "CtWindowContents.h"

class CtWindowContentsThumb : public CtWindowContents {
public :
	typedef enum ContentsThumbType {
		ContentsThumbType_Thumb,
		ContentsThumbType_ClipInfo,
		ContentsThumbType_DrawThumb,
		ContentsThumbType_Init,
		ContentsThumbType_SelectClipInfo,
	} ContentsThumbType;
	
	CtWindowContentsThumb(const CtWindowID WindowID);
	virtual ~CtWindowContentsThumb();
	void setContentsThumbType(ContentsThumbType type);
	ContentsThumbType getContentsThumbType() const;

protected :
	ContentsThumbType m_ThumbType;
	
};

#endif
