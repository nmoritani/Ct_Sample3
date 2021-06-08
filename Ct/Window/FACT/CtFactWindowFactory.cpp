/**
 *  Copyright (c) 2018 Persol AVC Technology.
 *  Element:			CtFactWindowFactory
 */


#include "CtFactWindowFactory.h"

CtWindowMain* CtFactWindowFactory::create(CtWindowID id,  CtWindowContents *pContents)
{
	CtWindowMain *pWin = NULL;

	CtFactWindowDialog::MessageInfo* pInfo = CtFactWindowDialog::getInfo(id);
	if (pInfo != NULL) {
		// ダイアログメッセージ
		pWin = new CtFactWindowDialog();
	}
	else {
		switch (id) {
			// 工場出荷設定
		case WindowID_Fact_InitialResult:
			pWin = new CtFactWindowInitialResult(pContents);    /* pgr0541 */
			break;

			// 仕向地切替
		case WindowID_Fact_DISTINATION:
			pWin = new CtWindow_FACT_DISTINATION(pContents);	/* pgr0541 */
			break;

			//タッチパネル調整＆キー検査
		case WindowID_Fact_KEY_TEST1:
			pWin = new CtFactWindowKeyTest(id, pContents);  /* pgr0541 */
			break;

		case WindowID_Fact_DispMessage:
			pWin = new CtFactWindowDispMessage(pContents);	/* pgr0541 */
			break;

			// 仕向け地切り替え完了
		case WindowID_Fact_DistResult:
			pWin = new CtFactWindowDistResult(pContents);	/* pgr0541 */
			break;

#if 0
			//アワーメータ
		case WindowID_Fact_HOUR_METERS:
			pWin = new CtFactWindowHourMeter(pContents);    /* pgr0541 */
			break;
#endif

		default:
			break;
		}
	}


	if( pWin != NULL ){
		pWin->setWindowID(id);
	}
	return pWin;
}
