/**
 *  Copyright (c) 2017 Panasonic Corporation
 *  Element:           draw function of line block
 */
#include "line_draw.h"
#include "line_debug.h"

#define LINE_OBJECT_RESOURCE_MAX	60 /* �`��I�u�W�F�N�g�����ő吔 (�S�o�͕�) */

typedef struct {				/* �`��̈�ɑ΂���I�t�Z�b�g */
	UH x;
	UH y;
} LINE_DRAW_OFFSET;

typedef struct _LINE_DRAW_RESOURCE_ {
	LINE_DRAW_OBJECT object;
	BOOL isUse;
} LINE_DRAW_RESOURCE;

typedef struct _LINE_RECT_ {
	LINE_POS start;				/* �J�n�ʒu */
	LINE_AREA area;				/* �̈� */
} LINE_RECT;

typedef struct _LINE_FITEDGE_ {	/* ���͂ݏo������ */
	LINE_RECT fit;				/* ������̗̈� */
	struct {					/* �͂ݏo����� */
		UH left;				/* ���� */
		UH right;				/* �E�� */
		UH top;					/* �㑤 */
		UH buttom;				/* ���� */
	} extra;
} LINE_FITEDGE;

static LINE_DRAW_RESOURCE Resource[LINE_OBJECT_RESOURCE_MAX]; /* �`�惊�\�[�X */

static LINE_DRAW_OBJECT* line_New(void);
static void line_Delete(const LINE_DRAW_OBJECT *obj);
static UB* line_GetStartAddr(const LINE_MEMORY *memory, UH x, UH y);
static LINE_ERR line_CheckArea(const LINE_MEMORY *memory, UH x, UH y, UH w, UH h);
static void line_FitEdge(LINE_FITEDGE *edge, const LINE_MEMORY *memory, const LINE_POS *start, const LINE_AREA *area, UH edge_width);
static void line_GetDrawRect(LINE_RECT *rect, const LINE_DRAW_OBJECT *object);
static void line_CalcRectUnion(LINE_RECT *answer, const LINE_RECT *rectA, const LINE_RECT *rectB);
static LINE_ERR line_FillRect(const LINE_MEMORY *memory, UH x, UH y, UH width, UH height, GUI_COLOR_ID color);
static LINE_ERR line_DrawSquare(const LINE_MEMORY *memory, UH x, UH y, UH w, UH h, UH bold, GUI_COLOR_ID color);
static LINE_ERR line_DrawLine(const LINE_MEMORY *memory, const LINE_LINE *line);
static LINE_ERR line_DrawLines(const LINE_MEMORY *memory, const LINE_DRAW_LINES *lines);
static LINE_ERR line_DrawGrid(const LINE_MEMORY *memory, const LINE_DRAW_GRID *grid);
static LINE_ERR line_DrawBox(const LINE_MEMORY *memory, const LINE_DRAW_BOX *box);
static LINE_ERR line_DrawBracket(const LINE_MEMORY *memory, const LINE_DRAW_BRACKET *bracket);
static LINE_ERR line_DrawCross(const LINE_MEMORY *memory, const LINE_DRAW_CROSS *bracket);
static LINE_ERR line_DrawSight(const LINE_MEMORY *memory, const LINE_DRAW_SIGHT *sight);

/**
   @brief   �������̈�̏�����
   @param[in] *memory : ���������
   @retval LINE_ERR (@ref gui_api)
*/
LINE_ERR Line_ClearMemory(const LINE_MEMORY *memory)
{
	if (memory == NULL) {
		return LINE_ERR_BADARG;
	}

	memset(memory->addr, GUI_COLOR_ID_DELETE, memory->lineOffset * memory->height);

	return LINE_OK;
}

/**
   @brief   �`��I�u�W�F�N�g�̐���
   @param[in] output      : �\����̑I��
   @param[in] drawType    : �`��^�C�v
   @param[in] objectId    : Objcet ����ID
   @param[in] layoutInfo  : �z�u���
   @param[in] color       : �F
   @retval LINE_ERR (@ref gui_api)
*/
LINE_DRAW_OBJECT* Line_CreateDrawObj(LINE_OBJECT_ID objectId)
{
	LINE_DRAW_OBJECT *object;

	object = line_New();
	if (object == NULL) {
		LineDebugPrint("%d fail!!\n", objectId);
		return NULL;
	}

	object->id = objectId;

	return object;
}

/**
   @brief   �`��I�u�W�F�N�g�̍폜
   @param[in] objcet : �폜����I�u�W�F�N�g
   @retval LINE_ERR (@ref gui_api)
*/
LINE_ERR Line_DeleteDrawObj(const LINE_DRAW_OBJECT *object)
{
	if (object == NULL) {
		return LINE_ERR_BADARG;
	}

	line_Delete(object);
	return LINE_OK;
}

/**
   @brief   �`�揈��
   @param[in] object : �`�悷��I�u�W�F�N�g
   @retval LINE_ERR (@ref gui_api)
*/
LINE_ERR Line_Draw(const LINE_DRAW_OBJECT *object)
{
	LINE_ERR result;

	if( object == NULL ){
		return LINE_ERR_BADARG;
	}

	switch( object->drawType ){
	case LINE_DRAW_TYPE_LINES:
		result = line_DrawLines(object->memory, &object->param.lines);
		break;
	case LINE_DRAW_TYPE_GRID:
		result = line_DrawGrid(object->memory, &object->param.grid);
		break;
	case LINE_DRAW_TYPE_BOX:
		result = line_DrawBox(object->memory, &object->param.box);
		break;
	case LINE_DRAW_TYPE_BRACKET:
		result = line_DrawBracket(object->memory, &object->param.bracket);
		break;
	case LINE_DRAW_TYPE_CROSS:
		result = line_DrawCross(object->memory, &object->param.cross);
		break;
	case LINE_DRAW_TYPE_SIGHT:
		result = line_DrawSight(object->memory, &object->param.sight);
		break;
	default:
		result = LINE_ERR_UNEXPECTED;
		break;
	}
	return result;
}

