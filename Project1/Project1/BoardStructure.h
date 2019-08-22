#pragma once
#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BOARD_SIZE 8
#define TRUE 1
#define FALSE 0
#define EMPTY ' '
#define ROW_INDEX 'A'
#define BOTTOM 'B'
#define TOP 'T'
typedef int BOOL;
typedef unsigned char Board[BOARD_SIZE][BOARD_SIZE];
typedef unsigned char Player;
typedef struct _checkersPos
{
	char row, col;
}checkersPos;

typedef struct _SingleSourceMovesTreeNode
{
	Board board;
	checkersPos *pos;
	unsigned short total_captures_so_far;
	struct _SingleSourceMovesTreeNode *next_move[2];
}SingleSourceMovesTreeNode;
typedef struct _SingleSourceMovesTree
{
	SingleSourceMovesTreeNode *source;
}SingleSourceMovesTree;

typedef struct _SingleSourceMovesListCell {
	checkersPos *position;
	unsigned short captures;
	struct _SingleSourceMovesListCell *next;
}SingleSourceMovesListCell;
typedef struct _SingleSourceMovesList {
	SingleSourceMovesListCell *head;
	SingleSourceMovesListCell *tail;
}SingleSourceMovesList;

typedef struct _multipleSourceMovesListCell {
	SingleSourceMovesList *single_source_moves_list;
	struct _multipleSourceMovesListCell *next;
}MultipleSourceMovesListCell;
typedef struct _multipleSourceMovesList {
	MultipleSourceMovesListCell *head;
	MultipleSourceMovesListCell *tail;
}MultipleSourceMovesList;
//

SingleSourceMovesTree *FindSingleSourceMoves(Board board, checkersPos *src);

void CreateCaptureMovesRec(Board board, int row, int col, SingleSourceMovesTreeNode ** root, char currPlayer,int direction,int count, unsigned short captures);

void InitializeBoard(Board *board);

void printBoardPlatform(Board board);

void Turn(Board board, Player player);

void DeleteAndUpdateBoard(Board board, SingleSourceMovesListCell *moves, int capture, Player player);

void StoreBoard(Board board, char * filename);

void LoadBoard(char * filename, Board board);

void PlayGame(Board board, Player starting_player);

Player checkForWinner(Board board, Player player);

void getAndSetMaxCapturesList(MultipleSourceMovesListCell * src, SingleSourceMovesList ** bestMove, short * max);

SingleSourceMovesList * FindSingleSourceOptimalMove(SingleSourceMovesTree * moves_tree);

void FindOptimalMovesRec(SingleSourceMovesList * list, SingleSourceMovesList HelperList, SingleSourceMovesTreeNode * root, int max, int count, int * flag);

int getMaxCaptures(SingleSourceMovesTreeNode * root);

void copyList(SingleSourceMovesList * lst, SingleSourceMovesList * copy);

MultipleSourceMovesList *FindAllPossiblePlayerMoves(Board board, Player player);
