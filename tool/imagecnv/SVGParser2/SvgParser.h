#ifndef _SVGPARSER_H_
#define _SVGPARSER_H_

#include "SvgCircle.h"
#include "SvgEllipse.h"
#include "SvgGroup.h"
#include "SvgSVg.h"
#include "SvgLine.h"
#include "SvgLinearGradient.h"
#include "SvgRadialGradient.h"
#include "SvgPath.h"
#include "SvgPolygon.h"
#include "SvgPolyline.h"
#include "SvgRect.h"

class SvgParser {
public:

protected:
	int				m_error;
	SvgGroup		m_defs;			//��`
	SvgSvg			*m_root;		//���[�g
	int				m_depth;		//�l�X�g
	int				m_skip_depth;	//�X�L�b�v���Ă���G�������g�̃l�X�g
	SvgGroup		*m_current;		//�J�����g�O���[�v
	bool			m_is_parse_style;	// �X�^�C���̃p�[�X�����ۂ�
	SVGSTYLEMAP     m_styles;			// �X�^�C����`�}�b�v
public:
	//�R���X�g���N�^
	SvgParser();
	//�f�X�g���N�^
	~SvgParser();
	//�G���[�R�[�h�ݒ�
	void set_error(int err) { m_error = err; }
	//�G���[�R�[�h�擾
	int error() const { return m_error; }
	//���
	int parse(const char *filename);
	//defs
	SvgGroup *defs() { return &m_defs; }
	//���[�g�O���[�v
	SvgSvg *root() { return m_root; }
	//id�����`������
	SvgObject *find_defs(const char *id) {
		return m_defs.find_object(id);
	}
	//��`���폜	(SvgLinearGradient�̃}�[�W�Ɏg�p)
	void delete_defs(SvgObject *obj) {
		m_defs.delete_object(obj);
	}
	// class������X�^�C��������
	SvgStyle *find_style_by_class(const char *name);

	/* XML�p�[�T�[�p */
	//XML�G�������g�J�n
	void element_start(const char *name, const char *atts[]);
	//XML�G�������g�I��
	void element_end(const char *name);
	//�X�^�C�������񏈗�
	void charcter_data(const char* c, int len);
};

#endif
