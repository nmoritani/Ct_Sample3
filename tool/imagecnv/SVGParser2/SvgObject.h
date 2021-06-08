#ifndef _SVGOBJECT_H_
#define _SVGOBJECT_H_

#include "SvgTransform.h"
#include "SvgStyle.h"
#include "SvgUtil.h"

extern int	g_SVGPARSER_COMPATIBLE_GENSKETCH_EVENODD;				//�f�t�H���g��EVEN_ODD�ɂ���

typedef enum {
	//�}�`
	SVG_TYPE_PATH,
	SVG_TYPE_POLYGON,
	SVG_TYPE_POLYLINE,
	SVG_TYPE_CIRCLE,
	SVG_TYPE_ELLIPSE,
	SVG_TYPE_ROUNDRECT,
	SVG_TYPE_RECT,
	SVG_TYPE_LINE,
	SVG_TYPE_FIGURE_END,
	//�}�`�ȊO
	SVG_TYPE_SVG,
	SVG_TYPE_GROUP,
	SVG_TYPE_GRADIENT,
	SVG_TYPE_LINEARGRADIENT,
	SVG_TYPE_RADIALGRADIENT,
	SVG_TYPE_STOP,
	SVG_TYPE_TYPE_MAX
} SVG_OBJECT_TYPE;

class SvgParser;
class SvgPath;

class SvgObject {
public:
	SVG_OBJECT_TYPE	m_type;
	int				m_ref_count;
	SvgObject		*m_referred_object;
	SvgParser		*m_parser;
	SvgObject		*m_parent;
	SvgTransform	*m_transform;
	SvgTransform	*m_abs_transform;
	SvgStyle		m_style;
	string			m_id;		//id����:��Gradient�ȊO�ł̓p�[�X���Ă��Ȃ�
	unsigned long	m_user_data;
protected:

public:
	//�R���X�g���N�^
	SvgObject(SvgParser *parser, SvgObject *parent);
	//�R���X�g���N�^(�p�X�ϊ�����p�Fparser,parent,transform,abs_transform,user_data���R�s�[)
	SvgObject(SvgObject *src);
	//�f�X�g���N�^
	virtual ~SvgObject();
	//�����̔z����
	PARSE_RESULT parse_atts(const char *atts[]);
	//�������
	virtual PARSE_RESULT parse_attribute(const char *att[]);
	//������͌��ʂ��`�F�b�N
	virtual PARSE_RESULT parse_attribute_end();
	//�e�I�u�W�F�N�g�ݒ�
	void set_parent(SvgObject *parent) {
		m_parent = parent;
	}
	//�p�[�T�[�I�u�W�F�N�g�擾
	SvgParser *parser() const {
		return m_parser;
	}
	//�e�I�u�W�F�N�g�擾
	SvgObject *parent() const {
		return m_parent;
	}
	//type�擾
	SVG_OBJECT_TYPE type() const { return m_type; }
	//id�擾
	const string* id() const { return &m_id; }
	//�Q�ƃJ�E���^++
	void add_ref_count() { m_ref_count++; }
	//�Q�ƃJ�E���^--
	void sub_ref_count() { m_ref_count--; }
	//�Q�ƃJ�E���^�擾
	int ref_count() const { return m_ref_count; }
	//�Q�ƌ��I�u�W�F�N�g�ݒ�
	void set_referred_object(SvgObject *obj) { m_referred_object = obj; }
	//�Q�ƌ��I�u�W�F�N�g�擾
	const SvgObject *referred_object() const { return m_referred_object; }
	//���[�U�[�f�[�^�ݒ�
	void set_user_data(unsigned long data) { m_user_data = data; }
	//���[�U�[�f�[�^�擾
	unsigned long user_data() const { return m_user_data; }
	//transform�擾
	const SvgTransform *transform() const { return m_transform; }
	const SvgTransform *abs_transform() const { return m_abs_transform; }
	//�X�^�C���擾
	const SvgStyle *style() const { return &m_style; }
	//�p�X�ɕϊ�
	virtual SvgPath *cnv_to_path();

};

#endif
