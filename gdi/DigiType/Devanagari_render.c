
#include "Devanagari_render.h"
#include "indic_find_syllable.h"


#define DEVA_REPH      0x0930
#define DEVA_VIRAMA    0x094d
#define DEVA_NUKTA     0x093c
#define DEVA_PREVOWEL  0x093f
#define DEVA_25CC      0x25CC
#define DEVA_25CC_REPLACE 0x0978

#define STA_START (0)
#define STA_VIRAMA (1)
#define STA_NUKTA (2)

#define SHIFT_DEPENDENT(xx) ((xx & 0x00ff)<<8)
#define SHIFT_SIGN_CAN(yy)  ((yy & 0x0003)<<6) 
#define SHIFT_REPH_SUP(zz)  ((zz & 0x0001)<<5)

#define SIGN_V(dependent_x , can_y , reph_sup_z) \
	SHIFT_DEPENDENT(dependent_x)+SHIFT_SIGN_CAN(can_y)+SHIFT_REPH_SUP(reph_sup_z)

UNI_CHAR reph_sup = 0xef10;
UNI_CHAR reph_sub = 0xef12;
/*
	The following table must be sorted by first column because 
	the program use binary search to get mapping value.
*/
static HALF_ROW signs_table[]={
	{SIGN_V(0,0x0902,1),      0xef13},
	/**/
	/*{SIGN_V(0x093f,0,1),      0xef14},*/
	/*{SIGN_V(0x093f,0x0902,1), 0xef1b},*/
	/**/
	{SIGN_V(0x0940,0,1),      0xef22},
	{SIGN_V(0x0940,0x0902,1), 0xef25},
	/**/
	/*
	{SIGN_V(0x0941,0,1),      0xef32},
	{SIGN_V(0x0942,0,1),      0xef33},*/

	{SIGN_V(0x0947,0,1),      0xef29},
	{SIGN_V(0x0947,0x0902,0), 0xef28},
	{SIGN_V(0x0947,0x0902,1), 0xef2a},
	/**/
	{SIGN_V(0x0948,0,1),      0xef2c},
	{SIGN_V(0x0948,0x0902,0), 0xef2b},
	{SIGN_V(0x0948,0x0902,1), 0xef2d},
	/**/
	{SIGN_V(0x094b,0,1),      0xef2e},
	{SIGN_V(0x094b,0x0902,1), 0xef30},
	/**/
	{SIGN_V(0x094c,0,1), 0xef2f},
	{SIGN_V(0x094c,0x0902,1), 0xef31},

};

/*REPH_SUB*/
static HALF_ROW reph_sub_table[] = {
	{0x0915,0xef34},
	{0x0916,0xef36},
	{0x0917,0xef37},
	{0x0918,0xef38},
	{0x091a,0xef39},
	{0x091c,0xef3a},
	{0x091d,0xef3b},
/*
	{0x091e,0xe99c},
	{0x091f,0xe99d},
*/
	{0x0924,0xef3d},
	{0x0925,0xef3e},
	{0x0926,0xef3f},
	{0x0927,0xef40},
	{0x0928,0xef41},
	{0x092a,0xef42},
	{0x092b,0xef43},
	{0x092c,0xef44},
	{0x092d,0xef45},
	{0x092e,0xef46},
	{0x092f,0xef47},
	{0x0932,0xef48},
	{0x0935,0xef4a},
	{0x0936,0xef4b},
	{0x0937,0xf36c},/**/
	{0x0938,0xef4c},
	{0x0939,0xef4d},
	{0x0958,0xef4e},
	{0x0959,0xef4f},
	{0x095a,0xef50},
	{0x095b,0xef51},
	{0x095e,0xef52},
	{0x095f,0xef53},
};

/*NUKTA*/
static HALF_ROW nukta_table[]={
	{0x0915,0x0958},
	{0x0916,0x0959},
	{0x0917,0x095a},
	{0x091c,0x095b},
	{0x0921,0x095c},
	{0x0922,0x095d},
	{0x092b,0x095e},
	{0x092f,0x095f},
};

/*NUKTA_REPH_SUB*/		
static HALF_ROW nukta_reph_sub_table[]={
	{0x0915,0xef4e},
	{0x0916,0xef4f},
	{0x0917,0xef50},
	{0x091c,0xef51},
/*
	{0x091f,0xe0ab},
*/
	{0x092b,0xef52},
	{0x092f,0xef53},
};


/*HALF FORM*/
static HALF_ROW half_table[]={
	{0x0915,0xf318},
	{0x0916,0xf319},
	{0x0917,0xf31b},
	{0x0918,0xf31c},
	{0x0919,0xf375},/**/
	{0x091A,0xf31d},
	{0x091b,0xf31f},
	{0x091c,0xf320},
	{0x091d,0xf321},
	{0x091e,0xf324},
	{0x091f,0xf376},/**/
	{0x0920,0xf34d},/**/
	{0x0921,0xf34e},/**/
	{0x0922,0xf34f},/**/
	{0x0923,0xf325},
	{0x0924,0xf326},
	{0x0925,0xf328},
	{0x0926,0xf377},/**/
	{0x0927,0xf329},
	{0x0928,0xf32a},
	{0x0929,0xf32c},
	{0x092a,0xf32d},
	{0x092b,0xf32f},
	{0x092c,0xf330},
	{0x092d,0xf332},
	{0x092e,0xf333},
	{0x092f,0xf335},
	{0x0930,0xef12},/**/
	{0x0931,0xf336},
	{0x0932,0xf337},
	{0x0933,0xf33a},
	{0x0934,0xf33b},
	{0x0935,0xf33c},
	{0x0936,0xf33e},
	{0x0937,0xf340},
	{0x0938,0xf342},
	{0x0939,0xf374},

	{0x0958,0xf344},
	{0x0959,0xf345},
	{0x095a,0xf346},
	{0x095b,0xf347},
	{0x095e,0xf348},
	{0x095f,0xf349},
};/*half_table*/



/*NUKTA_HALF*/
static HALF_ROW half_nukta_table[]={
	{0x0915,0xf344},
	{0x0916,0xf345},
	{0x0917,0xf346},
	{0x091c,0xf347},
	{0x092b,0xf348},
	{0x092f,0xf349},
	{0x0930,0xf336},
};

/*HALF_REPH_SUB*/
static HALF_ROW half_sub_table[]={
	{0x0915,0xef55},
	{0x0918,0xef56},
	{0x0924,0xef57},
	{0x0927,0xef59},
	{0x092a,0xef5a},
	{0x0935,0xef5b},
	{0x0936,0xef5c},
	{0x0938,0xef5d}
};

