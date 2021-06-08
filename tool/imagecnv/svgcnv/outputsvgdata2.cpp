#include "stdafx.h"
#include "SvgParser.h"
#include "svgcnv.h"

typedef enum {
	VG_ABSOLUTE = 0,
	VG_RELATIVE = 1
} VGPathAbsRel;

typedef enum {
	VG_CLOSE_PATH	= ( 0 << 1),
	VG_MOVE_TO		= ( 1 << 1),
	VG_LINE_TO		= ( 2 << 1),
	VG_HLINE_TO		= ( 3 << 1),
	VG_VLINE_TO		= ( 4 << 1),
	VG_QUAD_TO		= ( 5 << 1),
	VG_CUBIC_TO		= ( 6 << 1),
	VG_SQUAD_TO		= ( 7 << 1),
	VG_SCUBIC_TO	= ( 8 << 1),
	VG_SCCWARC_TO	= ( 9 << 1),
	VG_SCWARC_TO	= (10 << 1),
	VG_LCCWARC_TO	= (11 << 1),
	VG_LCWARC_TO	= (12 << 1)
} VGPathSegment;

typedef enum {
	VG_MOVE_TO_ABS		= VG_MOVE_TO | VG_ABSOLUTE,
	VG_MOVE_TO_REL		= VG_MOVE_TO | VG_RELATIVE,
	VG_LINE_TO_ABS		= VG_LINE_TO | VG_ABSOLUTE,
	VG_LINE_TO_REL		= VG_LINE_TO | VG_RELATIVE,
	VG_HLINE_TO_ABS		= VG_HLINE_TO | VG_ABSOLUTE,
	VG_HLINE_TO_REL		= VG_HLINE_TO | VG_RELATIVE,
	VG_VLINE_TO_ABS		= VG_VLINE_TO | VG_ABSOLUTE,
	VG_VLINE_TO_REL		= VG_VLINE_TO | VG_RELATIVE,
	VG_QUAD_TO_ABS		= VG_QUAD_TO | VG_ABSOLUTE,
	VG_QUAD_TO_REL		= VG_QUAD_TO | VG_RELATIVE,
	VG_CUBIC_TO_ABS		= VG_CUBIC_TO | VG_ABSOLUTE,
	VG_CUBIC_TO_REL		= VG_CUBIC_TO | VG_RELATIVE,
	VG_SQUAD_TO_ABS		= VG_SQUAD_TO | VG_ABSOLUTE,
	VG_SQUAD_TO_REL		= VG_SQUAD_TO | VG_RELATIVE,
	VG_SCUBIC_TO_ABS	= VG_SCUBIC_TO | VG_ABSOLUTE,
	VG_SCUBIC_TO_REL	= VG_SCUBIC_TO | VG_RELATIVE,
	VG_SCCWARC_TO_ABS	= VG_SCCWARC_TO | VG_ABSOLUTE,
	VG_SCCWARC_TO_REL	= VG_SCCWARC_TO | VG_RELATIVE,
	VG_SCWARC_TO_ABS	= VG_SCWARC_TO | VG_ABSOLUTE,
	VG_SCWARC_TO_REL	= VG_SCWARC_TO | VG_RELATIVE,
	VG_LCCWARC_TO_ABS	= VG_LCCWARC_TO | VG_ABSOLUTE,
	VG_LCCWARC_TO_REL	= VG_LCCWARC_TO | VG_RELATIVE,
	VG_LCWARC_TO_ABS	= VG_LCWARC_TO | VG_ABSOLUTE,
	VG_LCWARC_TO_REL	= VG_LCWARC_TO | VG_RELATIVE
} VGPathCommand;

//ヘッダ
static int output_svgheader(SvgParser *parser, const char *id, OUTPUT_TYPE type, int flag, FILE *fp);
//グラデーション
static int get_gradient_num(SvgParser *parser);
static int get_object_num(SvgParser *parser, SvgGroup *group);
static int output_stops(SvgParser *parser, SvgGradient *obj, const char *id, int flag, FILE *fp);
static int output_gradient_defs(SvgParser *parser, const char *id, int flag, FILE *fp);
static int output_lineargradient_def(SvgParser *parser, SvgLinearGradient *obj, const char *id, int flag, FILE *fp);
static int output_radialgradient_def(SvgParser *parser, SvgRadialGradient *obj, const char *id, int flag, FILE *fp);
//オブジェクト
static int output_objects(SvgParser *parser, SvgGroup *group, const char *id, OUTPUT_TYPE type, int flag, FILE *fp);
static int output_objects_as_path(SvgParser *parser, SvgGroup *group, const char *id, OUTPUT_TYPE type, int flag, FILE *fp);
static int output_objects_data(SvgParser *parser, SvgGroup *group, const char *id, OUTPUT_TYPE type, int flag, SVG_OBJECT_TYPE output_obj_type, int index, FILE *fp);
static int output_objects_data_as_path(SvgParser *parser, SvgGroup *group, const char *id, OUTPUT_TYPE type, int flag, int index, FILE *fp);
static int output_path_data(SvgParser *parser, SvgPath *obj, const char *id, OUTPUT_TYPE type, int flag, FILE *fp);
static int output_polygon_data(SvgParser *parser, SvgPolygon *obj, const char *id, OUTPUT_TYPE type, int flag, FILE *fp);
static int output_polyline_data(SvgParser *parser, SvgPolyline *obj, const char *id, OUTPUT_TYPE type, int flag, FILE *fp);
static int output_circle_data(SvgParser *parser, SvgCircle *obj, const char *id, OUTPUT_TYPE type, int flag, FILE *fp);
static int output_ellipse_data(SvgParser *parser, SvgEllipse *obj, const char *id, OUTPUT_TYPE type, int flag, FILE *fp);
static int output_roundrect_data(SvgParser *parser, SvgRect *obj, const char *id, OUTPUT_TYPE type, int flag, FILE *fp);
static int output_rect_data(SvgParser *parser, SvgRect *obj, const char *id, OUTPUT_TYPE type, int flag, FILE *fp);
static int output_line_data(SvgParser *parser, SvgLine *obj, const char *id, OUTPUT_TYPE type, int flag, FILE *fp);
static int output_objects_header(SvgParser *parser, SvgGroup *group, const char *id, OUTPUT_TYPE type, int flag, int no, FILE *fp);
static int output_objects_header_as_path(SvgParser *parser, SvgGroup *group, const char *id, OUTPUT_TYPE type, int flag, int no, FILE *fp);
static int output_object_header_style_GDI(SvgObject *obj, FILE *fp, const char *id);
static int output_object_header_style_info(SvgObject *obj, FILE *fp, const char *id, int no, int tab_count);
static int output_objects_color(SvgParser *parser, SvgGroup *group, const char *id, OUTPUT_TYPE type, int flag, int no, FILE *fp);
static int output_objects_fillcolor(SvgObject *obj, FILE *fp, const char *id, int tab_count);
static int output_objects_strokecolor(SvgObject *obj, FILE *fp, const char *id, int tab_count);
static SvgPath *make_transformed_path(const SvgPath *obj);
static SVG_OBJECT_TYPE get_output_obj_type(SvgObject *obj);

/* グラデーションデータの開始番号ファイル */
#define GRADIENT_BASE_INDEX_FILE	"gradient_index.tmp"
/* グラデーションデータの開始番号 GENSKETCH互換 */
static int s_gradient_base_index;

int output_svgdata(SvgParser *parser, const char *id, OUTPUT_TYPE type, int flag, FILE *fp)
{
	int ret = 0, r;

	//グラデーション開始番号
	s_gradient_base_index = 1;

	//グラデーション出力
	r = output_gradient_defs(parser, id, flag, fp);
	if (r < 0) {
		ret = r;
	}
	//図形オブジェクト出力
	if (flag & OUTPUT_SVG_CNV_TO_PATH) {
		//SvgPathに変換して出力
		r = output_objects_as_path(parser, parser->root(), id, type, flag, fp);
	} else {
		r = output_objects(parser, parser->root(), id, type, flag, fp);
	}
	if (r < 0) {
		ret = r;
	}
	
	//ヘッダ出力
	r = output_svgheader(parser, id, type, flag, fp);
	if (r < 0) {
		ret = r;
	}
	//終端出力
	//	fprintf (fp, "/* End Marker */\n");
	//	fprintf (fp, "IMAGE_MARKER(%s);\n", id);

	return ret;
}

