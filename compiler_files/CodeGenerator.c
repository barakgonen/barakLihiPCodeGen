#include	"CodeGenerator.h"

const int CODE_INIT_FRAME_IN_BYTES = 4;

typedef struct variable {
	int address;
	char* identifier;
	tn_t type;
	char* value;
	int is_value_set;
	int data_as_int;
	/* Think! what does a Variable contain? */
} Variable;

typedef struct variable_node {
	// Representation of a single variable node, hold data about it's own Variable and a pointer to the next one
	struct variable data;
	struct variable_node* next;
} VariableNode;

typedef struct symbol_table {
	// This struct holds a linked list of variables called vars, and a counter for current number of variables
	VariableNode* vars;
	int variables_counter;
} Symbol_table;

Symbol_table* symbolTalble = NULL;
VariableNode* endOfVariablesTable = NULL;
Variable* UKNOWN_VARIABLE = NULL;

/*
*	You need to build a data structure for the symbol table
*	I recommend to use linked list.
*
*	You also need to build some functions that add/remove/find element in the symbol table
*/

void add_variable_to_symbol_table(VariableNode** head_ref, Variable var_to_add) 
{
	// printf("      <add_variable_to_symbol_table()> inside_add_variable to symbol table\n");
	// Incresing symbol table size by 1 in oreder to decide the address of the variable
	symbolTalble->variables_counter += 1;
	
	// Creating an instance of a new variable
	struct variable_node* var_node = (struct variable_node*)malloc(sizeof(struct variable_node));

	var_node->next = (*head_ref);
	var_node->data = var_to_add;
	var_node->data.address = CODE_INIT_FRAME_IN_BYTES + symbolTalble->variables_counter;
	
	printf("         <add_variable_to_symbol_table()> new_var identifier is: %s\n", var_node->data.identifier);
	printf("         <add_variable_to_symbol_table()> new_var type is: %d\n", var_node->data.type);
	printf("         <add_variable_to_symbol_table()> new_var address is: %d\n", var_node->data.address);
	if (var_node->data.is_value_set == 1){ 
		printf("         <add_variable_to_symbol_table()> new_var value is: %d\n", var_node->data.data_as_int);
	}

	(*head_ref) = var_node;
}

