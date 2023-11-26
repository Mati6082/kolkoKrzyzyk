#include <iostream>
#include <vector>
#include <ctime>

using namespace std;

class Gra {
public:
    vector<int> plansza{0, 0, 0, 0, 0, 0, 0, 0, 0};
    bool winner;
    int wart = -1;

    void wyswietlNrPol() {
        cout << "Numery pol:\n";
        for (int i = 0; i < plansza.size(); i++) {
            cout << i+1 << " ";
            if ((i+1) % 3 == 0 && i != 0) cout << endl;
        }
    }

    void wyswietl() {
        cout << "Plansza:\n";
        for (int i = 0; i < plansza.size(); i++) {
            if (i % 3 == 0 && i != 0) cout << endl;
            if (plansza[i] == 1) cout << "X ";
            else if (plansza[i] == -1) cout << "O ";
            else cout << "- ";
        } cout << endl;
    }

    bool sprawdz() {
        int suma;
        for (int i = 0; i < 3; i++) {
            suma = plansza[i] + plansza[i + 3] + plansza[i + 6];
            if (suma == 3) {
                winner = true;
                return true;
            } else if (suma == -3) {
                winner = false;
                return true;
            }
        }
        for (int i = 0; i < 9; i+=3) {
            suma = plansza[i] + plansza[i + 1] + plansza[i + 2];
            if (suma == 3) {
                winner = true;
                return true;
            } else if (suma == -3) {
                winner = false;
                return true;
            }
        }
        suma = plansza[0] + plansza[4] + plansza[8];
        if (suma == 3) {
            winner = true;
            return true;
        } else if (suma == -3) {
            winner = false;
            return true;
        }
        suma = plansza[2] + plansza[4] + plansza[6];
        if (suma == 3) {
            winner = true;
            return true;
        } else if (suma == -3) {
            winner = false;
            return true;
        }
        return false;
    }

    bool czyPusta() {
        for (int el: plansza)
            if (el == 0)
                return false;
        return true;
    }

    bool end() {
        return sprawdz() || czyPusta();
    }

    void ruch() {
        int ruchBota = rand() % 10;
        while (plansza[ruchBota] != 0) {
            ruchBota = rand() % 10;
        }
        plansza[ruchBota] = wart;
    }
};

class Gracz {
public:
    int wart = 1;
    int pole;
    Gra game;

    void ruch() {
        game.wyswietlNrPol();
        game.wyswietl();
        cout << "Podaj pole: ";
        cin >> pole;
        pole--;
        while (game.plansza[pole] != 0 || pole > 8) {
            cout << "Podaj pole: ";
            cin >> pole;
            pole--;
        }
        game.plansza[pole] = wart;
    }

    Gracz(Gra game) {
        this->game = game;
    }
};

int main() {
    srand(time(nullptr));
    Gra game;
    Gracz player(game);
    while(!game.end()) {
        player.ruch();
        game.plansza = player.game.plansza;
        if (game.end()) break;
        game.ruch();
        player.game.plansza = game.plansza;
    }
    game.wyswietl();
    if (game.winner) cout << "WINNER";
    else if (!game.winner) cout << "LOSER";
    else cout << "DRAW";
    return 0;
}
