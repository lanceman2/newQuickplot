#define _GNU_SOURCE
#include <link.h>

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <locale.h>

#include <panels.h>

//#include "../include/quickplot.h"
#include "debug.h"



char decimal_point = 0;

static void __attribute__((constructor)) constructor(void) {

    DSPEW();
    ERROR("pnWidget_create=%p", pnWidget_create);

    if(!decimal_point) {
        decimal_point = *localeconv()->decimal_point;
        DASSERT(decimal_point);
    }
}


static void __attribute__((destructor)) destructor(void) {

    DSPEW("libquickplot.so done");
}
