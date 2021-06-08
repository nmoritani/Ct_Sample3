#include "DTsuba.h"

struct cell
{
	DT32_uint size;
	DT32_int line;
	ref_t next;	/* reference to next cell in free list */
};

#ifndef offsetof
#define offsetof(s,m)   (DT_size_t)&(((s *)0)->m)
#endif

#define ALIGNMASK 7UL
#define ALIGN(s) (((s) + ALIGNMASK) & ~ALIGNMASK)
#define POFF ALIGN(offsetof(struct cell, next))
#define C2P(c) ((DT8_char *)(c) + POFF)
#define P2C(p) ((struct cell *)((DT8_char *)(p) - POFF))
#define ISADJ(c1,c2) ((struct cell *)(C2P(c1) + (c1)->size) == (struct cell *)(c2))
#define SREF(s,p) (ref_t)((DT8_char *)(p) - (DT8_char *)(s))
#define SADR(s,r) (DT_void *)((DT8_char *)(s) + (r))
#define RECLAIM_DEPTH_MAX 2
#define SUBA_MAGIC "DCW_FDLA"

#define C2PLAST(c)	((DT8_char *)(c) + POFF + sizeof(ref_t))
#define P2CLAST(p)	((struct cell *)((DT8_char *)(p) - POFF - + sizeof(ref_t)))
#define REVALIGN(s)	(((s) - ALIGNMASK) & ~ALIGNMASK)


DT_void *DT_memory_addr(const struct allocator *suba, const ref_t ref)
{
DBG_MSG_SHOW_FUNC_NAME();

	if(suba && ref > 0 && ref <= suba->size)
	{
		return(DT8_char *)suba + ref;
	}
	return(NULL);
}

ref_t DT_memory_ref(const struct allocator *suba, const DT_void *ptr)
{
DBG_MSG_SHOW_FUNC_NAME();

	if(suba && ptr)
	{
		ref_t ref = (DT8_char *)ptr - (DT8_char *)suba;
		if(ref > 0 && ref <= suba->size)
		{
			return(ref);
		}
	}
	return(0);
}

struct allocator *DT_memory_init(DT_void *mem, DT32_uint size, DT32_int rst, DT32_uint mincell)
{
	struct allocator *suba = mem;
	DT32_uint hdrsiz;
	
DBG_MSG_SHOW_FUNC_NAME();

	hdrsiz = ALIGN(sizeof(*suba));	/*hdrsiz = ALIGN(sizeof *suba);*//* Modified_by_Jacky_20100817 */

	if(mem == NULL || size <= (hdrsiz + POFF) || (!rst && DT_strncmp(SUBA_MAGIC, (DT8_char*)suba->magic, 8)) != 0)
	{
		return(NULL);
	}

	if(rst)
	{
		struct cell *c;

		DT_memset(suba, 0, hdrsiz);
		DT_memcpy(suba->magic, SUBA_MAGIC, 8);
		suba->tail = hdrsiz;
		/* cell data must be large enough for next ref_t */
		suba->mincell = ALIGN(sizeof(DT32_uint));
		if(mincell > suba->mincell)
		{
			suba->mincell = ALIGN(mincell);
		}
		suba->size = suba->max_free = size;

		c = DT_memory_addr(suba, hdrsiz);
		c->size = size - (hdrsiz + POFF);
		c->next = suba->tail;
	}

	return(suba);
}

