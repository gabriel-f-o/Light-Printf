/*
 * light_print.c
 *
 *  Created on: Mar 28, 2021
 *      Author: Gabriel
 */

#include <stdio.h>
#include <stdarg.h>

#include "lp_printf.h"

/**********************************************
 * DEFINES
 *********************************************/

#ifndef __weak
#define __weak __attribute__((weak))
#endif

/**********************************************
 * PRIVATE FUNCTIONS
 *********************************************/
 
#if (defined(LIGHT_PRINT_EN) && LIGHT_PRINT_EN == 1)

static void print_int_arg (uint32_t arg, bool sign, uint8_t base, size_t min, char fill){
    char argStr[32] = {[0 ... 31] = 0 };
    char digits[] = { "0123456789ABCDEF" };

    size_t argLen = 0;
    bool neg = 0;

    if ( (sign == 1) && ( (arg & (1ULL << 31)) != 0 ) ){
        arg = -arg;
        neg = 1;
    }

    if(arg == 0){
    	argStr[argLen++] = '0';
    }

    while (arg > 0){
        argStr[argLen++] = (digits[arg % base]);
        arg /= base;
    }

#if (defined (LIGHT_PRINT_FILL) && LIGHT_PRINT_FILL == 1)
    if(neg == 1){
        if(fill == '0') lp_putc('-');
        
        min = ( (min == 0) ? 0 : min - 1);
    }
    
    while(min > argLen){
        lp_putc(fill);
        min--;
    }
#endif

    if(neg == 1 && fill != '0'){
        lp_putc('-');
    }

    while(argLen > 0){
        lp_putc(argStr[argLen - 1]);
        argLen--;
    }
}

#if (defined(LIGHT_PRINT_FLOAT) && LIGHT_PRINT_FLOAT == 1)
static void print_float_arg(double arg, size_t min, size_t precision, char fill){
    
    char argStr[200] =  {[0 ... 199] = 0 };
    size_t argLen = 0;
    bool neg = 0;

    if ( arg < 0 ){
        arg = -arg;
        neg = 1;
    }
    
    
    
#if 0
    /*printf("pre = %lu, min = %lu\n", precision, min);
    char argStr[200] = {[0 ... 199] = 0 };

    size_t argLen = 0;
    bool neg = 0;

    if ( arg < 0 ){
        arg = -arg;
        neg = 1;
    }

    uint64_t whole = (uint64_t) arg;

    while ( whole > 0){
        argStr[argLen++] = (whole % 10) + '0';
        whole /= 10;
    }
    
    for(size_t i = 0; i < argLen / 2; i++){
        char aux = argStr[i];
        argStr[i] = argStr[argLen - i - 1];
        argStr[argLen - i - 1] = aux;
    }*/
    
    if ( arg < 0 ){ 
        arg = -arg;
    }
    
    char argStr[200] = {[0 ... 199] = 0 };

    size_t argLen = 0;
    //bool neg = 0;
    
    uint64_t digits = (uint64_t) ( (arg - (uint64_t) arg) * pow(10, precision) );
    
    if(digits > 0) argStr[argLen++] = '.';
    
    size_t digBegin = argLen;

    while(digits > 0){
        argStr[argLen++] = (digits % 10) + '0';
        digits /= 10;
    }
    
    for(size_t i = digBegin; i < (digBegin + argLen) / 2; i++){
        char aux = argStr[i];
        argStr[i] = argStr[digBegin + argLen - i - 1];
        argStr[digBegin + argLen - i - 1] = aux;
    }

/*#if (defined (LIGHT_PRINT_FILL) && LIGHT_PRINT_FILL == 1)
    if(neg == 1){
        if(fill == '0') lp_putc('-');
        min = ( (min == 0) ? 0 : min - 1);
    }
    
    while(min > argLen){
        lp_putc(fill);
        min--;
    }
#endif*/

    /*if(neg == 1 && fill != '0'){
        lp_putc('-');
    }*/
    
    print_int_arg((uint64_t) arg, true, 10, ( (min < argLen) ? 0 : min - argLen) , fill);

    for(size_t i = 0; i < argLen; i++){
        lp_putc(argStr[i]);
    }
#endif
    
}
#endif
/**********************************************
 * PUBLIC FUNCTIONS
 *********************************************/

