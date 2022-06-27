/**
 * Run the Media Downloader JAR file using a custom JRE.
 *
 * Update date: 2022-04-28
 * Author: Sune
 */

#include <stdlib.h>
#include <stdio.h>

#include "constants.h"
#include "mdprocess.h"

static inline void error(const char* value) {
    fprintf(stderr, "An error occurred: %s", value);
}

static inline void error_unknown(int error_code) {
    fprintf(stderr, "An unknown error occurred: %d", error_code);
}

int main(int argc, char** argv) {
    _char_t* exe_path = java_executable();
    _char_t* jar_path = full_jar_path();
    _char_t* cmd_args = command_line_arguments();
    int return_code;
    if((return_code = run_process(exe_path, jar_path, cmd_args))) {
        switch(return_code) {
            case EXIT_CODE_EXEC_ARGS_FAILURE:
                error("Unable to parse exec arguments.");
                break;
            case EXIT_CODE_EXEC_FAILURE:
                error("Unable to execute the application.");
                break;
            default:
                error_unknown(return_code);
                break;
        }
    }
    free(exe_path);
    free(jar_path);
    return return_code;
}
