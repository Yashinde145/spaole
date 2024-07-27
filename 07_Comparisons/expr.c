#include "defs.h"
#include "data.h"
#include "decl.h"


//Parsing expr and return AST node
static struct ASTnode *primary(void){
	struct ASTnode *n;
	int id;

//For INTLIT token, generate leaf AST node and scan
//next token. Else syntax error for other token types.
	switch (Token.token){
		case T_INTLIT:
			n = mkastleaf(A_INTLIT, Token.intvalue);
			break;

		case T_IDENT:
			id = findglob(Text);
			if (id == -1)
				fatals("Unknown variable", Text);
			n = mkastleaf(A_IDENT, id);
			break;

		default:
			fatald("Syntax error, token", Token.token);
	}
	// Scan in the next token and return the leaf node
	scan(&Token);
	return (n);
}


//Convrt a binary operator into AST
static int arithop(int tokentype){
	if (tokentype > T_EOF && tokentype < T_INTLIT)
	return (tokentype);
	fatald("Syntax error, token", tokentype);	
}


//Operator precedence for tokens
static int OpPrec[] = {	0, 10, 10,			// T_EOF, T_PLUS, T_MINUS 
						20, 20,				// T_STAR, T_SLASH
						30, 30,				// T_EQ, T_NE
						40, 40 , 40, 40		// T_LT, T_GT, T_LE, T_GE
};


static int op_precedence(int tokentype){
	int prec = OpPrec[tokentype];
	if (prec == 0)
		fatald("Syntax error, token", tokentype);
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
	if (tokentype == T_SEMI)
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
		if(tokentype == T_SEMI)
			return (left);
	}
	//Return tree when precedence is same or lower
	return (left);
}

