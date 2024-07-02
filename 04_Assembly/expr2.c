#include "defs.h"
#include "data.h"
#include "decl.h"


//Parsing of expr with full recursive descent
//Parse a primary factor and return AST node representing it
static struct ASTnode *primary(void){
	struct ASTnode *n;

	//For INTLIT token, make a leaf AST node
	//and scan it in next token. Else syntax
	//error for other token type.
	switch(Token.token){
		case T_INTLIT:
			n = mkastleaf(A_INTLIT, Token.intvalue);
			scan(&Token);
			return (n);
		default:
			fprintf(stderr, "syntax error on line %d, token %d\n", Line, Token.token);
			exit(1);
	}
}


//Convert a binary operator token into AST operation
static int arithop(int tok){
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
			fprintf(stderr, "suntax error on line %d, token %d\n", Line, tok);
		exit(1);		
	}
}


struct ASTnode *additive_expr(void);


//Return AST tree whose root is '*' or '/' binary operator
struct ASTnode *multiplicative_expr(void){
	struct ASTnode *left, *right;
	int tokentype;

	//Get int literal on left and fetch next token
	left = primary();

	//If no tokens left, return left node
	tokentype = Token.token;
	if(tokentype == T_EOF)
		return (left);

	//While the token us '*' or '/'
	while ((tokentype == T_STAR) || (tokentype == T_SLASH)){
		//Fetch next int literal
		scan(&Token);
		right = primary();

		//Join that with left int literal
		left =  mkastnode(arithop(tokentype), left, right, 0);
		//Update details of current token
		//if no tokens left, return left node
		tokentype = Token.token;
		if(tokentype == T_EOF)
			break;
	}
	// Return whatever tree is created
	return (left);
}


// Return an AST tree whose root is a '+' or '-' binary operator
struct ASTnode *additive_expr(void) {
  struct ASTnode *left, *right;
  int tokentype;

  // Get the left sub-tree at a higher precedence
  left = multiplicative_expr();

  // If no tokens left, return the left node
  tokentype = Token.token;
  if (tokentype == T_EOF)
    return (left);

  // Cache the '+' or '-' token type

  // Loop working on token at our level of precedence
  while (1) {
    // Fetch in the next integer literal
    scan(&Token);

    // Get the right sub-tree at a higher precedence than us
    right = multiplicative_expr();

    // Join the two sub-trees with our low-precedence operator
    left = mkastnode(arithop(tokentype), left, right, 0);

    // And get the next token at our precedence
    tokentype = Token.token;
    if (tokentype == T_EOF)
      break;
  }

  // Return whatever tree we have created
  return (left);
}

struct ASTnode *binexpr(int n) {
  return (additive_expr());
}
