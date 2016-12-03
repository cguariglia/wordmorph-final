/* WORDMORPH - FINAL
 * Authors: Ana Carolina Lima & Carina Fernandes
 * */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"
#include "words.h"

int main(int argc, char **argv) {
	FILE *fpdic, *fpprob;
	
	if(argc != 3) 
		exit(0);
	
	/* Verify file extensions and open Input files*/
	fpdic = fcheck(argv[1], ".dic");
	fpprob = fcheck(argv[2], ".pal");
  
    problemSolver(fpdic, fpprob);
	
    fclose(fpdic);
	fclose(fpprob);
 
	return 0;
}


