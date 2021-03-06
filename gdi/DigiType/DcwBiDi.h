// File: Bidi.h
//
/*	For use with Bidi Reference Implementation
	For more information see the associated file bidi.cpp

	Credits:
	-------
	Written by: Asmus Freytag
	Command line interface by: Rick McGowan
	Verification (v24): Doug Felt

	Disclaimer and legal rights:
	---------------------------
	Copyright (C) 1999-2009, ASMUS, Inc. All Rights Reserved.
	Distributed under the Terms of Use in http://www.unicode.org/copyright.html.

	THIS SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
	OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT OF THIRD PARTY RIGHTS.
	IN NO EVENT SHALL THE COPYRIGHT HOLDER OR HOLDERS INCLUDED IN THIS NOTICE
	BE LIABLE FOR ANY CLAIM, OR ANY SPECIAL INDIRECT OR CONSEQUENTIAL DAMAGES,
	OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS,
	WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION,
	ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THE SOFTWARE.

	 The files bidi.rc, and resource.h are distributed together with this file and are included 
	 in the above definition of software.
*/
// Copyright (C) 1999-2009, ASMUS, Inc.     All Rights Reserved

#ifndef __DCWBIDI_H
#define __DCWBIDI_H

#include "DcwLayout.h"

//#define WINDOWS_UI 0
//#if WINDOWS_UI
//	// disable some warnings generated by windows.h
//	#pragma warning (disable : 4514 4201)
//#endif
//#if WINDOWS_UI > 1
//   #include "main.h"		// private header, includes Windows.h
//   #include "window.h"		// center
//   #define DEMO 1			// force demo mode
//   #ifdef DEBUG_ENABLED
//	   #define DEBUGGING 1	// conditionally enable debug support 
//	   #define ASSERT_ENABLED 1
//   #else 
//	   #define ASSERT_ENABLED 0
//   #endif					// for private build
//#elif WINDOWS_UI
//	#define ASSERT(x)		// suppress ASSERTs for standalone
//	#define ASSERT_ENABLED 0
//	#include "windows.h"	// standard include file for windows
//	#include "windowsx.h"	// extended include file for windows
//	#include "resource.h"	// resource defines
// #else
//	// commandline version, define printf based ASSERT
//	#pragma message("commandline version")
//	#include <stdio.h>
//	#define ASSERT(x) if (!(x)) fprintf(stdout, "assert failed: %s\n", #x); else ;
//	#define ASSERT_ENABLED 1
//#endif
//// duplicate some windows.h defines for commandline
//#ifndef TEXT
//#define TCHAR  char
//#define LPTSTR char *
//#define bool   int
//#define true   1
//#define false  0
//#endif
//#if WINDOWS_UI==1
//LRESULT CALLBACK BidiWndProc(HWND hwndDlg, UINT message, WPARAM wParam, LPARAM lParam);
//#endif
//#ifdef _MAIN_H_
//BOOL CALLBACK BidiDlgProc(HWND hwndDlg, UINT message, WPARAM wParam, LPARAM lParam);
//#endif
//// For convenience of external callers, the following constitute the interface to the actual algorithm. 
//// For usage notes and paramter descriptions see the file bidi.cpp
////void BidiLines(int baselevel, TCHAR * pszLine, int * pclsLine,
////			   int * plevelLine, int cchPara, int fMirror, bool * pbrk = 0);
////int BidiParagraph(int &baselevel,  int * types, int * levels, int cch);

#define chLRM 0x200E
#define chRLM 0x200F

#define chLS  0x2028
#define chPS  0x2029
#define chLRE 0x202A
#define chRLE 0x202B
#define chPDF 0x202C
#define chLRO 0x202D
#define chRLO 0x202E
//#define chBN  '~'

#define DLO_BIDI_MAX_NSM	8