//SVGヘッダ出力
static int output_svgheader(SvgParser *parser, const char *id, OUTPUT_TYPE type, int flag, FILE *fp)
{
	const char *grf_type_str;
	int grad_num;
	int obj_num;

#if 1
	grf_type_str = "GDI_IMAGE_TYPE_SVG";
#else
	/* SVGタイプ */
	switch (type) {
	case OUTPUT_TYPE_1BPP:
		grf_type_str = "GDI_IMAGE_TYPE_SVG";
		break;
	case OUTPUT_TYPE_8BPP:
	default:
		grf_type_str = "GDI_IMAGE_TYPE_SVG";
		break;
	}
#endif
	/* グラデーション数取得 */
	grad_num = get_gradient_num(parser);
	/* オブジェクト数取得 */
	obj_num = get_object_num(parser, parser->root());
	/* ルートオブジェクト */
	SvgSvg *obj = parser->root();
	int width = (int)obj->width();
	int height = (int)obj->height();
	int bpp;

	if (type == OUTPUT_TYPE_1BPP) {
		bpp = 1;
	} else {
		bpp = 0;
	}

	//GDI用データ形式
	fprintf (fp, "/* Data extern */\n");
	fprintf (fp, "extern const GDI_IMAGE_SVG GDI_IMAGE_%s;\n", id);
	fprintf (fp, "/* Header */\n");
//	fprintf (fp, "static const GDI_PARTS * const partslist%s[];\n", id);
	fprintf (fp, "const GDI_IMAGE_SVG GDI_IMAGE_%s __rodata_imagedata ={%s,%d,%d,0,%d,partslist%s};\n", 
			id, grf_type_str, width, height, obj_num, id);

	fprintf(fp, "\n");

	return 0;
}

//出力するグラデーション数を計算する
static int get_gradient_num(SvgParser *parser)
{
	SvgGroup					*defs = parser->defs();
	SVGOBJECTLIST				*objs = defs->objects();
	SVGOBJECTLIST::iterator		i;
	int							num;

	num = 0;
	for (i = objs->begin(); i != objs->end(); ++i) {
		SvgLinearGradient *obj = dynamic_cast<SvgLinearGradient*>(*i);
		//使用されていれば出力
		if (obj != NULL && obj->ref_count() > 0) {
			num++;
		}
	}

	return num;
}

//出力するオブジェクト数を計算する
static int get_object_num(SvgParser *parser, SvgGroup *group)
{
	SVGOBJECTLIST				*objs = group->objects();
	SVGOBJECTLIST::iterator		i;
	int							num;

	num = 0;
	for (i = objs->begin(); i != objs->end(); ++i) {
		if ( ((*i)->style()->display() != SVGDISPLAY_NONE)
			&& ( (*i)->style()->fill_enable() || (*i)->style()->stroke_enable() )
		){
			const type_info &t = typeid(**i);
			if (t == typeid(SvgGroup)) {
				SvgGroup *obj = static_cast<SvgGroup*>(*i);
				num += get_object_num(parser, obj);
			} else {
				num++;
			}
		}
	}

	return num;
}

//グラデーション出力
static int output_gradient_defs(SvgParser *parser, const char *id, int flag, FILE *fp)
{
	SvgGroup					*defs = parser->defs();
	SVGOBJECTLIST				*objs = defs->objects();
	SVGOBJECTLIST::iterator		i;
	int							index;

	//stop情報出力
	index = 0;
	for (i = objs->begin(); i != objs->end(); ++i) {
		SvgGradient *obj = dynamic_cast<SvgGradient*>(*i);
		//使用されていれば出力
		if (obj != NULL && obj->ref_count() > 0) {
			if (index == 0) {
				fprintf(fp, "/* Gradient */\n");
			}
			//pathなどの出力時に参照できるようにidをuser_dataに設定しておく
			obj->set_user_data(s_gradient_base_index + index);
			//出力
			output_stops(parser, obj, id, flag, fp);
			//id更新
			index++;
		}
	}

	//グラデーションがなければ終了
	if (index == 0) {
		return 0;
	}

	//グラデーション開始番号更新
	s_gradient_base_index += index;
	
	//グラデーション定義情報出力
	for (i = objs->begin(); i != objs->end(); ++i) {
		SvgLinearGradient *linear_gradient_obj = dynamic_cast<SvgLinearGradient*>(*i);
		if (linear_gradient_obj != NULL) {
			if (linear_gradient_obj->ref_count() > 0) {
				//出力
				fprintf(fp, "static const GDI_GRADIENT gradient%s_%d __rodata_imagedata =", id, linear_gradient_obj->user_data());
				output_lineargradient_def(parser, linear_gradient_obj, id, flag, fp);
				fprintf(fp,"};\n");
			}
		} else {
			SvgRadialGradient *radial_gradient_obj = dynamic_cast<SvgRadialGradient*>(*i);
			if (radial_gradient_obj != NULL) {
				if (radial_gradient_obj->ref_count() > 0) {
					//出力
					fprintf(fp, "static const GDI_GRADIENT gradient%s_%d __rodata_imagedata =", id, radial_gradient_obj->user_data());
					output_radialgradient_def(parser, radial_gradient_obj, id, flag, fp);
					fprintf(fp,"};\n");
				}
			}
		}
	}
	fprintf(fp,"\n");

	return 0;
}

//stop出力
static int output_stops(SvgParser *parser, SvgGradient *obj, const char *id, int flag, FILE *fp)
{
	//stops
	int							index = obj->user_data();
	const SVGSTOPS				*stops;
	SVGSTOPS::const_iterator	i;
	bool						first;

	//stop情報取得
	stops = obj->find_stops();
	if (stops == NULL) {
		return 0;
	}

	//stop情報出力
	fprintf (fp, "static const VGfloat gradcolor%s_%d[] __rodata_imagedata ={\n", id, index);
	//
	first = true;
	for (i = stops->begin(); i != stops->end(); ++i) {
		if (!first) {
			fprintf(fp, ",\n");	//区切り記号と改行
		} else {
			first = false;
		}
		fprintf(fp, "\t%.4ff, %.4ff, %.4ff, %.4ff, %.4ff",
			(*i)->offset(),
			(float)(*i)->style()->stop_color()->r / 255,
			(float)(*i)->style()->stop_color()->g / 255,
			(float)(*i)->style()->stop_color()->b / 255,
			(*i)->style()->stop_opacity()
			);
	}
	fprintf(fp,"\n};\n\n");

	return 0;
}

//LinearGradient出力
static int output_lineargradient_def(SvgParser *parser, SvgLinearGradient *obj, const char *id, int flag, FILE *fp)
{
	//stops
	int							index = obj->user_data();
	const SVGSTOPS				*stops;
	SVGSTOPS::const_iterator	i;
	int							stop_num;
	float						x1, y1, x2, y2;
	const SvgTransform			*ref_trans;
	const SvgTransform			*obj_trans;
	SvgTransform				*trans;


	//stop情報取得
	stops = obj->find_stops();
	if (stops == NULL) {
		return 0;
	}
	stop_num = stops->size();

	//グラデーション定義情報出力
	//変換は参照元オブジェクトを基準にする
	ref_trans = obj->referred_object()->abs_transform();
	obj_trans = obj->transform();
	if (ref_trans != NULL && obj_trans != NULL) {
		trans = NEW SvgTransform(ref_trans);
		trans->mul(obj_trans);
	} else if (ref_trans != NULL) {
		trans = NEW SvgTransform(ref_trans);
	} else if (obj_trans != NULL) {
		trans = NEW SvgTransform(obj_trans);
	} else {
		trans = NULL;
	}

	if (trans != NULL) {
		trans->trans_xy(obj->x1(), obj->y1(), &x1, &y1);
		trans->trans_xy(obj->x2(), obj->y2(), &x2, &y2);
		delete trans;
	} else {
		x1 = obj->x1();
		y1 = obj->y1();
		x2 = obj->x2();
		y2 = obj->y2();
	}

	//グラデーションID
	fprintf(fp, "{VG_PAINT_LINEAR_GRADIENT, ");
	//グラデーションベクトル
	fprintf(fp, "%.4ff, %.4ff, %.4ff, %.4ff,", x1, y1, x2, y2 );
	//放射グラデーション半径（０固定）
	fprintf(fp, " %.4ff, ", 0.0f);
	//stop数
	fprintf(fp, "%d, ", stop_num);
	//
	fprintf(fp, "gradcolor%s_%d", id, index);

	return 0;
}

