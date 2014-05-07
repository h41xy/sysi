#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <pwd.h>


int main(int argc, char **argv){
  // Arguments test
    int i;
    for (i = 1; i < argc; ++i)
      printf("%s\n", argv[i]);

  // Get file info in struct
    char *pathname;
    pathname = argv[1];
    printf("%s\n", pathname);

    struct stat fileStat;
    struct passwd *pwd;
    int accessRights;
    struct tm info;

  // Get File Statistics
    lstat(pathname, &fileStat);

  // Get User Informations
    pwd = getpwuid(fileStat.st_uid); 

  // Get Accessrights
    accessRights = (fileStat.st_mode & S_IRWXO + S_IRWXG + S_IRWXU); 

    printf("File type:                ");
    switch (fileStat.st_mode & S_IFMT) {
      case S_IFBLK:  printf("block device\n");            break;
      case S_IFCHR:  printf("character device\n");        break;
      case S_IFDIR:  printf("directory\n");               break;
      case S_IFIFO:  printf("FIFO/pipe\n");               break;
      case S_IFLNK:  printf("symlink\n");                 break;
      case S_IFREG:  printf("regular file\n");            break;
      case S_IFSOCK: printf("socket\n");                  break;
      default:       printf("unknown?\n");                break;
    }
    printf("Username:\t%s\n", pwd->pw_name);
    printf("User ID:\t%d\n", fileStat.st_uid);
    printf("Group ID:\t%d\n", fileStat.st_gid);
    printf("Access:\t\t%o\n", accessRights);
    printf("Last Access:\tMYASS\n");

    return 0;
}
