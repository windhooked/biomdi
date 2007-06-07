/*
 * This software was developed at the National Institute of Standards and
 * Technology (NIST) by employees of the Federal Government in the course
 * of their official duties. Pursuant to title 17 Section 105 of the
 * United States Code, this software is not subject to copyright protection
 * and is in the public domain. NIST assumes no responsibility  whatsoever for
 * its use by other parties, and makes no guarantees, expressed or implied,
 * about its quality, reliability, or any other characteristic.
 */

/******************************************************************************/
/* This file contains the functions necessary to sort a set of minutiae       */
/* using the Angle method.                                                    */
/*                                                                            */
/******************************************************************************/
#include <sys/queue.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <fmr.h>
#include <fmrsort.h>
#include <biomdimacro.h>

/*
 * Compare two minutiae records by the minutiae angle.
 */
static int
compare_by_angle(const void *m1, const void *m2)
{
	FMD **lmpp;
	FMD *lm1, *lm2;

	lmpp = (FMD **)m1;
	lm1 = (FMD *)*lmpp;
	lmpp = (FMD **)m2;
	lm2 = (FMD *)*lmpp;

	if (lm1->angle == lm2->angle)
		return (0);
	else
		if (lm1->angle < lm2->angle)
			return (-1);
		else
			return (1);
}

/*
 * Sort a set of finger minutiae data in Angle order.
 */
void
sort_fmd_by_angle(FMD **fmds, int mcount)
{
	int m;
	FMD **lfmds;

	if (mcount == 0)
		return;

	/* Allocate an array to hold the sorting criteria for the FMDs */
	lfmds = (FMD **)malloc(mcount * sizeof(FMD *));
	if (lfmds == NULL)
		ALLOC_ERR_EXIT("Sorting criteria array");

	for (m = 0; m < mcount; m++)
		lfmds[m] = fmds[m];
	
	qsort(lfmds, mcount, sizeof(FMD *), compare_by_angle);

	for (m = 0; m < mcount; m++)
		fmds[m] = lfmds[m];

	free(lfmds);
}
