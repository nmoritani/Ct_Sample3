
#if !defined(__CTAPLPARAM_H__)
#define __CTAPLPARAM_H__

#include "AplParamService.h"

typedef enum _CtParamState {
	CtParamState_Visible,		/* �L���\�� */
	CtParamState_Invalid,		/* �����\�� */
	CtParamState_Invisible,		/* ��\��   */
	CtParamState_End,			/* �I��     */
}CtParamState;

class CtAplParam {
public:
	static int getData(int id);
	static int getLanguage();
	static int getCharLuminance();
	static int getSdiIndicatorDisp();
	static int getHdmiIndicatorDisp();
	static CtParamState getState(int id, int val);

private:
	CtAplParam(){}
};

#endif // !defined(__CTAPLPARAM_H__)
