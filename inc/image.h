/**
 *  image.h
 *
 */


#ifndef __IMAGE_H__
#define __IMAGE_H__


#include "class.h"
#include "osa.h"

#ifdef __cplusplus
extern "C"
{
#endif

typedef enum
{
    IPL_8U = 8,
    IPL_16U = 16
}
ats_image_depth_t;


typedef struct IMAGE_ROI
{
    osa_uint32_t    r_x;
    osa_uint32_t    r_y;
    osa_uint32_t    r_width;
    osa_uint32_t    r_height;
} ats_image_roi_t;


struct ATS_IMAGE_CLASS
{
    osa_uint32_t        size;

    osa_uint32_t        width;
    osa_uint32_t        height;
    ats_image_depth_t   depth;
    osa_uint32_t        channels;
    osa_uint32_t        width_step;

    ats_image_roi_t     roi;

    osa_char_t          *scan0;
};


ats_image_t     *ats_image_new();
ats_image_t     *ats_image_new_ex(osa_uint32_t      width,
                                  osa_uint32_t        height,
                                  ats_image_depth_t   depth,
                                  osa_uint32_t        channels,
                                  osa_char_t          *data);
void        ats_image_delete(ats_image_t *img);


void        ats_image_set_roi(ats_image_t *img, osa_uint32_t x, osa_uint32_t y, osa_uint32_t w, osa_uint32_t h);
void        ats_image_2_cvimage(ats_image_t *img, void **out_pp_cvimg);

void        ats_image_scan(ats_image_t *img, void (*each_pixel_func)(void *pixel));



#ifdef __cplusplus
}
#endif


#endif
