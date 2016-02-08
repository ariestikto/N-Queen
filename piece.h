class Piece {
	private:
		string name;
		int ID;

	public:
		// constructor
		Piece(){}
		Piece(string N, int id) {
			ID = id;
			name = N;
		}
		// ---------------------------------------------------

		// setter and getter
		void setName(string N) {
			name = N;
		}
		
		string getName() {
			return name;
		}
		
		// ---------------------------------------------------

		// other functions
		bool isEqual(Piece *P) {
			return (this->ID == P->ID);
		}
};
