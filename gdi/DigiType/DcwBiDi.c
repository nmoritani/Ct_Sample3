
/* This code is slightly modified from:
	Bidi.cpp - version 26
	Reference implementation for Unicode Bidirectional Algorithm

   Using no language extensions, and providing commandline only with
   no debugging support. Not verified against the other implementations.
*/
#include "DcwBiDi.h"

#define DT_ASSERT(x)	if (!(x)) ; else ;

//#include <stdio.h>
//#define DT_ASSERT(x) if (!(x)) fprintf(stdout, "assert failed: %s\n", #x); else ;
//#define TCHAR	char
//#define LPTSTR  char *
//#ifndef DT_BOOL
//#define DT_BOOL char
//#define DT_FALSE 0
//#define DT_TRUE  1
//#endif

/*------------------------------------------------------------------------
     File: Bidi.C
     
	 Description
	 -----------

	 Sample Implementation of the Unicode Bidirectional Algorithm as it 
     was revised by Revision 5 of the Uniode Technical Report # 9 
	 (1999-8-17)

     This implementation is organized into several passes, each implemen-
     ting one or more of the rules of the Unicode Bidi Algorithm. The 
     resolution of Weak Types and of Neutrals each use a state table
     approach.

 
	 Implementation Note
	 -------------------

	 NOTE: The Unicode Birdirectional Algorithm removes all explicit 
		   formatting codes in rule X9, but states that this can be 
		   simulated by conformant implementations. This implementation
		   attempts to demonstrate such a simulation

		   To demonstrate this, the current implementation does the
		   following:

			in resolveExplicit()
				- change LRE, LRO, RLE, RLO, PDF to BN
				- assign nested levels to BN

			in resolveWeak and resolveNeutrals
				- assign L and R to BN's where they exist in place of
				  sor and eor by changing the last BN in front of a 
				  level change to a strong type
				- skip over BN's for the purpose of determining actions
				- include BN in the count of deferred runs
					which will resolve some of them to EN, AN and N

			in resolveWhiteSpace
				- set the level of any surviving BN to the base level, 
					or the level of	the preceding character
				- include LRE,LRO, RLE, RLO, PDF and BN in the count 
				   whitespace to be reset

		   This will result in the same order for non-BN characters as
		   if the BN characters had been removed.

		   The bidi_clean() function can be used to remove boundary marks for
		   verification purposes.

	 Notation
	 --------
	 Pointer variables generally start with the letter p
	 Counter variables generally start with the letter c
	 Index variables generally start with the letter i
	 Boolean variables generally start with the letter f

	 The enumerated bidirectional types have the same name as in the
	 description for the Unicode Bidirectional Algorithm

	 Update History:
	 --------------
	 Version 24 is the initial published and verified version of this
	 reference implementation. Version 25 and its updates fix various
	 minor issues with the scaffolding used for demonstrating the
	 algorithm using pseudo-alphabets from the command line or dialog
	 box. No changes to the implementation of the actual bidi algrithm
	 are made in any of the minor updates to version 25.

	 - updated pseudo-alphabet
	
	 - Last Revised 12-10-99 (25)

	 - enable demo mode for release builds - no other changes

	 - Last Revised 12-10-00 (25a)

	 - fix regression in pseudo alphabet use for Windows UI

	 - Last Revised 02-01-01 (25b)

	 - fixed a few comments, renamed a variable

	 - Last Revised 03-04-01 (25c)

	 - make base level settable, enable mirror by default, 
	   fix dialog size

     - Last Revised 06-02-01 (25e)

	 - fixed some comments

	 - Last Revised 09-29-01 (25f)

     - fixed classification for LS,RLM,LRM in pseudo alphabet, 
	   focus issues in UI, regression fix to commandline from 25(e)
	   fix DEMO switch

     - Last Revised 11-07-01 (25g)

     - fixed classification for plus/minus in pseudo alphabet
       to track changes made in Unicode 4.0.1

	 - Last Revised 12-03-04 (25h)

     Credits:
	 -------
	 Written by: Asmus Freytag
	 Command line interface by: Rick McGowan
	 Verification and Test Harness: Doug Felt

	 Disclaimer and legal rights:
	 ---------------------------
     Copyright (C) 1999-2005, ASMUS, Inc. All Rights Reserved. 
	 Distributed under the Terms of Use in http://www.unicode.org/copyright.html.
	  
	 THIS SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS 
	 OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
	 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT OF THIRD PARTY RIGHTS. 
	 IN NO EVENT SHALL THE COPYRIGHT HOLDER OR HOLDERS INCLUDED IN THIS NOTICE 
	 BE LIABLE FOR ANY CLAIM, OR ANY SPECIAL INDIRECT OR CONSEQUENTIAL DAMAGES, 
	 OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, 
	 WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, 
	 ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THE SOFTWARE.
------------------------------------------------------------------------*/


// === HELPER FUNCTIONS AND DECLARATIONS =================================

#define DT_odd(x) ((x) & 1)

extern DT_BiDiCls_Entry BidiClassArray[];
extern DT32_int gBidiClass_ArraySize;
extern DT_BidiCls_Plane_Idx gBidiClass_ArrayPlaneIdx[256];

/*---------------------------------------------------------------------- 
   The following array maps character codes to types for the purpose of 
   this sample implementation. The legend string gives a human readable 
   explanation of the pseudo alphabet.

   For simplicity, characters entered by buttons are given a 1:1 mapping
   between their type and pseudo character value. Pseudo characters that
   can be typed from the keyboard are explained in the legend string.

   Use the Unicode Character Database for the real values in real use.
 ---------------------------------------------------------------------*/

//#define chLRM 4
//#define chRLM 5
//#define chLS 0x15
//#define chRLO '}'
//#define chLRO '{'
//#define chRLE ']'
//#define chLRE '['
//#define chPDF '^'
//#define chBN  '~'

//DT32_int TypesFromChar[]  =
//{
//
////0   1   2   3   4   5   6   7   8   9   a   b   c   d   e   f
// BN, BN, BN, BN,  L,  R, BN, BN, BN,  S,  B,  S, WS,  B, BN, BN, /*00-0f*/
//LRO,LRE,PDF,RLO,RLE, WS,  L,  R, BN, BN, BN, BN,  B,  B,  B,  S, /*10-1f*/
// WS, ON, ON, ET, ET, ET, ON, ON, ON, ON, ON, ES, CS, ES, CS, ES, /*20-2f*/
// EN, EN, EN, EN, EN, EN, AN, AN, AN, AN, CS, ON, ON, ON, ON, ON, /*30-3f*/
// ON, AL, AL, AL, AL, AL, AL,  R,  R,  R,  R,  R,  R,  R,  R,  R, /*40-4f*/
//  R,  R,  R,  R,  R,  R,  R,  R,  R,  R,  R,LRE, ON,RLE,PDF,  S, /*50-5f*/
//NSM,  L,  L,  L,  L,  L,  L,  L,  L,  L,  L,  L,  L,  L,  L,  L, /*60-6f*/
//  L,  L,  L,  L,  L,  L,  L,  L,  L,  L,  L,LRO,  B,RLO, BN, ON, /*70-7f*/
//};


/***************************************
Reverse, human readable reference:
LRM: 0x4
RLM: 0x5
  L: 0x16,a-z
LRE: 0x11,[
LRO: 0x10,{
  R: 0x17,G-Z
 AL: A-F
RLE: 0x14,]
RLO: 0x13,}
PDF: 0x12,^
 EN: 0-5
 ES: /,+,[hyphen]
 ET: #,$,%
 AN: 6-9
 CS: [comma],.,:
NSM: `
 BN: 0x0-0x8,0xe,0xf,0x18-0x1b,~
  B: 0xa,0xd,0x1c-0x1e,|
  S: 0x9,0xb,0x1f,_
 WS: 0xc,0x15,[space]
 ON: !,",&,',(,),*,;,<,=,>,?,@,\,0x7f
****************************************/

// WS, LS and S are not explicitly needed except for L1. Therefore this
// Table conflates ON, S, WS, and LS to N, all others unchanged
DT32_int NTypes[] = {    
    N,      // ON,    
    L,      // L,     
    R,      // R,     
    AN,     // AN, 
    EN,     // EN, 
    AL,     // AL 
    NSM,    // NSM 
    CS,     // CS 
    ES,     // ES 
    ET,     // ET 
    BN,     // BN
    N,      // S  
    N,      // WS 
    B,      // B
    RLO,    // RLO
    RLE,    // RLE
    LRO,    // LRO
    LRE,    // LRE
    PDF,    // PDF
	ON,		// LS
};


DT32_int bidi_bsearch(DT16_ushort code, DT32_int n, DT_Bidi_Class *cls)
{
	DT32_int mid, low = 0, high = n - 1;
	DT16_ushort plane;

DBG_MSG_SHOW_FUNC_NAME();

	plane = code>>8;
	low = gBidiClass_ArrayPlaneIdx[plane].idx_beg;
	if(low < 0)
		return -1;
	
	// get next plane idx
	high = gBidiClass_ArrayPlaneIdx[plane].idx_end;
	//if(high < 0 || high > n - 1)		// make_gBidiClass_ArrayPlaneIdx() should ensure the accuracy.
	//	return -1;
	
    while (low <= high)
    {
        mid = (low + high) / 2;

        if (BidiClassArray[mid].code == code)
        {
			if(cls){
				*cls = BidiClassArray[mid].cls;
			}
            return mid;
        }
        else if (BidiClassArray[mid].code > code)
        {
            high = mid - 1;
        }
        else if (BidiClassArray[mid].code < code)
        {
            low = mid + 1;
        }
    }

    return -1;
}