/*
	LIGA = HALF+HALANT+CONSONANT 
*/
static LIGA_ROW liga_table[]={
	{0xef57,0x092f,0xefc8},
	{0xef5c,0x092f,0xef73},
	/*0x0915---0xf318*/
	{0xf318,0x0915,0xf201},
	{0xf318,0x0916,0xf202},
	{0xf318,0x091a,0xf203},
	{0xf318,0x091c,0xf204},
	{0xf318,0x091f,0xf205},
	{0xf318,0x0923,0xf206},
	{0xf318,0x0924,0xf207},
	{0xf318,0x0925,0xf208},
	{0xf318,0x0926,0xf209},
	{0xf318,0x0928,0xf20a},
	{0xf318,0x092a,0xf20b},
	{0xf318,0x092b,0xf20c},
	{0xf318,0x092e,0xf20d},
	{0xf318,0x092f,0xf20e},
	{0xf318,0x0932,0xf20f},
	{0xf318,0x0935,0xf211},
	{0xf318,0x0936,0xf212},
	{0xf318,0x0937,0xef5e},/**/
	{0xf318,0x0938,0xf213},
	{0xf318,0xef3d,0xefa3},/*24+30*/ /*0xef3d*/
	{0xf318,0xef42,0xefa6},/*2a+30*/ /*0xef42*/
	{0xf318,0xf36c,0xef54},/*37+30*/ /*0xf36c*/

	/*0x0916 --- 0xf319*/
	{0xf319,0x0916,0xf214},
	{0xf319,0x0924,0xf215},
	{0xf319,0x0928,0xf216},
	{0xf319,0x092e,0xf217},
	{0xf319,0x092f,0xf218},
	{0xf319,0x0935,0xf219},
	{0xf319,0x0936,0xf21a},
	/*0x0917 --- 0xf31b*/
	{0xf31b,0x0917,0xf21b},
	{0xf31b,0x0918,0xf21c},
	{0xf31b,0x091c,0xf21d},
	{0xf31b,0x0923,0xf21e},
	{0xf31b,0x0926,0xf21f},
	{0xf31b,0x0927,0xf220},
	{0xf31b,0x0928,0xf221},
	{0xf31b,0x092c,0xf222},
	{0xf31b,0x092d,0xf223},
	{0xf31b,0x092e,0xf224},
	{0xf31b,0x092f,0xf225},
	{0xf31b,0x0932,0xf226},
	{0xf31b,0x0935,0xf228},
	{0xf31b,0x0938,0xf229},
	/*0x0918 --- 0xf31c*/
	{0xf31c,0x0928,0xf22b},
	{0xf31c,0x092e,0xf22c},
	{0xf31c,0x092f,0xf22d},
	/*0x091a --- 0xf31d*/
	{0xf31d,0x091a,0xf22e},
	{0xf31d,0x091b,0xf22f},
	{0xf31d,0x0928,0xf230},
	{0xf31d,0x092e,0xf231},
	{0xf31d,0x092f,0xf232},
	/*0x091b --- 0xf31f*/
	{0xf31f,0x0935,0xf234},
	/*0x091c --- 0xf320*/
	{0xf320,0x0915,0xf235},
	{0xf320,0x091c,0xf236},
	{0xf320,0x091d,0xf237},
	{0xf320,0x091e,0xef5f},/**/
	{0xf320,0x091f,0xf238},
	{0xf320,0x0921,0xf239},
	{0xf320,0x0924,0xf23a},
	{0xf320,0x0926,0xf23b},
	{0xf320,0x0928,0xf23c},
	{0xf320,0x092c,0xf23d},
	{0xf320,0x092e,0xf23e},
	{0xf320,0x092f,0xf23f},
	{0xf320,0x0935,0xf240},
	/*0x091d --- 0xf321*/
	{0xf321,0x0928,0xf241},
	{0xf321,0x092e,0xf242},
	{0xf321,0x092f,0xf244},
	/*0x091e --- 0xf324*/
	{0xf324,0x091a,0xf246},
	{0xf324,0x091b,0xf247},
	{0xf324,0x091c,0xf248},
	{0xf324,0x0936,0xf249},
	/*0x0923 --- 0xf325*/
	{0xf325,0x091f,0xf24a},
	{0xf325,0x0920,0xf24b},
	{0xf325,0x0921,0xf24c},
	{0xf325,0x0922,0xf24d},
	{0xf325,0x0923,0xf24e},
	{0xf325,0x092e,0xf24f},
	{0xf325,0x092f,0xf250},
	{0xf325,0x0935,0xf251},
	/*0x0924 --- 0xf326*/
	{0xf326,0x0915,0xf252},
	{0xf326,0x0916,0xf253},
	{0xf326,0x0924,0xf254},
	{0xf326,0x0925,0xf255},
	{0xf326,0x0928,0xf256},
	{0xf326,0x092a,0xf257},
	{0xf326,0x092b,0xf258},
	{0xf326,0x092e,0xf259},
	{0xf326,0x092f,0xf25a},
	{0xf326,0x0932,0xf25b},
	{0xf326,0x0935,0xf25d},
	{0xf326,0x0938,0xf25e},
	{0xf326,0xef34,0xefbb}, /*15+30*//*0xef34*/
	{0xf326,0xef36,0xefc0}, /*16+30*//*0xef36*/
	{0xf326,0xef42,0xefc4}, /*2a+30*/
	/*0x0925 --- 0xf328*/
	{0xf328,0x092f,0xf25f},
	{0xf328,0x0935,0xf260},
	/*0x0927 --- 0xf329*/
	{0xf329, 0x0928, 0xf262},
	{0xf329, 0x092e, 0xf263},
	{0xf329, 0x092f, 0xf264},
	{0xf329, 0x0935, 0xf265},
	/*0x0928 --- 0xf32a*/
	{0xf32a, 0x0915, 0xf266},
	{0xf32a, 0x091a, 0xf267},
	{0xf32a, 0x091b, 0xf268},
	{0xf32a, 0x091f, 0xf269},
	{0xf32a, 0x0921, 0xf26a},
	{0xf32a, 0x0924, 0xf26b},
	{0xf32a, 0x0925, 0xf26c},
	{0xf32a, 0x0926, 0xf26d},
	{0xf32a, 0x0927, 0xf26e},
	{0xf32a, 0x0928, 0xf26f},
	{0xf32a, 0x092a, 0xf270},
	{0xf32a, 0x092b, 0xf271},
	{0xf32a, 0x092d, 0xf272},
	{0xf32a, 0x092e, 0xf273},
	{0xf32a, 0x092f, 0xf274},
	{0xf32a, 0x0935, 0xf275},
	{0xf32a, 0x0938, 0xf276},
	{0xf32a, 0x0939, 0xf277},
	{0xf32a,0xef3d,0xefd0}, /*24+30*/
	{0xf32a,0xef3f,0xefd5}, /*26+30*/ /*0xef3f*/
	{0xf32a,0xef40,0xefd8}, /*27+30*/ /*0xef40*/
	{0xf32a,0xef42,0xefda}, /*2a+30*/
	/*0x092a --- 0xf32d*/
	{0xf32d, 0x091f, 0xf278},
	{0xf32d, 0x0924, 0xf279},
	{0xf32d, 0x0928, 0xf27a},
	{0xf32d, 0x092a, 0xf27b},
	{0xf32d, 0x092b, 0xf27c},
	{0xf32d, 0x092e, 0xf27d},
	{0xf32d, 0x092f, 0xf27e},
	{0xf32d, 0x0932, 0xf27f},
	{0xf32d, 0x0935, 0xf281},
	{0xf32d, 0x0938, 0xf282},
	/*0x092b --- 0xf32f*/
	{0xf32f, 0x091c, 0xf283},
	{0xf32f, 0x091f, 0xf284},
	{0xf32f, 0x0924, 0xf285},
	{0xf32f, 0x092a, 0xf287},
	{0xf32f, 0x092b, 0xf288},
	{0xf32f, 0x092f, 0xf289},
	{0xf32f, 0x0932, 0xf28a},
	{0xf32f, 0x0936, 0xf28c},
	/*0x092c --- 0xf330*/
	{0xf330, 0x091c, 0xf28d},
	{0xf330, 0x091d, 0xf28e},
	{0xf330, 0x0924, 0xf290},
	{0xf330, 0x0926, 0xf291},
	{0xf330, 0x0927, 0xf292},
	{0xf330, 0x0928, 0xf293},
	{0xf330, 0x092c, 0xf294},
	{0xf330, 0x092d, 0xf295},
	{0xf330, 0x092f, 0xf296},
	{0xf330, 0x0932, 0xf297},
	{0xf330, 0x0935, 0xf299},
	{0xf330, 0x0936, 0xf29a},
	{0xf330, 0x0938, 0xf29b},
	{0xf330, 0x095b, 0xf29c},
	{0xf330,0xef45,0xefe4}, /*2d+30*/
	/*0x092d --- 0xf332*/
	{0xf332, 0x092f, 0xf29d},
	{0xf332, 0x0932, 0xf29e},
	{0xf332, 0x0935, 0xf2a0},
	/*0x092e --- 0xf333*/
	{0xf333, 0x0924, 0xf2a3},
	{0xf333, 0x0926, 0xf2a4},
	{0xf333, 0x0928, 0xf2a5},
	{0xf333, 0x092a, 0xf2a6},
	{0xf333, 0x092c, 0xf2a7},
	{0xf333, 0x092d, 0xf2a8},
	{0xf333, 0x092e, 0xf2a9},
	{0xf333, 0x092f, 0xf2aa},
	{0xf333, 0x0932, 0xf2ab},
	{0xf333, 0x0935, 0xf2ad},
	{0xf333, 0x0936, 0xf2ae},
	{0xf333, 0x0938, 0xf2af},
	{0xf333, 0x0939, 0xf2b0},
	{0xf333,0xef42,0xefe6}, /*2a+30*/ 
	{0xf333,0xef44,0xefe8}, /*2c+30*/ /*0xef44*/
	{0xf333,0xef45,0xefea}, /*2d+30*/ /*0xef45*/
	/*0x092f --- 0xf335*/
	{0xf335, 0x092f, 0xf2b1},
	/*0x0932 --- 0xf337*/
	{0xf337, 0x0915, 0xf2b2},
	{0xf337, 0x0916, 0xf2b3},
	{0xf337, 0x0917, 0xf2b4},
	{0xf337, 0x091c, 0xf2b5},
	{0xf337, 0x091f, 0xf2b6},
	{0xf337, 0x0920, 0xf2b7},
	{0xf337, 0x0921, 0xf2b8},
	{0xf337, 0x0922, 0xf2b9},
	{0xf337, 0x0924, 0xf2ba},
	{0xf337, 0x0925, 0xf2bb},
	{0xf337, 0x0926, 0xf2bc},
	{0xf337, 0x092a, 0xf2bd},
	{0xf337, 0x092b, 0xf2bf},
	{0xf337, 0x092c, 0xf2c0},
	{0xf337, 0x092d, 0xf2c1},
	{0xf337, 0x092e, 0xf2c2},
	{0xf337, 0x092f, 0xf2c3},
	{0xf337, 0x0932, 0xf2c4},
	{0xf337, 0x0935, 0xf2c6},
	{0xf337, 0x0938, 0xf2c7},
	{0xf337, 0x0939, 0xf2c8},
	{0xf337, 0x095b, 0xf2c9},
	{0xf337,0xef3f,0xefee}, /*26+30*/
	/*0x0933 --- 0xf33a*/
	{0xf33a, 0x092f, 0xf2ca},
	/*0x0935 --- 0xf33c*/
	{0xf33c, 0x092f, 0xf2cb},
	{0xf33c, 0x0932, 0xf2cc},
	{0xf33c, 0x0935, 0xf2ce},
	{0xf33c, 0x0939, 0xf2cf},
	/*0x0936 --- 0xf33e*/
	{0xf33e, 0x0915, 0xf2d0},
	{0xf33e, 0x091a, 0xf2d1},
	{0xf33e, 0x091b, 0xf2d2},
	{0xf33e, 0x091f, 0xf2d3},
	{0xf33e, 0x0924, 0xf2d4},
	{0xf33e, 0x0928, 0xf2d5},
	{0xf33e, 0x092e, 0xf2d6},
	{0xf33e, 0x092f, 0xf2d7},
	{0xf33e, 0x0932, 0xf2d8},
	{0xf33e, 0x0935, 0xf2da},
	{0xf33e, 0x0936, 0xf2db},
	{0xf33e, 0x0958, 0xf2dc},
	/*0x0937 --- 0xf340*/
	{0xf340, 0x0915, 0xf2dd},
	{0xf340, 0x091f, 0xf2de},
	{0xf340, 0x0920, 0xf2df},
	{0xf340, 0x0923, 0xf2e0},
	{0xf340, 0x092a, 0xf2e1},
	{0xf340, 0x092b, 0xf2e2},
	{0xf340, 0x092e, 0xf2e3},
	{0xf340, 0x092f, 0xf2e4},
	{0xf340, 0x0935, 0xf2e5},
	{0xf340, 0x0937, 0xf2e6},
	{0xf340,0xef34,0xeff2},/*15+30*/
	{0xf340,0xef42,0xeff4},/*2a+30*/
	/*0x0938 --- 0xf342*/
	{0xf342, 0x0915, 0xf2e7},
	{0xf342, 0x0916, 0xf2e8},
	{0xf342, 0x091c, 0xf2ea},
	{0xf342, 0x091f, 0xf2eb},
	{0xf342, 0x0924, 0xf2ec},
	{0xf342, 0x0925, 0xf2ed},
	{0xf342, 0x0926, 0xf2ee},
	{0xf342, 0x0928, 0xf2ef},
	{0xf342, 0x092a, 0xf2f0},
	{0xf342, 0x092b, 0xf2f1},
	{0xf342, 0x092c, 0xf2f2},
	{0xf342, 0x092e, 0xf2f3},
	{0xf342, 0x092f, 0xf2f4},
	{0xf342, 0x0932, 0xf2f5},
	{0xf342, 0x0935, 0xf2f7},
	{0xf342, 0x0938, 0xf2f8},
	{0xf342, 0xef34, 0xeff6},/*15+30*/
	{0xf342, 0xef3d, 0xeffa},/*24+30*/
	{0xf342, 0xef42, 0xefff},/*2a+30*/
	/*0x0958 --- 0xf344*/
	{0xf344, 0x0924, 0xf2f9},
	{0xf344, 0x092b, 0xf2fa},
	{0xf344, 0x092c, 0xf2fb},
	{0xf344, 0x092e, 0xf2fc},
	{0xf344, 0x0958, 0xf2fd},
	{0xf344, 0x095e, 0xf2fe},
	/*0x0959 --- 0xf345*/
	{0xf345, 0x0924, 0xf2ff},
	{0xf345, 0x092e, 0xf300},
	{0xf345, 0x092f, 0xf301},
	{0xf345, 0x0935, 0xf302},
	{0xf345, 0x0936, 0xf303},
	{0xf345, 0x0938, 0xf304},
	/*0x095b --- 0xf347*/
	{0xf347, 0x092f, 0xf305},
	{0xf347, 0x095b, 0xf306},
	/*0x095e --- 0xf348*/
	{0xf348, 0x0924,0xf307},
	{0xf348, 0x0938,0xf308},
	{0xf348, 0x095b,0xf309},
	{0xf348, 0x095e,0xf30a},

	/*15+37*/
	{0xf34a, 0x092e,0xefa8},
	{0xf34a, 0x092f,0xefa9},
	{0xf34a, 0x0935,0xefaa}, 
	/*1c+1e*/
	{0xf34b, 0x092f,0xefb7},
	/*24*24*/
	{0xf30c, 0x092f,0xefc1},
	{0xf30c, 0x0935,0xefc2},

	/*0x0920 --- 0xf34d*/
	{0xf34d,0x0920,0xef83},
	/*0x0921 --- 0xf34e*/
	{0xf34e,0x091f,0xef85},
	{0xf34e,0x0921,0xef86},
	{0xf34e,0x0922,0xef87},
	/*0x0922 --- 0xf34f*/
	{0xf34f,0x0922,0xef89},

	/*0x0939 --- 0xf374*/
	{0xf374,0x0923,0xef95},
	{0xf374,0x0928,0xef96},
	{0xf374,0x092e,0xef97},
	{0xf374,0x092f,0xef98},
	{0xf374,0x0932,0xef99},
	{0xf374,0x0935,0xef9a},

	/*0x0919 --- 0xf375*/
	{0xf375,0x0915,0xef78},
	{0xf375,0x0916,0xef79},
	{0xf375,0x0917,0xef7a},
	{0xf375,0x0918,0xef7b},
	{0xf375,0x092e,0xef7c},
	
	{0xf375, 0xef34, 0xef61}, /*15+30*/
	/*0x091f --- 0xf376*/
	{0xf376,0x091f,0xef7e},
	{0xf376,0x0920,0xef7f},
	{0xf376,0x0922,0xef80},
	
	{0xf376,0x0935,0xef82},
	/*0x0926 --- 0xf377*/
	{0xf377,0x0917,0xef8b},
	{0xf377,0x0918,0xef8c},
	{0xf377,0x0926,0xef8d},
	{0xf377,0x0927,0xef8e},
	{0xf377,0x0928,0xef8f},
	{0xf377,0x092c,0xef90},
	{0xf377,0x092d,0xef91},
	{0xf377,0x092e,0xef92},
	{0xf377,0x092f,0xef93},
	{0xf377,0x0935,0xef94},
	/*c+sub*/
	{0xf377,0xef37,0xef67},
	{0xf377,0xef44,0xef6a},
	{0xf377, 0xef4a,0xef6e}, 

};/*liga_table*/

