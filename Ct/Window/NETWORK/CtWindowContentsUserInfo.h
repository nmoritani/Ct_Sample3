#ifndef __CtWindowContentsUserInfo_H__
#define __CtWindowContentsUserInfo_H__

#include "CtWindowContents.h"
#include "CtVector.h"

class CtUserInfo : public CtObject {
public :

	typedef struct UserInfo {
		char name[50];
	} UserInfo;

	CtUserInfo();
	CtUserInfo(CtUserInfo& obj);  /*ïœêîÇ∆ä÷êîìØñºÇ≈Ç∑*/
	virtual ~CtUserInfo();
	
	UserInfo getUserInfo();
	void setUserInfo(UserInfo& info);

private :
	UserInfo m_UserInfo;

};

class CtWindowContentsUserInfo : public CtWindowContents {
public :
	typedef CtVector::Vector<CtUserInfo*> UserInfoList;
	typedef CtVector::Vector<CtUserInfo*>::iterator UserInfoListItr;
	
	CtWindowContentsUserInfo(const CtWindowID WindowID);
	CtWindowContentsUserInfo(CtWindowContentsUserInfo& contents);
	virtual ~CtWindowContentsUserInfo();
	
	UserInfoList& getUserInfoList();

    void setUserInfoList(CtUserInfo* pCtUserInfo);

    unsigned long getCurrentIndex();
	void setCurrentIndex(unsigned long Index);

private :
	void removeAllUserInfo();
	
	UserInfoList m_UserInfoList;

    unsigned long m_Index;
};

#endif
