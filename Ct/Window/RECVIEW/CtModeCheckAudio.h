/******************************************************************************
 * Copyright(c) 2018 Persol AVC Technology.
 ******************************************************************************/

#ifndef __CtModeCheckAudio_H__
#define __CtModeCheckAudio_H__

#include "Ct.h"
#include "CtEvent.h"
#include "CtWidget.h"
#include "CtHLayout.h"
#include "CtVLayout.h"
#include "AplParamService.h"
#include "CtStackLabel.h"
#include "CtFastContainerAudioLevel_Home.h"

class CtModeCheckAudio : public CtContainer
{
public:
	CtModeCheckAudio();
	virtual bool destroyWindow();
	virtual bool startupContainer();

	bool handleParamEvent(const CtEventParam& Param);
	bool handleButtonEvent(const CtEventButton& Button);
	bool handleKeyEvent(const CtEventKey& Key);
	virtual CtLayout* createContainer();

protected :
	~CtModeCheckAudio();

private :
	CtLayout *m_pAll;
	CtLabel* m_pAudioOut;
	bool updateHpOut(int int_Data);

	CtLabel* m_pCh1Select;
	bool updateCh1Select(int int_Data);
	
	CtLabel* m_pCh2Select;
	bool updateCh2Select(int int_Data);

	CtLabel* m_pCh1LineMic;
	bool updateCh1LineMic();

	CtLabel* m_pCh2LineMic;
	bool updateCh2LineMic();

	CtLabel* m_pCh1Level;
	bool updateCh1Level(int int_Data);
	
	CtLabel* m_pCh2Level;
	bool updateCh2Level(int int_Data);

	CtLabel* m_pCh1Limiter;
	bool updateCh1Limiter();

	CtLabel* m_pCh2Limiter;
	bool updateCh2Limiter();

	CtLabel* m_pCh1Lowcut;
	bool updateCh1Lowcut(int int_Data);

	CtLabel* m_pCh2Lowcut;
	bool updateCh2Lowcut(int int_Data);

	CtFastContainerAudioLevel_Home* m_pAudioLevel;
};

#endif /* __CtMenuButtonList_H__ */

