#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

char *fileCombine(const char *a, char *b);

int main (int argc, char *argv[]){

  if (argc < 3){ //dealing with only 1 argument
		printf("%s", "tucp: too few arguments. Exiting program.\n");
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

  //Now dealing with 2 args
  if (argc == 3){
    
    stat(argv[2], &buf);

    //if second arg is directory name, copy it to directory
    if(S_ISDIR(buf.st_mode)){

      puts("yup that's a directory");

      char* newName = fileCombine(argv[2], argv[1]);

      FILE *orig, *copy;

      orig = fopen(argv[1], "r");
      copy = fopen(newName, "w");

      //error checking on open
      if (orig == NULL || copy == NULL){
        printf("%s", "tucp: error opening specified files. Exiting program.");
        return 1;
      }

      char buffer[BUFSIZ];
      int b;

      while ((b = fread(buffer, 1, sizeof(buffer), orig))) {
        fwrite(buffer, 1, b, copy);
      }

      fclose(orig);
      fclose(copy);

			free(newName); //freeing the memeory

    } else {

      FILE *orig, *copy;

      orig = fopen(argv[1], "r");
      copy = fopen(argv[2], "w");

      //error checking on open
      if (orig == NULL || copy == NULL){
        printf("%s", "tucp: error opening specified files. Exiting program.");
        return 1;
      }

      char buffer[BUFSIZ];
      int b;

      while ((b = fread(buffer, 1, sizeof(buffer), orig))) {
        fwrite(buffer, 1, b, copy);
      }

      fclose(orig);
      fclose(copy);

    }


  } else {

    //Now more than 2 args

    //If there is more than 2 args, last arg must be a directory. Checking here if not

    stat(argv[(argc - 1)], &buf);

    //if last arg is not a directory name, print out error
    if(!S_ISDIR(buf.st_mode)){   
      printf("%s", "tucp: incorrect arguments. Final argument must be direcory. Exiting program.");
      return 1;
    } else {

      //at this point we can really just do what we did before for 2 args with a directory using a for loop

      for (size_t i = 1; i < argc - 1; i++){

        char* newName = fileCombine(argv[(argc - 1)], argv[i]);

        FILE *orig, *copy;

        orig = fopen(argv[i], "r");
        copy = fopen(newName, "w");

      //error checking on open
        if (orig == NULL || copy == NULL){
          printf("%s", "tucp: error opening specified files. Exiting program.");
          return 1;
        }

        char buffer[BUFSIZ];
        int b;

        while ((b = fread(buffer, 1, sizeof(buffer), orig))) {
          fwrite(buffer, 1, b, copy);
        }

        fclose(orig);
        fclose(copy);

			  free(newName); //freeing the memeory



      }

    }

  }

  
}

//made this for part A might as well use it
char *fileCombine(const char *a, char *b) {
	char *ret = malloc(strlen(a) + strlen(b) + 2);
	int x = 0;
	int y = 0;

	for (x = 0; (ret[y] = a[x]) != '\0'; ++x, ++y);//copying first string to array
	ret[y] = '/'; //adding a /
	y++;
	for (x = 0; (ret[y] = b[x]) != '\0'; ++x, ++y); //copying second string to array
	return ret; //returning
}