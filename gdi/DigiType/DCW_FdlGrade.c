
#include "Dcw.h"


#define BETWEEN(n, min, max)    ((n) >= (min) && (n) <= (max))

static DT32_int  FG_Get(pFdlGradeData fgdata, DT16_WORD *idx, pFGXPair *pair);
static DT_void FG_Free(pFdlGradeData fgdata, DT16_WORD idx);
/*static DT_void FG_Check(pFdlGradeData fgdata);*/


/*---------------------------------------------------------------------------*/
DT_void FG_Initial(pFdlGradeData fgdata, DT32_int yt, DT32_int yb, DT8_char *mem, DT32_long memsize, DT_void *wrk)
{
	DT32_int  lcnt = yb - yt + 1;
	DT32_long lsize = lcnt * sizeof(DT16_WORD)*2;

DBG_MSG_SHOW_FUNC_NAME();

	if(lsize > memsize)	
		lsize = memsize;

	fgdata->wrk       = wrk;
	fgdata->yt        = (DT16_short)yt;
	fgdata->yb        = (DT16_short)yb;
	fgdata->memsize   = memsize;
	fgdata->linecnt   = (DT16_WORD)lcnt;
	fgdata->line      = (DT16_WORD*)mem;
	fgdata->linelast  = (DT16_WORD*)(mem+lsize/2);	// Alan.
	fgdata->pool      = (pFGXPair)(mem + lsize);
	fgdata->freemax   = (DT16_WORD)((memsize - lsize) / sizeof(TFGXPair));
	fgdata->freelist  = 0;
	fgdata->recycle   = 0xffff;

	/* DT_memset(fgdata->line, 0xff, lsize); */
	DT_memset(fgdata->line, 0xff, lsize);		// Clear fgdata->line and fgdata->linelast. 
}
/*---------------------------------------------------------------------------*/
//#ifdef myDT_DBGMSG
//#include <dbg.h>
//DT16_WORD freelist_maxrecord = 0;
//#endif

DT32_int FG_Get(pFdlGradeData fgdata, DT16_WORD *idx, pFGXPair *pair)
{
DBG_MSG_SHOW_FUNC_NAME();

//#ifdef myDT_DBGMSG
//if(fgdata->freelist > freelist_maxrecord){
//	freelist_maxrecord = fgdata->freelist;
//	DBG("fgdata.freelist >= freemax: code=0x%04X, freelist=%d\n", ((pDcwWrk)fgdata->wrk)->fdl.fontidx, freelist_maxrecord);
//}
//#endif

	if(fgdata->freelist >= fgdata->freemax)						// Alan.
	{
		if(fgdata->recycle != 0xffff)
		{
			*idx = fgdata->recycle;
			*pair = &fgdata->pool[*idx];
			fgdata->recycle = (*pair)->next;

			return 1;
		}else
		{
			*idx = 0xffff;
			*pair = NULL;
			return 0;
		}// end if
	}else
	{	// Alan.
		*idx = fgdata->freelist++;
		*pair = &fgdata->pool[*idx];
		return 1;
	}// end if

}// end FG_Get

/*---------------------------------------------------------------------------*/
DT_void FG_Free(pFdlGradeData fgdata, DT16_WORD idx)
{
DBG_MSG_SHOW_FUNC_NAME();

	if(fgdata->recycle != 0xffff)
		fgdata->pool[idx].next = fgdata->recycle;
	else
		fgdata->pool[idx].next = 0xffff;

	fgdata->recycle = idx;
}

/*---------------------------------------------------------------------------*/
#if 1