/*
@except_liga_table
	It records the ligatures. They are not owning half from of first consonant. 
*/
static LIGA_ROW except_liga_table[]=
{
	/*0x0939*/
	{0,0,0}
};

static LIGA_TRI_ROW except_tri_liga_table[]=
{
	{0xf318,0xf342,0x0921,0xefac},
	{0xf31b,0xef12,0x092f,0xef60},
	{0xf32a,0xf333,0x092f,0xefdd},
	{0xf332,0xef12,0x092f,0xef72},
	{0xf337,0xf33c,0x0921,0xeff0},
	{0xf342,0xf333,0x092f,0xf200},
	{0xf374,0xf333,0x092f,0xef77},
	{0xf377,0xef12,0x092f,0xef6c},
};/*except_tri_liga_table*/

/*LIGA_HALF*/
static LIGA_ROW liga_half_table[] = {
	{0x0915,0x0937,0xf34a},
	{0x091c,0x091e,0xf34b},
	{0x0924,0x0924,0xf30c},
};

/*LIGA_LIGA_ROW*/ 
static LIGA_ROW liga_liga_table[]=
{
	/*0x0915---0xf318*/
	{0xf318,0xefff,0xef9c},
	{0xf318,0xf25a,0xefa2}, /*24+2f*/ /*0xf25a*/
	{0xf318,0xf25d,0xefa5}, /*24+35*/ /*0xf25d*/
	{0xf318,0xf2cb,0xefa7}, /*35+2f*/ /*0xf2cb*/
	{0xf318,0xf2e3,0xefa8}, /*37+2e*/ /*0xf2e3*/
	{0xf318,0xf2e5,0xefaa}, /*37+35*/ /*0xf2e5*/
	{0xf318,0xf2eb,0xefab}, /*38+1f*/ /*0xf2eb*/
	/*---*//*{0xf318,,0xefac},*/ /*38+21*/
	{0xf318,0xf2ec,0xefad}, /*38+24*/ /*0xf2ec*/
	{0xf318,0xf2f4,0xefa9}, /*37+2f*/ /*0xf2f4*/
	/*0x0917 --- 0xf31b*/
	{0xf31b,0xf264,0xefae}, /*27+2f*/ /*0xf264*/
	{0xf31b,0xf265,0xefaf}, /*27+35*/ /*0xf265*/
	{0xf31b,0xf274,0xefb0}, /*28+2f*/ /*0xf274*/
	{0xf31b,0xf29d,0xefb1}, /*2d+2f*/ /* 0xf29d*/
	/*0x091a --- 0xf31d*/
	{0xf31d,0xf228,0xefb3}, /*1b+35*/ /*0xf228*/
	/*0x091c --- 0xf320*/
	{0xf320,0xef5f,0xefb4}, /*1c+1e*/ /*0xef5f*/
	{0xf320,0xf23f,0xefb5}, /*1c+2f*/ /*0xf23f*/
	{0xf320,0xf240,0xefb6}, /*1c+35*/ /*0xf240*/
	/*---*//*{0xf320,,0xefb7},*/ /*1e+2f*/
	/*0x091e --- 0xf324*/
	{0xf324,0xf232,0xefb8}, /*1a+2f*/ /*0xf232*/
	{0xf324,0xf23f,0xefb9}, /*1c+2f*/
	/*0x0924 --- 0xf326*/
	{0xf326,0xef5e,0xefbe}, /*15+37*/ /*0xef5e*/
	{0xf326,0xf20e,0xefba}, /*15+2f*/ /*0xf20e*/
	{0xf326,0xf211,0xefbd}, /*15+35*/ /*0xf211*/
	{0xf326,0xf216,0xefbf}, /*16+28*/ /*0xf216*/
	{0xf326,0xf25a,0xefc1}, /*24+2f*/
	{0xf326,0xf25d,0xefc2}, /*24+35*/
	{0xf326,0xf274,0xefc3}, /*28+2f*/
	{0xf326,0xf27f,0xefc5}, /*2a+32*/ /*0xf27f*/
	{0xf326,0xf2aa,0xefc7}, /*2e+2f*/ /* 0xf2aa*/
	/*---*//*{0xf326,, 0xefc8},*/ /*30+2f*/
	{0xf326,0xf2ef,0xefca}, /*38+28*/ /*0xf2ef*/
	{0xf326,0xf2f4,0xefcb}, /*38+2f*/ /*0xf2f4*/
	{0xf326,0xf2f7,0xefcc}, /*38+35*/ /*0xf2f7*/

	{0xf329, 0xf274, 0xef6f},
	
	/*0x0928 --- 0xf32a*/
	{0xf32a,0xf213,0xefcd}, /*15+38*/ /*0xf213*/
	{0xf32a,0xf25a,0xefcf}, /*24+2f*/ 
	{0xf32a,0xf25e,0xefd2}, /*24+38*/ /*0xf25e*/
	{0xf32a,0xf25f,0xefd3}, /*25+2f*/ /*0xf25f*/
	{0xf32a,0xf260,0xefd4}, /*25+35*/ /*0xf260*/

	{0xf32a, 0xf274, 0xef70},

	{0xf32a,0xef94,0xefd6}, /*26+35*/ /***0xef94*/
	{0xf32a,0xf264,0xefd7}, /*27+2f*/
	{0xf32a,0xf265,0xefd9}, /*27+35*/ /*0xf265*/
	{0xf32a,0xf29d,0xefdb}, /*2d+2f*/
	{0xf32a,0xf2ad,0xefdc}, /*2e+35*/ /*0xf2ad*/
	{0xf32a,0xf2aa,0xefdd}, /*2e+2f*/
	{0xf32a,0xf2eb,0xefde}, /*38+1f*/
	{0xf32a,0xf2f4,0xefdf}, /*38+2f*/
	{0xf32a,0xef98,0xefe0}, /*39+2f*/ /****0xef98*/

	/*0x092a --- 0xf32d*/
	{0xf32d,0xf25a,0xefe1}, /*24+2f*/

	/*0x092c --- 0xf330*/
	{0xf330,0xf23f,0xefe2}, /*1c+2f*/
	{0xf330,0xf265,0xefe3}, /*27+35*/
	{0xf330,0xf2c3,0xefe5}, /*32+2f*/

	/*0x092e --- 0xf333*/
	{0xf333,0xf296,0xefe7}, /*2c+2f*/ /*0xf296*/ 
	{0xf333,0xf29d,0xefe9}, /*2d+2f*/ 
	{0xf333,0xf281,0xefeb}, /*2d+35*/ /* 0xf281*/

	/*0x0932 --- 0xf337*/
	{0xf337,0xf20e,0xefec}, /*15+2f*/
	{0xf337,0xf25f,0xefed}, /*25+2f*/
	{0xf337,0xf2c3,0xefef}, /*32+2f*/ /*0xf2c3*/
	/*---*//*{0xf337,,0xeff0},*/ /*35+21*/
	{0xf337,0xef98,0xeff1}, /*39+2f*/ /****0xef98*/

	/*0x0937 --- 0xf340*/	
	{0xf340,0xef82,0xef75},

	

	{0xf340,0xf250,0xeff3},/*23+2f*/ /*0xf250*/
	{0xf340,0xf2aa,0xeff5},/*2e+2f*/

	/*0x0938 --- 0xf342*/
	{0xf342, 0xf211, 0xeff8},/*15+35*/
	{0xf342, 0xf25a, 0xeff9},/*24+2f*/
	{0xf342, 0xf25d, 0xeffc},/*24+35*/
	{0xf342, 0xf25f, 0xeffd},/*25+2f*/



	/*0x0919 --- 0xf375*/
	{0xf375, 0xef5e, 0xef62}, /*15+37*/

	/*0x0926 --- 0xf377*/
	
	{0xf377, 0xef93, 0xef68}, /*26+2f*/
	{0xf377, 0xf264, 0xef69}, /*27+2f*/
	{0xf377, 0xf29d, 0xef6b},
	{0xf377, 0xf2cb, 0xef6d},
	
};/*liga_liga_table*/

