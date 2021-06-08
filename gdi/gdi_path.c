/*
 * Copyright(c) 2018 Persol AVC Technology.
 */

#include <string.h>

#ifdef WIN32_GUI_SIM
#include "egl.h"
#include "openvg.h"
#else
#define PANA_ORG_FUNC
#define _DMPNATIVE_
#include "EGL/egl.h"

#include "DMP/eglNative.h"
#include "DMP/eglNativePhlox.h"
#include "DMP/eglDMP.h"
#include "DMP/vgDMPX.h"
#endif

#include "gdi.h"
#include "gdi_local.h"

#define CUBIC_CTRL_FACTOR		(0.5522847498308f)	/* ベジェ曲線制御点計算用定数 4 * (√2 - 1) / 3 */
#define MAX_POLYGON_COUNT		(100)
#define MAX_GRADIENT_STOPS	5

VGfloat gdi_int_to_float_100[101] = {
	0.0f/100.0f,
	1.0f/100.0f,
	2.0f/100.0f,
	3.0f/100.0f,
	4.0f/100.0f,
	5.0f/100.0f,
	6.0f/100.0f,
	7.0f/100.0f,
	8.0f/100.0f,
	9.0f/100.0f,
	10.0f/100.0f,
	11.0f/100.0f,
	12.0f/100.0f,
	13.0f/100.0f,
	14.0f/100.0f,
	15.0f/100.0f,
	16.0f/100.0f,
	17.0f/100.0f,
	18.0f/100.0f,
	19.0f/100.0f,
	20.0f/100.0f,
	21.0f/100.0f,
	22.0f/100.0f,
	23.0f/100.0f,
	24.0f/100.0f,
	25.0f/100.0f,
	26.0f/100.0f,
	27.0f/100.0f,
	28.0f/100.0f,
	29.0f/100.0f,
	30.0f/100.0f,
	31.0f/100.0f,
	32.0f/100.0f,
	33.0f/100.0f,
	34.0f/100.0f,
	35.0f/100.0f,
	36.0f/100.0f,
	37.0f/100.0f,
	38.0f/100.0f,
	39.0f/100.0f,
	40.0f/100.0f,
	41.0f/100.0f,
	42.0f/100.0f,
	43.0f/100.0f,
	44.0f/100.0f,
	45.0f/100.0f,
	46.0f/100.0f,
	47.0f/100.0f,
	48.0f/100.0f,
	49.0f/100.0f,
	50.0f/100.0f,
	51.0f/100.0f,
	52.0f/100.0f,
	53.0f/100.0f,
	54.0f/100.0f,
	55.0f/100.0f,
	56.0f/100.0f,
	57.0f/100.0f,
	58.0f/100.0f,
	59.0f/100.0f,
	60.0f/100.0f,
	61.0f/100.0f,
	62.0f/100.0f,
	63.0f/100.0f,
	64.0f/100.0f,
	65.0f/100.0f,
	66.0f/100.0f,
	67.0f/100.0f,
	68.0f/100.0f,
	69.0f/100.0f,
	70.0f/100.0f,
	71.0f/100.0f,
	72.0f/100.0f,
	73.0f/100.0f,
	74.0f/100.0f,
	75.0f/100.0f,
	76.0f/100.0f,
	77.0f/100.0f,
	78.0f/100.0f,
	79.0f/100.0f,
	80.0f/100.0f,
	81.0f/100.0f,
	82.0f/100.0f,
	83.0f/100.0f,
	84.0f/100.0f,
	85.0f/100.0f,
	86.0f/100.0f,
	87.0f/100.0f,
	88.0f/100.0f,
	89.0f/100.0f,
	90.0f/100.0f,
	91.0f/100.0f,
	92.0f/100.0f,
	93.0f/100.0f,
	94.0f/100.0f,
	95.0f/100.0f,
	96.0f/100.0f,
	97.0f/100.0f,
	98.0f/100.0f,
	99.0f/100.0f,
	100.0f/100.0f,
	
};

