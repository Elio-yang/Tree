/*
    we build a tree like this 
	    +
	   / \
 	  +   *
	 / \  | \
	a   * d  e
	   / \
	  b   c
	@pre_order traversal: ++a*bc*de        (root--->left--->right)
	@in_order traversal: (a+(b*c))+(d*e)   (left--->root--->right)
	@post_order traversal: abc*+de*+       (left--->right--->root)

	programming to make a post_order expression to an expression tree 
	and give the in_order//post_order traversal.
*/

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
/*
**Tree part
*/
typedef struct ExpTree Tree;
typedef struct ExpTree* Ptree;
typedef char   Eletype;

/*
**Stack part
*/
typedef struct stackNode stack;
typedef stack* Pstack;

struct ExpTree
{
	Eletype ele_data;
	Ptree left;
	Ptree right;
};

struct stackNode
{
	Ptree data;
	Pstack next;
};


/*
**@methods 
**create tree and give traversal
*/
Ptree CreateTree(void);
void  inOrderTraversal(const Ptree T); 
void  postOrderTraversal(const Ptree T);

/*
**@methods
**create stack and operations
*/
Pstack CreateStack(void);
void push(Pstack P, Ptree T);
Ptree pop(Pstack P);

using namespace std;

int main(void) {
	Ptree ET;
	ET = CreateTree();
	cout << "in_order traversal: ";
	inOrderTraversal(ET);
	cout << endl;
	cout << "post_order traversal: ";
	postOrderTraversal(ET);
	cout << endl;
	system("pause");
	return 0;
}


Ptree CreateTree(void) {
	char data;
	Ptree T;
	Pstack P = CreateStack();//return a null stack P, P->next=null

	cout << "Enter post_order expression:(Enter and Ctrl+Z to end )";
	while (cin>>data){
		if ('a'<=data&&'z'>=data){
			T = (Ptree)malloc(sizeof(Tree));
			T->ele_data = data;
			T->left = NULL;
			T->right = NULL;
			push(P, T);//enter the stack
		} 
		else
		{
			T = (Ptree)malloc(sizeof(Tree));
			T->ele_data = data;
			T->left = pop(P);
			T->right = pop(P);
			push(P, T);
		}
	}
	return pop(P);//the final expression tree

}
/*
expression:  a b + 
    @ if ('a'<=data&&'z'>=data)
    -------------
    |   |   |   |(head)      ------>this is a stack
	--|---|------
	  |	  |
	  a   b                  ------>this is a tree

	@else         //operations
    -------------
    |   |   |   |            ------>this is a stack
    --|----------
      |	 
	  +
	 / \
	/   \
   a     b                   ------>pop two elements and  construct a new tree
     
*/
void  inOrderTraversal(const Ptree T) {
	if (T){
		if (T->left){
			cout << '(';
		}
		inOrderTraversal(T->left);
		cout << T->ele_data;
		inOrderTraversal(T->right);
		if (T->right){
			cout << ')';
		}
	}
}
void  postOrderTraversal(const Ptree T) {
	if (T) {
		postOrderTraversal(T->left);
		postOrderTraversal(T->right);
		cout << T->ele_data;
	}
}


Pstack CreateStack(void) {
	Pstack P = (Pstack)malloc(sizeof(stack));
	if (P) {
		P->next = NULL;
		return P;
	}
	else {
		exit(-1);
	}
}
void push(Pstack P, Ptree T) {
	Pstack temp = (Pstack)malloc(sizeof(stack));
	temp->data = T;
	temp->next = P->next;
	P->next = temp;
}
Ptree pop(Pstack P) {
	Pstack temp;
	Ptree T = (Ptree)malloc(sizeof(Tree));
	temp = P->next;
	P->next = P->next->next;

	T->ele_data = temp->data->ele_data;
	T->left = temp->data->left;
	T->right = temp->data->right;
	free(temp);
	
	return T;//top can achieve this ,too.
}