//RadialGradient出力
static int output_radialgradient_def(SvgParser *parser, SvgRadialGradient *obj, const char *id, int flag, FILE *fp)
{
	//stops
	int							index = obj->user_data();
	const SVGSTOPS				*stops;
	SVGSTOPS::const_iterator	i;
	int							stop_num;
	float						cx, cy, fx, fy, r;
	const SvgTransform			*ref_trans;
	const SvgTransform			*obj_trans;
	SvgTransform				*trans;


	//stop情報取得
	stops = obj->find_stops();
	if (stops == NULL) {
		return 0;
	}
	stop_num = stops->size();

	//グラデーション定義情報出力
	//変換は参照元オブジェクトを基準にする
	ref_trans = obj->referred_object()->abs_transform();
	obj_trans = obj->transform();
	if (ref_trans != NULL && obj_trans != NULL) {
		trans = NEW SvgTransform(ref_trans);
		trans->mul(obj_trans);
	} else if (ref_trans != NULL) {
		trans = NEW SvgTransform(ref_trans);
	} else if (obj_trans != NULL) {
		trans = NEW SvgTransform(obj_trans);
	} else {
		trans = NULL;
	}

	if (trans != NULL) {
		trans->trans_xy(obj->cx(), obj->cy(), &cx, &cy);
		trans->trans_xy(obj->fx(), obj->fy(), &fx, &fy);
		delete trans;
	} else {
		cx = obj->cx();
		cy = obj->cy();
		fx = obj->fx();
		fy = obj->fy();
	}
	r = obj->r();

	//グラデーションID
	fprintf(fp, "{VG_PAINT_RADIAL_GRADIENT, ");
	//グラデーションベクトル
	fprintf(fp, "%.4ff, %.4ff, %.4ff, %.4ff, %.4ff, ", cx, cy, fx, fy, r );
	//stop数
	fprintf(fp, "%d, ", stop_num);
	//
	fprintf(fp, "gradcolor%s_%d", id, index);

	return 0;
}

//図形オブジェクト出力
static int output_objects(SvgParser *parser, SvgGroup *group, const char *id, OUTPUT_TYPE type, int flag, FILE *fp)
{
	SVGOBJECTLIST				*objs = group->objects();
	int							output_obj_type;
	int							ret = 0;
	int							i;
	int							obj_no;

	//オブジェクトのデータ出力と種類ごとのインデックス付与
	//種類ごとにまとめて出力する(GENWARE互換)
	for (output_obj_type = 0; output_obj_type < SVG_TYPE_FIGURE_END; output_obj_type++) {
		//CIRCLEはELLIPSEと一緒に出力するためスキップ
		if (output_obj_type == SVG_TYPE_CIRCLE) {
			continue;
		}
		ret = output_objects_data(parser, group, id, type, flag, (SVG_OBJECT_TYPE)output_obj_type, 1, fp);
		if (ret < 0) {
			return ret;
		} else if (ret >= 2) {
			fprintf(fp, "\n");
		}
	}

	fprintf(fp, "/* Color */\n");
#if 1
	ret = output_objects_color(parser, group, id, type, flag, 1, fp);
		if (ret < 0) {
			return ret;
		} else if (ret >= 2) {
			fprintf(fp, "\n");
		}

#else
	for (output_obj_type = 0; output_obj_type < SVG_TYPE_FIGURE_END; output_obj_type++) {
		//CIRCLEはELLIPSEと一緒に出力するためスキップ
		if (output_obj_type == SVG_TYPE_CIRCLE) {
			continue;
		}
		ret = output_objects_color(parser, group, id, type, flag, 1, fp);
		if (ret < 0) {
			return ret;
		} else if (ret >= 2) {
			fprintf(fp, "\n");
		}
	}
#endif
	//オブジェクトのヘッダ出力
	fprintf(fp, "/* Parts */\n");
	obj_no = output_objects_header(parser, group, id, type, flag, 1, fp);	//次のオブジェクトの番号が返る
	if (obj_no < 0) {
		return -1;
	}
	fprintf(fp, "\n");

	//全オブジェクトのテーブル(GDI_PARTS)出力
	fprintf(fp, "static const GDI_PARTS * const partslist%s[] __rodata_imagedata =\n", id);
	fprintf(fp, "{\n");
	for (i = 1; i < obj_no; i++) {
		fprintf(fp, "\t(GDI_PARTS*)&parts%s_%d", id, i);
		if(i != (obj_no - 1)){
			fprintf(fp, ",");
		}
		fprintf(fp, "\n");
	}
	fprintf(fp, "};\n\n");

	return 0;
}

//図形オブジェクトをパスに変換して出力
static int output_objects_as_path(SvgParser *parser, SvgGroup *group, const char *id, OUTPUT_TYPE type, int flag, FILE *fp)
{
	SVGOBJECTLIST				*objs = group->objects();
	int							ret = 0;
	int							i;
	int							obj_no;

	fprintf(fp, "/* path */\n");
	ret = output_objects_data_as_path(parser, group, id, type, flag, 1, fp);
	if (ret < 0) {
		return ret;
	}

	//オブジェクトのヘッダ出力
	fprintf(fp, "/* Parts */\n");
	obj_no = output_objects_header_as_path(parser, group, id, type, flag, 1, fp);	//次のオブジェクトの番号が返る
	if (obj_no < 0) {
		return -1;
	}
	fprintf(fp, "\n");

	//全オブジェクトのテーブル(GDI_PARTS)出力
	fprintf(fp, "static const GDI_PARTS * const partslist%s[] __rodata_imagedata =\n", id);
	fprintf(fp, "{\n");
	for (i = 1; i < obj_no; i++) {
		fprintf(fp, "\t(GDI_PARTS*)&parts%s_%d", id, i);
		if(i != (obj_no - 1)){
			fprintf(fp, ",");
		}
		fprintf(fp, "\n");
	}
	fprintf(fp, "};\n\n");

	return 0;
}

//オブジェクトを出力するときに先頭に出力するコメント文字列取得
inline static const char *get_obj_type_comment_str(SVG_OBJECT_TYPE type)
{
	switch (type) {
	case SVG_TYPE_PATH:
		return "path";
	case SVG_TYPE_POLYGON:
		return "polygon";
	case SVG_TYPE_POLYLINE:
		return "polyline";
	case SVG_TYPE_ELLIPSE:
		return "ellipse";
	case SVG_TYPE_ROUNDRECT:
		return "roundrect";
	case SVG_TYPE_RECT:
		return "rect";
	case SVG_TYPE_LINE:
		return "line";
	default:
		return "????";
	}
}

//図形オブジェクトデータ出力と種類ごとのインデックス付与
//次のインデックスを返す
static int output_objects_data(SvgParser *parser, SvgGroup *group, const char *id, OUTPUT_TYPE type, int flag, SVG_OBJECT_TYPE output_obj_type, int index, FILE *fp)
{
	SVGOBJECTLIST				*objs = group->objects();
	SVGOBJECTLIST::iterator		i;
	SVG_OBJECT_TYPE				obj_type;
	int							ret = 0;
	int							r;

	for (i = objs->begin(); i != objs->end(); ++i) {
		if ((*i)->style()->display() == SVGDISPLAY_NONE) {
			//非表示のデータは出力しない
			continue;
		}
		/* 塗りつぶさないデータは出力しない */
		if( !(*i)->style()->fill_enable() && !(*i)->style()->stroke_enable() ){
			continue;
		}
		
		//出力するときの形式を取得（objの形式と異なる場合がある）
		obj_type = get_output_obj_type(*i);
		//出力しようとしている形式と一致した場合は出力
		if (obj_type == output_obj_type) {
			//コメント
			if (index == 1) {
				fprintf(fp, "/* %s */\n", get_obj_type_comment_str(output_obj_type));
			}
			//インデックス付与
			(*i)->set_user_data(index);
			index++;
			//出力
			switch (obj_type) {
			case SVG_TYPE_PATH:
				if ((*i)->type() == SVG_TYPE_PATH) {
					r = output_path_data(parser, static_cast<SvgPath*>(*i), id, type, flag, fp);
				} else {
					//Path以外はSvgPathに変換してから出力
					SvgPath *obj = (*i)->cnv_to_path();
					if (obj != NULL) {
						r = output_path_data(parser, obj, id, type, flag, fp);
						delete obj;
					} else {
						fprintf(stderr, "ERROR: Convert to Path failed\n");
						r = -1;
					}
				}
				break;
			case SVG_TYPE_POLYGON:
				r = output_polygon_data(parser, static_cast<SvgPolygon*>(*i), id, type, flag, fp);
				break;
			case SVG_TYPE_POLYLINE:
				r = output_polyline_data(parser, static_cast<SvgPolyline*>(*i), id, type, flag, fp);
				break;
			case SVG_TYPE_ELLIPSE:
				//EllipseはCircleの場合があるので判定
				if ((*i)->type() == SVG_TYPE_CIRCLE) {
					r = output_circle_data(parser, static_cast<SvgCircle*>(*i), id, type, flag, fp);
				} else {
					r = output_ellipse_data(parser, static_cast<SvgEllipse*>(*i), id, type, flag, fp);
				}
				break;
			case SVG_TYPE_ROUNDRECT:
				r = output_roundrect_data(parser, static_cast<SvgRect*>(*i), id, type, flag, fp);
				break;
			case SVG_TYPE_RECT:
				r = output_rect_data(parser, static_cast<SvgRect*>(*i), id, type, flag, fp);
				break;
			case SVG_TYPE_LINE:
				r = output_line_data(parser, static_cast<SvgLine*>(*i), id, type, flag, fp);
				break;
			default:
				r = 0;
				break;
			}
		} else
		if (obj_type == SVG_TYPE_GROUP) {
			//グループ
			SvgGroup *obj = static_cast<SvgGroup*>(*i);
			r = output_objects_data(parser, obj, id, type, flag, output_obj_type, index, fp);
			index = r;
		} else
		{
			r = 0;
		}

		//戻り値チェック
		if (r < 0) {
			return r;
		}
	}


	return index;
}

