#include <stdafx.h>
#include <iostream>
#include <map>
#include <string>
#include <vector>
using namespace std;

class PlayerName
{
public:

	bool CheckNumber(unsigned int TestNumber) {

		bool check = (TestNumber <= 10);

		return check;
	}
	unsigned int GetOneNumberAndCheckIt() {
		unsigned int xthrow;
		cin >> xthrow;
		while (!CheckNumber(xthrow))
		{
			cout << "nie umiesz BUCU policzyć do 10 \n sprobuj policzyć jeszcze raz "
				"wykorzystujac reszte mozgu \n";
			cin >> xthrow;
		}
		return xthrow;
	}

	const unsigned int players = take_players();

	unsigned int take_players() {
		cout << " podaj liczbe graczy - MAX 10 \t";

		unsigned int xplayers;
		xplayers = GetOneNumberAndCheckIt();
		while (xplayers == 0) {
			cout << "\n chyba nie trudno się domyslic, ze 0 nie gra w kregle, podaj "
				"liczbe wieksza od 0 i mniejsza od 10 POWODZENIA \n";
			xplayers = GetOneNumberAndCheckIt();
		}


		return xplayers;
	}

	map<int, string> name;
	map<int, string> TakeName(unsigned int p) {
		
		string player;
		while (p < players)

		{
			p++;
			cout << "podaj imię gracza numer " << p << "\t";
			p--;
			cin >> player;
			name[p] = player;
			p++;
		}
		return name;
	}

	void WriteName()

	{
		cout << "\n \n oto lista graczy \n \n";
		unsigned int p = 0;
			while (p < players) {
			cout << name[p] << "\n";
			p++;
		}
	}


};



unsigned int CheckBonus(size_t bonusIndex);
void LastBonusThrows(PlayerName names);



vector<int> points(10, 0);
vector<int> bonus(10, 0);

unsigned int throw1, throw2, spare, strike, oframe;




void Summary(PlayerName names) {
	
	size_t p = 0;
	for (p=0; p<names.players; p++) {
		cout << names.name[p] << "\t" << points[p]<< endl;
			}
}

int main()
{
	PlayerName names;
	constexpr uint8_t ROUND_NUMBERS = 10;
	size_t p = 0;
	names.TakeName(p);
	names.WriteName();

	cout << "\n \n PROGRAM ZLICZA PUNKTACJE GRY KREGLE \n";

	for (int i = 1; i <= ROUND_NUMBERS; i++) {
		cout << "\n RUNDA " << i << endl;
		for (p = 0; p < names.players; p++) {
			cout << "\n \n RZUCA \t \t" << names.name[p];
		begin:
			cout << "\n \n podaj liczbę wyrzuconych kręgli \t";
			
			throw1 = names.GetOneNumberAndCheckIt();

			if (throw1 == 10) {
				cout << "STRIKE zdobyłeś \t" << throw1 << "\t punktów";

				points[p] += throw1;
				if (i > 1) points[p] = CheckBonus(p);
				bonus[p] = 2;
			}
			else {
				cout << "podaj liczbe wyrzuconych kregli w drugim rzucie \t";
				
				throw2 = names.GetOneNumberAndCheckIt();
				if (i > 1) points[p] = CheckBonus(p);

				if (throw1 + throw2 == 10) {
					spare = throw1 + throw2;
					cout << "SPARE zdobyłeś \t" << spare << "\t punktów ";
					points[p] += spare;
					bonus[p] = 1;
				}
				else {
					oframe = throw1 + throw2;
					if (oframe >= 10) {
						cout << "suma punktow z dwoch rzutow nie moze byc wieksza niz 10, "
							"zacznij od nowa";
						goto begin;
					}
					else {
						cout << "OPEN FRAME zdobyłeś \t" << oframe << "\t punktów ";
						points[p] += oframe;
						bonus[p] = 0;
					}
				}
			}
		}

		cout << "\n \n \n PODSUMOWANIE \n\n";
		Summary(names);
	}
	LastBonusThrows(names);

	cout << "\n \n \n PODSUMOWANIE FINAL\n\n";
	Summary(names);

	cin.get();
	cin.get();
	return 0;

}





unsigned int CheckBonus(size_t bonusIndex) {
	//  bonus counting - start

	if (bonus[bonusIndex] == 2) {
		if (throw1 == 10)
			points[bonusIndex] += throw1;
		else
			points[bonusIndex] += throw1 + throw2;
	}
	else if (bonus[bonusIndex] == 1)
		points[bonusIndex] += throw1;
	// bonus counting - end
	return points[bonusIndex];
}

void LastBonusThrows(PlayerName names) {
	for (size_t p = 0; p < names.players; p++) {
		if (bonus[p] == 2) {
			cout << "\n"<<names.name[p]<< "\t Masz dodatkowe dwa rzuty \n podaj ile wyrzuciles w pierwszym "
				"rzucie: \t";
			throw1 = names.GetOneNumberAndCheckIt();
			if (throw1 == 10) {
				cout << "\n STRIKE";
				points[p] += throw1 * 2;
			}
			else {
				cout << "\n podaj ile wyrzuciłeś w drugim rzucie: \t";
				throw2 = names.GetOneNumberAndCheckIt();
				points[p] += throw1 + throw2;
			}
		}
		else if (bonus[p] == 1) {
			cout << "\n"<<names.name[p]<< "\t Masz dodatkowy rzut \n podaj ile wyrzuciles w pierwszym "
				"rzucie: \t";
			throw1 = names.GetOneNumberAndCheckIt();
			points[p] += throw1;
		}
	}
}
