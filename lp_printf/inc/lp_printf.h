#ifndef LIGHT_PRINT_H
#define LIGHT_PRINT_H

#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>
#include <math.h>

#include "lp_conf.h"

/**********************************************
 * GENERAL INFO
 *********************************************/

 /**
  * This library implements the printf function for tiny MCUs. The most relevant features are kept, while most of them are not implemented in order to save flash
  *     Syntax
  *     %[flags][number of digits minumum][.maximum decimal precision (float only)][identifier]
  *
  *     Flags   : 0 or space : Adds these characters so the minumum digits is respected
  *     Minimum : A number always shows this many characters
  *     Decimal : Maximum number of characters after the decimal point
  *
  *     id      :   %i or %d : prints a signed integer
  *                 %u       : prints an unsigned integer
  *                 %x       : prints an integer in hexadecimal format
  *                 %b       : prints an integer in binary format
  *                 %s       : printf a string
  *                 %f       : prints a floating number (must be enabled)
  *
  * The user can implement lp_putc to easily port this library
  *
  ***/

/**********************************************
 * PUBLIC FUNCTIONS
 *********************************************/

/*************************************************
 * LP_PUTC
 *
 * @brief This function is responsible of implementing put char in your system.
 *
 * @param char c : Char to be printed [in]
 *
************************************************/
void lp_putc(char c);

/*************************************************
 * LP PRINTF
 *
 * @brief This function implements a reduced printf
 *
 * @param char * s : String to be printed [in]
 * @param ...      : Sequence of arguments to be printed [in]
 *
************************************************/
void lp_printf(char const * const s, ...);
void lp_vprintf(char const* const s, va_list args);

#endif
