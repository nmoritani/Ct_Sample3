/**
*  Copyright(c) 2018 Persol AVC Technology.
*  Element:			CtContainerThumbnailTitleBar
*/


#ifndef __CtContainerThumbnailTitleBar_H__
#define __CtContainerThumbnailTitleBar_H__

#include "CtContainer.h"
#include "CtWindowCommon.h"

class CtContainerWifi;
class CtContainerBattery;

class CtContainerThumbnailTitleBar : public CtContainer
{
public:
	typedef enum ClipMediaType {
		ClipMediaType_None,
		ClipMediaType_SD1,
		ClipMediaType_SD2,
	} ClipMediaType;

public:
	CtContainerThumbnailTitleBar(CtWindowID _id);
	virtual ~CtContainerThumbnailTitleBar() {}

	virtual bool handleParamEvent(const CtEventParam& Param);

	bool updateOpratorSel(CtWindowID _id);
	bool updateMediaType(ClipMediaType _MediaType);

private:
	virtual CtLayout* createContainer();
	virtual bool destroyContainer();

	void      createLabels();
	CtLayout* createLayout();

	void updateUpper();
	bool updateTitle();
	bool updateWaiting();
	bool updateOpratorSel();
	bool updateP2();
	bool updateMov();
	bool updateAvchd();
	bool updateP2Start();
	bool updateSd();

private:
	CtWindowID              m_WindowID;

	CtStackLabel*			m_pTitle;
	CtLayout*				m_pWaiting;
	CtStackLabel*			m_pOpratorSel;
	CtStackLabel*			m_pP2;
	CtStackLabel*			m_pMov;
	CtStackLabel*			m_pAvchd;
	CtStackLabel*			m_pNG;
	CtStackLabel*			m_pSd1;
	CtStackLabel*			m_pSd2;
	CtContainerWifi*		m_pWifi;
	CtContainerBattery*		m_pBatt;

	ClipMediaType           m_MediaType;

};

#endif