/* ligature of consonant+dependent_vowel*/
static LIGA_ROW liga_dependent[] =
{
	{0x0926, 0x0943,0xf311},
	{0x0930, 0x0941,0xf312}, 
	{0x0930, 0x0942,0xf313},
	{0x0936, 0x0943,0xf314},
	{0x0939, 0x0943,0xf315}
};

/*
	@half_chains.
	It is a chain, must take care the order of substituting.
	ex1: SHRA+Hanlant
*/
static LIGA_ROW half_chains[] =
{
	{0xf32a,0xf332,0xf30d},
	{0xf32a,0xf342,0xf30e},
	{0xf333,0xf332,0xf30f},
	{0xf337,0xf332,0xf310},
	{0xf34a,0xf333,0xf30b},
};

static LIGA_ROW half_sub_chains[] =
{
	{0xf31b,0x0930,0xf371},
	{0xf332,0x0930,0xf373},
	{0xf377,0x0930,0xf372},
};

/*
This table nukta_liga_table is only per-liga of nukta_liga_liga_table,
*/
static LIGA_ROW ya_liga_table[]=
{
	/*0x091b --- 0xf31f*/
	{0xf31f,0x092f,0xf233},
	/*0x0920 --- 0xf34d*/
	{0xf34d,0x092f,0xef84},
	/*0x0921 --- 0xf34e*/	
	{0xf34e,0x092f,0xef88},
	/*0x0922 --- 0xf34f*/
	{0xf34f,0x092f,0xef8a},
	{0xf375,0x092f,0xef7d},
	{0xf376,0x092f,0xef81},
};

static LIGA_ROW ya_liga_liga_table[]=
{
	/*0x0937 --- 0xf340*/	
	{0xf340,0xef81,0xef74},
	{0xf340,0xef84,0xef76},	
	/*0x0920 --- 0xf34d*/
	{0xf34d, 0xef84,0xef64},
	/*0x0921 --- 0xf34e*/
	{0xf34e, 0xef88,0xef65},
	/*0x0922 --- 0xf34f*/
	{0xf34f, 0xef8a,0xef66},
	/*0x091f --- 0xf376*/
	{0xf376, 0xef81, 0xef63}, /*1f+2f*/
};

static LIGA_ROW artistic_sub_dependent[] =
{
	{0xef12, 0x0941, 0xef32},
	{0xef12, 0x0942, 0xef33},

};
/*
	@replace dependent pervowel for artistic.
	ex:0x0916+0x093f =>0x0916+ a glypf is a tranformed shape as ox093f. 
*/
static HALF_ROW artistic_dependent_pervowel[] =
{
	{0x0915,0xf397},
	{0x0915,0xf396},
};

static LIGA_ROW artistic_dependent_vowel[] =
{
	{0x0915, 0x0940,0xf3a9},
	{0x0915, 0xef22,0xf3ac},
	{0x0915, 0xef25,0xf3af},
	
	{0x0916, 0x0940,0xf3aa},
	{0x0916, 0xef22,0xf3ad},
	{0x0916, 0xef25,0xf3b0},
	
	{0x0917, 0x0940,0xf3ab},
	{0x0917, 0xef22,0xf3ae},
	{0x0917, 0xef25,0xf3b1},
};

/*
artistic_expect_complex, it is reverted table, the first is consonant.
*/
static COMPLEX_LIGA artistic_expect_complex[]=
{
	0xef9b,2,0xf2aa,0xf34a,
	0xef9d,3,0xf27f,0xf342,0xf318,
	0xefa0,2,0xf2aa,0xf30e,
	0x00,0x00,
};

#define LOOKUP_REPH_SUB(x)  lookup_consonants_table(x, reph_sub_table, TABLE_SIZE(reph_sub_table))
#define LOOKUP_HALF(x)      lookup_consonants_table(x, half_table, TABLE_SIZE(half_table))
#define LOOKUP_HALF_SUB(x)  lookup_consonants_table(x, half_sub_table, TABLE_SIZE(half_sub_table))
#define LOOKUP_NUKTA(x)  lookup_consonants_table(x, nukta_table, TABLE_SIZE(nukta_table))
#define LOOKUP_NUKTA_SUB(x)  lookup_consonants_table(x, nukta_reph_sub_table, TABLE_SIZE(nukta_reph_sub_table))
#define LOOKUP_NUKTA_HALF(x)  lookup_consonants_table(x, half_nukta_table, TABLE_SIZE(half_nukta_table))
#define LOOKUP_SIGN(x) lookup_consonants_table(x, signs_table, TABLE_SIZE(signs_table))
//
#define LOOKUP_LIGATURE(x,y) lookup_liga_table(x, y, liga_table, TABLE_SIZE(liga_table))
#define LOOKUP_LIGATURE_LIGATURE(x,y) lookup_liga_table(x, y, liga_liga_table, TABLE_SIZE(liga_liga_table))
#define LOOKUP_LIGATURE_HALF(x,y) lookup_liga_table(x, y, liga_half_table, TABLE_SIZE(liga_half_table) )
#define LOOKUP_LIGATURE_DEPENDENT(x,y) lookup_liga_table(x, y, liga_dependent, TABLE_SIZE(liga_dependent) )
#define LOOKUP_HALF_CHAINS(x,y) lookup_liga_table(x, y, half_chains, TABLE_SIZE(half_chains) )
#define LOOKUP_HALF_SUB_CHAINS(x,y) lookup_liga_table(x, y, half_sub_chains, TABLE_SIZE(half_sub_chains) )
#define LOOKUP_EXCEPT_LIGA(x,y) lookup_liga_table(x, y, except_liga_table, TABLE_SIZE(except_liga_table) ) 
#define LOOKUP_EXCEPT_TRI_LIGA(x,y,z) lookup_tri_liga_table(x,y,z,except_tri_liga_table, TABLE_SIZE(except_tri_liga_table) )