DT32_int FG_Add(pFdlGradeData fgdata, DT32_int y, DT32_int xl, DT32_int xr)
{
	DT32_int lineidx = y - fgdata->yt;
	DT16_WORD idx, idx2;
	pFGXPair pair, pair1, pair2;

DBG_MSG_SHOW_FUNC_NAME();

	if(lineidx < 0 || lineidx >= fgdata->linecnt)
		return 1;

	idx2 = fgdata->line[lineidx];
	if(idx2 == 0xffff)
	{// add first
		if(!FG_Get(fgdata, &idx, &pair))
			return 0;
		pair->xl    = (DT16_short)xl;
		pair->xr    = (DT16_short)xr;
		pair->next  = 0xffff;

		fgdata->line[lineidx] = idx;
		fgdata->linelast[lineidx] = idx;
	}else if( xl > fgdata->pool[ fgdata->linelast[lineidx] ].xr )
	{
		if(!FG_Get(fgdata, &idx, &pair))
			return 0;
		pair->xl    = (DT16_short)xl;
		pair->xr    = (DT16_short)xr;
		pair->next  = 0xffff;

		fgdata->pool[ fgdata->linelast[lineidx] ].next = idx;
		fgdata->linelast[lineidx] = idx;
	}else
	{
		pair1 = NULL;
		do
		{
			pair2 = &fgdata->pool[idx2];
			if(xr < pair2->xl-1)
			{	// insert before
				if(!FG_Get(fgdata, &idx, &pair))
					return 0;
				pair->xl    = (DT16_short)xl;
				pair->xr    = (DT16_short)xr;
				pair->next  = idx2;

				if(pair1 == NULL)
					fgdata->line[lineidx] = idx;
				else
					pair1->next	= idx;
				break;
			}else if(xr <= pair2->xr)
			{	// merge
				if(xl < pair2->xl)
					pair2->xl = (DT16_short)xl;
				break;
			}else if(xl <= pair2->xr+1 && xr > pair2->xr)
			{	// merge
				DT16_WORD idx0 = idx2;
				if(xl < pair2->xl)
					pair2->xl = (DT16_short)xl;
				if(xr > pair2->xr)
					pair2->xr = (DT16_short)xr;

				// merge next scanline
				idx2 = pair2->next;
				while(idx2 != 0xffff)
				{
					pair1 = pair2;
					pair2 = &fgdata->pool[idx2];
					if(pair2->xl <= pair1->xr+1)
					{
						if(xr < pair2->xr)
							pair1->xr = pair2->xr;
						pair1->next = pair2->next;
						FG_Free(fgdata, idx2);

						pair2 = pair1;
						idx2 = pair1->next;
					}else break;
				}// end while

				if(fgdata->pool[idx0].next == 0xffff)
					fgdata->linelast[lineidx] = idx0;
				break;
			}else if(pair2->next == 0xffff)
			{	// insert last
				if(!FG_Get(fgdata, &idx, &pair))
					return 0;
				pair->xl    = (DT16_short)xl;
				pair->xr    = (DT16_short)xr;
				pair->next  = 0xffff;

				pair2->next = idx;
				fgdata->linelast[lineidx] = idx;
				break;
			}else
			{// next scanline
				pair1 = pair2;
				idx2 = pair1->next;
			}// end if
		} while(1);
	}// end if

	return 1;
}

#else

DT32_int count ;
FG_AddFist()
{
	count++;
}

FG_InsertBefore()
{
	count++;
}

FG_Dispear()
{
	count++;
}

