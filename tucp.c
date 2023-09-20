#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>

//function prototype for dynamic string combination for file names in directories (from part A)
char *fileCombine(const char *a, char *b);

int main (int argc, char *argv[]){

  if (argc < 3){ //if only 1 argument, print error
		printf("%s", "tucp: too few arguments. Exiting program.\n");
		return 1;
	}

  //for every possible command, the first argument must be an existing file. 
  //this makes sure that this is true and return an error if not.

  //creating a buffer stat
  struct stat buf;
  stat(argv[1], &buf);

  if (!S_ISREG(buf.st_mode)){ //st_mode is a member of stat struct
    puts("tucp: invalid source file name. Exiting program.");
    return 1;
  }

  //Now dealing with 2 args
  if (argc == 3){
    
    //calling stat on the last arg
    stat(argv[2], &buf);

    //if second arg is directory name, copy it to directory
    if(S_ISDIR(buf.st_mode)){

      //using name combining function
      char* newName = fileCombine(argv[2], argv[1]);

      //declairing files
      FILE *orig, *copy;

      //opening files 
      orig = fopen(argv[1], "r");
      copy = fopen(newName, "w");

      //error checking on open
      if (orig == NULL || copy == NULL){
        printf("%s", "tucp: error opening specified files. Exiting program.");
        return 1;
      }

      //creating a buffer array to copy things into 
      char buffer[BUFSIZ];
      size_t b;

      //reading from orig and writing to copy
      while ((b = fread(buffer, 1, sizeof(buffer), orig))) {
        fwrite(buffer, 1, b, copy);
      }

      //closing files
      fclose(orig);
      fclose(copy);


			free(newName); //freeing the memory

    } else { //this is when copying into the same directory with a different name

      //preventing trying to copy a file to itself
      if (strcmp(argv[1], argv[2]) == 0){

        printf("%s", "tuls: cannot copy file to itself. Exiting program");
        return 1;

      }


      //creating files
      FILE *orig, *copy;

      orig = fopen(argv[1], "r");
      copy = fopen(argv[2], "w");

      //error checking on open
      if (orig == NULL || copy == NULL){
        printf("%s", "tucp: error opening specified files. Exiting program.");
        return 1;
      }

      //buffer
      char buffer[BUFSIZ];
      size_t b;

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

      //at this point it just does what we did before for 2 args with a directory using a for loop

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
        size_t b;

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