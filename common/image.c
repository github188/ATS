/**
 *  image.c
 *
 */


#include "osa.h"
#include "class.h"
#include "image.h"


image_t   *image_new()
{
    image_t   *img = osa_mem_alloc(sizeof(image_t));

    osa_mem_zero(img, sizeof(image_t));

    return img;
}


image_t   *ATS_ImageNewWithData(osa_uint32_t width, osa_uint32_t height, ATS_ImageDepth depth, osa_uint32_t channels, osa_char_t *data)
{
    image_t *img = image_new();

    img->width      = width;
    img->height     = height;
    img->depth      = depth;
    img->channels   = channels;
    img->widthStep  = width;
    img->size       = img->widthStep * img->height;
    img->scan0      = data;

    ATS_ImageSetROI(img, 0, 0, img->width, img->height);

    return img;
}


void        ATS_ImageDelete(image_t *img)
{
    if (img)
    {
        if (img->scan0)
        {
            osa_mem_free(img->scan0);
        }
        img->scan0 = NULL;

        osa_mem_free(img);
    }
}


void        ATS_ImageSetROI(image_t *img, osa_uint32_t x, osa_uint32_t y, osa_uint32_t w, osa_uint32_t h)
{
    img->roi.r_x        = x;
    img->roi.r_y        = y;
    img->roi.r_width    = w;
    img->roi.r_height   = h;
}


void        ATS_Image2CVImage(image_t *img, void **out_ppcvImg)
{
}

void        ATS_ImageScan(image_t *img, void (*foreachFunc)(void *pixel))
{

}
