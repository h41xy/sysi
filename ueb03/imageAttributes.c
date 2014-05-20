#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>

main(int argc, char *argv[]){
  int fd;

//  Open File
  fd = open(argv[1], O_RDONLY);
  if(fd == -1){
    perror("Fehler");
    return;
  }

//  Set offset for type
  off_t fileOff;
  fileOff = lseek(fd, 0x6e, SEEK_SET);
  if(fileOff == -1){
    perror("Fehler");
    return;
  }

// Read type with offset
  char cameraType[19];
  if((read(fd, cameraType, 20)) == -1){
    perror("Fehler");
    return;
  }

// Set offset for date
  fileOff = lseek(fd, 0x11c, SEEK_SET);
  if(fileOff == -1){
    perror("Fehler");
    return;
  }

// Read date with offset
  char date[19];
  if((read(fd, date, 20)) == -1){
      perror("Fehler");
      return;
  }

// Close File
  if((close(fd)) == -1){
    perror("Fehler");
    return;
  }

// Output
  printf("Kameramodel:\t\t%s\n", &cameraType);
  printf("Datum der Aufnahme:\t%s\n", &date);
}
