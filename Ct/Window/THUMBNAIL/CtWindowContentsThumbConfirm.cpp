#include "CtWindowContentsThumbConfirm.h"

CtWindowContentsThumbConfirm::CtWindowContentsThumbConfirm(const CtWindowID WindowID) : CtWindowContents(WindowID) , m_ThumbConfirmType(CtWindowContentsThumbConfirm::ContentsThumbType_Thumb_None) {
    memset(&m_ThumbConfirmInfo,0x00,sizeof(m_ThumbConfirmInfo));
}

CtWindowContentsThumbConfirm::~CtWindowContentsThumbConfirm() {
}

CtWindowContentsThumbConfirm::ContentsThumbConfirmType CtWindowContentsThumbConfirm::getContentsThumbConfirmType() {
	return m_ThumbConfirmType;
}

void CtWindowContentsThumbConfirm::setContentsThumbConfirmType(ContentsThumbConfirmType type) {
	m_ThumbConfirmType = type;
}

ContentsThumbConfirmInfo CtWindowContentsThumbConfirm::getContentsThumbConfirmInfo() {
	return m_ThumbConfirmInfo;
}

void CtWindowContentsThumbConfirm::setContentsThumbConfirmInfo(ContentsThumbConfirmInfo& info) {
	memcpy(&m_ThumbConfirmInfo,&info,sizeof(info));
}
