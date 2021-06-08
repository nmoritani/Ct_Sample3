#include "CtFileInfo.h"

CtFileInfo::CtFileInfo() {
	memset(&m_FileInfo, 0, sizeof(m_FileInfo));
}

CtFileInfo::CtFileInfo(CtFileInfo& obj) {	/* pgr2222 */
	memset(&m_FileInfo, 0, sizeof(m_FileInfo));
	m_FileInfo = obj.getFileInfo();		/* pgr2222 */
}

CtFileInfo::~CtFileInfo() {
}

CtFileInfo::FileInfo CtFileInfo::getFileInfo() {
	return m_FileInfo;
}

void CtFileInfo::setFileInfo(CtFileInfo::FileInfo& info) {
	m_FileInfo = info;
}
