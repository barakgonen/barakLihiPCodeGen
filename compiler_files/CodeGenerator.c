#include	"CodeGenerator.h"

typedef struct variable {
	int address;
	char* identifier;
	tn_t type;
	char* value;
	/* Think! what does a Variable contain? */
} Variable;

typedef struct symbol_table {

	/* Think! what does a symbol_table contain? */
	Variable data;
	Variable* next;
} Symbol_table;

Symbol_table symbolTalble;

/*
*	You need to build a data structure for the symbol table
*	I recommend to use linked list.
*
*	You also need to build some functions that add/remove/find element in the symbol table
*/

void add_variable_to_symbol_table(Variable var) 
{
	printf("inside_add_variable to symbol table\n");
	printf("Var identifier is: %s\n", var.identifier);
	printf("Var type is: %d\n", var.type);
	// add to the linked list
}


Variable* get_variable_from_table(const char* name) 
{
	printf("BARAK need to get variable named: \n", name);
	return &symbolTalble.data;
}

void remove_variable_from_symbol_table(const char* name) 
{
	printf("BARAK PREFOREM REMOVE FROM YOUR SYMBOL LIST for this var: \n", name);
}


/*
*	This recursive function is the main method for Code Generation
*	Input: treenode (AST)
*	Output: prints the Pcode on the console
*/
int  code_recur(treenode *root)
{
	printf("PCODE BRO\n");
	if_node  *ifn;
	for_node *forn;
	leafnode *leaf;
	
    if (!root)
        return SUCCESS;

    switch (root->hdr.which){
		case LEAF_T:
			leaf = (leafnode *) root;
			switch (leaf->hdr.type) {
				case TN_IDENT:
					printf(leaf->data.sval->str);
					/*
					*	In order to get the identifier name you have to use:
					*	leaf->data.sval->str
					*/
					break;

				case TN_INT:
					/* 
					*	In order to get the int value you have to use: 
					*	leaf->data.ival 
					*/
					printf("This node represent an Integer");
					printf("%d", leaf->data.ival);
					break;

				case TN_REAL:
					/*
					*	In order to get the real value you have to use:
					*	leaf->data.dval
					*/
					printf("%f", leaf->data.dval);
					break;
			}
			break;

		case IF_T:
			ifn = (if_node *) root;
			switch (ifn->hdr.type) {
				case TN_IF:
					if (ifn->else_n == NULL) {
						/* if case */
						code_recur(ifn->cond);
						code_recur(ifn->then_n);
					}
					else {
						/* if - else case*/ 
						code_recur(ifn->cond);
						code_recur(ifn->then_n);
						code_recur(ifn->else_n);
					}
					return 0;

				case TN_COND_EXPR:
					code_recur(ifn->cond);
					code_recur(ifn->then_n);
					code_recur(ifn->else_n);
					break;
				/*
				*	Maybe there is more cases!
				*	Add them here
				*/
			}
			break;

		case FOR_T:
			forn = (for_node *) root;
			switch (forn->hdr.type) {
				case TN_FUNC_DEF:
					code_recur(forn->init);
					code_recur(forn->test);
					code_recur(forn->incr);
					code_recur(forn->stemnt);
					break;

				case TN_FOR:
					code_recur(forn->init);
					code_recur(forn->test);
					code_recur(forn->stemnt);
					code_recur(forn->incr);
					return 0;
				/*
				*	Maybe there is more cases!
				*	Add them here
				*/
			}
			break;

		case NODE_T:
			switch (root->hdr.type) {
				case TN_ASSIGN:
					code_recur(root->lnode);
					code_recur(root->rnode);
					break;

				case TN_EXPR:
					switch (root->hdr.tok) {
					  case PLUS:
						  code_recur(root->lnode);
						  code_recur(root->rnode);
						  break;

					  case MINUS:
						  code_recur(root->lnode);
						  code_recur(root->rnode);
						  break;
					  case DIV:
						  code_recur(root->lnode);
						  code_recur(root->rnode);
						  break;
					  case STAR:
						  code_recur(root->lnode);
						  code_recur(root->rnode);
						  break;
					  case NOT:
						  code_recur(root->lnode);
						  code_recur(root->rnode);
						  break;
					  case AND:
						  code_recur(root->lnode);
						  code_recur(root->rnode);
						  break;
					  case EQUAL:
						  code_recur(root->lnode);
						  code_recur(root->rnode);
						  break;
					  case NOT_EQ:
						  code_recur(root->lnode);
						  code_recur(root->rnode);
						  break;
					  case GRTR:
						  code_recur(root->lnode);
						  code_recur(root->rnode);
						  break;
					  case LESS:
						  code_recur(root->lnode);
						  code_recur(root->rnode);
						  break;
					  case GRTR_EQ:
						  code_recur(root->lnode);
						  code_recur(root->rnode);
						  break;
					  case LESS_EQ:
						  code_recur(root->lnode);
						  code_recur(root->rnode);
						  break;
					  case INCR:
						  code_recur(root->lnode);
						  code_recur(root->rnode);
						  break;
					  case DECR:
						  code_recur(root->lnode);
						  code_recur(root->rnode);
						  break;
					  /*
					  *	Maybe there is more cases!
					  *	Add them here
					  */
					}
					break;

				case TN_WHILE:
					code_recur(root->lnode);
					code_recur(root->rnode);
					return 0;

				case TN_DOWHILE:
					code_recur(root->lnode);
					code_recur(root->rnode);				
					break;
				/*
				*	Maybe there is more cases!
				*	Add them here
				*/
			}
			break;

		case NONE_T:
			printf("Error: Unknown node type!\n");
			exit(FAILURE);
    }

    return SUCCESS;
}


/*
*	This function prints all the variables on your symbol table with their data
*	Input: treenode (AST)
*	Output: prints the Sumbol Table on the console
*/
void print_symbol_table(treenode *root) {
	treenode *right_node;
	treenode *left_node;
	leafnode *leaf;
	//printf("---------------------------------------\n");
	//printf("Showing the Symbol Table:\n");

	//root->hdr.c_contxt->tags
	/*
	*	add your code here
	*/

	switch (root->hdr.which) {
		case NODE_T:
			switch (root->hdr.type) {
				case TN_TRANS_LIST:
					//printf(node->hdr);
					printf("This is TN_TRANS_LIST, means it childs\n");
					print_symbol_table(root->lnode);
					print_symbol_table(root->rnode);
					break;
				case TN_DECL:
					printf("==================================================\n");
					// printf("I should add you to the symbol table, but first of all, i need to parse you to a variable\n");
					// printf("Lets find some data:\n");
					left_node = (treenode *)root->lnode;
					right_node = (treenode *)root->rnode;
					
					Variable* var = malloc(sizeof(Variable));
					if (left_node->hdr.type == TN_TYPE_LIST && right_node->hdr.type == TN_IDENT)
					{
						// printf("Found a decleration node!! \n");
						leaf = (leafnode *) left_node->lnode;
						var->type = leaf->hdr.type;
						leaf = (leafnode *) right_node;
						var->identifier = leaf->data.str;
						add_variable_to_symbol_table(*var);
					}
					else
					{
						printf("NADA\n");
					}
					free(var);
					
					printf("==================================================\n");
					break;
			}
			break;
	}
}

