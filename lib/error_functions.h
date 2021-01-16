//
// Created by 俞思真 on 2021/1/16.
//

#ifndef HELLO_ERROR_FUNCTIONS_H
#define HELLO_ERROR_FUNCTIONS_H


#ifdef __GNUC__

/* This macro stops 'gcc -Wall' complaining that "control reaches
   end of non-void function" if we use the following functions to
   terminate main() or some other non-void function. */

#define NORETURN __attribute__ ((__noreturn__))
#else
#define NORETURN
#endif


void usageErr(const char *format, ...) NORETURN;

void errExit(const char *format, ...) NORETURN;

void cmdLineErr(const char *format, ...) NORETURN;

#endif //HELLO_ERROR_FUNCTIONS_H
