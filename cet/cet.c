#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#define BLOCK_SIZE 1024
int fd1,fd2;

void clean(){
  if(fd1 != -1)
    close(fd1);
  if(fd2 != -1)
    close(fd2);
}

int main(int argc, char **argv){
  if(argc < 3){
    puts("Usage:\ncet file1 file2 - Appens file2 to file1.");
    return 1;
  }

  fd1 = open(argv[1],O_RDWR);
  fd2 = open(argv[2],O_RDONLY);
  if(fd1 * fd2 < 0){
    puts("An error occured opening one of the files.");
    clean();
    return 2;
  }

  if( lseek(fd1,0,SEEK_END) == (off_t)-1){
    puts("An error occured seeking to the end of the file.");
    clean();
    return 4;
  } //seek to the end of the file.

  struct stat st;
  if(stat(argv[2],&st) == -1){
    puts("Unable to stat file2 - this shouldn't happen!");
    clean();
    return 3;
  }

  char *buffer = malloc(BLOCK_SIZE);
  if(!buffer){
      puts("Unable to allocate memory blocks.");
      clean();
      return 4;
  }

  off_t BytesRead = 0;
  off_t BytesWritten = 0;
  while(BytesWritten < st.st_size){
      off_t ret = read(fd2,buffer,BLOCK_SIZE);
      if(ret == -1){
        puts("An error occured during the append process.\nSafe exit.");
        clean();
        return 3;
      }
      BytesRead += ret;
      off_t ret2 = write(fd1,buffer,ret);
      if(ret2 == -1){
        puts("An error occured during the append process.\nUnsafe exit.");
        clean();
        return 5;
      }
      BytesWritten += ret2;
      //ignores partial writes - assuming that if I read a whole block writing a whole block should be fine.
      //This is definitely not safe.
  }
  if(BytesWritten != BytesRead){
    puts("The process did not execute correctly.");
    printf("Dump:\n Written %lu\n Read %lu\n",BytesWritten,BytesRead);
    return 6;
  }
  clean();
  puts("File concatenated.");
  return 0;
}
