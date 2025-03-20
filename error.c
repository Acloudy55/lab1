#include "error.h"

static const char *error_messages[] = {
    "Null pointer dereference",
    "Memory allocation failed",
    "Buffer overflow",
    "Type mismatch",
    "Length is invalid",
    "Invalid input"
    "Unknown error"

};

void log_error(error_type error)
{
    if (error < 0 || error > ERR_TYPE_MISMATCH)
        error = ERR_UNKNOWN;

    fprintf(stderr, "В ходе работы программы возникла ошибка: %s.\n", error_messages[error]);
};