FG_Merge()
{
	count++;
}
FG_InsertLast()
{
	count++;
}
FG_InsertLastsss()
{
	count++;
}
DT32_int count1;
DT32_int FG_Add(pFdlGradeData fgdata, DT32_int y, DT32_int xl, DT32_int xr)
{
	DT32_int lineidx = y - fgdata->yt;
	DT16_WORD idx, idx2;
	pFGXPair pair, pair1, pair2;

DBG_MSG_SHOW_FUNC_NAME();

	if(lineidx < 0 || lineidx >= fgdata->linecnt)
		return 1;

	pair1 = NULL;
	idx2 = fgdata->line[lineidx];

	if(idx2 == 0xffff)
	{// add first
FG_AddFist();
		if(!FG_Get(fgdata, &idx, &pair))
			return 0;
		pair->xl    = (DT16_short)xl;
		pair->xr    = (DT16_short)xr;
		pair->next  = 0xffff;

		fgdata->line[lineidx] = idx;
	}else
	{
		count1=0;
		do
		{
			pair2 = &fgdata->pool[idx2];
			if(xr < pair2->xl-1)
			{	// insert before
FG_InsertBefore();
				if(!FG_Get(fgdata, &idx, &pair))
					return 0;
				pair->xl    = (DT16_short)xl;
				pair->xr    = (DT16_short)xr;
				pair->next  = idx2;

				if(pair1 == NULL)
					fgdata->line[lineidx] = idx;
				else
					pair1->next	= idx;
				break;
			}else if(xr <= pair2->xr)
			{	// merge
FG_Dispear();
				if(xl < pair2->xl)
					pair2->xl = (DT16_short)xl;
				break;
			}else if(xl <= pair2->xr+1 && xr > pair2->xr)
			{	// merge
FG_Merge();
				if(xl < pair2->xl)
					pair2->xl = (DT16_short)xl;
				if(xr > pair2->xr)
					pair2->xr = (DT16_short)xr;

				// merge next scanline
				idx2 = pair2->next;
				while(idx2 != 0xffff)
				{
					pair1 = pair2;
					pair2 = &fgdata->pool[idx2];
					if(pair2->xl <= pair1->xr+1)
					{
						if(xr < pair2->xr)
							pair1->xr = pair2->xr;
						pair1->next = pair2->next;
						FG_Free(fgdata, idx2);

						pair2 = pair1;
						idx2 = pair1->next;
					} else
						break;
				}// end while
				break;
			}else if(pair2->next == 0xffff)
			{	// insert last
if(count1 == 0)
	FG_InsertLast();
else FG_InsertLastsss();
				if(!FG_Get(fgdata, &idx, &pair))
					return 0;
				pair->xl    = (DT16_short)xl;
				pair->xr    = (DT16_short)xr;
				pair->next  = 0xffff;

				pair2->next = idx;
				break;
			}else
			{// next scanline
count1++;
				pair1 = pair2;
				idx2 = pair1->next;
			}// end if
		} while(1);
	}// end if

	return 1;
}
#endif

