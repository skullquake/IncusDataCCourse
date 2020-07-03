#ifndef DUKTAPE_NCURSES_H
#define DUKTAPE_NCURSES_H
#ifdef DUK_USE_NCURSES
#include"duktape.h"
void duk_register_ncurses(duk_context*ctx);
#endif
#endif
