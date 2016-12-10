/* WORDMORPH - FINAL
 * Authors: Ana Carolina Lima (83993) & Carina Fernandes (84019)
 * */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"
#include "words.h"

int main(int argc, char **argv) {
	FILE *fpdic, *fpprob, *fppath;
    char *filename;
	
    /* args: ./wordmorph .dic .pal */
	if(argc != 3) 
		exit(0);
	
	/* Verify file extensions and open input files*/
	fpdic = fcheck(argv[1], ".dic");
	fpprob = fcheck(argv[2], ".pal");
  
    filename = outputFileExtension(argv[2]);
    fppath = fopen(filename, "w");
  
    problemSolver(fpdic, fpprob, fppath);
	
    /* Close every file */
    fclose(fppath);
    free(filename);
    fclose(fpdic);
	fclose(fpprob);
 
	return 0;
}



