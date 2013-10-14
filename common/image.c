/**
 *  image.c
 *
 */


#include "osa.h"
#include "core.h"


ats_image_t *image_new()
{
    ats_image_t   *img = osa_mem_alloc(sizeof(ats_image_t));

    osa_mem_zero(img, sizeof(ats_image_t));

    return img;
}


ats_image_t *ats_image_new_ex(osa_uint32_t width, osa_uint32_t height, ats_image_depth_t depth, osa_uint32_t channels, osa_char_t *data)
{
    ats_image_t *img = image_new();

    img->width      = width;
    img->height     = height;
    img->depth      = depth;
    img->channels   = channels;
    img->width_step = width;
    img->size       = img->width_step * img->height;
    img->scan0      = data;

    ats_image_set_roi(img, 0, 0, img->width, img->height);

    return img;
}


void ats_image_delete(ats_image_t *img)
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


void ats_image_set_roi(ats_image_t *img, osa_uint32_t x, osa_uint32_t y, osa_uint32_t w, osa_uint32_t h)
{
    img->roi.r_x        = x;
    img->roi.r_y        = y;
    img->roi.r_width    = w;
    img->roi.r_height   = h;
}


void ats_image_2_cvimage(ats_image_t *img, void **out_pp_cvimg)
{
}

void ats_image_scan(ats_image_t *img, void (*each_pixel_func)(void *pixel))
{

}
