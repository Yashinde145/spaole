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
		return (c);
	}

	c = fgetc(Infile);			//Read from input file
	if ('\n' == c)				//Increment line count
		Line++;
	return (c);
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
	while((k = chrpos("0123456789", c)) >= 0){
		val = val * 10 + k;
		c = next();
	}

	//Non-int value, putback
	putback(c);
	return (val);
}


// Scan identifier from input file
// and store it in buf[]. Return identifier's length

static int scanident(int c, char *buf, int lim) {
	int i = 0;

	// Allow digits, alpha and underscores
	while(isalpha(c) || isdigit(c) || '_' == c) {
		//Error if identifier limit length is hit,
		//else append to buf[] and get next char

		if(lim - 1 == i) {
			printf("identifier too long on line %d\n", Line);
			exit(1);
    	} else if (i < lim - 1) {
			buf[i++] = c;
		}
		c = next();
	}


	// Hit non-valid char, put it back
	// NUL-terminate the buf[] and return length

	putback(c);
	buf[i] = '\0';
	return (i);
}


// Given word from input, return the matching
// keyword token number or 0 if it's not a keyword.
// Switch on the first letter so that we don't have
// to waste time strcmp()ing against all keywords.

static int keyword(char *s) {
	switch(*s) {
		case 'p':
				if (!strcmp(s, "print"))
					return (T_PRINT);
				break;
	}
	return (0);
}

// Scan and return the next token found
// Return 1 if token valid, 0 if no tokens left.

int scan(struct token *t){
	int c, tokentype;
	
	//skip whitespace
	c = skip();

	//Determine token based on i/p character
	switch(c){
		case EOF:
			t->token = T_EOF;
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
		case ';':
			t->token = T_SEMI;
			break;
		default:
			// If digit, scan the value
			// literal integer value
			if (isdigit(c)){
				t->intvalue = scanint(c);
				t->token = T_INTLIT;
				break;
			} else if (isalpha(c) || '_' ==c) {
				// Read in a keyword or identifier
				scanident(c, Text, TEXTLEN);

				// If recognised keyword, return that token
				if(tokentype = keyword(Text)) {
					t->token = tokentype;
					break;
				}

				//  Not a recognised keyword, error
				printf("Unrecognised symbol %s on line %d\n", Text, Line);
				exit(1);
			}

			// The character isn't part of any recognised token, error
			printf("Unrecognised character %c on line %d\n", c, Line);
			exit(1);
		}

		//Token found
		return (1);
	}

