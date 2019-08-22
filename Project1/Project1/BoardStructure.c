#include "BoardStructure.h"
#include "InitialFunctions.h"

////////1.
SingleSourceMovesTree * FindSingleSourceMoves(Board board, checkersPos * src)
{
	SingleSourceMovesTree *movesTree = (SingleSourceMovesTree*)malloc(sizeof(SingleSourceMovesTree));
	checkMemoryAllocation(movesTree);
	allocateTree(movesTree);
	copyBoard(movesTree->source->board, board);
	int rowNum = src->row - 'A', colNum = src->col - '1';
	char player = board[rowNum][colNum];//which player are we with.
	
	switch (player) {
	case TOP:   //top player case.
		if (rowNum + 1 > 7) {
			return NULL;
			FreeTree(movesTree);
		}
		if ((colNum - 1 < 0 && board[rowNum + 1][colNum + 1] == TOP) || (colNum + 1 > 7 && board[rowNum + 1][colNum - 1] == TOP)) {// if we are at the edges and blocked
			return NULL;
			FreeTree(movesTree);
		}
		if (colNum - 1 < 0) {
			movesTree->source->pos->row = src->row;
			movesTree->source->pos->col = src->col;
			movesTree->source->next_move[0] = NULL;
		}
		else if (board[rowNum + 1][colNum - 1] != TOP) { //verify if its not the same player.
			if (board[rowNum + 1][colNum - 1] != EMPTY) //if its not empty,looking for capture moves chain.
			{
				CreateCaptureMovesRec(board, rowNum + 1, colNum - 1, &(movesTree->source->next_move[0]), TOP, -1, 2, 0);
				movesTree->source->pos->row = src->row;
				movesTree->source->pos->col = src->col;
			}
			else {
				copyBoard(movesTree->source->next_move[0]->board, board);
				movesTree->source->pos->row = src->row;
				movesTree->source->pos->col = src->col;
				movesTree->source->next_move[0]->pos->row = src->row + 1;
				movesTree->source->next_move[0]->pos->col = src->col - 1;
				movesTree->source->next_move[0]->total_captures_so_far = 0;

			}
		}
		else {
			movesTree->source->pos->row = src->row;
			movesTree->source->pos->col = src->col;
			movesTree->source->next_move[0] = NULL;
		}

		if (colNum + 1 > 7) {
			movesTree->source->pos->row = src->row;
			movesTree->source->pos->col = src->col;
			movesTree->source->next_move[1] = NULL;
		}
		else if (board[rowNum + 1][colNum + 1] != TOP) {
			if (board[rowNum + 1][colNum + 1] != EMPTY) {
				CreateCaptureMovesRec(board, rowNum + 1, colNum + 1, &(movesTree->source->next_move[1]), TOP, 1, 2, 0);
				movesTree->source->pos->row = src->row;
				movesTree->source->pos->col = src->col;
			}
			else {
				copyBoard(movesTree->source->next_move[1]->board, board);
				movesTree->source->pos->row = src->row;
				movesTree->source->pos->col = src->col;
				movesTree->source->next_move[1]->pos->row = src->row + 1;
				movesTree->source->next_move[1]->pos->col = src->col + 1;
				movesTree->source->next_move[1]->total_captures_so_far = 0;
			}
		}
		else {
			movesTree->source->pos->row = src->row;
			movesTree->source->pos->col = src->col;
			movesTree->source->next_move[1] = NULL;
		}
		if (board[rowNum + 1][colNum - 1] == TOP && board[rowNum + 1][colNum + 1] == TOP) {
			return NULL; //if the position is blocked by its own tools, return NULL.
			FreeTree(movesTree);
		}
		break;

///////

	case BOTTOM:   //bottom player case.
		if (rowNum - 1 < 0) {
			return NULL;
			FreeTree(movesTree);
		}
		if (colNum - 1 < 0 && board[rowNum - 1][colNum + 1] == BOTTOM || colNum + 1 > 7 && board[rowNum - 1][colNum - 1] == BOTTOM){ // if we are at the edges and blocked
			return NULL;
		FreeTree(movesTree);
	}
		if (colNum - 1 < 0) {
			movesTree->source->pos->row = src->row;
			movesTree->source->pos->col = src->col;
			movesTree->source->next_move[0] = NULL;
		}
		else if (board[rowNum - 1][colNum - 1] != BOTTOM) {
			if (board[rowNum - 1][colNum - 1] != EMPTY) //if its not empty,looking for capture moves chain.
			{
				CreateCaptureMovesRec(board, rowNum - 1, colNum - 1, &(movesTree->source->next_move[0]), BOTTOM, -1, 2, 0);
				movesTree->source->pos->row = src->row;
				movesTree->source->pos->col = src->col;
			}
			else {
				copyBoard(movesTree->source->next_move[0]->board, board);
				movesTree->source->pos->row = src->row;
				movesTree->source->pos->col = src->col;
				movesTree->source->next_move[0]->pos->row = src->row - 1;
				movesTree->source->next_move[0]->pos->col = src->col - 1;
				movesTree->source->next_move[0]->total_captures_so_far = 0;
			}
		}
		else {
			movesTree->source->pos->row = src->row;
			movesTree->source->pos->col = src->col;
			movesTree->source->next_move[0] = NULL;
		}
		
		if (colNum + 1 > 7) {
			movesTree->source->pos->row = src->row;
			movesTree->source->pos->col = src->col;
			movesTree->source->next_move[1] = NULL;
		}
		else if (board[rowNum - 1][colNum + 1] != BOTTOM) {
			if (board[rowNum - 1][colNum + 1] != EMPTY) {
				CreateCaptureMovesRec(board, rowNum - 1, colNum + 1, &(movesTree->source->next_move[1]), BOTTOM, 1, 2, 0);
				movesTree->source->pos->row = src->row;
				movesTree->source->pos->col = src->col;
			}
			else {
				copyBoard(movesTree->source->next_move[1]->board, board);
				movesTree->source->pos->row = src->row;
				movesTree->source->pos->col = src->col;
				movesTree->source->next_move[1]->pos->row = src->row - 1;
				movesTree->source->next_move[1]->pos->col = src->col + 1;
				movesTree->source->next_move[1]->total_captures_so_far = 0;
			}
		}
		else {
			movesTree->source->pos->row = src->row;
			movesTree->source->pos->col = src->col;
			movesTree->source->next_move[1] = NULL;
		}
		if (board[rowNum - 1][colNum - 1] == BOTTOM && board[rowNum - 1][colNum + 1] == BOTTOM) {
			return NULL; //if the position is blocked by its own tools, return NULL.
			FreeTree(movesTree);
		}
		break;
	
	}
	return movesTree;
}
/*The function checks whether or not the player can capture a cell and move on.
If can capture,it will update the moves. 
#count - indication for player state (1 if should meet the enemy,2 if needs an empty cell after capture)
#direction - the direction of the move the player made, for recursive use(-1 is left,1 is right).
*/
void CreateCaptureMovesRec(Board board, int row, int col, SingleSourceMovesTreeNode** root, char currPlayer,int direction,int count,unsigned short captures) {
	switch (currPlayer)
	{
	case TOP:
		if (count == 1 && (col >= 0 && col <= 7 && row <= 7 && board[row+1][col+direction] == BOTTOM)) { //if we have another enemy in the way, keep looking.
			CreateCaptureMovesRec(board, row + 1, col+direction, root, currPlayer,direction, count + 1, captures);
		}
		else if (count == 1 && ((col+direction < 0 || col+direction>7 || row + 1 > 7) || board[row+1][col+direction] != BOTTOM)) { //if we dont,stop here.
			(*root) = NULL;
			break;
		}
		else if (count==2 && ((col+direction<0 || col+direction>7 || row+1>7) || board[row+1][col+direction] != EMPTY)) { /*if we cant land on the cell
																														 ,cancel the capture move.*/
			(*root) = NULL;
			break;
		}
		else if (count == 2 && board[row+1][col+direction]==EMPTY) { //if we can land, capture and update information.
			(*root)->total_captures_so_far = captures+1;
			copyBoard((*root)->board, board);
			(*root)->next_move[0] = (SingleSourceMovesTreeNode*)malloc(sizeof(SingleSourceMovesTreeNode));
			(*root)->next_move[1] = (SingleSourceMovesTreeNode*)malloc(sizeof(SingleSourceMovesTreeNode));
			(*root)->next_move[0]->pos = (checkersPos*)(malloc(sizeof(checkersPos)));
			(*root)->next_move[1]->pos = (checkersPos*)(malloc(sizeof(checkersPos)));
			checkMemoryAllocation((*root)->next_move[0]);	checkMemoryAllocation((*root)->next_move[1]); 
			checkMemoryAllocation((*root)->next_move[0]->pos);	checkMemoryAllocation((*root)->next_move[1]->pos);
			(*root)->pos->row = row+1 + 'A';
			(*root)->pos->col = col+direction + '1';
			count = 0;
		CreateCaptureMovesRec(board, row + 1, col+direction, &(*root)->next_move[0], currPlayer,-1,count+1, captures + 1);
		CreateCaptureMovesRec(board, row + 1, col+direction, &(*root)->next_move[1], currPlayer,1,count+1, captures + 1);	
		}
	break;

	case BOTTOM:
		if (count == 1 && (col >= 0 && col <= 7 && row >= 0 && board[row-1][col+direction] == TOP)) {
			CreateCaptureMovesRec(board, row - 1, col + direction, root, currPlayer, direction,count+1, captures);
		}
		else if (count == 1 && ((col+direction < 0 || col+direction>7 || row - 1 < 0) || board[row-1][col+direction] != TOP)) {
			(*root) = NULL;
			break;
		}
		else if (count == 2 && ((col+direction < 0 || col+direction>7 || row -1 < 0) || board[row-1][col+direction] != EMPTY)) {
			(*root) = NULL;
			break;
		}
		else if (count == 2 && board[row-1][col+direction] == EMPTY){
				(*root)->total_captures_so_far = captures+1;
				copyBoard((*root)->board, board);
				(*root)->next_move[0] = (SingleSourceMovesTreeNode*)malloc(sizeof(SingleSourceMovesTreeNode));
				(*root)->next_move[1] = (SingleSourceMovesTreeNode*)malloc(sizeof(SingleSourceMovesTreeNode));
				(*root)->next_move[0]->pos = (checkersPos*)(malloc(sizeof(checkersPos)));
				(*root)->next_move[1]->pos = (checkersPos*)(malloc(sizeof(checkersPos)));
				(*root)->pos->row = row - 1 + 'A';
				(*root)->pos->col = col + direction + '1';
				count = 0;
		CreateCaptureMovesRec(board, row - 1, col+direction, &(*root)->next_move[0], currPlayer,-1,count+1,captures + 1);
		CreateCaptureMovesRec(board, row - 1, col+direction, &(*root)->next_move[1], currPlayer,1, count+1,captures + 1);
	}
	break;
	}
}