//Put Char function to overload (depending on MCU)
__weak void lp_putc(char c){
	putc(c, stdout);
}

void lp_vprintf(char const* const s, va_list args){
    
    if(s == NULL) return;

    /* Init local variables
    -------------------------------------------------------- */
    char c = s[0];
    size_t pos = 0;

    while (c != '\0'){
        c = s[pos];

        if(c == '\0') break;

        /* Check for %% in a string -> prints only one %
        -------------------------------------------------------- */
        short scape_perc = ((c == '%' && s[pos + 1] == '%') ? 1 : 0);

        if (scape_perc == 1){
            lp_putc('%');
            pos += 2;
            continue;
        }

        /* Check for % in a string -> prints data in argument
        -------------------------------------------------------- */
        short special_p = ((c == '%' && s[pos + 1] != '%') ? 1 : 0);

        if (special_p == 1){
            size_t min = 0;
            char fill = ' ';
            size_t ipos = pos + 1;

#if (defined (LIGHT_PRINT_FILL) && LIGHT_PRINT_FILL == 1)
            if(s[ipos] == ' ' || s[ipos] == '0'){
                fill = s[ipos++];
            }

            while( '0' <= s[ipos] && s[ipos] <= '9' ){
                min = min * 10 + ( s[ipos++] - '0');
            }
            
            min = ( (min > 100) ? 1000 : min);
#endif

#if (defined(LIGHT_PRINT_FLOAT) && LIGHT_PRINT_FLOAT == 1)
            size_t precision = 6;

#if (defined(LIGHT_PRINT_PRECISION) && LIGHT_PRINT_PRECISION == 1)

            if(s[ipos] == '.'){
                
                ipos++;
                precision = 0;
                while( '0' <= s[ipos] && s[ipos] <= '9' ){
                    precision = precision * 10 + ( s[ipos++] - '0');
                }
            }
            
#endif
#endif

            char id = s[ipos++];
            switch (id){

                case 'd' : case 'i' : case 'u' : {
                    uint32_t arg = va_arg(args, uint32_t);
                    print_int_arg(arg, ( (id == 'u') ? false : true), 10, min, fill);
                    break;
                }

#if (defined (LIGHT_PRINT_HEX) && LIGHT_PRINT_HEX == 1)
                case 'x' : case 'X' : {
                    uint32_t arg = va_arg(args, uint32_t);
                    print_int_arg(arg, false, 16, min, fill);
                    break;
                }
#endif

#if (defined (LIGHT_PRINT_BIN) && LIGHT_PRINT_BIN == 1)
                case 'b' : {
                    uint32_t arg = va_arg(args, uint32_t);
                    print_int_arg(arg, false, 2, min, fill);
                    break;
                }
#endif

#if (defined (LIGHT_PRINT_FLOAT) && LIGHT_PRINT_FLOAT == 1)
                case 'f' : {
                    double arg = va_arg(args, double);
                    print_float_arg(arg, min, precision, fill);
                    break;
                }
#endif

                case 's' : {
                    char * str = va_arg(args, char*);
                    size_t strLen = strlen(str);

                    while( min-- > strLen) lp_putc(' ');
                    while( *str != '\0' ) {
                    	lp_putc(*str++);
                    }

                    break;
                }

                default : {
                    lp_putc('%');
                    pos++;
                    continue;
                }
            }

            pos = ipos;
            continue;
        }

        /* Otherwise print character by character
        -------------------------------------------------------- */
        lp_putc(c);
        pos++;
    }

}

//Light Printf main function
void lp_printf (char const *const s, ...){

    /* Init arg list
    -------------------------------------------------------- */
    va_list args;
    va_start (args, s);

    /* Call function
    -------------------------------------------------------- */
    lp_vprintf(s, args);

    /* End argument list
    -------------------------------------------------------- */
    va_end (args);
}

#else

/**********************************************
 * PUBLIC FUNCTIONS
 *********************************************/

//Put Char function to overload (depending on MCU) (disabled)
__weak void lp_putc(char c){}

//Light Printf main function (disabled)
void lp_printf (char const *const s, ...){}

#endif
