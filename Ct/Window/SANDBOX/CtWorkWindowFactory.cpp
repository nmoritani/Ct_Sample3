/**
 *  Copyright(c) 2018 Persol AVC Technology.
 *  Element:			CtWorkWindowFactory
 */


#include "CtWorkWindowFactory.h"

CtWindowMain* CtWorkWindowFactory::create(CtWindowID id,  CtWindowContents *pContents)
{
	CtWindowMain *pWin = NULL;
#if 0
	if ((id & 0xFF000000) != WindowMainCategory_Work) {
		return NULL;	//対象外のカテゴリー
	}
#endif
	switch (id) {
	case Window_001:				pWin = new CtWindow_001(pContents);		break;	/* pgr0541 */
	case Window_002:				pWin = new CtWindow_002(pContents);		break;	/* pgr0541 */
	case Window_003:				pWin = new CtWindow_003(pContents);		break;	/* pgr0541 */
	case Window_004:				pWin = new CtWindow_004(pContents);		break;	/* pgr0541 */
	case Window_005:				pWin = new CtWindow_005(pContents);		break;	/* pgr0541 */
	case Window_006:				pWin = new CtWindow_006(pContents);		break;	/* pgr0541 */
	case Window_007:				pWin = new CtWindow_007(pContents);		break;	/* pgr0541 */
	case Window_008:				pWin = new CtWindow_008(pContents);		break;	/* pgr0541 */
	default:						break;
	}
#if 0
	if (pWin == NULL) {
		if (((id & 0xFFFF0000) == WindowCategory_TransitionA) ||
			((id & 0xFFFF0000) == WindowCategory_TransitionB)) {
			pWin = new CtWindow_TransitionTest();
		}
	}
#endif
	if (pWin != NULL) {
		pWin->setWindowID(id);
	}

	return pWin;
}