/**
   @brief   �`��̏���
   @param[in] object : ��������I�u�W�F�N�g
   @retval LINE_ERR (@ref gui_api)
*/
LINE_ERR Line_Erase(LINE_DRAW_OBJECT *object)
{
	UB ii;

	if (object == NULL) {
		return LINE_ERR_BADARG;
	}

	switch (object->drawType) {
	case LINE_DRAW_TYPE_LINES:
		for (ii = 0; ii < object->param.lines.num; ii++) {
			object->param.lines.line[ii].color = GUI_COLOR_ID_DELETE;
		}
		break;
	case LINE_DRAW_TYPE_GRID:
		object->param.grid.color = GUI_COLOR_ID_DELETE;
		break;
	case LINE_DRAW_TYPE_BOX:
		object->param.box.color = GUI_COLOR_ID_DELETE;
		object->param.box.edge.color = GUI_COLOR_ID_DELETE;
		break;
	case LINE_DRAW_TYPE_BRACKET:
		object->param.bracket.color = GUI_COLOR_ID_DELETE;
		object->param.bracket.edge.color = GUI_COLOR_ID_DELETE;
		break;
	case LINE_DRAW_TYPE_CROSS:
		object->param.cross.color = GUI_COLOR_ID_DELETE;
		object->param.cross.edge.color = GUI_COLOR_ID_DELETE;
		break;
	case LINE_DRAW_TYPE_SIGHT:
		object->param.sight.bracket.color = GUI_COLOR_ID_DELETE;
		object->param.sight.bracket.edge.color = GUI_COLOR_ID_DELETE;
		object->param.sight.cross.color = GUI_COLOR_ID_DELETE;
		object->param.sight.cross.edge.color = GUI_COLOR_ID_DELETE;
		break;
	default:		 /* Draw �����ŃG���[�ɂȂ�̂ŁA���ɉ������Ȃ� */
		break;
	}
	return Line_Draw(object);
}

/**
   @brief   �I�u�W�F�N�g���m���d�Ȃ��Ă��邩���`�F�b�N
   @param[in] *source : ��r��
   @param[in] *dest   : ��r��
   @retval TRUE: �d�Ȃ��Ă��� / FALSE : �d�Ȃ��Ă��Ȃ�
*/
BOOL Line_IsOverlapping(const LINE_DRAW_OBJECT *source, const LINE_DRAW_OBJECT *dest)
{
	LINE_RECT rect_source, rect_dest;

	if ((source == NULL) || (dest == NULL)) {
		return FALSE;
	}

	/* �I�u�W�F�N�g�̕`���`�͈͂��Z�o���A
	   ���ꂼ��̊e���_�̈ʒu�֌W�̘_���ςŔ��肷��
	   ��`�͈� A �̒��_ Ax1, Ay1, Ax2, Ay2) �� ��`�͈� B �̒��_ Bx1, By1, Bx2, By2 �ɂ���
	   (Ax1 �� Bx2 && Bx1 �� Ax2) && (Ay1 �� By2 && By1 �� Ay2)
	*/
	line_GetDrawRect(&rect_source, source);
	line_GetDrawRect(&rect_dest, dest);

	if ((rect_source.start.x <= (rect_dest.start.x + rect_dest.area.w)) && (rect_dest.start.x <= (rect_source.start.x + rect_source.area.w)) /* parasoft-suppress BD-PB-NOTINIT */
		&& (rect_source.start.y <= (rect_dest.start.y + rect_dest.area.h)) && (rect_dest.start.y <= (rect_source.start.y + rect_source.area.h))) {
		return TRUE;
	}
	return FALSE;
}

/* --- ���[�J���֐� --- */
/**
   @brief   ���\�[�X����`��I�u�W�F�N�g�𐶐�
   @param[in] �Ȃ�
   @retval LINE_DRAW_OBJECT* (�G���[���� NULL)
*/
LINE_DRAW_OBJECT* line_New(void)
{
	UB ii;
	LINE_DRAW_OBJECT *object = NULL;

	for (ii = 0; ii < LINE_OBJECT_RESOURCE_MAX; ii++) {
		if (Resource[ii].isUse != TRUE){
			object = &(Resource[ii].object);
			Resource[ii].isUse = TRUE;
			break;
		}
	}
	return object;
}

/**
   @brief   �`��I�u�W�F�N�g��j�����ă��\�[�X�ɖ߂�
   @param[in] obj : �j������I�u�W�F�N�g
   @retval �Ȃ�
*/
void line_Delete(const LINE_DRAW_OBJECT *object)
{
	UB ii;

	for (ii = 0; ii < LINE_OBJECT_RESOURCE_MAX; ii++) {
		if ((Resource[ii].isUse == TRUE) && (&(Resource[ii].object) == object)) {
			Resource[ii].isUse = FALSE;
			break;
		}
	}
}

/**
   @brief   �w��|�C���g�̏������݃������A�h���X���擾
   @param[in] *memory : �`��X�N���[�����
   @param[in] x       : x ���W
   @param[in] y       : y ���W
   @retval UB* (�G���[���� NULL ��Ԃ�)
*/
UB* line_GetStartAddr(const LINE_MEMORY *memory, UH x, UH y)
{
	if (memory == NULL) {
		return NULL;
	}
	return memory->addr + memory->lineOffset * (y + memory->drawOffset.y) + (x + memory->drawOffset.x);
}

/**
   @brief   �w��͈͂��`�惁�����͈͓����`�F�b�N����
   @param[in] *memory : �`��X�N���[�����
   @param[in] x       : x ���W
   @param[in] y       : y ���W
   @param[in] w       : ��
   @param[in] h       : ����
   @retval LINE_ERR (@ref gui_api)
*/
LINE_ERR line_CheckArea(const LINE_MEMORY *memory, UH x, UH y, UH w, UH h)
{
	if (memory == NULL) {
		return LINE_ERR_BADARG;
	}
	if ((w == 0) || (h == 0) || ((x + w) > memory->lineOffset) || ((y + h) > memory->height)) {
		return LINE_ERR_BADARG;
	}
	return LINE_OK;
}

/**
   @brief   ���������ꍇ�A�����������`��͈͂Ɏ��܂�悤�ɕ␳�������Z�l��Ԃ�
   @param[Out] *edge  : ���␳���
   @param[in] *memory : �`��X�N���[�����
   @param[in] x       : x ���W
   @param[in] y       : y ���W
   @param[in] w       : ��
   @param[in] h       : ����
   @retval LINE_ERR (@ref gui_api)
*/
void line_FitEdge(LINE_FITEDGE *edge, const LINE_MEMORY *memory, const LINE_POS *start, const LINE_AREA *area, UH EdgeWidth)
{
	/* �͂ݏo�����l�����ė̈�̈ʒu�T�C�Y���v�Z */
	if ((edge == NULL) || (memory == NULL) || (start == NULL) || (area == NULL) || (EdgeWidth == 0)) {
		return;
	}

	/* ���ʂ̒l���v�Z */
	edge->fit.start.x = start->x - EdgeWidth;	/* pgr0351 */
	edge->fit.start.y = start->y - EdgeWidth;	/* pgr0351 */
	edge->fit.area.w = area->w + EdgeWidth * 2;	/* pgr0351 */
	edge->fit.area.h = area->h + EdgeWidth * 2;	/* pgr0351 */
	edge->extra.left = 0;
	edge->extra.right = 0;
	edge->extra.top = 0;
	edge->extra.buttom = 0;

	/* �͂ݏo�����莞�̕␳ */
	if (start->x < EdgeWidth) { /* ���ɂ͂ݏo�� */
		edge->fit.start.x = 0;
		edge->extra.left = EdgeWidth - start->x; /* pgr0351 */
		edge->fit.area.w -= edge->extra.left;
	}
	if (start->y < EdgeWidth) { /* ��ɂ͂ݏo�� */
		edge->fit.start.y = 0;
		edge->extra.right = EdgeWidth - start->y; /* pgr0351 */
		edge->fit.area.h -= edge->extra.right;
	}
	if ((edge->fit.start.x + edge->fit.area.w) > memory->lineOffset) { /* �E�ɂ͂ݏo�� */
		edge->extra.top = (edge->fit.start.x + edge->fit.area.w) - memory->lineOffset; /* pgr0351 */
		edge->fit.area.w -= edge->extra.top;
	}
	if ((edge->fit.start.y + edge->fit.area.h) > memory->height) { /* ���ɂ͂ݏo�� */
		edge->extra.buttom = (edge->fit.start.y + edge->fit.area.h) - memory->height; /* pgr0351 */
		edge->fit.area.h -= edge->extra.buttom;
	}
}

