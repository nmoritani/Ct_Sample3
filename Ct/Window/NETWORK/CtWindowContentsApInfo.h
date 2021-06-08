#ifndef __CtWindowContentsApInfo_H__
#define __CtWindowContentsApInfo_H__

#include "CtWindowContents.h"
#include "CtVector.h"

class CtApInfo : public CtObject {
public :
    typedef enum CtApInfoEncryptionType {
		EncryptionType_WPA_TKIP,
		EncryptionType_WPA_AES,
		EncryptionType_WPA2_TKIP,
		EncryptionType_WPA2_AES,
    	EncryptionType_None,
    } CtApInfoEncryptionType;

    typedef enum CtApInfoSignalStrength {
    	SignalStrength_None,
		SignalStrength_1,
		SignalStrength_2,
		SignalStrength_3,
		SignalStrength_4,
    } CtApInfoSignalStrength;

	typedef struct ApInfo {
		char ssid[50];
		CtApInfoEncryptionType EncryptionType;
		CtApInfoSignalStrength SignalStrength;
		bool IsHistory;
	} ApInfo;

	CtApInfo();
	CtApInfo(CtApInfo& obj);  /*ïœêîÇ∆ä÷êîìØñºÇ≈Ç∑*/
	virtual ~CtApInfo();
	
	ApInfo getApInfo();
	void setApInfo(ApInfo& info);

private :
	ApInfo m_ApInfo;

};

class CtWindowContentsApInfo : public CtWindowContents {
public :
	typedef CtVector::Vector<CtApInfo*> ApInfoList;
	typedef CtVector::Vector<CtApInfo*>::iterator ApInfoListItr;
	
	CtWindowContentsApInfo(const CtWindowID WindowID);
	CtWindowContentsApInfo(CtWindowContentsApInfo& contents);
	virtual ~CtWindowContentsApInfo();
	
	ApInfoList& getApInfoList();

    void setApInfoList(CtApInfo* pCtApInfo);

    unsigned long getCurrentIndex();
	void setCurrentIndex(unsigned long Index);

private :
	void removeAllApInfo();
	
	ApInfoList m_ApInfoList;

    unsigned long m_Index;
};

#endif