//RAM実行エリアにおく場合は、constをつける意味がない
VGfloat gdi_int_to_float_255[256] = {
	0.0f/255.0f,
	1.0f/255.0f,
	2.0f/255.0f,
	3.0f/255.0f,
	4.0f/255.0f,
	5.0f/255.0f,
	6.0f/255.0f,
	7.0f/255.0f,
	8.0f/255.0f,
	9.0f/255.0f,
	10.0f/255.0f,
	11.0f/255.0f,
	12.0f/255.0f,
	13.0f/255.0f,
	14.0f/255.0f,
	15.0f/255.0f,
	16.0f/255.0f,
	17.0f/255.0f,
	18.0f/255.0f,
	19.0f/255.0f,
	20.0f/255.0f,
	21.0f/255.0f,
	22.0f/255.0f,
	23.0f/255.0f,
	24.0f/255.0f,
	25.0f/255.0f,
	26.0f/255.0f,
	27.0f/255.0f,
	28.0f/255.0f,
	29.0f/255.0f,
	30.0f/255.0f,
	31.0f/255.0f,
	32.0f/255.0f,
	33.0f/255.0f,
	34.0f/255.0f,
	35.0f/255.0f,
	36.0f/255.0f,
	37.0f/255.0f,
	38.0f/255.0f,
	39.0f/255.0f,
	40.0f/255.0f,
	41.0f/255.0f,
	42.0f/255.0f,
	43.0f/255.0f,
	44.0f/255.0f,
	45.0f/255.0f,
	46.0f/255.0f,
	47.0f/255.0f,
	48.0f/255.0f,
	49.0f/255.0f,
	50.0f/255.0f,
	51.0f/255.0f,
	52.0f/255.0f,
	53.0f/255.0f,
	54.0f/255.0f,
	55.0f/255.0f,
	56.0f/255.0f,
	57.0f/255.0f,
	58.0f/255.0f,
	59.0f/255.0f,
	60.0f/255.0f,
	61.0f/255.0f,
	62.0f/255.0f,
	63.0f/255.0f,
	64.0f/255.0f,
	65.0f/255.0f,
	66.0f/255.0f,
	67.0f/255.0f,
	68.0f/255.0f,
	69.0f/255.0f,
	70.0f/255.0f,
	71.0f/255.0f,
	72.0f/255.0f,
	73.0f/255.0f,
	74.0f/255.0f,
	75.0f/255.0f,
	76.0f/255.0f,
	77.0f/255.0f,
	78.0f/255.0f,
	79.0f/255.0f,
	80.0f/255.0f,
	81.0f/255.0f,
	82.0f/255.0f,
	83.0f/255.0f,
	84.0f/255.0f,
	85.0f/255.0f,
	86.0f/255.0f,
	87.0f/255.0f,
	88.0f/255.0f,
	89.0f/255.0f,
	90.0f/255.0f,
	91.0f/255.0f,
	92.0f/255.0f,
	93.0f/255.0f,
	94.0f/255.0f,
	95.0f/255.0f,
	96.0f/255.0f,
	97.0f/255.0f,
	98.0f/255.0f,
	99.0f/255.0f,
	100.0f/255.0f,
	101.0f/255.0f,
	102.0f/255.0f,
	103.0f/255.0f,
	104.0f/255.0f,
	105.0f/255.0f,
	106.0f/255.0f,
	107.0f/255.0f,
	108.0f/255.0f,
	109.0f/255.0f,
	110.0f/255.0f,
	111.0f/255.0f,
	112.0f/255.0f,
	113.0f/255.0f,
	114.0f/255.0f,
	115.0f/255.0f,
	116.0f/255.0f,
	117.0f/255.0f,
	118.0f/255.0f,
	119.0f/255.0f,
	120.0f/255.0f,
	121.0f/255.0f,
	122.0f/255.0f,
	123.0f/255.0f,
	124.0f/255.0f,
	125.0f/255.0f,
	126.0f/255.0f,
	127.0f/255.0f,
	128.0f/255.0f,
	129.0f/255.0f,
	130.0f/255.0f,
	131.0f/255.0f,
	132.0f/255.0f,
	133.0f/255.0f,
	134.0f/255.0f,
	135.0f/255.0f,
	136.0f/255.0f,
	137.0f/255.0f,
	138.0f/255.0f,
	139.0f/255.0f,
	140.0f/255.0f,
	141.0f/255.0f,
	142.0f/255.0f,
	143.0f/255.0f,
	144.0f/255.0f,
	145.0f/255.0f,
	146.0f/255.0f,
	147.0f/255.0f,
	148.0f/255.0f,
	149.0f/255.0f,
	150.0f/255.0f,
	151.0f/255.0f,
	152.0f/255.0f,
	153.0f/255.0f,
	154.0f/255.0f,
	155.0f/255.0f,
	156.0f/255.0f,
	157.0f/255.0f,
	158.0f/255.0f,
	159.0f/255.0f,
	160.0f/255.0f,
	161.0f/255.0f,
	162.0f/255.0f,
	163.0f/255.0f,
	164.0f/255.0f,
	165.0f/255.0f,
	166.0f/255.0f,
	167.0f/255.0f,
	168.0f/255.0f,
	169.0f/255.0f,
	170.0f/255.0f,
	171.0f/255.0f,
	172.0f/255.0f,
	173.0f/255.0f,
	174.0f/255.0f,
	175.0f/255.0f,
	176.0f/255.0f,
	177.0f/255.0f,
	178.0f/255.0f,
	179.0f/255.0f,
	180.0f/255.0f,
	181.0f/255.0f,
	182.0f/255.0f,
	183.0f/255.0f,
	184.0f/255.0f,
	185.0f/255.0f,
	186.0f/255.0f,
	187.0f/255.0f,
	188.0f/255.0f,
	189.0f/255.0f,
	190.0f/255.0f,
	191.0f/255.0f,
	192.0f/255.0f,
	193.0f/255.0f,
	194.0f/255.0f,
	195.0f/255.0f,
	196.0f/255.0f,
	197.0f/255.0f,
	198.0f/255.0f,
	199.0f/255.0f,
	200.0f/255.0f,
	201.0f/255.0f,
	202.0f/255.0f,
	203.0f/255.0f,
	204.0f/255.0f,
	205.0f/255.0f,
	206.0f/255.0f,
	207.0f/255.0f,
	208.0f/255.0f,
	209.0f/255.0f,
	210.0f/255.0f,
	211.0f/255.0f,
	212.0f/255.0f,
	213.0f/255.0f,
	214.0f/255.0f,
	215.0f/255.0f,
	216.0f/255.0f,
	217.0f/255.0f,
	218.0f/255.0f,
	219.0f/255.0f,
	220.0f/255.0f,
	221.0f/255.0f,
	222.0f/255.0f,
	223.0f/255.0f,
	224.0f/255.0f,
	225.0f/255.0f,
	226.0f/255.0f,
	227.0f/255.0f,
	228.0f/255.0f,
	229.0f/255.0f,
	230.0f/255.0f,
	231.0f/255.0f,
	232.0f/255.0f,
	233.0f/255.0f,
	234.0f/255.0f,
	235.0f/255.0f,
	236.0f/255.0f,
	237.0f/255.0f,
	238.0f/255.0f,
	239.0f/255.0f,
	240.0f/255.0f,
	241.0f/255.0f,
	242.0f/255.0f,
	243.0f/255.0f,
	244.0f/255.0f,
	245.0f/255.0f,
	246.0f/255.0f,
	247.0f/255.0f,
	248.0f/255.0f,
	249.0f/255.0f,
	250.0f/255.0f,
	251.0f/255.0f,
	252.0f/255.0f,
	253.0f/255.0f,
	254.0f/255.0f,
	255.0f/255.0f,
};

