class Board {
	private:
		int dimension; // width & height
		int size; 
		vector<Piece> board;

	public:
		// constructor
		Board(){}
		Board(int D){
			dimension = D;
			size = D*D;
			board.resize(size);
			this->emptyBoard();						
		}
		// ---------------------------------------------------

		// setter and getter
		void setContent(vector<Piece> V) {
			this->board = V;
		}

		void setDimension(int D) {
			dimension = D;
			size = D*D;
		}

		int getSize() {
			return size;
		}

		int getDimension() {
			return dimension;
		}

		vector<Piece> getContent() {
			vector<Piece> V;

			V.resize(this->size);
			for (int i = 0; i < this->size; ++i)
			{
				V[i] = this->board[i];
			}
			return V;
		}

		// ---------------------------------------------------

		// other functions
		void emptyBoard(){
			Piece emptyPiece("___", 0);

			board.clear();
			for (int i = 0; i < this->size; i++)
				board[i] = emptyPiece;
		}

		void putPiece(Piece P, int X, int Y) {
			board[(this->dimension-Y)*this->dimension+(X-1)] = P;
		}

		// the view will messed up if theres more than 99 Queen pieces
		void showBoard() {
			for(int i = 0; i < this->size; i++) 
			{
				cout << setfill('_') << setw(3) << board[i].getName() << "|";
				if ((i+1)%this->dimension==0)
				{
					cout << "\n";
				}
			}
			cout << "\n";
		}

		void copyBoard(Board *B) {
			Board dummyBoard;

			*B = dummyBoard;
			B->setDimension(this->getDimension());
			B->setContent(this->getContent());
		}
};