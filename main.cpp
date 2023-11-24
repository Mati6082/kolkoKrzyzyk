#include <iostream>
#include <vector>

using namespace std;

class Gra {
public:
    vector<int> plansza{0, 0, 0, 0, 0, 0, 0, 0, 0};
    bool winner;

    void wyswietlNrPol() {
        cout << "Numery pol:\n";
        for (int i = 0; i < plansza.size(); i++) {
            cout << i+1 << " ";
            if (i % 3 == 0 && i != 0) cout << endl;
        }
        cout << endl;
    }

    void wyswietl() {
        cout << "Plansza:\n";
        for (int i = 0; i < plansza.size(); i++) {
            if (i % 3 == 0 && i != 0) cout << endl;
            if (plansza[i+1] == 1) cout << "X ";
            else if (plansza[i+1] == -1) cout << "O ";
            else cout << "- ";
        }
    }

    int sprawdzRzad() {
        for (int i = 0; i < 9; i += 3) {
            if (plansza[i] + plansza[i + 1] + plansza[i + 2] == 3) return 3;
            if (plansza[i] + plansza[i + 1] + plansza[i + 2] == -3) return -3;
        }
        return 0;
    }

    int sprawdzKol() {
        for (int i = 0; i < 3; i++) {
            if (plansza[i] + plansza[i + 3] + plansza[i + 6] == 3) return 3;
            if (plansza[i] + plansza[i + 3] + plansza[i + 6] == -3) return -3;
        }
        return 0;
    }

    int sprawdzPrzek() {
        if (plansza[0] + plansza[4] + plansza[8] == 3 ||
            plansza[2] + plansza[4] + plansza[6] == 3)
            return 3;
        if (plansza[0] + plansza[4] + plansza[8] == -3 ||
            plansza[2] + plansza[4] + plansza[6] == -3)
            return -3;
        return 0;
    }

    bool sprawdz() {
        if (sprawdzKol() == 3 || sprawdzRzad() == 3 || sprawdzPrzek() == 3) {
            winner = true;
            return true;
        }
        if (sprawdzKol() == -3 || sprawdzRzad() == -3 || sprawdzPrzek() == -3) {
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
        while (game.plansza[pole-1] != 0) {
            cout << "Podaj pole: ";
            cin >> pole;
        }
        game.plansza[pole-1] = wart;
    }

    Gracz(Gra game) {
        this->game = game;
    }
};

int main() {
    Gra game;
    Gracz player(game);
    while(!game.end()) {
        player.ruch();
        game.plansza = player.game.plansza;
    }
    if (game.winner) cout << "W";
    return 0;
}
