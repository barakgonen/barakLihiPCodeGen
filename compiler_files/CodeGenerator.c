#include "CodeGenerator.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define NR_BUCKETS 1024

struct StructObject
{
	char *key;
	void *value;
	struct StructObject *next;
};

struct StructsMapper
{
	struct StructObject *buckets[NR_BUCKETS];
	void (*free_key)(char *);
	void (*free_value)(void *);
	unsigned int (*hash)(const char *key);
	int (*cmp)(const char *first, const char *second);
};

void *get(struct StructsMapper *table, const char *key)
{
	int i = 0;
	struct StructObject *node;
	node = table->buckets[0];
	while (node)
	{
		// printf("size of node->key is: %d\n", strlen(node->key));
		// printf("size of key is: %d\n", strlen(key));
		if (table->cmp(key, node->key) == 0)
			return node->value;
		// else
		// {
		// 	// printf("%s != %s\n", key ,node->key);
		// 	// while(i<strlen(key)&&i<strlen(node->key))
		// 	// {
		// 	// 	printf("^^^^^^^%c\n",key[i]);
		// 	// 	printf("$$$ %c\n",node->key[i]);
		// 	// 	i++;
		// 	// }
		// 	// if(i<strlen(key))
		// 	// {
		// 	// 	printf("^^^^^^^%c\n",key[i]);
		// 	// }
		// }

		node = node->next;
	}
	printf("Returning nulll :(\n");
	return NULL;
}

int insert(struct StructsMapper *table, char *key, void *value)
{
	struct StructObject **tmp;
	struct StructObject *node;

	node = malloc(sizeof *node);
	if (node == NULL)
		return -1;

	tmp = &table->buckets[0];
	while (*tmp)
	{
		if (table->cmp(key, (*tmp)->key) == 0)
			break;
		tmp = &(*tmp)->next;
	}
	if (*tmp)
	{
		if (table->free_key != NULL)
			table->free_key((*tmp)->key);
		if (table->free_value != NULL)
			table->free_value((*tmp)->value);
		node = *tmp;
	}
	else
	{
		while ((*tmp) != NULL)
			tmp = (*tmp)->next;
	}
	node->key = strdup(key);
	node->value = strdup(value);
	(*tmp) = node;

	return 0;
}

unsigned int foo_strhash(const char *str)
{
	unsigned int hash = 0;
	for (; *str; str++)
		hash = 31 * hash + *str;
	return hash;
}

const int CODE_INIT_FRAME_IN_BYTES = 4;
typedef struct variable *varPtr;
typedef struct variable
{
	int address;
	char str[100];
	tn_t type;
	varPtr prev;
	varPtr next;
} Variable;

// This struct holds a linked list of variables called vars, and a counter for current number of variables
typedef struct symbol_table
{
	Variable *vars;
	int variables_counter;
} Symbol_table;

Symbol_table *symbolTalble = NULL;
Variable *UKNOWN_VARIABLE = NULL;

varPtr add_variable_to_symbol_table(char *identifier, tn_t type, varPtr list)
{
	varPtr p, q;
	symbolTalble->variables_counter += 1;

	/* allocate memory for new record */
	if ((p = (varPtr)malloc(sizeof(Variable))) == NULL)
	{
		printf("Cannot allocate memory\n");
		exit(1);
	}
	p->address = CODE_INIT_FRAME_IN_BYTES + symbolTalble->variables_counter; /* store input in new record */
																			 // printf("add_variable_to_symbol_table5:\n");
	strcpy(p->str, identifier);
	p->type = type;

	// printf("Key is: %s\n", identifier);
	if (list == NULL)
	{ /* in the case if "p" is the first element in the list */
		p->next = 0;
		p->prev = 0;
		return p;
	}
	else
	{
		q = list;
		while (q->next != NULL)
		{ /* moving to the end of the list */
			q = q->next;
		}
		p->next = q->next;
		q->next = p;
		p->prev = q;
		return list;
	}
}

int get_variable_from_table(char *identifier)
{
	varPtr curNode;
	curNode = symbolTalble->vars;

	// Iterate till last element until key is not found
	while (curNode != NULL && strcmp(curNode->str, identifier) != 0)
		curNode = curNode->next;
	return (curNode != NULL) ? curNode->address : -1;
}

tn_t get_variable_type_from_symbol_table(char *identifier)
{
	// printf("id is: %s\n", identifier);
	varPtr curNode;
	curNode = symbolTalble->vars;

	// Iterate till last element until key is not found
	while (curNode != NULL && strcmp(curNode->str, identifier) != 0)
		curNode = curNode->next;
	return (curNode != NULL) ? curNode->type : -1;
}

void update_pointer_target(char *srcIdentifier, int targetAddress)
{
	varPtr curNode;
	curNode = symbolTalble->vars;

	// Iterate till last element until key is not found
	while (curNode != NULL && strcmp(curNode->str, srcIdentifier) != 0)
		curNode = curNode->next;
	if (curNode != NULL)
		curNode->address = targetAddress;
}

void remove_variable_from_symbol_table(const char *name)
{
	// printf("BARAK PREFOREM REMOVE FROM YOUR SYMBOL LIST for this var: \n", name);
}