/**
   @brief   �`��͈͂̎Z�o
   @param[out] *rect  : �Z�o�����͈�
   @param[in] *object : �`��I�u�W�F�N�g
   @retval LINE_ERR (@ref gui_api)
*/
void line_GetDrawRect(LINE_RECT *rect, const LINE_DRAW_OBJECT *object)
{
	const LINE_EDGE *edge = NULL; /* �� (�Ō�ɕ␳��������) */
	LINE_RECT rect_a, rect_b;	/* ���ԉ��Z�p */

	if ((rect == NULL) || (object == NULL)) {
		return;
	}

	switch (object->drawType) {
	case LINE_DRAW_TYPE_LINES:
		if (object->param.lines.num == 0) {
			rect->start.x = 0;
			rect->start.y = 0;
			rect->area.w = 0;
			rect->area.h = 0;
		} else {				/* �����̐��̂����ő�͈͂���� */
			UB ii;
			UH end_x, end_y;
			rect->start.x = object->param.lines.line[0].start.x;
			rect->start.y = object->param.lines.line[0].start.y;
			end_x = object->param.lines.line[0].end.x;
			end_y = object->param.lines.line[0].end.y;
			for (ii = 1; ii < object->param.lines.num; ii++) {
				if (rect->start.x > object->param.lines.line[ii].start.x) {
					rect->start.x = object->param.lines.line[ii].start.x;
				}
				if (rect->start.x > object->param.lines.line[ii].end.x) {
					rect->start.x = object->param.lines.line[ii].end.x;
				}
				if (rect->start.y > object->param.lines.line[ii].start.y) {
					rect->start.y = object->param.lines.line[ii].start.y;
				}
				if (rect->start.y > object->param.lines.line[ii].end.y) {
					rect->start.y = object->param.lines.line[ii].end.y;
				}
				if (end_x < object->param.lines.line[ii].start.x) {
					end_x = object->param.lines.line[ii].start.x;
				}
				if (end_x < object->param.lines.line[ii].end.x) {
					end_x = object->param.lines.line[ii].end.x;
				}
				if (end_y < object->param.lines.line[ii].start.y) {
					end_y = object->param.lines.line[ii].start.y;
				}
				if (end_y < object->param.lines.line[ii].end.y) {
					end_y = object->param.lines.line[ii].end.y;
				}
			}
			rect->area.w = end_x - rect->start.x + 1; /* pgr0351 */
			rect->area.h = end_y - rect->start.y + 1; /* pgr0351 */
		}
		break;
	case LINE_DRAW_TYPE_GRID:
		rect->start = object->param.grid.start;
		rect->area = object->param.grid.area;
		break;
	case LINE_DRAW_TYPE_BOX:
		rect->start = object->param.box.start;
		rect->area = object->param.box.area;
		edge = &(object->param.box.edge);
		break;
	case LINE_DRAW_TYPE_BRACKET:
		rect->start = object->param.bracket.start;
		rect->area = object->param.bracket.area;
		edge = &(object->param.bracket.edge);
		break;
	case LINE_DRAW_TYPE_CROSS:
		rect_a.start = object->param.cross.horizon.start;
		rect_a.area = object->param.cross.horizon.area;
		rect_b.start = object->param.cross.vertical.start;
		rect_b.area = object->param.cross.vertical.area;
		line_CalcRectUnion(rect, &rect_a, &rect_b);
		edge = &(object->param.bracket.edge);
		break;
	case LINE_DRAW_TYPE_SIGHT:
		rect_a.start = object->param.sight.cross.horizon.start;
		rect_a.area = object->param.sight.cross.horizon.area;
		rect_b.start = object->param.sight.cross.vertical.start;
		rect_b.area = object->param.sight.cross.vertical.area;
		line_CalcRectUnion(rect, &rect_a, &rect_b);

		rect_a = *rect;
		rect_b.start = object->param.sight.bracket.start;
		rect_b.area = object->param.sight.bracket.area;
		line_CalcRectUnion(rect, &rect_a, &rect_b);

		edge = (object->param.sight.bracket.edge.width > object->param.sight.cross.edge.width) ? &(object->param.sight.bracket.edge) : &(object->param.sight.cross.edge);
		break;
	default:	/* ���ɉ������Ȃ��B���̕␳���X���[�����͂��B */
		break;
	}
	/* ���̍l�� */
	if ((edge != NULL) && (edge->width > 0)) {
		/* �J�n�ʒu x �̕␳ */
		if (rect->start.x > edge->width) {
			rect->start.x -= edge->width;
			rect->area.w += edge->width;
		} else {
			rect->area.w += rect->start.x;
			rect->start.x = 0;
		}
		/* �J�n�ʒu y �̕␳ */
		if (rect->start.y > edge->width) {
			rect->start.y -= edge->width;
			rect->area.h += edge->width;
		} else {
			rect->area.h += rect->start.y;
			rect->start.y = 0;
		}
		/* �I���ʒu�̕␳ */
		rect->area.w += edge->width;
		rect->area.h += edge->width;
	}
}

/**
   @brief   2 �̋�`�̈�𕹍������̈� (Union ���Z�̌���) ��Ԃ�
   @param[out] answer : ��������
   @param[in] rectA   : �̈� A
   @param[in] rectB   : �̈� B
   @retval �Ȃ�
*/
void line_CalcRectUnion(LINE_RECT *answer, const LINE_RECT *rectA, const LINE_RECT *rectB)
{
	LINE_POS endA, endB, end;
	if ((answer == NULL) || (rectA == NULL) || (rectB == NULL)) {
		return;
	}

	answer->start.x = (rectA->start.x < rectB->start.x) ? rectA->start.x : rectB->start.x; /* pgr0351 */
	answer->start.y = (rectA->start.y < rectB->start.y) ? rectA->start.y : rectB->start.y; /* pgr0351 */
	endA.x = rectA->start.x + rectA->area.w; /* pgr0351 */
	endA.y = rectA->start.y + rectA->area.h; /* pgr0351 */
	endB.x = rectB->start.x + rectB->area.w; /* pgr0351 */
	endB.y = rectB->start.y + rectB->area.h; /* pgr0351 */
	end.x = (endA.x > endB.x) ? endA.x : endB.x; /* pgr0351 */
	end.y = (endA.y > endB.y) ? endA.y : endB.y; /* pgr0351 */
	answer->area.w = end.x - answer->start.x + 1; /* pgr0351 */
	answer->area.h = end.y - answer->start.y + 1; /* pgr0351 */
}

