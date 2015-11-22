lex lexical-analysis.l 
yacc -d syntactic-analysis.y 
g++ -o analysis y.tab.c 
./analysis
