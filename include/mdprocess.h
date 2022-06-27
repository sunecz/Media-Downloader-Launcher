/**
 * Contains general functions for creating a Media Downloader process.
 *
 * Update date: 2022-04-28
 * Author: Sune
 */

#pragma once

#ifndef MDRUN_MDPROCESS_H
#define MDRUN_MDPROCESS_H

#include <stdbool.h>
#include "types.h"

_char_t* java_executable();
_char_t* full_jar_path();
_char_t* command_line_arguments();
bool is_path_separator(_char_t c);
int run_process(const _char_t* exe_path, const _char_t* jar_path, const _char_t* cmd_args);

#endif // MDRUN_MDPROCESS_H