//図形オブジェクトデータをパスに変換して出力と種類ごとのインデックス付与
//次のインデックスを返す
static int output_objects_data_as_path(SvgParser *parser, SvgGroup *group, const char *id, OUTPUT_TYPE type, int flag, int index, FILE *fp)
{
	SVGOBJECTLIST				*objs = group->objects();
	SVGOBJECTLIST::iterator		i;
	SVG_OBJECT_TYPE				obj_type;
	int							ret = 0, r;

	for (i = objs->begin(); i != objs->end(); ++i) {
		if ((*i)->style()->display() == SVGDISPLAY_NONE) {
			//非表示のデータは出力しない
			continue;
		}
		/* 塗りつぶさないデータは出力しない */
		if( !(*i)->style()->fill_enable() && !(*i)->style()->stroke_enable() ){
			continue;
		}
		obj_type = (*i)->type();
		if (obj_type == SVG_TYPE_GROUP) {
			//グループ
			SvgGroup *obj = static_cast<SvgGroup*>(*i);
			r = output_objects_data_as_path(parser, obj, id, type, flag, index, fp);
			index = r;
		} else
		{
			//インデックス付与
			(*i)->set_user_data(index);
			index++;
			//出力
			if (obj_type == SVG_TYPE_PATH) {
				//Path
				SvgPath *obj = static_cast<SvgPath*>(*i);
				r = output_path_data(parser, obj, id, type, flag, fp);
			} else
			{
				//その他
				SvgPath *obj = (*i)->cnv_to_path();
				if (obj != NULL) {
					r = output_path_data(parser, obj, id, type, flag, fp);
					delete obj;
				} else {
					fprintf(stderr, "ERROR: Convert to Path failed\n");
					r = -1;
				}
			}
		}
		//戻り値チェック
		if (r < 0) {
			return r;
		}
	}

	return index;
}

inline static int get_openvg_cmd(SVG_CMD cmd)
{
	switch (cmd) {
	case SVG_CMD_M:
		return VG_MOVE_TO_ABS;
	case SVG_CMD_m:
		return VG_MOVE_TO_REL;
	case SVG_CMD_z:
		return VG_CLOSE_PATH;
	case SVG_CMD_L:
		return VG_LINE_TO_ABS;
	case SVG_CMD_l:
		return VG_LINE_TO_REL;
	case SVG_CMD_H:
		return VG_HLINE_TO_ABS;
	case SVG_CMD_h:
		return VG_HLINE_TO_REL;
	case SVG_CMD_V:
		return VG_VLINE_TO_ABS;
	case SVG_CMD_v:
		return VG_VLINE_TO_REL;
	case SVG_CMD_C:
		return VG_CUBIC_TO_ABS;
	case SVG_CMD_c:
		return VG_CUBIC_TO_REL;
	case SVG_CMD_S:
		return VG_SCUBIC_TO_ABS;
	case SVG_CMD_s:
		return VG_SCUBIC_TO_REL;
	case SVG_CMD_Q:
		return VG_QUAD_TO_ABS;
	case SVG_CMD_q:
		return VG_QUAD_TO_REL;
	case SVG_CMD_T:
		return VG_SQUAD_TO_ABS;
	case SVG_CMD_t:
		return VG_SQUAD_TO_REL;
	case SVG_CMD_A:
		return -1;
	case SVG_CMD_a:
		return -1;
	default:
		return -1;
	}
}

inline static const char *get_openvg_cmd_str(int vgcmd)
{
	switch (vgcmd) {
	case VG_MOVE_TO_ABS:
		return "VG_MOVE_TO_ABS";
	case VG_MOVE_TO_REL:
		return "VG_MOVE_TO_REL";
	case VG_CLOSE_PATH:
		return "VG_CLOSE_PATH";
	case VG_LINE_TO_ABS:
		return "VG_LINE_TO_ABS";
	case VG_LINE_TO_REL:
		return "VG_LINE_TO_REL";
	case VG_HLINE_TO_ABS:
		return "VG_HLINE_TO_ABS";
	case VG_HLINE_TO_REL:
		return "VG_HLINE_TO_REL";
	case VG_VLINE_TO_ABS:
		return "VG_VLINE_TO_ABS";
	case VG_VLINE_TO_REL:
		return "VG_VLINE_TO_REL";
	case VG_CUBIC_TO_ABS:
		return "VG_CUBIC_TO_ABS";
	case VG_CUBIC_TO_REL:
		return "VG_CUBIC_TO_REL";
	case VG_SCUBIC_TO_ABS:
		return "VG_SCUBIC_TO_ABS";
	case VG_SCUBIC_TO_REL:
		return "VG_SCUBIC_TO_REL";
	case VG_QUAD_TO_ABS:
		return "VG_QUAD_TO_ABS";
	case VG_QUAD_TO_REL:
		return "VG_QUAD_TO_REL";
	case VG_SQUAD_TO_ABS:
		return "VG_SQUAD_TO_ABS";
	case VG_SQUAD_TO_REL:
		return "VG_SQUAD_TO_REL";
	default:
		return "????";
	}
}

inline static const char *get_openvg_rule_str(SVGFILLRULE rule)
{
	switch (rule) {
	case SVGFILLRULE_EVENODD:
		return "VG_EVEN_ODD";
	case SVGFILLRULE_NONZERO:
		return "VG_NON_ZERO";
	default:
		return "????";
	}
}

inline static const char *get_openvg_linecap_str(SVGLINECAP cap)
{
	switch (cap) {
	case SVGLINECAP_BUTT:
		return "VG_CAP_BUTT";
	case SVGLINECAP_ROUND:
		return "VG_CAP_ROUND";
	case SVGLINECAP_SQUARE:
		return "VG_CAP_SQUARE";
	default:
		return "????";
	}
}

inline static const char *get_openvg_linejoin_str(SVGLINEJOIN join)
{
	switch (join) {
	case SVGLINEJOIN_MITER:
		return "VG_JOIN_MITER";
	case SVGLINEJOIN_ROUND:
		return "VG_JOIN_ROUND";
	case SVGLINEJOIN_BEVEL:
		return "VG_JOIN_BEVEL";
	default:
		return "????";
	}
}

inline static const char *get_openvg_paintmode_str(bool fill, bool stroke)
{
	if (fill && stroke) {
		return "(VG_FILL_PATH|VG_STROKE_PATH)";
	} else if (fill) {
		return "(VG_FILL_PATH)";
	} else if (stroke) {
		return "(VG_STROKE_PATH)";
	} else {
		return "(VGPaintMode)0";
	}
}