/* sin cos を取得する際に使用 */
static const double s_sin_table[] = {
	0.00000000000000000000000e+00, /*  0度 */
	1.74524064372835116532023e-02, /*  1度 */
	3.48994967025009691918846e-02, /*  2度 */
	5.23359562429438276986993e-02, /*  3度 */
	6.97564737441253024385901e-02, /*  4度 */
	8.71557427476581658698507e-02, /*  5度 */
	1.04528463267653456969519e-01, /*  6度 */
	1.21869343405147476100403e-01, /*  7度 */
	1.39173100960065437847746e-01, /*  8度 */
	1.56434465040230868959625e-01, /*  9度 */
	1.73648177666930331186634e-01, /* 10度 */
	1.90808995376544804356556e-01, /* 11度 */
	2.07911690817759314819924e-01, /* 12度 */
	2.24951054343864975670897e-01, /* 13度 */
	2.41921895599667730047955e-01, /* 14度 */
	2.58819045102520739476404e-01, /* 15度 */
	2.75637355816999163327097e-01, /* 16度 */
	2.92371704722736713844000e-01, /* 17度 */
	3.09016994374947395751718e-01, /* 18度 */
	3.25568154457156699876919e-01, /* 19度 */
	3.42020143325668712908083e-01, /* 20度 */
	3.58367949545300268354708e-01, /* 21度 */
	3.74606593415912014766178e-01, /* 22度 */
	3.90731128489273771275947e-01, /* 23度 */
	4.06736643075800152757893e-01, /* 24度 */
	4.22618261740699441286750e-01, /* 25度 */
	4.38371146789077403838064e-01, /* 26度 */
	4.53990499739546804480739e-01, /* 27度 */
	4.69471562785890805802325e-01, /* 28度 */
	4.84809620246337058535602e-01, /* 29度 */
	4.99999999999999944488849e-01, /* 30度 */
	5.15038074910054155530759e-01, /* 31度 */
	5.29919264233204900804708e-01, /* 32度 */
	5.44639035015027084263295e-01, /* 33度 */
	5.59192903470746793814783e-01, /* 34度 */
	5.73576436351046048400804e-01, /* 35度 */
	5.87785252292473137103457e-01, /* 36度 */
	6.01815023152048267363057e-01, /* 37度 */
	6.15661475325658291701814e-01, /* 38度 */
	6.29320391049837390973209e-01, /* 39度 */
	6.42787609686539251896420e-01, /* 40度 */
	6.56059028990507275835853e-01, /* 41度 */
	6.69130606358858237570075e-01, /* 42度 */
	6.81998360062498476530379e-01, /* 43度 */
	6.94658370458997254104361e-01, /* 44度 */
	7.07106781186547461715008e-01, /* 45度 */
	7.19339800338651080835461e-01, /* 46度 */
	7.31353701619170459835573e-01, /* 47度 */
	7.43144825477394133095288e-01, /* 48度 */
	7.54709580222771903024181e-01, /* 49度 */
	7.66044443118978013451681e-01, /* 50度 */
	7.77145961456970901792829e-01, /* 51度 */
	7.88010753606721903175014e-01, /* 52度 */
	7.98635510047292829227672e-01, /* 53度 */
	8.09016994374947340240567e-01, /* 54度 */
	8.19152044288991798559607e-01, /* 55度 */
	8.29037572555041624156047e-01, /* 56度 */
	8.38670567945423939271166e-01, /* 57度 */
	8.48048096156425956770875e-01, /* 58度 */
	8.57167300702112222587914e-01, /* 59度 */
	8.66025403784438596588302e-01, /* 60度 */
	8.74619707139395741180010e-01, /* 61度 */
	8.82947592858926877390502e-01, /* 62度 */
	8.91006524188367898808849e-01, /* 63度 */
	8.98794046299167037616940e-01, /* 64度 */
	9.06307787036649936673882e-01, /* 65度 */
	9.13545457642600866599025e-01, /* 66度 */
	9.20504853452440374717014e-01, /* 67度 */
	9.27183854566787313267184e-01, /* 68度 */
	9.33580426497201742996879e-01, /* 69度 */
	9.39692620785908316882740e-01, /* 70度 */
	9.45518575599316735136313e-01, /* 71度 */
	9.51056516295153531181938e-01, /* 72度 */
	9.56304755963035435506470e-01, /* 73度 */
	9.61261695938318894150143e-01, /* 74度 */
	9.65925826289068312213715e-01, /* 75度 */
	9.70295726275996472942609e-01, /* 76度 */
	9.74370064785235245885531e-01, /* 77度 */
	9.78147600733805577810642e-01, /* 78度 */
	9.81627183447663975712771e-01, /* 79度 */
	9.84807753012208020315654e-01, /* 80度 */
	9.87688340595137770350220e-01, /* 81度 */
	9.90268068741570361979143e-01, /* 82度 */
	9.92546151641321983127852e-01, /* 83度 */
	9.94521895368273289861349e-01, /* 84度 */
	9.96194698091745545198705e-01, /* 85度 */
	9.97564050259824197652847e-01, /* 86度 */
	9.98629534754573833232882e-01, /* 87度 */
	9.99390827019095762118184e-01, /* 88度 */
	9.99847695156391269577512e-01, /* 89度 */
	1.00000000000000000000000e+00, /* 90度 */
};