DT_Bidi_Class bidi_getBidiClass(DT16_ushort ch)
{
	DT_Bidi_Class bdcls = L;	
	DT_BiDiCls_Entry *item = NULL;

DBG_MSG_SHOW_FUNC_NAME();

#if (DT_CODE_ASCII_IN_PUA==0xE400)
	if(ch >= 0xE420 && ch <= 0xE47F){		// ASCII in PUA, convert to ASCII directly.
		ch -= 0xE400;
	}else
#endif
	if(ch >= 0xFF01 && ch <= 0xFF5E){		// Fullwidth ASCII
		ch -= 0xFEE0;
	}

	if(ch <= 0x007F){						// ASCII
		if(ch < 0x0041){
			item = &BidiClassArray[ch];
			return item->cls;
		}else if(ch < 0x005B){				// A, B, C, D....X, Y, Z, not in array.
			return L;
		}else if(ch < 0x0061){				
			item = &BidiClassArray[ch-26];
			return item->cls;
		}else if(ch < 0x007B){				// a, b, c, d....x, y, z, not in array.
			return L;
		}else{
			item = &BidiClassArray[ch-52];
			return item->cls;
		}
	}

	if(ch >= 0x3040 && ch <= 0x30FF){		// Hiragana, Katakana
		switch(ch){
		case 0x3099:
		case 0x309A:
			return NSM;
		case 0x309B:
		case 0x309C:
		case 0x30A0:
		case 0x30FB:
			return ON;
		default:
			return L;
		}
	}
	if(ch >= 0x4E00 && ch <= 0x9FFF)		// CJK, Han
		return L;

	// in DcwBidiClassData.c(according to Unicode 5.0), 0xFF9E & 0xFF9F won't be NSM.
//	if(ch >= 0xFF65 && ch <= 0xFF9F){		// Halfwidth Katakana
//		switch(ch){
//		case 0xFF65:
//			return ON;
//		case 0xFF9E:
//		case 0xFF9F:
//			return NSM;
//		default:
//			return L;
//		}
//	}
	if(ch >= 0xFF65 && ch <= 0xFF9F){		// Halfwidth Katakana
		if(ch == 0xFF65)
			return ON;
		else
			return L;
	}

	if( 0 > bidi_bsearch( ch, gBidiClass_ArraySize, &bdcls))
	{
		// Not found
		if( (0x0600<=ch && ch<=0x07BF)
			|| (0xFB50<=ch && ch<=0xFDFF)
			|| (0xFE70<=ch && ch<=0xFEFF) )
		{
			bdcls = AL;
		}
		else if( (0x0590<=ch && ch<=0x05FF)
			|| (0x07C0<=ch && ch<=0x08FF)
			|| (0xFB1D<=ch && ch<=0xFB4F)
			//	|| (0x00010800<=ch && ch<=0x00010FFF)
			//	|| (0x0001E800<=ch && ch<=0x0001EFFF)
			)
		{
			bdcls = R;
		}
		else
			bdcls = L;

	}else{
		// found
	}

	return bdcls;
}

DT32_int bidi_ClassFromChN(DT16_ushort ch)
{
DBG_MSG_SHOW_FUNC_NAME();

    //DT_ASSERT(ch < 0x7f && ch >= 0);
    //return NTypes[TypesFromChar[ch & 0x7f]];
	return NTypes[bidi_getBidiClass(ch)];
}

DT32_int bidi_ClassFromChWS(DT16_ushort ch)
{
 DBG_MSG_SHOW_FUNC_NAME();
 
	//DT_ASSERT(ch < 0x7f && ch >= 0);
    //return TypesFromChar[ch & 0x7f];
	return bidi_getBidiClass(ch);
}

// === DISPLAY SUPPORT =================================================
 
//    enum display_symbol   // Display character codes
//    {
//		RIGHT = '<',			// rtl arrow
//		LEFT = '>',				// ltr arrow
//		PUSH = '+',				// dn arrow
//		POP = '-',				// up arrow
//		LSEP =  '=',			// double dagger
//		NEUTRAL = ' ',			// rtl/ltr dbl headed arrow
//		ALPHA = 'a',
//    };

// display support: 
//DT16_ushort CharFromTypes[] =
//{
//    NEUTRAL,    // ON,
//    LEFT,       // L,
//    RIGHT,      // R,
//    '9',        // AN,
//    '1',        // EN, 
//    ALPHA,      // AL 
//    '@',        // NSM 
//    '.',        // CS 
//    ',',        // ES 
//    '$',        // ET 
//    ':',        // BN
//    'X',        // S  
//    '_',        // WS 
//    'B',        // B
//    PUSH,       // RLO
//    PUSH,       // RLE
//    PUSH,       // LRO
//    PUSH,       // LRE
//    POP,        // PDF
//	LSEP,		// LS
//                      
//};


// This works only for testing
// a full implementation would need 61 levels....
//DT16_ushort CharFromLevel[] =
//{
//    '0', '1', '2', '3', '4', 
//    '5', '6', '7', '8', '9',    
//    'A', 'B', 'C', 'D', 'E',
//    'F', 'X', 'Y', 'Z'      // overhang levels
//};

// === HELPER FUNCTIONS ================================================

// reverse cch characters 
DT_void bidi_reverse(DT16_ushort* psz, DT32_int cch)
{
    DT16_ushort chTemp;
	DT32_int ich = 0;
    for (; ich < --cch; ich++)
    {
        chTemp = psz[ich];
        psz[ich] = psz[cch];
        psz[cch] = chTemp;
    }
}

// Set a run of cval values at locations all prior to, but not including 
// iStart, to the new value nval.
DT_void bidi_SetDeferredRun(DT32_int *pval, DT32_int cval, DT32_int iStart, DT32_int nval)
{
	DT32_int i = iStart - 1;
    for (; i >= iStart - cval; i--)
    {
        pval[i] = nval;
    }
}

// === ASSIGNING BIDI CLASSES ============================================

/*------------------------------------------------------------------------
    Function: bidi_classify
    
    Determines the character classes for all following
    passes of the algorithm

    Input: Text string
           Character count
           Whether to report types as WS, ON, S or as N (false)

    Output: Array of directional classes    
------------------------------------------------------------------------*/
DT32_int bidi_classify(const DT16_ushort* pszText, DT32_int * pcls,  DT32_int cch, DT_BOOL fWS)
{
    if (fWS)
    {
		DT32_int ich = 0;
        for (; ich < cch; ich++)
        {
            pcls[ich] = bidi_ClassFromChWS(pszText[ich]);
        }
        return ich;
    }
    else
    {
		DT32_int ich = 0;
        for (; ich < cch; ich++)
        {
            pcls[ich] = bidi_ClassFromChN(pszText[ich]);
        }
        return ich;
    }
}

// === THE PARAGRAPH LEVEL ===============================================

/*------------------------------------------------------------------------
    Function: bidi_resolveParagraphs
    
    Resolves the input strings into blocks over which the algorithm
    is then applied.

	Implements Rule P1 of the Unicode Bidi Algorithm

    Input: Text string
           Character count

    Output: revised character count

    Note:	This is a very simplistic function. In effect it restricts
			the action of the algorithm to the first paragraph in the input
			where a paragraph ends at the end of the first block separator
			or at the end of the input text.

------------------------------------------------------------------------*/

DT32_int bidi_resolveParagraphs(DT32_int * types, DT32_int cch)
{
	// skip characters not of type B
	DT32_int ich = 0;
	for(; ich < cch && types[ich] != B; ich++) 
		;
	// stop after first B, make it a BN for use in the next steps
	if (ich < cch && types[ich] == B) 
		types[ich++] = BN;
	return ich;
}

/*------------------------------------------------------------------------
    Function: bidi_baseLevel
    
    Determines the base level 

    Implements rule P2 of the Unicode Bidi Algorithm.

    Input: Array of directional classes
           Character count

    Note: Ignores explicit embeddings
------------------------------------------------------------------------*/
DT32_int bidi_baseLevel(const DT32_int * pcls,  DT32_int cch)
{
	DT32_int ich = 0;
    for (; ich < cch; ich++)
    {
        switch (pcls[ich])
        {
        // strong left
        case L:
            return 0;
            break;

        // strong right
        case R:
        case AL:
            return 1;
            break;
        }
    }
    return 0;
}

//====== RESOLVE EXPLICIT ================================================

DT32_int bidi_GreaterEven(DT32_int i)
{
    return DT_odd(i) ? i + 1 : i + 2;
}

DT32_int bidi_GreaterOdd(DT32_int i)
{
    return DT_odd(i) ? i + 2 : i + 1;
}

DT32_int bidi_EmbeddingDirection(DT32_int level)
{
    return DT_odd(level) ? R : L;
}


