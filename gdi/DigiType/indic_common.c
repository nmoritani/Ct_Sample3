#include "indic_common.h"

/*
	Binary search for half table.
*/
UNI_CHAR lookup_consonants_table(UNI_CHAR A,  HALF_ROW * p_half_table, DT32_int length)
{
	HALF_ROW * p_half_row = p_half_table;
	DT32_int start, end, half_idx;;
	start=0;
	end = length -1;
	while(start <= end)
	{
		half_idx = (start+end) /2;
		if( (p_half_row+half_idx)->A <A ){
			start = half_idx+1;
		}
		else if( (p_half_row+half_idx)->A >A )
		{
			end = half_idx-1;
		}
		else if( (p_half_row+half_idx)->A == A )
		{
			return (p_half_row+half_idx)->B;
		}
	}
	return DEVA_EMPTY;
}


/*
	Binary search for ligature table.
*/
UNI_CHAR lookup_liga_table(UNI_CHAR A, UNI_CHAR B, P_LIGA_ROW p_liga_row, DT32_int length)
{
/*	LIGA_ROW * p_row = p_liga_row;*/
	DT32_int half_idx;
	DT32_int start, end;
	start=0;
	end = length -1;
	while(start <= end)
	{
		half_idx = (start+end) /2;
		if( ( (p_liga_row+half_idx)->A < A) || 
			( (p_liga_row+half_idx)->A == A && (p_liga_row+half_idx)->B < B))
		{
				start = half_idx+1;
		}
		else if( (p_liga_row+half_idx)->A > A || 
			( (p_liga_row+half_idx)->A == A && (p_liga_row+half_idx)->B > B) )
		{
				end = half_idx-1;
		}
		else if( (p_liga_row+half_idx)->A == A && (p_liga_row+half_idx)->B == B)
		{
		
				return (p_liga_row+half_idx)->C;
		}
	}

	return DEVA_EMPTY;
}


/*
	Binary search for tri_liga table.
*/
UNI_CHAR lookup_tri_liga_table(UNI_CHAR A, UNI_CHAR B, UNI_CHAR C, P_LIGA_TRI_ROW p_tri_liga_row, DT32_int length)
{
	DT32_int half_idx;
	DT32_int start, end;
	P_LIGA_TRI_ROW p; 
	start=0;
	end = length -1;
	while(start <= end)
	{
		half_idx = (start+end) /2;
		p = p_tri_liga_row+half_idx;
		if( ( p->A < A) || 
			( p->A == A && p->B < B) ||
			( p->A == A && p->B == B && p->C < C) )
		{
				start = half_idx+1;
		}
		else if( p->A > A || 
			( p->A == A && p->B > B) ||
			( p->A == A && p->B == B && p->C > C) )
		{
				end = half_idx-1;
		}
		else if( p->A == A && p->B == B && p->C == C)
		{
				return p->D;
		}
	}
	return DEVA_EMPTY;
}



/*Binary search for check table*/
DT_BOOL lookup_check_table(UNI_CHAR A,  UNI_CHAR * p_check_table, DT32_int length)
{
	UNI_CHAR * p_check_row = p_check_table;
	DT32_int start, end, half_idx;
	start=0;
	end = length-1;
	while(start <= end)
	{
		half_idx = (start+end) /2;
		if( *(p_check_row+half_idx) <A ){
			start = half_idx+1;
		}
		else if( *(p_check_row+half_idx) >A )
		{
			end = half_idx-1;
		}
		else if( *(p_check_row+half_idx) == A )
		{
			return TRUE;
		}
	}
	return FALSE;
}
/*
	@Function: lookup_spliter_table, look up split two part vowel table 
			   to find be splittedtwo parts. 
	@Parameter: uOrg, Input two part vowel
				p_split_tow_part_table, mapping table which relation of vowels 
										and parts of them.
				length, size of p_split_tow_part_table pointing table.
	@Return: A pointer to relative pair.
			 SUCCESS, not NULL.
	@Note: It only return one pointer.
*/