static GDI_ERRCODE gdi_create_parts_path(VGPath *path, GDI_SHAPE_TYPE type, const void *data);
static GDI_ERRCODE gdi_set_gradient(VGPaint *paint, GDI_GRADIENT *gradient, VGPaintType grad_type, float alpha);

#if 0
static VGErrorCode gdi_append_path_line(VGPath path, VGfloat x0, VGfloat y0, VGfloat x1, VGfloat y1);
VGErrorCode gdi_append_path_rect(VGPath path, VGfloat x, VGfloat y, VGfloat width, VGfloat height);
static VGErrorCode gdi_append_path_roundrect(VGPath path, VGfloat x, VGfloat y, VGfloat width, VGfloat height, VGfloat arc_width, VGfloat arc_height);
static VGErrorCode gdi_append_path_ellipse(VGPath path, VGfloat cx, VGfloat cy, VGfloat width, VGfloat height);
static VGErrorCode gdi_append_path_polygon(VGPath path, const VGfloat * points, VGint count, VGboolean closed);
#endif

/*
 *	<summary>		:	指定ペイントへグラデーション情報を設定
 *
 *	<parameter>		:	(i)VGPaint *	paint		:設定先ペイント
 *						(i)GDI_GRADIENT *gradient	:設定するグラデーション情報
 *						(i)VGPaintType	grad_type	:グラデーションタイプ
 *						(i)float		alpha		:アニメーションのα値
 *
 *	<return>		:	TRUE		: 処理成功
 *						FALSE		: 処理失敗
 *
 *	<description>	:	本関数は、指定されたペイントへグラデーション情報を設定する
 *		
 */
GDI_ERRCODE gdi_set_gradient(VGPaint * paint, GDI_GRADIENT *gradient, VGPaintType grad_type, float alpha)
{
	float	gradient_area[5] = { 0,0,0,0,0 };
	float	stops_tmp[5*MAX_GRADIENT_STOPS];
	const float	*gradient_stops;
	const float	*stops;
	VGint	stop_num;

	if ((!paint) || (!gradient)){
		return GDI_ILLEGAL_ARGUMENT_ERROR;
	}

	stop_num = gradient->num_stops;
	if (MAX_GRADIENT_STOPS < stop_num) {
		stop_num = MAX_GRADIENT_STOPS;
	}
	
	stops_tmp[0] = 0.0f; /* 静的解析での指摘回避 */
	
	/* Stop情報 */
	gradient_stops = gradient->stops;

	/* グラデにアニメαがかかっているか？ */
	if (alpha != 1.0F) {
		/* カラーストップのα値を変更 */
		int i;
		for (i = 0; i<stop_num; i++) {
			stops_tmp[i*5 + 0] = gradient_stops[i*5 + 0];
			stops_tmp[i*5 + 4] = gradient_stops[i*5 + 4] * alpha;
			stops_tmp[i*5 + 1] = gradient_stops[i*5 + 1] * alpha;
			stops_tmp[i*5 + 2] = gradient_stops[i*5 + 2] * alpha;
			stops_tmp[i*5 + 3] = gradient_stops[i*5 + 3] * alpha;
		}
		stops = stops_tmp;
	} else {
		/* PhloxはNon-PreMultipliedのため変更しない */
		stops = gradient_stops;
	}

	/* グラデーション種類 */
	/* 線形グラデーション */
	if (grad_type == VG_PAINT_TYPE_LINEAR_GRADIENT) {
		gradient_area[0] = gradient->x1;
		gradient_area[1] = gradient->y1;
		gradient_area[2] = gradient->x2;
		gradient_area[3] = gradient->y2;
		gradient_area[4] = 0;
		vgSetParameteri(*paint, VG_PAINT_TYPE, VG_PAINT_TYPE_LINEAR_GRADIENT);
		vgSetParameteri(*paint, VG_PAINT_COLOR_RAMP_SPREAD_MODE, VG_COLOR_RAMP_SPREAD_PAD);
		//vgSetParameteri(*paint, VG_PAINT_COLOR_RAMP_PREMULTIPLIED, TRUE);
		vgSetParameterfv(*paint, VG_PAINT_LINEAR_GRADIENT, 4, gradient_area);
		vgSetParameterfv(*paint, VG_PAINT_COLOR_RAMP_STOPS, (5 * stop_num), (float *)stops);
		
		return GDI_NO_ERROR;
	} else {
		return GDI_ILLEGAL_ARGUMENT_ERROR;
	}
}


/*
 *	<summary>		:	パスへパスデータを設定
 *
 *	<parameter>		:	(i)VGPath	path			:パス
 *						(i)short	figure_type		:図形タイプ
 *						(i)void *	figure_data		:設定するパスデータ
 *						(i)GDI_IMAGE_SVG *svg	:ヘッダ
 *
 *	<return>		:	TRUE		: 処理成功
 *						FALSE		: 処理失敗
 *
 *	<description>	:	本関数は、パスへパスデータを設定する。
 *						パスデータの形式は、図形タイプによって異なる。
 *						パスデータは描画開始位置からの相対座標のため、
 *						あらかじめイメージデータ描画開始座標へペン位置を
 *						移動しておく必要がある。
 *		
 */