/*------------------------------------------------------------------------
    Function: resolveExplicit
    
    Recursively resolves explicit embedding levels and overrides. 
    Implements rules X1-X9, of the Unicode Bidirectional Algorithm.

    Input: Base embedding level and direction
           Character count

    Output: Array of embedding levels
            
    In/Out: Array of direction classes


    Note: The function uses two simple counters to keep track of 
          matching explicit codes and PDF. Use the default argument for 
          the outermost call. The nesting counter counts the recursion
		  depth and not the embedding level.
------------------------------------------------------------------------*/
#define MAX_LEVEL 61 // the real value

DT32_int bidi_resolveExplicit(DT32_int level, DT32_int dir, DT32_int * pcls, DT32_int * plevel, DT32_int cch, 
                    DT32_int nNest)
{
    // always called with a valid nesting level
    // nesting levels are != embedding levels
    DT32_int nLastValid = nNest;
	DT32_int ich = 0;

    // check input values 
    DT_ASSERT(nNest >= 0 && level >= 0 && level <= MAX_LEVEL);

    // process the text
    for (; ich < cch; ich++)
    {
        DT32_int cls = pcls[ich];
        switch (cls)
        {
        case LRO:
        case LRE:
            nNest++;
            if (bidi_GreaterEven(level) <= MAX_LEVEL)    
            {
                plevel[ich] = bidi_GreaterEven(level);
                pcls[ich] = BN;
                ich += bidi_resolveExplicit(plevel[ich], (cls == LRE ? N : L),
							&pcls[ich+1], &plevel[ich+1], 
                             cch - (ich+1), nNest);
                nNest--;
                continue;
            }
            cls = pcls[ich] = BN;
            break;

        case RLO:
        case RLE:
            nNest++;
            if (bidi_GreaterOdd(level) <= MAX_LEVEL)  
            {
                plevel[ich] = bidi_GreaterOdd(level);
                pcls[ich] = BN;
                ich += bidi_resolveExplicit(plevel[ich], (cls == RLE ? N : R),
								&pcls[ich+1], &plevel[ich+1],
                                 cch - (ich+1), nNest);
                nNest--;
                continue;
            }
            cls = pcls[ich] = BN;
            break;

        case PDF:
            cls = pcls[ich] = BN;
            if (nNest)
            {
                if (nLastValid < nNest)
                {
                    nNest--;
                }
                else
                {
                    cch = ich; // break the loop, but complete body
                }
            }
			break;
        }

        // Apply the override
        if (dir != N)
        {
            cls = dir;
        }
        plevel[ich] = level;
		if (pcls[ich] != BN)
			pcls[ich] = cls;
    }

    return ich;
}

// === RESOLVE WEAK TYPES ================================================

typedef enum _DT_bidi_state // possible states
{
	xa,		//  arabic letter            
	xr,		//  right leter			  
	xl,		//  left letter			  
    		                               
	ao,		//  arabic lett. foll by ON  
	ro,		//  right lett. foll by ON	  
	lo,		//  left lett. foll by ON	  
    		                               
	rt,		//  ET following R          
	lt,		//  ET following L		  
    		                               
	cn,		//  EN, AN following AL      
	ra,		//  arabic number foll R    
	re,		//  european number foll R  
	la,		//  arabic number foll L    
	le,		//  european number foll L  
    		                               
	ac,		//  CS following cn          
	rc,		//  CS following ra		  
	rs,		//  CS,ES following re       
	lc,		//  CS following la		  
	ls,		//  CS,ES following le		  

	ret,	//  ET following re
	let,	//  ET following le
} DT_bidi_state;

DT32_int stateWeak[][10] =
{
    //  N,  L,  R   AN, EN, AL,NSM, CS, ES, ET,  
/*xa*/  ao, xl, xr, cn, cn, xa, xa, ao, ao, ao, /* arabic letter          */    
/*xr*/  ro, xl, xr, ra, re, xa, xr, ro, ro, rt, /* right letter           */    
/*xl*/  lo, xl, xr, la, le, xa, xl, lo, lo, lt, /* left letter            */
                                  
/*ao*/  ao, xl, xr, cn, cn, xa, ao, ao, ao, ao, /* arabic lett. foll by ON*/    
/*ro*/  ro, xl, xr, ra, re, xa, ro, ro, ro, rt, /* right lett. foll by ON */    
/*lo*/  lo, xl, xr, la, le, xa, lo, lo, lo, lt, /* left lett. foll by ON  */    
                                  
/*rt*/  ro, xl, xr, ra, re, xa, rt, ro, ro, rt, /* ET following R         */      
/*lt*/  lo, xl, xr, la, le, xa, lt, lo, lo, lt, /* ET following L         */
                                  
/*cn*/  ao, xl, xr, cn, cn, xa, cn, ac, ao, ao, /* EN, AN following AL    */
/*ra*/  ro, xl, xr, ra, re, xa, ra, rc, ro, rt, /* arabic number foll R   */
/*re*/  ro, xl, xr, ra, re, xa, re, rs, rs,ret, /* european number foll R */      
/*la*/  lo, xl, xr, la, le, xa, la, lc, lo, lt, /* arabic number foll L   */    
/*le*/  lo, xl, xr, la, le, xa, le, ls, ls,let, /* european number foll L */      
                                  
/*ac*/  ao, xl, xr, cn, cn, xa, ao, ao, ao, ao, /* CS following cn        */    
/*rc*/  ro, xl, xr, ra, re, xa, ro, ro, ro, rt, /* CS following ra        */
/*rs*/  ro, xl, xr, ra, re, xa, ro, ro, ro, rt, /* CS,ES following re     */      
/*lc*/  lo, xl, xr, la, le, xa, lo, lo, lo, lt, /* CS following la        */    
/*ls*/  lo, xl, xr, la, le, xa, lo, lo, lo, lt, /* CS,ES following le     */    

/*ret*/ ro, xl, xr, ra, re, xa,ret, ro, ro,ret, /* ET following re        */      
/*let*/ lo, xl, xr, la, le, xa,let, lo, lo,let, /* ET following le        */
								  

};                                              

enum bidi_action // possible actions 
{
	// primitives
    IX = 0x100,					// increment
    XX = 0xF,					// no-op

	// actions
    xxx = (XX << 4) + XX,		// no-op
    xIx = IX + xxx,				// increment run
    xxN = (XX << 4) + ON,		// set current to N
    xxE = (XX << 4) + EN,		// set current to EN
    xxA = (XX << 4) + AN,		// set current to AN
    xxR = (XX << 4) + R,		// set current to R
    xxL = (XX << 4) + L,		// set current to L
    Nxx = (ON << 4) + 0xF,		// set run to neutral
    Axx = (AN << 4) + 0xF,		// set run to AN
    ExE = (EN << 4) + EN,		// set run to EN, set current to EN
    NIx = (ON << 4) + 0xF + IX, // set run to N, increment
    NxN = (ON << 4) + ON,		// set run to N, set current to N
    NxR = (ON << 4) + R,		// set run to N, set current to R
    NxE = (ON << 4) + EN,		// set run to N, set current to EN

    AxA = (AN << 4) + AN,		// set run to AN, set current to AN
    NxL = (ON << 4) + L,		// set run to N, set current to L
    LxL = (L << 4) + L,			// set run to L, set current to L
};


DT32_int actionWeak[][10] =                          
{                                               
    //  N,   L,   R    AN,  EN,  AL, NSM,  CS,  ES,  ET,  
/*xa*/ xxx, xxx, xxx, xxx, xxA, xxR, xxR, xxN, xxN, xxN, /* arabic letter           */    
/*xr*/ xxx, xxx, xxx, xxx, xxE, xxR, xxR, xxN, xxN, xIx, /* right leter             */    
/*xl*/ xxx, xxx, xxx, xxx, xxL, xxR, xxL, xxN, xxN, xIx, /* left letter             */

/*ao*/ xxx, xxx, xxx, xxx, xxA, xxR, xxN, xxN, xxN, xxN, /* arabic lett. foll by ON */    
/*ro*/ xxx, xxx, xxx, xxx, xxE, xxR, xxN, xxN, xxN, xIx, /* right lett. foll by ON  */    
/*lo*/ xxx, xxx, xxx, xxx, xxL, xxR, xxN, xxN, xxN, xIx, /* left lett. foll by ON   */    

/*rt*/ Nxx, Nxx, Nxx, Nxx, ExE, NxR, xIx, NxN, NxN, xIx, /* ET following R         */      
/*lt*/ Nxx, Nxx, Nxx, Nxx, LxL, NxR, xIx, NxN, NxN, xIx, /* ET following L         */

/*cn*/ xxx, xxx, xxx, xxx, xxA, xxR, xxA, xIx, xxN, xxN, /* EN, AN following  AL    */
/*ra*/ xxx, xxx, xxx, xxx, xxE, xxR, xxA, xIx, xxN, xIx, /* arabic number foll R   */
/*re*/ xxx, xxx, xxx, xxx, xxE, xxR, xxE, xIx, xIx, xxE, /* european number foll R */      
/*la*/ xxx, xxx, xxx, xxx, xxL, xxR, xxA, xIx, xxN, xIx, /* arabic number foll L   */    
/*le*/ xxx, xxx, xxx, xxx, xxL, xxR, xxL, xIx, xIx, xxL, /* european number foll L */      

/*ac*/ Nxx, Nxx, Nxx, Axx, AxA, NxR, NxN, NxN, NxN, NxN, /* CS following cn         */    
/*rc*/ Nxx, Nxx, Nxx, Axx, NxE, NxR, NxN, NxN, NxN, NIx, /* CS following ra         */
/*rs*/ Nxx, Nxx, Nxx, Nxx, ExE, NxR, NxN, NxN, NxN, NIx, /* CS,ES following re      */      
/*lc*/ Nxx, Nxx, Nxx, Axx, NxL, NxR, NxN, NxN, NxN, NIx, /* CS following la         */    
/*ls*/ Nxx, Nxx, Nxx, Nxx, LxL, NxR, NxN, NxN, NxN, NIx, /* CS,ES following le      */    

/*ret*/xxx, xxx, xxx, xxx, xxE, xxR, xxE, xxN, xxN, xxE, /* ET following re		    */      
/*let*/xxx, xxx, xxx, xxx, xxL, xxR, xxL, xxN, xxN, xxL, /* ET following le			*/      
};                                                            
                                                              
