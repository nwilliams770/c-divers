#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


bool file_exists(char *fname) {
  if (access(fname, F_OK) != -1) {
    return true;
  } else {
    return false;
  }
}

int exit_with_error(char *error) {
  printf("Error: %s\n", error);
  exit(EXIT_FAILURE);
}

int main(int argc, char *argv[]) {
  // Input: infile outfile

  // Pre-check: Check if 3 arguments given
  if (argc != 3) {
    char error[100];
    sprintf(error, "2 arguments expected, %d provided\nUsage: %s input_file output_file", argc - 1, argv[0]);
    exit_with_error(error);
  }

  char *inputf_name = argv[1];
  char *outputf_name = argv[2];

  // 1 Fail if the output file already exists
  if (file_exists(outputf_name)) {
    char error[50];
    sprintf(error, "Outfile file %s already exists", outputf_name);
    exit_with_error(error);
  }

  // 2 Open the input file if it exists, fail if it doesn't
  FILE *inputf = fopen(inputf_name, "r");
  if (inputf == NULL) {
    char error[50];
    sprintf(error, "Input file %s does not exist", inputf_name);
    exit_with_error(error);
  }

  // 3 Create output file
  FILE *outputf = fopen(outputf_name, "w");

  // 4 Reverse input file & write output to file
  fseek(inputf, 0, SEEK_END);
  int inputf_size = ftell(inputf);
  fseek(inputf, 0, SEEK_SET);

  for (int i = 0; i < inputf_size; i++) {
    // Improvement: increasing chunk size
    fseek(inputf, inputf_size - i - 1, SEEK_SET);
    char c;
    fread((void *)&c, sizeof(c), 1, inputf);
    fwrite((void *)&c, sizeof(c), 1, outputf);
  }

  // 5 Close both files
  fclose(inputf);
  fclose(outputf);
  return 0;
}
