#include "defs.h"
#include "data.h"
#include "decl.h"


//generic code gen

//Given AST, generate assembly code recursively
int genAST(struct ASTnode *n){
	int leftreg, rightreg;

	//Get the left and right sub-tree values
	if(n->left)
		leftreg = genAST(n->left);
	if(n->right)
		rightreg = genAST(n->right);


	switch(n->op){
		case A_ADD:
			return (cgadd(leftreg, rightreg));
		case A_SUBTRACT:
			return (cgsub(leftreg,rightreg));
	    case A_MULTIPLY:
			return (cgmul(leftreg,rightreg));
	    case A_DIVIDE:
			return (cgdiv(leftreg,rightreg));
	    case A_INTLIT:
			return (cgload(n->intvalue));
	    default:
			fprintf(stderr, "Unknown AST operator %d\n", n->op);
			exit(1);
	}
}


void genpreamble() {
	cgpreamble();
}

void genpostamble() {
	cgpostamble();
}

void genfreeregs() {
	freeall_registers();
}

void genprintint(int reg) {
	cgprintint(reg);
}
