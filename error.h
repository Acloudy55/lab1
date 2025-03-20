#pragma once
#ifndef _ERROR_DEFINITION_
#define _ERROR_DEFINITION_
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef enum error_type {
    ERR_NULL_POINTER,
    ERR_MEMORY_ALLOCATION_FAILED,
    ERR_BUFFER_OVERFLOW,
    ERR_TYPE_MISMATCH,
    ERR_LENGTH_INVALID,
    ERR_INVALID_INPUT,
    ERR_UNKNOWN
}   error_type;

void log_error(error_type error);


#endif

