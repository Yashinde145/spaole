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


//Convrt a binary operator into AST
int arithop(int tokentype){
	switch (tokentype){
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


//Operator precedence for tokens
static int OpPrec[] = {0, 10, 10, 20, 20, 0};


static int op_precedence(int tokentype){
	int prec = OpPrec[tokentype];
	if (prec == 0){
		fprintf(stderr, "syntax error on line %d, token %d\n", Line, tokentype);
		exit(1);
	}
	return (prec);
}


//Check we have binary operator and return its precedence.
struct ASTnode *binexpr(int ptp){
	struct ASTnode *left, *right;
	int tokentype;

	//Get int literal on left and fetch next token
	left = primary();

	//If no tokens left, return just left node
	tokentype = Token.token;
	if (tokentype == T_EOF)
		return (left);

	//While precedence of this token is more than previous token precedence
	while(op_precedence(tokentype) > ptp){
		//Get the next int literal
		scan(&Token);

		//Recursively call binexpr() with precedence of token to build a sub-tree
		right = binexpr(OpPrec[tokentype]);

		//Join that sub-tree with current. Convert the token into AST operation at same time.
		left = mkastnode(arithop(tokentype), left, right, 0);

		//Update details of current token. If no tokens left, return left node
		tokentype = Token.token;
		if(tokentype == T_EOF)
			return (left);
	}
	//Return tree when precedence is same or lower
	return (left);
}