/**
   @brief   �w��͈͂�h��Ԃ�
   @param[in] *memory : �`��X�N���[�����
   @param[in] x       : x ���W
   @param[in] y       : y ���W
   @param[in] width   : ��
   @param[in] height  : ����
   @param[in] color   : �F
   @retval LINE_ERR (@ref gui_api)
*/
LINE_ERR line_FillRect(const LINE_MEMORY *memory, UH x, UH y, UH width, UH height, GUI_COLOR_ID color)
{
	/* �̈�`�F�b�N�͏�ł���Ă���O�� */
	UH line;
	UB *start = line_GetStartAddr(memory, x, y);

	if (start == NULL) {
		return LINE_ERR_BADARG;
	}
	for (line = 0; line < height; line++) {
		memset(start, (UB)color, width); /* pgr0247 */
		start += memory->lineOffset;	 /* pgr0541 */
	}
	return LINE_OK;
}

/**
   @brief   ����т��l�p��`��
   @param[in] *memory : �`��X�N���[�����
   @param[in] x       : �J�n x ���W
   @param[in] y       : �J�n y ���W
   @param[in] w       : ��
   @param[in] h       : ����
   @param[in] bold    : ���̑���
   @param[in] color   : �F
   @retval LINE_ERR (@ref gui_api)
*/
LINE_ERR line_DrawSquare(const LINE_MEMORY *memory, UH x, UH y, UH w, UH h, UH bold, GUI_COLOR_ID color)
{
	LINE_ERR result;

	/* �����̐������͏�ʂŃ`�F�b�N�ς݂̑O�� */

	/* ��� */
	result = line_FillRect(memory, x, y, w, bold, color);
	if (result != LINE_OK) {
		return result;
	}

	/* ���� */
	result = line_FillRect(memory, x, y + h - bold, w, bold, color); /* pgr0397 */
	if (result != LINE_OK) {
		return result;
	}

	/* ���� */
	result = line_FillRect(memory, x, y + bold, bold, h - (bold * 2), color); /* pgr0397 */
	if (result != LINE_OK) {
		return result;
	}

	/* �E�� */
	result = line_FillRect(memory, x + w - bold, y + bold, bold, h - (bold * 2), color); /* pgr0397 */
	return result;
}

/**
   @brief   ����`��
   @param[in] *memory  : �`��X�N���[�����
   @param[in] *line    : �����
   @retval LINE_ERR (@ref gui_api)
*/
LINE_ERR line_DrawLine(const LINE_MEMORY *memory, const LINE_LINE *line)
{
	LINE_RECT rect;
	if ((memory == NULL) || (line == NULL)) {
		return LINE_ERR_BADARG;
	}

	/* �h��ׂ��̈���v�Z */
	if( line->start.x == line->end.x ){ /* ������ */
		rect.start.x = line->start.x;
		rect.area.w = line->bold;
		if( line->start.y > line->end.y ){
			rect.start.y = line->end.y;
			rect.area.h = line->start.y - line->end.y; /* pgr0351 */
		}else{
			rect.start.y = line->start.y;
			rect.area.h = line->end.y - line->start.y; /* pgr0351 */
		}
		rect.area.h += 1;		/* ���W�Ԃ̋����𕝂ɂ��邽�� +1 */
	}else if( line->start.y == line->end.y ){ /* ������ */
		rect.start.y = line->start.y;
		if( line->start.x > line->end.x ){
			rect.start.x = line->end.x;
			rect.area.w = line->start.x - line->end.x; /* pgr0351 */
		}else{
			rect.start.x = line->start.x;
			rect.area.w = line->end.x - line->start.x; /* pgr0351 */
		}
		rect.area.w += 1;		/* ���W�Ԃ̋����𕝂ɂ��邽�� +1 */
		rect.area.h = line->bold;
	}else{						/* �����E�������ȊO�͑Ή����Ȃ� */
		return LINE_ERR_NOT_SUPPORTED;
	}

	/* �͈͂����������Ɏ��܂��Ă��邩�`�F�b�N */
	if( LINE_OK != line_CheckArea(memory, rect.start.x, rect.start.y, rect.area.w, rect.area.h) ){
		return LINE_ERR_BADARG;
	}

	return line_FillRect(memory, rect.start.x, rect.start.y, rect.area.w, rect.area.h, line->color);
}

/**
   @brief   �����̐���`��
   @param[in] *memory : �`��X�N���[�����
   @param[in] *lines  : ���������
   @retval LINE_ERR (@ref gui_api)
*/
LINE_ERR line_DrawLines(const LINE_MEMORY *memory, const LINE_DRAW_LINES *lines)
{
	LINE_ERR result = LINE_OK;
	UB ii;

	if (memory == NULL) {
		return LINE_ERR_NOMEM;
	}

	if (lines == NULL) {
		return LINE_ERR_BADARG;
	}

	for (ii = 0; ii < lines->num; ii++) {
		result = line_DrawLine(memory, &(lines->line[ii]));
		if (result != LINE_OK){
			break;
		}
	}
	return result;
}

/**
   @brief   �i�q��`��
   @param[in] *memory : �`��X�N���[�����
   @param[in] *grid   : �i�q���
   @retval LINE_ERR (@ref gui_api)
*/
LINE_ERR line_DrawGrid(const LINE_MEMORY *memory, const LINE_DRAW_GRID *grid)
{
	LINE_ERR result_h = LINE_OK;
	LINE_ERR result_v = LINE_OK;
	LINE_MEMORY local_memory;

	if (memory == NULL) {
		return LINE_ERR_NOMEM;
	}

	if (grid == NULL) {
		return LINE_ERR_BADARG;
	}

	if (LINE_OK != line_CheckArea(memory, grid->start.x, grid->start.y, grid->area.w, grid->area.h)) {
		return LINE_ERR_BADARG;
	}

	/* �ȍ~�͊i�q�̈�ւ̕`��ƍl����B FillRect ���Ɋi�q�̈�ʒu���I�t�Z�b�g�ŉ����� */
	local_memory.lineOffset = memory->lineOffset; /* ���������͕ς��Ȃ� */
	local_memory.height = grid->area.h;

	if (grid->horizon.bold > 0) { /* ������ */
		if (grid->horizon.interval == 0) {
			result_h = LINE_ERR_BADARG;
		} else if (grid->horizon.bold >= grid->horizon.interval) { /* ������������ꍇ */
			/* �����̓h��ׂ� */
			result_h = line_FillRect(memory, grid->start.x, grid->start.y + grid->horizon.start, local_memory.lineOffset, local_memory.height - grid->horizon.start, grid->color); /* pgr0397 */
		} else {
			UH y;
			for (y = grid->horizon.start; y < local_memory.height; y += grid->horizon.interval) {
				UH h = grid->horizon.bold;
				if ((y + h) > local_memory.height) {
					h = local_memory.height - y; /* pgr0351 */
				}
				result_h = line_FillRect(memory, grid->start.x, grid->start.y + y, grid->area.w, h, grid->color); /* pgr0397 */
				if (result_h != LINE_OK) {
					break;
				}
			}
		}
	}

	if (grid->vertical.bold > 0) { /* ������ */
		if (grid->vertical.interval == 0) {
			result_v = LINE_ERR_BADARG;
		} else if (grid->vertical.bold >= grid->vertical.interval) { /* �i�q����Ȃ��đS�h�� */
			result_v = line_FillRect(memory, grid->start.x + grid->vertical.start, grid->start.y, grid->area.w - grid->vertical.start, local_memory.height, grid->color); /* pgr0397 */
		} else {
			UH x;
			for (x = grid->vertical.start; x < local_memory.lineOffset; x += grid->vertical.interval) {
				UH w = grid->vertical.bold;
				if ((x + w) > local_memory.lineOffset) {
					w = local_memory.lineOffset - x; /* pgr0351 */
				}
				result_v = line_FillRect(memory, grid->start.x + x, grid->start.y, w, local_memory.height, grid->color); /* pgr0397 */
				if (result_v != LINE_OK) {
					break;
				}
			}
		}
	}

	return (result_h == LINE_OK) ? result_v : result_h;
}

