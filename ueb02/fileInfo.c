#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <pwd.h>
#include <errno.h>


int main(int argc, char **argv){
    struct stat fileStat;
    struct passwd *pwd;
    int accessRights;
 
   time_t timeT;
	char *curFileName;



while(--argc > 0){
  // Get File Statistics
	curFileName = argv[argc];
printf("\nFile:\t%s\n", curFileName);
    errno = lstat(curFileName, &fileStat);
	if(errno == -1){
		perror("Error: ");
		return(errno);

	}

  // Get User Informations
    pwd = getpwuid(fileStat.st_uid); 

  // Get Accessrights
    accessRights = (fileStat.st_mode & S_IRWXO + S_IRWXG + S_IRWXU); 


    printf("File type:\t");
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
    printf("Last Access:\t%s", ctime(&fileStat.st_atime));
	printf("Last Modify:\t%s", ctime(&fileStat.st_mtime));
        printf("Last Change:\t%s", ctime(&fileStat.st_ctime));
	printf("File Birth:\t%s", ctime(&fileStat.st_birthtime));
}

    return 0;
}
