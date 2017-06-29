#include <stdafx.h>
#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

unsigned int check(unsigned int xthrow);
unsigned int take_players ();
map <int, string> TakeName ();
void WriteName ();

const unsigned int players=take_players();
  map<int, string> name;
  
int main()

{

  unsigned int throw1, throw2, spare, strike, oframe;

  int p = 0;
  name = TakeName();
  WriteName();
  

  cout << "\n \n PROGRAM ZLICZA PUNKTACJE GRY KREGLE \n";

  vector<int> points(players, 0);
  vector<int> bonus(players, 0);

  for (int i = 1; i < 11; i++) {
    cout << "\n RUNDA " << i << endl;
    for (p = 0; p < players; p++) {
      cout << "\n \n RZUCA \t \t" << name[p];
    begin:
      cout << "\n \n podaj liczbę wyrzuconych kręgli \t";
      cin >> throw1;
      throw1 = check(throw1);

      if (throw1 == 10) {
        cout << "STRIKE zdobyłeś \t" << throw1 << "\t punktów";

        points[p] += throw1;
        if (i > 1)  // naliczanie premii po pierwszym rzucie
        {
          if ((bonus[p] == 2) || (bonus[p] == 1))

            points[p] += throw1;

        }  // koniec naliczania premii po pierwszym rzucie

        bonus[p] = 2;
      } else {
        cout << "podaj liczbe wyrzuconych kregli w drugim rzucie \t";
        cin >> throw2;
        throw2 = check(throw2);

        if (i > 1)  // naliczanie premii po drugim  rzucie
        {
          if (bonus[p] == 2)
            if (throw1 == 10)
              points[p] += throw1 * 2;
            else
              points[p] += throw1 + throw2;
          else if (bonus[p] == 1)
            points[p] += throw1;
        }  // koniec naliczania premii po drugim rzucie

        if (throw1 + throw2 == 10) {
          spare = throw1 + throw2;
          cout << "SPARE zdobyłeś \t" << spare << "\t punktów ";
          points[p] += spare;
          bonus[p] = 1;
        } else {
          oframe = throw1 + throw2;
          if (oframe >= 10) {
            cout << "suma punktow z dwoch rzutow nie moze byc wieksza niz 10, "
                    "zacznij od nowa";
            goto begin;
          } else {
            cout << "OPEN FRAME zdobyłeś \t" << oframe << "\t punktów ";
            points[p] += oframe;
            bonus[p] = 0;
          }
        }
      }
    }

    cout << "\n \n \n PODSUMOWANIE \n\n";
    vector<int>::iterator see;
    p = 0;
    for (see = points.begin(); see != points.end(); ++see) {
      cout << name[p] << "\t" << *see << endl;
      p++;
    }

    /*				for (see = bonus.begin()+1; see !=bonus.end();
       ++see)
                           {

                                   cout<< name[p]<< "\t"<<*see<<endl;
                                   p++;
                           }   */
  }

  /*	 if (1<p<players)
                                                          {
                                                          if (bonus[p]==2)
                                                                  if
     (throw1==10)
                                                                  points[p]=points[p]+throw1*2;
                                                                  else
                                                                          points[p]=points[p]+throw1
     +throw2;
                                                          else
                                                                  if(bonus[p]==1)
                                                                  points[p]=points[p]+throw1;
                                                                  else
                                                                  points[p]=points[p];
                                                          }
                                          else
                                                  points[p]=points[p];


           */

  //////

  cin.get();
  cin.get();
  return 0;
}

unsigned int check(unsigned int xthrow)

{
  while (xthrow > 10)

  {
    cout << "nie umiesz BUCU policzyć do 10 \n sprobuj policzyć jeszcze raz "
            "wykorzystujac reszte mozgu \n";
    cin >> xthrow;
  }
  return xthrow;
}

unsigned int take_players ()
 {
		 
  cout<< " podaj liczbe graczy - MAX 10 \t";
  unsigned int xplayers;
  cin>> xplayers;
  xplayers = check (xplayers);
	 while (xplayers == 0)
	 {
	 cout<< "\n chyba nie trudno się domyslic, ze 0 nie gra w kregle, podaj liczbe wieksza od 0 i mniejsza od 10 POWODZENIA \n";
	 cin>>xplayers;
	}
	 xplayers = check (xplayers);
	
	 return xplayers;
	 }


map <int, string> TakeName ()
{
	int p=0;
	string player;
	 map<int, string> name;
  while (p < players)

  {
    cout << "podaj imię gracza numer " << p << "\t";

    cin >> player;
    name[p] = player;
    p++;
  }
return name;
}


void WriteName ()

{
	  cout << "\n \n oto lista graczy \n \n";
  int p = 0;
  while (p < players) 
  {
    cout << name[p] << "\n";
    p++;
  }

}
