#include "stdafx.h"
#include "string.h"
#include "expat.h"
#include "SvgParser.h"
#include "SvgUtil.h"
#include "SvgStyle.h"

static void handler_element_start(void *userData, const XML_Char *name, const XML_Char *atts[]);
static void handler_element_end(void *userData, const XML_Char *name);
static void handler_character_data(void *userData, const XML_Char *s, int len);

SvgParser::SvgParser()
	: m_defs(NULL, NULL)
{
	m_error = 0;	//�G���[�N���A
	m_depth = 1;
	m_skip_depth = 0;
	m_root = NULL;
	m_current = NULL;
	m_is_parse_style = false;
}

SvgParser::~SvgParser()
{
	delete(m_root);

	if (!m_styles.empty()) {
		for( SVGSTYLEMAP::iterator itr = m_styles.begin(); itr != m_styles.end(); ++itr ) {
			delete itr->second;
		}
	}
}

int SvgParser::parse(const char *filename)
{
	FILE			*fp;
	fpos_t			fsize;
	size_t			bufsize;
	char			*buf;
	XML_Parser		parser;
	XML_Status		xmlerr;

	//�t�@�C���I�[�v��
	fp = fopen(filename, "rb");
	if (fp == NULL) {
		fprintf(stderr, "ERROR: File Not Found %s\n", filename);
		return -1;
	}

	//�t�@�C���T�C�Y
	fseek(fp, 0, SEEK_END); 
	fgetpos(fp, &fsize);
	fseek(fp, 0, SEEK_SET); 

	//�������ɓǂݍ���
	bufsize = (size_t)fsize;
	buf = (char *)malloc(bufsize);
	fread(buf, 1, bufsize, fp);

	//�t�@�C���N���[�Y
	fclose(fp);

	//�p�[�T�[������
	parser = XML_ParserCreate(NULL);
	if (parser == NULL) {
		fprintf(stderr, "ERROR: Create Parser Error\n");
		return -1;
	}
	//���[�U�[�f�[�^��this�ݒ�
	XML_SetUserData(parser, this);
	//�n���h���ݒ�
	XML_SetElementHandler(parser, handler_element_start, handler_element_end);
	XML_SetCharacterDataHandler(parser, handler_character_data);

	//�p�[�X
	xmlerr = XML_Parse(parser, buf, (int)bufsize, 1);

	//�p�[�T�[�폜
	XML_ParserFree(parser);

	//���������
	free(buf);

	if (xmlerr != XML_STATUS_OK) {
		fprintf(stderr, "ERROR: Parse Xml Error\n");
		return -1;
	}

	if (m_error != 0) {
		fprintf(stderr, "ERROR: Parse Error\n");
		return -1;
	}

	return 0;
}

static void handler_element_start(void *userData, const XML_Char *name, const XML_Char *atts[])
{
	SvgParser *p = (SvgParser*)userData;
	p->element_start(name, atts);
}

static void handler_element_end(void *userData, const XML_Char *name)
{
	SvgParser *p = (SvgParser*)userData;
	p->element_end(name);
}

