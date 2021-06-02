#include <iostream>
#include "Board.h"
#include <stdio.h>
#include <conio.h>

int main() {


	Board brd;

	const char fen[] = { "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR " };

	std::string pos;
	brd.Init(fen);
	while (true) {	
		try {
			system("CLS");
			brd.Draw();
			std::cin >> pos;
			const char* p = pos.c_str();
			brd.Move(p);
		}
		catch(std::string s){
			std::cout << s <<"\n";
			_getch();
		}
 	//	getchar();
		
	}

	
	//brd.Show();
	
}