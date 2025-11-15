/*
 *	ionpatch.c:	functions enabling the use of ION's
 *			private memory management system in
 *			the BPSec Library.
 *
 *	Author: Scott Burleigh
 *
 *	Copyright (c) 2025, California Institute of Technology.
 *	ALL RIGHTS RESERVED.  U.S. Government Sponsorship acknowledged.
 */

#include "ion.h"
#include "ionpatch.h"

extern void	*ion_malloc(const char *file, int line, size_t size)
{
	writeMemo("[i] ION BSL_MALLOC called.");
	return allocFromIonMemory(file, line, size);
}

extern void	*ion_calloc(const char *file, int line, size_t ct, size_t size)
{
	writeMemo("[i] ION BSL_CALLOC called.");
	return allocFromIonMemory(file, line, ct * size);
}

extern void	*ion_realloc(const char *file, int line, void *mem, size_t size)
{
	writeMemo("[?] ION's function for BSL_REALLOC invoked.  Utility \
unknown, not yet implemented.");
	return NULL;
#if 0
	/*	Note that, if implemented, this function would not
	 	be of any use to BSL_BundleCtx_ReallocBTSD, since
		ION stores extension blocks in the SDR heap rather
	 	than in system memory.
	 
	 	Note that if this function WERE implemented it
	 	would not work in the way that standard realloc()
		works.  The space immediately adjacent to a block of
		ION working memory will typically NOT be unoccupied,
		i.e, will NOT be available to be silently appended
		to that block.

		So the content of the original block would instead
		be copied to a newly allocated block of the requested
		size; the address of that new block would be returned.	*/

	void	*newMem;

	if (size == 0)
	{
		releaseToIonMemory(file, line, mem);
		newMem = NULL;
	}
	else
	{
		newMem = allocFromIonMemory(file, line, size);
		if (newMem == NULL)
		{
			newMem = mem;	/*	Retain orginal data.	*/
		}
		else	/*	New memory block was obtained.		*/
		{
			memcpy(newMem, mem, size);
			releaseToIonMemory(file, line, mem);
		}
	}

	return newMem;
#endif
}

extern void	ion_free(const char *file, int line,  void *mem)
{
	writeMemo("[i] ION BSL_FREE called.");
	releaseToIonMemory(file, line, mem);
}
