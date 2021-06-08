/**
*  Copyright (c) 2018 Persol AVC Technology.
*  Element:			CtFactKeyTestBase
*/


#include "CtFactWindowKeyTest.h"

CtFactWindowKeyTest::CtFactWindowKeyTest(CtWindowID id, CtWindowContents *pContents) :
	m_TouchPos(0)
{
	//タッチ検査の初期化
	m_contents_left_top = new CtWindowContentsFactKey(id);
	m_contents_left_bottom = new CtWindowContentsFactKey(id);
	m_contents_right_top = new CtWindowContentsFactKey(id);
	m_contents_right_bottom = new CtWindowContentsFactKey(id);
	m_contents_center = new CtWindowContentsFactKey(id);

	m_left_top = new CtButton(CtSize(21, 21), CtButton::Rect);
	m_layout_left_top = createAdjustButton(m_left_top);
	m_left_bottom = new CtButton(CtSize(21, 21), CtButton::Rect);
	m_layout_left_bottom = createAdjustButton(m_left_bottom);

	m_right_top = new CtButton(CtSize(21, 21), CtButton::Rect);
	m_layout_right_top = createAdjustButton(m_right_top);
	m_right_bottom = new CtButton(CtSize(21, 21), CtButton::Rect);
	m_layout_right_bottom = createAdjustButton(m_right_bottom);

	m_center = new CtButton(CtSize(21, 21), CtButton::Rect);
	m_layout_center = createAdjustButton(m_center);


	if (pContents == NULL) {
		//最初のコンテンツがNULLで渡されたら、キーテスト用のボタンは非表示にしてタッチボタンのみの画面を作る
		//もし、最初は空っぽにしておいて、後からキーテスト用ボタンを表示したい場合は、setContentsで行うこと
		for (int i = 0; i < FACT_KEYTEST_ITEM_MAX; i++) {
			m_label_items[i] = new CtFactKeyTestLabel(NULL);
		}

		//タッチ検査項目を非表示
		m_layout_left_top->setVisible(false);
		m_layout_left_bottom->setVisible(false);
		m_layout_right_top->setVisible(false);
		m_layout_right_bottom->setVisible(false);
		m_layout_center->setVisible(false);
	} else {
		CtWindowContentsFactKey *keytest_contents = (CtWindowContentsFactKey*)pContents;
		CtWindowContentsFactKey::FactKeyTestItem *items = keytest_contents->GetKeyTestItems();
		int max = keytest_contents->GetKeyTestItemCountMax();
		for (int i = 0; i < max; i++) {
			m_label_items[i] = new CtFactKeyTestLabel(&items[i]);
		}

		//タッチ検査項目が無効なら非表示
		CtWindowContentsFactKey::FACT_TOUCH_POS touchPos = keytest_contents->getFactTouchTestPos();
		if (touchPos == CtWindowContentsFactKey::FACT_TOUCH__POS_DISABLE) {
			m_layout_left_top->setVisible(false);
			m_layout_left_bottom->setVisible(false);
			m_layout_right_top->setVisible(false);
			m_layout_right_bottom->setVisible(false);
			m_layout_center->setVisible(false);
		}
		
		//レイアウト情報を保存しておく
		m_TouchAdjust = keytest_contents->getFactTouchAdjust();
	}
	setClassType(CtClassType_WindowFACT);
}

CtFactWindowKeyTest::~CtFactWindowKeyTest()
{
	if(m_contents_left_top != NULL){
		delete m_contents_left_top;
		m_contents_left_top = NULL;	
	}
	if(m_contents_left_bottom != NULL){
		delete m_contents_left_bottom;
		m_contents_left_bottom = NULL;	
	}
	if(m_contents_right_top != NULL){
		delete m_contents_right_top;
		m_contents_right_top = NULL;	
	}
	if(m_contents_right_bottom != NULL){
		delete m_contents_right_bottom;
		m_contents_right_bottom = NULL;	
	}
	if(m_contents_center != NULL){
		delete m_contents_center;
		m_contents_center = NULL;	
	}
	
	destroyWindow();
}

bool CtFactWindowKeyTest::destroyWindow()
{
	if (NULL != m_pWin) delete m_pWin;

	for (int i = 0; i < FACT_KEYTEST_ITEM_MAX; i++) {
		if (NULL != m_label_items[i]) delete m_label_items[i];
		m_label_items[i] = NULL;
	}
	return true;
}

CtWindow* CtFactWindowKeyTest::createWindow()
{
	m_IsFinish = false;
	m_pWin = new CtWindow(CtColor::Black);

	// タッチ調整とタッチ検査でレイアウトを変更する
	if( true == m_TouchAdjust )
	{
		CtVLayout *Left = new CtVLayout();
		Left->addWidget(m_layout_left_top, 63);
		Left->addStretch(514);
		Left->addWidget(m_layout_left_bottom, 63);

		CtVLayout *Center = new CtVLayout();
		Center->addWidget(m_layout_center, 1);

		CtVLayout *Right = new CtVLayout();
		Right->addWidget(m_layout_right_top, 63);
		Right->addStretch(514);
		Right->addWidget(m_layout_right_bottom, 63);
		
		CtHLayout *all = new CtHLayout();
		all->addWidget(Left, 63);
		all->addWidget(Center, 834);
		all->addWidget(Right, 63);
		
		m_pWin->addWidget(all, 1);
	}
	else
	{
		CtVLayout *Left = new CtVLayout();
		Left->addWidget(m_layout_left_top, 47);
		Left->addStretch(546);
		Left->addWidget(m_layout_left_bottom, 47);

		CtVLayout *Center = new CtVLayout();
		Center->addWidget(m_layout_center, 1);

		CtVLayout *Right = new CtVLayout();
		Right->addWidget(m_layout_right_top, 47);
		Right->addStretch(546);
		Right->addWidget(m_layout_right_bottom, 47);

		CtHLayout *all = new CtHLayout();
		all->addWidget(Left, 47);
		all->addWidget(CreateKeyTestLayout(0, 7), 409);
		all->addWidget(Center, 48);
		all->addWidget(CreateKeyTestLayout(7, 7), 409);
		all->addWidget(Right, 47);
		
		m_pWin->addWidget(all, 1);
	}

	return m_pWin;
}