DT32_int bidi_GetDeferredType(DT32_int action)
{
    return (action >> 4) & 0xF;
}

DT32_int bidi_GetResolvedType(DT32_int action)
{
    return action & 0xF;
}

/* Note on action table:

  States can be of two kinds: 
     - Immediate Resolution State, where each input token
       is resolved as soon as it is seen. These states havve
       only single action codes (xxN) or the no-op (xxx)
       for static input tokens.
     - Deferred Resolution State, where input tokens either
       either extend the run (xIx) or resolve its Type (e.g. Nxx).

   Input classes are of three kinds
     - Static Input Token, where the class of the token remains 
       unchanged on output (AN, L, N, R) 
     - Replaced Input Token, where the class of the token is
       always replaced on output (AL, BN, NSM, CS, ES, ET) 
     - Conditional Input Token, where the class of the token is
       changed on output in some, but not all, cases (EN) 

     Where tokens are subject to change, a double action
     (e.g. NxA, or NxN) is _required_ after deferred states,  
     resolving both the deferred state and changing the current token.
*/

/*------------------------------------------------------------------------
    Function: bidi_resolveWeak
    
    Resolves the directionality of numeric and other weak character types

    Implements rules X10 and W1-W6 of the Unicode Bidirectional Algorithm.

    Input: Array of embedding levels
           Character count

    In/Out: Array of directional classes    
    
    Note: On input only these directional classes are expected
          AL, HL, R, L,  ON, BN, NSM, AN, EN, ES, ET, CS,
------------------------------------------------------------------------*/
DT_void bidi_resolveWeak(DT32_int baselevel, DT32_int *pcls, DT32_int *plevel, DT32_int cch)
{
    DT32_int state = DT_odd(baselevel) ? xr : xl;
    DT32_int cls;

	DT32_int level = baselevel;
	DT32_int action, clsRun, clsNew;
    DT32_int cchRun = 0;
	DT32_int ich = 0;

	for (; ich < cch; ich++)
    {
		// ignore boundary neutrals
		if (pcls[ich] == BN)
		{
			// must flatten levels unless at a level change;
		    plevel[ich] = level;

			// lookahead for level changes
			if (ich + 1 == cch && level != baselevel)
			{
				// have to fixup last BN before end of the loop, since
				// its fix-upped value will be needed below the assert
				pcls[ich] = bidi_EmbeddingDirection(level);
			} 
			else if (ich + 1 < cch && level != plevel[ich+1] && pcls[ich+1] != BN)
			{
				// fixup LAST BN in front / after a level run to make 
				// it act like the SOR/EOR in rule X10
				DT32_int newlevel = plevel[ich+1];
				if (level > newlevel) {
					newlevel = level;
				}
				plevel[ich] = newlevel;

				// must match assigned level
				pcls[ich] = bidi_EmbeddingDirection(newlevel);
				level = plevel[ich+1];
			}
			else
			{
				// don't interrupt runs
				if (cchRun) 
				{
					cchRun++;
				}
				continue;
			}
		}

		DT_ASSERT(pcls[ich] <= BN);
        cls = pcls[ich];

        action = actionWeak[state][cls];

        // resolve the directionality for deferred runs
        clsRun = bidi_GetDeferredType(action);
        if (clsRun != XX)
        {
            bidi_SetDeferredRun(pcls, cchRun, ich, clsRun);
            cchRun = 0;
        }

        // resolve the directionality class at the current location
        clsNew = bidi_GetResolvedType(action);
        if (clsNew != XX)
            pcls[ich] = clsNew;

		// increment a deferred run
        if (IX & action)
            cchRun++;

        state = stateWeak[state][cls];
    }
    
    // resolve any deferred runs
	// use the direction of the current level to emulate PDF
	cls = bidi_EmbeddingDirection(level);

    // resolve the directionality for deferred runs
    clsRun = bidi_GetDeferredType(actionWeak[state][cls]);
    if (clsRun != XX) 
        bidi_SetDeferredRun(pcls, cchRun, ich, clsRun);
}

// === RESOLVE NEUTAL TYPES ==============================================

// action values
enum neutral_action
{
    // action to resolve previous input
    nL = L,         // resolve EN to L
    En = 3 << 4,    // resolve neutrals run to embedding level direction
    Rn = R << 4,    // resolve neutrals run to strong right
    Ln = L << 4,    // resolved neutrals run to strong left
    In = (1<<8),    // increment count of deferred neutrals
    LnL = (1<<4)+L, // set run and EN to L
};

DT32_int bidi_GetDeferredNeutrals(DT32_int action, DT32_int level)
{
    action = (action >> 4) & 0xF;
    if (action == (En >> 4))
        return bidi_EmbeddingDirection(level);
    else
        return action;
}

DT32_int bidi_GetResolvedNeutrals(DT32_int action)
{
    action = action & 0xF;
    if (action == In)
        return 0;
    else
        return action;
}

// state values
enum neutral_state
{
    // new temporary class
    r,  // R and characters resolved to R
    l,  // L and characters resolved to L
    rn, // N preceded by right
    ln, // N preceded by left
    a,  // AN preceded by left (the abbrev 'la' is used up above)
    na, // N preceeded by a
} ;


/*------------------------------------------------------------------------
  Notes:

  By rule W7, whenever a EN is 'dominated' by an L (including start of 
  run with embedding direction = L) it is resolved to, and further treated 
  as L.

  This leads to the need for 'a' and 'na' states.
------------------------------------------------------------------------*/

DT32_int actionNeutrals[][5] =                   
{
// N,  L,  R, AN, EN, = cls
                      // state =                      
  In,  0,  0,  0,  0, // r    right                               
  In,  0,  0,  0,  L, // l    left
            
  In, En, Rn, Rn, Rn, // rn   N preceded by right                           
  In, Ln, En, En, LnL,// ln   N preceded by left                            
                                     
  In,  0,  0,  0,  L, // a   AN preceded by left
  In, En, Rn, Rn, En, // na   N  preceded by a     
} ;

DT32_int stateNeutrals[][5] =
{
//  N, L,  R,  AN, EN = cls
                       // state =   
   rn, l,  r,  r,  r,   // r   right                                        
   ln, l,  r,  a,  l,   // l   left                                      
                                                                      
   rn, l,  r,  r,  r,   // rn  N preceded by right                       
   ln, l,  r,  a,  l,   // ln  N preceded by left                        
                                                                    
   na, l,  r,  a,  l,   // a  AN preceded by left                       
   na, l,  r,  a,  l,   // na  N preceded by la                      
} ;

/*------------------------------------------------------------------------
    Function: bidi_resolveNeutrals
    
    Resolves the directionality of neutral character types.

    Implements rules W7, N1 and N2 of the Unicode Bidi Algorithm.
	
    Input: Array of embedding levels
           Character count
		   Baselevel

    In/Out: Array of directional classes    
    
    Note: On input only these directional classes are expected
          R,  L,  N, AN, EN and BN

		  W8 resolves a number of ENs to L
------------------------------------------------------------------------*/
DT_void bidi_resolveNeutrals(DT32_int baselevel, DT32_int *pcls, const DT32_int *plevel, DT32_int cch)
{   
    // the state at the start of text depends on the base level
    DT32_int state = DT_odd(baselevel) ? r : l;
    DT32_int cls;

    DT32_int cchRun = 0;
    DT32_int level = baselevel;

	DT32_int action, clsRun, clsNew;
    DT32_int ich = 0;
	for (; ich < cch; ich++)
    {
		// ignore boundary neutrals
		if (pcls[ich] == BN)
		{
			// include in the count for a deferred run
			if (cchRun)
				cchRun++;

			// skip any further processing
			continue;
		}

        DT_ASSERT(pcls[ich] < 5); // "Only N, L, R,  AN, EN are allowed"
        cls = pcls[ich];

        action = actionNeutrals[state][cls];

        // resolve the directionality for deferred runs
        clsRun = bidi_GetDeferredNeutrals(action, level);
        if (clsRun != N)
        {
            bidi_SetDeferredRun(pcls, cchRun, ich, clsRun);
            cchRun = 0;
        }

        // resolve the directionality class at the current location
        clsNew = bidi_GetResolvedNeutrals(action);
        if (clsNew != N)
            pcls[ich] = clsNew;

        if (In & action)
            cchRun++;

        state = stateNeutrals[state][cls];
        level = plevel[ich];
    }
    
    // resolve any deferred runs
    cls = bidi_EmbeddingDirection(level);    // eor has type of current level

    // resolve the directionality for deferred runs
    clsRun = bidi_GetDeferredNeutrals(actionNeutrals[state][cls], level);
    if (clsRun != N) 
        bidi_SetDeferredRun(pcls, cchRun, ich, clsRun);
}