PAIR * lookup_spliter_table(UNI_CHAR u_org, SPLIT_TWO_PART * p_split_tow_part_table,
							DT32_int length)
{
	DT32_int start, end, half_idx;
	SPLIT_TWO_PART * p_split_tow_part_row = p_split_tow_part_table;
	start=0;
	end = length=1;
	while(start <= end)
	{
		half_idx = (start+end) /2;
		if((p_split_tow_part_row+half_idx)->ORG < u_org) 
		{
				start = half_idx+1;
		}
		else if( (p_split_tow_part_row+half_idx)->ORG > u_org) 
		{
				end = half_idx-1;
		}
		else if( (p_split_tow_part_row+half_idx)->ORG == u_org )
		{
				return &((p_split_tow_part_row+half_idx)->TWO_PART);
		}
	}
	return NULL; 
}


/*@Function:lookup_complex_table, lookup complex ligature table
			the table format is, substitution,
			words of length , c1 of works, c2 of works...,
			as 0xee22,4,0x0bb8,0x0bcd,0x0bb0,0xbc0, represent a statement.
			and the ending of table making 0x00.
			As the statement,If it find data, it return a pointer to 0xee22.
  @Parameter: p_uorg,point to comparing string.
			  org_length, the length of p_uorg pointing string.
			  p_complex_table, point to specific table.
			  length, the size of p_complex_table pointing the table.
  @Return: SUCCESS, not NULL.
		  		
  @Note: It only return one pointer.		
*/

UNI_CHAR * lookup_complex_table(UNI_CHAR * p_uorg, DT32_int org_length, 
					 COMPLEX_LIGA * p_complex_table, DT32_int length)
{
	DT32_int i,j;
	DT_BOOL bfind;
	COMPLEX_LIGA * p = p_complex_table;
	
	i=0;j=0;
	while(i<length)
	{
		p = p_complex_table+i;
		if(*p== 0x0){
			break;
		}
		else if(*(p+1) <= org_length){
			bfind= TRUE;
			for(j=0; j<*(p+1); j++)
			{
				if(*(p+j+2) == p_uorg[j]){
					continue;
				}
				else{
					bfind =FALSE;
					break;
				}
			}
			if(bfind == TRUE){
				return p;
			}else;
		}else;
		i+= (*(p+1)+2);	
	}
	return NULL;
}
/*--------------------------------------------------------------------*/


UNI_CHAR lookup_complex_table_ex(UNI_CHAR * p_uorg, DT32_int org_length, 
					 COMPLEX_LIGA * p_complex_table, DT32_int length, DT32_int *pstr_end_idx)
{
	DT32_int i,j;
	DT_BOOL bfind;
	COMPLEX_LIGA * p = p_complex_table;
	UNI_CHAR * pstr;
	DT32_int idx;
	
	i=0;j=0;
	while(i<length)
	{
		p = p_complex_table+i;
		idx =0;
		pstr = p_uorg;
		if(*p== 0x0){
			break;
		}
		else if(*(p+1) <= org_length){
			bfind= TRUE;
			for(j=0; j<*(p+1); j++)
			{
				if(idx>org_length)
				{
					bfind =FALSE;
					break;
				}
				else
				{
					while(idx<(org_length-1))
					{
						if( pstr[idx] ==0)
						{
							idx++;
							continue;
						}
						else
							break;
					}
				}
			
				if(*(p+j+2) == pstr[idx]){
					idx++;
				}
				else{
					bfind =FALSE;
					break;
				}
			}
			if(bfind == TRUE){
				{
					*pstr_end_idx = idx-1;
					return *p;
				}
			}else;
		}else;

		i+= (*(p+1)+2);	
	}
	*pstr_end_idx = -1;
	return DEVA_EMPTY;
}