static int output_path_data(SvgParser *parser, SvgPath *obj, const char *id, OUTPUT_TYPE type, int flag, FILE *fp)
{
	const SVGCMDS				*cmds;
	SVGCMDS::const_iterator		cmd_i;
	const SVGCOORDS				*coords;
	SVGCOORDS::const_iterator	coord_i;
	SVGCOORDS					tmp_coords;
	SVG_CMD						cmd;
	int							vgcmd;
	bool						first;
	int							coord_index;
	int							coord_num;
	const SvgTransform			*trans;
	float						x, y;
	float						abs_x, abs_y;
	float						out_x, out_y;
	int							i;
	int							index = obj->user_data();
	SvgPath						*transformed_path = NULL;

	//座標変換チェック
	trans = obj->abs_transform();
	if (trans != NULL && !trans->is_identity()) {
		//座標変換適用後のパスに変換する
		transformed_path = make_transformed_path(obj);
		if (transformed_path == NULL) {
			fprintf(stderr, "ERROR: Apply tranform failed\n");
			goto error;
		}
		cmds = transformed_path->commands();
		coords = transformed_path->coords();
	} else {
		cmds = obj->commands();
		coords = obj->coords();
	}

	//コマンド出力
	fprintf(fp, "static const VGubyte segment%s_%d[] __rodata_imagedata ={", id, index);
	first = true;
	for (cmd_i = cmds->begin(); cmd_i != cmds->end(); ++cmd_i) {
		cmd = *cmd_i;
		//A,aは座標データによってOpenVGのコマンドが変わるため未対応
		if (cmd == SVG_CMD_A || cmd == SVG_CMD_a) {
			fprintf(stderr, "\n");
			fprintf(stderr, "ERROR: Not Support Output 'A' and 'a'\n");
			goto error;
		}

		//コマンド出力
		if (!first) {
			fprintf(fp, ",");
		} else {
			first = false;
		}
		vgcmd = get_openvg_cmd(cmd);
		if (flag & OUTPUT_SVG_ABSCOORD) {
			fprintf(fp, "%s", get_openvg_cmd_str(vgcmd & ~VG_RELATIVE));
		} else {
			fprintf(fp, "%s", get_openvg_cmd_str(vgcmd));
		}
	}
	fprintf(fp, "};\n");

	//座標出力
	abs_x = 0.0f;
	abs_y = 0.0f;
	//
	fprintf(fp, "static const VGfloat pathData%s_%d[] __rodata_imagedata ={", id, index);

	first = true;
	coord_index = 0;

	for (cmd_i = cmds->begin(); cmd_i != cmds->end(); ++cmd_i) {
		/* コマンド */
		cmd = *cmd_i;

		if (!first) {
			if (cmd != SVG_CMD_z) {
				fprintf(fp, ",");
			}
		} else {
			first = false;
		}

		switch (cmd) {
		case SVG_CMD_z:
			break;
		case SVG_CMD_H:
			//X座標のみ
			x = coords->at(coord_index);
			fprintf(fp, "%.4ff", x);
			abs_x = x;
			coord_index++;
			break;
		case SVG_CMD_h:
			//X座標のみ
			x = coords->at(coord_index);
			//絶対値変換
			if (flag & OUTPUT_SVG_ABSCOORD) {
				out_x = abs_x + x;
			} else {
				out_x = x;
			}
			fprintf(fp, "%.4ff", out_x);
			abs_x += x;
			coord_index++;
			break;
		case SVG_CMD_V:
			//Y座標のみ
			y = coords->at(coord_index);
			fprintf(fp, "%.4ff", y);
			abs_y = y;
			coord_index++;
			break;
		case SVG_CMD_v:
			//Y座標のみ
			y = coords->at(coord_index);
			//絶対値変換
			if (flag & OUTPUT_SVG_ABSCOORD) {
				out_y = abs_y + y;
			} else {
				out_y = y;
			}
			fprintf(fp, "%.4ff", out_y);
			abs_y += y;
			coord_index++;
			break;
		default:
			bool first2 = true;
			coord_num = svgutil_cmd_coords_num(cmd);
			vgcmd = get_openvg_cmd(cmd);
			for (i = 0; i < coord_num; i += 2) {
				if (!first2) {
					fprintf(fp, ",");
				} else {
					first2 = false;
				}
				x = coords->at(coord_index);
				y = coords->at(coord_index + 1);
				//絶対値変換
				if ((vgcmd & VG_RELATIVE) && (flag & OUTPUT_SVG_ABSCOORD)) {
					out_x = abs_x + x;
					out_y = abs_y + y;
				} else {
					out_x = x;
					out_y = y;
				}
				fprintf(fp, "%.4ff,%.4ff",out_x, out_y);
				coord_index += 2;
			}
			if (vgcmd & VG_RELATIVE) {
				abs_x += x;
				abs_y += y;
			} else {
				abs_x = x;
				abs_y = y;
			}
			break;
		}
	}
	fprintf(fp, "};\n");

	//ヘッダ出力
	fprintf(fp, "static const GDI_SHAPE_PATH path%s_%d __rodata_imagedata ={%d,segment%s_%d,pathData%s_%d};\n",
				id, index, cmds->size(), id, index, id, index);
	fprintf(fp, "\n");

	if (transformed_path != NULL) {
		delete transformed_path;
	}

	return 0;

error:
	if (transformed_path != NULL) {
		delete transformed_path;
	}

	return -1;
}

static int output_polygon_data(SvgParser *parser, SvgPolygon *obj, const char *id, OUTPUT_TYPE type, int flag, FILE *fp)
{
	const SVGCOORDS				*coords;
	SVGCOORDS::const_iterator	coord_i;
	bool						first;
	int							index = obj->user_data();
	const SvgTransform			*trans;
	float						x, y;

	//座標情報
	coords = obj->coords();
	//座標出力
	first = true;
	fprintf(fp, "const VGfloat polygonList%s_%d[] __rodata_imagedata = {", id, index);

	//変換行列
	trans = obj->abs_transform();
	if (trans != NULL && trans->is_identity()) {
		//恒等変換なら無視する
		trans = NULL;
	}

	for (coord_i = coords->begin(); coord_i != coords->end(); ++coord_i) {
		if (!first) {
			fprintf(fp, ", ");
		} else {
			first = false;
		}
		x = *coord_i;
		coord_i++;
		y = *coord_i;
		//座標変換を適用
		if (trans != NULL) {
			trans->trans_xy(x, y, &x, &y);
		}
		fprintf(fp, "%.4ff,%.4ff",x, y);
	}
	fprintf(fp, "};\n");
	//ヘッダ出力
	fprintf(fp, "const GDI_SHAPE_POLYGON polygon%s_%d __rodata_imagedata = {%d, (VGfloat*)&polygonList%s_%d};\n",
				id, index, coords->size() / 2, id, index);
	fprintf(fp, "\n");

	return 0;
}

static int output_polyline_data(SvgParser *parser, SvgPolyline *obj, const char *id, OUTPUT_TYPE type, int flag, FILE *fp)
{
	const SVGCOORDS				*coords;
	SVGCOORDS::const_iterator	coord_i;
	bool						first;
	int							index = obj->user_data();
	const SvgTransform			*trans;
	float						x, y;

	//座標情報
	coords = obj->coords();
	//座標出力
	first = true;
	fprintf(fp, "const VGfloat polylineList%s_%d[] __rodata_imagedata = {", id, index);
	
	//変換行列
	trans = obj->abs_transform();
	if (trans != NULL && trans->is_identity()) {
		//恒等変換なら無視する
		trans = NULL;
	}

	for (coord_i = coords->begin(); coord_i != coords->end(); ++coord_i) {
		if (!first) {
			fprintf(fp, ", ");
		} else {
			first = false;
		}
		x = *coord_i;
		coord_i++;
		y = *coord_i;
		//座標変換を適用
		if (trans != NULL) {
			trans->trans_xy(x, y, &x, &y);
		}
		fprintf(fp, "%.4ff,%.4ff",x, y);
	}
	fprintf(fp, "};\n");
	//ヘッダ出力
	fprintf(fp, "const GDI_SHAPE_POLYLINE polyline%s_%d __rodata_imagedata = {%d, (VGfloat*)&polylineList%s_%d};\n",
					id, index, coords->size() / 2, id, index);
	fprintf(fp, "\n");

	return 0;
}

static int output_circle_data(SvgParser *parser, SvgCircle *obj, const char *id, OUTPUT_TYPE type, int flag, FILE *fp)
{
	int			index = obj->user_data();

	//CircleはEllipseとして出力(GENWARE互換)
	fprintf(fp, "const GDI_SHAPE_ELLIPSE ellipse%s_%d __rodata_imagedata = {%.4ff,%.4ff,%.4ff,%.4ff};\n",
			id, index,
			obj->cx(), obj->cy(), obj->r() * 2.0f, obj->r() * 2.0f);

	return 0;
}

static int output_ellipse_data(SvgParser *parser, SvgEllipse *obj, const char *id, OUTPUT_TYPE type, int flag, FILE *fp)
{
	int			index = obj->user_data();

	fprintf(fp, "const GDI_SHAPE_ELLIPSE ellipse%s_%d __rodata_imagedata = {%.4ff,%.4ff,%.4ff,%.4ff};\n",
			id, index,
			obj->cx(), obj->cy(), obj->rx() * 2.0f, obj->ry() * 2.0f);

	return 0;
}

