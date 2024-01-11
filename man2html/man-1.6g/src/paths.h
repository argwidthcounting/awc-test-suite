/*
 * Generated automatically from paths.h.in by the
 * configure script.
 */
/* paths.h - included in man-config.c */
/*
 * Define the absolute path to the configuration file and programs used.
 * (If no configuration file is found then the preset values are used.)
 */
#ifndef CONFIG_FILE
#define CONFIG_FILE "/usr/lib/man.conf"
#endif

static struct paths {
    char *name;
    char *path;			/* path plus command options - never NULL */
} paths[] = {
    { "MANBIN",	"" },		/* value unused */
    { "APROPOS",  "/usr/bin/apropos" },
    { "WHATIS",   "/usr/bin/whatis" },
    { "TROFF",	"/bin/groff -Tps -mandoc" },
    { "NROFF",	"/bin/nroff -Tlatin1 -mandoc" },
    { "JNROFF",	"/bin/groff -Tnippon -mandocj" },
    { "EQN",	"/bin/geqn -Tps" },
    { "NEQN",	"/bin/geqn -Tlatin1" },
    { "JNEQN",	"/bin/geqn -Tnippon" },
    { "TBL",	"/bin/gtbl" },
    { "COL",	"" },
    { "REFER",	"" },
    { "PIC",	"/bin/gpic" },
    { "VGRIND",	"" },
    { "GRAP",	"" },
    { "PAGER",	"/bin/less -is" },
    { "BROWSER","/bin/less -is" },
    { "HTMLPAGER", "/bin/cat" },
    { "CMP",	"/bin/cmp -s" },
    { "CAT",	"/bin/cat" },
    { "COMPRESS",	"/bin/xz" },
    { "COMPRESS_EXT", ".xz" }, /* not a path, just a string variable */
    { "DECOMPRESS",	"/bin/unxz -c" },
    { "MANSECT",  "1:1p:8:2:3:3p:4:5:6:7:9:0p:tcl:n:l:p:o"},          /* idem */
    { "MANDEFOPTIONS", ""}                /* idem */
};