CtLayout * CtFactWindowKeyTest::createAdjustButton(CtButton* _button)
{
	if(NULL == _button)
	{
		return NULL;
	}
	
	_button->setButtonColors(CtColor::Red, CtColor(134, 134, 134, 0xff), CtColor::NoColor);
	_button->setFocusable(false);
	CtLayout *buttonLayout = new CtLayout(CtSize(63, 63), CtColor::White);
	buttonLayout->addWidget(_button, AlignCenter);
	return buttonLayout;
}

CtLayout* CtFactWindowKeyTest::CreateKeyTestLayout(int startIndex, int count)
{
	CtFontSet fSet_right = CtFontSet(FontTypeNormal_alignRight_Middle, CtColor::White);
	fSet_right.setSize(30);

	CtVLayout *left = new CtVLayout();
	left->addStretch(120);

	int end = (startIndex + count);
	if (FACT_KEYTEST_ITEM_MAX < end) {
		end = FACT_KEYTEST_ITEM_MAX;
	}

	for (int index = startIndex; index < end; index++) {
		left->addWidget(m_label_items[index]->CreateLayout(), 80);
	}
	left->addStretch(120);

	return left;
}


bool CtFactWindowKeyTest::handleKeyEvent(const CtEventKey& Key)
{
	return false;
}

bool CtFactWindowKeyTest::handleTouchEvent(const CtEventTouch& Touch)
{
	return false;
}

bool CtFactWindowKeyTest::updateContents()
{
	//キー検査項目の描画更新
	for (int i = 0; i < FACT_KEYTEST_ITEM_MAX; i++) {
		if (NULL != m_label_items[i]) m_label_items[i]->UpdateItem();
	}

	// 各タッチボタンの表示を更新
	if (m_TouchPos & CtWindowContentsFactKey::FACT_TOUCH__POS_LEFT_TOP)
	{
		m_layout_left_top->setVisible(true);
	}
	else
	{
		m_layout_left_top->setVisible(false);
	}
	if (m_TouchPos & CtWindowContentsFactKey::FACT_TOUCH__POS_LEFT_BOTTOM)
	{
		m_layout_left_bottom->setVisible(true);
	}
	else
	{
		m_layout_left_bottom->setVisible(false);
	}
	if (m_TouchPos & CtWindowContentsFactKey::FACT_TOUCH__POS_RIGHT_TOP)
	{
		m_layout_right_top->setVisible(true);
	}
	else
	{
		m_layout_right_top->setVisible(false);
	}
	if (m_TouchPos & CtWindowContentsFactKey::FACT_TOUCH__POS_RIGHT_BOTTOM)
	{
		m_layout_right_bottom->setVisible(true);
	}
	else
	{
		m_layout_right_bottom->setVisible(false);
	}
	if (m_TouchPos & CtWindowContentsFactKey::FACT_TOUCH__POS_CENTER)
	{
		m_layout_center->setVisible(true);
	}
	else
	{
		m_layout_center->setVisible(false);
	}

	return true;
}

bool CtFactWindowKeyTest::setContents(const CtWindowContents* pContents)
{
	if (pContents == NULL) return false;
	if (pContents->getType() != getWindowID()) {
		return false;
	}

	if (m_IsFinish) {
		return false;
	}

	SetKeyResult(pContents);

	SetTouchResult(pContents);

	SetResultMessage(pContents);

	return true;
}

void CtFactWindowKeyTest::SetKeyResult(const CtWindowContents* pContents)
{
	CtWindowContentsFactKey *keytest_contents = (CtWindowContentsFactKey*)pContents;
	CtWindowContentsFactKey::FactKeyTestItem *items = keytest_contents->GetKeyTestItems();
	int max = keytest_contents->GetKeyTestItemCountMax();
	for (int i = 0; i < max; i++) {
		m_label_items[i]->setItem(&items[i]);
	}
}

void CtFactWindowKeyTest::SetTouchResult(const CtWindowContents* pContents)
{
	CtWindowContentsFactKey *keytest_contents = (CtWindowContentsFactKey*)pContents;
	m_TouchPos = keytest_contents->getFactTouchTestPos();
}

void CtFactWindowKeyTest::SetResultMessage(const CtWindowContents* pContents)
{
	CtWindowContentsFactKey *keytest_contents = (CtWindowContentsFactKey*)pContents;
	const char *message = keytest_contents->getMessage();

	if (NULL != message) {
		m_IsFinish = true;
		CtHLayout *all = new CtHLayout(CtColor(ColorRGBA, 0x00000077, NULL));	//半透明黒背景
		all->addWidget(new CtLabel(message));

		m_pWin->addWidget(all, 1);

		m_pWin->setRegion(CtRegion(0, 0, 960, 540));
		m_pWin->setColor(CtColor::Black);
		m_pWin->setVisible(true);
		m_pWin->setLayout();
	}
}
