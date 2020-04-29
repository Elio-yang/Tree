/*
	We build a tree like this
		6
	   / \
	  2   7
	 / \   \
	1   4   8
	   / \
	  3   5

	For each node, the val of left_child is smaller than the right. This
	kind of tree are called search_tree.

	programming to make a some basic ADT of search_tree.(No same val)

	Methods:
	@MakeEmpty()
	@Find()
	@FindMin/Max()
	@Delete/Insert()
	@Retrieve()
	@Traverse()
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
/**
 * Tree part
 */
struct TreeNode;
typedef struct TreeNode* Position;//aimed for nodes
typedef struct TreeNode* Tree;//aimed for tree
typedef int type;//data type
/**
 * Stack part
 */
struct StackNode;
typedef struct StackNode* stack;
/**
 * @ Stack Method
 */
stack CreateStack();
void push(stack P, Tree tree_Node);
void pop(stack P);
Tree top(stack P);
stack MakeEmpty(stack P);
bool isEmpty(stack P);
/**
 * @Make a tree an empty one
 */
Tree MakeEmpty(Tree tree);
/**
 * @Create a tree
 * @Insert an element into a tree
 * Method 1 using recursion
 * Method 2 using while-loop
 */
Tree Insert_1(type val, Tree tree);//create the tree at the first time
Tree Insert_2(type val, Tree tree);

Tree Delete(type val, Tree tree);

/**
 * @Find a node with data:val and return this node.
 * Method 1 using recursion
 * Method 2 using while-loop
 */
Position Find_prev(const type val, const Tree tree);
Position Find(const type val, const Tree tree);
/**
 * @Find the min/max data in a tree and return it's position
 * Method 1 using recursion
 * Method 2 using while-loop
 */
Position FindMin_1(const Tree tree);
Position FindMin_2(const Tree tree);
Position FindMax_1(const Tree tree);
Position FindMax_2(const Tree tree);

/**
 * @Traverse a tree
 * Method 1 using recursion
 * Method 2 using stack
 */
void pre_Traverse_1(const Tree tree);
void in_Traverse_1(const Tree tree);
void post_Traverse_1(const Tree tree);
void pre_Traverse_2(const Tree tree, stack P);
void in_Traverse_2(const Tree tree, stack P);
//void post_Traverse_2(const Tree tree);
/**
 * @Get hight of a tree
 * Method 1 using recursion
 * Method 2 using stack
 */
 //int getHight_1(const Tree tree);
 //int getHight_2(const Tree tree);
 /**
  * @Delete a tree
  */
  //void Release(Tree tree);