UNI_CHAR lookup_liga_2_table(UNI_CHAR A, UNI_CHAR B, P_LIGA_2_ROW p_liga_2_row_table, DT32_int length)
{
	DT32_int start, end, half_idx;
	P_LIGA_2_ROW p_liga_2_row = p_liga_2_row_table;
	start=0;
	end = length-1;
	while(start <= end)
	{
		half_idx = (start+end) /2;
		if((p_liga_2_row+half_idx)->ORG < A) 
		{
				start = half_idx+1;
		}
		else if( (p_liga_2_row+half_idx)->ORG > A) 
		{
				end = half_idx-1;
		}
		else if( (p_liga_2_row+half_idx)->ORG == A )
		{
			return lookup_consonants_table(B,
				(p_liga_2_row+half_idx)->P_SECOND_ROW, 
				(p_liga_2_row+half_idx)->TABLESIZE);		
		}
	}
	return DEVA_EMPTY; 
}

/*--------------------------------------------------------------------*/
DT_void indic_init_out_syllable(s_out_syllable * p_out_syllable, UNI_CHAR * p_unitxt)
{
	p_out_syllable->p_unitxt = p_unitxt;
	/*Initialize value*/
	p_out_syllable->f_special_part = 0;
	p_out_syllable->pre_special_part = 0;
	SET_IDX_LAST_CONSONANT(*p_out_syllable, IDX_NONE);
	SET_IDX_HALF_REPH_SUB(*p_out_syllable, IDX_NONE);
	SET_IDX_SIGNS (*p_out_syllable, IDX_NONE);
	SET_LENGTH(*p_out_syllable, 0);
	SET_IDX_BEGIN(*p_out_syllable,IDX_NONE);
	SET_IDX_END(*p_out_syllable,IDX_NONE);
	SET_IDX_DEPENDENT_VOWEL(*p_out_syllable,IDX_NONE);
	SET_IDX_CANDRA_SIGNS(*p_out_syllable,IDX_NONE);

	/*set flags false.*/	
	SET_SECIAL_PART_FALSE(*p_out_syllable);
	
	/*set flags false.*/
	/*
	SET_REPH_SUP_FALSE( *p_out_syllable);
	SET_REPH_SUB_FALSE( *p_out_syllable);
	SET_PREVOWEL_FALSE( *p_out_syllable);
	SET_NUKTA_FALSE(*p_out_syllable);
	SET_PREDEPENDENT_NUKTA_FALSE(*p_out_syllable);*/

}

DT_void assert(DT32_int n)
{
	return ;
}

DT16_ushort Read_UShort(DT8_char * pdata, DT32_int ofs)
{
	DT16_ushort uval;
	DT8_uchar *p;
	p = (DT8_uchar*)pdata+ofs;
	uval = *p + ((DT16_ushort)*(p+1)<<8);
	return uval;
}

DT32_uint Read_uInt(DT8_char * pdata, DT32_int ofs)
{
	DT32_uint uval;
	DT8_uchar *p;
	p = (DT8_uchar*)pdata+ofs;
	uval = *p + ((DT32_uint)*(p+1)<<8) + ((DT32_uint)*(p+2)<<16) + ((DT32_uint)*(p+3)<<24);
	return uval;
}

//DT_void Read_xxx(DT8_char * pdata, DT32_int ofs, DT8_char * pdesc, DT16_ushort size)
//{
//	DT32_int i=0;
//	DT8_char *p;
//	p = pdata+ofs;
//	for(i=0; i<size; i++)
//	{
//		*pdesc++ = *p++;
//	}
//}