// === RESOLVE IMPLLICIT =================================================

/*------------------------------------------------------------------------
    Function: bidi_resolveImplicit
    
    Recursively resolves implicit embedding levels. 
    Implements rules I1 and I2 of the Unicode Bidirectional Algorithm.

    Input: Array of direction classes
           Character count
		   Base level

    In/Out: Array of embedding levels
            
    Note: levels may exceed 15 on output.
          Accepted subset of direction classes
          R, L, AN, EN
------------------------------------------------------------------------*/
DT32_int addLevel[][4] =
{
        // L,  R,   AN, EN = cls 
                            // level =
/* even */  0,  1,  2,  2,  // EVEN
/* odd  */  1,  0,  1,  1,  // ODD

};

DT_void bidi_resolveImplicit(const DT32_int * pcls, DT32_int * plevel, DT32_int cch)
{
    DT32_int ich = 0;
	for (; ich < cch; ich++)
    {
		// cannot resolve bn here, since some bn were resolved to strong 
		// types in resolveWeak. To remove these we need the original 
		// types, which are available again in resolveWhiteSpace
		if (pcls[ich] == BN)
		{
			continue;
		}
		DT_ASSERT(pcls[ich] > 0); // "No Neutrals allowed to survive here."
	    DT_ASSERT(pcls[ich] < 5); // "Out of range."
        plevel[ich] += addLevel[DT_odd(plevel[ich])][pcls[ich] - 1];
    }
}

// === REORDER ===========================================================
/*------------------------------------------------------------------------
    Function: bidi_resolveLines
    
    Breaks a paragraph into lines 

    Input:  Character count
    In/Out: Array of characters
			Array of line break flags

    Returns the count of characters on the first line

    Note: This function only breaks lines at hard line breaks. Other
	line breaks can be passed in. If pbrk[n] is TRUE, then a break
	occurs after the character in pszInput[n]. Breaks before the first
	character are not allowed.
------------------------------------------------------------------------*/
DT32_int bidi_resolveLines(DT16_ushort * pszInput, DT_BOOL * pbrk, DT32_int cch)
{
	// skip characters not of type LS
	DT32_int ich = 0;
	for(; ich < cch; ich++)
	{
		if (pszInput[ich] == chLS || (pbrk && pbrk[ich]))
		{
			ich++;
			break;
		}
	}

	return ich;
}

/*------------------------------------------------------------------------
    Function: bidi_resolveWhiteSpace
    
    Resolves levels for WS and S 
    Implements rule L1 of the Unicode bidi Algorithm.

    Input:  Base embedding level
            Character count
            Array of direction classes (for one line of text)

    In/Out: Array of embedding levels (for one line of text)

    Note: this should be applied a line at a time. The default driver 
		  code supplied in this file assumes a single line of text; for
		  a real implementation, cch and the initial pointer values 
		  would have to be adjusted.
------------------------------------------------------------------------*/
DT_void bidi_resolveWhitespace(DT32_int baselevel, const DT32_int *pcls, DT32_int *plevel, DT32_int cch)
{
    DT32_int cchrun = 0;
    DT32_int oldlevel = baselevel;
    
	DT32_int ich = 0;
	for (; ich < cch; ich++)
    {
        switch(pcls[ich])
        {
        default:
            cchrun = 0; // any other character breaks the run
            break;
        case WS:
			cchrun++;
			break;

		case RLE:
		case LRE:
		case LRO:
		case RLO:
		case PDF:
		case BN:
			plevel[ich] = oldlevel;
            cchrun++;
            break;

        case S:
        case B:
            // reset levels for WS before eot
            bidi_SetDeferredRun(plevel, cchrun, ich, baselevel);
            cchrun = 0;
            plevel[ich] = baselevel;
            break;
        }
		oldlevel = plevel[ich];
    }
    // reset level before eot
    bidi_SetDeferredRun(plevel, cchrun, ich, baselevel);
}


/*------------------------------------------------------------------------
    Functions: bidi_reorder/bidi_reorderLevel
    
    Recursively reorders the display string 
    "From the highest level down, reverse all characters at that level and 
    higher, down to the lowest odd level"

	Implements rule L2 of the Unicode bidi Algorithm.

    Input: Array of embedding levels
           Character count
           Flag enabling reversal (set to false by initial caller)

    In/Out: Text to reorder     
            
    Note: levels may exceed 15 resp. 61 on input.

	Rule L3 - reorder combining marks is not implemented here
	Rule L4 - glyph mirroring is implemented as a display option below

    Note: this should be applied a line at a time
-------------------------------------------------------------------------*/
// reverse cch characters 
DT32_int bidi_reorderLevel(DT32_int level, DT16_ushort* pszText, const DT32_int * plevel, DT32_int cch, DT_BOOL fReverse)
{
    DT32_int ich = 0;

    // true as soon as first odd level encountered
    fReverse = fReverse || DT_odd(level);
	
	for (; ich < cch; ich++)
    {
        if (plevel[ich] < level)
        {
            break;
        }
        else if (plevel[ich] > level)
        {
            ich += bidi_reorderLevel(level + 1, pszText + ich, plevel + ich, 
                cch - ich, fReverse) - 1;
        }
    }
    if (fReverse)
    {
        bidi_reverse(pszText, ich);
		//bidi_reverse_nsm(pszText, ich);
    }
    return ich;
}

