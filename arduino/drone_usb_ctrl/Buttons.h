#ifndef BUTTONS_H
#define BUTTONS_H

#include "stdint.h"

#define _PDIV(rtop, rbottom) ((3.3) * ((rbottom) / ((rbottom) + (rtop))))
#define _VTHRESH(vtop, vlow) ((vlow) + (((vtop) - (vlow)) / 2.0))

typedef struct _decode_buttons_config_t
{
  const uint16_t threshold;
  const uint8_t mapping; 
} decode_buttons_config_t;

typedef struct _decode_buttons_t
{
  const decode_buttons_config_t *config;    
  uint8_t count;
  uint8_t raw_state;
  uint8_t deglitched_state;
} decode_buttons_t;

void buttons_init(const decode_buttons_config_t *config, uint8_t count, decode_buttons_t *context);
uint8_t buttons_decode(uint16_t sample, decode_buttons_t *context);

#endif
