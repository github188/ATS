/**
 *  image.h
 *
 */


#ifndef __IMAGE_H__
#define __IMAGE_H__


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
ATS_ImageDepth;


typedef struct _IMAGE_ROI
{
    osa_uint32_t    r_x;
    osa_uint32_t    r_y;
    osa_uint32_t    r_width;
    osa_uint32_t    r_height;
} ATS_ImageROI;


typedef struct _IMAGE_OBJECT
{
    osa_uint32_t    size;

    osa_uint32_t    width;
    osa_uint32_t    height;
    ATS_ImageDepth  depth;
    osa_uint32_t    channels;
    osa_uint32_t    widthStep;

    ATS_ImageROI    roi;

    osa_char_t      *scan0;
} ATS_Image;



ATS_Image   *ATS_ImageNew();
ATS_Image   *ATS_ImageNewWithData(osa_uint32_t width, osa_uint32_t height, ATS_ImageDepth depth, osa_uint32_t channels, osa_char_t *data);
void        ATS_ImageDelete(ATS_Image *img);


void        ATS_ImageSetROI(ATS_Image *img, osa_uint32_t x, osa_uint32_t y, osa_uint32_t w, osa_uint32_t h);
void        ATS_Image2CVImage(ATS_Image *img, void **out_ppcvImg);

void        ATS_ImageScan(ATS_Image *img, void (*foreachFunc)(void *pixel));



#ifdef __cplusplus
}
#endif


#endif