/*
*	This recursive function is the main method for Code Generation
*	Input: treenode (AST)
*	Output: prints the Pcode on the console
*/
struct StructsMapper tbl = {{0}, NULL, NULL, foo_strhash, strcmp};
char struct_name[5000] = "";
char break_dest[50] = "";
const char SUPPERATOR = '!';
int last_loop_end_lable_line_num = -1;
int code_recur(treenode *root)
{
	if (symbolTalble == NULL)
		print_symbol_table(root);
	if_node *ifn;
	for_node *forn;
	leafnode *leaf;
	Variable target_var;
	Variable src_var;
	treenode *right_node;
	treenode *left_node;

	if (!root)
		return SUCCESS;

	switch (root->hdr.which)
	{
	case LEAF_T:
		leaf = (leafnode *)root;
		switch (leaf->hdr.type)
		{
			// case TN_LABEL:
			// 	/* Maybe you will use it later */
			// 	break;

		case TN_IDENT:
			if (strcmp(leaf->data.sval->str, "printf") != 0 && strcmp(leaf->data.sval->str, "main") != 0)
			{
				//lihi here
				// printf("HEERE!!!\n");
				// printf("Need to load variable identified as: %s%s\n", leaf->data.sval->str, " from memory");
				// src_var = get_variable_from_table(leaf->data.sval->str);
				// if you remove this comment you should check b = a<6;
				// printf("LDC %d\n", get_variable_from_table(leaf->data.sval->str));
			}
			/*
					*	In order to get the identifier name you have to use:
					*	leaf->data.sval->str
					*/
			break;

			// case TN_COMMENT:
			// 	/* Maybe you will use it later */
			// 	break;

			// case TN_ELLIPSIS:
			// 	/* Maybe you will use it later */
			// 	break;

		case TN_STRING:
			/* Maybe you will use it later */
			break;

		case TN_TYPE:
			/* Maybe you will use it later */
			break;

		case TN_INT:
			/* 
					*	In order to get the int value you have to use: 
					*	leaf->data.ival 
					*/
			printf("LDC %d\n", leaf->data.ival);
			break;

		case TN_REAL:
			/*
					*	In order to get the real value you have to use:
					*	leaf->data.dval
					*/
			printf("LDC %f\n", leaf->data.dval);
			break;
		default:
			printf("barak unhandled leaf bro, it's type is: %d\n", leaf->hdr.type);
		}
		break;

	case IF_T:
		ifn = (if_node *)root;
		switch (ifn->hdr.type)
		{
		case TN_IF:
			if (ifn->else_n == NULL)
			{
				/* if case */
				code_recur(ifn->cond);
				switch (ifn->cond->hdr.type)
				{
				case TN_IDENT:
					leaf = (leafnode *)ifn->cond;
					printf("LOD %d\n", get_variable_from_table(leaf->data.sval->str));
					break;
				default:
					// printf("BBBBB\n type is: %d\n", ifn->cond->hdr.which);
					break;
				}
				printf("FJP end_if_%d\n", root->hdr.line);
				code_recur(ifn->then_n);
				printf("end_if_%d%s\n", root->hdr.line, ":");
			}
			else
			{
				code_recur(ifn->cond);
				printf("FJP else_%d\n", root->hdr.line);
				code_recur(ifn->then_n);
				printf("ujp end_%d\n", root->hdr.line);
				printf("else_%d%s\n", root->hdr.line, ":");
				code_recur(ifn->else_n);
				printf("end_%d%s\n", root->hdr.line, ":");
			}
			return 0;

		case TN_COND_EXPR:
			code_recur(ifn->cond);
			printf("FJP else_condition_%d\n", root->hdr.line);
			code_recur(ifn->then_n);
			printf("ujp after_condition_%d\n", root->hdr.line);
			printf("else_condition_%d%s\n", root->hdr.line, ":");
			code_recur(ifn->else_n);
			printf("ujp after_condition_%d\n", root->hdr.line);
			printf("after_condition_%d%s\n", root->hdr.line, ":");
			break;

		default:
			/* Maybe you will use it later */
			code_recur(ifn->cond);
			code_recur(ifn->then_n);
			code_recur(ifn->else_n);
		}
		break;

	case FOR_T:
		forn = (for_node *)root;
		switch (forn->hdr.type)
		{

		case TN_FUNC_DEF:
			/* Function definition */
			/* e.g. int main(...) { ... } */
			/* Look at the output AST structure! */
			code_recur(forn->init);
			code_recur(forn->test);
			code_recur(forn->incr);
			code_recur(forn->stemnt);
			break;

		case TN_FOR:
			/* For case*/
			/* e.g. for(i=0;i<5;i++) { ... } */
			/* Look at the output AST structure! */
			last_loop_end_lable_line_num = root->hdr.line;
			strcpy(break_dest, "end_of_for_");
			code_recur(forn->init);
			printf("entering_for_%d%s\n", root->hdr.line, ":");
			code_recur(forn->test);
			printf("FJP end_of_for_%d\n", root->hdr.line);
			code_recur(forn->stemnt);
			code_recur(forn->incr);
			printf("ujp entering_for_%d\n", root->hdr.line);
			printf("end_of_for_%d%s\n", root->hdr.line, ":");
			break;
		default:
			/* Maybe you will use it later */
			code_recur(forn->init);
			code_recur(forn->test);
			code_recur(forn->stemnt);
			code_recur(forn->incr);
		}
		break;

	case NODE_T:
		switch (root->hdr.type)
		{
		case TN_PARBLOCK:
			/* Maybe you will use it later */
			code_recur(root->lnode);
			code_recur(root->rnode);
			break;

		case TN_PARBLOCK_EMPTY:
			/* Maybe you will use it later */
			code_recur(root->lnode);
			code_recur(root->rnode);
			break;

		case TN_TRANS_LIST:
			/* Maybe you will use it later */
			code_recur(root->lnode);
			code_recur(root->rnode);
			break;

		case TN_FUNC_DECL:
			/* Maybe you will use it later */
			code_recur(root->lnode);
			code_recur(root->rnode);
			break;

		case TN_FUNC_CALL:
			/* Function call */
			// printf("HI\n");
			if (strcmp(((leafnode *)root->lnode)->data.sval->str, "printf") == 0)
			{
				/* printf case */
				/* The expression that you need to print is located in */
				/* the currentNode->right->right sub tree */
				/* Look at the output AST structure! */
				// code_recur(root->lnode);
				code_recur(root->rnode);
				right_node = root->rnode;
				left_node = root->lnode;
				if (right_node != NULL)
				{
					if (right_node->hdr.type == TN_EXPR_LIST &&
						right_node->rnode != NULL &&
						right_node->rnode->hdr.type == TN_DEREF &&
						right_node->rnode->rnode != NULL)
					{
						// printf("need to print *a\n"); // need to print the address that the pointer points to
						leaf = (leafnode *)right_node->rnode->rnode;
						printf("LDC %d\n", get_variable_from_table(leaf->data.sval->str));
					}
					if (right_node->hdr.type == TN_EXPR_LIST && 
						right_node->rnode != NULL && 
						right_node->rnode->hdr.type == TN_SELECT){
							// printf("NANANAN\n");
							// printf("struct name is: %s\n", struct_name);
							printf("LOD %d\n", get_variable_from_table(struct_name));
							strcpy(struct_name, "");
						}
					// 	if (ru
					// 		root->rnode->hdr.type == TN_EXPR &&
					// 		root->rnode->rnode != NULL &&
					// 		root->rnode->rnode->hdr.type == TN_IDENT)
					// {
					// 	switch (root->rnode->rnode->hdr.which)
					// 	{
					// 	case TN_BLOCK:
					// 		leaf = (leafnode *)root->rnode->rnode->rnode;
					// 		printf("LDC %d\n", get_variable_from_table(leaf->data.sval->str));
					// 		break;
					// 	default:
					// 		printf("Unhandled which: %d\n", root->rnode->rnode->hdr.which);
					// 		break;
					// 	}
					// }

					else if (right_node->rnode != NULL &&
							 right_node->rnode->hdr.type == TN_IDENT)
					{
						leaf = (leafnode *)root->rnode->rnode;
						printf("LOD %d\n", get_variable_from_table(leaf->data.sval->str));
					}
				}

				printf("PRINT\n");
			}
			else
			{
				/* other function calls - for HW3 */
				code_recur(root->lnode);
				code_recur(root->rnode);
			}
			break;

		case TN_BLOCK:
			/* Maybe you will use it later */
			code_recur(root->lnode);
			code_recur(root->rnode);
			break;

		case TN_ARRAY_DECL:
			/* array declaration - for HW2 */
			code_recur(root->lnode);
			code_recur(root->rnode);
			break;

		case TN_EXPR_LIST:
			/* Maybe you will use it later */
			code_recur(root->lnode);
			// printf("before\n");
			code_recur(root->rnode);
			break;

		case TN_NAME_LIST:
			/* Maybe you will use it later */
			code_recur(root->lnode);
			code_recur(root->rnode);
			break;

		case TN_ENUM_LIST:
			/* Maybe you will use it later */
			code_recur(root->lnode);
			code_recur(root->rnode);
			break;

		case TN_FIELD_LIST:
			/* Maybe you will use it later */
			code_recur(root->lnode);
			code_recur(root->rnode);
			break;

		case TN_PARAM_LIST:
			/* Maybe you will use it later */
			code_recur(root->lnode);
			code_recur(root->rnode);
			break;

		case TN_IDENT_LIST:
			/* Maybe you will use it later */
			code_recur(root->lnode);
			code_recur(root->rnode);
			break;

		case TN_TYPE_LIST:
			/* Maybe you will use it later */
			code_recur(root->lnode);
			code_recur(root->rnode);
			break;

		case TN_COMP_DECL:
			/* struct component declaration - for HW2 */
			code_recur(root->lnode);
			code_recur(root->rnode);
			break;

		case TN_DECL:
			// printf("HERE\n");
			code_recur(root->lnode);
			code_recur(root->rnode);
			break;

			break;
		case TN_DECL_LIST:
			/* Maybe you will use it later */
			code_recur(root->lnode);
			code_recur(root->rnode);
			break;

		case TN_DECLS:
			/* Maybe you will use it later */
			code_recur(root->lnode);
			code_recur(root->rnode);
			break;

		case TN_STEMNT_LIST:
			/* Maybe you will use it later */
			// printf("hello\n");
			code_recur(root->lnode);
			code_recur(root->rnode);
			break;

		case TN_STEMNT:
			/* Maybe you will use it later */
			code_recur(root->lnode);
			code_recur(root->rnode);
			break;

		case TN_BIT_FIELD:
			/* Maybe you will use it later */
			code_recur(root->lnode);
			code_recur(root->rnode);
			break;

		case TN_PNTR:
			/* pointer - for HW2! */
			code_recur(root->lnode);
			code_recur(root->rnode);
			break;

		case TN_TYPE_NME:
			/* Maybe you will use it later */
			code_recur(root->lnode);
			code_recur(root->rnode);
			break;

		case TN_INIT_LIST:
			/* Maybe you will use it later */
			code_recur(root->lnode);
			code_recur(root->rnode);
			break;

		case TN_INIT_BLK:
			/* Maybe you will use it later */
			code_recur(root->lnode);
			code_recur(root->rnode);
			break;

		case TN_OBJ_DEF:
			/* Maybe you will use it later */
			code_recur(root->lnode);
			code_recur(root->rnode);
			break;

		case TN_OBJ_REF:
			/* Maybe you will use it later */
			code_recur(root->lnode);
			code_recur(root->rnode);
			break;

		case TN_CAST:
			/* Maybe you will use it later */
			code_recur(root->lnode);
			code_recur(root->rnode);
			break;

		case TN_JUMP:
			if (root->hdr.tok == RETURN)
			{
				/* return jump - for HW2! */
				code_recur(root->lnode);
				code_recur(root->rnode);
			}
			else if (root->hdr.tok == BREAK)
			{
				/* break jump - for HW2! */
				printf("UJP %s%d\n", break_dest, last_loop_end_lable_line_num);
				code_recur(root->lnode);
				code_recur(root->rnode);
			}
			else if (root->hdr.tok == GOTO)
			{
				/* GOTO jump - for HW2! */
				code_recur(root->lnode);
				code_recur(root->rnode);
			}
			break;

		case TN_SWITCH:
			/* Switch case - for HW2! */
			code_recur(root->lnode);
			if (root->lnode != NULL)
			{
				if (root->lnode->hdr.type == TN_IDENT)
				{
					leaf = ((leafnode *)root->lnode);
					printf("LOD %d\n", get_variable_from_table(leaf->data.sval->str));
				}
				else
				{
					code_recur(root->lnode);
				}
			}
			last_loop_end_lable_line_num = root->hdr.line;
			strcpy(break_dest, "end_switch_");
			code_recur(root->rnode);
			printf("end_switch_%d%s\n", root->hdr.line, ":");
			break;

		case TN_INDEX:
			/* call for array - for HW2! */
			code_recur(root->lnode);
			code_recur(root->rnode);
			break;

		case TN_DEREF:
			/* pointer derefrence - for HW2! */
			if (root->lnode != NULL)
			{
				code_recur(root->lnode);
			}
			if (root->rnode != NULL)
			{
				code_recur(root->rnode);
				leaf = ((leafnode *)root->rnode);
				printf("LOD %d\n", get_variable_from_table(leaf->data.sval->str));
			}
			// if (root->lnode == NULL &&
			// 	root->rnode != NULL &&
			// 	root->rnode->hdr.which == LEAF_T)
			// {
			// 	printf("QQQQQQQQQQQQQQQQQQQLDC %d\n", get_variable_from_table(((leafnode *)root->rnode)->data.sval->str));
			// 	printf("QQQQQQQQQQQQQQQQQQQIND\n");
			// }

			break;

		case TN_SELECT:
			/* struct case - for HW2! */
			if (root->hdr.tok == ARROW)
			{
				/* Struct select case "->" */
				/* e.g. struct_variable->x; */
				code_recur(root->lnode);
				code_recur(root->rnode);
			}
			else
			{
				/* Struct select case "." */
				/* e.g. struct_variable.x; */
				if (root->rnode->hdr.which == LEAF_T && root->lnode->hdr.which == LEAF_T)
				{
					strncat(struct_name, ((leafnode *)root->lnode)->data.sval->str, strlen(((leafnode *)root->lnode)->data.sval->str));
					strncat(struct_name, &SUPPERATOR, 1);
				}
				code_recur(root->lnode);
				code_recur(root->rnode);
				if (((leafnode *)root->rnode) != NULL && ((leafnode *)root->rnode)->hdr.type == TN_IDENT)
				{
					strncat(struct_name, ((leafnode*)root->rnode)->data.sval->str, strlen(((leafnode*)root->rnode)->data.sval->str));
					strncat(struct_name, &SUPPERATOR, 1);
				}
			}
		break;
		case TN_ASSIGN:
			if (root->lnode != NULL && root->lnode->hdr.type == TN_IDENT)
			{
				//lihi aki
				if (get_variable_from_table(((leafnode *)root->lnode)->data.sval->str) != UKNOWN_VARIABLE->address)
					printf("LDC %d\n", get_variable_from_table(((leafnode *)root->lnode)->data.sval->str));
			}
			switch (root->hdr.tok)
			{
			case EQ:
				/* Regular assignment "=" */
				/* e.g. x = 5; */
				if (root->lnode != NULL &&
					root->rnode != NULL &&
					root->lnode->hdr.type == TN_IDENT &&
					root->rnode->hdr.type == TN_EXPR &&
					root->rnode->lnode != NULL && root->rnode->rnode == NULL &&
					(root->rnode->hdr.tok == INCR || root->rnode->hdr.tok == DECR) &&
					root->rnode->lnode->hdr.type != TN_DEREF &&
					strcmp(((leafnode *)root->rnode->lnode)->data.sval->str, ((leafnode *)root->lnode)->data.sval->str) == 0)
				{
					// because of c++ and c diffrences: x=x++ increments x in c++ and does nothing in c
				}
				else if (root->lnode != NULL &&
						 root->rnode != NULL &&
						 root->lnode->hdr.type == TN_IDENT &&
						 root->rnode->hdr.type == TN_EXPR &&
						 root->rnode->lnode == NULL &&
						 root->rnode->rnode != NULL &&
						 root->rnode->rnode->hdr.type == TN_IDENT)
				{
					printf("LOD %d\n", get_variable_from_table(((leafnode *)root->rnode->rnode)->data.sval->str));
					// printf("LDC %d\n", get_variable_from_table(((leafnode *)root->rnode->rnode)->data.sval->str));
					// printf("IND\n");

					// printf("lod %d\n", get_variable_from_table(((leafnode *)root->rnode->rnode)->data.sval->str));
					// printf("Updating %s\n", ((leafnode *)root->lnode)->data.sval->str);
					// printf("to point to this var's address: %s\n", ((leafnode *)root->rnode->rnode)->data.sval->str);
					// printf("which is: %d\n", get_variable_from_table(((leafnode *)root->rnode->rnode)->data.sval->str));
					// update_pointer_target(((leafnode *)root->lnode)->data.sval->str, get_variable_from_table(((leafnode *)root->rnode->rnode)->data.sval->str));
					// printf("The new address of pc is: %d\n", get_variable_from_table(((leafnode *)root->lnode)->data.sval->str));
				}
				else
				{
					code_recur(root->lnode);
					if (root->lnode != NULL && root->lnode->hdr.type == TN_SELECT){
						// printf("we would like to have the address of: %s\n", struct_name);
						printf("LDC %d\n", get_variable_from_table(struct_name));
						strcpy(struct_name, "");
					}
					// strncat(struct_name, leaf->data.sval->str, strlen(leaf->data.sval->str));
					code_recur(root->rnode);
					if (root->rnode != NULL && root->rnode->hdr.type == TN_IDENT)
					{
						// NO NEED TO GET THE IDENTIFIER HERE JUST NEED THE ADDRESS
						leaf = (leafnode *)root->rnode;
						printf("LDC %d\n", get_variable_from_table(leaf->data.sval->str));
					}
					if (root->lnode != NULL && root->lnode->hdr.type == TN_IDENT &&
						root->rnode->lnode != NULL && root->rnode->lnode->hdr.type == TN_IDENT &&
						root->rnode != NULL && root->rnode->hdr.type == TN_EXPR &&
						(root->rnode->hdr.tok == INCR || root->rnode->hdr.tok == DECR))
						printf("STO\n");
				}
				printf("STO\n");
				break;
			case PLUS_EQ:
				/* Plus equal assignment "+=" */
				/* e.g. x += 5; */
				code_recur(root->lnode);
				if (root->lnode != NULL && root->lnode->hdr.type == TN_IDENT)
				{
					leaf = (leafnode *)root->lnode;
					printf("LOD %d\n", get_variable_from_table(leaf->data.sval->str));
				}
				code_recur(root->rnode);
				if (root->rnode != NULL && root->rnode->hdr.type == TN_IDENT)
				{
					leaf = (leafnode *)root->rnode;
					printf("LOD %d\n", get_variable_from_table(leaf->data.sval->str));
				}
				printf("ADD\n");
				printf("STO\n");
				break;
			case MINUS_EQ:
				/* Minus equak assigment "-=" */
				/* e.g. x-= 5; */
				code_recur(root->lnode);
				if (root->lnode != NULL && root->lnode->hdr.type == TN_IDENT)
				{
					leaf = (leafnode *)root->lnode;
					printf("LOD %d\n", get_variable_from_table(leaf->data.sval->str));
				}
				code_recur(root->rnode);
				if (root->rnode != NULL && root->rnode->hdr.type == TN_IDENT)
				{
					leaf = (leafnode *)root->rnode;
					// printf("LDC %d\n", get_variable_from_table(leaf->data.sval->str));
					// printf("IND\n");
					printf("LOD %d\n", get_variable_from_table(leaf->data.sval->str));
				}
				printf("SUB\n");
				printf("STO\n");
				break;
			case STAR_EQ:
				/* Multiply equal assignment "*=" */
				/* e.g. x *= 5; */
				code_recur(root->lnode);
				if (root->lnode != NULL && root->lnode->hdr.type == TN_IDENT)
				{
					leaf = (leafnode *)root->lnode;
					printf("LOD %d\n", get_variable_from_table(leaf->data.sval->str));
				}
				code_recur(root->rnode);
				if (root->rnode != NULL && root->rnode->hdr.type == TN_IDENT)
				{
					leaf = (leafnode *)root->rnode;
					printf("LOD %d\n", get_variable_from_table(leaf->data.sval->str));
				}
				printf("MUL\n");
				printf("STO\n");
				break;
			case DIV_EQ:
				/* Divide equal assignment "/=" */
				/* e.g. x /= 5; */
				code_recur(root->lnode);
				if (root->lnode != NULL && root->lnode->hdr.type == TN_IDENT)
				{
					leaf = (leafnode *)root->lnode;
					printf("LOD %d\n", get_variable_from_table(leaf->data.sval->str));
				}
				code_recur(root->rnode);
				if (root->rnode != NULL && root->rnode->hdr.type == TN_IDENT)
				{
					leaf = (leafnode *)root->rnode;
					printf("LOD %d\n", get_variable_from_table(leaf->data.sval->str));
				}
				printf("DIV\n");
				printf("STO\n");
				break;
			default:
				printf("BUG, didn't handle assigment token: %d\n, ", root->hdr.tok);
				break;
			}
			break;
		case TN_EXPR:
			switch (root->hdr.tok)
			{
			case CASE:
				/* you should not get here */
				printf("DPL\n");
				code_recur(root->lnode);
				code_recur(root->rnode);
				printf("EQU \n");
				break;

			case INCR:
				/* Increment token "++" */
				if (root->lnode == NULL && root->rnode == NULL)
				{
					leaf = (leafnode *)root;
				}
				else if (root->lnode == NULL &&
						 root->rnode != NULL &&
						 root->rnode->hdr.type == TN_IDENT)
				{
					leaf = (leafnode *)root->rnode;
					printf("LDC %d\n", get_variable_from_table(leaf->data.sval->str));
					printf("LOD %d\n", get_variable_from_table(leaf->data.sval->str));
					printf("INC 1\n");
					printf("STO\n");
					printf("LOD %d\n", get_variable_from_table(leaf->data.sval->str));
				}
				else if (root->lnode != NULL &&
						 ((leafnode *)root->lnode)->hdr.type == TN_IDENT &&
						 root->rnode == NULL)
				{
					leaf = (leafnode *)root->lnode;
					printf("LOD %d\n", get_variable_from_table(leaf->data.sval->str));
					printf("LDC %d\n", get_variable_from_table(leaf->data.sval->str));
					printf("LOD %d\n", get_variable_from_table(leaf->data.sval->str));
					printf("INC 1\n");
					printf("STO\n");
				}
				// else if (root->lnode == NULL &&
				// 		 root->rnode != NULL &&
				// 		 root->rnode->hdr.type == TN_DEREF)
				// {
				// 	leaf = (leafnode *)root->rnode;
				// 	printf("LDC %d\n", get_variable_from_table(leaf->data.sval->str));
				// 	printf("LDC %d\n", get_variable_from_table(leaf->data.sval->str));
				// 	printf("IND\n");
				// 	printf("INC 1\n");
				// 	printf("STO\n");
				// 	printf("LDC %d\n", get_variable_from_table(leaf->data.sval->str));
				// 	printf("IND\n");
				// }
				// else if (root->lnode != NULL &&
				// 		 ((leafnode *)root->lnode)->hdr.type == TN_DEREF &&
				// 		 root->rnode == NULL)
				// {
				// 	leaf = (leafnode *)root->lnode->rnode;
				// 	printf("LDC %d\n", get_variable_from_table(leaf->data.sval->str));
				// 	// printf("IND\n");
				// 	// printf("LDC %d\n", get_variable_from_table(leaf->data.sval->str));
				// 	// printf("LDC %d\n", get_variable_from_table(leaf->data.sval->str));
				// 	// printf("IND\n");
				// 	printf("LOD %d\n", get_variable_from_table(leaf->data.sval->str));
				// 	printf("INC 1\n");
				// 	printf("STO\n");
				// }
				break;

			case DECR:
				/* Decrement token "--" */
				if (root->lnode == NULL && root->rnode == NULL)
				{
					leaf = (leafnode *)root;
				}
				else if (root->lnode == NULL &&
						 root->rnode != NULL &&
						 root->rnode->hdr.type == TN_IDENT)
				{
					leaf = (leafnode *)root->rnode;
					printf("LDC %d\n", get_variable_from_table(leaf->data.sval->str));
					printf("LOD %d\n", get_variable_from_table(leaf->data.sval->str));
					printf("DEC 1\n");
					printf("STO\n");
					printf("LOD %d\n", get_variable_from_table(leaf->data.sval->str));
				}
				else if (root->lnode != NULL &&
						 ((leafnode *)root->lnode)->hdr.type == TN_IDENT &&
						 root->rnode == NULL)
				{
					leaf = (leafnode *)root->lnode;
					printf("LOD %d\n", get_variable_from_table(leaf->data.sval->str));
					printf("LDC %d\n", get_variable_from_table(leaf->data.sval->str));
					printf("LOD %d\n", get_variable_from_table(leaf->data.sval->str));
					printf("DEC 1\n");
					printf("STO\n");
				}
				break;

			case PLUS:
				/* Plus token "+" */
				code_recur(root->lnode);
				if (root->lnode != NULL &&
					(root->lnode->hdr.tok == IDENT || root->lnode->hdr.type == TN_IDENT))
					printf("LOD %d\n", get_variable_from_table(((leafnode *)root->lnode)->data.sval->str));
				code_recur(root->rnode);
				if (root->rnode != NULL &&
					(root->rnode->hdr.tok == IDENT || root->rnode->hdr.type == TN_IDENT))
					printf("LOD %d\n", get_variable_from_table(((leafnode *)root->rnode)->data.sval->str));
				printf("ADD\n");
				break;
			case MINUS:
				/* Minus token "-" */
				/* e.g. x-y; */
				code_recur(root->lnode);
				if (root->lnode != NULL &&
					(root->lnode->hdr.tok == IDENT || root->lnode->hdr.type == TN_IDENT))
					printf("LOD %d\n", get_variable_from_table(((leafnode *)root->lnode)->data.sval->str));
				code_recur(root->rnode);
				if (root->rnode != NULL &&
					(root->rnode->hdr.tok == IDENT || root->rnode->hdr.type == TN_IDENT))
					printf("LOD %d\n", get_variable_from_table(((leafnode *)root->rnode)->data.sval->str));
				if (root->lnode == NULL)
					printf("NEG\n");
				else
					printf("SUB\n");
				break;

			case DIV:
				/* Divide token "/" */
				code_recur(root->lnode);
				if (root->lnode != NULL &&
					(root->lnode->hdr.tok == IDENT || root->lnode->hdr.type == TN_IDENT))
					printf("LOD %d\n", get_variable_from_table(((leafnode *)root->lnode)->data.sval->str));
				code_recur(root->rnode);
				if (root->rnode != NULL &&
					(root->rnode->hdr.tok == IDENT || root->rnode->hdr.type == TN_IDENT))
					printf("LOD %d\n", get_variable_from_table(((leafnode *)root->rnode)->data.sval->str));
				printf("DIV\n");
				break;

			case STAR:
				/* multiply token "*" */
				code_recur(root->lnode);
				if (root->lnode != NULL &&
					(root->lnode->hdr.tok == IDENT || root->lnode->hdr.type == TN_IDENT))
					printf("LOD %d\n", get_variable_from_table(((leafnode *)root->lnode)->data.sval->str));
				code_recur(root->rnode);
				if (root->rnode != NULL &&
					(root->rnode->hdr.tok == IDENT || root->rnode->hdr.type == TN_IDENT))
					printf("LOD %d\n", get_variable_from_table(((leafnode *)root->rnode)->data.sval->str));
				printf("MUL\n");
				break;
			case AND:
				/* And token "&&" */
				code_recur(root->lnode);
				if (root->lnode != NULL &&
					(root->lnode->hdr.tok == IDENT || root->lnode->hdr.type == TN_IDENT))
					printf("LOD %d\n", get_variable_from_table(((leafnode *)root->lnode)->data.sval->str));
				code_recur(root->rnode);
				if (root->rnode != NULL &&
					(root->rnode->hdr.tok == IDENT || root->rnode->hdr.type == TN_IDENT))
					printf("LOD %d\n", get_variable_from_table(((leafnode *)root->rnode)->data.sval->str));
				printf("AND\n");
				break;
			case OR:
				/* Or token "||" */
				code_recur(root->lnode);
				if (root->lnode != NULL &&
					(root->lnode->hdr.tok == IDENT || root->lnode->hdr.type == TN_IDENT))
					printf("LOD %d\n", get_variable_from_table(((leafnode *)root->lnode)->data.sval->str));
				code_recur(root->rnode);
				if (root->rnode != NULL &&
					(root->rnode->hdr.tok == IDENT || root->rnode->hdr.type == TN_IDENT))
					printf("LOD %d\n", get_variable_from_table(((leafnode *)root->rnode)->data.sval->str));
				printf("OR\n");
				break;

			case NOT:
				/* Not token "!" */
				code_recur(root->lnode);
				if (root->lnode != NULL &&
					(root->lnode->hdr.tok == IDENT || root->lnode->hdr.type == TN_IDENT))
					printf("LOD %d\n", get_variable_from_table(((leafnode *)root->lnode)->data.sval->str));
				code_recur(root->rnode);
				if (root->rnode != NULL &&
					(root->rnode->hdr.tok == IDENT || root->rnode->hdr.type == TN_IDENT))
					printf("LOD %d\n", get_variable_from_table(((leafnode *)root->rnode)->data.sval->str));
				printf("NOT\n");
				break;

			case GRTR:
				/* Greater token ">" */
				code_recur(root->lnode);
				if (root->lnode != NULL &&
					(root->lnode->hdr.tok == IDENT || root->lnode->hdr.type == TN_IDENT))
					printf("LOD %d\n", get_variable_from_table(((leafnode *)root->lnode)->data.sval->str));
				code_recur(root->rnode);
				if (root->rnode != NULL &&
					(root->rnode->hdr.tok == IDENT || root->rnode->hdr.type == TN_IDENT))
					printf("LOD %d\n", get_variable_from_table(((leafnode *)root->rnode)->data.sval->str));
				printf("GRT\n");
				break;

			case LESS:
				/* Less token "<" */
				code_recur(root->lnode);
				if (root->lnode != NULL &&
					(root->lnode->hdr.tok == IDENT || root->lnode->hdr.type == TN_IDENT))
					printf("LOD %d\n", get_variable_from_table(((leafnode *)root->lnode)->data.sval->str));
				code_recur(root->rnode);
				if (root->rnode != NULL &&
					(root->rnode->hdr.tok == IDENT || root->rnode->hdr.type == TN_IDENT))
					printf("LOD %d\n", get_variable_from_table(((leafnode *)root->rnode)->data.sval->str));
				printf("LES\n");
				break;

			case EQUAL:
				/* Equal token "==" */
				code_recur(root->lnode);
				if (root->lnode != NULL &&
					(root->lnode->hdr.tok == IDENT || root->lnode->hdr.type == TN_IDENT))
					printf("LOD %d\n", get_variable_from_table(((leafnode *)root->lnode)->data.sval->str));
				code_recur(root->rnode);
				if (root->rnode != NULL &&
					(root->rnode->hdr.tok == IDENT || root->rnode->hdr.type == TN_IDENT))
					printf("LOD %d\n", get_variable_from_table(((leafnode *)root->rnode)->data.sval->str));
				printf("EQU\n");
				break;

			case NOT_EQ:
				/* Not equal token "!=" */
				code_recur(root->lnode);
				if (root->lnode != NULL &&
					(root->lnode->hdr.tok == IDENT || root->lnode->hdr.type == TN_IDENT))
					printf("LOD %d\n", get_variable_from_table(((leafnode *)root->lnode)->data.sval->str));
				code_recur(root->rnode);
				if (root->rnode != NULL &&
					(root->rnode->hdr.tok == IDENT || root->rnode->hdr.type == TN_IDENT))
					printf("LOD %d\n", get_variable_from_table(((leafnode *)root->rnode)->data.sval->str));
				printf("NEQ\n");
				break;

			case LESS_EQ:
				/* Less or equal token "<=" */
				code_recur(root->lnode);
				if (root->lnode != NULL &&
					(root->lnode->hdr.tok == IDENT || root->lnode->hdr.type == TN_IDENT))
					printf("LOD %d\n", get_variable_from_table(((leafnode *)root->lnode)->data.sval->str));
				code_recur(root->rnode);
				if (root->rnode != NULL &&
					(root->rnode->hdr.tok == IDENT || root->rnode->hdr.type == TN_IDENT))
					printf("LOD %d\n", get_variable_from_table(((leafnode *)root->rnode)->data.sval->str));
				printf("LEQ\n");
				break;

			case GRTR_EQ:
				/* Greater or equal token ">=" */
				code_recur(root->lnode);
				if (root->lnode != NULL &&
					(root->lnode->hdr.tok == IDENT || root->lnode->hdr.type == TN_IDENT))
					printf("LOD %d\n", get_variable_from_table(((leafnode *)root->lnode)->data.sval->str));
				code_recur(root->rnode);
				if (root->rnode != NULL &&
					(root->rnode->hdr.tok == IDENT || root->rnode->hdr.type == TN_IDENT))
					printf("LOD %d\n", get_variable_from_table(((leafnode *)root->rnode)->data.sval->str));
				printf("GEQ\n");
				break;
			default:
				code_recur(root->lnode);
				code_recur(root->rnode);
				break;
			}
			break;

		case TN_WHILE:
			/* While case */
			last_loop_end_lable_line_num = root->hdr.line;
			strcpy(break_dest, "end_while_");
			printf("while_statement_%d%s\n", root->hdr.line, ":");
			code_recur(root->lnode);
			printf("FJP end_while_%d\n", root->hdr.line);
			code_recur(root->rnode);
			printf("UJP while_statement_%d\n", root->hdr.line);
			printf("end_while_%d%s\n", root->hdr.line, ":");
			break;

		case TN_DOWHILE:
			/* Do-While case */
			last_loop_end_lable_line_num = root->hdr.line;
			strcpy(break_dest, "end_do_while_");
			printf("do_while_statement_%d%s\n", root->hdr.line, ":");
			code_recur(root->rnode);
			code_recur(root->lnode);
			printf("FJP end_do_while_%d\n", root->hdr.line);
			printf("UJP do_while_statement_%d\n", root->hdr.line);
			printf("end_do_while_%d%s\n", root->hdr.line, ":");
			break;

		case TN_LABEL:
			code_recur(root->lnode);
			printf("FJP case_%d\n", root->hdr.line);
			code_recur(root->rnode);
			printf("case_%d%s\n", root->hdr.line, ":");
			break;

		default:
			code_recur(root->lnode);
			code_recur(root->rnode);
			break;
		}
		break;

	case NONE_T:
		printf("Error: Unknown node type!\n");
		exit(FAILURE);
	}

	return SUCCESS;
}
char struct_definition[5000] = "";
const char PAIR_SUP = '~';
const char STR_END = '\0';
int should_print_id = 1;

