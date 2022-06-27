/**
 * Contains Unix-specific implementation of general functions for creating
 * a Media Downloader process.
 *
 * Update date: 2022-04-28
 * Author: Sune
 */

#include "mdprocess.h"

#include <unistd.h>
#include <stdio.h>

#ifdef __APPLE__
#include <sys/syslimits.h>
#include <mach-o/dyld.h>
#else // not __APPLE__
#include <limits.h>
#endif

#include "constants.h"
#include "utils.h"

// Taken from: https://unix.stackexchange.com/a/317215
static _char_t* current_dir_file_path(const _char_t* rel_path) {
    char buf[PATH_MAX] = { 0 };
#ifdef __APPLE__
    uint32_t size = sizeof(buf);
    if(_NSGetExecutablePath(buf, &size) != 0)
        return NULL;
#else // not __APPLE__
    size_t size = sizeof(buf);
    if(readlink("/proc/self/exe", buf, size) == -1)
        return NULL;
#endif
    const size_t buf_size = strlen(buf) * sizeof(_char_t);
    _char_t* dir = malloc(buf_size);
    if(!get_file_name(buf, &dir, NULL)) return NULL;
    const size_t full_size = buf_size + (strlen(rel_path) + 2) * sizeof(_char_t);
    _char_t* full_path = malloc(full_size);
    snprintf(full_path, full_size, "%s/%s", dir, rel_path);
    return full_path;
}

_char_t* java_executable() {
    return current_dir_file_path("jre/bin/java");
}

_char_t* full_jar_path() {
    return current_dir_file_path("media-downloader.jar");
}

_char_t* command_line_arguments() {
    return "";
}

inline bool is_path_separator(_char_t c) {
    return c == '/';
}

int run_process(const _char_t* exe_path, const _char_t* jar_path, const _char_t* cmd_args) {
    int return_code = EXIT_CODE_SUCCESS;
    // Get the file name from the given path
    _char_t* exe_name;
    if(!get_file_name(exe_path, NULL, &exe_name)) return EXIT_CODE_EXEC_ARGS_FAILURE; // Exit early
    // Prepare the execution arguments
    _char_t* args[] = { exe_name, "-jar", (_char_t*) jar_path, (_char_t*) cmd_args, NULL };
    // Create the process
    if(execvp(exe_path, args) == -1) return_code = EXIT_CODE_EXEC_FAILURE;
    free(exe_name);
    return return_code;
}
