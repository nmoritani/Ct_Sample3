/**
 *  Copyright(c) 2018 Persol AVC Technology.
 *  Element:			CtContainer
 */


#ifndef __CtTimeStamp_H__
#define __CtTimeStamp_H__

#include "CtObject.h"
#include "CtTsInterface.h"

#include "SysIf.h"
#include "gui_timestamp_api.h"

class CtTimeStamp : public CtObject {
public:
	enum CtTsDisp {
		CtTsDispDate = (1 << 0),
		CtTsDispTime = (1 << 1),
		CtTsDispDateTime = CtTsDispDate | CtTsDispTime,
	};

public :
    CtTimeStamp(CtSize size, CtColorFormat colorFormat, int colorDepth, CtTsDisp dispMode);
    virtual ~CtTimeStamp();

	bool create();
	bool destroy();
	bool update();
	bool setInvalid();
	bool getCurrent(GUI_TS_INFO *info);
	bool isCreated() { return m_State != StateInit; }

private :
	enum CtDateFormat {
		CtDateFormatYMD,
		CtDateFormatMDY,
		CtDateFormatDMY,
	};

	enum CtTsState {
		StateInit,			// Init�����������ACreate�҂�
		StateReqUpdate,		// update�҂�
		StateFinUpdate,		// getCurrent�҂�
		StateInvalid,
	};

	struct CtTsPBuffer {
		unsigned char *Yaddr;
		unsigned char *Caddr;	
		unsigned int MemWidth;
		unsigned int Width;
		unsigned int Height;
	};

	CtColor FgColor;		// �O�i�F(�����F)
	CtColor BgColor;		// �w�i�F
	static const int BASE_COUNT = 2;	// �o�b�t�@�ʐ�

	struct drawables {
		GDI_HANDLER Month[3];
		GDI_HANDLER Separator;
		GDI_HANDLER Dec[10];
		GDI_HANDLER Space;
	} m_Drawables;

	struct DateTimeDrawabales {
		GDI_HANDLER Year[4];
		GDI_HANDLER Month[3];
		GDI_HANDLER Day[2];
		GDI_HANDLER Hour[2];
		GDI_HANDLER Min[2];
		GDI_HANDLER Sec[2];
	} m_DateDrawables[BASE_COUNT];

	CtTsState m_State;						// 
	GDI_HANDLER m_Base[BASE_COUNT];			// �`��Ώۗ̈�
	GDI_HANDLER m_BaseLow;					// 10bit�p�`��Ώۗ̈�
	SYS_DATE_TIME m_Time[BASE_COUNT];		// �`�抮���ς݂̎���
	SYS_DATE_TIME m_CurTime;
	int m_Current;							// �`�抮���ς݂�m_Base�C���f�b�N�X
	CtSize m_Size;							// Base�T�C�Y
	CtSize m_CharSize;						// �P�����̃T�C�Y
	CtColorFormat m_ColorFormat;			// �^�C���X�^���v�̃J���[�t�H�[�}�b�g(YUV422,YUV420,RGB8888,RGB4444)
	int m_ColorDepth;						// �^�C���X�^���v�̐F�[�x
	CtDateFormat m_DateFormat;				// ���t�\���t�H�[�}�b�g(YMD/DMY/MDY)
	CtTsDisp m_DispMode;					// ���t�\�����[�h(OFF/Date/Time/Date&Time)
	bool m_bReformat[BASE_COUNT];			// �N�����t�H�[�}�b�g�ύX�L��

private:
	CtSize getCharSize();
	CtDateFormat getDateFormat();
	CtTsDisp getDispMode();
	short getTimeStampLength();
	int getBytePerPixel(CtColorFormat format);
	CtTsPBuffer BaseToPbuffer(GDI_HANDLER handle);
	CtTsPBuffer DrawableToPbuffer(GDI_HANDLER handle);
	int getNextIndex();
	void setCurrent(int idx);
	void setState(CtTsState state);

	void createBase();
	void createDrawables();
	void createDrawablesMonth();
	void createDrawablesMonth(int month);
	bool drawDateTime(SYS_DATE_TIME& date, int index);
	void drawDrawable(GDI_HANDLER dest, int x, int y, GDI_HANDLER src);
	
	void clearTest();
	void drawTest(GDI_HANDLER drawable);
	
	DateTimeDrawabales getDateTimeDrawables(const SYS_DATE_TIME &date);

	// for TEST
	void DrawChar(GDI_HANDLER handle, char c);
};

#endif