#define LOOKUP_YA_LIGATURE(x,y) lookup_liga_table(x, y, ya_liga_table, TABLE_SIZE(ya_liga_table) )
#define LOOKUP_YA_LIGATURE_LIGATURE(x,y) lookup_liga_table(x, y, ya_liga_liga_table, TABLE_SIZE(ya_liga_liga_table) )

#define LOOKUP_ARTISTIC_SUB_DEPENDENT(x,y) lookup_liga_table(x, y, artistic_sub_dependent, TABLE_SIZE(artistic_sub_dependent) )
#define LOOKUP_ARTISTIC_DEPENDENT_PREVOWEL(x) lookup_consonants_table(x, artistic_dependent_pervowel, TABLE_SIZE(artistic_dependent_pervowel) )
#define LOOKUP_ARTISTIC_DEPENDENT_VOWEL(x,y) lookup_liga_table(x, y, artistic_dependent_vowel, TABLE_SIZE(artistic_dependent_vowel) )
#define LOOKUP_ARTISTIC_COMPLEX_EX(pstr, n, pstr_end_idx)  lookup_complex_table_ex(pstr, n, artistic_expect_complex, TABLE_SIZE(artistic_expect_complex), pstr_end_idx)

UNI_CHAR  ExpectArtisticSub(UNI_CHAR *p, DT32_int len, DT32_int * pstr_end_idx)
{
	UNI_CHAR pp = LOOKUP_ARTISTIC_COMPLEX_EX(p, len, pstr_end_idx);
	return  pp;
}

static UNI_CHAR lookup_artistic_dependent_prevowel(ALL_TBL * p_all_table, UNI_CHAR x)
{
	if(p_all_table->p_gup_vowel_sub_table){

		return getSubVowel_st(p_all_table->p_gup_vowel_sub_table,0x093f, x);
	}
	else{
		return 0;
	}

}

static UNI_CHAR lookup_artistic_dependent_vowel(ALL_TBL * p_all_table, UNI_CHAR x,  UNI_CHAR y)
{
	if(p_all_table->p_gup_vowel_sub_table){

		return getSubVowel_st(p_all_table->p_gup_vowel_sub_table, y, x);
	}
	else{
		return 0;
	}
}