DT_void *DT_memory_alloc(struct allocator *suba, DT32_uint size, DT32_int zero)
{
	struct cell *c1, *c2, *c3;
	DT32_uint s = size;
	DT32_int reclaim = 0;
	DT32_int progress = 0;

DBG_MSG_SHOW_FUNC_NAME();

	size = size < suba->mincell ? suba->mincell : ALIGN(size);

	again:
	if(reclaim)
	{
		progress = 0;

		if(suba->reclaim && suba->reclaim_depth <= RECLAIM_DEPTH_MAX)
		{
			suba->reclaim_depth++;
			progress = suba->reclaim(suba, suba->reclaim_arg, reclaim);
			suba->reclaim_depth--;
		}

		if(!progress)
		{
			return(NULL);
		}
	}

	c2 = SADR(suba, suba->tail);
	for(;;)
	{
		c1 = c2;
		if((c2 = DT_memory_addr(suba, c1->next)) == NULL)
		{
			/*DumpDebugString(": 0x%08x\n", c1->next);*/
			return(NULL);
		}
		if(c2->size >= size)
		{
			break;		 /* found a cell large enough */
		}
		if(c1->next == suba->tail)
		{
			reclaim++;
			goto again;
		}
	}

	if(c2->size > (POFF + size + suba->mincell))
	{
		/* split new cell */
		c3 = (struct cell *)(C2P(c2) + size);
		c3->size = c2->size - (size + POFF);
		if(c1 == c2)
		{
			c1 = c3;
		} else
		{
			c3->next = c2->next;
		}
		c1->next = SREF(suba, c3);
		c2->size = size;
		if(c2 == SADR(suba, suba->tail))
		{
			suba->tail = SREF(suba, c3);
		}
	} else if(c1->next == suba->tail)
	{
		/* never use the last cell! */
		reclaim++;
		goto again;
	} else					 /* use the entire cell */
	{
		c1->next = c2->next;
	}

	suba->alloc_total += POFF + c2->size;
	suba->DT32_uintotal += s;

	return(zero ? DT_memset(C2P(c2), 0, size) : C2P(c2));
}

DT32_int DT_memory_free(DT_void *suba0, DT_void *ptr)
{
	struct allocator *suba = suba0;
	struct cell *c1, *c2, *c3;
	ref_t ref;
	DT32_int j1, j2;

DBG_MSG_SHOW_FUNC_NAME();

	if(!ptr) return(0);

	if(!DT_memory_ref(suba, ptr))
	{
		return(-1);
	}
	/* splice the cell back into the list */
	c1 = SADR(suba, suba->tail);
	c2 = P2C(ptr);
	if(c2->size > suba->max_free || (ref = DT_memory_ref(suba, c2)) == 0)
	{
		/*DumpDebugString(": %p: %d\n", ptr, c2->size);*/
		return(-1);
	}

	suba->free_total += POFF + c2->size;

	if(c2 > c1)			  /* append to end of list */
	{
		if(ISADJ(c1,c2))	/* join with last cell */
		{
			c1->size += POFF + c2->size;
			return(0);
		}
		c2->next = c1->next;
		suba->tail = c1->next = ref;

		return(0);
	}

	while(c1->next < ref)	/* find insertion poDT32_int */
	{
		if(c1->next < POFF)
		{
			/*DumpDebugString(": next ref corrupted: %d\n", c1->next);*/
			return(-1);
		}
		c1 = SADR(suba, c1->next);
	}
	c3 = SADR(suba, c1->next);

	j1 = ISADJ(c1,c2); /* c1 and c2 need to be joined */
	j2 = ISADJ(c2,c3); /* c2 and c3 need to be joined */

	if(j1)
	{
		if(j2)	/* splice all three cells together */
		{
			if(SREF(suba, c3) == suba->tail)
			{
				suba->tail = SREF(suba, c1);
			}
			c1->next = c3->next;
			c1->size += POFF + c3->size;
		}
		c1->size += POFF + c2->size;
	} else
	{
		if(j2)
		{
			if(SREF(suba, c3) == suba->tail)
			{
				suba->tail = ref;
			}
			c2->next = c3->next == SREF(suba, c3) ? ref : c3->next;
			c2->size += POFF + c3->size;
		} else
		{
			c2->next = c1->next;
		}
		c1->next = ref;
	}

	return(0);
}

DT_void *DT_memory_realloc(struct allocator *suba, DT_void *ptr, DT32_uint size)
{
	struct cell *c;
	DT_void *p;

DBG_MSG_SHOW_FUNC_NAME();

	if(ptr == NULL)
	{
		if((p = DT_memory_alloc(suba, size, 0)) == NULL)
		{
			/*AMSG("");*/
		}
		return(p);
	}
	if(size == 0)
	{
		DT_memory_free(suba, ptr);
		return(NULL);
	}
	c = P2C(ptr);
	if(c->size < size || (c->size - ALIGN(size)) > suba->mincell)
	{
		p = DT_memory_alloc(suba, size, 0);
	} else
	{
		return(ptr);
	}
	if(p)
	{
		DT_memcpy(p, ptr, size);
		DT_memory_free(suba, ptr);
	}

	return(p);
}

