/*
  TaintedStr.h

  Copyright Dustin Laurence, 2016.  This file may be used and/or
  redistributed for any purpose in any form.

  Taint analysis example
*/


typedef struct {
    char    *priv_TaintedStr_base;
    size_t   priv_TaintedStr_len;
    size_t   priv_TaintedStr_max;
} dll_TaintedStr;


void dll_TaintedStr_read(dll_TaintedStr buf, int fd, dll_Err *err);

dll_Str dll_TaintedStr_get_username(dll_TaintedStr buf, dll_Err *err);