GDI_ERRCODE gdi_set_figure_data(VGPath path, short figure_type, void *figure_data)
{
	int			num;
	VGboolean	close;
	VGErrorCode	err;

	if (!figure_data) {
		return GDI_ILLEGAL_ARGUMENT_ERROR;
	}

	switch (figure_type) {
	/* 直線 */
	case GDI_SHAPE_TYPE_LINE :
		err = gdi_append_path_line(path,
								   ((GDI_SHAPE_LINE*)figure_data)->x0,
								   ((GDI_SHAPE_LINE*)figure_data)->y0,
								   ((GDI_SHAPE_LINE*)figure_data)->x1,
								   ((GDI_SHAPE_LINE*)figure_data)->y1
			);
		break;

	/* 矩形 */
	case GDI_SHAPE_TYPE_RECT :
		err = gdi_append_path_rect(path,
								   ((GDI_SHAPE_RECT*)figure_data)->x,
								   ((GDI_SHAPE_RECT*)figure_data)->y,
								   ((GDI_SHAPE_RECT*)figure_data)->width,
								   ((GDI_SHAPE_RECT*)figure_data)->height
			);
		break;

	/* 角丸矩形 */
	case GDI_SHAPE_TYPE_RRECT :
		err = gdi_append_path_roundrect(path,
										((GDI_SHAPE_RRECT*)figure_data)->x,
										((GDI_SHAPE_RRECT*)figure_data)->y,
										((GDI_SHAPE_RRECT*)figure_data)->width,
										((GDI_SHAPE_RRECT*)figure_data)->height,
										((GDI_SHAPE_RRECT*)figure_data)->arc_width,
										((GDI_SHAPE_RRECT*)figure_data)->arc_height
			);
		break;

	/* 楕円&円 */
	case GDI_SHAPE_TYPE_ELLIPSE :
		err = gdi_append_path_ellipse(path,
									  ((GDI_SHAPE_ELLIPSE*)figure_data)->x, 
									  ((GDI_SHAPE_ELLIPSE*)figure_data)->y, 
									  ((GDI_SHAPE_ELLIPSE*)figure_data)->width, 
									  ((GDI_SHAPE_ELLIPSE*)figure_data)->height
			);
		break;

	/* 連続直線 */
	case GDI_SHAPE_TYPE_POLYLINE :
	/* 多角形 */
	case GDI_SHAPE_TYPE_POLYGON :
		if (figure_type == GDI_SHAPE_TYPE_POLYGON) {
			close = VG_TRUE;
		} else {
			close = VG_FALSE;
		}
		num = ((GDI_SHAPE_POLYLINE*)figure_data)->num_points;
		err = gdi_append_path_polygon(path, ((GDI_SHAPE_POLYLINE*)figure_data)->points, num, close);

		break;

	/* パス */
	case GDI_SHAPE_TYPE_PATH :
		vgGetError();	//clear the error state
		vgAppendPathData(path,												// データを紐づけるパスオブジェクトポインタ
						 ((GDI_SHAPE_PATH*)figure_data)->num_segments, 		// セグメントの数
						 ((GDI_SHAPE_PATH*)figure_data)->path_segments, 	// セグメント先頭配列
						 ((GDI_SHAPE_PATH*)figure_data)->path_data );		// 紐づけるデータ先頭配列
		err = vgGetError();
		break;

	default :
		/* エラー */
		return GDI_ILLEGAL_ARGUMENT_ERROR;
	}

	return GDI_NO_ERROR;
}



/**************************************************************************//**
 * Function Name : append_path_line
 * @brief		 : 直線のパス設定
 * @param        : [in] VGPath	path		パス
 *						VGfloat x0			X方向の開始位置
 *						VGfloat y0			Y方向の開始位置
 *						VGfloat x1			X方向の終了位置
 *						VGfloat y1			Y方向の終了位置
 * @retval       : VGErrorCode	
 *****************************************************************************/
VGErrorCode gdi_append_path_line(VGPath path, VGfloat x0, VGfloat y0, VGfloat x1, VGfloat y1)
{
	VGErrorCode error = vgGetError();	//clear the error state
	static const VGubyte segments[2] = {VG_MOVE_TO | VG_ABSOLUTE, VG_LINE_TO | VG_ABSOLUTE};
	VGfloat data[4];
	/* 始点 */
	data[0] = x0;
	data[1] = y0;
	/* 終点 */
	data[2] = x1;
	data[3] = y1;

	vgAppendPathData(path, 2, segments, data);
	error = vgGetError();
	
	return error;
}


/**************************************************************************//**
 * Function Name : append_path_rect
 * @brief		 : 四角のパス設定
 * @param        : [in]void
 * @retval       : void        : none
 *****************************************************************************/
VGErrorCode gdi_append_path_rect(VGPath path, VGfloat x, VGfloat y, VGfloat width, VGfloat height)
{
	VGErrorCode error = vgGetError();	//clear the error state

	static const VGubyte segments[5] = {VG_MOVE_TO  | VG_ABSOLUTE,
										VG_HLINE_TO | VG_ABSOLUTE,
										VG_VLINE_TO | VG_ABSOLUTE,
										VG_HLINE_TO | VG_ABSOLUTE,
										VG_CLOSE_PATH};
	VGfloat data[5];

	if (width <= 0 || height <= 0) {
		return VG_ILLEGAL_ARGUMENT_ERROR;
	}

	/* 始点 */
	data[0] = x;
	data[1] = y;
	/* 横にどれだけ進むか */
	data[2] = x + width;
	/* 縦にどれだけ進むか */
	data[3] = y + height;
	/* 横にどれだけ進むか */
	data[4] = x;

	vgAppendPathData(path, 5, segments, data);
	error = vgGetError();
	
	return error;
}


