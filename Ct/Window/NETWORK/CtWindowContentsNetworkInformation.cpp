#include "CtWindowContentsNetworkInformation.h"

CtWindowContentsNetworkInformation::CtWindowContentsNetworkInformation(const CtWindowID WindowID) : CtWindowContents(WindowID) {
	memset( &m_InformationTextInfo, 0, sizeof(m_InformationTextInfo) );
}

CtWindowContentsNetworkInformation::CtWindowContentsNetworkInformation(CtWindowContentsNetworkInformation& contents) : CtWindowContents(contents.getType()) {
	memset( &m_InformationTextInfo, 0, sizeof(m_InformationTextInfo) );
	
	CtInformationTextInfo& textInfo= contents.getInformationTextInfo();
	m_InformationTextInfo = textInfo;
}

CtWindowContentsNetworkInformation::~CtWindowContentsNetworkInformation() {
}

void CtWindowContentsNetworkInformation::setInformationTextInfo(CtWindowContentsNetworkInformation::CtInformationTextInfo& info) {
	m_InformationTextInfo = info;
}

CtWindowContentsNetworkInformation::CtInformationTextInfo& CtWindowContentsNetworkInformation::getInformationTextInfo() {
	return m_InformationTextInfo;
}
