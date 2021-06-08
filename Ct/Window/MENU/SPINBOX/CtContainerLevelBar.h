/**
 *  Copyright(c) 2018 Persol AVC Technology.
 *  Element:	CtButton
 */
 
#ifndef __CtContainerLevelBar_H_
#define __CtContainerLevelBar_H_

#include "CtWindowCommon.h"


#define LEVEL_MAX   9   /* LevelBarÇÃñ{êî */

class CtContainerLevelBar : public CtContainer
{
public :

	typedef enum LevelBarType {
		LevelBarType_Default,
		LevelBarType_Short,
	}LevelBarType;

public:

	CtContainerLevelBar(int param, int max, int min);
	virtual ~CtContainerLevelBar();
	virtual CtLayout* createContainer();
	virtual bool destroyContainer();

	virtual bool handleParamEvent(const CtEventParam& Param);
	void setLevelBarType(LevelBarType type);

private:

	void executionUpdateViewLebelBar();
	int getValue(int ParamID);
	int getBarReduce();


private:

	LevelBarType      m_Type;

	int m_Param;
	int m_Max;
	int m_Min;

	CtLabel*        m_pLevelBar[LEVEL_MAX];
	int             m_pLevelVal[LEVEL_MAX];


};
inline void CtContainerLevelBar::setLevelBarType(LevelBarType type) {
	m_Type = type;
}
#endif
