#include <stdafx.h>
#include <iostream>
#include <map>
#include <string>
#include <vector>
using namespace std;

class Bowles
{
public:
	Bowles() : players(take_players()), points(players, 0), bonus(players, 0) {}

	bool CheckNumber(const unsigned int TestNumber) const {
		// modyfikator const przy funkcji mowi ze funkcja jest stala, czyli nie zmieni zadnego pola w klasie
		// i korzysta tylko ze stałych funkcji
		return (TestNumber <= 10);
	}

	unsigned int GetOneNumberAndCheckIt() const {
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


	unsigned int take_players() {
		cout << " podaj liczbe graczy - MAX 10 \t";

		unsigned int xplayers = GetOneNumberAndCheckIt();
		while (xplayers == 0) {
			cout << "\n chyba nie trudno się domyslic, ze 0 nie gra w kregle, podaj "
				"liczbe wieksza od 0 i mniejsza od 10 POWODZENIA \n";
			xplayers = GetOneNumberAndCheckIt();
		}


		return xplayers;
	}
	unsigned int ChangePlayers(unsigned int change)
	{
		change = players;
		return (change);
	}
	void TakeName() {
		size_t p = 0;
		string player;
		while (p < players)

		{
			cout << "podaj imię gracza numer " << p + 1 << "\t";
			cin >> player;
			name[p++] = player;
		}
	}

	void WriteName() const
	{
		cout << "\n \n oto lista graczy \n \n";
		for (auto& oneName : name)
			std::cout << oneName.second << std::endl;
	}


	void Summary() {
		for (size_t p = 0; p<players; p++) {
			cout << name[p] << "\t" << points[p] << endl;
		}
	}

	unsigned int CheckBonus(const size_t bonusIndex) {
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

	void GetPoints(size_t p)


	{

		cout << "\n \n RZUCA \t \t" << name[p];
		cout << "\n \n podaj liczbę wyrzuconych kręgli \t";

		throw1 = GetOneNumberAndCheckIt();

		if (throw1 == 10) {
			cout << "STRIKE zdobyłeś \t" << throw1 << "\t punktów";

			points[p] += throw1;
			points[p] = CheckBonus(p);
			bonus[p] = 2;
		}
		else {
			cout << "podaj liczbe wyrzuconych kregli w drugim rzucie \t";

			throw2 = GetOneNumberAndCheckIt();
			points[p] = CheckBonus(p);

			if (throw1 + throw2 == 10) {
				spare = throw1 + throw2;
				cout << "SPARE zdobyłeś \t" << spare << "\t punktów ";
				points[p] += spare;
				bonus[p] = 1;
			}
			else {
				oframe = throw1 + throw2;
				if (oframe <= 10) {
					cout << "OPEN FRAME zdobyłeś \t" << oframe << "\t punktów ";
					points[p] += oframe;
					bonus[p] = 0;
				}
				else {
					cout << "suma punktow z dwoch rzutow nie moze byc wieksza niz 10, "
						"zacznij od nowa";
					GetPoints(p);
				}
			}
		}
	}





private:
	unsigned int throw1, throw2, spare, oframe;
	const unsigned int players;
	vector<unsigned int> points;
	vector<unsigned int> bonus;
	map<unsigned int, string> name;

};


int main()
{
	Bowles names;
	constexpr uint8_t ROUND_NUMBERS = 10;
	size_t p = 0;
	names.TakeName();
	names.WriteName();
	unsigned int PlayersNumber = 0;
		PlayersNumber = names.ChangePlayers(PlayersNumber);
	cout << "\n \n PROGRAM ZLICZA PUNKTACJE GRY KREGLE \n";

	for (int i = 1; i <= ROUND_NUMBERS; i++) {
		cout << "\n RUNDA " << i << endl;
		for (p = 0; p < PlayersNumber; p++) {

			names.GetPoints(p);
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