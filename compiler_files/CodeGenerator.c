#include	"CodeGenerator.h"

typedef struct symbol_table {

	/* Think! what does a symbol_table contain? */

} Symbol_table;

typedef struct variable {

	/* Think! what does a Variable contain? */

} Variable;

/*
*	You need to build a data structure for the symbol table
*	I recommend to use linked list.
*
*	You also need to build some functions that add/remove/find element in the symbol table
*/


/*
*	This recursive function is the main method for Code Generation
*	Input: treenode (AST)
*	Output: prints the Pcode on the console
*/
int  code_recur(treenode *root)
{
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
					break;

				case TN_REAL:
					/*
					*	In order to get the real value you have to use:
					*	leaf->data.dval
					*/
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
	printf("---------------------------------------\n");
	printf("Showing the Symbol Table:\n");
	/*
	*	add your code here
	*/
}