// 298~a!
int add_simple_struct_to_symbol_table(char* string, char* structIdentifier, char* middleName, int start_index){
	int i = start_index;
	tn_t vartype = 0;
	char typeC[1000] = "";
	char name[1000] = "";
	int type = 0;
	int was_found = 0;

	while(i < strlen(string) && was_found == 0){
		if (string[i] == PAIR_SUP)
		{
			// printf("typeC is %s\n", typeC);
			type = atoi(typeC);
			switch (type)
			{
			case 0:
				break;
			case INT:
				vartype = TN_INT;
				break;
			case DOUBLE:
			case FLOAT:
				vartype = TN_REAL;
				break;
			default:
				printf("UNHANDLED TOKEN%d\n", type);
				break;
			};
			strcpy(typeC, "");
			i++;
			strncat(name, structIdentifier, strlen(structIdentifier));
			strncat(name, middleName, strlen(middleName));
			strncat(name, &SUPPERATOR, 1);

			while (string[i] != SUPPERATOR)
			{
				strncat(name, &string[i], 1);
				i++;
			}
			// printf("name is:%s\n", name);
			strncat(name, &SUPPERATOR, 1);
			symbolTalble->vars = add_variable_to_symbol_table(name, vartype, symbolTalble->vars);
			strcpy(name, "");
			was_found = 1;
		}
		else
		{
			strncat(typeC, &string[i], 1);
			i++;
		}
	}
	return i;
}

