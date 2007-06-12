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
/*                                                                            */
/* Routines that read, write, and validate Feature Point Blocks in compliance */
/* with the Face Recognition Format for Data Interchange (ANS/INCITS 385-2004)*/
/* format standard.                                                           */
/*                                                                            */
/******************************************************************************/
#include <sys/queue.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <biomdimacro.h>
#include <frf.h>

int
new_fpb(struct feature_point_block **fpb)
{
	struct feature_point_block *lfpb;

	lfpb = (struct feature_point_block *)malloc(
			sizeof(struct feature_point_block));
	if (lfpb == NULL) {
		perror("Failed to allocate Feature Point Block");
		return -1;
	}
	memset((void *)lfpb, 0, sizeof(struct feature_point_block));
	
	*fpb = lfpb;

	return 0;
}

void
free_fpb(struct feature_point_block *fpb)
{
	free(fpb);
}

int
read_fpb(FILE *fp, struct feature_point_block *fpb)
{
	unsigned char cval;

	// Feature Type
	CREAD(&fpb->type, fp);

	// Feature Point
	CREAD(&cval, fp);
	fpb->major_point = (cval & FRF_FEATURE_POINT_MAJOR_MASK) >> 
				FRF_FEATURE_POINT_MAJOR_SHIFT;
	fpb->minor_point = cval & FRF_FEATURE_POINT_MINOR_MASK;

	// Horizontal Position
	SREAD(&fpb->x_coord, fp);

	// Vertical Position
	SREAD(&fpb->y_coord, fp);

	// Reserved
	SREAD(&fpb->reserved, fp);

        return READ_OK;

eof_out:
	return READ_EOF;

err_out:
        return READ_ERROR;
}

int
write_fpb(FILE *fp, struct feature_point_block *fpb)
{
	unsigned char cval;

	CWRITE(&fpb->type, fp);

	cval = (fpb->major_point << FRF_FEATURE_POINT_MAJOR_SHIFT) | 
		fpb->minor_point;
	CWRITE(&cval, fp);

	SWRITE(&fpb->x_coord, fp);
	SWRITE(&fpb->y_coord, fp);

	SWRITE(&fpb->reserved, fp);

        return WRITE_OK;

err_out:
        return WRITE_ERROR;
}

int
print_fpb(FILE *fp, struct feature_point_block *fpb)
{
	FPRINTF(fp, "Feature Point Block\n");

	FPRINTF(fp, "\tFeature Type 0x%1u\n", fpb->type);

	FPRINTF(fp, "\tFeature Point %u.%u\n", fpb->major_point,
			fpb->minor_point);

	FPRINTF(fp, "\tCoordinate (%u,%u)\n", fpb->x_coord, fpb->y_coord);

	FPRINTF(fp, "\tReserved 0x%04x\n", fpb->reserved);

        return PRINT_OK;

err_out:
        return PRINT_ERROR;
}

int
validate_fpb(struct feature_point_block *fpb)
{
        return VALIDATE_OK;
}