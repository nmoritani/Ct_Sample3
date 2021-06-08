#include "Ct.h"
#include "CtWidget.h"
#include "CtLabel.h"
#include "CtButton.h"
#include "CtWindow.h"

// 画面作成のサンプルコード

CtWindow * Factory_WindowID_0003()
{
#if 0
	CtRegion WinRegion = {0,0,960,540};
	
	
	// addWidgetは、Widget, 割合(addされた数の合算から),
	//  縦横マージン/縦マージン, 横マージン/TOPマージン,LEFTマージン,BOTTOMマージン,RIGHTマージン
	CtVLayout* c1_1 = new CtVLayout();
	c1_1->addWidget(new CtRoundButton(DrawType_Vector, IMAGE_ID_0001), margin);
	c1_1->addWidget(new CtLabel(DrawType_Font, STRING_ID_0070), h_margin, v_margin);

	// ボタンに背景ラベルと、アイコンを登録
	CtButton* b_2_1 = new CtButton();
	b_2_1->setLabel(new CtLabel(DrawType_RRect, ColorType_ButtonBase, 2, ColorType_ButtonFrame));
	b_2_1->setLabel(new CtLabel(DrawType_Vector, IMAGE_ID_0005));

	// VLayoutの上部80%にボタン、下部20%にラベルを配置
	CtVLayout* c1_2 = new CtVLayout();
	c1_2->addWidget(b_2_1, 80, 5);
	c1_2->addWidget(new CtLabel(DrawType_Font, STRING_ID_0071), 20, 2, 5);

	CtButton* b_3_1 = new CtButton();
	b_3_1->setLabel(new CtLabel(DrawType_RRect, ColorType_ButtonBase, 2, ColorType_ButtonFrame));
	b_3_1->setLabel(new CtLabel(DrawType_Vector, IMAGE_ID_0008));
	CtLabel* l_3_2 = new CtLabel(DrawType_Font, STRING_ID_0070);
	
	CtVLayout* c1_3 = new CtVLayout();
	c1_3->addWidget(b_3_1, 5, 5);
	c1_3->addWidget(l_3_2, 5, 5);

	// HLayoutに３つ同じ割合でボタンを追加する(
	CtLayout* c1 = new CtHLayout();	// 個数指定なし。(addWidgetされた数から個数算出)
	c1->addLayout(c_1_1, 1);
	c1->addLayout(c_1_2, 1);
	c1->addLayout(c_1_3, 1);
	
	CtGridLayout* c2 = new CtGridLayout();
	c2->addWidget(new CtLabel(DrawType_Font, STRING_ID_0001), {0,0});
	c2->addWidget(new CtLabel(DrawType_Font, STRING_ID_0008), {0,0});
	c2->addWidget(new CtLabel(DrawType_Vector, IMAGE_ID_0013));
	c2->addWidget(new CtLabel(DrawType_Font, STRING_ID_0201));
	c2->addWidget(new CtLabel(DrawType_Vector, IMAGE_ID_0014));
	c2->addWidget(new CtLabel(DrawType_Vector, IMAGE_ID_0018));

	
	CtButton* b_3_1 = new CtButton();
	b_3_1->setLabel(new CtLabel(DrawType_RRect, ColorType_ButtonBase, 2, ColorType_ButtonFrame));
	b_3_1->setLabel(new CtLabel(DrawType_Vector, IMAGE_ID_0001));
	
	CtButton* b_3_2 = new CtButton();
	b_3_2->setLabel(new CtLabel(DrawType_RRect, ColorType_ButtonBase, 2, ColorType_ButtonFrame));
	b_3_2->setLabel(new CtLabel(DrawType_Vector, IMAGE_ID_0001));
	
	CtButton* b_3_3 = new CtButton();
	b_3_2->setLabel(new CtLabel(DrawType_RRect, ColorType_ButtonBase, 2, ColorType_ButtonFrame));
	b_3_2->setLabel(new CtLabel(DrawType_Vector, IMAGE_ID_0001));
	
	CtHLayout* c3 = new CtHLayout();
	c3->addLayout(b_3_1);
	c3->addLayout(b_3_2);
	c3->addLayout(b_3_3);

	ca = new CtVLayout();
	ca->addLayout(c1, 23);
	ca->addLayout(c2, NOKORI);
	ca->addLayout(c3, 23);
	
	CtWindow* win = createWindow(WinRegion);
	win->setLayout(ca);
	win->invalidete();

	return win;
#else
	return NULL;
#endif
}	


	


