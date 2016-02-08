// check index of piece
// I: *Board, piece
// O: Index
int findTile(Board *B, Piece P) {
    for (int i = 0; i < B->getSize(); ++i)
    {
        if (P.isEqual(&B->getContent()[i]))
        {
            return i;
            break;
        }
    }
    return 0;
}

// convert index to coordinate in board
// I: *Board, Index, Output Code (1:X, 2:Y)
// O: Position
int indexToCoor(Board *B, int I, int O) {
	switch(O) {
        case 1: 
            return (I%B->getDimension())+1;
            break;
        case 2:
            return B->getDimension()-(I/B->getDimension());
            break; 
    }
}

// check queen position in board
// I: *Board, Piece, Output Code (1:X, 2:Y)
// O: Position
int tilePosition(Board *B, Piece P, int O) {
	return indexToCoor(B, findTile(B, P), O);
}

// calculate number of attacking pair of queens directly or indirectly
// I: Board
// O: int
int numAttackingPairs(Board *B) {
	Piece emptyPiece("___", 0);
	vector<Piece> V(B->getDimension());
	int attack = 0, posX = 0, posY = 0, q = 0;

	for (int i = 0; i < B->getSize(); ++i)
	{
		if (!B->getContent()[i].isEqual(&emptyPiece))
		{
			V[q] = B->getContent()[i];
			q++;
		}
	}

	for (int i = 0; i < V.size()-1; ++i)
	{
		posX = tilePosition(B, V[i], 1);
		posY = tilePosition(B, V[i], 2);
		for (int j = i+1; j < V.size(); ++j)
		{
			// horizontal attack
			if (posX == tilePosition(B, V[j], 1))
				attack++;
			// vertical attack
			if (posY == tilePosition(B, V[j], 2))
				attack++;
			// diagonal attack
			if (abs(posX-tilePosition(B, V[j], 1)) == abs(posY-tilePosition(B, V[j], 2)))
				attack++;
		}
	}
	return attack;
}

// handle queen move
void moveQueen(Board *B, Piece P, int newX, int newY) {
	Piece emptyPiece("___", 0);
	Piece temp;

	B->putPiece(emptyPiece, tilePosition(B, P, 1), tilePosition(B, P, 2));
	B->putPiece(P, newX, newY);
}

// generate random board
void generateState(Board *B) {
	Piece emptyPiece("___", 0);
	int genX = 0, genY = 0;

	B->emptyBoard();
	for (int i = 0; i < B->getDimension(); ++i)
	{
		Piece Q("Q"+to_string(i+1), i+1);
		do
		{
			genX = rand() % B->getDimension() + 1;
			genY = rand() % B->getDimension() + 1;	
		} while (!B->getContent()[(B->getDimension()-genY)*B->getDimension()+(genX-1)].isEqual(&emptyPiece) && genX != 0 && genY != 0);
		B->putPiece(Q, genX, genY);
	}
}

// calculate number of attack made by that piece directly or indirectly
int numAttack(Board *B, Piece P) {
	Piece emptyPiece("___", 0);
	vector<Piece> V;
	int attack = 0, posX = 0, posY = 0;

	for (int i = 0; i < B->getSize(); ++i)
	{
		if (!B->getContent()[i].isEqual(&emptyPiece) && !B->getContent()[i].isEqual(&P))
		{
			V.push_back(B->getContent()[i]);
		}
	}

	posX = tilePosition(B, P, 1);
	posY = tilePosition(B, P, 2);
	for (int i = 0; i < V.size(); ++i)
	{
		// horizontal attack
		if (posX == tilePosition(B, V[i], 1))
			attack++;
		// vertical attack
		if (posY == tilePosition(B, V[i], 2))
			attack++;
		// diagonal attack
		if (abs(posX-tilePosition(B, V[i], 1)) == abs(posY-tilePosition(B, V[i], 2)))
			attack++;
	}
	return attack;	
}

// check possible move from that piece
vector<pair<int, int>> generateMove(Board *B, Piece P) {
	Piece emptyPiece("___", 0);
	int j;
	int posX = tilePosition(B, P, 1);
	int posY = tilePosition(B, P, 2);
	vector<pair<int, int>> movePos;
	vector<pair<int, int>> queenPos;

	// cout << "(" << posX << ", " << posY << ") - " << numAttack(B, P) << endl;
	for (int i = 0; i < B->getSize(); ++i)
	{
		if (!B->getContent()[i].isEqual(&emptyPiece))
		{
			queenPos.push_back(make_pair(indexToCoor(B, i, 1), indexToCoor(B, i, 2)));
		}
	}

	// check up
	for (int i = posY+1; i < B->getDimension()+1; ++i)
	{
		if (find(queenPos.begin(), queenPos.end(), make_pair(posX, i)) == queenPos.end())
		{
			movePos.push_back(make_pair(posX, i));
		} else {
			break;
		}
	}
	// check down
	for (int i = posY-1; i > 0; --i)
	{
		if (find(queenPos.begin(), queenPos.end(), make_pair(posX, i)) == queenPos.end())
		{
			movePos.push_back(make_pair(posX, i));
		} else {
			break;
		}
	}
	// check right
	for (int i = posX+1; i < B->getDimension()+1; ++i)
	{
		if (find(queenPos.begin(), queenPos.end(), make_pair(i, posY)) == queenPos.end())
		{
			movePos.push_back(make_pair(i, posY));
		} else {
			break;
		}
	}
	// check left
	for (int i = posX-1; i > 0; --i)
	{
		if (find(queenPos.begin(), queenPos.end(), make_pair(i, posY)) == queenPos.end())
		{
			movePos.push_back(make_pair(i, posY));
		} else {
			break;
		}
	}
	// check up right
	j = 1;
	for (int i = posX+1; i < B->getDimension()+1; ++i)
	{
		if (posY+j < B->getDimension()+1)
		{
			if (find(queenPos.begin(), queenPos.end(), make_pair(i, posY+j)) == queenPos.end())
			{
				movePos.push_back(make_pair(i, posY+j));
			} else {
				break;
			}
		}
		j++;
	}
	// check down right
	j = 1;
	for (int i = posX+1; i < B->getDimension()+1; ++i)
	{
		if (posY-j > 0)
		{
			if (find(queenPos.begin(), queenPos.end(), make_pair(i, posY-j)) == queenPos.end())
			{
				movePos.push_back(make_pair(i, posY-j));
			} else {
				break;
			}
		}
		j++;
	}
	// check down left
	j = 1;
	for (int i = posX-1; i > 0; --i)
	{
		if (posY-j > 0)
		{
			if (find(queenPos.begin(), queenPos.end(), make_pair(i, posY-j)) == queenPos.end())
			{
				movePos.push_back(make_pair(i, posY-j));
			} else {
				break;
			}
		}
		j++;
	}
	// check up left
	j = 1;
	for (int i = posX-1; i > 0; --i)
	{
		if (posY+j < B->getDimension()+1)
		{
			if (find(queenPos.begin(), queenPos.end(), make_pair(i, posY+j)) == queenPos.end())
			{
				movePos.push_back(make_pair(i, posY+j));
			} else {
				break;
			}
		}
		j++;
	}

	return movePos;
}