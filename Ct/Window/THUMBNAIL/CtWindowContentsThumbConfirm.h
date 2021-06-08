#ifndef __CtWindowContentsConfirm_H__
#define __CtWindowContentsConfirm_H__

#include "CtWindowContents.h"
#include "CtWindowContentsThumbCommon.h"

class CtWindowContentsThumbConfirm : public CtWindowContents {
public :
	typedef enum ContentsThumbType {
		ContentsThumbType_Thumb_None,
		ContentsThumbType_Thumb_Copy,
		ContentsThumbType_Thumb_Delete,
	} ContentsThumbConfirmType;
	
	CtWindowContentsThumbConfirm(const CtWindowID WindowID);
	virtual ~CtWindowContentsThumbConfirm();
	void setContentsThumbConfirmType(ContentsThumbConfirmType type);
	ContentsThumbConfirmType getContentsThumbConfirmType();

	void setContentsThumbConfirmInfo(ContentsThumbConfirmInfo& info);
	ContentsThumbConfirmInfo getContentsThumbConfirmInfo();
	
protected :
	ContentsThumbConfirmType m_ThumbConfirmType;
	ContentsThumbConfirmInfo m_ThumbConfirmInfo;
};

#endif