/**
   @brief   ���t���l�p��`��
   @param[in] *memory : �`��X�N���[�����
   @param[in] *box   : �i�q���
   @retval LINE_ERR (@ref gui_api)
*/
LINE_ERR line_DrawBox(const LINE_MEMORY *memory, const LINE_DRAW_BOX *box)
{
	LINE_ERR result = LINE_OK;
	BOOL no_hole = FALSE;		/* �l�p�ɂ��蔲�������邩�ǂ��� */

	if (memory == NULL) {
		return LINE_ERR_NOMEM;
	}

	if (box == NULL) {
		return LINE_ERR_BADARG;
	}

	/* �p�����[�^�`�F�b�N (�O���́A�͂ݏo�Ă��Ă����Ȃ�) */
	if ((box->bold == 0) || (box->area.w == 0) || (box->area.h == 0)) {
		return LINE_ERR_BADARG;
	}
	if (LINE_OK != line_CheckArea(memory, box->start.x, box->start.y, box->area.w, box->area.h)) {
		return LINE_ERR_BADARG;
	}

	/* �l�p�`�� */
	if (((box->bold * 2) >= box->area.w) || ((box->bold * 2) >= box->area.h)) { /* ������������ꍇ */
		/* �����̓h��ׂ��ł悢 */
		result = line_FillRect(memory, box->start.x, box->start.y, box->area.w, box->area.h, box->color);
		no_hole = TRUE;
	} else {
		result = line_DrawSquare(memory, box->start.x, box->start.y, box->area.w, box->area.h, box->bold, box->color);
	}
	if (result != LINE_OK) {
		return result;
	}

	/* ���`�� */
	if (box->edge.width != 0) { /* ���̐ݒ肠��̂Ƃ��̂� */
		LINE_RECT edge;
		UH edgeWidthLeft, edgeWidthRight, edgeWidthTop, edgeWidthButtom;

		/* ---�O��--- */
		/* �S�̗̈�ƁA�ʂ̉��������v�Z����B�`��̈���͂ݏo���Ă���ꍇ�͕␳ */
		edge.start.x = box->start.x - box->edge.width;	 /* pgr0351 */
		edge.start.y = box->start.y - box->edge.width;	 /* pgr0351 */
		edge.area.w = box->area.w + box->edge.width * 2; /* pgr0351 */
		edge.area.h = box->area.h + box->edge.width * 2; /* pgr0351 */
		edgeWidthLeft = box->edge.width;
		edgeWidthRight = box->edge.width;
		edgeWidthTop = box->edge.width;
		edgeWidthButtom = box->edge.width;
		if (box->start.x < box->edge.width) {
			edge.start.x = 0;
			edge.area.w -= box->edge.width - box->start.x; /* pgr0351 */
			edgeWidthLeft = box->start.x;
		}
		if (box->start.y < box->edge.width) {
			edge.start.y = 0;
			edge.area.h -= box->edge.width - box->start.y; /* pgr0351 */
			edgeWidthTop = box->start.y;
		}
		if ((edge.start.x + edge.area.w) > memory->lineOffset) {
			edge.area.w -= (edge.start.x + edge.area.w - memory->lineOffset); /* pgr0351 */
			edgeWidthRight = memory->lineOffset - box->start.x + box->area.w; /* pgr0351 */
		}
		if ((edge.start.y + edge.area.h) > memory->height) {
			edge.area.h -= (edge.start.y + edge.area.h - memory->height); /* pgr0351 */
			edgeWidthButtom = memory->height - box->start.y + box->area.h; /* pgr0351 */
		}

		/* �O��(��)�̕`�� */
		if (edgeWidthTop != 0) { /* �l�p����[�̏ꍇ�s�v */
			result = line_FillRect(memory, edge.start.x, edge.start.y, edge.area.w, edgeWidthTop, box->edge.color);
			if (result != LINE_OK) {
				return result;
			}
		}
		/* �O��(��)�̕`�� */
		if (edgeWidthButtom < memory->height) { /* �l�p�����[�܂ł̏ꍇ�s�v */
			result = line_FillRect(memory, edge.start.x, edge.start.y + edge.area.h - edgeWidthButtom, edge.area.w, edgeWidthButtom, box->edge.color); /* pgr0397 */
			if (result != LINE_OK) {
				return result;
			}
		}
		/* �O��(��)�̕`�� */
		if (edgeWidthLeft != 0) { /* �l�p�����[�̏ꍇ�͕s�v */
			result = line_FillRect(memory, edge.start.x, edge.start.y + edgeWidthTop, edgeWidthLeft, edge.area.h - (edgeWidthTop + edgeWidthButtom), box->edge.color); /* pgr0397 */
			if (result != LINE_OK) {
				return result;
			}
		}
		/* �O��(�E)�̕`�� */
		if (edgeWidthRight != 0) { /* �l�p���E�[�̏ꍇ�͕s�v */
			result = line_FillRect(memory, edge.start.x + edge.area.w - edgeWidthRight, edge.start.y + edgeWidthTop, edgeWidthRight, edge.area.h - (edgeWidthTop + edgeWidthButtom), box->edge.color); /* pgr0397 */
			if (result != LINE_OK) {
				return result;
			}
		}

		/* ---����--- */
		if (no_hole == FALSE) {	/* ���蔲���Ȃ� = �����Ȃ� */
			edge.start.x = box->start.x + box->bold;   /* pgr0351 */
			edge.start.y = box->start.y + box->bold;   /* pgr0351 */
			edge.area.w = box->area.w - box->bold * 2; /* pgr0351 */
			edge.area.h = box->area.h - box->bold * 2; /* pgr0351 */

			if (((box->edge.width * 2) >= edge.area.w) || ((box->edge.width * 2) >= edge.area.h)) { /* ������������ꍇ */
				/* �����̓h��ׂ��ł悢 */
				result = line_FillRect(memory, edge.start.x, edge.start.y, edge.area.w, edge.area.h, box->color);
			} else {
				result = line_DrawSquare(memory, edge.start.x, edge.start.y, edge.area.w, edge.area.h, box->edge.width, box->color);
			}
			if (result != LINE_OK) {
				return result;
			}
		}
	}
	return result;
}