static int output_roundrect_data(SvgParser *parser, SvgRect *obj, const char *id, OUTPUT_TYPE type, int flag, FILE *fp)
{
	int			index = obj->user_data();

	fprintf(fp, "const GDI_SHAPE_ROUNDRECT roundrect%s_%d __rodata_imagedata = {%.4ff,%.4ff,%.4ff,%.4ff,%.4ff,%.4ff};\n",
			id, index,
			obj->x(), obj->y(), obj->width(), obj->height(), obj->rx() * 2.0f, obj->ry() * 2.0f);

	return 0;
}

static int output_rect_data(SvgParser *parser, SvgRect *obj, const char *id, OUTPUT_TYPE type, int flag, FILE *fp)
{
	int			index = obj->user_data();

	fprintf(fp, "const GDI_SHAPE_RECT rect%s_%d __rodata_imagedata = {%.4ff,%.4ff,%.4ff,%.4ff};\n",
			id, index,
			obj->x(), obj->y(), obj->width(), obj->height());

	return 0;
}

static int output_line_data(SvgParser *parser, SvgLine *obj, const char *id, OUTPUT_TYPE type, int flag, FILE *fp)
{
	int			index = obj->user_data();
	const SvgTransform			*trans;
	float						x1, y1, x2, y2;

	//変換行列
	trans = obj->abs_transform();
	if (trans != NULL && trans->is_identity()) {
		//恒等変換なら無視する
		trans = NULL;
	}

	x1 = obj->x1();
	y1 = obj->y1();
	x2 = obj->x2();
	y2 = obj->y2();

	//座標変換を適用
	if (trans != NULL) {
		trans->trans_xy(x1, y1, &x1, &y1);
		trans->trans_xy(x2, y2, &x2, &y2);
	}

	fprintf(fp, "const GDI_SHAPE_LINE line%s_%d __rodata_imagedata = {%.4ff,%.4ff,%.4ff,%.4ff};\n",
				id, index,
				x1, y1, x2, y2);

	return 0;
}

//図形オブジェクトヘッダ出力
//次の図形番号を返す
static int output_objects_header(SvgParser *parser, SvgGroup *group, const char *id, OUTPUT_TYPE type, int flag, int no, FILE *fp)
{
	SVGOBJECTLIST				*objs = group->objects();
	SVGOBJECTLIST::iterator		i;
	SVG_OBJECT_TYPE				obj_type;
	int							ret = 0;
	const char					*grf_parts_type, *grf_val_type, *grf_val_name;

	for (i = objs->begin(); i != objs->end(); ++i) {
		if ((*i)->style()->display() == SVGDISPLAY_NONE) {
			//非表示のデータは出力しない
			continue;
		}
		/* 塗りつぶさないデータは出力しない */
		if( !(*i)->style()->fill_enable() && !(*i)->style()->stroke_enable() ){
			continue;
		}
		
		//出力するときの形式を取得（objの形式と異なる場合がある）
		obj_type = get_output_obj_type(*i);
		//出力
		if (obj_type == SVG_TYPE_GROUP) {
			SvgGroup *obj = static_cast<SvgGroup*>(*i);
			no = output_objects_header(parser, obj, id, type, flag, no, fp);
			if (no < 0) {
				return no;
			}
		} else {
			switch (obj_type) {
			case SVG_TYPE_PATH:
				grf_parts_type = "GDI_SHAPE_TYPE_PATH";
				grf_val_type   = "GDI_SHAPE_PATH";
				grf_val_name   = "path";
				break;
			case SVG_TYPE_POLYGON:
				grf_parts_type = "GDI_SHAPE_TYPE_POLYGON";
				grf_val_type   = "GDI_SHAPE_POLYGON";
				grf_val_name   = "polygon";
				break;
			case SVG_TYPE_POLYLINE:
				grf_parts_type = "GDI_SHAPE_TYPE_POLYLINE";
				grf_val_type   = "GDI_SHAPE_POLYLINE";
				grf_val_name   = "polyline";
				break;
			case SVG_TYPE_CIRCLE:
				grf_parts_type = "GDI_SHAPE_TYPE_ELLIPSE";
				grf_val_type   = "GDI_SHAPE_ELLIPSE";
				grf_val_name   = "ellipse";
				break;
			case SVG_TYPE_ELLIPSE:
				grf_parts_type = "GDI_SHAPE_TYPE_ELLIPSE";
				grf_val_type   = "GDI_SHAPE_ELLIPSE";
				grf_val_name   = "ellipse";
				break;
			case SVG_TYPE_ROUNDRECT:
				grf_parts_type = "GDI_SHAPE_TYPE_ROUNDRECT";
				grf_val_type   = "GDI_SHAPE_ROUNDRECT";
				grf_val_name   = "roundrect";
				break;
			case SVG_TYPE_RECT:
				grf_parts_type = "GDI_SHAPE_TYPE_RECT";
				grf_val_type   = "GDI_SHAPE_RECT";
				grf_val_name   = "rect";
				break;
			case SVG_TYPE_LINE:
				grf_parts_type = "GDI_SHAPE_TYPE_LINE";
				grf_val_type   = "GDI_SHAPE_LINE";
				grf_val_name   = "line";
				break;
			default:
				return -1;
			}
			//ヘッダ出力
#if 1
			fprintf(fp, "static const GDI_PARTS parts%s_%d __rodata_imagedata ={%s,",id, no, grf_parts_type);
			fprintf(fp, "\t&%s%s_%d,", grf_val_name, id, (*i)->user_data());
			output_object_header_style_info(*i, fp, id, no, 1);
			fprintf(fp, "};\n");
			//ヘッダ出力
#else
			if (type == OUTPUT_TYPE_1BPP) {
				//モノクロ
				fprintf(fp, "static const GDI_PARTS_MONO parts%s_%d __rodata_imagedata ={%s,&%s%s_%d};\n",
					id, no,
					grf_parts_type,
					grf_val_name,
					id,
					(*i)->user_data());
			} else {
				//カラー
				fprintf(fp, "static const GDI_PARTS_COLOR parts%s_%d __rodata_imagedata ={%s,",
					id, no,
					grf_parts_type);
				//
				output_object_header_style_GDI(*i, fp, id);
				//
				fprintf(fp, "&%s%s_%d};\n",
					grf_val_name,
					id,
					(*i)->user_data());
			}
			//
#endif
			no++;
		}
	}
	
	return no;
}

//図形オブジェクトヘッダをパスに変換して出力
//次の図形番号を返す
static int output_objects_header_as_path(SvgParser *parser, SvgGroup *group, const char *id, OUTPUT_TYPE type, int flag, int no, FILE *fp)
{
	SVGOBJECTLIST				*objs = group->objects();
	SVGOBJECTLIST::iterator		i;
	SVG_OBJECT_TYPE				obj_type;
	int							ret = 0;
	const char					*grf_parts_type, *grf_val_type, *grf_val_name;

	for (i = objs->begin(); i != objs->end(); ++i) {
		if ((*i)->style()->display() == SVGDISPLAY_NONE) {
			//非表示のデータは出力しない
			continue;
		}
		/* 塗りつぶさないデータは出力しない */
		if( !(*i)->style()->fill_enable() && !(*i)->style()->stroke_enable() ){
			continue;
		}
		obj_type = (*i)->type();
		//出力
		if (obj_type == SVG_TYPE_GROUP) {
			SvgGroup *obj = static_cast<SvgGroup*>(*i);
			no = output_objects_header_as_path(parser, obj, id, type, flag, no, fp);
			if (no < 0) {
				return no;
			}
		} else {
			//GDI用データ形式
			grf_parts_type = "GDI_SHAPE_TYPE_PATH";
			grf_val_type   = "GDI_SHAPE_PATH";
			grf_val_name   = "path";

			fprintf(fp, "static const GDI_PARTS parts%s_%d __rodata_imagedata ={%s,",id, no, grf_parts_type);
			fprintf(fp, "&%s%s_%d,\n", grf_val_name, id, (*i)->user_data());
			fprintf(fp, "{");
			output_object_header_style_info(*i, fp, id, no, 1);
			fprintf(fp, "},");
			//ヘッダ出力
			//
			no++;
		}
	}

	return no;
}

