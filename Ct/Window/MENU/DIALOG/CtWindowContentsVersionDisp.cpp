#include "CtWindowContentsVersionDisp.h"

CtWindowContentsVersionDisp::CtWindowContentsVersionDisp(const CtWindowID WindowID) : CtWindowContents(WindowID) {
	memset(m_Version,0,sizeof(m_Version));
}

CtWindowContentsVersionDisp::~CtWindowContentsVersionDisp() {
}

void CtWindowContentsVersionDisp::setNextVersion( unsigned char *version ) {
	if(version == NULL) return;
	memcpy(m_Version,version,Version_Size);
}

unsigned char *CtWindowContentsVersionDisp::getNextVersion() {
	return m_Version;
}
