#include "defs.h"
#include "data.h"
#include "decl.h"


// Parsing od statements

void print_statement(void) {
	struct ASTnode *tree;
	int reg;

	// Match 'print' as first token
	match(T_PRINT, "print");

	// Parse following expression and generate assembly code
	tree = binexpr(0);
	reg = genAST(tree, -1);
	genprintint(reg);
	genfreeregs();

	//Match following semi colon
	semi();
}


	void assignment_statement (void) {
		struct ASTnode *left, *right, *tree;
		int id;

		// Emsure identifier
		ident();

		// Check it's been defined then make a leaf node for it
		if ((id = findglob(Text) == -1)) {
			fatals("Undeclared variable", Text);
		}
		right = mkastleaf(A_LVIDENT, id);

		// Ensure '='
		match(T_ASSIGN, "=");

		// Parse expressions
		left = binexpr(0);

		// Make assignment AST tree
		tree = mkastnode(A_ASSIGN, left, right, 0);

		// Generate assembly code for assignment
		genAST(tree, -1);
		genfreeregs();

		// Match following ';'
		semi();
}


// Parse statements
void statements(void) {
	while(1) {
		switch (Token.token) {
			case T_PRINT:
				print_statement();
				break;
			case T_INT:
				var_declaration();
				break;
			case T_IDENT:
				assignment_statement();
				break;
			case T_EOF:
				return;
			default:
				fatald("Syntax error, token", Token.token);
		}
	}
}