DT_void *DT_memory_alloc_last(struct allocator *suba, DT32_uint *size)
{
	struct cell *c1, *c2;
	DT32_int reclaim = 0;
	DT32_int progress = 0;

DBG_MSG_SHOW_FUNC_NAME();

	if(reclaim)
	{
		progress = 0;

		if(suba->reclaim && suba->reclaim_depth <= RECLAIM_DEPTH_MAX)
		{
			suba->reclaim_depth++;
			progress = suba->reclaim(suba, suba->reclaim_arg, reclaim);
			suba->reclaim_depth--;
		}

		if(!progress)
		{
			return(NULL);
		}
	}

	c2 = SADR(suba, suba->tail);
	for(;;)
	{
		c1 = c2;
		if((c2 = DT_memory_addr(suba, c1->next)) == NULL)
		{
			/*DumpDebugString(": 0x%08x\n", c1->next);*/
			return(NULL);
		}

		if(c1->next == suba->tail)
			break; /* use total cell */
	}
	c1->next = c2->next;

	suba->alloc_total += POFF + c2->size;
	suba->DT32_uintotal += c2->size;
	*size = c2->size;

	return C2P(c2);
}

DT_void *DT_memory_get_last(struct allocator *suba, DT32_uint *size)
{
	struct cell *c2;
// 	DT32_long	tmpsz = 0;

DBG_MSG_SHOW_FUNC_NAME();

	*size = 0;

	c2 = SADR(suba, suba->tail);
//	for(;;)
//	{
//		c1 = c2;
//		if((c2 = DT_memory_addr(suba, c1->next)) == NULL)
//		{
//			/*DumpDebugString(": 0x%08x\n", c1->next);*/
//			return(NULL);
//		}
//
//		if(c1->next == suba->tail)
//			break; /* use total cell */
//	}
//	c1->next = c2->next;

	// check if it's really the last?
	if(c2->next != suba->tail){
		return(NULL);
	}else{
		if(c2->next == 0){	// c2->next = suba->tail = 0 
			return(NULL);
		}
	}

	suba->alloc_total += POFF + c2->size;
	suba->DT32_uintotal += c2->size;

	if( SADR(c2, c2->size+POFF) > SADR(suba, suba->max_free) || c2->size <= sizeof(ref_t))
	{
		*size = 0;
		return (NULL);
	}else{
		*size = c2->size - sizeof(ref_t);
		return C2PLAST(c2);
	}


	return (NULL);
}

DT32_int DT_memory_rel_last(DT_void *suba0, DT_void *ptr)
{
	struct allocator *suba = suba0;
	struct cell *c2;

DBG_MSG_SHOW_FUNC_NAME();

	if(!ptr) return(0);

	if(!DT_memory_ref(suba, ptr))
	{
		return(-1);
	}
	/* splice the cell back into the list */
	c2 = P2CLAST(ptr);
	if(c2->size > suba->max_free || DT_memory_ref(suba, c2) == 0)
	{
		/*DumpDebugString(": %p: %d\n", ptr, c2->size);*/
		return(-1);
	}

	suba->alloc_total -= POFF + c2->size;
	suba->DT32_uintotal -= c2->size;

	return (0);
}

/***************************************************************************************/
/********* DO NOT call the following functions if gDT_Set_Fix_Memory_Size != 1 *********/
/***************************************************************************************/
extern struct allocator * submem;

DT_void *DT_malloc_remained(DT_size_t *size)
{

DBG_MSG_SHOW_FUNC_NAME();

	if(1==gDT_Set_Fix_Memory_Size){
		// Use Fix-Memory Dynamically.
		return DT_memory_get_last(submem, size);
	}else{
		return DT_malloc(*size);
	}

	return NULL;
}

DT_void DT_free_remained( DT_void *memblock )
{

DBG_MSG_SHOW_FUNC_NAME();

	if(1==gDT_Set_Fix_Memory_Size){
		DT_memory_rel_last(submem, memblock);
	}else{
		DT_free(memblock);
	}

}

DT_size_t DT_query_memory_remained()
{
	DT_size_t sz = 0;
	DT_void *p = NULL;

	p = DT_malloc_remained(&sz);
	DT_free_remained(p);

	// Reverse ALIGN(sz) and not use the last cell to ensure it can be DT_malloc() successfully.
	return REVALIGN(sz) - submem->mincell;
}
