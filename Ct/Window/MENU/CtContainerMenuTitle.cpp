
#include "CtContainerMenuTitle.h"
#include "CtLanguage.h"


CtContainerMenuTitle::CtContainerMenuTitle(CtWindowID Windowid):
	m_WindowID(Windowid),
	m_pTitle(NULL),
	m_pPage(NULL),
	m_Color(CtColor::NoColor),
	m_pInfo(NULL)
{
}
CtContainerMenuTitle::~CtContainerMenuTitle()
{
	destroyContainer();
}
bool CtContainerMenuTitle::destroyContainer() {
	return true;
}

CtLayout* CtContainerMenuTitle::createContainer(){

	CtFontSet fSet = CtFontSet(FontTypeNormal_alignAuto, CtColor::White);

	m_pInfo = CtMenuInfo::getWindowInfo(m_WindowID);

	m_pTitle = new CtLabel("", fSet);

	CtHLayout *pLayout = new CtHLayout();
	CtMenuInfo::CtMenuTitleType Type = (m_pInfo == NULL) ? CtMenuInfo::TitleType_Max :m_pInfo->title.type;
	switch (Type) {

	case CtMenuInfo::TitleType_SetPhase:
		/* |--|- 646 ---------------|-- 100 --|--|-- 100 --|--|  */
		/* |14|   Title             |   SAT   |50|  PHASE  |50|  */
		/* |__|_____________________|_________|__|_________|__|  */

		pLayout->addStretch(14);
		pLayout->addWidget(m_pTitle, AlignLeft, 646);
		pLayout->addWidget(new CtLabel(STR_ID_NO_10769, CtFontSet(FontTypeNormal_alignCenter, CtColor::White)), AlignCenter, 100);
		pLayout->addStretch(50);
		pLayout->addWidget(new CtLabel(STR_ID_NO_10770, CtFontSet(FontTypeNormal_alignCenter, CtColor::White)), AlignCenter, 100);
		pLayout->addStretch(50);
		break;

	case CtMenuInfo::TitleType_Default:
	case CtMenuInfo::TitleType_Set:
	case CtMenuInfo::TitleType_Phase:
	default:
		/* |--|- 841 -----------------------------|-- 90 --|--|  */
		/* |14|   Title                           |  Page  |15|  */
		/* |__|___________________________________|________|__|  */

		pLayout->addStretch(14);

		if (m_pPage != NULL) {
			pLayout->addWidget(m_pTitle, AlignLeft, 841);
			pLayout->addWidget(m_pPage, AlignRight, 90);
		}
		else {
			pLayout->addWidget(m_pTitle, AlignLeft, 841 + 90);
		}

		pLayout->addStretch(15);
		break;

	}

	if (m_pInfo != NULL) {
		updateTitle();
	}

	CtVLayout* pAll = new CtVLayout(m_Color);
	pAll->addStretch(12);
	pAll->addWidget(pLayout, 60);
	pAll->addStretch(18);

	return pAll;
}
void CtContainerMenuTitle::setColor(CtColor color)
{
	m_Color = color;
}
void CtContainerMenuTitle::setPage(CtLabel* pLabel)
{
	m_pPage = pLabel;
}

