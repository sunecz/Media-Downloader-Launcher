/**
 * Run the Media Downloader JAR file using a custom JRE.
 *
 * Update date: 2022-08-03
 * Author: Sune
 */

#include <stdlib.h>
#include <stdio.h>

#include "constants.h"
#include "mdprocess.h"

static inline void error(const char* value) {
    fprintf(stderr, "An error occurred: %s\n", value);
}

static inline void error_unknown(int error_code) {
    fprintf(stderr, "An unknown error occurred: %d\n", error_code);
}

int main(int argc, char** argv) {
    int return_code = EXIT_CODE_SUCCESS;

    // Run the extractor only if the JAR file does not exist
    // and the extractor file exists.
    if(!jar_file_exists()) {
        return_code = EXIT_CODE_FAILURE;

        if(extractor_file_exists()
                && (return_code = run_extract()) != EXIT_CODE_SUCCESS) {
            error("Unable to extract the application.");
        }

        if(return_code == EXIT_CODE_FAILURE) {
            error("Extractor file does not exist.");
        }
    }

    if(return_code == EXIT_CODE_SUCCESS) {
        _char_t* exe_path = java_executable();
        _char_t* jar_path = full_jar_path();
        _char_t* cmd_args = command_line_arguments();

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
    }

    return return_code;
}
