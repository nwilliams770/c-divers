#include <fcntl.h>
#include <stdio.h>
#include <sys/mman.h>


int main()
{
  // Open the file
  FILE *file = fopen("hello.txt", "r+");
  if (file == NULL)
  {
    perror("Error opening file");
    return 1;
  }

  // Get file size
  if (fseek(file, 0, SEEK_END) != 0)
  {
    perror("Error seeking to the end of file");
    fclose(file);
    return 1;
  }

  size_t file_size = ftell(file);

  if (file_size == -1)
  {
    perror("Error getting file size");
    fclose(file);
    return 1;
  }
  else if (file_size == 0)
  {
    // Handle the case of an empty file
    fclose(file);
    return 0;
  }


  // Memory map the file
  char *file_data = mmap(NULL, file_size, PROT_READ | PROT_WRITE, MAP_SHARED, fileno(file), 0);
  if (file_data == MAP_FAILED)
  {
    perror("Failed to map file to memory");
    fclose(file);
    return 1;
  }

  // Modify data
  if (file_data[0] == 'H')
  {
    file_data[0] = 'J';
  }

  // Write to file
  msync(file_data, file_size, MS_SYNC);

  // Unmap memory and close file
  if (munmap(file_data, file_size) != 0)
  {
    perror("Error unmapping memory");
    close(file);
    return 1;
  }
  close(file);

  return 0;
}