/**************************************************************************//**
 * Function Name : append_path_roundrect
 * @brief		 : 角丸四角のパス設定
 * @param        : [in]void
 * @retval       : void        : none
 *****************************************************************************/
VGErrorCode gdi_append_path_roundrect(VGPath path, VGfloat x, VGfloat y, VGfloat width, VGfloat height, VGfloat arc_width, VGfloat arc_height)
{
	VGErrorCode error = vgGetError();	//clear the error state

	static const VGubyte segments[10] = {VG_MOVE_TO    | VG_ABSOLUTE,
										 VG_HLINE_TO   | VG_ABSOLUTE,
										 VG_SCCWARC_TO | VG_ABSOLUTE,
										 VG_VLINE_TO   | VG_ABSOLUTE,
										 VG_SCCWARC_TO | VG_ABSOLUTE,
										 VG_HLINE_TO   | VG_ABSOLUTE,
										 VG_SCCWARC_TO | VG_ABSOLUTE,
										 VG_VLINE_TO   | VG_ABSOLUTE,
										 VG_SCCWARC_TO | VG_ABSOLUTE,
										 VG_CLOSE_PATH};
	VGfloat data[26];
	VGfloat x0, x1, x2, x3;
	VGfloat y0, y1, y2, y3;
	VGfloat half_arc_width, half_arc_height;

	if (width <= 0 || height <= 0) {
		return VG_ILLEGAL_ARGUMENT_ERROR;
	}

	half_arc_width = arc_width / 2.0f;
	half_arc_height = arc_height / 2.0f;
	
	x0 = x;
	x1 = x + half_arc_width;
	x2 = x + width - half_arc_width;
	x3 = x + width;
	
	y0 = y;
	y1 = y + half_arc_height;
	y2 = y + height - half_arc_height;
	y3 = y + height;

	/* 始点 */
	data[0] = x1;
	data[1] = y0;
	/* 横に進む位置 */
	data[2] = x2;
	/* 角丸 */
	data[3] = x3-x2;
	data[4] = y1-y0;
	data[5] = 0;
	data[6] = x3;
	data[7] = y1;
	/* 縦に進む位置 */
	data[8] = y2;
	/* 角丸 */
	data[9] = x3-x2;
	data[10] = y3-y2;
	data[11] = 0;
	data[12] = x2;
	data[13] = y3;
	/* 横に進む位置 */
	data[14] = x1;
	/* 角丸 */
	data[15] = x1-x0;
	data[16] = y3-y2;
	data[17] = 0;
	data[18] = x0;
	data[19] = y2;
	/* 縦に進む位置 */
	data[20] = y1;
	/* 角丸 */
	data[21] = x1-x0;
	data[22] = y1-y0;
	data[23] = 0;
	data[24] = x1;
	data[25] = y0;

    vgAppendPathData(path, 10, segments, data);
	error = vgGetError();
	
	return error;
}


/**************************************************************************//**
 * Function Name : append_path_ellipse
 * @brief		 : 円・楕円のパス設定
 * @param        : [in]void
 * @retval       : void        : none
 *****************************************************************************/
VGErrorCode gdi_append_path_ellipse(VGPath path, VGfloat cx, VGfloat cy, VGfloat width, VGfloat height)
{
	VGErrorCode error = vgGetError();	//clear the error state

	static const VGubyte segments[4] = {VG_MOVE_TO    | VG_ABSOLUTE,
										VG_SCCWARC_TO | VG_ABSOLUTE,
										VG_SCCWARC_TO | VG_ABSOLUTE,
										VG_CLOSE_PATH};
	VGfloat data[12];

	if (width <= 0 || height <= 0) {
		return VG_ILLEGAL_ARGUMENT_ERROR;
	}

	/* 始点 */
	data[0] = cx + width/2;
	data[1] = cy;
	/* 半円 */
	data[2] = width/2;
	data[3] = height/2;
	data[4] = 0;
	data[5] = cx - width/2;
	data[6] = cy;
	/* 半円 */
	data[7] = width/2;
	data[8] = height/2;
	data[9] = 0;
	data[10] = cx + width/2;
	data[11] = cy;

    vgAppendPathData(path, 4, segments, data);

	error = vgGetError();
	return error;
}


/**************************************************************************//**
 * Function Name : append_path_polygon
 * @brief		 : 多角形のパス設定
 * @param        : [in]void
 * @retval       : void        : none
 *****************************************************************************/
VGErrorCode gdi_append_path_polygon(VGPath path, const VGfloat * points, VGint count, VGboolean closed)
{
    VGubyte segments[MAX_POLYGON_COUNT + 1];
	VGErrorCode error = vgGetError();	//clear the error state

	if (!points || (((int)points) & 3) || count <= 0 || count > MAX_POLYGON_COUNT) {
		return VG_ILLEGAL_ARGUMENT_ERROR;
	}

	if (count > MAX_POLYGON_COUNT) {
		return VG_ILLEGAL_ARGUMENT_ERROR;
	}

	/* GPIのMALLOCを使用 */
    /* ToDo:最大頂点数を調べて固定長で確保 */
    segments[0] = VG_MOVE_TO_ABS;
	/* 絶対座標で線を描く */
    memset(&segments[1], VG_LINE_TO_ABS, count - 1);
	/* もしパスを閉じるならcount+1まで使う/閉じないならcountまで */
    segments[count] = VG_CLOSE_PATH;
    vgAppendPathData(path, closed? (count + 1) : count, segments, points);
	error = vgGetError();

	return error;
}


