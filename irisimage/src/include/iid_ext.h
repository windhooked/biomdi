/*
* This software was developed at the National Institute of Standards and
* Technology (NIST) by employees of the Federal Government in the course
* of their official duties. Pursuant to title 17 Section 105 of the
* United States Code, this software is not subject to copyright protection
* and is in the public domain. NIST assumes no responsibility whatsoever for
* its use by other parties, and makes no guarantees, expressed or implied,
* about its quality, reliability, or any other characteristic.
*/
/******************************************************************************/
/* Header file for the NIST IREX extensions to the Iris Image Data Record     */
/* format, as specified in  ISO/IEC 19794-6:2005. See "Iris Exchange (IREX)   */
/* Evaluation 2008: Concept, Evaluation Plan and API" at                      */
/* http://iris.nist.gov/irex/                                                 */
/*                                                                            */
/******************************************************************************/
#ifndef _IID_EXT_H
#define _IID_EXT_H

struct roi_mask {
	uint8_t			upper_eyelid_mask;
	uint8_t			lower_eyelid_mask;
	uint8_t			sclera_mask;
};
typedef struct roi_mask ROIMASK;

struct unsegmented_polar {
	uint16_t		num_samples_radially;
	uint16_t		num_samples_circumferentially;
	uint16_t		inner_outer_circle_x;
	uint16_t		inner_outer_circle_y;
	uint16_t		inner_circle_radius;
	uint16_t		outer_circle_radius;
};
typedef struct unsegmented_polar UNSEGPOLAR;

#define IID_EXT_COORD_NOT_COMPUTED	0xFFFF

struct image_ancillary {
	uint16_t		pupil_center_of_ellipse_x;
	uint16_t		pupil_center_of_ellipse_y;
	uint16_t		pupil_semimajor_intersection_x;
	uint16_t		pupil_semimajor_intersection_y;
	uint16_t		pupil_semiminor_intersection_x;
	uint16_t		pupil_semiminor_intersection_y;
	uint16_t		iris_center_of_ellipse_x;
	uint16_t		iris_center_of_ellipse_y;
	uint16_t		iris_semimajor_intersection_x;
	uint16_t		iris_semimajor_intersection_y;
	uint16_t		iris_semiminor_intersection_x;
	uint16_t		iris_semiminor_intersection_y;
	uint8_t			pupil_iris_boundary_freeman_code_length;
	uint8_t		       *pupil_iris_boundary_freeman_code_data;
	uint8_t			sclera_iris_boundary_freeman_code_length;
	uint8_t		       *sclera_iris_boundary_freeman_code_data;
};
typedef struct image_ancillary IMAGEANCILLARY;

/******************************************************************************/
/* Define the interface for allocating and freeing iris image data blocks.    */
/******************************************************************************/
int new_roimask(ROIMASK **roimask);
void free_roimask(ROIMASK *roimask);

int new_unsegpolar(UNSEGPOLAR **unsegpolar);
void free_unsegpolar(UNSEGPOLAR *unsegpolar);

int new_image_ancillary(IMAGEANCILLARY **ancillary);
void free_image_ancillary(IMAGEANCILLARY *ancillary);

/******************************************************************************/
/* Define the interface for reading/writing/verifying iris image data blocks. */
/******************************************************************************/
int read_roimask(FILE *fp, ROIMASK *roimask);
int write_roimask(FILE *fp, ROIMASK *roimask);
int print_roimask(FILE *fp, ROIMASK *roimask);
int validate_roimask(ROIMASK *roimask);

int read_unsegpolar(FILE *fp, UNSEGPOLAR *unsegpolar);
int write_unsegpolar(FILE *fp, UNSEGPOLAR *unsegpolar);
int print_unsegpolar(FILE *fp, UNSEGPOLAR *unsegpolar);
int validate_unsegpolar(UNSEGPOLAR *unsegpolar);

int read_image_ancillary(FILE *fp, IMAGEANCILLARY *ancillary);
int write_image_ancillary(FILE *fp, IMAGEANCILLARY *ancillary);
int print_image_ancillary(FILE *fp, IMAGEANCILLARY *ancillary);
int validate_image_ancillary(IMAGEANCILLARY *ancillary);

#endif 	/* _IID_EXT_H */