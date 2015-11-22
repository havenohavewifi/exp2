%{
#include <stdlib.h>
#include <stdio.h>
#include <malloc.h> 
#include <memory.h>
#include <string.h>
#include "lex.yy.c"
%}

%start	program		
%token  CREATE_TABLE DROP_TABLE INSERT VALUES DELETE SELECT FROM WHERE ORDER_BY ATTRIBUTE
%token  BEqual BUNEqual BSmaller BSmallerEqual BBigger BBiggerEqual BLike
%token	LEFT_PARENTHESIS RIGHT_PARENTHESIS COMMA
%token  AND OR
%token	INT_TYPE VARCHAR_TYPE DATE_TYPE
%token	VARIABLE
%token	NUMBER
%token	CHAR
%token	DATE

%%

program
	: command program
	| command
	;

command
	: create | drop | insert | delete | select;

create
	: CREATE_TABLE VARIABLE {printf("create table %s\n", $2.name);} LEFT_PARENTHESIS attribute_type_list RIGHT_PARENTHESIS;

attribute_type_list
	: attribute_type_list COMMA attribute_type
	| attribute_type
	;

attribute_type
	: VARIABLE INT_TYPE {printf("add attribute name %s type %d\n", $1.name, $2.val);}
	| VARIABLE VARCHAR_TYPE {printf("add attribute name %s type %d\n", $1.name, $2.val);}
	| VARIABLE DATE_TYPE {printf("add attribute name %s type %d\n", $1.name, $2.val);}
	|
	;

drop
	: DROP_TABLE VARIABLE {printf("drop table %s\n", $2.name);}
	;

insert
	: INSERT VARIABLE {printf("insert table %s ", $2.name);} VALUES LEFT_PARENTHESIS record RIGHT_PARENTHESIS 
	;

record
	: record COMMA item
	| item
	;

item: NUMBER {printf("item %d ", $1.val);} | CHAR {printf("item %s ", $1.name);} | DATE {printf("item %s ", $1.name);} ;

delete
	: DELETE VARIABLE WHERE where_list {printf("delete from table %s ", $2.name);};

where_list
	: where_list AND condition
	| where_list OR condition
	| condition
	;

compare_opt
	: BEqual | BUNEqual | BSmaller | BSmallerEqual | BBigger | BBiggerEqual | BLike;

condition
	: attribute compare_opt item {printf("condition: %s %d ", $1.name, $2.val);}
	| attribute compare_opt attribute {printf("condition: %s %d ", $1.name, $2.val);}
	;

select
	: SELECT attribute_list FROM variable_list WHERE where_list
	| SELECT attribute_list FROM variable_list WHERE where_list ORDER_BY variable_list
	;

attribute_list
	: attribute_list COMMA attribute
	| attribute
	;

attribute
	: VARIABLE {printf("attribute: %s\n", $1.name);}
	| ATTRIBUTE {printf("attribute: %s\n", $1.name);}
	;

variable_list
	: variable_list COMMA VARIABLE {printf("variable: %s\n", $3.name);}
	| VARIABLE {printf("variable: %s\n", $1.name);}
	;

%%

int main() {
    return yyparse();
}

void yyerror(char *s) {
    printf("parse error!\n");
}

int yywrap() {
	return 1;
}
