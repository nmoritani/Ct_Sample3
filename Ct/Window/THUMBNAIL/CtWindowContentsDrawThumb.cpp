#include "CtWindowContentsDrawThumb.h"

CtWindowContentsDrawThumb::CtWindowContentsDrawThumb(const CtWindowID WindowID) : CtWindowContentsThumb(WindowID) {
	m_ThumbType = CtWindowContentsDrawThumb::ContentsThumbType_DrawThumb;
	memset(&m_DrawThumbInfo, 0, sizeof(m_DrawThumbInfo));
}

CtWindowContentsDrawThumb::CtWindowContentsDrawThumb(CtWindowContentsDrawThumb& ContentsDrawThumb) : CtWindowContentsThumb(ContentsDrawThumb.getType()) {
	m_ThumbType = CtWindowContentsDrawThumb::ContentsThumbType_DrawThumb;
	memset(&m_DrawThumbInfo, 0, sizeof(m_DrawThumbInfo));
	
	m_DrawThumbInfo = ContentsDrawThumb.getDrawThumbInfo();
}

CtWindowContentsDrawThumb::~CtWindowContentsDrawThumb() {
}

ContentsThumbInfo CtWindowContentsDrawThumb::getDrawThumbInfo() {
	return m_DrawThumbInfo;
}

void CtWindowContentsDrawThumb::setDrawThumbInfo(ContentsThumbInfo& info) {
	m_DrawThumbInfo = info;
}
