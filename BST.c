#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct Tree* tree_ptr;
typedef struct Tree {
	int value;
	char* key;
	tree_ptr leftChild;
	tree_ptr rightChild;
}tree;


void InorderBST(tree_ptr node) {
	if (node) {
		InorderBST(node->leftChild);
		printf("(%d,%c)\n", node->value, node->key);
		InorderBST(node->rightChild);
	}
	return;
}

void InsertBST(tree_ptr *root, int value, char key)
{
	tree_ptr ptr= (tree_ptr)malloc(sizeof(tree));
	tree_ptr node = *root;
	ptr->value = value;
	ptr->key = key;
	ptr->leftChild = ptr->rightChild = NULL;
	if (*root == NULL) {
		*root = ptr;
	}
	else {
		while (node!= NULL) {
			//printf("node!=NULL\n");
			if (node->value < value) {
				if (node->rightChild == NULL) {
					node->rightChild = ptr; 
					break;
				}
				else node = node->rightChild;
			}
			else {
				if (node->leftChild == NULL) {
					node->leftChild = ptr;
					break;
				}
				else node = node->leftChild;
			}
		}
	}
	return;
}
tree_ptr SearchBST(tree_ptr root, int value) {

	if (!root) return NULL;
	if (value == root->value) printf("%c\n", root->key);
	if (value < root->value) return SearchBST(root->leftChild, value);
	return SearchBST(root->rightChild, value);
}

int main () {
	char type, key;
	char newline;
	int value;
	int rflag = 0;
	tree_ptr root = NULL;

	FILE* fp = fopen("BST.txt", "r");
	while (fscanf(fp,"%c",&type) != -1) {
		//printf("t = %c\n", type);
		if (type == 'I') {
			fscanf(fp, "%d%c\n", &value, &key);
			InsertBST(&root,value,key);
			//printf("root val = %d\n", root->value);
		}
		else if (type == 'T') {
			//break;
			fscanf(fp, "%c", &newline);
			InorderBST(root);
			
		}
		else if (type == 'S') {
			fscanf(fp,"%d\n", &value);
			//printf("val = %d\n", value);
			SearchBST(root, value);
		}
	}
	
	fclose(fp);
	return 0;
}