/*------------------------------------------------------------------------
	Bidirectional Character Types 
	
	as defined by the Unicode Bidirectional Algorithm Table 3-7.

	Note:
	  
	  The list of bidirectional character types here is not grouped the 
	  same way as the table 3-7, since the numberic values for the types
	  are chosen to keep the state and action tables compact.
------------------------------------------------------------------------*/
typedef enum _DT_Bidi_Class
{
    // input types
			 // ON MUST be zero, code relies on ON = N = 0
    ON = 0,  // Other Neutral, 0, 0x00  
    L,       // Left Letter, 1, 0x01
    R,       // Right Letter, 2, 0x02
    AN,      // Arabic Number, 3, 0x03
    EN,      // European Number, 4,0x04
    AL,      // Arabic Letter (Right-to-left), 5, 0x05
    NSM,     // Non-spacing Mark, 6, 0x06
    CS,      // Common Separator, 7, 0x07
    ES,      // European Separator, 8, 0x08
    ET,      // European Terminator (post/prefix e.g. $ and %), 9, 0x09
    
	// resolved types
    BN,      // Boundary neutral (type of RLE etc after explicit levels), 10, 0x0a
    
	// input types, 
    S,       // Segment Separator (TAB)		// used only in L1, 11, 0x0b
    WS,      // White space					// used only in L1, 12, 0x0c
    B,       // Paragraph Separator (aka as PS), 13, 0x0d
    
	// types for explicit controls
    RLO,     // these are used only in X1-X9, 14, 0x0e
    RLE,	 // 15, 0x0f
    LRO,	 // 16, 0x10
    LRE,	 // 17, 0x11
    PDF,	 // 18, 0x12

	// resolved types, also resolved directions
    N = ON,  // alias, where ON, WS and S are treated the same, 0, 0x00
}DT_Bidi_Class;

typedef struct _DT_BiDiCls_Entry
{
	DT16_ushort		code;
	DT_Bidi_Class	cls;
}DT_BiDiCls_Entry;

typedef struct{
	DT32_int	idx_beg;
	DT32_int	idx_end;
}DT_BidiCls_Plane_Idx;

typedef struct _DT_CodePair
{
	DT16_ushort	code;
	DT16_ushort	mirror;
}DT_CodePair, *pDT_CodePair;


DT_Bidi_Class bidi_getBidiClass(DT16_ushort ch);
DT32_int bidi_classify(const DT16_ushort* pszText, DT32_int * pcls,  DT32_int cch, DT_BOOL fWS);
DT_void bidi_BidiLines( DT32_int baselevel, DT16_ushort * pszLine, DT32_int * pclsLine, 
						DT32_int * plevelLine, DT32_int cchPara, DT32_int fMirror, DT_BOOL * pbrk);
DT32_int bidi_BidiParagraph(DT32_int *baselevel,  DT32_int * types, DT32_int * levels, DT32_int cch);

/* internal used function */
DT32_int bidi_resolveLines(DT16_ushort * pszInput, DT_BOOL * pbrk, DT32_int cch);
DT_void bidi_resolveWhitespace(DT32_int baselevel, const DT32_int *pcls, DT32_int *plevel, DT32_int cch);
DT_void bidi_mirror(DT16_ushort* pszInput, const DT32_int * plevel, DT32_int cch);
DT_void bidi_reverse(DT16_ushort* psz, DT32_int cch);
DT_void bidi_reverse_nsm(DT16_ushort* psz, DT32_int cch);
DT_void bidi_reverse_nsm_cg(CodevsGlyph* pszCaret, DT32_int cch, DT16_ushort *refText);
DT_void bidi_reverse_nsm_withg2info(DT16_ushort* psz, FontCodeInfo *pszg2info, DT32_int cch);
DT_void bidi_reverse_nsm_caret_seq(DLO_CodePositioning* pszCaret, DT32_int cch, DT16_ushort *refText);
DT32_int bidi_reorder(DT32_int baselevel, DT16_ushort* pszText, const DT32_int * plevel, DT32_int cch);
DT32_int bidi_reorder_nsm(DT32_int baselevel, DT16_ushort* pszText, const DT32_int * plevel, DT32_int cch);
DT32_int bidi_reorder_cg(DT32_int baselevel, CodevsGlyph* pszCaret, const DT32_int * plevel, DT32_int cch, DT16_ushort *refText);
//DT32_int bidi_reorder_caret_seq(DT32_int baselevel, DLO_CodePositioning* pszCaret, const DT32_int * plevel, DT32_int cch, DT16_ushort *refText, DT_BOOL fNsm);
DT32_int bidi_reorder_caret_seq_g2info(DT32_int baselevel, DLO_CodePositioning* pszCaret, FontCodeInfo* pszg2info, const DT32_int * plevel, DT32_int cch, DT16_ushort *refText, DT_BOOL fNsm);

extern DT_void make_gBidiClass_ArrayPlaneIdx();
#endif /*__DCWBIDI_H*/
