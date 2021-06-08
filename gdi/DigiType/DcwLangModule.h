#ifndef __DCWLANGMODULE_H
#define __DCWLANGMODULE_H


/* Font Render Engine */
/* You can enable only one render engine  in every build. */

#define DIGITYPE_STD
 #ifdef DIGITYPE_STD				/* Modified by Jacky_20090910 for DcwRaster-V1.10				*/
  #include "Digitype_std.h"
 #endif

#include <model_config.h>

#if KCSPEC_OPENVG == 1 || KCSPEC_MAP_VIEW == 1
 #define DIGITYPE_OUL
 #include "Digitype_oul.h"
#endif

#define BDF_RASTER
 #ifdef BDF_RASTER
  #include "BDF_Raster.h"
 #endif

#define DIF_RASTER
 #ifdef DIF_RASTER
  #include "DIF_Raster.h"
 #endif

#define INDICS_TABLE_TEST /*load indics_table from file to go test*/

/* Font Language Module */
#define LATIN_latin		/* Please don't disable this one. */
#define ARABIC_arabic
#define THAI_thai
#define INDICS_devanagari

/*#define INDICS_tamil*/
#define HEBREW_hebrew
#define LATIN_vietnamese

 #ifdef LATIN_latin
  #include "DcwLatin.h"
 #endif

 #ifdef ARABIC_arabic
  #include "DcwArabic.h"
 #endif

 #ifdef THAI_thai
  #include "DcwThai.h"
 #endif

 #ifdef INDICS_devanagari
  #include "DcwDevanagari.h"
 #endif

/* #ifdef INDICS_tamil
  #include "DcwTamil.h" 	
 #endif
*/
 #ifdef HEBREW_hebrew
  #include "DcwHebrew.h"
 #endif


#ifdef LATIN_vietnamese
  #include "DcwVietnamese.h"
#endif

#endif
