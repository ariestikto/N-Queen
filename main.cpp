#include <iostream>		// IO functions (i.e. cin, cout)
#include <sstream>
#include <iomanip>
#include <string>		// string
#include <algorithm>    // random_shuffle
#include <cmath>        // abs
#include <array>		// array
#include <vector>		// vector

using namespace std;

#include "piece.h"
#include "board.h"
#include "helper.h"
#include "algorithm.h"

int main() {
	srand(time(0)); // seed random function

	for (int i = 0; i < 1; ++i)
	{
		Board B(5);
		Board B2;
		Board B3;
		generateState(&B);
		B.copyBoard(&B2);
		B.copyBoard(&B3);
		
		cout << "\n" << "Number " << i+1 << ". ===================" << endl;
		cout << "Attacking pairs: " << numAttackingPairs(&B) << endl;
		B.showBoard();
		
		HC(&B);
		SA(&B2);
		IMC(&B3);
	}

	return 0;
}