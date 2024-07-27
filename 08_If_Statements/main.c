#include "defs.h"
#define extern_
#include "data.h"
#undef extern_
#include "decl.h"
#include <errno.h>


//Initialise global variables
static void init(){
	Line = 1;
	Putback = '\n';
}


//Print out a usage if started wrong
static void usage(char *prog){
	fprintf(stderr, "Usage: %s infile\n", prog);
	exit(1);
}


//Check args and print usage if there's no correct arg.
//Else open the ip file and call scanfile() to scan tokens
void main(int argc, char *argv[]){
	struct ASTnode *tree;

	if (argc != 2)
		usage(argv[0]);

	init();

	//Open the input file
	if ((Infile = fopen(argv[1], "r")) == NULL){
		fprintf(stderr, "Unable to open %s: %s\n", argv[1], strerror(errno));
	exit(1);
	}

	// Create the output file
  	if ((Outfile = fopen("out.s", "w")) == NULL) {
    	fprintf(stderr, "Unable to create out.s: %s\n", strerror(errno));
    	exit(1);
  	}

	scan(&Token);			// Get the first token from the input
	genpreamble();			// Output the preamble
	tree = compound_statement();			// Parse the statements in the input
	genAST(tree, NOREG, 0);	// // Generate the assembly code for it
	genpostamble();			// Output the postamble
	fclose(Outfile);		// Close the output file and exit
	exit(0);
}