#define DRAW_ALPHA_FACTOR_MAX 		(1.0f)
#define DRAW_ALPHA_FACTOR_MIN 		(0.5f)
static VGfloat checkAlphaFactor(VGfloat alpha_factor)
{
	VGfloat ret = alpha_factor;

	if (0.0f == ret) {
		return DRAW_ALPHA_FACTOR_MAX;
	}

	//α係数は0.5～1.0の範囲で設定
	if (DRAW_ALPHA_FACTOR_MAX < ret) {
		ret = DRAW_ALPHA_FACTOR_MAX;
	} else if (ret < DRAW_ALPHA_FACTOR_MIN) {
		ret = DRAW_ALPHA_FACTOR_MIN;
	}
	return ret;
}

static VGPaint getDrawColor(VGPaint paint, VGfloat alpha_factor)
{
	VGPaint drawPaint = vgCreatePaint();
	VGuint color = vgGetColor(paint);
	VGuint alpha = (color & 0xFF);

	if ((drawPaint == VG_INVALID_HANDLE) || (vgGetError() != VG_NO_ERROR)) {
		return VG_INVALID_HANDLE;
	}
	
	alpha = ((VGuint)(alpha * checkAlphaFactor(alpha_factor))) & 0xFF;	/* pgr0247	*/	//α値に係数を掛ける
	color = (color & (~0xFF)) | alpha;
	vgSetColor(drawPaint, color);

	return drawPaint;
}


GDI_ERRCODE gdi_create_color(GDI_COLOR *color_set, VGPaint *ppaint, VGfloat alpha_factor)
{
	GDI_GRADIENT	*gradient;
	float			color[4];
	float			alpha;
	VGPaint			paint = VG_INVALID_HANDLE;
	GDI_ERRCODE		err = GDI_NO_ERROR;

	if ((color_set == NULL) || (ppaint == NULL))
		return GDI_ILLEGAL_ARGUMENT_ERROR;
	
	//塗りつぶし情報を設定		
	switch (color_set->type) {	
	case VG_PAINT_TYPE_COLOR:			/* 通常塗りつぶし */
		paint = vgCreatePaint();
		if (VG_INVALID_HANDLE == paint || vgGetError() != VG_NO_ERROR) {
			err = GDI_EGL_ERROR;
			goto error;
		}

		GDI_MAKE_F_RGBA(color_set->color, color);


		color[3] *= checkAlphaFactor(alpha_factor);

#if 0
		color[0] = ((color_set->color >> 24) & 0xFF) / 255.0f;
		color[1] = ((color_set->color >> 16) & 0xFF) / 255.0f;
		color[2] = ((color_set->color >>  8) & 0xFF) / 255.0f;
		color[3] = ((color_set->color)       & 0xFF) / 255.0f;
#endif
		vgSetParameteri(paint, VG_PAINT_TYPE, VG_PAINT_TYPE_COLOR);

		vgSetParameterfv(paint, VG_PAINT_COLOR, 4, color);

//		vgSetColor(paint, color_set->color);


		break;

	case VG_PAINT_TYPE_LINEAR_GRADIENT:	/* 線形グラデーション or 放射グラデーション */
		paint = vgCreatePaint();
		if (VG_INVALID_HANDLE == paint || vgGetError() != VG_NO_ERROR) {
			err = GDI_EGL_ERROR;
			goto error;
		}
		
		GDI_MAKE_F_RGB_A(color_set->color, color);
		
		if ((gradient = (GDI_GRADIENT *)color_set->gradient) == NULL) {
			err = GDI_ILLEGAL_ARGUMENT_ERROR;
			goto error;
		}
		
		/* グラデーションを使用するエレメントに半透明設定があれば反映させる、*/
		alpha = color[3] * checkAlphaFactor(alpha_factor);
		
		/* 線塗りつぶし用ペイントにグラデーション情報を設定 */
		err = gdi_set_gradient(&paint, (GDI_GRADIENT *)gradient, color_set->type, alpha);
		if (GDI_NO_ERROR != err) goto error;
		break;
		
	default :	/* エラー */
		err = GDI_ILLEGAL_ARGUMENT_ERROR;
		goto error;
	}

	*ppaint = paint;
	return err;

error:
	if (paint != VG_INVALID_HANDLE)
		vgDestroyPaint(paint);
	
	return err;
}

