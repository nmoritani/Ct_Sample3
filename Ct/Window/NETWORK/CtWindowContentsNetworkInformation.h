#ifndef __CtWindowContentsNetworkInformation_H__
#define __CtWindowContentsNetworkInformation_H__

#include "CtWindowContents.h"

class CtWindowContentsNetworkInformation : public CtWindowContents {
public :
	static const unsigned long CT_NETWORK_INFORMATION_TEXT_MAX = 2048;
	
	typedef struct CtInformationTextInfo {
		bool IsValidUpButton;
		bool IsValidDownButton;
		
		char InformationText[CT_NETWORK_INFORMATION_TEXT_MAX];	// LOG/STATUSÇÃï∂éöóÒ(â¸çsÇÕAPLÅ®GUIÇ…ìnÇ∑ëOÇ…í≤êÆ)
	} CtInformationTextInfo;
	
	CtWindowContentsNetworkInformation(const CtWindowID WindowID);
	CtWindowContentsNetworkInformation(CtWindowContentsNetworkInformation& contents);
	virtual ~CtWindowContentsNetworkInformation();
	
	void setInformationTextInfo(CtInformationTextInfo& info);
	CtInformationTextInfo& getInformationTextInfo();
private :
	CtInformationTextInfo m_InformationTextInfo;
};

#endif
