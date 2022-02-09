#ifndef LIGHT_PRINT_CONF_H
#define LIGHT_PRINT_CONF_H

#ifndef LIGHT_PRINT_EN
#define LIGHT_PRINT_EN 1
#endif
  
//This oprtion enables filling an argument with zeros or spaces in order to align them ex: %02d
#ifndef LIGHT_PRINT_FILL
#define LIGHT_PRINT_FILL 1
#endif

//This option enables floating point printing using %f
#ifndef LIGHT_PRINT_FLOAT
#define LIGHT_PRINT_FLOAT 0
#endif
  
//This oprtion enables the decimal precision option in float (must be enabled alongside LIGHT_PRINT_FLOAT) ex: %3.2f
#ifndef LIGHT_PRINT_PRECISION
#define LIGHT_PRINT_PRECISION 0
#endif
  
//This option enables printing in binary form using %b
#ifndef LIGHT_PRINT_BIN
#define LIGHT_PRINT_BIN 1
#endif
  
//This option enables printing in hexadecimal format using %x or %X
#ifndef LIGHT_PRINT_HEX
#define LIGHT_PRINT_HEX 1
#endif
  
#endif