/*---------------------------------------------------------------------------*/
DT32_int FG_Delete(pFdlGradeData fgdata, DT32_int y, DT32_int xl, DT32_int xr)
{
	DT32_int lineidx = y - fgdata->yt;
	DT16_WORD idx2, idx3, next;
	pFGXPair pair1, pair2, pair3;

DBG_MSG_SHOW_FUNC_NAME();

	if(lineidx < 0 || lineidx >= fgdata->linecnt) return 1;

	pair1 = NULL;
	idx2 = fgdata->line[lineidx];

	while(idx2 != 0xffff)
	{
		pair2 = &fgdata->pool[idx2];
		if(xr < pair2->xl) /* finish */
		{
			break;
		} else if(xl <= pair2->xl && xr >= pair2->xr) /* delete full line */
		{
			next = pair2->next;
			if(pair1 == NULL)
				fgdata->line[lineidx] = next;
			else
				pair1->next	= next;
			FG_Free(fgdata, idx2);
			idx2 = next;
			continue;
		} else if(xl > pair2->xl && xr < pair2->xr)	/* delete middle */
		{
			/* add one */
			if(!FG_Get(fgdata, &idx3, &pair3)) return 0;
			pair3->xl   = (DT16_short)(xr + 1);
			pair3->xr   = pair2->xr;
			pair3->next = pair2->next;

			/* modify */
			pair2->xr   = (DT16_short)(xl - 1);
			pair2->next = idx3;

			pair2 = pair3;
		} else if(BETWEEN(xl,pair2->xl,pair2->xr) && xr >= pair2->xr) /* delete end */
		{
			pair2->xr = (DT16_short)(xl - 1);
		} else if(BETWEEN(xr,pair2->xl,pair2->xr) && xl <= pair2->xl) /* delete head */
		{
			pair2->xl = (DT16_short)(xr + 1);
		}

		/* next */
		pair1 = pair2;
		idx2 = pair1->next;
	}

	return 1;
}
/*---------------------------------------------------------------------------*/
DT_void FG_GetLineRange(pFdlGradeData fgdata, DT32_int *yt, DT32_int *yb)
{
	DT32_int idx;
	DT32_int last = fgdata->yb - fgdata->yt;

DBG_MSG_SHOW_FUNC_NAME();

	idx = 0;
	while(idx < last && fgdata->line[idx] == 0xffff) idx++;
	*yt = fgdata->yt + idx;

	idx = last;
	while(idx > 0 && fgdata->line[idx] == 0xffff) idx--;
	*yb = fgdata->yt + idx;
}
/*---------------------------------------------------------------------------*/
pFGXPair FG_GetLine(pFdlGradeData fgdata, DT32_int y)
{
	DT32_int lineidx = y - fgdata->yt;
	DT32_int idx;

DBG_MSG_SHOW_FUNC_NAME();

	if(lineidx < 0 || lineidx >= fgdata->linecnt)
		return NULL;
	else
	{
		idx = fgdata->line[lineidx];
		if(idx != 0xffff)
			return &fgdata->pool[idx];
		else
			return NULL;
	}
}
/*---------------------------------------------------------------------------*/
DT32_int FG_GetLineNum(pFdlGradeData fgdata, pFGXPair pair)
{
	pFGXPair startp=pair;
	DT32_int count=1;
	DT32_int idx;
DBG_MSG_SHOW_FUNC_NAME();

	for(; ;count++)
	{
		idx = startp->next;
	
		if(idx != 0xffff)
			startp = &fgdata->pool[idx];
		else
			break;
	}// end for

	return count;
}// end FG_GetLineNum

pFGXPair FG_GetNext(pFdlGradeData fgdata, pFGXPair pair)
{
	DT32_int idx = pair->next;

DBG_MSG_SHOW_FUNC_NAME();

	if(idx != 0xffff)
		return &fgdata->pool[idx];
	else
		return NULL;
}
/*---------------------------------------------------------------------------*/
DT32_long FG_UsedMemSize(pFdlGradeData fgdata)
{
	
DBG_MSG_SHOW_FUNC_NAME();

	return fgdata->memsize - (fgdata->freemax - fgdata->freelist) * sizeof(TFGXPair);
}
/*---------------------------------------------------------------------------*/
/*
  DT_void FG_Check(pFdlGradeData fgdata)
  {
	DT32_int yt, yb, y;
	pFGXPair pair, prev;
	DT32_int errcnt=0, wran=0;
	DT32_int total=0;
	DT32_int pairs, maxpair=0, maxy=-1;
	DT8_char msg2[1024], msg[1024], s1[256];
  
	FG_GetLineRange(fgdata, &yt, &yb);
  
	for (y=yt; y<=yb; y++)
	{
		pair = FG_GetLine(fgdata, y);
	  prev = NULL;
	  pairs = 0;
	  msg[0] = 0;
  
	  while (pair != NULL)
		{
		if (pair->xl > pair->xr)
		  errcnt++;
  
		if (prev && (prev->xr >= pair->xl))
			errcnt++;
  
		if (prev && (prev->xr+1 == pair->xl))
			wran++;
  
		total++;
		pairs++;
		sprintf(s1, "(%d,%d)", pair->xl, pair->xr);
		strcat(msg, s1);
  
		prev = pair;
		pair = FG_GetNext(fgdata, pair);
	  }
  
	  if (pairs > maxpair)
	  {
		maxpair = pairs;
		maxy = y;
		strcpy(msg2, msg);
	  }
	}
  
	if (errcnt>0 || wran>0)
	{
		errcnt = 0;
	}
  }
*/
/*---------------------------------------------------------------------------*/

