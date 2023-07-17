#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  if (argc != 2) {
      fprintf(stderr, "Usage: %s <input_file>\n", argv[0]);
      exit(1);
  }

  // Attempt to open the file
  int file_descriptor = open(argv[1], O_RDONLY);
  if (file_descriptor == -1) {
      perror("Failed to open file");
      exit(1);
  }

  // Get the file size
  off_t file_size = lseek(file_descriptor, 0, SEEK_END);
  if (file_size == -1) {
      perror("Failed to get file size");
      if (close(file_descriptor) == -1) {
          perror("Failed to close file");
      }
      exit(1);
  }

  if (file_size == 0) {
      printf("Input file is empty.\n");
      if (close(file_descriptor) == -1) {
          perror("Failed to close file");
      }
      exit(1);
  }

  // Allocate virtual memory for file
  int *mapped_data = mmap(NULL, (size_t)file_size, PROT_READ, MAP_PRIVATE, file_descriptor, 0);
  if (mapped_data == MAP_FAILED) {
      perror("Failed to mmap input file");
      if (close(file_descriptor) == -1) {
          perror("Failed to close file");
      }
      exit(1);
  }

  // Write the mapped data to stdout
  ssize_t bytes_written = write(STDOUT_FILENO, mapped_data, file_size);
  if (bytes_written == -1) {
      perror("Failed to write to stdout");
      if (munmap(mapped_data, (size_t)file_size) == -1) {
          perror("Failed to munmap input file data");
      }
      if (close(file_descriptor) == -1) {
          perror("Failed to close file");
      }
      exit(1);
  }

  // Free the mapped memory
  if (munmap(mapped_data, (size_t)file_size) == -1) {
      perror("Failed to munmap input file data");
  }

  // Close the file
  if (close(file_descriptor) == -1) {
      perror("Failed to close file");
  }

  return 0;
}