DT16_ushort getSubVowel_st(DT8_char * pdata, DT16_ushort vowel, DT16_ushort consonant)
{
/*
this function binary search
*/
	DT32_int i;
	DT16_ushort cnt_table;
	DT16_ushort name_len;
	DT16_ushort cnt_item;
	DT16_ushort table_vowel;
	DT32_uint table_offset;
	DT32_int ofs_table_offset; 
	DT32_int ofs=0;
	DT16_ushort item;
	DT8_char* ptable, *ptable_item_start;

	DT32_int start, end, half_idx;
	cnt_table = Read_UShort(pdata, ofs);
	ofs+=2;
	ofs_table_offset = ofs;
	for(i=0; i<cnt_table; i++)
	{
		table_offset = Read_uInt(pdata, ofs_table_offset+i*4);

		ptable = pdata+table_offset;
		ofs = 0;
		name_len = Read_UShort(ptable, ofs);
		ofs+=2;
		ofs+=name_len;
		table_vowel = Read_UShort(ptable, ofs);
		if(vowel!= table_vowel)
			continue;
		ofs+=2;
		cnt_item = Read_UShort(ptable, ofs);
		ofs+=2;

		ptable_item_start = ptable+ofs;
		/*binary search*/
		start=0;
		end = cnt_item-1;
		while(start <= end)
		{
			half_idx = (start+end)/2;
			item = Read_UShort(ptable_item_start, half_idx*4);
			if(item < consonant ){
				start = half_idx+1;
			}
			else if( item > consonant )
			{
				end = half_idx-1;
			}
			else if( item == consonant )
			{
				return Read_UShort(ptable_item_start, half_idx*4+2);
			}
		}
	}
	return 0;
}

DT32_int getPosAdjustment_st(char * pdata, DT16_ushort base, DT16_ushort sign, DT16_short *poffsetx, DT16_short *poffsety, DT32_int table_begin_index, DT32_int table_end_index)
{
	/*
		this is serial search.
	*/
	DT32_int i,j;
	DT32_int ret = -1;
	DT16_ushort cnt_table;
	DT32_uint table_offset;
	DT32_int ofs_table_offset; 
	DT16_ushort cnt_item_m, cnt_item_n;
	DT8_char* ptable,* pbase, * pmark, *pbasemark;
	DT8_char* ptable_item_start;
	DT16_ushort mark_base_block_size;
	DT32_int start, end;
	DT16_ushort half_item;
	DT32_int idx_mark = -1, idx_base = -1;
	DT32_int ofs=0;
	DT16_short base_x =0, base_y=0, mark_x =0, mark_y=0;

	cnt_table = Read_UShort(pdata, ofs);
	HINDI_ASSERT(cnt_table>= 255);
	ofs+=2;
	ofs_table_offset = ofs;

	i = table_begin_index;
	if(i<0) 
		i=0;
	if(table_end_index < cnt_table)
		cnt_table = (DT16_ushort)(table_end_index+1); 

	for(;i<cnt_table; i++)
	{
		table_offset = Read_uInt(pdata,ofs_table_offset+i*4);
		ptable = pdata+table_offset;
		ofs = 0;
		cnt_item_m = Read_UShort(ptable, ofs);
		ofs += 2;
		cnt_item_n = Read_UShort(ptable, ofs);
		ofs += 2;
		pbase = ptable+ofs;
		pmark = pbase+ 6*cnt_item_m;
		pbasemark = pmark+2*cnt_item_n;

		mark_base_block_size = (DT16_ushort) (cnt_item_n*4);
	
		idx_mark = -1, idx_base = -1;
		/*binary search mark*/
		start=0;
		end = cnt_item_n-1;
		ptable_item_start = pmark;
	
		for(j=0; j<cnt_item_n; j++)
		{
			half_item = Read_UShort(ptable_item_start, j*2);
			if( half_item == sign){
				idx_mark = j;	
				break;
			}
		}

		
		if(idx_mark>=0)
		{
			start=0;
			end = cnt_item_m-1;
			ptable_item_start = pbase; 
			for(j=0;j<cnt_item_m; j++)	
			{
				half_item = Read_UShort(ptable_item_start, j*6);
				if( half_item == base){
					base_x = Read_UShort(pbase, j*6+2);
					base_y = Read_UShort(pbase, j*6+4);
					idx_base = j;
					break;
				}
			}
			if(idx_base>=0)
			{
				mark_x = Read_UShort(pbasemark, mark_base_block_size*idx_base+idx_mark*4);
				mark_y = Read_UShort(pbasemark, mark_base_block_size*idx_base+idx_mark*4+2);
				*poffsetx = (DT16_short) ( base_x - mark_x);
				*poffsety = (DT16_short) ( base_y - mark_y);
				ret = 0;
				break;
			}
		}
	}
	return ret;
}