/**
   @brief   �ꊇ�ʎl�p (�l���ɂ������̐�������l�p) ��`��
   @param[in] *memory : �`��X�N���[�����
   @param[in] *grid   : �i�q���
   @retval LINE_ERR (@ref gui_api)
*/
LINE_ERR line_DrawBracket(const LINE_MEMORY *memory, const LINE_DRAW_BRACKET *bracket)
{
	LINE_RECT rect;
	LINE_ERR result = LINE_OK;

	if (memory == NULL) {
		return LINE_ERR_NOMEM;
	}

	if (bracket == NULL) {
		return LINE_ERR_BADARG;
	}

	/* �p�����[�^�`�F�b�N (�����͂ݏo�Ă��Ă����Ȃ�) */
	if ((bracket->bold == 0) || (bracket->area.w == 0) || (bracket->area.h == 0) || (bracket->hook.w == 0) || (bracket->hook.h == 0)) {
		return LINE_ERR_BADARG;
	}
	if (LINE_OK != line_CheckArea(memory, bracket->start.x, bracket->start.y, bracket->area.w, bracket->area.h)) {
		return LINE_ERR_BADARG;
	}

	/* ���`�� */
	if (bracket->edge.width != 0) { /* ���̐ݒ肠��̂Ƃ��̂� */
		LINE_FITEDGE edge;
		line_FitEdge(&edge, memory, &bracket->start, &bracket->area, bracket->edge.width);

		/* �`�� */
		if ((bracket->bold >= bracket->hook.w) || (bracket->bold >= bracket->hook.h)) {	/* �������߂���ꍇ�A�����̎l�p */
			/* ���� */
			rect.area.w = bracket->hook.w + bracket->edge.width * 2 - edge.extra.left; /* pgr0351 */
			rect.area.h = bracket->hook.h + bracket->edge.width * 2 - edge.extra.top; /* pgr0351 */
			rect.start.x = edge.fit.start.x;
			rect.start.y = edge.fit.start.y;
			result = line_FillRect(memory, rect.start.x, rect.start.y, rect.area.w, rect.area.h, bracket->edge.color);
			if (result != LINE_OK) {
				return result;
			}
			/* �E�� */
			rect.area.w = bracket->hook.w + bracket->edge.width * 2 - edge.extra.right;	/* pgr0351 */
			rect.start.x = edge.fit.start.x + edge.fit.area.w - rect.area.w; /* pgr0351 */
			result = line_FillRect(memory, rect.start.x, rect.start.y, rect.area.w, rect.area.h, bracket->edge.color);
			if (result != LINE_OK) {
				return result;
			}
			/* ���� */
			rect.area.w = bracket->hook.w + bracket->edge.width * 2 - edge.extra.left; /* pgr0351 */
			rect.area.h = bracket->hook.h + bracket->edge.width * 2 - edge.extra.buttom; /* pgr0351 */
			rect.start.x = edge.fit.start.x;
			rect.start.y = edge.fit.start.y + edge.fit.area.h - rect.area.h; /* pgr0351 */
			result = line_FillRect(memory, rect.start.x, rect.start.y, rect.area.w, rect.area.h, bracket->edge.color);
			if (result != LINE_OK) {
				return result;
			}
			/* �E�� */
			rect.area.w = bracket->hook.w + bracket->edge.width * 2 - edge.extra.right;	/* pgr0351 */
			rect.start.x = edge.fit.start.x + edge.fit.area.w - rect.area.w; /* pgr0351 */
			result = line_FillRect(memory, rect.start.x, rect.start.y, rect.area.w, rect.area.h, bracket->edge.color);
			if (result != LINE_OK) {
				return result;
			}
		} else {					/* ���ʂ��ꊇ�� */
			/* ���� */
			rect.area.w = bracket->hook.w + bracket->edge.width * 2 - edge.extra.left; /* pgr0351 */
			rect.area.h = bracket->bold + bracket->edge.width * 2 - edge.extra.top;	/* pgr0351 */
			rect.start.x = edge.fit.start.x;
			rect.start.y = edge.fit.start.y;
			result = line_FillRect(memory, rect.start.x, rect.start.y, rect.area.w, rect.area.h, bracket->edge.color);
			if (result != LINE_OK) {
				return result;
			}

			rect.start.y += rect.area.h;
			rect.area.w = bracket->bold + bracket->edge.width * 2 - edge.extra.left; /* pgr0351 */
			rect.area.h = bracket->hook.h + bracket->edge.width * 2 - edge.extra.top - rect.area.h;	/* pgr0351 */
			result = line_FillRect(memory, rect.start.x, rect.start.y, rect.area.w, rect.area.h, bracket->edge.color);
			if (result != LINE_OK) {
				return result;
			}

			/* �E�� */
			rect.area.w = bracket->hook.w + bracket->edge.width * 2 - edge.extra.right;	/* pgr0351 */
			rect.area.h = bracket->bold + bracket->edge.width * 2 - edge.extra.top;	/* pgr0351 */
			rect.start.x = edge.fit.start.x + edge.fit.area.w - rect.area.w; /* pgr0351 */
			rect.start.y = edge.fit.start.y;
			result = line_FillRect(memory, rect.start.x, rect.start.y, rect.area.w, rect.area.h, bracket->edge.color);
			if( result != LINE_OK ){
				return result;
			}

			rect.start.y += rect.area.h;
			rect.area.w = bracket->bold + bracket->edge.width * 2 - edge.extra.right; /* pgr0351 */
			rect.area.h = bracket->hook.h + bracket->edge.width * 2 - edge.extra.top - rect.area.h;	/* pgr0351 */
			rect.start.x = edge.fit.start.x + edge.fit.area.w - rect.area.w; /* pgr0351 */
			result = line_FillRect(memory, rect.start.x, rect.start.y, rect.area.w, rect.area.h, bracket->edge.color);
			if (result != LINE_OK) {
				return result;
			}

			/* ���� */
			rect.area.w = bracket->hook.w + bracket->edge.width * 2 - edge.extra.left; /* pgr0351 */
			rect.area.h = bracket->bold + bracket->edge.width * 2 - edge.extra.buttom; /* pgr0351 */
			rect.start.x = edge.fit.start.x;
			rect.start.y = edge.fit.start.y + edge.fit.area.h - rect.area.h; /* pgr0351 */
			result = line_FillRect(memory, rect.start.x, rect.start.y, rect.area.w, rect.area.h, bracket->edge.color);
			if (result != LINE_OK) {
				return result;
			}

			rect.area.w = bracket->bold + bracket->edge.width * 2 - edge.extra.left; /* pgr0351 */
			rect.area.h = bracket->hook.h + bracket->edge.width * 2 - edge.extra.buttom - rect.area.h; /* pgr0351 */
			rect.start.y -= rect.area.h;
			result = line_FillRect(memory, rect.start.x, rect.start.y, rect.area.w, rect.area.h, bracket->edge.color);
			if (result != LINE_OK) {
				return result;
			}

			/* �E�� */
			rect.area.w = bracket->hook.w + bracket->edge.width * 2 - edge.extra.right;	/* pgr0351 */
			rect.area.h = bracket->bold + bracket->edge.width * 2 - edge.extra.buttom; /* pgr0351 */
			rect.start.x = edge.fit.start.x + edge.fit.area.w - rect.area.w; /* pgr0351 */
			rect.start.y = edge.fit.start.y + edge.fit.area.h - rect.area.h; /* pgr0351 */
			result = line_FillRect(memory, rect.start.x, rect.start.y, rect.area.w, rect.area.h, bracket->edge.color);
			if (result != LINE_OK) {
				return result;
			}

			rect.area.w = bracket->bold + bracket->edge.width * 2 - edge.extra.right; /* pgr0351 */
			rect.area.h = bracket->hook.h + bracket->edge.width * 2 - edge.extra.buttom - rect.area.h; /* pgr0351 */
			rect.start.x = edge.fit.start.x + edge.fit.area.w - rect.area.w; /* pgr0351 */
			rect.start.y -= rect.area.h;
			result = line_FillRect(memory, rect.start.x, rect.start.y, rect.area.w, rect.area.h, bracket->edge.color);
			if (result != LINE_OK) {
				return result;
			}
		}
	} /* ���̕`�悱���܂� */

	/* �{�� */
	if ((bracket->bold >= bracket->hook.w) || (bracket->bold >= bracket->hook.h)) {	/* �������߂���ꍇ�A�����̎l�p */
		/* ���� */
		rect.area.w = bracket->hook.w;
		rect.area.h = bracket->hook.h;
		rect.start.x = bracket->start.x;
		rect.start.y = bracket->start.y;
		result = line_FillRect(memory, rect.start.x, rect.start.y, rect.area.w, rect.area.h, bracket->edge.color);
		if (result != LINE_OK) {
			return result;
		}
		/* �E�� */
		rect.start.x = bracket->start.x + bracket->area.w - rect.area.w; /* pgr0351 */
		result = line_FillRect(memory, rect.start.x, rect.start.y, rect.area.w, rect.area.h, bracket->edge.color);
		if (result != LINE_OK) {
			return result;
		}
		/* ���� */
		rect.start.x = bracket->start.x;
		rect.start.y = bracket->start.y + bracket->area.h - rect.area.h; /* pgr0351 */
		result = line_FillRect(memory, rect.start.x, rect.start.y, rect.area.w, rect.area.h, bracket->edge.color);
		if (result != LINE_OK) {
			return result;
		}
		/* �E�� */
		rect.start.x = bracket->start.x + bracket->area.w - rect.area.w; /* pgr0351 */
		result = line_FillRect(memory, rect.start.x, rect.start.y, rect.area.w, rect.area.h, bracket->edge.color);
		if (result != LINE_OK) {
			return result;
		}
	} else {					/* ���ʂ��ꊇ�� */
		/* ���� */
		rect.area.w = bracket->hook.w;
		rect.area.h = bracket->bold;
		rect.start.x = bracket->start.x;
		rect.start.y = bracket->start.y;
		result = line_FillRect(memory, rect.start.x, rect.start.y, rect.area.w, rect.area.h, bracket->color);
		if (result != LINE_OK) {
			return result;
		}

		rect.start.y += rect.area.h;
		rect.area.w = bracket->bold;
		rect.area.h = bracket->hook.h - rect.area.h; /* pgr0351 */
		result = line_FillRect(memory, rect.start.x, rect.start.y, rect.area.w, rect.area.h, bracket->color);
		if (result != LINE_OK) {
			return result;
		}

		/* �E�� */
		rect.area.w = bracket->hook.w;
		rect.area.h = bracket->bold;
		rect.start.x = bracket->start.x + bracket->area.w - rect.area.w; /* pgr0351 */
		rect.start.y = bracket->start.y;
		result = line_FillRect(memory, rect.start.x, rect.start.y, rect.area.w, rect.area.h, bracket->color);
		if (result != LINE_OK) {
			return result;
		}

		rect.start.y += rect.area.h;
		rect.area.w = bracket->bold;
		rect.area.h = bracket->hook.h - rect.area.h; /* pgr0351 */
		rect.start.x = bracket->start.x + bracket->area.w - rect.area.w; /* pgr0351 */
		result = line_FillRect(memory, rect.start.x, rect.start.y, rect.area.w, rect.area.h, bracket->color);
		if (result != LINE_OK) {
			return result;
		}

		/* ���� */
		rect.area.w = bracket->hook.w;
		rect.area.h = bracket->bold;
		rect.start.x = bracket->start.x;
		rect.start.y = bracket->start.y + bracket->area.h - rect.area.h; /* pgr0351 */
		result = line_FillRect(memory, rect.start.x, rect.start.y, rect.area.w, rect.area.h, bracket->color);
		if (result != LINE_OK) {
			return result;
		}

		rect.area.w = bracket->bold;
		rect.area.h = bracket->hook.h - rect.area.h; /* pgr0351 */
		rect.start.y -= rect.area.h;
		result = line_FillRect(memory, rect.start.x, rect.start.y, rect.area.w, rect.area.h, bracket->color);
		if (result != LINE_OK) {
			return result;
		}

		/* �E�� */
		rect.area.w = bracket->hook.w;
		rect.area.h = bracket->bold;
		rect.start.x = bracket->start.x + bracket->area.w - rect.area.w; /* pgr0351 */
		rect.start.y = bracket->start.y + bracket->area.h - rect.area.h; /* pgr0351 */
		result = line_FillRect(memory, rect.start.x, rect.start.y, rect.area.w, rect.area.h, bracket->color);
		if (result != LINE_OK) {
			return result;
		}

		rect.area.w = bracket->bold;
		rect.area.h = bracket->hook.h - rect.area.h; /* pgr0351 */
		rect.start.x = bracket->start.x + bracket->area.w - rect.area.w; /* pgr0351 */
		rect.start.y -= rect.area.h;
		result = line_FillRect(memory, rect.start.x, rect.start.y, rect.area.w, rect.area.h, bracket->color);
		if (result != LINE_OK) {
			return result;
		}
	}
	return result;
}

