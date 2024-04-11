#include "defs.h"
#include "data.h"
#include "decl.h"


//Lexical scanning
static int chrpos(char *s, int c){
	char *p;

	p = strchr(s, c);
	return (p? p - s : -1);
}


// Get next char from input file
static int next(void){
	int c;

	if(Putback){				//Use char put
		c = Putback;			//back if there is one
		Putback = 0;
		return c;
	}

	c = fgetc(Infile);			//Read from input file
	if ('\n' == c)				//Increment line count
		Line++;
	return c;
	}


// Put back an unwanted character
static void putback(int c){
	Putback = c;
}


// Read and skip whitespaces
static int skip(void){
	int c;

	c = next();
	while(' ' == c || '\t' == c || '\n' == c || '\r' == c || '\f' == c){
		c = next();
	}
	return (c);
}


//Scan and return integer literal value from file
static int scanint(int  c){
	int k, val = 0;

	//Convert each char into int value
	while((k = chrpos((char *) "0123456789", c)) >= 0){
		val = val * 10 + k;
		c = next();
	}

	//Non-int value, putback
	putback(c);
	return val;
}


// Scan and return the next token found
// Return 1 if token valid, 0 if no tokens left.

int scan(struct token *t){
	int c;
	
	//skip whitespace
	c = skip();

	//Determine token based on i/p character
	switch(c){
		case EOF:
			return (0);
		case '+':
			t->token = T_PLUS;
			break;
		case '-':
			t->token = T_MINUS;
			break;
		case '*':
			t->token = T_STAR;
			break;
		case '/':
			t->token = T_SLASH;
			break;
		default:
			// If digit, scan the value
			if (isdigit(c)){
				t->intvalue = scanint(c);
				t->token = T_INTLIT;
				break;
			}

			printf("Unrecognised character %c on line %d\n", c, Line);
			exit(1);
		}

		//Token found
		return (1);
	}

