// Generated by `wit-bindgen` 0.25.0. DO NOT EDIT!
#ifndef __BINDINGS_BINDINGS_H
#define __BINDINGS_BINDINGS_H
#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>

typedef struct bindings_string_t {
  uint8_t*ptr;
  size_t len;
} bindings_string_t;

// Exported Functions from `example`
void bindings_hello_world(bindings_string_t *ret);

// Helper Functions

// Transfers ownership of `s` into the string `ret`
void bindings_string_set(bindings_string_t *ret, const char*s);

// Creates a copy of the input nul-terminate string `s` and
// stores it into the component model string `ret`.
void bindings_string_dup(bindings_string_t *ret, const char*s);

// Deallocates the string pointed to by `ret`, deallocating
// the memory behind the string.
void bindings_string_free(bindings_string_t *ret);

#ifdef __cplusplus
}
#endif
#endif