char old_middle_name[1000] = "";
char curr_middle_name[1000] = "";

void add_complex_data_type(char *string, char *structIdnt, int startIndex, int endIndex)
{
	int i = startIndex;
	int complex_counter = 0;
	int complex_start_index = 0;
	int complex_end_index = 0;
	int complex_identifier_start_index = 0;
	int complex_identifier_end_index = 0;
	// printf("=================I = Start index = %d\n", i);
	// printf("=================END INDEX = %d\n", endIndex);
	// 00000000001111111111222222222233333333334444444444555555555566666666667777
	// 01234567890123456789012345678901234567890123456789012345678901234567890123
	// 298~a!298~b!298~c!#%aa%298~aa!#%base%298~aa!298~bb!298~cc!#298~bb!298~cc!#
	while(i < endIndex){
		// printf("=========i is: %d\n", i);
		if (string[i] == '%'){
			strcpy(old_middle_name, curr_middle_name);
			i++;
			strncat(curr_middle_name, &SUPPERATOR, 1);
			while (string[i] != '%')
			{
				strncat(curr_middle_name, &string[i], 1);
				i++;
			}
			// printf("middle name is: %s\n", curr_middle_name);
		}
		else if (string[i] == '#') {
			complex_start_index = i;
			complex_counter = 1;
			i++;
			while(complex_counter != 0){
				i++;
				if (string[i] == '#') {
					if (string[i + 1] != '%')
						complex_counter--;
					else
						complex_counter++;
				}
			}
			complex_end_index = i;
			// printf("FOUND DECLERATION OF COMPLEX, which starts at: %d\n", complex_start_index);
			// printf("                                  AND ENDS AT: %d\n", complex_end_index);
			// printf("middle name is: %s\n", middle_name);
			add_complex_data_type(string, structIdnt, complex_start_index + 1, complex_end_index);
			strcpy(curr_middle_name, old_middle_name);
			// while(complex_start_index < complex_end_index){
			// 	complex_start_index = add_simple_struct_to_symbol_table(string, structIdnt, middle_name, complex_start_index);
			// }
		}
		else{
			// printf("before add_simple_struct_to_symbol_table, index of i is: %d\n", i);
			i = add_simple_struct_to_symbol_table(string, structIdnt, curr_middle_name, i);
			// printf("after add_simple_struct_to_symbol_table, index of i is: %d\n", i);
		}
	i++;
	}
}

