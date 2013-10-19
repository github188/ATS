/**
 *  osa_ioch.c
 *
 */
 
#include "osa_types.h"
#include "osa_error.h"
#include "osa_ioch.h"
#include "osa_log.h"


osa_err_t   osa_ioch_open(osa_ioch_t *ch, void *user_data)
{
	return OSA_ERR_ERR;
}

void        osa_ioch_close(osa_ioch_t *ch)
{
}

osa_size_t  osa_ioch_write(osa_ioch_t   *ch, 
                           osa_char_t   *data,
                           osa_size_t   size)
{
	return 0;
}

osa_size_t  osa_ioch_read(osa_ioch_t    *ch,
                          osa_char_t    *data,
                          osa_size_t    size)
{
	return 0;
}

osa_err_t   osa_ioch_ctrl(osa_ioch_t    *ch,
                          osa_int32_t   cmd,
                          void          *param)
{
	return OSA_ERR_ERR;
}
