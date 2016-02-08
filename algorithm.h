// HILL CLIMBER
void HC(Board *B) {
	Piece emptyPiece("___", 0);
	vector<Piece> V;
	vector<pair<int, int>> M;
	int iteration = 1;
	int violation = numAttackingPairs(B);
	int attack = 0;
	int piece, move; 

	// store all queens in board
	for (int i = 0; i < B->getSize(); ++i)
	{
		if (!B->getContent()[i].isEqual(&emptyPiece))
		{
			V.push_back(B->getContent()[i]);
		}
	}

	while(numAttackingPairs(B) > 0 && iteration < 15000)	
	{
		
		Board dummyBoard;			
		B->copyBoard(&dummyBoard);

		piece = rand() / (RAND_MAX / V.size() + 1);
		M = generateMove(B, V[piece]);
		move = rand() / (RAND_MAX / M.size() + 1);

		moveQueen(&dummyBoard, V[piece], get<0>(M[move]), get<1>(M[move]));
		attack = numAttackingPairs(&dummyBoard);

		if (violation >= attack)
		{
			dummyBoard.copyBoard(B);
			violation = attack;
		}
		iteration++;
		cout << "(HC) Iteration number: " << iteration << endl;
		B->showBoard();
	}
}

// SIMULATED ANNEALING
void SA(Board *B) {
	Piece emptyPiece("___", 0);
	vector<Piece> V;
	vector<pair<int, int>> M;
	int iteration = 1;
	int violation = numAttackingPairs(B);
	int attack = 0;
	int L = B->getDimension();
	int piece = 0;
	int move = 0;
	long double c = B->getDimension()-1;
	long double prob;
	long double accepted;

	// store all queens in board
	for (int i = 0; i < B->getSize(); ++i)
	{
		if (!B->getContent()[i].isEqual(&emptyPiece))
		{
			V.push_back(B->getContent()[i]);
		}
	}

	while(numAttackingPairs(B) > 0 && iteration < 10000)	
	{
		for (int i = 0; i < L; ++i)
		{
			Board dummyBoard;
			
			B->copyBoard(&dummyBoard);
			piece = rand() / (RAND_MAX / V.size() + 1);
			M = generateMove(B, V[piece]);
			move = rand() / (RAND_MAX / M.size() + 1);

			moveQueen(&dummyBoard, V[piece], get<0>(M[move]), get<1>(M[move]));
			attack = numAttackingPairs(&dummyBoard);

			prob = (double)rand()/(RAND_MAX);
			accepted = (long double)exp((violation-attack)/c);
			if (violation >= attack)
			{
				dummyBoard.copyBoard(B);
				violation = attack;
			} else if (prob < accepted)
			{
				cout << "prob: " << prob << ", accepted: " << accepted << endl;
				dummyBoard.copyBoard(B);
				violation = attack;
			}

			cout << "(SA) Iteration number: " << iteration << endl;
			B->showBoard();
		}
		c = c*0.95;
		iteration++;
	}
}

// ITERATIVE MIN CONFLICTS
void IMC(Board *B) {
	Piece emptyPiece("___", 0);
	vector<Piece> V;
	vector<pair<int, int>> M;
	int ranIndex;
	int violation = 9999;
	int moveX = 0, moveY = 0;
	int iteration = 1;
	int attack = 0;

	// store all queens in board
	for (int i = 0; i < B->getSize(); ++i)
	{
		if (!B->getContent()[i].isEqual(&emptyPiece))
		{
			V.push_back(B->getContent()[i]);
		}
	}

	while(numAttackingPairs(B) > 0 && iteration < 1000)	
	{
		violation = 9999;
		moveX = 0;
		moveY = 0;
		// choose random queen
		do
		{
			ranIndex = rand() / (RAND_MAX / B->getDimension() + 1);

		} while ( numAttack(B, V[ranIndex]) < 1);

		M = generateMove(B, V[ranIndex]);

		// cout << V[ranIndex].getName() << endl;
		for (int i = 0; i < M.size(); ++i)
		{
			Board dummyBoard;

			B->copyBoard(&dummyBoard);
			moveQueen(&dummyBoard, V[ranIndex], get<0>(M[i]), get<1>(M[i]));
			attack = numAttackingPairs(&dummyBoard);
			if (violation >= attack)
			{
				violation = attack;
				moveX = get<0>(M[i]);
				moveY = get<1>(M[i]);
			}
		}
		moveQueen(B, V[ranIndex], moveX, moveY);

		iteration++;
		cout << "(IMC) Iteration number: " << iteration << endl;
		B->showBoard();
	}
}