void SvgParser::element_start(const char *name, const char *atts[])
{
	if (m_skip_depth == 0) {
		//svg�G�������g
		if (!strcmp(name, "svg")) {
			//svg
			SVG_DPRINTF("<svg>\n");
			SvgSvg *obj = NEW SvgSvg(this, m_current);
			//�������
			obj->parse_atts(atts);
			//���[�g�ɐݒ�
			m_root = obj;
			//�J�����g�O���[�v�X�V
			m_current = obj;
		} else
		//defs�G�������g
		if (!strcmp(name, "defs")) {
			//defs
			SVG_DPRINTF("<defs>\n");
			m_defs.set_parent(m_current);
			m_current = &m_defs;		//��`��m_defs�ɒǉ����� defs���l�X�g����Ă����NG
		} else
		//g�G�������g
		if (!strcmp(name, "g")) {
			//g
			SVG_DPRINTF("<g>\n");
			SvgGroup *obj = NEW SvgGroup(this, m_current);
			//�������
			obj->parse_atts(atts);
			//�J�����g�O���[�v�ɒǉ�
			m_current->add(obj);
			//�J�����g�O���[�v�X�V
			m_current = obj;
		} else
		//circle�G�������g
		if (!strcmp(name, "circle")) {
			//circle
			SVG_DPRINTF("<circle>\n");
			SvgCircle *obj = NEW SvgCircle(this, m_current);
			//�������
			obj->parse_atts(atts);
			//�J�����g�O���[�v�ɒǉ�
			m_current->add(obj);
			//current�ɐݒ肵�Ȃ��̂�element_end�ŊK�w���߂�Ȃ��悤�ɃX�L�b�v�ݒ肵�Ă���
			m_skip_depth = m_depth;
		} else
		//ellipse�G�������g
		if (!strcmp(name, "ellipse")) {
			//ellipse
			SVG_DPRINTF("<ellipse>\n");
			SvgEllipse *obj = NEW SvgEllipse(this, m_current);
			//�������
			obj->parse_atts(atts);
			//�J�����g�O���[�v�ɒǉ�
			m_current->add(obj);
			//current�ɐݒ肵�Ȃ��̂�element_end�ŊK�w���߂�Ȃ��悤�ɃX�L�b�v�ݒ肵�Ă���
			m_skip_depth = m_depth;
		} else
		//line�G�������g
		if (!strcmp(name, "line")) {
			//ellipse
			SVG_DPRINTF("<line>\n");
			SvgLine *obj = NEW SvgLine(this, m_current);
			//�������
			obj->parse_atts(atts);
			//�J�����g�O���[�v�ɒǉ�
			m_current->add(obj);
			//current�ɐݒ肵�Ȃ��̂�element_end�ŊK�w���߂�Ȃ��悤�ɃX�L�b�v�ݒ肵�Ă���
			m_skip_depth = m_depth;
		} else
		//path�G�������g
		if (!strcmp(name, "path")) {
			//path
			SVG_DPRINTF("<path>\n");
			SvgPath *obj = NEW SvgPath(this, m_current);
			//�������
			obj->parse_atts(atts);
			//�J�����g�O���[�v�ɒǉ�
			m_current->add(obj);
			//current�ɐݒ肵�Ȃ��̂�element_end�ŊK�w���߂�Ȃ��悤�ɃX�L�b�v�ݒ肵�Ă���
			m_skip_depth = m_depth;
		} else
		//polygon�G�������g
		if (!strcmp(name, "polygon")) {
			//polygon
			SVG_DPRINTF("<polygon>\n");
			SvgPolygon *obj = NEW SvgPolygon(this, m_current);
			//�������
			obj->parse_atts(atts);
			//�J�����g�O���[�v�ɒǉ�
			m_current->add(obj);
			//current�ɐݒ肵�Ȃ��̂�element_end�ŊK�w���߂�Ȃ��悤�ɃX�L�b�v�ݒ肵�Ă���
			m_skip_depth = m_depth;
		} else
		//polyline�G�������g
		if (!strcmp(name, "polyline")) {
			//polygon
			SVG_DPRINTF("<polyline>\n");
			SvgPolyline *obj = NEW SvgPolyline(this, m_current);
			//�������
			obj->parse_atts(atts);
			//�J�����g�O���[�v�ɒǉ�
			m_current->add(obj);
			//current�ɐݒ肵�Ȃ��̂�element_end�ŊK�w���߂�Ȃ��悤�ɃX�L�b�v�ݒ肵�Ă���
			m_skip_depth = m_depth;
		} else
		//rect�G�������g
		if (!strcmp(name, "rect")) {
			//rect
			SVG_DPRINTF("<rect>\n");
			SvgRect *obj = NEW SvgRect(this, m_current);
			//�������
			obj->parse_atts(atts);
			//�J�����g�O���[�v�ɒǉ�
			m_current->add(obj);
			//current�ɐݒ肵�Ȃ��̂�element_end�ŊK�w���߂�Ȃ��悤�ɃX�L�b�v�ݒ肵�Ă���
			m_skip_depth = m_depth;
		} else
		//linearGradient�G�������g
		if (!strcmp(name, "linearGradient")) {
			//linearGradient
			SVG_DPRINTF("<linearGradient>\n");
			SvgLinearGradient *obj = NEW SvgLinearGradient(this, m_current);
			//�������
			obj->parse_atts(atts);
			//defs�ɒǉ�����
			//�{���Ȃ�J�����g�O���[�v�ɒǉ�����ׂ�������defs�ɂ܂Ƃ܂��Ă�������������₷���̂ł�������
			m_defs.add(obj);
			//�J�����g�O���[�v�X�V
			m_current = obj;
		} else
		//radialGradient�G�������g
		if (!strcmp(name, "radialGradient")) {
			//radialGradient
			SVG_DPRINTF("<radialGradient>\n");
			SvgRadialGradient *obj = NEW SvgRadialGradient(this, m_current);
			//�������
			obj->parse_atts(atts);
			//defs�ɒǉ�����
			//�{���Ȃ�J�����g�O���[�v�ɒǉ�����ׂ�������defs�ɂ܂Ƃ܂��Ă�������������₷���̂ł�������
			m_defs.add(obj);
			//�J�����g�O���[�v�X�V
			m_current = obj;
		} else
		//stop�G�������g
		if (!strcmp(name, "stop")) {
			//stop
			SVG_DPRINTF("<stop>\n");
			//�e���O���f�[�V�����̏ꍇ�������
			SvgGradient *gradient = dynamic_cast<SvgGradient*>(m_current);
			if (gradient != NULL) {
				SvgStop *obj = NEW SvgStop(this, m_current);
				//�������
				obj->parse_atts(atts);
				gradient->add_stop(obj);
			}
			//current�ɐݒ肵�Ȃ��̂�element_end�ŊK�w���߂�Ȃ��悤�ɃX�L�b�v�ݒ肵�Ă���
			m_skip_depth = m_depth;
		} else
		// style�G�������g
		if (!strcmp(name, "style")) {
			//style
			SVG_DPRINTF("<style>\n");
			// �X�^�C���^�O���̂݃X�^�C���p�[�X���s��
			m_is_parse_style = true;
			m_skip_depth = m_depth;
		} else
		{
			//���̑�
			SVG_DPRINTF("<%s>\n", name);
			SVG_DPRINTF("  ignore internal elements...\n");
			//�X�L�b�v
			m_skip_depth = m_depth;
		}
	}
	//�l�X�g�𑝂₷
	m_depth++;
}

