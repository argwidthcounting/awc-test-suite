#include "defs.h"

#ifndef NULL
#define NULL	((void *) 0)
#endif

int nroff = 1;

#define NROFF (-666)
#define TROFF (-667)

STRDEF *chardef, *strdef, *defdef;
INTDEF *intdef;

static INTDEF standardint[] = {
    { V('n',' '), NROFF, 0, (INTDEF *) NULL },
    { V('t',' '), TROFF, 0, (INTDEF *) NULL },
    { V('o',' '), 1,     0, (INTDEF *) NULL },
    { V('e',' '), 0,     0, (INTDEF *) NULL },
    { V('.','l'), 70,    0, (INTDEF *) NULL },
    { V('.','$'), 0,     0, (INTDEF *) NULL },
    { V('.','A'), NROFF, 0, (INTDEF *) NULL },
    { V('.','T'), TROFF, 0, (INTDEF *) NULL },
    { V('.','V'), 1,     0, (INTDEF *) NULL }, /* the me package tests for this */
    { 0, 0, 0, (INTDEF *) NULL } };

static STRDEF standardstring[] = {
    { V('R',' '), 1, "&#174;", (STRDEF *) NULL },
    { V('l','q'), 2, "``", (STRDEF *) NULL },
    { V('r','q'), 2, "''", (STRDEF *) NULL },
    { 0, 0, (char *) NULL, (STRDEF *) NULL}
};


