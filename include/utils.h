/**
 * Contains common utilities for use in various implementations.
 *
 * Update date: 2022-04-28
 * Author: Sune
 */

#pragma once

#ifndef MDRUN_UTILS_H
#define MDRUN_UTILS_H

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

static bool skip_till(_char_t** ptr, _char_t val) {
    for(; **ptr; ++*ptr) if(**ptr == val) return true; // Found
    return false; // Not found
}

bool get_file_name(const _char_t* path, _char_t** dir, _char_t** name) {
    if(path == NULL || (dir == NULL && name == NULL)) return false;
    _char_t* ptr = (_char_t*) path;
    // Skip to the first double quote
    if(!skip_till(&ptr, '"')) ptr = (_char_t*) path;
    else ++ptr; // Skip double quote
    // Find the last path separator indicating the file name
    _char_t* begin = (_char_t*) ptr;
    _char_t* last = NULL;
    for(; *ptr; ++ptr) if(is_path_separator(*ptr)) last = ptr;
    if(last == NULL) last = (_char_t*) path; // Full string is a file name
    else ++last; // Skip path separator
    // Skip to the last double quote
    ptr = last;
    skip_till(&ptr, '"'); // Skip double quote
    // Optionally populate the directory argument
    if(dir != NULL) {
        const size_t len = last - begin - 1;
        // Allocate a new string for the directory
        *dir = malloc((len + 1) * sizeof(_char_t));
        memcpy(*dir, begin, len * sizeof(_char_t));
        (*dir)[len] = '\0';
    }
    // Optionally populate the name argument
    if(name != NULL) {
        const size_t len = ptr - last;
        // Allocate a new string for the name
        *name = malloc((len + 1) * sizeof(_char_t));
        memcpy(*name, last, len * sizeof(_char_t));
        (*name)[len] = '\0';
    }
    return true;
}

#endif // MDRUN_UTILS_H