static int output_object_header_style_info(SvgObject *obj, FILE *fp, const char *id, int no, int tab_count)
{
	const SvgStyle		*style = obj->style();
	char tab[64] = {0};
	int i;

	for (i=0; i<tab_count; i++) {
		tab[i] = '\t';
	}
	tab[i] = NULL;

	//Paint Mode
	fprintf(fp, "\t(VGPaintMode)%s,", get_openvg_paintmode_str(style->fill_enable(), style->stroke_enable()));

	//Fill Rule
	if (style->fill_rule() == SVGFILLRULE_NONZERO) {
		fprintf(fp, " VG_NON_ZERO,");
	}
	else {
		fprintf(fp, " VG_EVEN_ODD,");
	}
	//Cap Style
	if (style->stroke_linecap() == SVGLINECAP_SQUARE) {
		fprintf(fp, " VG_CAP_SQUARE,");
	}
	else if (style->stroke_linecap() == SVGLINECAP_ROUND) {
		fprintf(fp, " VG_CAP_ROUND,");
	}
	else {
		fprintf(fp, " VG_CAP_BUTT,");
	}
	//Join Style
	if (style->stroke_linejoin() == SVGLINEJOIN_BEVEL) {
		fprintf(fp, " VG_JOIN_BEVEL,");
	}
	else if (style->stroke_linejoin() == SVGLINEJOIN_ROUND) {
		fprintf(fp, " VG_JOIN_ROUND,");
	}
	else {
		fprintf(fp, " VG_JOIN_MITER,");
	}
	//Miter Limit
	fprintf(fp, " %.04ff,", style->stroke_miter_limit());
	//Stroke Width
	fprintf(fp, " %.04ff,", style->stroke_width());
	//DashID	NOT SUPPORT
	fprintf(fp, " 0,");

	fprintf(fp, " &strokecolor%s_%d,", id, no);
	fprintf(fp, " &fillcolor%s_%d,", id, no);

	return 0;
}

static int output_objects_color(SvgParser *parser, SvgGroup *group, const char *id, OUTPUT_TYPE type, int flag, int no, FILE *fp)
{
	SVGOBJECTLIST				*objs = group->objects();
	SVGOBJECTLIST::iterator		i;
	SVG_OBJECT_TYPE				obj_type;
	int							ret = 0;
	const char					*grf_parts_type, *grf_val_type, *grf_val_name;

	for (i = objs->begin(); i != objs->end(); ++i) {
		if ((*i)->style()->display() == SVGDISPLAY_NONE) {
			//非表示のデータは出力しない
			continue;
		}
		/* 塗りつぶさないデータは出力しない */
		if( !(*i)->style()->fill_enable() && !(*i)->style()->stroke_enable() ){
			continue;
		}
		
		//出力するときの形式を取得（objの形式と異なる場合がある）
		obj_type = get_output_obj_type(*i);
		//出力
		if (obj_type == SVG_TYPE_GROUP) {
			SvgGroup *obj = static_cast<SvgGroup*>(*i);
			no = output_objects_color(parser, obj, id, type, flag, no, fp);
			if (no < 0) {
				return no;
				
			}
		} else {
			fprintf(fp, "static const GDI_COLOR strokecolor%s_%d __rodata_imagedata ={", id, no);
			output_objects_strokecolor(*i, fp, id, 1);
			fprintf(fp, "};\n");
			fprintf(fp, "static const GDI_COLOR fillcolor%s_%d __rodata_imagedata ={", id, no);
			output_objects_fillcolor(*i, fp, id, 1);
			fprintf(fp, "};\n");
			no++;
		}
	}
	
	return no;
}

static int output_objects_fillcolor(SvgObject *obj, FILE *fp, const char *id, int tab_count)
{
	const SVGRGB		*color;
	const SvgStyle		*style = obj->style();
	int					alpha;
	float				fval;
	char tab[64] = {0};
	int i;

	for (i=0; i<tab_count; i++) {
		tab[i] = '\t';
	}
	tab[i] = NULL;

	if (style->fill_enable()) {
		//Fill Paint Type
		if (style->fill()->ref_obj != NULL) {
			if (style->fill()->ref_obj->m_type == SVG_TYPE_LINEARGRADIENT) {
				fprintf(fp, "VG_PAINT_TYPE_LINEAR_GRADIENT,");
			} else {
				fprintf(fp, "VG_PAINT_TYPE_RADIAL_GRADIENT,");
			}
		} else {
			fprintf(fp, "VG_PAINT_TYPE_COLOR,");
		}
		//Fill Paint Color
		color = &style->fill()->rgb;
		//α値を0～255にする
		alpha = (int)(255.0f * style->fill_opacity() + 0.5f);
		//α値の誤差が発生する場合はINFO表示
		fval = alpha / 255.0f;
		if ( fval != style->fill_opacity() ) {
			fprintf(stderr, "INFO: %s alpha value was rounded. (alpha=%f)\n", id, style->fill_opacity());
		}
		fprintf(fp, " GDI_RGBA(%d,%d,%d,%d),", color->r, color->g, color->b, alpha);

		//fill_gradient
		if (style->fill()->ref_obj != NULL) {
			fprintf(fp, " &gradient%s_%d", id,style->fill()->ref_obj->user_data());
		} else {
			fprintf(fp, " NULL");
		}
	} else {
		//塗りつぶしなしの場合
		fprintf(fp, " VG_PAINT_TYPE_COLOR, 0, NULL");
	}

	return 0;
}


static int output_objects_strokecolor(SvgObject *obj, FILE *fp, const char *id, int tab_count)
{
	const SVGRGB		*color;
	const SvgStyle		*style = obj->style();
	int					alpha;
	float				fval;
	char tab[64] = {0};
	int i;

	for (i=0; i<tab_count; i++) {
		tab[i] = '\t';
	}
	tab[i] = NULL;

	if (style->stroke_enable()) {
		//Stroke Paint Type		NOT SUPPORT Gradient
		if (style->stroke()->ref_obj != NULL) {
			if (style->fill()->ref_obj->m_type == SVG_TYPE_LINEARGRADIENT) {
				fprintf(fp, "VG_PAINT_TYPE_LINEAR_GRADIENT,");
			} else {
				fprintf(fp, "VG_PAINT_TYPE_RADIAL_GRADIENT,");
			}
		} else {
			fprintf(fp, "VG_PAINT_TYPE_COLOR,");
		}
		//Stroke Paint Color
		color = &style->stroke()->rgb;
		//α値を0～255にする
		alpha = (int)(255.0f * style->stroke_opacity() + 0.5f);
		//α値の誤差が発生する場合はINFO表示
		fval = alpha / 255.0f;
		if ( fval != style->stroke_opacity() ) {
			fprintf(stderr, "INFO: %s alpha value was rounded. (alpha=%f)\n", id, style->stroke_opacity());
		}
		fprintf(fp, " GDI_RGBA(%d,%d,%d,%d),", color->r, color->g, color->b, alpha);

		//Stroke Gradient
		if (style->stroke()->ref_obj != NULL) {
			fprintf(fp, " &gradient%s_%d", id, style->stroke()->ref_obj->user_data());
		} else {
			fprintf(fp, " NULL");
		}
	} else {
		//線なしの場合
		fprintf(fp, " VG_PAINT_TYPE_COLOR, 0, NULL");
	}

	return 0;
}


