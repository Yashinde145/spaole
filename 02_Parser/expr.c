#include "defs.h"
#include "data.h"
#include "decl.h"


//Parsing expr and return AST node
static struct ASTnode *primary(void){
	struct ASTnode *n;


//For INTLIT token, generate leaf AST node and scan
//next token. Else syntax error for other token types.
switch (Token.token){
	case T_INTLIT:
		n = mkastleaf(A_INTLIT, Token.intvalue);
		scan(&Token);
		return (n);
	default:
		fprintf(stderr, "syntax error on line %d\n", Line);
		exit(1);
	}
}


//Convrt a token into AST
int arithop(int tok){
	switch (tok){
		case T_PLUS:
			return (A_ADD);
		case T_MINUS:
			return (A_SUBTRACT);
		case T_STAR:
			return (A_MULTIPLY);
		case T_SLASH:
			return (A_DIVIDE);
		default:
			fprintf(stderr, "unknown token is arithop() on line %d\n", Line);
		exit(1);
	}
}


//Return AST tree whose root is ninary operator
struct ASTnode *binexpr(void){
	struct ASTnode *n, *left, *right;
	int nodetype;

	//Get int literal on left and fetch next token
	left = primary();

	//If no tokens left, return just left node
	if (Token.token == T_EOF)
		return (left);

	//Convert token into node type
	nodetype = arithop(Token.token);

	//Get the next token
	scan(&Token);

	//Recursively get the right-hand tree
	right = binexpr();

	//Now build a tree with both sub-trees
	n = mkastnode(nodetype, left, right, 0);
	return (n);
}

