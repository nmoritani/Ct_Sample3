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
		// �_�C�A���O���b�Z�[�W
		pWin = new CtFactWindowDialog();
	}
	else {
		switch (id) {
			// �H��o�אݒ�
		case WindowID_Fact_InitialResult:
			pWin = new CtFactWindowInitialResult(pContents);    /* pgr0541 */
			break;

			// �d���n�ؑ�
		case WindowID_Fact_DISTINATION:
			pWin = new CtWindow_FACT_DISTINATION(pContents);	/* pgr0541 */
			break;

			//�^�b�`�p�l���������L�[����
		case WindowID_Fact_KEY_TEST1:
			pWin = new CtFactWindowKeyTest(id, pContents);  /* pgr0541 */
			break;

		case WindowID_Fact_DispMessage:
			pWin = new CtFactWindowDispMessage(pContents);	/* pgr0541 */
			break;

			// �d�����n�؂�ւ�����
		case WindowID_Fact_DistResult:
			pWin = new CtFactWindowDistResult(pContents);	/* pgr0541 */
			break;

#if 0
			//�A���[���[�^
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
