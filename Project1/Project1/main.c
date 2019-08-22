
#include "BoardStructure.h"

int main() {
	Board board;
	InitializeBoard(&board);
	/*FindAllPossiblePlayerMoves(board, TOP);
	Turn(board, TOP);*/
	PlayGame(board, 'T');
	/*StoreBoard(board, "boardData");hjn
	LoadBoard("boardData", board);*/
	//int a= recExample(3, 3, 0);
	system("pause");
	return 0;
}