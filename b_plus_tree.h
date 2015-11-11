#include<stdio.h>

#define MAX 5
#define MIN 3

#define NODE 0
#define LEAF 1

#define LEFT 0
#define RIGHT 1

typedef struct
{
	int key;
	int pos;
}Element;

typedef struct
{
	int type;
	int count;
	Element pair[MAX];
	int parent;
}Node;


void displayElement(Element element);
void displayNode(FILE *index,Node &node);
void display(FILE *index);
void getRoot(FILE *index, Node &node);
int search(FILE *index, int key);
void searchNode(FILE *index, Node &node, int key);
int searchElement(Node &node, int key);
int insert(FILE *index, Element element);
int insertElement(FILE *index, Node &node, Element element);
void splitNode(FILE *index, Node &nodea, Element element, int pos);
void enlargeKey(FILE *index, Node &node);
int del(FILE *index, int key);
int delElement(FILE *index, Node &node, int key);
void transElement(FILE *index, Node &left, Node &right, int dir, int pos);
void mergeNode(FILE *index, Node &left, Node &right);
void ensmallKey(FILE *index, Node &nod);
void changeParent(FILE *index, Node &node, int child, int parent);