void add_struct_to_symbolTable(char *string, char *structIdnt)
{
	int i = 0;
	int complex_counter = 0;
	int complex_start_index = 0;
	int complex_end_index = 0;
	while (i < strlen(string))
	{
		if (string[i] == '#'){
			complex_start_index = i;
			complex_counter = 1;
			i++;
			while(complex_counter != 0){
				i++;
				if (string[i] == '#') {
					if (string[i + 1] != '%')
						complex_counter--;
					else
						complex_counter++;
				}
			}
			complex_end_index = i;
			// printf("FOUND DECLERATION OF COMPLEX, which starts at: %d\n", complex_start_index);
			// printf("                                  AND ENDS AT: %d\n", complex_end_index);
			// printf("CALLING TO A FRIEND WHICH WILL HANDLE IT!\n");
			add_complex_data_type(string, structIdnt, complex_start_index + 1, complex_end_index);
		}
		else{
			i = add_simple_struct_to_symbol_table(string, structIdnt, "", i);
		}
		// printf("ADTER i = %d\n", i);
		i ++;
	}
}

/*
*	This function prints all the variables on your symbol table with their data
*	Input: treenode (AST)
*	Output: prints the Sumbol Table on the console
*/
void print_symbol_table(treenode *root)
{
	if (symbolTalble == NULL)
	{
		// printf("---------------------------------------\n");
		// printf("Showing the Symbol Table:\n");
		symbolTalble = (Symbol_table *)malloc(sizeof(Symbol_table));
		symbolTalble->variables_counter = 0;
		symbolTalble->vars = NULL;
		UKNOWN_VARIABLE = (Variable *)malloc(sizeof(Variable));
		UKNOWN_VARIABLE->address = 0;
	}

	treenode *right_node;
	treenode *left_node;
	leafnode *leaf;
	for_node *forn;

	switch (root->hdr.which)
	{
	case NODE_T:
		switch (root->hdr.type)
		{
		case TN_TRANS_LIST:
			print_symbol_table(root->lnode);
			print_symbol_table(root->rnode);
			break;
		case TN_DECL:
			left_node = (treenode *)root->lnode;
			right_node = (treenode *)root->rnode;
			if (left_node->hdr.type == TN_TYPE_LIST)
			{
				if (left_node->lnode != NULL &&
					left_node->lnode->hdr.type == TN_OBJ_DEF)
				{
					left_node = (treenode *)left_node->lnode;
					strcpy(struct_definition, "");
					right_node = (treenode *)left_node->rnode;
					if (right_node != NULL)
					{
						print_symbol_table(right_node);
						if (insert(&tbl, ((leafnode *)left_node->lnode)->data.sval->str, struct_definition) == 0)
						{
							// printf("Inserted KEY IS: %s\n", ((leafnode *)left_node->lnode)->data.sval->str);
							// printf("Inserted value IS: %s\n", struct_definition);
						}
						else
						{
							printf("KIBINIMAT\n");
							/* code */
						}
					}
				}
				else if (right_node != NULL &&
						 right_node->hdr.type == TN_DECL &&
						 right_node->lnode != NULL &&
						 right_node->lnode->hdr.type == TN_PNTR &&
						 right_node->rnode != NULL &&
						 ((leafnode *)right_node->rnode)->hdr.type == TN_IDENT)
					symbolTalble->vars = add_variable_to_symbol_table(((leafnode *)right_node->rnode)->data.sval->str, TN_PNTR, symbolTalble->vars);
				else
				{
					leaf = (leafnode *)left_node->lnode;
					tn_t varType = 0;
					switch (leaf->hdr.tok)
					{
					case FLOAT:
					case DOUBLE:
						varType = TN_REAL;
						break;
					case INT:
						varType = TN_INT;
						break;
					case STRUCT:
						varType = TN_OBJ_DEF;
						if (left_node->lnode != NULL)
						{
							leaf = (leafnode *)left_node->lnode->lnode;
							// printf("Intitlizing new instance of type: %s \n", leaf->data.sval->str); // lihis code must be here
							// printf("Key is: %s\n", get(&tbl, leaf->data.sval->str));
							add_struct_to_symbolTable(get(&tbl, leaf->data.sval->str), ((leafnode *)right_node)->data.sval->str);
							// printf("the address of a!blaAAAA is:%d\n", get_variable_from_table("a!blaAAAA"));
							// printf("the address of a!blabbbbBBBbbb is:%d\n", get_variable_from_table("a!blabbbbBBBbbb"));
							// printf("the address of a!blaccccccc is:%d\n", get_variable_from_table("a!blaccccccc"));
							// printf("the address of a!bladdDDDDD is:%d\n", get_variable_from_table("a!bladdDDDDD"));
							// printf("the address of a!blaEeEeEeE is:%d\n", get_variable_from_table("a!blaEeEeEeE"));
							// printf("the address of a!blablafFfFFfFFFFFFFFFF is:%d\n", get_variable_from_table("a!blafFfFFfFFFFFFFFFF"));
							// printf("the address of a!blagggggggggggggggggggggggg is:%d\n", get_variable_from_table("a!blagggggggggggggggggggggggg"));
							// printf("the address of a!hhhhhhhh is:%d\n", get_variable_from_table("a!hhhhhhhh"));
							// printf("the address of a!jjjjjjjjjjJJjjjjjjjj is:%d\n", get_variable_from_table("a!jjjjjjjjjjJJjjjjjjjj"));
							// printf("the address of a!kkkkkkkkKKKKKKKKKKkkkkkkkkkkk is:%d\n", get_variable_from_table("a!kkkkkkkkKKKKKKKKKKkkkkkkkkkkk"));
							// printf("the address of a!lllllllllLLllllllll is:%d\n", get_variable_from_table("a!lllllllllLLllllllll"));
							//blafFfFFfFFFFFFFFFF
							// printf("the address of b!blaAAAA is:%d\n", get_variable_from_table("b!blaAAAA"));
							// printf("the address of b!blabbbbBBBbbb is:%d\n", get_variable_from_table("b!blabbbbBBBbbb"));
							// printf("the address of b!blaccccccc is:%d\n", get_variable_from_table("b!blaccccccc"));
							// printf("the address of b!bladdDDDDD is:%d\n", get_variable_from_table("b!bladdDDDDD"));
							// printf("the address of b!blaEeEeEeE is:%d\n", get_variable_from_table("b!blaEeEeEeE"));
							// printf("the address of b!blablafFfFFfFFFFFFFFFF is:%d\n", get_variable_from_table("b!blafFfFFfFFFFFFFFFF"));
							// printf("the address of b!blagggggggggggggggggggggggg is:%d\n", get_variable_from_table("b!blagggggggggggggggggggggggg"));
							// printf("the address of b!hhhhhhhh is:%d\n", get_variable_from_table("b!hhhhhhhh"));
							// printf("the address of b!jjjjjjjjjjJJjjjjjjjj is:%d\n", get_variable_from_table("b!jjjjjjjjjjJJjjjjjjjj"));
							// printf("the address of b!kkkkkkkkKKKKKKKKKKkkkkkkkkkkk is:%d\n", get_variable_from_table("b!kkkkkkkkKKKKKKKKKKkkkkkkkkkkk"));
							// printf("the address of b!lllllllllLLllllllll is:%d\n", get_variable_from_table("b!lllllllllLLllllllll"));
							// must say something about memory size!
						}
						else
						{
							printf("Error accoured, couldn't identify structs name in initialization, maybe tree's structure had modified\n");
						}
						break;
					default:
						printf("UNHANDLED TOKEN, value is: %d\n", leaf->hdr.tok);
						break;
					};
					if (right_node->hdr.type == TN_IDENT)
						leaf = (leafnode *)right_node;
					else if (right_node->hdr.type == TN_ASSIGN)
						leaf = (leafnode *)right_node->lnode;
					symbolTalble->vars = add_variable_to_symbol_table(leaf->data.sval->str, varType, symbolTalble->vars);
				}
			}
			else
			{
				printf("SALAM aLEICUM\n");
			}

			break;
		case TN_BLOCK:
			if (root->lnode != NULL)
				print_symbol_table(root->lnode);
			if (root->rnode != NULL)
				print_symbol_table(root->rnode);
			break;
		case TN_FUNC_DECL:
			break;
		case TN_TYPE_LIST:
			if (root->lnode != NULL)
			{
				leaf = (leafnode *)(root->lnode);
				switch (leaf->hdr.tok)
				{
				case INT:
					strcat(struct_definition, "298");
					strncat(struct_definition, &PAIR_SUP, 1);
					break;
				case FLOAT:
				case DOUBLE:
					strcat(struct_definition, "296");
					strncat(struct_definition, &PAIR_SUP, 1);
					break;
				case STRUCT:
					if (leaf->hdr.type == TN_OBJ_REF)
					{
						if (get(&tbl, ((leafnode *)root->lnode->lnode)->data.sval->str) != NULL)
						{
							// printf("ADDING THE FOLLOWING: %s\n", get(&tbl, ((leafnode *)root->lnode->lnode)->data.sval->str), strlen(get(&tbl, ((leafnode *)root->lnode->lnode)->data.sval->str)));
							strncat(struct_definition, get(&tbl, ((leafnode *)root->lnode->lnode)->data.sval->str), strlen(get(&tbl, ((leafnode *)root->lnode->lnode)->data.sval->str)));
							strncat(struct_definition, "#", 1);
						}
					}
					else
					{
						printf("NEED TO FIGURE IT OUT\n");
					}

					break;
				default:
					printf("Unhandled leaf token, it's: %d\n", leaf->hdr.tok);
					break;
				}
			}
			break;
		case TN_DECL_LIST:
			print_symbol_table(root->lnode);
			print_symbol_table(root->rnode);
			break;
		case TN_STEMNT_LIST:
			if (root->lnode != NULL)
				print_symbol_table(root->lnode);
			if (root->rnode != NULL)
				print_symbol_table(root->rnode);
			break;

		case TN_STEMNT:
			if (root->lnode != NULL)
				print_symbol_table(root->lnode);
			else if (root->rnode != NULL)
				print_symbol_table(root->rnode);
			break;
		case TN_ASSIGN:
			break;
		case TN_FUNC_CALL:
			break;
		case TN_COMP_DECL:
			/* struct component declaration - for HW2 */
			if (root->rnode != NULL & root->rnode->hdr.which == LEAF_T && 
				root->lnode != NULL && root->lnode->hdr.type == TN_TYPE_LIST && 
				root->lnode->lnode != NULL && root->lnode->lnode->hdr.type == TN_OBJ_REF){
				strncat(struct_definition, "#", 1);
				strncat(struct_definition, "%", 1);
				strncat(struct_definition, ((leafnode*)root->rnode)->data.sval->str, strlen(((leafnode*)root->rnode)->data.sval->str));
				strncat(struct_definition, "%", 1);
				should_print_id = 0;
			}
			print_symbol_table(root->lnode);
			print_symbol_table(root->rnode);
			strncat(struct_definition, &STR_END, 1);
			should_print_id = 1;

			break;
		case TN_FIELD_LIST:
			print_symbol_table(root->lnode);
			print_symbol_table(root->rnode);
			break;
		default:
			break;
		}
		break;
	case FOR_T:
		// printf("Apperently for and main represents the same fucking way \n");
		forn = (for_node *)root;
		if (forn != NULL)
			print_symbol_table(forn->stemnt);

		break;

	case LEAF_T:
		switch (root->hdr.tok)
		{
		case IDENT:
			if (should_print_id == 1){
				// printf("%s before \n", struct_definition);
				strcat(struct_definition, ((leafnode *)root)->data.sval->str);
				strncat(struct_definition, &SUPPERATOR, 1);
				// printf("%s after \n", struct_definition);
				should_print_id = 1;
			}
			break;
		default:
			printf("UNHANDLED LEAF TOKEN is: %d\n", root->hdr.tok);
			break;
		}
		break;

	default:
		break;
	}
}