DT32_int indic_get_draw_syllable(pLayWrk pwrk, s_out_syllable * p_out_syllable,
						UNI_CHAR * p_heap_memory, 
						UNI_CHAR * _p_out, DT32_int * out_len, DT32_int * idx_c, DT32_int * f_special_part, ALL_TBL * p_all_table)
{
	DT32_int i;
	UNI_CHAR  *p, *p_out;
	DT32_int idx=0, idx_out =0;
	DT32_int idx_start, idx_end, idx_dependent=1;
	DT32_int state;
	CHAR_CLASS char_class;
	DT32_int idx_tmp;
	UNI_CHAR * p_unitxt = p_out_syllable->p_unitxt;
	DT32_int idx_lvl1_consonant=0 , idx_lvl1_prevowel= IDX_NONE,
		idx_lvl1_dependent_vowel= IDX_NONE, idx_lvl1_signs=IDX_NONE ;

	UNI_CHAR uni_ligature = DEVA_EMPTY, uni_first = DEVA_EMPTY;
	p= p_heap_memory ;
	p_out = _p_out;
	if(!HAS_LAST_CONSONANT(*p_out_syllable))
	{
		*idx_c = 0;
		/*copy to result.*/
		state = 0;
		if(p_out_syllable->length==1)
		{
			if(p_out_syllable->pre_special_part==0)
			{
				char_class = get_class(*p_unitxt);
				if(*p_unitxt == DEVA_PREVOWEL)
				{
					state = 2;
				}
				else
				if(
					 char_class == C_DEPENDENT_VOWEL
					||char_class == C_SIGN_STRESS
					|| char_class == C_SIGN_ACCENT
					|| char_class == C_SIGN_NESAL
					|| char_class == C_SIGN_VIRAMA
					|| char_class == C_SIGN_NUKTA
					)
				{
					*_p_out++ = DEVA_25CC_REPLACE;
					*_p_out++ = DEVA_25CC;
				
					state = 1;
				}
				else;
			}
		}
		else if(p_out_syllable->length==2 && (p_out_syllable->f_special_part&OUT_ZWJ))
		{
			    char_class = get_class(*p_unitxt);
				if(*p_unitxt == DEVA_PREVOWEL)
				{
					state = 3;
				}
				else
				if(
					 char_class == C_DEPENDENT_VOWEL
					||char_class == C_SIGN_STRESS
					|| char_class == C_SIGN_ACCENT
					|| char_class == C_SIGN_NESAL
					|| char_class == C_SIGN_VIRAMA
					|| char_class == C_SIGN_NUKTA
					)
				{
					*_p_out++ = DEVA_25CC_REPLACE;
					*_p_out++ = DEVA_25CC;
					state = 1;
				}
				else;
		}
		for(i=0; i<p_out_syllable->length; i++)
		{
			*(_p_out+i)=  *(p_out_syllable->p_unitxt+i);
		}
		if(state >0)
		{
			*out_len = p_out_syllable->length+1;
			//i = p_out_syllable->length;
			/*As it is DEVA_PREVOWEL*/
			if(state == 2)
			{
				*(_p_out+i) = DEVA_25CC;
			}
			else if(state ==3)
			{
				*(_p_out+i) = *(_p_out+i-1);
				*(_p_out+i-1) = DEVA_25CC;
			}else
			{
				(*out_len)++;
			}
		}
		else{
			*out_len = p_out_syllable->length;
		}
	}
	else
	{
		/*last-consonant.*/
		if(IS_REPH_SUB(*p_out_syllable))
		{
			if(IS_NUKTA(*p_out_syllable)){
				*(p+idx) = LOOKUP_NUKTA_SUB(*(p_unitxt+ p_out_syllable->idx_last_consonant));
			}
			else{
				*(p+idx) = LOOKUP_REPH_SUB( *(p_unitxt+ p_out_syllable->idx_last_consonant) );
			}

			if( *(p+idx) != DEVA_EMPTY){
				idx++;
				idx_lvl1_consonant = 0;
			}
			else{
					if(reph_sub!=0){
						*(p+idx++) = reph_sub;
						idx_lvl1_consonant = 1;
					}
					else{
						*(p+idx++) = DEVA_REPH ;
						*(p+idx++) = DEVA_VIRAMA ;
						idx_lvl1_consonant = 2;
					}
					if(IS_NUKTA(*p_out_syllable)){
						  *(p+idx) = DEVA_EMPTY; /*0921+093c+094d+0930 will be combined by position table.*/
						  //*(p+idx) = LOOKUP_NUKTA(*(p_unitxt+ p_out_syllable->idx_last_consonant));
						 if( *(p+idx) == DEVA_EMPTY){
							*(p+idx++) = DEVA_NUKTA;
							*(p+idx++) = *(p_unitxt+ p_out_syllable->idx_last_consonant);
							idx_lvl1_consonant++;
						 }
						 else{
							 idx++;
						 }
					}else
					{
						*(p+idx++) = *(p_unitxt+ p_out_syllable->idx_last_consonant);
					}
			}
		}
		else{
			idx_lvl1_consonant = 0; 
			if(IS_NUKTA(*p_out_syllable)){
				 *(p+idx) = LOOKUP_NUKTA(*(p_unitxt+ p_out_syllable->idx_last_consonant));
				 if( *(p+idx) == DEVA_EMPTY)
				 {
					*(p+idx++) = DEVA_NUKTA;
					*(p+idx++) = *(p_unitxt+ p_out_syllable->idx_last_consonant);
					idx_lvl1_consonant++;
				 }
				 else{
					idx++;
				 }
			}
			else{
				*(p+idx++) = *(p_unitxt+ p_out_syllable->idx_last_consonant);
			}
		}

		/*half-sub-form.*/
		if(HAS_HALF_REPH_SUB(*p_out_syllable)){
			*(p+idx) = LOOKUP_HALF_SUB( *(p_unitxt+p_out_syllable->idx_half_reph_sub) );
			if( *(p+idx) != DEVA_EMPTY){
				idx++;
			}
			else{
				/*There is not half_sub table and 
				next step do checking half-form table.*/
				p_out_syllable->idx_end+=4;
			}
		
		}
		else;	
	
		/*half-form and half-ligature.*/
		idx_start = idx;
		for(uni_first=DEVA_EMPTY, state = STA_START, i= p_out_syllable->idx_end;
				i >= p_out_syllable->idx_begin; i--)
		{

			if(STA_START == state)
			{
				if( DEVA_VIRAMA == *(p_unitxt+i)){
					state = STA_VIRAMA;
				}
				else{
					*(p+idx++) = *(p_unitxt+i);
				}
			}
			else if(STA_VIRAMA == state)
			{
				if(DEVA_NUKTA == *(p_unitxt+i)){
					state = STA_NUKTA;	
				}
				else{
						if(uni_first != DEVA_EMPTY 
							&& (*(p+idx) = LOOKUP_LIGATURE_HALF(*(p_unitxt+i), uni_first)) 
									!= DEVA_EMPTY )
						{
							if( *(p+idx-1) == uni_first){
								*(p+idx-2)= *(p+idx);
								idx--;
							}
							else{
								*(p+idx-1)= *(p+idx);
							}
							uni_first = DEVA_EMPTY;
						}
						else
						{
							*(p+idx) = LOOKUP_HALF( *(p_unitxt+i) );
							if( *(p+idx) != DEVA_EMPTY){
								idx++;
							}
							else{
								 *(p+idx++) = DEVA_VIRAMA;
								 *(p+idx++) = *(p_unitxt+i); 
							}
							uni_first = *(p_unitxt+i);
						}
						state = STA_START;
				}
			}
			else if(STA_NUKTA == state)
			{
				*(p+idx) = LOOKUP_NUKTA_HALF(*(p_unitxt+i));
				if( *(p+idx) != DEVA_EMPTY){
						idx++;
				}
				else{
					 *(p+idx) = LOOKUP_HALF( *(p_unitxt+i) );
					 if( *(p+idx) != DEVA_EMPTY){

						*(p+idx+1) = *(p+idx);
						*(p+idx) = DEVA_NUKTA;
						idx+=2;
					 }
					 else{	
						 *(p+idx++) = DEVA_VIRAMA;
						 *(p+idx++) = DEVA_NUKTA;
						 *(p+idx++) = *(p_unitxt+i); 
					 }
				}
				state = STA_START;
				uni_first = DEVA_EMPTY;
			}else
				;
		}
		idx_end = idx;

		/*NUKTA*/
	
		/*Ligutures substitution. 
		when it had done substition,set other bytes to 0x0.*/
		//if( (!IS_NUKTA (*p_out_syllable)) && (idx - idx_lvl1_consonant) >=2 )
		state = 0; //now , nukta_ligature is enable or not;
		if( (idx - idx_lvl1_consonant) >=2 )
		{
			uni_ligature = LOOKUP_LIGATURE(*(p+idx_lvl1_consonant+1),
				*(p+idx_lvl1_consonant));

			if( uni_ligature == DEVA_EMPTY && !IS_NUKTA (*p_out_syllable))
			{
					uni_ligature = LOOKUP_YA_LIGATURE(*(p+idx_lvl1_consonant+1),*(p+idx_lvl1_consonant));
					state = 1; /*ya_ligature is enable.*/
			}

			/*for pos table for nukta and ya(0x092f)*/	
			if( (*(p+idx_lvl1_consonant+1)== DEVA_NUKTA) && ( (*(p+idx_lvl1_consonant)== 0x092f) ) )
			{
				uni_ligature = LOOKUP_YA_LIGATURE(*(p+idx_lvl1_consonant+2),*(p+idx_lvl1_consonant));
				if(uni_ligature != DEVA_EMPTY)
				{
					*(p+idx_lvl1_consonant) = DEVA_EMPTY;
					*(p+idx_lvl1_consonant+2) = uni_ligature;
					/*consonant be mixed in ligature before reph_sub so modify idx_lvl1_consonant.*/
					idx_lvl1_consonant +=2;
					state = 2; /*ya_ligature is enable and move nukta pos. */
				}
			}

			if(uni_ligature == DEVA_EMPTY)
			{
				/*for pos table reorder reph_sub and ligature,ya(0x092f)*/ 
				if(*(p+idx_lvl1_consonant+1)== reph_sub && *(p+idx_lvl1_consonant) == 0x092f ) 
				{
					//sub table get privilage.
					uni_ligature = LOOKUP_EXCEPT_TRI_LIGA(*(p+idx_lvl1_consonant+2), *(p+idx_lvl1_consonant+1), *(p+idx_lvl1_consonant));
					if(uni_ligature != DEVA_EMPTY)
					{
						*(p+idx_lvl1_consonant) = uni_ligature;
						*(p+idx_lvl1_consonant+1) = DEVA_EMPTY;
						*(p+idx_lvl1_consonant+2) = DEVA_EMPTY;
					}
					else
					{
						/*This exchange position reph_sub*/
						uni_ligature = LOOKUP_LIGATURE(*(p+idx_lvl1_consonant+2),
							*(p+idx_lvl1_consonant));

						if( uni_ligature == DEVA_EMPTY && !IS_NUKTA (*p_out_syllable))
						{
							uni_ligature = LOOKUP_YA_LIGATURE(*(p+idx_lvl1_consonant+2),*(p+idx_lvl1_consonant));
						}
						if(uni_ligature != DEVA_EMPTY)
						{
							*(p+idx_lvl1_consonant) = DEVA_EMPTY;
							*(p+idx_lvl1_consonant+2) = uni_ligature;
							//consonant be mixed in ligature before reph_sub so modify idx_lvl1_consonant.
							idx_lvl1_consonant +=2;
						}
					}
				}

				if(uni_ligature == DEVA_EMPTY)
				{

					if((idx - idx_lvl1_consonant) >=3)
					{
						if( (*(p+idx_lvl1_consonant+1) == DEVA_VIRAMA))
						{
							uni_ligature = LOOKUP_EXCEPT_LIGA(*(p+idx_lvl1_consonant+2),*(p+idx_lvl1_consonant) );
							if(uni_ligature != DEVA_EMPTY)
							{
								*(p+idx_lvl1_consonant) = uni_ligature;
								*(p+idx_lvl1_consonant+1) = DEVA_EMPTY;
								*(p+idx_lvl1_consonant+2) = DEVA_EMPTY;
							}else;
						}
						else{
							uni_ligature = LOOKUP_EXCEPT_TRI_LIGA(*(p+idx_lvl1_consonant+2), *(p+idx_lvl1_consonant+1), *(p+idx_lvl1_consonant));
							if(uni_ligature != DEVA_EMPTY)
							{
								*(p+idx_lvl1_consonant) = uni_ligature;
								*(p+idx_lvl1_consonant+1) = DEVA_EMPTY;
								*(p+idx_lvl1_consonant+2) = DEVA_EMPTY;
							}else;
						};
					}else;
				}
			}
			else
			{
				if(state!=2)
				{
					*(p+idx_lvl1_consonant) = uni_ligature;
					*(p+idx_lvl1_consonant+1) = DEVA_EMPTY;
					if( (idx - idx_lvl1_consonant) >=3 )
					{
						if( state ==0)
						{
							uni_ligature = LOOKUP_LIGATURE_LIGATURE(*(p+idx_lvl1_consonant+2), 
															*(p+idx_lvl1_consonant));
						}
						else{ 
							/*ya_ligature is enable.*/
							uni_ligature = DEVA_EMPTY;
						}

						if( uni_ligature == DEVA_EMPTY && !IS_NUKTA (*p_out_syllable))
						{
							uni_ligature = LOOKUP_YA_LIGATURE_LIGATURE(*(p+idx_lvl1_consonant+2), 
															*(p+idx_lvl1_consonant));
						}
		
						if(uni_ligature == DEVA_EMPTY)
						;
						else{
								*(p+idx_lvl1_consonant) = uni_ligature;
								*(p+idx_lvl1_consonant+2) = DEVA_EMPTY;
						}
					}else;
				}
				else{
						/*for pos table for nukta and ya(0x092f)*/
						if( (idx - idx_lvl1_consonant) >=2 )
						{

							uni_ligature = LOOKUP_YA_LIGATURE_LIGATURE(*(p+idx_lvl1_consonant+1), 
													*(p+idx_lvl1_consonant));
						}
						
						if(uni_ligature == DEVA_EMPTY)
						;
						else{
								*(p+idx_lvl1_consonant) = uni_ligature;
								*(p+idx_lvl1_consonant+1) = DEVA_EMPTY;
						}
				}
			}
		}else;

		/* HALF_CHAINS */
		for(i= idx_end-1; i >= idx_start+1; i--)
		{
			uni_first = LOOKUP_HALF_CHAINS(*(p+i), *(p+i-1));
			if(uni_first != DEVA_EMPTY)
			{
				*(p+i) = DEVA_EMPTY;
				*(p+i-1) = uni_first;
			}
			else if( *(p+i-2)==DEVA_VIRAMA)
			{
				uni_first = LOOKUP_HALF_SUB_CHAINS(*(p+i), *(p+i-1));
				if(uni_first != DEVA_EMPTY)
				{
					*(p+i) = DEVA_EMPTY;
					*(p+i-1) = uni_first;
					*(p+i-2) = DEVA_EMPTY;
				}
			}
			else continue;
		}
		/**/
		uni_first = ExpectArtisticSub(p, idx_end, &idx_tmp);
		if(uni_first != DEVA_EMPTY)
		{
			*p = uni_first;
			for(i=1; i<=idx_tmp; i++)
			{
				*(p+i) = DEVA_EMPTY;
			}
		}
	
		/*reph_sup*/
		if(IS_REPH_SUP(*p_out_syllable) &&  reph_sup == 0x0)
		{
				*(p+idx++) = DEVA_VIRAMA;
				*(p+idx++) = DEVA_REPH;
		}else;
		

		idx_lvl1_signs = idx;
		
		/*-----------------------------------------------
		 Drawing signs order, 
		 1.)Dependent vowel signs
		 2.)Reph_sup signs
		 3.)Various signs one, 0x0901~0x0903
		 4.)Various signs two, 0x094d~0x0954
		*/
		
		/*
		 Find the virama from the idx_lvl1_consonant 
		 to decide where place prevowel 0x093f. 
		*/
		if(IS_PREVOWEL(*p_out_syllable))
		{
			for(i=idx_lvl1_consonant+1;	i<idx; i++)
			{
					if( *(p+i)== DEVA_VIRAMA){
						idx_lvl1_prevowel = i;
						break;
					}else continue;
			}
		}else;

		/*copy dependent vowels but prevowel 0x093f.*/
		if(HAS_DEPENDENT_VOWEL(*p_out_syllable))
		{
			uni_ligature = LOOKUP_LIGATURE_DEPENDENT(*(p+idx_lvl1_consonant),
				*(p_unitxt+p_out_syllable->idx_dependent_vowel));
			
			if(uni_ligature != DEVA_EMPTY)
			{
				*(p+idx_lvl1_consonant) = uni_ligature;
				*(p+idx++) = DEVA_EMPTY;
			}
			else
			{	
				idx_lvl1_dependent_vowel = idx;
				*(p+idx++) = *(p_unitxt+p_out_syllable->idx_dependent_vowel); 
			}
		}
		
		/**/
		uni_ligature=  SIGN_V(
			 		((idx_lvl1_dependent_vowel == IDX_NONE)? 0 :(*(p+idx_lvl1_dependent_vowel))),
					(!HAS_CANDRA_SIGNS(*p_out_syllable))? 0: ( *(p_unitxt+p_out_syllable->idx_candra_signs)),
					(IS_REPH_SUP(*p_out_syllable))?1:0 
					);

		uni_ligature = LOOKUP_SIGN(uni_ligature);

		if(uni_ligature != DEVA_EMPTY)
		{
			if(IS_PREVOWEL(*p_out_syllable))
				 *(p+idx-1) = DEVA_EMPTY;
			else 
				if(HAS_DEPENDENT_VOWEL(*p_out_syllable))
					 *(p+idx-1) = uni_ligature;
			else
					 *(p+idx++) = uni_ligature;
			
			/*Disable the ra +varima, because is mixed in signs substitution.*/ 
			if(IS_REPH_SUP(*p_out_syllable) &&  reph_sup == 0x0)
			{
				*(p+idx_lvl1_signs-1)= DEVA_EMPTY ;
				*(p+idx_lvl1_signs-2)= DEVA_EMPTY;
			}else;
		}
		else
		{	
			/*copy prevowel later.*/
			if(IS_PREVOWEL(*p_out_syllable))
				 *(p+idx-1) = DEVA_EMPTY;

			/*if exist reph_sup*/
			if(IS_REPH_SUP(*p_out_syllable) &&  reph_sup != 0x0)
			{
					*(p+idx++) = reph_sup;
			}else;

		}

		/*copy other various signs,but dependent vowels*/
		if(HAS_VARIOUS_SIGNS(*p_out_syllable))
		for(i=p_out_syllable->idx_signs; i<p_out_syllable->length; i++)
		{
			if (i == p_out_syllable->idx_dependent_vowel)
				continue;
			else if	((uni_ligature!=DEVA_EMPTY) && (i==p_out_syllable->idx_candra_signs))
				continue;
			else if(IS_PREDEPENDENT_NUKTA(*p_out_syllable) &&  *(p_unitxt+i) == DEVA_NUKTA)
				continue;
			else
				*(p+idx++) = *(p_unitxt+i);
		}
			
		/*-----------------------------------------------
		The second step, reorder the glyph for display. 
		*/
		/*
		To reverse main glyph to put array, 
		jump the value DEVA_EMPTY and insert pervowel to correct position.
		*/
		if(idx_lvl1_signs > 0)
		{
			if(IS_PREVOWEL(*p_out_syllable) && idx_lvl1_prevowel!= IDX_NONE)
			{/*insert pervowel*/
				for(i=idx_lvl1_signs-1; i>=idx_lvl1_prevowel; i--)
				{
					if(*(p+i)!=DEVA_EMPTY)
							*(p_out+idx_out++) = *(p+i);
				}
				
				if(uni_ligature != DEVA_EMPTY)
					*(p_out+idx_out++) = uni_ligature;
				else {
					idx_dependent = idx_out;
					*(p_out+idx_out++) = DEVA_PREVOWEL;
				}
				
				if( IS_PREDEPENDENT_NUKTA(*p_out_syllable))
							*(p_out+idx_out++) = DEVA_NUKTA; 
						else;

				for(i = idx_lvl1_prevowel-1; i>=0; i--)
				{
					if(*(p+i)!=DEVA_EMPTY)
						*(p_out+idx_out++) = *(p+i);
				}
			}
			else{
				if(IS_PREVOWEL(*p_out_syllable))
				{
					if(uni_ligature != DEVA_EMPTY){
						*(p_out+idx_out++) = uni_ligature;
					}
					else{
						idx_dependent = idx_out;
						*(p_out+idx_out++) = DEVA_PREVOWEL;
					}

					if( IS_PREDEPENDENT_NUKTA(*p_out_syllable))
						*(p_out+idx_out++) = DEVA_NUKTA; 
					else;
				}
				else;
				/*only do reverseing.*/
				for(i=idx_lvl1_signs-1; i>=0; i--)
				{
					if(*(p+i)!=DEVA_EMPTY)
					{
						*(p_out+idx_out++) = *(p+i);
					}else;
				}
				/*copy reserved*/
				/*for(i=idx_lvl1_signs-1; i>=0; i--)
				{
					if(*(p+i)!=DEVA_EMPTY)
					{
						*(p_out+idx_out++) = *(p+i);
					}else;
				}*/
			}
		}
		
		/*To do keep consonant idx is easy for us to position*/
		*idx_c = idx_out-1;
		if(*(p_out + *idx_c) == reph_sub || *(p_out + *idx_c) == DEVA_NUKTA)
		{
			(*idx_c)--;
			if(*idx_c >0 && *(p_out + *idx_c) == DEVA_NUKTA)
			{
				(*idx_c)--;
			}
		}

		/*To do get some value for position.*/
		GET_SECIAL_PART(*p_out_syllable, *f_special_part);


		/*copy signs to put array and 
		do sign substitutin to adjust sign glyphs.*/
		if(idx> idx_lvl1_signs)
		{	
			uni_first = LOOKUP_ARTISTIC_SUB_DEPENDENT(*(p_out+idx_out-1), *(p+idx_lvl1_signs));
			if(uni_first != DEVA_EMPTY)
			{
				*(p_out+idx_out-1) = uni_first;
				idx_lvl1_signs+=1;
			}
			if(idx> idx_lvl1_signs)
			{
				uni_first = *(p+idx_lvl1_signs);
				if(uni_first != DEVA_EMPTY)
				{
					idx_dependent = idx_out;
				}else;
				for(i=idx_lvl1_signs+1; i<idx; i++)
				{
					if(uni_first != DEVA_EMPTY)
					{
						*(p_out+idx_out++) = uni_first;
					}
					uni_first = *(p+i);
				}
				if(uni_first != DEVA_EMPTY)
					*(p_out+idx_out++) = uni_first;	
			}
		}

		/*dependent vowel artistic replace*/
		if(IS_PREVOWEL(*p_out_syllable))
		{
			if(idx_out> idx_dependent)
			{
				//uni_ligature = LOOKUP_ARTISTIC_DEPENDENT_PREVOWEL(p_out[idx_dependent+1]);
				uni_ligature = lookup_artistic_dependent_prevowel(p_all_table, p_out[idx_dependent+1]);
				if(uni_ligature != DEVA_EMPTY){
					p_out[idx_dependent] = uni_ligature;
				}
			}else;
		}

		else if(HAS_DEPENDENT_VOWEL(*p_out_syllable))
		{
			if(idx_dependent>0)
			{
				//uni_ligature = LOOKUP_ARTISTIC_DEPENDENT_VOWEL(p_out[idx_dependent-1], p_out[idx_dependent]);
				if( (0xef12==p_out[idx_dependent-1])|| (0x093c==p_out[idx_dependent-1]) )
				{
					uni_ligature = lookup_artistic_dependent_vowel(p_all_table, p_out[idx_dependent-2], p_out[idx_dependent]);
				}
				else{
					uni_ligature = lookup_artistic_dependent_vowel(p_all_table, p_out[idx_dependent-1], p_out[idx_dependent]);
				}
				if(uni_ligature != DEVA_EMPTY){
					p_out[idx_dependent] = uni_ligature;
				}
				if(p_out[idx_dependent]==0x0940)
					p_out[idx_dependent] = 0xF3a9;
				if(p_out[idx_dependent]==0xef22)
					p_out[idx_dependent] = 0xF3ac;
				if(p_out[idx_dependent]==0x0ef25)
					p_out[idx_dependent] = 0xF3af;
			}
		}
		*out_len = idx_out;
	}
	return 0;
}