void SvgParser::element_end(const char *name)
{
	//�l�X�g�����炷
	m_depth--;

	if (strcmp(name, "style") == 0) {
		// �X�^�C���^�O�O�̓X�^�C���p�[�X���s��Ȃ�
		m_is_parse_style = false;
	}
	
	if (m_skip_depth == 0) {
		SVG_DPRINTF("</%s>\n", name);
		m_current = m_current->parent();
	} else {
		if (m_skip_depth == m_depth) {
			SVG_DPRINTF("</%s>\n", name);
			m_skip_depth = 0;
		}
	}
}

static void handler_character_data(void *userData, const XML_Char *s, int len)
{
	SvgParser *p = (SvgParser*)userData;
	p->charcter_data(s,len);
}

void SvgParser::charcter_data(const char* c, int len)
{
	// ���s�����X�L�b�v
	if (len==1 && c[0]==0x0a) return;

	// �^�u�����X�L�b�v
	if (c[0] == '\t'){
		c++;
		len--;
	}

	if ( m_is_parse_style ) {
		SVG_DPRINTF("handler_SetCharacterData(On)\n");

		// [.�N���X��]�w��̂ݑΉ�
		// [#id��]�w���[�v�f��]�w�蓙�ɂ͔�Ή�
		// �܂��A�����s�̃X�^�C����`�ɂ���Ή�
		string line(c, c+len);
		string class_name = line.substr(0, line.find("{"));		// '.'����'{'��class��
		string style_def  = line.substr(line.find("{") + 1);	// '{'����'}'���X�^�C����`
		style_def.erase(style_def.end()-1);
		
		SvgStyle *style = new SvgStyle();
		style->parse_style(this, m_current->parent(), style_def.c_str());
		
		// �X�^�C����ۑ�
		m_styles[class_name] = style;
	}
}

SvgStyle *SvgParser::find_style_by_class(const char *name) {
	string class_name(name);
	class_name = "." + class_name;
	
	if (m_styles.count(class_name) > 0 ) {
		return m_styles[class_name];
	}

	return NULL;
}