/////////2.
SingleSourceMovesList *FindSingleSourceOptimalMove(SingleSourceMovesTree *moves_tree) {
	int max, flag = 0;
	SingleSourceMovesList *moveList=(SingleSourceMovesList*) malloc(sizeof(SingleSourceMovesList));
	checkMemoryAllocation(moveList);
	SingleSourceMovesList temp;
	makeEmptyList(&temp);
	makeEmptyList(moveList);
	max = getMaxCaptures(moves_tree->source);
	FindOptimalMovesRec(moveList,temp, moves_tree->source, max, 0, &flag);
	return moveList;
}
void FindOptimalMovesRec(SingleSourceMovesList *list,SingleSourceMovesList HelperList, SingleSourceMovesTreeNode *root, int max, int count,int *flag) {
	SingleSourceMovesListCell *curr;
	if (root == NULL||*flag==1)
		return;
	else {
		curr = createNewCell(root->pos, root->total_captures_so_far, NULL);
		HelperList = insertNodeToEndList(HelperList, curr);
		if (count != 0) {
			if (curr->captures == max) { //we found the wanted route,copy the given list.
				copyList(list, &HelperList);
				*flag = 1;
				return;
			}
		}
		FindOptimalMovesRec(list,HelperList, root->next_move[0], max, count + 1, flag);
		FindOptimalMovesRec(list,HelperList, root->next_move[1], max, count + 1, flag);
	}
}
////////3.
MultipleSourceMovesList *FindAllPossiblePlayerMoves(Board board, Player player) {
	int i, j;
	MultipleSourceMovesListCell *curr = (MultipleSourceMovesListCell*)calloc(1, sizeof(MultipleSourceMovesListCell));
	MultipleSourceMovesList *AllMoves = (MultipleSourceMovesList*)calloc(1, sizeof(MultipleSourceMovesList));
	AllMoves->head = AllMoves->tail = NULL;
	SingleSourceMovesList *SingleMoves = (SingleSourceMovesList*)malloc(sizeof(SingleSourceMovesList));
	SingleSourceMovesTree *tr = (SingleSourceMovesTree*)malloc(sizeof(SingleSourceMovesTree));
	checkersPos *src= (checkersPos*)malloc(sizeof(checkersPos));
	checkMemoryAllocation(curr);	checkMemoryAllocation(AllMoves); 	checkMemoryAllocation(SingleMoves);
	checkMemoryAllocation(tr);	checkMemoryAllocation(src);

	for (i = 0; i < BOARD_SIZE; i++) {
		for (j = 0; j < BOARD_SIZE; j++) {
			if (player == board[i][j]) {
				src->row = i + 'A';
				src->col = j + '1';
				tr = FindSingleSourceMoves(board, src);
				
				if (tr != NULL) {
					allocateMultiListCell(curr);
					SingleMoves = FindSingleSourceOptimalMove(tr);
					if (SingleMoves->head != NULL) {
						curr->single_source_moves_list = SingleMoves;
						insertToListPointer2(AllMoves, curr);
					}
					curr = curr->next;
				}
			}
		}
	}
	if (AllMoves->head == NULL)
		return NULL;
	return AllMoves;
}
//////////4.
void Turn(Board board, Player player) {
	MultipleSourceMovesList *list = (MultipleSourceMovesList*)malloc(sizeof(MultipleSourceMovesList));
	SingleSourceMovesList *bestMove = (SingleSourceMovesList*)malloc(sizeof(SingleSourceMovesList));
	checkMemoryAllocation(list);	checkMemoryAllocation(bestMove);

	short max = -1;  //initializing to something lower than 0.
	list = FindAllPossiblePlayerMoves(board, player);
	getAndSetMaxCapturesList((list->head), &bestMove, &max);
	if (max > 0) {
		DeleteAndUpdateBoard(board, bestMove->head,max,player);
	}
	else {
		board[bestMove->head->position->row - 'A'][bestMove->head->position->col - '1'] = EMPTY;
		board[bestMove->tail->position->row - 'A'][bestMove->tail->position->col - '1'] = player;
	}
	switch (player) {
	case TOP:
		printf("player TOP_DOWN's turn\n%c%c -> %c%c\n", bestMove->head->position->row, bestMove->head->position->col,
			bestMove->tail->position->row, bestMove->tail->position->col);
		break;
	case BOTTOM:
		printf("player BOTTOM_UP's turn\n%c%c -> %c%c\n", bestMove->head->position->row, bestMove->head->position->col,
			bestMove->tail->position->row, bestMove->tail->position->col);
		break;
	}
	if(list!=NULL)
	freeMultipleList(list);
	return;
}
//deletes the captured cells from board and updates current positions recursively.
void DeleteAndUpdateBoard(Board board, SingleSourceMovesListCell *moves,int capture,Player player)
{
	int direction;
	int currColNum, currRowNum, nextColNum,nextRowNum;
	currColNum = moves->position->col - '1'; currRowNum = moves->position->row - 'A';
	if (capture == 0) {
		board[currRowNum][currColNum] = player;
		return;
	}
	else {
		nextColNum = moves->next->position->col - '1';
		nextRowNum = moves->next->position->row - 'A';
		board[currRowNum][currColNum] = EMPTY; //update current position, the player has moved.
		if (player == TOP) //check the direction of player(for row)
			direction = 1;
		else
			direction = -1;
		//finds the position of the captured cell by comparing the positions of the current Player
		if (currColNum < nextColNum) {
			board[currRowNum + direction][currColNum + 1] = EMPTY;
		}
		else if (currColNum > nextColNum) {
			board[currRowNum + direction][currColNum - 1] = EMPTY;
		}
		DeleteAndUpdateBoard(board, moves->next, capture - 1, player);
	}
}
//////////5.
void StoreBoard(Board board, char *filename) {
	unsigned short maskT = 1, maskB = 2;
	unsigned char cell;
	unsigned short rowToWrite;
	int i, j;
	FILE* f;
	f = fopen(filename, "wb");
	for (i = 0; i < BOARD_SIZE; i++) {
		if (i != 0)
			fwrite(&rowToWrite, sizeof(unsigned short), 1, f);
		rowToWrite = 0;

		for (j = 0; j < BOARD_SIZE; j++) {
			cell = board[i][j];
			switch (cell)
			{
			case TOP:
				rowToWrite |= (maskT << (16 - (j + 1) * 2));
				break;
			case BOTTOM:
				rowToWrite |= (maskB << (16 - (j + 1) * 2));
				break;
			}
		}
	}
	fwrite(&rowToWrite, sizeof(unsigned short), 1, f); //last row to write
	fclose(f);
}
//////////6.
void LoadBoard(char *filename, Board board) {
	FILE *f;
	f = fopen(filename, "rb");
	unsigned short mask = 0,bytes;
	int i,row=0,numOfBytes;
	numOfBytes = fseek(f, 0, SEEK_END);
	rewind(f);
	fread(&bytes, sizeof(unsigned short), 1, f);

	while (ftell(f) < numOfBytes) {
		for (i = 0; i < 16; i+=2) {
			bytes = bytes << i;
			bytes = bytes >> i;
			mask |= bytes >> (16 - i-2);
			switch (mask)
			{
			case 1:
				board[row][(i / 2)] = TOP;
				break;

			case 2:
				board[row][(i / 2)] = BOTTOM;
				break;
			case 0:
				board[row][(i / 2)] = EMPTY;
				break;
			}
			mask = 0;
		}
		fread(&bytes, sizeof(unsigned short), 1, f);
		row++;
		
	}
	fclose(f);
}
//////////7.
void PlayGame(Board board, Player starting_player) {
	char flag = FALSE;
	Player player = starting_player;
	Player winner;
	while (!flag) {
		printBoardPlatform(board);
		winner=checkForWinner(board, player);
		if (winner != 0) {
			flag = TRUE;
			switch (winner)
			{
			case TOP:
				printf("player TOP_DOWN has won.");
				break;
			
			case BOTTOM:
				printf("player BOTTOM_UP has won.");
				break;
		}
		}
		else {
			Turn(board, player);
			if (player == TOP)
				player = BOTTOM;
			else
			player = TOP;
		}

	}
	return;
}
//a function that checks whether a player won.
Player checkForWinner(Board board,Player player) {
	int i;
	MultipleSourceMovesList *list = (MultipleSourceMovesList*)malloc(sizeof(MultipleSourceMovesList));
	checkMemoryAllocation(list);
	list = FindAllPossiblePlayerMoves(board, player);
	if (list == NULL) {
		if (player == TOP)
			return BOTTOM;
		return TOP;
	}
	else {
		for (i = 0; i < BOARD_SIZE; i++) {
			if (board[0][i] == BOTTOM)
				return BOTTOM;
			else if (board[7][i] == TOP)
				return TOP;
		}
		freeMultipleList(list);
		return 0;
	}
}
void getAndSetMaxCapturesList(MultipleSourceMovesListCell * src, SingleSourceMovesList ** bestMove, short *max) {
	if (src->single_source_moves_list == NULL|| src->single_source_moves_list->head==NULL)
		return;
	else if (src->single_source_moves_list->tail->captures > *max) {
		*max = src->single_source_moves_list->tail->captures;
		*bestMove = src->single_source_moves_list;
	}
	getAndSetMaxCapturesList(src->next, bestMove, max);
}
int getMaxCaptures(SingleSourceMovesTreeNode *root) {
	if (root == NULL)
		return 0;
	else if (root->next_move[0] == NULL && root->next_move[1] == NULL)
		return root->total_captures_so_far;
	return max(getMaxCaptures(root->next_move[0]), getMaxCaptures(root->next_move[1]));
}