DT_void assign_test_syllable(s_out_syllable * pout_syllable, DT32_int *psyllable_end, UNI_CHAR * p)
{
	if(p[1]==0x093f)
	{
		pout_syllable->f_special_part =4;
		pout_syllable->idx_last_consonant =0;
		pout_syllable->idx_begin =0;
		pout_syllable->idx_end = -1;
		pout_syllable->idx_half_reph_sub = -1;
		pout_syllable->idx_signs =1;
		pout_syllable->idx_candra_signs = -1;
		pout_syllable->idx_dependent_vowel = 1;
		pout_syllable->length = 2;
		*psyllable_end = 2;

	}else 
	if(p[1]==0x0940){
		pout_syllable->f_special_part =0;
		pout_syllable->idx_last_consonant =0;
		pout_syllable->idx_begin =0;
		pout_syllable->idx_end = -1;
		pout_syllable->idx_half_reph_sub = -1;
		pout_syllable->idx_signs =1;
		pout_syllable->idx_candra_signs = -1;
		pout_syllable->idx_dependent_vowel = 1;
		pout_syllable->length = 2;
		*psyllable_end = 2;
	}else
	if(p[0]== 0x0930 && p[1]==0x094d && p[3]==0x0940)
	{
		if(p[4]==0x0902)
		{
			pout_syllable->f_special_part =1;
			pout_syllable->idx_last_consonant =2;
			pout_syllable->idx_begin =2;
			pout_syllable->idx_end = 1;
			pout_syllable->idx_half_reph_sub = -1;
			pout_syllable->idx_signs = 3;
			pout_syllable->idx_candra_signs = 4;
			pout_syllable->idx_dependent_vowel = 3;
			pout_syllable->length = 5;
			*psyllable_end = 5;
		}else
		{
			pout_syllable->f_special_part =1;
			pout_syllable->idx_last_consonant =2;
			pout_syllable->idx_begin =2;
			pout_syllable->idx_end = 1;
			pout_syllable->idx_half_reph_sub = -1;
			pout_syllable->idx_signs = 3;
			pout_syllable->idx_candra_signs = -1;
			pout_syllable->idx_dependent_vowel = 3;
			pout_syllable->length = 4;
			*psyllable_end = 4;
		}
	}


/*
	    2.0x0915+0x0940
	        3.0x0930+0x094d+0x0915+0x0940
	        4.0x0930+0x094d+0x0915+0x0940+0x0902*/
}

