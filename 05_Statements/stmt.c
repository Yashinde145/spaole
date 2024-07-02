#include "defs.h"
#include "data.h"
#include "decl.h"


// Parsing od statements

void statements(void) {
	struct ASTnode *tree;
	int reg;

	while(1) {
		// Match 'print' as first token
		match(T_PRINT, "print");

		// Parse following expressions and
		// generate assembly code
		tree = binexpr(0);
		reg = genAST(tree);
		genprintint(reg);
		genfreeregs();

		// Match following semicolon
		// and stop if EOF

		semi();
		if (Token.token == T_EOF)
			return;
		}
}
