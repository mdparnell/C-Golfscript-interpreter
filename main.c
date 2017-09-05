#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "golf.h"

int main(int argc, char *argv[]) {
  const char *filename = NULL;
  const char *command_text = NULL;

  for (int i = 1; i < argc; i++) {
    if (argv[i][0] != '-') {
      if (filename != NULL) {
        error("The interpreter can only handle one file at once!");
      }
      filename = argv[i];
    }
    else if (strcmp(argv[i], "-r") || strcmp(argv[i], "--run")) {
      if (command_text != NULL) {
        error("Can only run one command-line argument script at a time!");
      }
      else if (++i == argc) {
        error("No command-line script given to run!");
      }
      command_text = argv[i];
    }
    else {
      error("Invalid command-line argument '%s'!", argv[i]);
    }
  }

  if (filename == NULL && command_text == NULL) {
    error("No golfscript file provided!");
  }
  else if (filename != NULL && command_text != NULL) {
    error("Can only run either a command-line script or file, not both!");
  }

  String code;

  if (filename) {
    FILE *file = fopen(argv[1], "r");
    if (file == NULL) {
      error("Unable to open '%s'!", argv[1]);
    }
    code = read_file_to_string(file);
    fclose(file);
  }
  else if (command_text) {
    code = create_string(command_text);
  }

  init_interpreter();
  execute_string(&code);
  end_interpreter();
  free(code.str_data);

  return 0;
}