DT32_int bidi_reorder(DT32_int baselevel, DT16_ushort* pszText, const DT32_int * plevel, DT32_int cch)
{
    DT32_int ich = 0;

    while (ich < cch)
    {
        ich += bidi_reorderLevel(baselevel, pszText + ich, plevel + ich, 
            cch - ich, DT_FALSE);
    }
    return ich;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
DT_void bidi_reverse_nsm(DT16_ushort* psz, DT32_int cch)
{
	DT16_ushort nsmsz[DLO_BIDI_MAX_NSM];	// a temp buffer for NSM code points (glyphs), assume 8 is enough
	DT8_uchar	nsmcnt;
	DT32_int	i, sidx, ich = 0;

	bidi_reverse(psz, cch);	// reverse the string

	// deal with NSM
	nsmcnt = 0;	
	sidx = -1;		// use -1 to represent it's not a NSM
	//DT_memset(nsmsz, 0, sizeof(nsmsz));		// 2012-02-06: not required.
	while(ich < cch)
	{
		if(NSM==bidi_ClassFromChWS(psz[ich]))
		{
			sidx = ich;		// encountered a NSM, keep its index.

			// count how many continuous NSMs are there.
			while( NSM==bidi_ClassFromChWS(psz[ich]) && ich < cch && nsmcnt < DLO_BIDI_MAX_NSM){
				nsmsz[nsmcnt] = psz[ich];
				nsmcnt++;
				ich++;
			}
			// Set base glyph
			if(ich >= cch){				// the last glyph is a NSM

			}else{
				psz[sidx] = psz[ich];	// assume it's the base glyph of these NSMs.
				ich++;
				sidx++;
			}
			bidi_reverse(nsmsz, nsmcnt);// reverse NSMs back.
			for(i=0; i<nsmcnt; i++){	// copy NSMs to psz
				psz[sidx++] = nsmsz[i];
			}
			
			nsmcnt = 0;
			sidx = -1;
		}else{
			ich++;
		}
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
DT_void bidi_reverse_g2info(FontCodeInfo* pszg2info, DT32_int cch);
DT_void bidi_reverse_nsm_withg2info(DT16_ushort* psz, FontCodeInfo *pszg2info, DT32_int cch)
{
	DT16_ushort nsmsz[DLO_BIDI_MAX_NSM];	// a temp buffer for NSM code points (glyphs), assume 8 is enough
	FontCodeInfo nsmg2[DLO_BIDI_MAX_NSM];
	DT8_uchar	nsmcnt;
	DT32_int	i, sidx, ich = 0;

	bidi_reverse_g2info(pszg2info, cch);
	bidi_reverse(psz, cch);	// reverse the string

	// deal with NSM
	nsmcnt = 0;	
	sidx = -1;		// use -1 to represent it's not a NSM
	//DT_memset(nsmsz, 0, sizeof(nsmsz));		// 2012-02-06: not required.
	//DT_memset(nsmg2, 0, sizeof(nsmg2));		// 2012-02-06: not required.
	while(ich < cch)
	{
		if(NSM==bidi_ClassFromChWS(psz[ich]))
		{
			sidx = ich;		// encountered a NSM, keep its index.

			// count how many continuous NSMs are there.
			while( NSM==bidi_ClassFromChWS(psz[ich]) && ich < cch && nsmcnt < DLO_BIDI_MAX_NSM){
				nsmg2[nsmcnt] = pszg2info[ich];
				nsmsz[nsmcnt] = psz[ich];
				nsmcnt++;
				ich++;
			}
			// Set base glyph
			if(ich >= cch){				// the last glyph is a NSM

			}else{
				pszg2info[sidx] = pszg2info[ich];
				psz[sidx] = psz[ich];	// assume it's the base glyph of these NSMs.
				ich++;
				sidx++;
			}
			bidi_reverse_g2info(nsmg2, nsmcnt);
			bidi_reverse(nsmsz, nsmcnt);// reverse NSMs back.
			for(i=0; i<nsmcnt; i++){	// copy NSMs to psz
				pszg2info[sidx] = nsmg2[i];
				psz[sidx++] = nsmsz[i];
			}
			
			nsmcnt = 0;
			sidx = -1;
		}else{
			ich++;
		}
	}
}

DT32_int bidi_reorderLevel_nsm(DT32_int level, DT16_ushort* pszText, const DT32_int * plevel, DT32_int cch, DT_BOOL fReverse)
{
    DT32_int ich = 0;

    // true as soon as first odd level encountered
    fReverse = fReverse || DT_odd(level);
	
	for (; ich < cch; ich++)
    {
        if (plevel[ich] < level)
        {
            break;
        }
        else if (plevel[ich] > level)
        {
            ich += bidi_reorderLevel(level + 1, pszText + ich, plevel + ich, 
                cch - ich, fReverse) - 1;
        }
    }
    if (fReverse)
    {
		bidi_reverse_nsm(pszText, ich);
    }
    return ich;
}

DT32_int bidi_reorder_nsm(DT32_int baselevel, DT16_ushort* pszText, const DT32_int * plevel, DT32_int cch)
{
    DT32_int ich = 0;

    while (ich < cch)
    {
        ich += bidi_reorderLevel_nsm(baselevel, pszText + ich, plevel + ich, 
            cch - ich, DT_FALSE);
    }
    return ich;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// reverse cch characters 
DT_void bidi_reverse_cg(CodevsGlyph* pszCaret, DT32_int cch)
{
    CodevsGlyph chTemp;
	DT32_int ich = 0;
    for (; ich < --cch; ich++)
    {
        chTemp = pszCaret[ich];
        pszCaret[ich] = pszCaret[cch];
		pszCaret[ich].glyfidx = ich;
        pszCaret[cch] = chTemp;
		pszCaret[cch].glyfidx = cch;
    }
}

DT_void bidi_reverse_nsm_cg(CodevsGlyph* pszCaret, DT32_int cch, DT16_ushort *refText)
{
	CodevsGlyph nsmsz[DLO_BIDI_MAX_NSM];	// a temp buffer for NSM code points (glyphs), assume 8 is enough
											// use tempbuf in DTmanager instead.
	DT16_ushort	refnsm[DLO_BIDI_MAX_NSM];
	DT8_uchar	nsmcnt;
	DT32_int	i, sidx, ich = 0;

	bidi_reverse_cg(pszCaret, cch);	// reverse the string
	bidi_reverse(refText,cch);

	// deal with NSM
	nsmcnt = 0;	
	sidx = -1;		// use -1 to represent it's not a NSM
	//DT_memset(nsmsz, 0, sizeof(nsmsz));		// 2012-02-06: not required.
	//DT_memset(refnsm,0, sizeof(refnsm));		// 2012-02-06: not required.
	while(ich < cch)
	{
		if(NSM==bidi_ClassFromChWS(refText[ich]))
		{
			sidx = ich;		// encountered a NSM, keep its index.

			// count how many continuous NSMs are there.
			while( NSM==bidi_ClassFromChWS(refText[ich]) && ich < cch && nsmcnt < DLO_BIDI_MAX_NSM){
				nsmsz[nsmcnt] = pszCaret[ich];
				refnsm[nsmcnt]= refText[ich];
				nsmcnt++;
				ich++;
			}
			// Set base glyph
			if(ich >= cch){				// the last glyph is a NSM

			}else{
				pszCaret[sidx] = pszCaret[ich];	// assume it's the base glyph of these NSMs.
				pszCaret[sidx].glyfidx = sidx;
				refText[sidx]= refText[ich];
				ich++;
				sidx++;
			}
			bidi_reverse_cg(nsmsz, nsmcnt);// reverse NSMs back.
			bidi_reverse(refnsm, nsmcnt);
			for(i=0; i<nsmcnt; i++, sidx++){	// copy NSMs to psz
				pszCaret[sidx] = nsmsz[i];
				pszCaret[sidx].glyfidx = sidx;
				refText[sidx]  = refnsm[i];
			}
			
			nsmcnt = 0;
			sidx = -1;
		}else{
			ich++;
		}
	}
}

DT32_int bidi_reorderLevel_cg(DT32_int level, CodevsGlyph* pszCaret, const DT32_int * plevel, DT32_int cch, DT_BOOL fReverse, DT16_ushort *refText)
{
    DT32_int ich = 0;

    // true as soon as first odd level encountered
    fReverse = fReverse || DT_odd(level);
	
	for (; ich < cch; ich++)
    {
        if (plevel[ich] < level)
        {
            break;
        }
        else if (plevel[ich] > level)
        {
            ich += bidi_reorderLevel_cg(level + 1, pszCaret + ich, plevel + ich, 
                cch - ich, fReverse, refText + ich) - 1;
        }
    }
    if (fReverse)
    {
        //bidi_reverse(pszText, ich);
		bidi_reverse_nsm_cg(pszCaret, ich, refText);
    }
    return ich;
}

// pszCaret and refText are glyph based with the same count, and the index are matched.
DT32_int bidi_reorder_cg(DT32_int baselevel, CodevsGlyph* pszCaret, const DT32_int * plevel, DT32_int cch, DT16_ushort *refText)
{
    DT32_int ich = 0;

    while (ich < cch)
    {
        ich += bidi_reorderLevel_cg(baselevel, pszCaret + ich, plevel + ich, 
            cch - ich, DT_FALSE, refText + ich);
    }
    return ich;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// reverse cch characters 
DT_void bidi_reverse_caret_seq(DLO_CodePositioning* pszCaret, DT32_int cch)
{
    DLO_CodePositioning chTemp;
	DT32_int ich = 0;
    for (; ich < --cch; ich++)
    {
        chTemp = pszCaret[ich];
        pszCaret[ich] = pszCaret[cch];
		pszCaret[ich].glyfidx = ich;
        pszCaret[cch] = chTemp;
		pszCaret[cch].glyfidx = cch;
    }
}

DT_void bidi_reverse_g2info(FontCodeInfo* pszg2info, DT32_int cch)
{
    FontCodeInfo chTemp;
	DT32_int ich = 0;
    for (; ich < --cch; ich++)
    {
        chTemp = pszg2info[ich];
        pszg2info[ich] = pszg2info[cch];
        pszg2info[cch] = chTemp;
    }
}

DT_void bidi_reverse_nsm_caret_seq_g2info(DLO_CodePositioning* pszCaret, FontCodeInfo* pszg2info, DT32_int cch, DT16_ushort *refText)
{
	DLO_CodePositioning nsmsz[DLO_BIDI_MAX_NSM];	// a temp buffer for NSM code points (glyphs), assume DLO_BIDI_MAX_NSM is enough
													// use tempbuf in DTmanager instead.
	FontCodeInfo		nsmg2[DLO_BIDI_MAX_NSM];	// same as nsmsz
	DT16_ushort			refnsm[DLO_BIDI_MAX_NSM];
	DT8_uchar	nsmcnt;
	DT32_int	i, sidx, ich = 0;

	bidi_reverse_caret_seq(pszCaret, cch);	// reverse the string
	bidi_reverse_g2info(pszg2info, cch);
	bidi_reverse(refText,cch);

	// deal with NSM
	nsmcnt = 0;	
	sidx = -1;		// use -1 to represent it's not a NSM
	//DT_memset(nsmsz, 0, sizeof(nsmsz));		// 2012-02-06: not required.
	//DT_memset(nsmg2, 0, sizeof(nsmg2));		// 2012-02-06: not required.
	//DT_memset(refnsm,0, sizeof(refnsm));		// 2012-02-06: not required.
	while(ich < cch)
	{
		if(NSM==bidi_ClassFromChWS(refText[ich]))
		{
			sidx = ich;		// encountered a NSM, keep its index.

			// count how many continuous NSMs are there.
			while( NSM==bidi_ClassFromChWS(refText[ich]) && ich < cch && nsmcnt < DLO_BIDI_MAX_NSM){
				nsmsz[nsmcnt] = pszCaret[ich];
				nsmg2[nsmcnt] = pszg2info[ich];
				refnsm[nsmcnt]= refText[ich];
				nsmcnt++;
				ich++;
			}
			// Set base glyph
			if(ich >= cch){				// the last glyph is a NSM

			}else{
				pszCaret[sidx] = pszCaret[ich];	// assume it's the base glyph of these NSMs.
				pszCaret[sidx].glyfidx = sidx;
				pszg2info[sidx]= pszg2info[ich];
				refText[sidx]= refText[ich];
				ich++;
				sidx++;
			}
			bidi_reverse_caret_seq(nsmsz, nsmcnt);// reverse NSMs back.
			bidi_reverse_g2info(nsmg2, nsmcnt);
			bidi_reverse(refnsm, nsmcnt);
			for(i=0; i<nsmcnt; i++, sidx++){	// copy NSMs to psz
				pszCaret[sidx] = nsmsz[i];
				pszCaret[sidx].glyfidx = sidx;
				pszg2info[sidx]= nsmg2[i];
				refText[sidx]  = refnsm[i];
			}
			
			nsmcnt = 0;
			sidx = -1;
		}else{
			ich++;
		}
	}
}

DT32_int bidi_reorderLevel_caret_seq_g2info(DT32_int level, DLO_CodePositioning* pszCaret, FontCodeInfo* pszg2info, const DT32_int * plevel, DT32_int cch, DT_BOOL fReverse, DT16_ushort *refText, DT_BOOL fNsm)
{
    DT32_int ich = 0;

    // true as soon as first odd level encountered
    fReverse = fReverse || DT_odd(level);
	
	for (; ich < cch; ich++)
    {
        if (plevel[ich] < level)
        {
            break;
        }
        else if (plevel[ich] > level)
        {
            ich += bidi_reorderLevel_caret_seq_g2info(level + 1, pszCaret + ich, pszg2info + ich, plevel + ich, 
                cch - ich, fReverse, refText + ich, fNsm) - 1;
        }
    }
    if (fReverse)
    {
		if(!fNsm)
		{
			bidi_reverse(refText, ich);
			bidi_reverse_caret_seq(pszCaret,ich);
			bidi_reverse_g2info(pszg2info,ich);
		}else{
			bidi_reverse_nsm_caret_seq_g2info(pszCaret, pszg2info, ich, refText);
		}
    }
    return ich;
}

// pszCaret and refText are glyph based with the same count, and the index are matched.
DT32_int bidi_reorder_caret_seq_g2info(DT32_int baselevel, DLO_CodePositioning* pszCaret, FontCodeInfo* pszg2info, const DT32_int * plevel, DT32_int cch, DT16_ushort *refText, DT_BOOL fNsm)
{
    DT32_int ich = 0;

    while (ich < cch)
    {
        ich += bidi_reorderLevel_caret_seq_g2info(baselevel, pszCaret + ich, pszg2info + ich, plevel + ich, 
            cch - ich, DT_FALSE, refText + ich, fNsm);
    }
    return ich;
}

//DT_void bidi_reverse_gseq(GlyphSeq* pszCaret, DT32_int cch)
//{
//    GlyphSeq chTemp;
//	DT32_int ich = 0;
//    for (; ich < --cch; ich++)
//    {
//        chTemp = pszCaret[ich];
//        pszCaret[ich] = pszCaret[cch];
//		pszCaret[ich].idx_gseq2 = ich;
//        pszCaret[cch] = chTemp;
//		pszCaret[cch].idx_gseq2 = cch;
//    }
//}
//
//DT_void bidi_reverse_nsm_gseq(GlyphSeq* pszCaret, DT32_int cch, DT16_ushort *refText)
//{
//	GlyphSeq nsmsz[DLO_BIDI_MAX_NSM];	// a temp buffer for NSM code points (glyphs), assume 16 is enough
//											// use tempbuf in DTmanager instead.
//	DT16_ushort	refnsm[DLO_BIDI_MAX_NSM];
//	DT8_uchar	nsmcnt;
//	DT32_int	i, sidx, ich = 0;
//
//	bidi_reverse_gseq(pszCaret, cch);	// reverse the string
//	bidi_reverse(refText,cch);
//
//	// deal with NSM
//	nsmcnt = 0;	
//	sidx = -1;		// use -1 to represent it's not a NSM
//	DT_memset(nsmsz, 0, DLO_BIDI_MAX_NSM*sizeof(nsmsz[0]));
//	DT_memset(refnsm,0, DLO_BIDI_MAX_NSM*sizeof(refnsm[0]));
//	while(ich < cch)
//	{
//		if(NSM==bidi_ClassFromChWS(refText[ich]))
//		{
//			sidx = ich;		// encountered a NSM, keep its index.
//
//			// count how many continuous NSMs are there.
//			while( NSM==bidi_ClassFromChWS(refText[ich]) && ich < cch){
//				nsmsz[nsmcnt] = pszCaret[ich];
//				refnsm[nsmcnt]= refText[ich];
//				nsmcnt++;
//				ich++;
//			}
//			// Set base glyph
//			if(ich >= cch){				// the last glyph is a NSM
//
//			}else{
//				pszCaret[sidx] = pszCaret[ich];	// assume it's the base glyph of these NSMs.
//				pszCaret[sidx].glyfidx = sidx;
//				refText[sidx]= refText[ich];
//				ich++;
//				sidx++;
//			}
//			bidi_reverse_cg(nsmsz, nsmcnt);// reverse NSMs back.
//			bidi_reverse(refnsm, nsmcnt);
//			for(i=0; i<nsmcnt; i++, sidx++){	// copy NSMs to psz
//				pszCaret[sidx] = nsmsz[i];
//				pszCaret[sidx].glyfidx = sidx;
//				refText[sidx]  = refnsm[i];
//			}
//			
//			nsmcnt = 0;
//			sidx = -1;
//		}else{
//			ich++;
//		}
//	}
//}

extern DT_CodePair BidiMirrorArray[];
extern DT32_int	 gBidiMirror_ArraySize;
// === DISPLAY OPTIONS ================================================
DT32_int DTCodePair_bsearch(DT16_ushort key, DT_CodePair *data, DT32_int n, DT16_ushort *mirror)
{
	DT32_int mid, low = 0, high = n - 1;

DBG_MSG_SHOW_FUNC_NAME();
	
    while (low <= high)
    {
        mid = (low + high) / 2;

        if (data[mid].code == key)
        {
			if(mirror){
				*mirror = data[mid].mirror;
			}
            return mid;
        }
        else if (data[mid].code > key)
        {
            high = mid - 1;
        }
        else if (data[mid].code < key)
        {
            low = mid + 1;
        }
    }

    return -1;
}

DT16_ushort bidi_getMirrorCode(DT16_ushort ch)
{
	DT16_ushort mirror = 0;		// 0 means not found
	DT16_ushort	plane  = 0x0000;// Base ASCII
	
DBG_MSG_SHOW_FUNC_NAME();

#if (DT_CODE_ASCII_IN_PUA==0xE400)
	if(ch >= 0xE420 && ch <= 0xE47F){
		plane = 0xE400;
		ch -= plane;
	}else
#endif
	if(ch >= 0xFF01 && ch <= 0xFF5E){		// Fullwidth ASCII
		plane = 0xFEE0;
		ch -= plane;
	}

	if( ch < 0x007F	){
		switch(ch){
		case 0x0028:
			return plane+0x0029;
		case 0x0029:
			return plane+0x0028;
		case 0x003C:
			return plane+0x003E;
		case 0x003E:
			return plane+0x003C;
		case 0x005B:
			return plane+0x005D;
		case 0x005D:
			return plane+0x005B;
		case 0x007B:
			return plane+0x007D;
		case 0x007D:
			return plane+0x007B;
		default:
			return 0;	// not found
		}
	}

	if( 0 > DTCodePair_bsearch( ch, BidiMirrorArray, gBidiMirror_ArraySize, &mirror))
	{
		// Not found
	}else{
		// found
	}

	return mirror;
}
/*-----------------------------------------------------------------------
   Function:	mirror

    Crudely implements rule L4 of the Unicode Bidirectional Algorithm
    Demonstrate mirrored brackets, braces and parens
   

    Input:	Array of levels
		    Count of characters

    In/Out:	Array of characters (should be array of glyph ids)

	Note;
	A full implementation would need to substitute mirrored glyphs even
    for characters that are not paired (e.g. integral sign).
-----------------------------------------------------------------------*/
DT_void bidi_mirror(DT16_ushort* pszInput, const DT32_int * plevel, DT32_int cch)
{
    DT32_int ich = 0;
	DT16_ushort mirror = 0;
	for (; ich < cch; ich ++)
    {
        if (!DT_odd(plevel[ich]))
            continue;
	
//		if( 0 > DTCodePair_bsearch( pszInput[ich], BidiMirrorArray, gBidiMirror_ArraySize, &mirror))
//		{
//			// Not found
//		}else{
//			// found
//			pszInput[ich] = mirror;
//		}

		mirror = bidi_getMirrorCode(pszInput[ich]);
		if(mirror > 0)
			pszInput[ich] = mirror;

//        if (pszInput[ich] == '<')
//        {
//            pszInput[ich] = '>';
//        } 
//        else if (pszInput[ich] == '>')
//        {
//            pszInput[ich] = '<';
//        }
//        else if (pszInput[ich] == ')')
//        {
//            pszInput[ich] = '(';
//        }
//        else if (pszInput[ich] == '(')
//        {
//            pszInput[ich] = ')';
//        }
    }
}

/*-----------------------------------------------------------------------
	Function: bidi_clean

	remove formatting codes    

    In/Out:	Array of characters
		    Count of characters

	Note;

	This function can be used to remove formatting codes so the 
	ordering of the string can be compared to implementations that 
	remove formatting codes. This implementation is limited to the
	pseudo alphabet used for the demo version.

-----------------------------------------------------------------------*/
//DT32_int bidi_clean(DT16_ushort* pszInput, DT32_int cch)
//{
//    DT32_int cchMove = 0;
//    DT32_int ich = 0;
//	for (; ich < cch; ich ++)
//    {
//		DT32_int ch = pszInput[ich];
//		switch (ch) 
//		{
//		default:
//			if (pszInput[ich] < 0x20)
//			{
//				cchMove++;
//			}
//			else
//			{
//				pszInput[ich - cchMove] = pszInput[ich];
//			}
//			break;
//		case chRLO:
//		case chLRO:
//		case chRLE:
//		case chLRE:
//		case chPDF:
//		case chBN:
//			cchMove++;
//			break;
//		}
//    }
//    pszInput[ich - cchMove] = 0;
//    return ich - cchMove;
//}


/*------------------------------------------------------------------------
    Function: BidiLines
    
    Implements the Line-by-Line phases of the Unicode Bidi Algorithm 

  	Input:	 Count of characters
			 flag whether to mirror

	Inp/Out: Input text
			 Array of character directions
			 Array of levels
			
------------------------------------------------------------------------*/
DT_void bidi_BidiLines(DT32_int baselevel, DT16_ushort * pszLine, DT32_int * pclsLine, 
				  DT32_int * plevelLine, DT32_int cchPara, DT32_int fMirror, DT_BOOL * pbrk)
{
	DT32_int cchLine = 0;

	do
	{
		// break lines at LS
		cchLine = bidi_resolveLines(pszLine, pbrk, cchPara);

		// resolve whitespace
		bidi_resolveWhitespace(baselevel, pclsLine, plevelLine, cchLine);

    
		if (fMirror)
		{
			bidi_mirror(pszLine, plevelLine, cchLine);
		}

		// reorder each line in place
		bidi_reorder(baselevel, pszLine, plevelLine, cchLine);

		pszLine += cchLine;
		plevelLine += cchLine;
		pbrk += pbrk ? cchLine : 0;
		pclsLine += cchLine;
		cchPara -= cchLine;

	} while (cchPara);
}

/*------------------------------------------------------------------------
	Function: bidi_BidiParagraph

	Implements the per paragraph phases of the Unicode Bidi Algorithm

	Input:	
			 Count of characters

	Inp/Out: Input text
			 Base paragraph level (negative value on input means implicit)
			 Array of character directions
			 Array of levels

	Returns: The number of input characters processed for this paragraph

	Note:	 This function is not called by the demo code in this file, but 
			 provided here for completeness. It has been tested by being
			 used in the verfication code.
------------------------------------------------------------------------*/
DT32_int bidi_BidiParagraph(DT32_int *baselevel,  DT32_int * types, DT32_int * levels, DT32_int cch)
{
	DT32_int cchPara;
	// set baselevel
	if (*baselevel < 0)
		*baselevel = bidi_baseLevel(types, cch);
	
	// change B into BN and return length including
	cchPara = bidi_resolveParagraphs(types, cch);
	
	// resolve explicit
	bidi_resolveExplicit(*baselevel, N, types, levels, cchPara, 0);

	// resolve weak
	bidi_resolveWeak(*baselevel, types, levels, cchPara);

	// resolve neutrals
	bidi_resolveNeutrals(*baselevel,types, levels, cchPara);

	// resolveImplicit
	bidi_resolveImplicit(types, levels, cchPara);

	// return the part of the input processed so far
	return cchPara;
}

// ===== FUNCTIONS FOR COMMAND LINE VERSION ==============================

//#include <stdlib.h>
//#include <string.h>
//// An alternate CharFromTypes array may be needed to use the command 
//// line version,
//#define MAX_CCH 256
//void ShowInputTypes(FILE* f, LPTSTR pszInput, int cch)
//{
//    TCHAR pszTypes[MAX_CCH+1];
//    
//	int ich = 0;
//	for (; ich < cch; ich++)
//    {
//         pszTypes[ich] = CharFromTypes[ClassFromChWS(pszInput[ich])];
//    }
//    pszTypes[ich] = 0;
//        fprintf(f, pszTypes);
//}
//void ShowTypes(FILE* f, int * types, int cch)
//{
//    TCHAR pszTypes[MAX_CCH+1];
//    int ich = 0;
//	for (; ich < cch; ich++)
//    {
//         pszTypes[ich] = CharFromTypes[types[ich]];
//    }
//    pszTypes[ich] = 0;
//        fprintf(f, pszTypes);
//}
//void ShowLevels(FILE* f, int * levels, int cch)
//{
//	 #if DEMO
//	 // do nothing if levels are not limited to 15 as for debugging
//	 // since we can't show 0-61 in a single character
//	 TCHAR pszLevel[MAX_CCH+1];
//     int ich = 0;
//	 for (; ich < cch; ich++)
//     {
//          pszLevel[ich] = CharFromLevel[levels[ich]];
//     }
//     pszLevel[ich] = 0;
//        fprintf(f, pszLevel);
//	#else
//		// squelch compiler warnings
//		f; levels; cch;
//	#endif
//}
//void usage(char *s) 
//{
//    printf("Usage: %s [-verbose] [-nomirror] [-level #] [-clean] strings...\n", s);
//    printf("\t-verbose = verbose debugging output.\n");
//	printf("\t-level # = specify # as the base level.\n");
//    printf("\t-nomirror = refrain from glyph mirroring.\n");
//    printf("\t-clean = clean up the result.\n");
//    printf("\tOptions affect all subsequent arguments.\n");
//    printf("\tAll other arguments are interpreted as strings to process.\n");
//}
//int main(int argc, char** argv) 
//{
//    DT32_int realArg = 0;
//    DT32_int doMirror = 1;
//    DT32_int doClean = 0;
//	DT32_int doLevel = 1;
//	DT32_int baselevel = 0;
//    DT32_int beVerbose = 0;
//	DT32_int i, cch;
//	DT16_ushort pszInput[MAX_CCH+1];
//	DT32_int types[MAX_CCH];
//	DT32_int levels[MAX_CCH];
//    
//    DT_FILE* f = stdout;
//    if (argc == 1) 
//	{
//		usage(argv[0]); exit(0);
//    }
//    for (i = 1; i < argc; ++i) 
//	{
//		if (doLevel == -1)
//		{
//			baselevel = atoi(argv[i]);
//			doLevel = 0;
//			continue;
//		}
//		else if (strcmp(argv[i], "-verbose") == 0) 
//		{
//			beVerbose = 1;
//			continue;
//		} 
//		else if (strcmp(argv[i], "-nomirror") == 0) 
//		{
//			doMirror = 0;
//			continue;
//		} 
//		else if (strcmp(argv[i], "-clean") == 0) 
//		{
//			doClean = 1;
//			continue;
//		} 
//		else if (strcmp(argv[i], "-level") == 0) 
//		{
//			if (argc - 1 == i)
//			{
//				usage(argv[0]); exit(0);
//			}
//			doLevel = -1;
//			continue;
//		} 
//		else 
//		{
//			++realArg;
//		}
//    
//		cch = strlen(argv[i]);
//		if (cch > MAX_CCH) cch = MAX_CCH;
//		strncpy(pszInput, argv[i], cch);
//    
//		pszInput[cch] = 0;
//		fprintf(f, "Input    %2d: %s\n", realArg, pszInput);
//    
//  
//		// assign directional types
//		bidi_classify(pszInput, types, cch, DT_FALSE);
//    
//		if (beVerbose) 
//		{
//			fprintf(f, "Input Types: ");
//			ShowInputTypes(f, pszInput, cch); fprintf(f, "\n");
//		}
//    
//		// limit text to first block
//		cch = resolveParagraphs(types, cch);
//    
//		// set base level
//		if (doLevel)
//			baselevel = baseLevel(types, cch);
//		if (beVerbose) 
//		{
//			fprintf(f, "Base Level : %d\n", baselevel);
//		}
//    
//		// resolve explicit
//		resolveExplicit(baselevel, N, types, levels, cch, 0);
//    
//		if (beVerbose) 
//		{
//			fprintf(f, "Levels (A) : ");
//			ShowLevels(f, levels, cch); fprintf(f, "\n");
//		}
//    
//		// resolve weak
//		resolveWeak(baselevel, types, levels, cch);
//    
//		if (beVerbose) 
//		{
//			fprintf(f, "Types (A)  : ");
//			ShowTypes(f, types, cch); fprintf(f, "\n");
//		}
//    
//		// resolve neutrals
//		resolveNeutrals(baselevel,types, levels, cch);
//    
//		if (beVerbose) 
//		{
//			fprintf(f, "Types (B)  : ");
//			ShowTypes(f, types, cch); fprintf(f, "\n");
//		}
//    
//		// resolveImplicit
//		resolveImplicit(types, levels, cch);
//    
//		if (beVerbose) 
//		{
//			fprintf(f, "Levels (B) : ");
//			ShowLevels(f, levels, cch); fprintf(f, "\n");
//		}
//    
//		// assign directional types again, but for WS, S this time
//		bidi_classify(pszInput, types, cch, DT_TRUE);
//    
//		BidiLines(baselevel, pszInput, types, levels, cch, doMirror, 0);
//    
//		if (doClean) 
//		{ 
//			cch = bidi_clean(pszInput, cch); 
//		}
//    		fprintf(f, "Output   %2d: %s\n\n", realArg, pszInput);
//    }
//
//	printf("Press Enter to exit!\n");
//	getchar();
//    return 0;
//}

//[EOF]