Variable get_variable_from_table(const char* name) 
{
	// printf("      <get_variable_from_table()> need to get variable named: %s\n", name);
	VariableNode* tmp_var_lst = symbolTalble->vars;
	if (tmp_var_lst == NULL) {
		printf("      <get_variable_from_table()> ERROR! \n");
	}
	else {
		while(tmp_var_lst != endOfVariablesTable && tmp_var_lst != NULL ){
		// && tmp_var_lst->data != NULL) {
			// printf("var name: %s\n", tmp_var_lst->data.identifier);
			if(strcmp(tmp_var_lst->data.identifier, name) == 0) { 
				return tmp_var_lst->data;
			}
			tmp_var_lst = tmp_var_lst->next;
		}
	}
	// free(tmp_var_lst);
	return *UKNOWN_VARIABLE;
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
	if (symbolTalble == NULL) {
		// printf("---------------------------------------\n");
		// printf("Showing the Symbol Table:\n");
		symbolTalble = (Symbol_table*)malloc(sizeof(Symbol_table));
		symbolTalble->variables_counter = 0;
		endOfVariablesTable = symbolTalble->vars;
		// printf("<print_symbol_table()> Initialized the symbol table, it should happen only once. current variables_counter is: %d\n", symbolTalble->variables_counter);
		print_symbol_table(root);
	}
	if_node  *ifn;
	for_node *forn;
	leafnode *leaf;
	Variable target_var;
	Variable src_var;
	treenode *right_node;
	treenode *left_node;
	
    if (!root)
        return SUCCESS;

    switch (root->hdr.which){
		case LEAF_T:
			leaf = (leafnode *) root;
			switch (leaf->hdr.type) {
				case TN_LABEL:
					/* Maybe you will use it later */
					break;

				case TN_IDENT:
					// printf("%s\n", leaf->data.sval->str);
					/*
					*	In order to get the identifier name you have to use:
					*	leaf->data.sval->str
					*/
					break;

				case TN_COMMENT:
					/* Maybe you will use it later */
					break;

				case TN_ELLIPSIS:
					/* Maybe you will use it later */
					break;

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
					// printf("This node represent an Integer: \n%d", leaf->data.ival);
					break;

				case TN_REAL:
					/*
					*	In order to get the real value you have to use:
					*	leaf->data.dval
					*/
					// printf("%f\n", leaf->data.dval);
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

				default:
				/* Maybe you will use it later */
				code_recur(ifn->cond);
				code_recur(ifn->then_n);
				code_recur(ifn->else_n);
			}
			break;

		case FOR_T:
			forn = (for_node *) root;
			switch (forn->hdr.type) {

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
				code_recur(forn->init);
				code_recur(forn->test);
				code_recur(forn->stemnt);
				code_recur(forn->incr);
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
			switch (root->hdr.type) {
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
					if (strcmp(((leafnode*)root->lnode)->data.sval->str, "printf") == 0) {
						/* printf case */
						/* The expression that you need to print is located in */
						/* the currentNode->right->right sub tree */
						/* Look at the output AST structure! */
						// printf("left: %s\n", ((leafnode*)root->rnode->lnode)->data.sval);
						// printf("right: %d\n", ((leafnode*)root->rnode->rnode)->data.ival);
						switch (((leafnode*)root->rnode->rnode)->hdr.type){
							case TN_INT:
								printf("LDC %d\n", ((leafnode*)root->rnode->rnode)->data.ival);
							break;
							case TN_IDENT:
								printf("BBBBBBBB\n");
							// 	src_var = get_variable_from_table(((leafnode*)root->rnode->rnode)->data.sval->str);
							// 	if (src_var != NULL)
							// 		printf("need to print var identified as: %s\n", src_var->identifier);
							// 	else
							// 		printf("it was null i think, i couldnt find var named: %s\n", ((leafnode*)root->rnode->rnode)->data.sval->str);
								break;
							// default:
							// 	printf("type is: %s\n", ((leafnode*)root->rnode->rnode)->hdr.type);
							// break;
						}
						printf("PRINT\n");
					}
					else {
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
					// printf("I should add you to the symbol table, but first of all, i need to parse you to a variable\n");
					// printf("Lets find some data:\n");
					left_node = (treenode *)root->lnode;
					right_node = (treenode *)root->rnode;
					leaf = (leafnode*) root->rnode;

					if (left_node->hdr.type == TN_TYPE_LIST)
					{
						if (right_node->hdr.type == TN_IDENT && right_node->hdr.which == LEAF_T)
						{

							// target_var = get_variable_from_table(leaf->data.sval->str);		
							// if (target_var !=NULL){
							// 	printf("LDC %d\n", target_var->address);
							// 	target_var = NULL;
							// }
							// else
							// 	printf("ERROR variable hasn't found in symbol table!\n");
						}
					}
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
					if (root->hdr.tok == RETURN) {
						/* return jump - for HW2! */
						code_recur(root->lnode);
						code_recur(root->rnode);
					}
					else if (root->hdr.tok == BREAK) {
						/* break jump - for HW2! */
						code_recur(root->lnode);
						code_recur(root->rnode);
					}
					else if (root->hdr.tok == GOTO) {
						/* GOTO jump - for HW2! */
						code_recur(root->lnode);
						code_recur(root->rnode);
					}
					break;

				case TN_SWITCH:
					/* Switch case - for HW2! */
					code_recur(root->lnode);
					code_recur(root->rnode);
					break;

				case TN_INDEX: 
					/* call for array - for HW2! */
					code_recur(root->lnode);
					code_recur(root->rnode);
					break;

				case TN_DEREF:
					/* pointer derefrence - for HW2! */
					code_recur(root->lnode);
					code_recur(root->rnode);
					break;

				case TN_SELECT:
					/* struct case - for HW2! */
					if (root->hdr.tok == ARROW){
						/* Struct select case "->" */
						/* e.g. struct_variable->x; */
						code_recur(root->lnode);
						code_recur(root->rnode);
					}
					else{
						/* Struct select case "." */
						/* e.g. struct_variable.x; */
						code_recur(root->lnode);
						code_recur(root->rnode);
					}
					break;

				case TN_ASSIGN:
					leaf = (leafnode*) root->lnode;
					target_var = get_variable_from_table(leaf->data.sval->str);
					if(root->hdr.tok == EQ){
						/* Regular assignment "=" */
						/* e.g. x = 5; */
						// printf("   in TN_ASSIGN case =, need to preform: ");
						// printf("%s", leaf->data.sval->str);
						leaf = (leafnode*) root->rnode;
						switch(leaf->hdr.type) {
							case(TN_INT):
								// printf(" = %d\n", leaf->data.ival);
								printf("LDC %d\n", target_var.address);
								printf("LDC %d\n", leaf->data.dval);
								printf("STO\n");
							break;
							case(TN_REAL):
								printf(" = %f\n", leaf->data.dval);
							break;
							case(TN_IDENT):
								printf(" this is classic initialization without an assignment like int x;\n");
								// printf("Need to check symbol-table for the address of: %s\n", target_var.identifier);
								break;
							default:
								printf("ERROR, type is: %d\n", leaf->hdr.type);
								break;
						}
						
					}
					else if (root->hdr.tok == PLUS_EQ){
						/* Plus equal assignment "+=" */
						/* e.g. x += 5; */
						leaf = (leafnode*) root->rnode;
						src_var= get_variable_from_table(leaf->data.sval->str);
						printf("LDC %d\n", target_var.address);
						printf("LDC %d\n", src_var.address);
						printf("ADD\n");
					}
					else if (root->hdr.tok == MINUS_EQ){
						/* Minus equak assigment "-=" */
						/* e.g. x-= 5; */
						leaf = (leafnode*) root->rnode;
						src_var= get_variable_from_table(leaf->data.sval->str);
						printf("LDC %d\n", target_var.address);
						printf("LDC %d\n", src_var.address);
						printf("SUB\n");
					}
					else if (root->hdr.tok == STAR_EQ){
						/* Multiply equal assignment "*=" */
						/* e.g. x *= 5; */
						leaf = (leafnode*) root->rnode;
						src_var = get_variable_from_table(leaf->data.sval->str);
						// printf("   in TN_ASSIGN case *=, need to preform:  \n");
						printf("LDC %d\n", target_var.address);
						printf("LDC %d\n", src_var.address);
						printf("MUL\n");
					}
					else if (root->hdr.tok == DIV_EQ){
						/* Divide equal assignment "/=" */
						/* e.g. x /= 5; */
						leaf = (leafnode*) root->rnode;
						src_var = get_variable_from_table(leaf->data.sval->str);
						// printf("   in TN_ASSIGN case *=, need to preform:  \n");
						printf("LDC %d\n", target_var.address);
						printf("LDC %d\n", src_var.address);
						printf("DIV\n");
					}
					break;

				case TN_EXPR:
					switch (root->hdr.tok) {
					  case CASE:
					      /* you should not get here */
						  code_recur(root->lnode);
						  code_recur(root->rnode);
						  break;

					  case INCR:
						  /* Increment token "++" */
						  code_recur(root->lnode);
						  code_recur(root->rnode);
						  break;

					  case DECR:
						  /* Decrement token "--" */
						  code_recur(root->lnode);
						  code_recur(root->rnode);
						  break;

					  case PLUS:
					  	  /* Plus token "+" */
						  code_recur(root->lnode);
						  code_recur(root->rnode);
						  break;

					  case MINUS:
					  	  /* Minus token "-" */
						  code_recur(root->lnode);
						  code_recur(root->rnode);
						  break;

					  case DIV:
					  	  /* Divide token "/" */
						  code_recur(root->lnode);
						  code_recur(root->rnode);
						  break;

					  case STAR:
					  	  /* multiply token "*" */
						  code_recur(root->lnode);
						  code_recur(root->rnode);
						  break;

					  case AND:
					  	  /* And token "&&" */
						  code_recur(root->lnode);
						  code_recur(root->rnode);
						  break;

					  case OR:
					  	  /* Or token "||" */
						  code_recur(root->lnode);
						  code_recur(root->rnode);
						  break;
						
					  case NOT:
					  	  /* Not token "!" */
						  code_recur(root->lnode);
						  code_recur(root->rnode);
						  break;

					  case GRTR:
					  	  /* Greater token ">" */
						  code_recur(root->lnode);
						  code_recur(root->rnode);
						  break;

					  case LESS:
					  	  /* Less token "<" */
						  code_recur(root->lnode);
						  code_recur(root->rnode);
						  break;
						  
					  case EQUAL:
					  	  /* Equal token "==" */
						  code_recur(root->lnode);
						  code_recur(root->rnode);
						  break;

					  case NOT_EQ:
					  	  /* Not equal token "!=" */
						  code_recur(root->lnode);
						  code_recur(root->rnode);
						  break;

					  case LESS_EQ:
					  	  /* Less or equal token "<=" */
						  code_recur(root->lnode);
						  code_recur(root->rnode);
						  break;

					  case GRTR_EQ:
					  	  /* Greater or equal token ">=" */
						  code_recur(root->lnode);
						  code_recur(root->rnode);
						  break;

					  default:
						code_recur(root->lnode);
						code_recur(root->rnode);
						break;
					}
					break;

				case TN_WHILE:
					/* While case */
					code_recur(root->lnode);
					code_recur(root->rnode);
					break;

				case TN_DOWHILE:
					/* Do-While case */
					code_recur(root->rnode);
					code_recur(root->lnode);
					break;

				case TN_LABEL:
					code_recur(root->lnode);
					code_recur(root->rnode);
					break;

				default:
					code_recur(root->lnode);
					code_recur(root->rnode);
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
	if (symbolTalble == NULL) {
		printf("---------------------------------------\n");
		printf("Showing the Symbol Table:\n");
		symbolTalble = (Symbol_table*)malloc(sizeof(Symbol_table));
		symbolTalble->variables_counter = 0;
		endOfVariablesTable = symbolTalble->vars;
		UKNOWN_VARIABLE = (Variable*)malloc(sizeof(Variable));
		printf("<print_symbol_table()> Initialized the symbol table, it should happen only once. current variables_counter is: %d\n", symbolTalble->variables_counter);
	}
	// printf("current size of symbol table is: %d\n", symbolTalble->variables_counter);
	treenode *right_node;
	treenode *left_node;
	leafnode *leaf;
	for_node* forn;

	//root->hdr.c_contxt->tags
	/*
	*	add your code here
	*/
	switch(root->hdr.which) {
		case NODE_T:
			switch (root->hdr.type) {
				case TN_TRANS_LIST:
					// printf("root->left type: %d\n", root->lnode->hdr.type);
					print_symbol_table(root->lnode);
					// printf("root->right type: %d\n", root->rnode->hdr.type);
					print_symbol_table(root->rnode);
					break;
				case TN_DECL:
					printf("   =================================================================================================================\n");
					// printf("I should add you to the symbol table, but first of all, i need to parse you to a variable\n");
					// printf("Lets find some data:\n");
					left_node = (treenode *)root->lnode;
					right_node = (treenode *)root->rnode;
					
					Variable* var = malloc(sizeof(Variable));
					if (left_node->hdr.type == TN_TYPE_LIST && right_node->hdr.type == TN_IDENT)
					{
						printf("Found a decleration node!!! \n");
						leaf = (leafnode *) left_node->lnode;
						var->type = leaf->hdr.type;
						leaf = (leafnode *) right_node;
						// printf("BAKBAK SIZE IS: %d\n", sizeof(leaf->data.str));
						// printf("BAKBAK strlen IS: %d\n", strlen(leaf->data.str));
						// var->identifier = malloc(strlen(leaf->data.str) + 1);
						// strcpy(var->identifier, leaf->data.str);
						// printf("size of identifier is: %d\n", sizeof(leaf->data.sval));
						var->identifier = leaf->data.sval->str;
						// var->data_as_int = malloc(sizeof(int));
						var->is_value_set = 0;
						// strcpy(var->identifier, leaf->data.sval->str);
						add_variable_to_symbol_table(&symbolTalble->vars, *var);
					}
					else if (left_node->hdr.type == TN_TYPE_LIST &&right_node->hdr.type == TN_ASSIGN)
					{
							printf("Found a decleration node! for type int bla = 7; \n");
							leaf = (leafnode *) right_node->lnode;
							// printf("identifier = %s\n", leaf->data.sval->str);
							var->identifier = leaf->data.sval->str;
							leaf = (leafnode *) right_node->rnode;
							var->type = leaf->hdr.type;
							// var->is_data_set = 1;
							switch (leaf->hdr.type){
								case (TN_INT):
									// printf("value = %d\n", leaf->data.u_ival);
									var->is_value_set = 1;
									var->data_as_int = leaf->data.u_ival;
									// var->integer_data = leaf->data.u_ival;
									// sprintf(var->value, "%d", leaf->data.u_ival);
									break;
								case (TN_REAL):
									printf("value = %f\n", leaf->data.dval);
									// var->float_data = leaf->data.dval;
									// sprintf(var->value, "%f", leaf->data.dval);
									break;
								default:
									printf("DEFFFFFFAULT my type is: %d\n", leaf->hdr.type);
									break;
							}
							add_variable_to_symbol_table(&symbolTalble->vars, *var);
					}
					else
					{
						printf("NADA\n");
					// if (left_node->hdr.type == TN_TYPE_LIST)
					// {
					// 	if (right_node->hdr.type == TN_IDENT && right_node->hdr.which == LEAF_T)
					// 	{
					// 		// printf("Found a decleration node! for type int bla; that's why setting is_data_set flag to false\n");
					// 		// var->is_data_set = 0;
					// 		leaf = (leafnode *) left_node->lnode;
					// 		var->type = leaf->hdr.type;
					// 		leaf = (leafnode *) right_node;
					// 		var->identifier = leaf->data.sval->str;
					// 		add_variable_to_symbol_table(&symbolTalble->vars, var);
					// 	}
					// 	
						// }
						// else
						// {
							// printf("NADA\n");
						// }	
					}
					free(var);
					printf("   !!===============================================================================================================\n");
					break;
				case TN_BLOCK:
					// printf("in TN_BLOCK\n");
					// printf("root->left type: %d\n", root->lnode->hdr.type);
					if (root->lnode != NULL) {
						print_symbol_table(root->lnode);
					}
					// printf("root->right type: %d\n", root->rnode->hdr.type);
					if (root->rnode != NULL){
						print_symbol_table(root->rnode);
					}
					break;
				case TN_FUNC_DECL:
					// printf("   in TN_FUNC_DECL\n");
					// printf("kids types: \n");
					// printf("%d\n", root->lnode->hdr.type);
					// printf("%d\n", root->rnode->hdr.type);
					break;
				case TN_TYPE_LIST:
					// printf("   TN_TYPE_LIST\n");
					break;
				case TN_DECL_LIST:
					// printf("root->left type: %d\n", root->lnode->hdr.type);
					if (root->lnode != NULL) {
						print_symbol_table(root->lnode);
					}
					// printf("root->right type: %d\n", root->rnode->hdr.type);
					if (root->rnode != NULL){
						print_symbol_table(root->rnode);
					}
					break;
				case TN_STEMNT_LIST:
					printf("   in TN_STEMNT_LIST\n");
					if (root->lnode != NULL) {
						print_symbol_table(root->lnode);
					}
					// printf("root->right type: %d\n", root->rnode->hdr.type);
					if (root->rnode != NULL){
						print_symbol_table(root->rnode);
					}
					break;

				case TN_STEMNT:
					printf("   in TN_STEMNT\n");
					if (root->lnode == NULL && root->rnode->hdr.type ==TN_JUMP){
						printf("   This is the return statement!\n");
					}
					else if (root->lnode != NULL) {
						print_symbol_table(root->lnode);
					}
					// printf("root->right type: %d\n", root->rnode->hdr.type);
					else if (root->rnode != NULL){
						print_symbol_table(root->rnode);
					}
				break;
				case TN_ASSIGN:
					printf("   TN_ASSIGN, relevant for PCode generation\n");
				break;
				case TN_FUNC_CALL:
				break;
				default:
					printf("BBDFSDFDSDSFDSFDS my type is: %d\n", root->hdr.type);
					break;
			}
			break;
		case FOR_T:
			printf("Apperently for and main represents the same fucking way \n");
			forn = (for_node *) root;
			if (forn != NULL){
				print_symbol_table(forn->stemnt);
			}
			// printf("%d\n", forn->stemnt->hdr.type);

			break;
		default:
			printf("Barak, unrecognized which: %d\n", root->hdr.which);
	}
}

int counter = 0;

void print_variable_data(const char* varID){
	Variable v = get_variable_from_table(varID);
	if (v.address != UKNOWN_VARIABLE->address){
		printf("         <print_variable_data()> new_var identifier is: %s\n", v.identifier);
		printf("         <print_variable_data()> new_var type is: %d\n", v.type);
		printf("         <print_variable_data()> new_var address is: %d\n", v.address);
		if (v.is_value_set == 1)
		{
			printf("         <print_variable_data()> value is: ");
			switch (v.type){
				case (TN_INT):
					printf("value = %d\n", v.data_as_int);
					break;
				case (TN_REAL):
					printf("value = %f\n", v.value);
					break;
				default:
					printf("DEFFFFFFAULT my type is: %d\n", v.type);
					break;
			}
		}
		else{
			printf("         <print_variable_data()> variable initialized but without value, it's value is null\n");
		}

	}
	else{
		printf("         <print_variable_data()> couldnt find var named %s\n", varID);
	}
	counter += 1;
}

void print_result() {
	printf("   !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
	printf("   I'd like to iterate all the variables and print them\n");
	print_variable_data("a");
	print_variable_data("abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyz");
	// print_variable_data("AB");
	print_variable_data("b");
	// print_variable_data("c");
	// print_variable_data("d");
	// print_variable_data("e");
	// print_variable_data("f");
	// print_variable_data("c");
	// print_variable_data("d");
	// print_variable_data("e");
	// print_variable_data("f");
	// print_variable_data("j");
	// print_variable_data("g");
	// print_variable_data("h");
	// print_variable_data("i");
	// print_variable_data("j");
	// print_variable_data("k");
	printf("   Well Done! Code tested: %d%s%d\n", counter, " times, total number of variables in SymbolTable is:", symbolTalble->variables_counter);
	printf("   !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
	return;
}
 
// /* Function to print nodes in a given linked list. fpitr is used 
//    to access the function to be used for printing current node data. 
//    Note that different data types need different specifier in printf() */
// void printList(struct Node *node, void (*fptr)(void *)) 
// { 
//     while (node != NULL) 
//     { 
//         (*fptr)(node->data); 
//         node = node->next; 
//     } 
// } 
  
// // Function to print an integer 
// void printInt(void *n) 
// { 
//    printf(" %d", *(int *)n); 
// } 
  
// // Function to print a float 
// void printFloat(void *f) 
// { 
//    printf(" %f", *(float *)f); 
// } 
  
// /* Driver program to test above function */
// int main() 
// { 
//     struct Node *start = NULL; 
  
//     // Create and print an int linked list 
//     unsigned int_size = sizeof(int); 
//     int arr[] = {10, 20, 30, 40, 50}, i; 
//     for (i=4; i>=0; i--) 
//        push(&start, &arr[i], int_size); 
//     printf("Created integer linked list is \n"); 
//     printList(start, printInt); 
  
//     // Create and print a float linked list 
//     unsigned float_size = sizeof(float); 
//     start = NULL; 
//     float arr2[] = {10.1, 20.2, 30.3, 40.4, 50.5}; 
//     for (i=4; i>=0; i--) 
//        push(&start, &arr2[i], float_size); 
//     printf("\n\nCreated float linked list is \n"); 
//     printList(start, printFloat); 
  
//     return 0; 
// } 
