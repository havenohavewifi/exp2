%{
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	#include "define.h"
	#include "y.tab.h"
	extern YYSTYPE yylval;
%}
letter			[a-zA-Z]


%%
"CREATE TABLE"	{return CREATE_TABLE;}
"DROP TABLE"	{return DROP_TABLE;}
"INSERT INTO"	{return INSERT;}
"VALUES"		{return VALUES;}
"DELETE FROM"	{return DELETE;}
"SELECT"		{return SELECT;}
"FROM"			{return FROM;}
"WHERE"			{return WHERE;}
"ORDER BY"		{return ORDER_BY;}
"AND"			{return AND;}
"OR"			{return OR;}

"("		{return LEFT_PARENTHESIS;}
")"		{return RIGHT_PARENTHESIS;}
","		{return COMMA;}

"int"		{yylval.val=1; return INT_TYPE;}
"varchar"	{yylval.val=2; return VARCHAR_TYPE;}
"date"		{yylval.val=3; return DATE_TYPE;}

{letter}({letter}|[0-9])*	{sscanf(yytext, "%s", yylval.name); return VARIABLE;}

{letter}({letter}|[0-9])*"."{letter}({letter}|[0-9])*	{sscanf(yytext, "%s", yylval.name); return ATTRIBUTE;}

\".*\"		{strncpy(yylval.name,yytext+1,strlen(yytext)-2); return CHAR;}
[0-9]+		{sscanf(yytext, "%d", &yylval.val); return NUMBER;}

[0-9]{4}"-"[0-1][0-9]"-"[0-3][0-9]	{sscanf(yytext, "%s", yylval.name); return DATE;}

"="		{yylval.val=1; return BEqual;}
"<>"	{yylval.val=2; return BUNEqual;}
"<"		{yylval.val=3; return BSmaller;}
"<="	{yylval.val=4; return BSmallerEqual;}
">"		{yylval.val=5; return BBigger;}
">="	{yylval.val=6; return BBiggerEqual;}
"LIKE"	{yylval.val=7; return BLike;}

[ |\t]+ ;
\n ;

.	{return yytext[0]; }
%%