static int output_object_header_style_GDI(SvgObject *obj, FILE *fp, const char *id)
{
	const SVGRGB		*color;
	const SvgStyle		*style = obj->style();
	int					alpha;
	float				fval;

	//Fill Rule
	if (style->fill_rule() == SVGFILLRULE_NONZERO) {
		fprintf(fp, "VG_NON_ZERO,");
	}
	else {
		fprintf(fp, "VG_EVEN_ODD,");
	}
	//Paint Mode
	fprintf(fp, "%s,", get_openvg_paintmode_str(style->fill_enable(), style->stroke_enable()));
	//Cap Style
	if (style->stroke_linecap() == SVGLINECAP_SQUARE) {
		fprintf(fp, "VG_CAP_SQUARE,");
	}
	else if (style->stroke_linecap() == SVGLINECAP_ROUND) {
		fprintf(fp, "VG_CAP_ROUND,");
	}
	else {
		fprintf(fp, "VG_CAP_BUTT,");
	}
	//Join Style
	if (style->stroke_linejoin() == SVGLINEJOIN_BEVEL) {
		fprintf(fp, "VG_JOIN_BEVEL,");
	}
	else if (style->stroke_linejoin() == SVGLINEJOIN_ROUND) {
		fprintf(fp, "VG_JOIN_ROUND,");
	}
	else {
		fprintf(fp, "VG_JOIN_MITER,");
	}
	//Miter Limit
	fprintf(fp, "%.04ff,", style->stroke_miter_limit());
	//Stroke Width
	fprintf(fp, "%.04ff,", style->stroke_width());
	//DashID	NOT SUPPORT
	fprintf(fp, "0,");

	if (style->fill_enable()) {
		//Fill Paint Type
		if (style->fill()->ref_obj != NULL) {
			if (style->fill()->ref_obj->m_type == SVG_TYPE_LINEARGRADIENT) {
				fprintf(fp, "VG_PAINT_TYPE_LINEAR_GRADIENT,");
			} else {
				fprintf(fp, "VG_PAINT_TYPE_RADIAL_GRADIENT,");
			}
		} else {
			fprintf(fp, "VG_PAINT_TYPE_COLOR,");
		}
		//Fill Paint Color
		color = &style->fill()->rgb;
		//α値を0～255にする
		alpha = (int)(255.0f * style->fill_opacity() + 0.5f);
		//α値の誤差が発生する場合はINFO表示
		fval = alpha / 255.0f;
		if ( fval != style->fill_opacity() ) {
			fprintf(stderr, "INFO: %s alpha value was rounded. (alpha=%f)\n", id, style->fill_opacity());
		}
		fprintf(fp, "GDI_RGBA(%d,%d,%d,%d),", color->r, color->g, color->b, alpha);

		//fill_gradient
		if (style->fill()->ref_obj != NULL) {
			fprintf(fp, "&gradient%s_%d,", id,style->fill()->ref_obj->user_data());
		} else {
			fprintf(fp, "NULL,");
		}
	} else {
		//塗りつぶしなしの場合
		fprintf(fp, "VG_PAINT_TYPE_COLOR,0,NULL,");
	}

	if (style->stroke_enable()) {
		//Stroke Paint Type		NOT SUPPORT Gradient
		if (style->stroke()->ref_obj != NULL) {
			if (style->fill()->ref_obj->m_type == SVG_TYPE_LINEARGRADIENT) {
				fprintf(fp, "VG_PAINT_TYPE_LINEAR_GRADIENT,");
			} else {
				fprintf(fp, "VG_PAINT_TYPE_RADIAL_GRADIENT,");
			}
		} else {
			fprintf(fp, "VG_PAINT_TYPE_COLOR,");
		}
		//Stroke Paint Color
		color = &style->stroke()->rgb;
		//α値を0～255にする
		alpha = (int)(255.0f * style->stroke_opacity() + 0.5f);
		//α値の誤差が発生する場合はINFO表示
		fval = alpha / 255.0f;
		if ( fval != style->stroke_opacity() ) {
			fprintf(stderr, "INFO: %s alpha value was rounded. (alpha=%f)\n", id, style->stroke_opacity());
		}
		fprintf(fp, "GDI_RGBA(%d,%d,%d,%d),", color->r, color->g, color->b, alpha);

		//Stroke Gradient
		if (style->stroke()->ref_obj != NULL) {
			fprintf(fp, "&gradient%s_%d,", id, style->stroke()->ref_obj->user_data());
		} else {
			fprintf(fp, "NULL,");
		}
	} else {
		//線なしの場合
		fprintf(fp, "VG_PAINT_TYPE_COLOR,0,NULL,");
	}
	//Filter ID				NOT SUPPORT
	fprintf(fp, "NULL,");

	return 0;
}


//パスデータにtransformを適用したデータを作成する
//処理の簡略化のためパス情報はすべて絶対座標に変換し、HLINE,VLINEなどを使用した最適化は行わない。
static SvgPath *make_transformed_path(const SvgPath *obj)
{
	const SVGCMDS				*cmds;
	SVGCMDS::const_iterator		cmd_i;
	const SVGCOORDS				*coords;
	SVGCOORDS::const_iterator	coord_i;
	int							coord_num;
	SvgPath						*transformed_path;
	SVG_CMD						cmd;
	float						x, y;
	float						abs_x, abs_y;
	float						trans_x, trans_y;
	int							coord_index;
	const SvgTransform			*trans;
	int							i;

	transformed_path = NEW SvgPath(NULL, NULL);
	cmds = obj->commands();
	coords = obj->coords();

	abs_x = 0.0f;
	abs_y = 0.0f;
	coord_index = 0;
	trans=obj->abs_transform();

	for (cmd_i = cmds->begin(); cmd_i != cmds->end(); ++cmd_i) {
		/* コマンド */
		cmd = *cmd_i;

		switch (cmd) {
		case SVG_CMD_z:
			transformed_path->add_command(cmd);
			break;
		case SVG_CMD_H:
			//X座標のみ
			x = coords->at(coord_index);
			coord_index++;
			//座標変換
			trans->trans_xy(x, abs_y, &trans_x, &trans_y);
			//データ追加
			transformed_path->add_command(SVG_CMD_L);
			transformed_path->add_coord(trans_x);
			transformed_path->add_coord(trans_y);
			//座標更新
			abs_x = x;
			break;
		case SVG_CMD_h:
			//X座標のみ
			x = coords->at(coord_index);
			coord_index++;
			//座標変換
			trans->trans_xy(abs_x + x, abs_y, &trans_x, &trans_y);
			//データ追加
			transformed_path->add_command(SVG_CMD_L);
			transformed_path->add_coord(trans_x);
			transformed_path->add_coord(trans_y);
			//座標更新
			abs_x += x;
			break;
		case SVG_CMD_V:
			//Y座標のみ
			y = coords->at(coord_index);
			coord_index++;
			//座標変換
			trans->trans_xy(abs_x, y, &trans_x, &trans_y);
			//データ追加
			transformed_path->add_command(SVG_CMD_L);
			transformed_path->add_coord(trans_x);
			transformed_path->add_coord(trans_y);
			//座標更新
			abs_y = y;
			break;
		case SVG_CMD_v:
			//Y座標のみ
			y = coords->at(coord_index);
			coord_index++;
			//座標変換
			trans->trans_xy(abs_x, abs_y + y, &trans_x, &trans_y);
			//データ追加
			transformed_path->add_command(SVG_CMD_L);
			transformed_path->add_coord(trans_x);
			transformed_path->add_coord(trans_y);
			//座標更新
			abs_y += y;
			break;
		default:
			coord_num = svgutil_cmd_coords_num(cmd);
			//データ追加
			transformed_path->add_command(svgutil_cmd_cnv_to_abs(cmd));
			for (i = 0; i < coord_num; i += 2) {
				x = coords->at(coord_index);
				y = coords->at(coord_index + 1);
				coord_index += 2;
				//絶対座標なら座標変換を適用
				if (svgutil_is_cmd_relative(cmd)) {
					//絶対値変換
					x = abs_x + x;
					y = abs_y + y;
				}
				//座標変換
				trans->trans_xy(x, y, &trans_x, &trans_y);
				//データ追加
				transformed_path->add_coord(trans_x);
				transformed_path->add_coord(trans_y);
			}
			abs_x = x;
			abs_y = y;
			break;
		}
	}

	return transformed_path;
}

//データ出力するときの形式を取得する
//いくつかの場合で別の形式に変換して出力する必要がある
static SVG_OBJECT_TYPE get_output_obj_type(SvgObject *obj)
{
	SVG_OBJECT_TYPE		out_type;

	//元の形式
	out_type = obj->type();
	//必要なら形式を変更
	switch (out_type) {
		case SVG_TYPE_PATH:
		case SVG_TYPE_POLYGON:
		case SVG_TYPE_POLYLINE:
		case SVG_TYPE_LINE:
			break;
		case SVG_TYPE_CIRCLE:
		case SVG_TYPE_ELLIPSE:
		case SVG_TYPE_ROUNDRECT:
		case SVG_TYPE_RECT:
			//transformが設定されている場合は表示できないのでPathに変換して出力する
			if (obj->abs_transform() != NULL && !obj->abs_transform()->is_identity()) {
				out_type = SVG_TYPE_PATH;
			}

			//RoundRectはRectとは別に出力
			if (out_type == SVG_TYPE_RECT) {
				SvgRect *obj_rect = static_cast<SvgRect*>(obj);
				if (obj_rect->rx() != 0 && obj_rect->ry() != 0) { //(rx,ry共に0でなければ、RoundRectとする。
					out_type = SVG_TYPE_ROUNDRECT;
				}
			}
			//CircleはEllipseとして出力する
			if (out_type == SVG_TYPE_CIRCLE) {
				out_type = SVG_TYPE_ELLIPSE;
			}
			break;
		default:
			break;
	}

	return out_type;
}

