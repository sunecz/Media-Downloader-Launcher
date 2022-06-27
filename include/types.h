/**
 * Contains common types for use in various implementations.
 *
 * Update date: 2022-04-28
 * Author: Sune
 */

#pragma once

#ifndef MDRUN_TYPES_H
#define MDRUN_TYPES_H

#ifdef _WIN32
#include <wchar.h>
typedef wchar_t _char_t;
#else // not _WIN32
typedef char _char_t;
#endif

#endif // MDRUN_TYPES_H