/*
	@
*/
DT32_int deva_render(pLayWrk pwrk, UNI_CHAR* p_unitxt, DT32_int len, UNI_CHAR* p_heap_memory, 
				 UNI_CHAR* p_out , DT16_ushort * out_len , GlyphSeq * p_trace, 
				 DT16_ushort * count_syllable, ALL_TBL * p_all_table)
{
	DT32_int i;
	UNI_CHAR * p;
	DT32_int string_len;
	DT32_int syllable_end,syllable_end_tmp;
	DT_BOOL is_loop;
	DT32_int idx_begin, idx_end, idx_last_consonant;
	DT32_int out_length =0;		
	DT32_int idx_c, f_special_part =0;
	DT16_ushort	out_offset =0, out_count_sylable=0;
	DT32_int state;
	s_out_syllable out_syllable;
	DT32_int pre_special_part=0;
    CHAR_CLASS char_class;
	/*
	*/
	syllable_end =0;
	syllable_end_tmp =0;
	p = p_unitxt;
	string_len = len;
	while(string_len >0)
	{
		indic_init_out_syllable(&out_syllable, p);
		is_loop = indic_get_syllable(p, string_len, &syllable_end);

		SET_LENGTH(out_syllable, syllable_end);
	
		/*TO DO : look up the tree table, and substitue 
		ligature, half form for native */
		idx_begin = 0;
		idx_end = syllable_end-1; 
		idx_last_consonant = IDX_NONE;
		syllable_end_tmp = syllable_end;


		/*Find Reph_sup*/
		if(idx_end-idx_begin>=2	
			&&  ((*p)==DEVA_REPH) && (*(p+1)== DEVA_VIRAMA) )
		{
			SET_REPH_SUP_TRUE(out_syllable);
			idx_begin += 2;
		}

		if(*(p+idx_end) == ZWNJ)
		{
				SET_ZWNJ_TRUE(out_syllable);
				syllable_end_tmp--;
				idx_end--;
		}
		
		/*Filter dependent vowel and stress sign.
		to find the prevowel.*/
		for(i=0, state = STA_START; i<syllable_end_tmp; i++)
		{
			char_class = get_class(*(p+idx_end));

			if(char_class == C_DEPENDENT_VOWEL
			    || char_class == C_SIGN_STRESS
				|| char_class == C_SIGN_ACCENT
				|| char_class == C_SIGN_NESAL
				|| char_class == C_SIGN_VIRAMA
				|| char_class == C_SIGN_NUKTA)
			{
				/*Find the dependent's NUKTA*/
				if(*(p+idx_end) == DEVA_NUKTA) 	
				{
					state = STA_NUKTA;	
				}
				else if(char_class == C_DEPENDENT_VOWEL)
				{
					SET_IDX_DEPENDENT_VOWEL(out_syllable, idx_end);

					/*Find previous dependent vowel 0x093f*/
					if(*(p+idx_end) == DEVA_PREVOWEL) {
						SET_PREVOWEL_TRUE(out_syllable);
						if(STA_NUKTA == state){
							SET_PREDEPENDENT_NUKTA_TRUE(out_syllable);
						}else;
					}
					else
						state = STA_START;
					
				}
				else if(char_class == C_SIGN_NESAL)
				{
					SET_IDX_CANDRA_SIGNS(out_syllable, idx_end);
					state = STA_START;

				}else;

				idx_end--;
			}
			else
				break;
		}

		if(i>0){
			if(*(p+idx_end+1) ==  DEVA_NUKTA)
			{
				SET_IDX_SIGNS(out_syllable, idx_end+2);
				idx_end++;
			}
			else
				SET_IDX_SIGNS(out_syllable, idx_end+1);
		}

		/*Find Reph_sub*/
		if(idx_end-idx_begin >=2
			&& (*(p+idx_end-1) == DEVA_VIRAMA
			&& (*(p+idx_end) == DEVA_REPH)) ) 
		{
			SET_REPH_SUB_TRUE(out_syllable);
			idx_end-=2;
		}

		if(idx_end>0 && *(p+idx_end) == ZWJ)
		{
			idx_last_consonant = idx_end;
			SET_ZWJ_TRUE(out_syllable);

			/*when it is 0x0930,0x094d,0x200d,
			don't expect pervious result,so fixed it.*/
			if(idx_last_consonant == 2 && IS_REPH_SUP(out_syllable))
			{
				idx_begin =0;
				SET_REPH_SUP_FALSE(out_syllable);
			}
			if(syllable_end==2)
			{	/*This is only one character expect zwj.*/
				idx_last_consonant = IDX_NONE;
			}
		}
		else
		{
			/*Find lastest consonant or consonant_nukta*/	
			for(i=0; i<= idx_end-idx_begin; i++)
			{
				char_class = get_class(*(p+idx_end-i));
				if(C_CONSONANT == char_class 
				   || C_CONSONANT_NUKTA == char_class)
				{
					idx_last_consonant = idx_end-i;
					break;
				}
			}

			if(i>0 && (DEVA_NUKTA== *(p+idx_last_consonant+1)))
			{
				SET_NUKTA_TRUE(out_syllable);	  
			}
		}
		SET_IDX_LAST_CONSONANT(out_syllable, idx_last_consonant);
		idx_end = idx_last_consonant-1;

		/*It don't find consonant*/
		if(HAS_LAST_CONSONANT(out_syllable))
		{
			
			/*Half_form reph get privilege,
			Ex:0x0915,0x094d,0x0930,0x094d,0x0930.*/
			if(IS_REPH_SUB(out_syllable) && idx_last_consonant >=2 
				&&  (*(p+idx_last_consonant)== DEVA_REPH)
				&&  (*(p+idx_last_consonant-1)== DEVA_VIRAMA)
				&&  (*(p+idx_last_consonant-2)!= DEVA_REPH) )
			{
				SET_REPH_SUB_FALSE(out_syllable);
				idx_last_consonant+=2;
				idx_end+=2;
				SET_IDX_LAST_CONSONANT(out_syllable, idx_last_consonant);
			}
						
			/*check half reph sub.*/
			if( (idx_last_consonant-idx_begin >= 4) 
				&& (*(p+idx_last_consonant-1) == DEVA_VIRAMA )
				&& (*(p+idx_last_consonant-2) == DEVA_REPH ) 
				&& (*(p+idx_last_consonant-3) == DEVA_VIRAMA) )
			{
				SET_IDX_HALF_REPH_SUB(out_syllable, idx_last_consonant-4);
				idx_end-=4;
			}		

			SET_IDX_BEGIN(out_syllable, idx_begin);
			SET_IDX_END(out_syllable, idx_end);//the value is before the consonant  for replacement.
		}
		else;

#ifdef TABLE_FROM_USERDATA
if(p_all_table->process_switch & ENABLE_COPY_SUB)
{
	assign_test_syllable(&out_syllable, &syllable_end, p);
}else
if(p_all_table->process_switch & ENABLE_COPY_SUB_FOR_POS)
{
	assign_test_syllable(&out_syllable, &syllable_end, p);
	out_syllable.length = 3;
	syllable_end = 3;
}
#endif
			out_syllable.pre_special_part = pre_special_part;
			/*out corrent glyph to draw.*/
			indic_get_draw_syllable(pwrk, &out_syllable, p_heap_memory+out_offset,
				p_out+out_offset, &out_length, &idx_c, &f_special_part, p_all_table);

			pre_special_part = out_syllable.f_special_part;
			/*record syllable data*/	
			p_trace[out_count_sylable].n_per_glyf1 = syllable_end;
			p_trace[out_count_sylable].n_per_glyf2 = out_length;
			p_trace[out_count_sylable].idx_gseq2 = idx_c;
			p_trace[out_count_sylable].idx_gseq1 = (DT16_ushort)(f_special_part & 0xFFFFU);
		
			/*initialize next loop*/
			out_offset += (DT16_ushort)out_length;
			p += syllable_end;
			string_len -=syllable_end;
			out_count_sylable++;
	}

	*out_len = out_offset;
	*count_syllable = out_count_sylable;
	return 0;
}