void copyList(SingleSourceMovesList* lst, SingleSourceMovesList *copy) {
	SingleSourceMovesListCell *temp = copy->head;
	while (temp) {
		insertToListPointer1(lst, temp);
		temp = temp->next;
	}
}
void InitializeBoard(Board* board) {
	(*board)[0][0] = EMPTY; (*board)[0][1] = TOP; (*board)[0][2] = EMPTY; (*board)[0][3] = TOP;
	(*board)[0][4] = EMPTY; (*board)[0][5] = TOP; (*board)[0][6] = EMPTY; (*board)[0][7] = TOP;
	//
	(*board)[1][0] = TOP; (*board)[1][1] = EMPTY; (*board)[1][2] = TOP; (*board)[1][3] = EMPTY;
	(*board)[1][4] = TOP; (*board)[1][5] = EMPTY; (*board)[1][6] = TOP; (*board)[1][7] = EMPTY;
	//
	(*board)[2][0] = EMPTY; (*board)[2][1] = TOP; (*board)[2][2] = EMPTY; (*board)[2][3] = TOP;
	(*board)[2][4] = EMPTY; (*board)[2][5] = TOP; (*board)[2][6] = EMPTY; (*board)[2][7] = TOP;
	//
	(*board)[3][0] = EMPTY; (*board)[3][1] = EMPTY; (*board)[3][2] = EMPTY; (*board)[3][3] = EMPTY;
	(*board)[3][4] = EMPTY; (*board)[3][5] = EMPTY; (*board)[3][6] = EMPTY; (*board)[3][7] = EMPTY;
	//
	(*board)[4][0] = EMPTY; (*board)[4][1] = EMPTY; (*board)[4][2] = EMPTY; (*board)[4][3] = EMPTY;
	(*board)[4][4] = EMPTY; (*board)[4][5] = EMPTY; (*board)[4][6] = EMPTY; (*board)[4][7] = EMPTY;
	//
	(*board)[5][0] = BOTTOM; (*board)[5][1] = EMPTY; (*board)[5][2] = BOTTOM; (*board)[5][3] = EMPTY;
	(*board)[5][4] = BOTTOM; (*board)[5][5] = EMPTY; (*board)[5][6] = BOTTOM; (*board)[5][7] = EMPTY;
	//
	(*board)[6][0] = EMPTY; (*board)[6][1] = BOTTOM; (*board)[6][2] = EMPTY; (*board)[6][3] = BOTTOM;
	(*board)[6][4] = EMPTY; (*board)[6][5] = BOTTOM; (*board)[6][6] = EMPTY; (*board)[6][7] = BOTTOM;
	//
	(*board)[7][0] = BOTTOM; (*board)[7][1] = EMPTY; (*board)[7][2] = BOTTOM; (*board)[7][3] = EMPTY;
	(*board)[7][4] = BOTTOM; (*board)[7][5] = EMPTY; (*board)[7][6] = BOTTOM; (*board)[7][7] = EMPTY;
}
void printBoardPlatform(Board board) {
	int y,j;
	char rowIndex;
	printf("\n");
	printf("    ");
	for (y = 1; y <= 8; y++) {
		printf("|%d", y);
	}
	printf("|");
	printf("\n");
	printf("    ");
	for (y = 1; y <= 8; y++) {
		printf("%1s", "+-");
	}
	printf("%s", "+");
	printf("\n");
	for (rowIndex = 'A'; rowIndex <= 'H'; rowIndex++) {
		printf(" |%1c |", rowIndex);
			for (j = 0; j < BOARD_SIZE; j++) {
				printf("%1c|", board[rowIndex-ROW_INDEX][j]);
			}
			printf("\n");
			
		}
	printf("    ");
	for (y = 1; y <= 8; y++) {
		printf("%1s", "+-");
	}
	printf("%s", "+");
	printf("\n\n");
	}