GDI_CACHE_PATH *gdi_create_parts(const GDI_IMAGE_SVG *svg)
{
	const GDI_PARTS	*const *parts_list = NULL;
	const GDI_PARTS *parts = NULL;
	long 			parts_num;
	
	int	i;
	VGPath			path   = VG_INVALID_HANDLE;
	VGPaint			stroke = VG_INVALID_HANDLE;
	VGPaint			fill   = VG_INVALID_HANDLE;
	VGbitfield		mode   = 0;
	GDI_CACHE_PATH  top, *cache = NULL, *current = NULL;
	top.next = NULL;

	if (svg == NULL)
		return NULL;
	
	/* 図形データ取得 */
	parts_num = svg->shape_num;
	parts_list = svg->data;
	
	if (parts_list == NULL) {
		return NULL;
	}

	/* 
	 *	図形データの各属性を順次OpenVGコンテキストへ設定し、描画を行う
	 */
	for (i = 0; i < parts_num; i++) {
		//部品データの取り出し
		parts = parts_list[i];
		if (NULL == parts) {
			continue;
		}

		// 初期化
		{
			cache = gdi_alloc_cache_path();
			if (NULL == cache) {
				goto error;
			}
		
			path   = VG_INVALID_HANDLE;
			stroke = VG_INVALID_HANDLE;
			fill   = VG_INVALID_HANDLE;
			mode   = 0;
		}

		if (GDI_NO_ERROR != gdi_create_parts_path(&path, parts->type, parts->data)) {
			return NULL;
		}

		// ペイント情報の設定
		if (0 != (parts->paint_mode & VG_STROKE_PATH)) {
			if (GDI_NO_ERROR != gdi_create_color((GDI_COLOR *)parts->stroke_color, &stroke, DRAW_ALPHA_FACTOR_MAX)) {
				return NULL;
			}
			mode |= VG_STROKE_PATH;
		}

		if (0 != (parts->paint_mode & VG_FILL_PATH)) {
			if (GDI_NO_ERROR != gdi_create_color((GDI_COLOR *)parts->fill_color, &fill, DRAW_ALPHA_FACTOR_MAX)) {
				return NULL;
			}
			mode |= VG_FILL_PATH;
		}

		//キャッシュへの反映
		cache->parts  = (GDI_PARTS *)parts;
		cache->path   = path;
		cache->stroke = stroke;
		cache->fill   = fill;
		cache->mode   = mode;	/* pgr0351 */

		//先頭ポインタへの反映
		if (top.next == NULL) {
			top.next = cache;
		} else {
			//2つ目以降はnextにセット
			if (current != NULL)
				current->next = cache;
		}
		current = cache;
	}

	return top.next;
		
  error:
	cache = top.next;
	while (cache != NULL) {
		gdi_free_cache_path(cache);
		cache = cache->next;
	}
	
	return NULL;
}


static GDI_ERRCODE gdi_create_parts_path(VGPath *ppath, GDI_SHAPE_TYPE type, const void *data)
{
	VGPath	path = VG_INVALID_HANDLE;

	if ((ppath == NULL) || (data == NULL))
		return GDI_ILLEGAL_ARGUMENT_ERROR;
	
	/* VGPath作成 */
    if (((path = vgCreatePath(VG_PATH_FORMAT_STANDARD, VG_PATH_DATATYPE_F, 1.0f, 0.0f, 0, 0, VG_PATH_CAPABILITY_ALL)) == VG_INVALID_HANDLE) || (vgGetError() != VG_NO_ERROR)) {
		goto error;
	}

	/* 
	 *	図形タイプ毎に固有な情報をパスに設定する
	 */
	/* パスデータの紐付け(座標データは、リソース内での相対座標のためTranslateで移動が必要) */
	if (gdi_set_figure_data(path, type, (void *)data) != GDI_NO_ERROR)
		goto error;	/* 次の図形を処理 */

	*ppath = path;
	return GDI_NO_ERROR;

error:
	if (path != VG_INVALID_HANDLE) {
		vgDestroyPath(path);
		*ppath = VG_INVALID_HANDLE;
	}
	
	return GDI_EGL_ERROR;
}

void gdi_draw_parts(GDI_CACHE_PATH *cache, VGPaint stroke, VGPaint fill, VGfloat alpha_factor)
{
	VGPaint drawstroke = VG_INVALID_HANDLE;
	VGPaint drawfill = VG_INVALID_HANDLE;

	while (cache != NULL) {
		drawstroke = VG_INVALID_HANDLE;
		if (cache->mode & VG_STROKE_PATH) {
			vgSeti(VG_STROKE_CAP_STYLE,   cache->parts->cap_style);		/* エンドキャップスタイル */
			vgSeti(VG_STROKE_JOIN_STYLE,  cache->parts->join_style);	/* ライン接続スタイル */
			vgSetf(VG_STROKE_MITER_LIMIT, cache->parts->miter_limit);	/* マイターリミット */
			vgSetf(VG_STROKE_LINE_WIDTH,  cache->parts->stroke_width);	/* 外周線の幅 */

			if (NULL == (GDI_DASH *)cache->parts->dash_info) {
				vgSetfv(VG_STROKE_DASH_PATTERN, 0, NULL);
				vgSetf(VG_STROKE_DASH_PHASE, 0.0F);
			} else {
				vgSetfv(VG_STROKE_DASH_PATTERN, ((GDI_DASH *)cache->parts->dash_info)->count, ((GDI_DASH *)cache->parts->dash_info)->dash_pattern);	/* 外周線の点線パターン */
				vgSetf(VG_STROKE_DASH_PHASE, 0.0F);		/* 描画オフセット */
			}
			/* ペイントオブジェクト設定 */
			drawstroke = getDrawColor(((stroke == VG_INVALID_HANDLE) ? cache->stroke : stroke), alpha_factor);
			if (drawstroke != VG_INVALID_HANDLE)
				vgSetPaint(drawstroke, VG_STROKE_PATH);
		}

		drawfill = VG_INVALID_HANDLE;
		if (cache->mode & VG_FILL_PATH) {
			vgSeti(VG_FILL_RULE, cache->parts->fill_rule);		/* 塗り潰しルール */
			drawfill = getDrawColor(((fill == VG_INVALID_HANDLE) ? cache->fill : fill), alpha_factor);
			if (drawfill != VG_INVALID_HANDLE)
				vgSetPaint(drawfill, VG_FILL_PATH);
		}

		/* ペイントモードを指定しパスの描画 */
		vgDrawPath(cache->path, cache->mode);

		if (VG_INVALID_HANDLE != drawstroke) vgDestroyPaint(drawstroke);
		if (VG_INVALID_HANDLE != drawfill) vgDestroyPaint(drawfill);

		cache = cache->next;
	}
}
