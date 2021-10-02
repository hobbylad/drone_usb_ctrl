
#include "Buttons.h"

#include "Buttons.h"

#include "Arduino.h"

void buttons_init(const decode_buttons_config_t *config, uint8_t count, decode_buttons_t *context)
{
  context->config = config;
  context->count = count;
  context->raw_state = 0;
  context->deglitched_state = 0;
}

uint8_t buttons_decode(uint16_t sample, decode_buttons_t *context)
{  
  uint8_t unmapped_state = 0x1, state = 0;

  for (uint8_t i = 0; i < 5; ++i)
  {
    if (sample <= context->config[i].threshold)
    {
      break;
    }

    unmapped_state <<= 1;
  }

  unmapped_state &= 0x1F;

  for (uint8_t i = 0; i < 5; ++i)
  {
    if (unmapped_state & (1 << i))
    {
      state |= (1 << context->config[i].mapping);
    }
  }

  if (state != context->raw_state)
  {
    context->count = 1;
    context->raw_state = state;
  }
  else if (context->count != 255)
  {
    if (++context->count == 10)
    {
      context->deglitched_state = context->raw_state;
    }
  }

  return context->deglitched_state;
}