struct TreeNode
{
	type val;
	Tree left;
	Tree right;
};
struct StackNode
{
	Tree tree_node;
	stack next;
};
int main() {
	Tree ST = NULL;//search_tree
	//ST = MakeEmpty(ST);//return NULL
	ST = Insert_1(6, ST);
	ST = Insert_1(5, ST);
	ST = Insert_1(3, ST);
	ST = Insert_1(4, ST);
	ST = Insert_1(7, ST);
	ST = Insert_1(9, ST);
	/*
			 6
			/ \
		   5   7
		  /     \
		 3		 9
		  \
		   4
	*/
	//using recursion
	puts("pre_Traversal_1:");
	pre_Traverse_1(ST);
	printf("\n");
	puts("in_Traversal_1:");
	in_Traverse_1(ST);
	printf("\n");
	puts("post_Traversal_1:");
	post_Traverse_1(ST);
	printf("\n");
	//stack and while-loop
	puts("pre_traversal_2:");
	stack P = CreateStack();//empty stack
	pre_Traverse_2(ST, P);
	printf("\n");
	puts("in_Traversal_2:");
	P = MakeEmpty(P);
	in_Traverse_2(ST, P);
	printf("\n");

	Tree findnode = Find_prev(4, ST);
	printf("previous val of %d :%d\n", 4, findnode->val);
	Delete(4, ST);
	puts("pre_Traversal_1(after delete):");
	pre_Traverse_1(ST);
	printf("\n");
	//find min/max data
	Position min_local_1 = FindMin_1(ST);
	Position min_local_2 = FindMin_2(ST);
	Position max_local_1 = FindMax_1(ST);
	Position max_local_2 = FindMax_2(ST);
	printf("min_local_1=%-2d\n", min_local_1->val);
	printf("min_local_2=%-2d\n", min_local_2->val);
	printf("max_local_1=%-2d\n", max_local_1->val);
	printf("max_local_2=%-2d\n", max_local_2->val);

	return 0;
}
stack CreateStack() {//P is head of stack
	stack P = (stack)malloc(sizeof(StackNode));
	if (P) {
		P->next = NULL;
	}
	else
	{
		exit(-1);
		//heap overflow
	}
}
void push(stack P, Tree tree_Node) {
	stack temp = (stack)malloc(sizeof(StackNode));
	//error when heap overflow
	temp->tree_node = tree_Node;
	temp->next = P->next;//temp is a new node should after P
	P->next = temp;
}
void pop(stack P) {
	stack temp = (stack)malloc(sizeof(StackNode));
	//error when heap overflow
	temp = P->next;
	P->next = P->next->next;
	free(temp);
}
Tree top(stack P) {
	return P->next->tree_node;
}
stack MakeEmpty(stack P) {
	if (P == NULL) {
		exit(-1);
		//empty
	}
	else
	{
		while (!isEmpty(P)) {
			pop(P);
		}
	}
}
bool isEmpty(stack P) {
	return P->next == NULL;
}
Tree MakeEmpty(Tree tree) {
	if (tree != NULL) {
		MakeEmpty(tree->left);//later tree->left will be treated as tree to be freed.
		MakeEmpty(tree->right);
		free(tree);
	}
	return NULL;
}
Tree Insert_1(type val, Tree tree) {
	if (tree == NULL) {//for an empty tree create a Node
		tree = (Tree)malloc(sizeof(struct TreeNode));
		if (tree == NULL) {
			//heap overflow
			exit(-1);
		}
		else
		{
			tree->val = val;
			tree->left = tree->right = NULL;
		}
	}
	else if (val < tree->val) {//goto the left
		tree->left = Insert_1(val, tree->left);
	}
	else if (val > tree->val) {
		tree->right = Insert_1(val, tree->right);
	}
	return tree;
}
Tree Insert_2(type val, Tree tree) {
	Tree node = (Tree)malloc(sizeof(struct TreeNode));
	if (node == NULL) {
		//heap overflow
		exit(-1);
	}
	node->val = val;
	node->left = node->right = NULL;//preparing, new data has been in the node

	if (tree == NULL) {//empty tree
		tree = (Tree)malloc(sizeof(struct TreeNode));
		if (tree == NULL) {
			//heap overflow
			exit(-1);
		}
		tree = node;
	}
	else //not empty
	{
		while (tree != NULL) {
			if (val < tree->val) {
				if (tree->left == NULL) {
					tree->left = node;
					return tree;
				}
				else
				{
					tree = tree->left;
				}
			}
			else if (val > tree->val) {
				if (tree->right == NULL) {
					tree->right = node;
					return tree;
				}
				else
				{
					tree = tree->right;
				}
			}
		}
	}
}
Tree Delete(type val, Tree tree) {
	if (tree == NULL) {
		exit(-1);
	}
	Tree curr_node;
	curr_node = Find(val, tree);//current node
	Tree prev_node = Find_prev(val, tree);
	if (curr_node->left == NULL && curr_node->right == NULL) {//is a leaf_node
		Tree temp = curr_node;
		(curr_node->val < prev_node->val) ? (prev_node->left = NULL) : (prev_node->right = NULL);
		free(temp);
	}
	else if (curr_node->left == NULL ^ curr_node->right == NULL) {//only with a left/right child
		if (prev_node->left == curr_node) {
			prev_node->left = curr_node->left;
			curr_node->left = NULL;
		}
		else if (prev_node->right == curr_node) {
			prev_node->right = curr_node->left;
			curr_node->left = NULL;
		}
		free(curr_node);
	}
	else if (curr_node->left&&curr_node->right) {//with two child
		Tree min_node = FindMin_1(curr_node->right);
		Tree min_prev = Find_prev(min_node->val, curr_node->right);
		if (min_node->right == NULL) {
			curr_node->val = min_node->val;
			min_prev->left == NULL;
		}
		else
		{
			curr_node->val = min_node->val;
			min_prev->left = min_node->right;
			min_node->right = NULL;
		}
		free(min_node);
	}

	return tree;
}
Position Find_prev(const type val, const Tree tree) {
	if (tree == NULL) {
		return NULL;
	}
	if ((tree->left != NULL && tree->left->val == val) || (tree->right != NULL && tree->right->val == val)) {
		return tree;
	}
	if (tree->val < val) {
		return Find_prev(val, tree->right);
	}
	else if (tree->val > val) {
		return Find_prev(val, tree->left);
	}
}
Position Find(const type val, const Tree tree) {
	if (tree == NULL) {
		return NULL;
	}

	if (val < tree->val) {
		return Find(val, tree->left);
	}
	else if (val > tree->val) {
		return Find(val, tree->right);
	}
	else
	{
		return  tree;//Treenode* node for here
	}
}
Position FindMin_1(const Tree tree) {
	if (tree == NULL) {
		return NULL;
	}
	if (tree->left == NULL) {
		return tree;
	}
	else
	{
		return FindMin_1(tree->left);
	}
}
Position FindMin_2(const Tree tree) {
	if (tree == NULL) {
		return NULL;
	}
	Tree temp = (Tree)malloc(sizeof(TreeNode));
	temp = tree;
	while (temp->left != NULL) {
		temp = temp->left;
	}
	return temp;
}
Position FindMax_1(const Tree tree) {
	if (tree == NULL) {
		return NULL;
	}
	if (tree->right == NULL) {
		return tree;
	}
	else
	{
		return FindMax_1(tree->right);
	}
}
Position FindMax_2(const Tree tree) {
	if (tree == NULL) {
		return NULL;
	}
	Tree temp = (Tree)malloc(sizeof(TreeNode));
	temp = tree;
	while (temp->right != NULL) {
		temp = temp->right;
	}
	return temp;
}
void pre_Traverse_1(const Tree tree) {
	if (tree != NULL) {
		printf("%-2d", tree->val);
		pre_Traverse_1(tree->left);
		pre_Traverse_1(tree->right);
	}
}
void in_Traverse_1(const Tree tree) {
	if (tree != NULL) {
		in_Traverse_1(tree->left);
		printf("%-2d", tree->val);
		in_Traverse_1(tree->right);
	}
}
void post_Traverse_1(const Tree tree) {
	if (tree != NULL) {
		post_Traverse_1(tree->left);
		post_Traverse_1(tree->right);
		printf("%-2d", tree->val);
	}
}
/*
		6
	   / \
	  2   7
	 / \   \
	1   4   8
	   / \
	  3   5
*/
void pre_Traverse_2(const Tree tree, stack P) {
	Tree temp = (Tree)malloc(sizeof(TreeNode));
	temp = tree;
	if (temp == NULL) {
		return;
	}
	while (!isEmpty(P) || temp)
	{
		if (temp) {
			printf("%-2d", temp->val);
			push(P, temp);
			temp = temp->left;
		}
		else
		{
			temp = top(P);
			pop(P);
			temp = temp->right;
		}
	}
}
void in_Traverse_2(Tree tree, stack P) {
	Tree temp = (Tree)malloc(sizeof(TreeNode));
	temp = tree;
	while (!isEmpty(P) || temp)
	{
		if (temp) {
			push(P, temp);
			temp = temp->left;
		}
		else
		{
			temp = top(P);
			pop(P);
			printf("%-2d", temp->val);
			temp = temp->right;
		}
	}
}

//void post_Traverse_2(const Tree tree) {
//
//}
//int getHight_1(const Tree tree) {
//
//}
//int getHight_2(const Tree tree) {
//
//}
//void Release(Tree tree) {
//
//}