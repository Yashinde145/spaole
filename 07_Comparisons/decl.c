#include "defs.h"
#include "data.h"
#include "decl.h"


// Parsing of declarations

// Parse the declarations of variable
void var_declaration(void) {
	// Ensure 'int' token followed by identifier and ';'
	// Add it as known identifier
	match(T_INT, "int");
	ident();
	addglob(Text);
	genglobsym(Text);
	semi();
}


