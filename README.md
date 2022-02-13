# Light-Printf
This project was made as an effort to reduce the flash used to print to a console.

The user must implement the hardware interface used to communicate with the console by overriding the lp_putc(char c) function.

This library supports the most useful features from printf, such as:
  - Supports signed integers with %d and %i
  - Supports unsigned integers with %u
  - Supports strings with %s
  - (if enabled) Supports hexadecimal print with %x or %X
  - (if enabled) Supports binary print with %b
  - (if enabled) TODO : Supports floating print with %f 
  - (if enabled) Padding with space by using % 5d (minimum 5 characters printed. If less than 5, padding is added with spaces)
  - (if enabled) Padding with '0' by using %05d (minimum 5 characters printed. If less than 5, padding is added with '0's)
  - (if enabled) TODO : Supports floating precision by using %.2f (2 characters for the decimal part)