/**
   @brief   �\����`��
   @param[in] *memory : �`��X�N���[�����
   @param[in] *cross  : �\�����
   @retval LINE_ERR (@ref gui_api)
*/
LINE_ERR line_DrawCross(const LINE_MEMORY *memory, const LINE_DRAW_CROSS *cross)
{
	LINE_RECT rect;
	LINE_ERR result = LINE_OK;

	if (memory == NULL) {
		return LINE_ERR_NOMEM;
	}

	if (cross == NULL) {
		return LINE_ERR_BADARG;
	}

	/* �p�����[�^�`�F�b�N (�����͂ݏo�Ă��Ă����Ȃ�) */
	if (LINE_OK != line_CheckArea(memory, cross->horizon.start.x, cross->horizon.start.y, cross->horizon.area.w, cross->horizon.area.h)) {
		return LINE_ERR_BADARG;
	}
	if (LINE_OK != line_CheckArea(memory, cross->vertical.start.x, cross->vertical.start.y, cross->vertical.area.w, cross->vertical.area.h)) {
		return LINE_ERR_BADARG;
	}

	/* ������ */
	if ((cross->horizon.area.w != 0) && (cross->horizon.area.h != 0)) {
		UH cross_part_w = (cross->horizon.area.w - cross->horizon.blank) / 2;

		/* ���`�� */
		if (cross->edge.width != 0) { /* ������ */
			LINE_FITEDGE edge;
			line_FitEdge(&edge, memory, &cross->horizon.start, &cross->horizon.area, cross->edge.width);

			rect.start = edge.fit.start;
			rect.area.h = edge.fit.area.h;
			if (cross->horizon.blank <= (cross->edge.width * 2)) { /* ���ԂȂ� */
				rect.area.w = edge.fit.area.w;
				result = line_FillRect(memory, rect.start.x, rect.start.y, rect.area.w, rect.area.h, cross->edge.color);
				if (result != LINE_OK) {
					return result;
				}
			} else {			/* ���� */
				/* ���� */
				rect.area.w = cross_part_w + cross->edge.width * 2 - edge.extra.left; /* pgr0351 */
				result = line_FillRect(memory, rect.start.x, rect.start.y, rect.area.w, rect.area.h, cross->edge.color);
				if (result != LINE_OK) {
					return result;
				}

				/* �E�� */
				rect.start.x += rect.area.w + cross->horizon.blank - cross->edge.width * 2;	/* pgr0351 */
				rect.area.w = cross_part_w + cross->edge.width * 2 - edge.extra.right; /* pgr0351 */
				result = line_FillRect(memory, rect.start.x, rect.start.y, rect.area.w, rect.area.h, cross->edge.color);
				if (result != LINE_OK) {
					return result;
				}
			}
		} /* ���`�悱���܂� */

		/* �{�� */
		rect.start = cross->horizon.start;
		rect.area.h = cross->horizon.area.h;
		if (cross->horizon.blank == 0) { /* ���ԂȂ� */
			rect.area.w = cross->horizon.area.w;
			result = line_FillRect(memory, rect.start.x, rect.start.y, rect.area.w, rect.area.h, cross->color);
			if (result != LINE_OK) {
				return result;
			}
		} else {
			/* �㑤 */
			rect.area.w = cross_part_w;
			result = line_FillRect(memory, rect.start.x, rect.start.y, rect.area.w, rect.area.h, cross->color);
			if (result != LINE_OK) {
				return result;
			}

			/* ���� */
			rect.start.x += rect.area.w + cross->horizon.blank;	/* pgr0351 */
			result = line_FillRect(memory, rect.start.x, rect.start.y, rect.area.w, rect.area.h, cross->color);
			if (result != LINE_OK) {
				return result;
			}
		}
	} /* �����������܂� */

	/* ������ */
	if ((cross->vertical.area.w != 0) && (cross->vertical.area.h != 0)) {
		UH cross_part_h = (cross->vertical.area.h - cross->vertical.blank) / 2;

		/* ���`�� */
		if (cross->edge.width != 0) { /* ������ */
			LINE_FITEDGE edge;
			line_FitEdge(&edge, memory, &cross->vertical.start, &cross->vertical.area, cross->edge.width);

			rect.start = edge.fit.start;
			rect.area.w = edge.fit.area.w;
			if (cross->vertical.blank <= (cross->edge.width * 2)) { /* ���ԂȂ� */
				rect.area.h = edge.fit.area.h;
				result = line_FillRect(memory, rect.start.x, rect.start.y, rect.area.w, rect.area.h, cross->edge.color);
				if( result != LINE_OK ){
					return result;
				}
			} else {			/* ���� */
				/* �㑤 */
				rect.area.h = cross_part_h + cross->edge.width * 2 - edge.extra.top; /* pgr0351 */
				result = line_FillRect(memory, rect.start.x, rect.start.y, rect.area.w, rect.area.h, cross->edge.color);
				if (result != LINE_OK) {
					return result;
				}

				/* ���� */
				rect.start.y += rect.area.h + cross->vertical.blank - cross->edge.width * 2; /* pgr0351 */
				rect.area.h = cross_part_h + cross->edge.width * 2 - edge.extra.buttom;	/* pgr0351 */
				result = line_FillRect(memory, rect.start.x, rect.start.y, rect.area.w, rect.area.h, cross->edge.color);
				if (result != LINE_OK) {
					return result;
				}
			}
		} /* ���`�悱���܂� */

		/* �{�� */
		rect.start = cross->vertical.start;
		rect.area.w = cross->vertical.area.w;
		if (cross->vertical.blank == 0) { /* ���ԂȂ� */
			rect.area.h = cross->vertical.area.h;
			result = line_FillRect(memory, rect.start.x, rect.start.y, rect.area.w, rect.area.h, cross->color);
			if (result != LINE_OK) {
				return result;
			}
		} else {
			/* �㑤 */
			rect.area.h = cross_part_h;
			result = line_FillRect(memory, rect.start.x, rect.start.y, rect.area.w, rect.area.h, cross->color);
			if (result != LINE_OK) {
				return result;
			}

			/* ���� */
			rect.start.y += rect.area.h + cross->vertical.blank; /* pgr0351 */
			result = line_FillRect(memory, rect.start.x, rect.start.y, rect.area.w, rect.area.h, cross->color);
			if (result != LINE_OK) {
				return result;
			}
		}
	} /* �����������܂� */
	return result;
}

/**
   @brief   �Ə��` (�ꊇ�ʎl�p�̒��ɏ\��) ��`��
   @param[in] *memory : �`��X�N���[�����
   @param[in] *sight  : �Ə����
   @retval LINE_ERR (@ref gui_api)
*/
LINE_ERR line_DrawSight(const LINE_MEMORY *memory, const LINE_DRAW_SIGHT *sight)
{
	LINE_ERR result_bracket, result_cross;

	if (sight == NULL) {
		return LINE_ERR_BADARG;
	}

	result_bracket = line_DrawBracket(memory, &sight->bracket);
	result_cross = line_DrawCross(memory, &sight->cross);

	if (result_bracket != LINE_OK) {
		return result_bracket;
	}
	return result_cross;
}
