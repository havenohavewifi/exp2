#ifndef YYSTYPE
typedef union {
	char name[100];
	int val;
} yystype;
# define YYSTYPE yystype
# define YYSTYPE_IS_TRIVIAL 1
#endif

void yyerror(char *str);