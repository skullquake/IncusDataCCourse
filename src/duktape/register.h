#ifndef DUK_REGISTER_H
#define DUK_REGISTER_H
#include"duktape.h"
static duk_ret_t native_print(duk_context*ctx);
static duk_ret_t native_print_header(duk_context*ctx);
static duk_ret_t native_adder(duk_context*ctx);
static duk_ret_t native_env(duk_context*ctx);
void duk_register(duk_context*ctx);
#endif