static STRDEF standardchar[] = {
    { V('*','*'), 1, "*", (STRDEF *) NULL  },	/* math star */
    { V('*','A'), 1, "A", (STRDEF *) NULL  },
    { V('*','B'), 1, "B", (STRDEF *) NULL  },
    { V('*','C'), 2, "Xi", (STRDEF *) NULL  },
    { V('*','D'), 5, "Delta", (STRDEF *) NULL  },
    { V('*','E'), 1, "E", (STRDEF *) NULL  },
    { V('*','F'), 3, "Phi", (STRDEF *) NULL  },
    { V('*','G'), 5, "Gamma", (STRDEF *) NULL  },
    { V('*','H'), 5, "Theta", (STRDEF *) NULL  },
    { V('*','I'), 1, "I", (STRDEF *) NULL  },
    { V('*','K'), 1, "K", (STRDEF *) NULL  },
    { V('*','L'), 6, "Lambda", (STRDEF *) NULL  },
    { V('*','M'), 1, "M", (STRDEF *) NULL  },
    { V('*','N'), 1, "N", (STRDEF *) NULL  },
    { V('*','O'), 1, "O", (STRDEF *) NULL  },
    { V('*','P'), 2, "Pi", (STRDEF *) NULL  },
    { V('*','Q'), 3, "Psi", (STRDEF *) NULL  },
    { V('*','R'), 1, "P", (STRDEF *) NULL  },
    { V('*','S'), 5, "Sigma", (STRDEF *) NULL  },
    { V('*','T'), 1, "T", (STRDEF *) NULL  },
    { V('*','U'), 1, "Y", (STRDEF *) NULL  },
    { V('*','W'), 5, "Omega", (STRDEF *) NULL  },
    { V('*','X'), 1, "X", (STRDEF *) NULL  },
    { V('*','Y'), 1, "H", (STRDEF *) NULL  },
    { V('*','Z'), 1, "Z", (STRDEF *) NULL  },
    { V('*','a'), 5, "alpha", (STRDEF *) NULL },
    { V('*','b'), 4, "beta", (STRDEF *) NULL },
    { V('*','c'), 2, "xi", (STRDEF *) NULL },
    { V('*','d'), 5, "delta", (STRDEF *) NULL },
    { V('*','e'), 7, "epsilon", (STRDEF *) NULL },
    { V('*','f'), 3, "phi", (STRDEF *) NULL },
    { V('*','g'), 5, "gamma", (STRDEF *) NULL },
    { V('*','h'), 5, "theta", (STRDEF *) NULL },
    { V('*','i'), 4, "iota", (STRDEF *) NULL },
    { V('*','k'), 5, "kappa", (STRDEF *) NULL },
    { V('*','l'), 6, "lambda", (STRDEF *) NULL },
    { V('*','m'), 1, "&#181;", (STRDEF *) NULL  },
    { V('*','n'), 2, "nu", (STRDEF *) NULL },
    { V('*','o'), 1, "o", (STRDEF *) NULL },
    { V('*','p'), 2, "pi", (STRDEF *) NULL },
    { V('*','q'), 3, "psi", (STRDEF *) NULL },
    { V('*','r'), 3, "rho", (STRDEF *) NULL },
    { V('*','s'), 5, "sigma", (STRDEF *) NULL },
    { V('*','t'), 3, "tau", (STRDEF *) NULL },
    { V('*','u'), 7, "upsilon", (STRDEF *) NULL },
    { V('*','w'), 5, "omega", (STRDEF *) NULL },
    { V('*','x'), 3, "chi", (STRDEF *) NULL },
    { V('*','y'), 3, "eta", (STRDEF *) NULL },
    { V('*','z'), 4, "zeta", (STRDEF *) NULL },
    { V('+','-'), 1, "&#177;", (STRDEF *) NULL  },
    { V('1','2'), 1, "&#189;", (STRDEF *) NULL  },
    { V('1','4'), 1, "&#188;", (STRDEF *) NULL  },
    { V('3','4'), 1, "&#190;", (STRDEF *) NULL  },
    { V('F','i'), 3, "ffi", (STRDEF *) NULL  },
    { V('F','l'), 3, "ffl", (STRDEF *) NULL  },
    { V('a','a'), 1, "&#180;", (STRDEF *) NULL  },
    { V('a','p'), 1, "~", (STRDEF *) NULL  },
    { V('b','r'), 1, "|", (STRDEF *) NULL  },
    { V('b','u'), 1, "*", (STRDEF *) NULL  }, 	/* bullet */
    { V('b','v'), 1, "|", (STRDEF *) NULL  },
    { V('c','i'), 1, "o", (STRDEF *) NULL  }, 	/* circle */
    { V('c','o'), 1, "&#169;", (STRDEF *) NULL  },
    { V('c','t'), 1, "&#162;", (STRDEF *) NULL  },
    { V('d','e'), 1, "&#176;", (STRDEF *) NULL  },
    { V('d','g'), 1, "+", (STRDEF *) NULL  }, 	/* dagger */
    { V('d','i'), 1, "&#247;", (STRDEF *) NULL  },
    { V('e','m'), 3, "---", (STRDEF *) NULL  }, 	/* em dash */
    { V('e','n'), 1, "-", (STRDEF *) NULL }, 	/* en dash */
    { V('e','q'), 1, "=", (STRDEF *) NULL  },
    { V('e','s'), 1, "&#216;", (STRDEF *) NULL  },
    { V('f','f'), 2, "ff", (STRDEF *) NULL  },
    { V('f','i'), 2, "fi", (STRDEF *) NULL  },
    { V('f','l'), 2, "fl", (STRDEF *) NULL  },
    { V('f','m'), 1, "&#180;", (STRDEF *) NULL  },
    { V('g','a'), 1, "`", (STRDEF *) NULL  },
    { V('h','y'), 1, "-", (STRDEF *) NULL  },
    { V('l','c'), 2, "|&#175;", (STRDEF *) NULL  },
    { V('i','f'), 8, "Infinity", (STRDEF *) NULL }, /* infinity sign */
    { V('i','s'), 8, "Integral", (STRDEF *) NULL }, /* integral sign */
    { V('l','f'), 2, "|_", (STRDEF *) NULL  },
    { V('l','k'), 1, "<FONT SIZE=\"+2\">{</FONT>", (STRDEF *) NULL  },
    { V('m','i'), 1, "-", (STRDEF *) NULL  },
    { V('m','u'), 1, "&#215;", (STRDEF *) NULL  },
    { V('n','o'), 1, "&#172;", (STRDEF *) NULL  },
    { V('o','r'), 1, "|", (STRDEF *) NULL  },
    { V('p','d'), 1, "d", (STRDEF *) NULL }, 	/* partial derivative */
    { V('p','l'), 1, "+", (STRDEF *) NULL  },
    { V('r','c'), 2, "&#175;|", (STRDEF *) NULL  },
    { V('r','f'), 2, "_|", (STRDEF *) NULL  },
    { V('r','g'), 1, "&#174;", (STRDEF *) NULL  },
    { V('r','k'), 1, "<FONT SIZE=\"+2\">}</FONT>", (STRDEF *) NULL  },
    { V('r','n'), 1, "&#175;", (STRDEF *) NULL  },
    { V('r','u'), 1, "_", (STRDEF *) NULL  },
    { V('s','c'), 1, "&#167;", (STRDEF *) NULL  },
    { V('s','l'), 1, "/", (STRDEF *) NULL  },
    { V('s','q'), 2, "[]", (STRDEF *) NULL  },
    { V('t','s'), 1, "s", (STRDEF *) NULL }, 	/* should be terminal sigma */
    { V('u','l'), 1, "_", (STRDEF *) NULL  },
    { V('>','='), 1, "&gt;", (STRDEF *) NULL },
    { V('<','='), 1, "&lt;", (STRDEF *) NULL },
    { 0, 0, (char *) NULL, (STRDEF *) NULL  }
};

void stdinit(void) {
    STRDEF *stdf;
    int i;

    stdf = &standardchar[0];
    i = 0;
    while (stdf->nr) {
	if (stdf->st) stdf->st = xstrdup(stdf->st);
	stdf->next = &standardchar[i];
	stdf = stdf->next;
	i++;
    }
    chardef=&standardchar[0];

    stdf=&standardstring[0];
    i=0;
    while (stdf->nr) {
	 /* waste a little memory, and make a copy, to avoid
	    the segfault when we free non-malloced memory */
	if (stdf->st) stdf->st = xstrdup(stdf->st);
	stdf->next = &standardstring[i];
	stdf = stdf->next;
	i++;
    }
    strdef=&standardstring[0];

    intdef=&standardint[0];
    i=0;
    while (intdef->nr) {
	if (intdef->nr == NROFF) intdef->nr = nroff; else
	if (intdef->nr == TROFF) intdef->nr = !nroff;
	intdef->next = &standardint[i];
	intdef = intdef->next;
	i++;
    }
    intdef = &standardint[0];
    defdef = (STRDEF *) NULL;
}
