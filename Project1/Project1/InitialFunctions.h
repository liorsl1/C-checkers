#pragma once

void allocateTree(SingleSourceMovesTree *tr);

void allocateSingleList(SingleSourceMovesList *lst);

void copyBoard(Board board, Board src);

void allocateMultiListCell(MultipleSourceMovesListCell * src);

void insertToListPointer1(SingleSourceMovesList * lst, SingleSourceMovesListCell * newTail);

void insertToListPointer2(MultipleSourceMovesList * lst, MultipleSourceMovesListCell * newTail);

SingleSourceMovesList insertNodeToEndList(SingleSourceMovesList lst, SingleSourceMovesListCell * newTail);

BOOL isEmptyList(SingleSourceMovesList lst);

void makeEmptyList(SingleSourceMovesList * list);

SingleSourceMovesListCell * createNewCell(checkersPos * pos, unsigned short cap, SingleSourceMovesListCell * next);

void checkMemoryAllocation(void * ptr);

void freeMultipleList(MultipleSourceMovesList* list);

void freeSingleList(SingleSourceMovesList* list);

void FreeTree(SingleSourceMovesTree* tr);

void FreeTreeRec(SingleSourceMovesTreeNode * root);
