#include "CtWindowContentsThumb.h"

CtWindowContentsThumb::CtWindowContentsThumb(const CtWindowID WindowID) : CtWindowContents(WindowID) , m_ThumbType(CtWindowContentsThumb::ContentsThumbType_Thumb) {
}

CtWindowContentsThumb::~CtWindowContentsThumb() {
}

CtWindowContentsThumb::ContentsThumbType CtWindowContentsThumb::getContentsThumbType() const {
	return m_ThumbType;
}

void CtWindowContentsThumb::setContentsThumbType(ContentsThumbType type) {
	m_ThumbType = type;
}