bool CtContainerMenuTitle::handleParamEvent(const CtEventParam& Param)
{
	bool bRet = false;
	int t_Id = Param.getParamId();

	switch (t_Id) {
	case AplParamLanguage:
	{
		if (m_pTitle == NULL) break;
		if (m_pInfo == NULL) break;

		updateTitle();
		bRet = true;
		break;
	}
	default:
		break;
	}
	return bRet;
}
void CtContainerMenuTitle::updateTitle()
{
	unsigned short str[TITLE_STRING_MAX];
	unsigned short connect[10];
	memset(connect, 0, sizeof(connect));
	convert_char_str_to_ushort_str(connect, ">");

	short TitleMax = 0;
	CtSize Size;
	CtFontSet fSet = CtFontSet(FontTypeNormal, CtColor::White);
	fSet.setSize(MENU_LABEL_SIZE);
	fSet.setLanguageId(CtLanguage::getLanguageID());


	switch (m_pInfo->title.type) {
	case CtMenuInfo::TitleType_Default:
	case CtMenuInfo::TitleType_Set:
	case CtMenuInfo::TitleType_Phase:
		TitleMax = (short)TITLE_DEFAULT_MAX;
		break;
	case CtMenuInfo::TitleType_SetPhase:
		TitleMax = (short)TITLE_SETPHASE_MAX;
		break;
	default:
		break;
	}

	unsigned short hierarchy[MENU_HISTORY_NUM][50] = { 0 };	//”z—ñŠK‘w
	int s_Count = 0;
	int hierarchyNum = 0;
	// ‡@ ”z—ñ‚ÉŠK‘w–¼‚ðŠi”[
	for (; hierarchyNum < m_pInfo->title.num; hierarchyNum++) {	/* pgr0360 */
		const unsigned short *pStr = getString(m_pInfo->title.id[hierarchyNum]); //str–¼‘O
		if (pStr != NULL) {
			for (int len = 0; pStr[len]; len++) {
				hierarchy[hierarchyNum][s_Count++] = pStr[len];
				if (s_Count >= 50) break;
			}
		}
		s_Count = 0;
	}

	if ((m_pInfo->title.type == CtMenuInfo::TitleType_Set) ||
		(m_pInfo->title.type == CtMenuInfo::TitleType_Phase)) {
		GDI_STRING_ID STR_ID;
		if (m_pInfo->title.type == CtMenuInfo::TitleType_Set) {
			STR_ID = STR_ID_NO_10769;
		}
		else {
			STR_ID = STR_ID_NO_10770;
		}
		const unsigned short *pStr = GDI_GetString(CtLanguage::getLanguageID(), STR_ID);
		for (int len = 0; pStr[len]; len++) {
			hierarchy[hierarchyNum][s_Count++] = pStr[len];
			if (s_Count >= 50) break;
		}
		s_Count = 0;
	}

	// ‡A È—ª‰ÓŠ‚ð"...",‹ó—“‚É•ÏŠ·
	Size.width = TITLE_DEFAULT_MAX + 1;
	for (int h_count = 0; Size.width > TitleMax; h_count++) {
		switch (h_count) {
		case 0:
			break;
		case 1:
			memset(&hierarchy[h_count][0], 0, sizeof(hierarchy[h_count]));
			if (h_count == 1) {
				for (int len = 0; len < 3; len++) {
					hierarchy[h_count][len] = '.';
				}
			}
			break;
		default:
			memset(&hierarchy[h_count][0], 0, sizeof(hierarchy[h_count]));
			break;
		}

		// ‡B ”z—ñŠK‘w‚©‚çstrƒ^ƒCƒgƒ‹‚Ö‚Ì‘ã“ü
		memset(str, 0, sizeof(str));
		for (int i = 0; i < MENU_HISTORY_NUM; i++) {		/* pgr0360 */
			if (hierarchy[i][0] == 0) {
				continue;
			}
			if (i > 0) {
				str[s_Count++] = connect[0];
				if (s_Count == TITLE_STRING_MAX) break;
			}
			for (int len = 0; hierarchy[i][len]; len++) {
				str[s_Count++] = hierarchy[i][len];
				if (s_Count == TITLE_STRING_MAX) break;
			}

		}
		s_Count = 0;
		Size.width = 0;
		fSet.getStringSize(Size, str);
	}

	fSet.setSize(0);
	str[299] = 0;

	m_pTitle->setText(str, fSet);
}

unsigned short* CtContainerMenuTitle::getString(int id)
{
	static unsigned short str[TITLE_STRING_MAX];
	memset(str, 0, sizeof(str));

	CtMenuInfo::CtMenuButtonInfo* pInfo = CtMenuInfo::getButtonInfo(id);
	if (pInfo == NULL) {
		convert_char_str_to_ushort_str(str, "None");
		return str;
	}

	GDI_STRING_ID STR_ID = pInfo->StringId;

	if (STR_ID == STR_ID_MAX_SIZE) {
		convert_char_str_to_ushort_str(str, pInfo->str);
		return str;
	}
	return GDI_GetString(CtLanguage::getLanguageID(STR_ID), STR_ID);
}
