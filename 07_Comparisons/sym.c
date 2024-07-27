#include "defs.h"
#include "data.h"
#include "decl.h"

// Symbol table functions

static int Globs = 0;			// Position of next free global symbol slot


// Determine if symbol s is in global symbol table
// Return its slot position or -1 if not found

int findglob(char *s) {
	int i;

	for (i = 0; i < Globs; i++) {
		if (*s == *Gsym[i].name && !strcmp(s, Gsym[i].name)) {
			return (i);
		}
	}
	return (-1);
}


// Get position of new global symbol slot

static int newglob(void) {
	int p;

	if((p = Globs++) >= NSYMBOLS)
		fatal("Too many global symbols");
	return (p);
}


// Add global symbol to symbol table
// return slot number in symbol table
int addglob(char *name) {
	int y;

	// If already in symbol table, return existing slot
	if ((y = findglob(name)) != -1)
		return (y);

	// Otherwise get new slot, fill it in and return slot number
	y = newglob();
	Gsym[y].name = strdup(name);
	return (y);
}


