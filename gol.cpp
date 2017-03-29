#include <string>
#include <fstream>
#include <iostream>
#include <unistd.h>
using namespace std;
int cykle = 50;
#ifndef SZER
#define SZER 20
#endif
#ifndef WYS
#define WYS 12
#endif
int main(){
	fstream plik("generation.txt",fstream::in);
	int offX[8] = {0, 1, 1, 1, 0, -1, -1, -1};
	int offY[8] = {-1, -1, 0, 1, 1, 1, 0, -1};
	char p[WYS][SZER];
	int s[WYS][SZER];
	string temp;
	for(int y=0; y<WYS; y++) {
		plik >> temp;
		for(int x=0; x<SZER; x++) {
			p[y][x] = temp[x];
		}
	}
	for(int c=1; /*c<=cykle*/; c++) {
		cout << "\033[2J\033[1;1H";
		cout << c << endl;
		//OBLICZ SĄSIADÓW
		for(int y=0; y<WYS; y++) {
			for(int x=0; x<SZER; x++) {
				int sasiedzi = 0;
				// if(p[y][x] == 'X'){
				for(int o=0; o<8; o++) {
					int xx, yy;
					if(x+offX[o] == SZER) {
						xx = 0;
					}else if(x+offX[o] < 0) {
						xx = SZER-1;
					}else xx = x+offX[o];

					if(y+offY[o] == WYS) {
						yy = 0;
					}else if(y+offY[o] < 0) {
						yy = WYS-1;
					}else yy = y+offY[o];
					if(p[yy][xx] == 'X') sasiedzi++;
				}
				// }
				s[y][x] = sasiedzi;
			}
		}
		//WYŚWIETL
		cout << "  12345678901234567890" << endl << endl;

		for(int y=0; y<WYS; y++) {
			cout << (y+1)%10 << " ";
			for(int x=0; x<SZER; x++) {
				cout << p[y][x];
			}
			cout << endl;
		}
		//KOLEJNE POKOLENIE
		for(int y=0; y<WYS; y++) {
			for(int x=0; x<SZER; x++) {
				if(p[y][x] == 'X' && (s[y][x] == 2 || s[y][x] == 3)) {
					p[y][x] = 'X';
				}else if(p[y][x] == '.' && s[y][x] == 3) p[y][x] = 'X';
				else p[y][x] = '.';
			}
		}
		// cout << endl;
		// cout << "  12345678901234567890" << endl << endl;
		// for(int y=0; y<WYS; y++) {
		// 	cout << (y+1)%10  << " ";
		// 	for(int x=0; x<SZER; x++) {
		// 		cout << s[y][x];
		// 		s[y][x] = 0;
		// 	}
		// 	cout << endl;
		// }
		char hold=getchar();
		if(c+1 == cykle) std::cout << "KONIEC" << '\n';
	}
	plik.close();
	return 0;
}
