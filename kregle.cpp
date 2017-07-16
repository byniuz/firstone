#include <stdafx.h>
#include <iostream>
#include <map>
#include <string>
#include <vector>
using namespace std;

class Bowles
{
public:

	bool CheckNumber(const unsigned int TestNumber) {

		return (TestNumber <= 10);
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
	const unsigned int players;
	vector<int> points;
	vector<int> bonus;
	Bowles() : players(take_players()), points(players, 0), bonus(players, 0) {}


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
	map<int, string> TakeName() {
		size_t p = 0;
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
		size_t p = 0;
		while (p < players) {
			cout << name[p] << "\n";
			p++;
		}
	}


	void Summary() {

		size_t p = 0;
		for (p = 0; p<players; p++) {
			cout << name[p] << "\t" << points[p] << endl;
		}
	}

	unsigned int throw1, throw2;
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



	void LastBonusThrows() {
		for (size_t p = 0; p < players; p++) {
			if (bonus[p] == 2) {
				cout << "\n" << name[p] << "\t Masz dodatkowe dwa rzuty \n podaj ile wyrzuciles w pierwszym "
					"rzucie: \t";
				throw1 = GetOneNumberAndCheckIt();
				if (throw1 == 10) {
					cout << "\n STRIKE";
					points[p] += throw1 * 2;
				}
				else {
					cout << "\n podaj ile wyrzuciłeś w drugim rzucie: \t";
					throw2 = GetOneNumberAndCheckIt();
					points[p] += throw1 + throw2;
				}
			}
			else if (bonus[p] == 1) {
				cout << "\n" << name[p] << "\t Masz dodatkowy rzut \n podaj ile wyrzuciles w pierwszym "
					"rzucie: \t";
				throw1 = GetOneNumberAndCheckIt();
				points[p] += throw1;
			}
		}
	}

};


int main()
{
	Bowles names;
	constexpr uint8_t ROUND_NUMBERS = 10;
	size_t p = 0;
	names.TakeName();
	names.WriteName();
	unsigned int spare, oframe;
	cout << "\n \n PROGRAM ZLICZA PUNKTACJE GRY KREGLE \n";

	for (int i = 1; i <= ROUND_NUMBERS; i++) {
		cout << "\n RUNDA " << i << endl;
		for (p = 0; p < names.players; p++) {
			
			cout << "\n \n RZUCA \t \t" << names.name[p];
		begin:
			cout << "\n \n podaj liczbę wyrzuconych kręgli \t";

			names.throw1 = names.GetOneNumberAndCheckIt();

			if (names.throw1 == 10) {
				cout << "STRIKE zdobyłeś \t" << names.throw1 << "\t punktów";

				names.points[p] += names.throw1;
				if (i > 1) names.points[p] = names.CheckBonus(p);
				names.bonus[p] = 2;
			}
			else {
				cout << "podaj liczbe wyrzuconych kregli w drugim rzucie \t";

				names.throw2 = names.GetOneNumberAndCheckIt();
				if (i > 1) names.points[p] = names.CheckBonus(p);

				if (names.throw1 + names.throw2 == 10) {
					spare = names.throw1 + names.throw2;
					cout << "SPARE zdobyłeś \t" << spare << "\t punktów ";
					names.points[p] += spare;
					names.bonus[p] = 1;
				}
				else {
					oframe = names.throw1 + names.throw2;
					if (oframe >= 10) {
						cout << "suma punktow z dwoch rzutow nie moze byc wieksza niz 10, "
							"zacznij od nowa";
					goto begin;
					}
					else {
						cout << "OPEN FRAME zdobyłeś \t" << oframe << "\t punktów ";
						names.points[p] += oframe;
						names.bonus[p] = 0;
					}
				}
			}
		}

		cout << "\n \n \n PODSUMOWANIE \n\n";
		names.Summary();
	}
	names.LastBonusThrows();

	cout << "\n \n \n PODSUMOWANIE FINAL\n\n";
	names.Summary();

	cin.get();
	cin.get();
	return 0;

}








