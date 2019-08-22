#include "BoardStructure.h"
#include "InitialFunctions.h"

//Allocate tree
void allocateTree(SingleSourceMovesTree * tr)
{
tr->source =(SingleSourceMovesTreeNode*) calloc(1,sizeof(SingleSourceMovesTreeNode));
checkMemoryAllocation(tr->source);

tr->source->pos = (checkersPos*)malloc(sizeof(checkersPos));
checkMemoryAllocation(tr->source->pos);

tr->source->next_move[0] =(SingleSourceMovesTreeNode*) calloc(1,sizeof(SingleSourceMovesTreeNode));
checkMemoryAllocation(tr->source->next_move[0]);

tr->source->next_move[1] =(SingleSourceMovesTreeNode*) calloc(1,sizeof(SingleSourceMovesTreeNode));
checkMemoryAllocation(tr->source->next_move[1]);

tr->source->next_move[0]->pos =(checkersPos*) malloc(sizeof(checkersPos));
checkMemoryAllocation(tr->source->next_move[0]->pos);

tr->source->next_move[1]->pos = (checkersPos*)malloc(sizeof(checkersPos));
checkMemoryAllocation(tr->source->next_move[1]->pos);

tr->source->next_move[0]->next_move[0] = NULL;
tr->source->next_move[1]->next_move[0] = NULL;
tr->source->next_move[0]->next_move[1] = NULL;
tr->source->next_move[1]->next_move[1] = NULL;

}

void copyBoard(Board board, Board src) {
	int i = 0, j = 0;
	for (i; i < BOARD_SIZE; i++) {
		for (j = 0; j < BOARD_SIZE; j++) {
			board[i][j] = src[i][j];
		}
	}
}
void allocateMultiListCell(MultipleSourceMovesListCell *src)
{
	src->single_source_moves_list =(SingleSourceMovesList*) calloc(1, sizeof(SingleSourceMovesList));
	src->next = (MultipleSourceMovesListCell*) calloc(1, sizeof(MultipleSourceMovesListCell));
}

void insertToListPointer1(SingleSourceMovesList *lst, SingleSourceMovesListCell * newTail) {
	if (isEmptyList(*lst))
	{
		lst->head = lst->tail = newTail;
	}
	else
	{
		lst->tail->next = newTail;
		lst->tail = newTail;
	}
}
void insertToListPointer2(MultipleSourceMovesList *lst, MultipleSourceMovesListCell * newTail) {
	if (lst->head == NULL)
	{
		lst->head = lst->tail = newTail;
	}
	else
	{
		lst->tail->next = newTail;
		lst->tail = newTail;
	}
}
SingleSourceMovesList insertNodeToEndList(SingleSourceMovesList lst, SingleSourceMovesListCell * newTail)
{
	if (isEmptyList(lst))
	{
		lst.head = lst.tail = newTail;
	}
	else
	{
		lst.tail->next = newTail;
		lst.tail = newTail;
	}
	return lst;
}
BOOL isEmptyList(SingleSourceMovesList lst)
{
	return (lst.head == NULL);
}

void makeEmptyList(SingleSourceMovesList* list)
{

	(*list).head = (*list).tail = NULL;
}
SingleSourceMovesListCell* createNewCell(checkersPos* pos, unsigned short cap, SingleSourceMovesListCell* next) {
	SingleSourceMovesListCell* newCell = (SingleSourceMovesListCell*)calloc(1, sizeof(SingleSourceMovesListCell));
	newCell->position = pos;
	newCell->captures = cap;
	newCell->next = next;
	return newCell;
}
void checkMemoryAllocation(void * ptr)
{
	if (!ptr) {
		printf("allocation error\n");
		exit(1);
	}
}
//free MultipleSourceList
void freeMultipleList(MultipleSourceMovesList * list)
{
	MultipleSourceMovesListCell* curr = list->head;
	MultipleSourceMovesListCell* temp;
	while (curr != NULL) {
		temp = curr;
		curr = curr->next;
		if(temp->single_source_moves_list!=NULL)
		freeSingleList(temp->single_source_moves_list);
		free(temp);
	}
}
//free singleSourceList
void freeSingleList(SingleSourceMovesList * list)
{
	SingleSourceMovesListCell *curr = list->head;
	SingleSourceMovesListCell * temp;
	while (curr != NULL) {
		temp = curr;
		curr = curr->next;
		free(temp->position);
		free(temp);
	}
}

void FreeTree(SingleSourceMovesTree* tr)
{
	FreeTreeRec(tr->source);
}

//FreeTreeRec() function recursively free all tree nodes.
void FreeTreeRec(SingleSourceMovesTreeNode *root)
{
	if (root != NULL)
	{
		free(root->pos);
		FreeTreeRec(root->next_move[0]);
		FreeTreeRec(root->next_move[1]);
		free(root);
	}
}
