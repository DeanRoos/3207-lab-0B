#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main (int argc, char *argv[]){

  if (argc < 3){ //dealing with only 1 argument
		printf("%s", "tucp: incorrect arguments. Exiting program.\n");
		return 1;
	}

  //for every possible command, the first argument must be an existing file. 
  //I'm going to first make sure that this is true and return an error if not.
  struct stat buf;
  stat(argv[1], &buf);
  if (!S_ISREG(buf.st_mode)){
    puts("tucp: invalid source file name. Exiting program.");
    return 1;
  }

}