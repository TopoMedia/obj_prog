#include <iostream>
#include <string>
#include <utility>

using namespace std;

class Zrno {
public:
    string boja;
    float promjer;
};

class Pijesak {
public:
    int kolicina;
    Zrno* zrno;

    Pijesak(int _kolicina) : kolicina(_kolicina) {
        zrno = new Zrno[kolicina];
        for (int i = 0; i < kolicina; i++) {
            zrno[i].boja = "zuta";
            zrno[i].promjer = 0.5f;
        }
        cout << "Obicni konstruktor (" << kolicina << ")" << endl;
    }

    Pijesak(const Pijesak& drugi) : kolicina(drugi.kolicina) {
        zrno = new Zrno[kolicina];
        for (int i = 0; i < kolicina; i++) {
            zrno[i] = drugi.zrno[i];
        }
        cout << "Konstruktor kopiranja" << endl;
    }

    Pijesak(Pijesak&& drugi) : kolicina(drugi.kolicina), zrno(drugi.zrno) {
        drugi.kolicina = 0;
        drugi.zrno = nullptr;
        cout << "Konstruktor prijenosa" << endl;
    }

    Pijesak& operator=(const Pijesak& drugi) {
        if (this != &drugi) {
            delete[] zrno;
            kolicina = drugi.kolicina;
            zrno = new Zrno[kolicina];
            for (int i = 0; i < kolicina; i++) {
                zrno[i] = drugi.zrno[i];
            }
        }
        cout << "Operator pridruzivanja kopiranjem" << endl;
        return *this;
    }

    Pijesak& operator=(Pijesak&& drugi) {
        if (this != &drugi) {
            delete[] zrno;
            kolicina = drugi.kolicina;
            zrno = drugi.zrno;
            drugi.kolicina = 0;
            drugi.zrno = nullptr;
        }
        cout << "Operator pridruzivanja prijenosom" << endl;
        return *this;
    }

    ~Pijesak() {
        delete[] zrno;
        cout << "Destruktor (" << kolicina << ")" << endl;
    }
};

int main() {
    Pijesak igraliste(1000000);
    cout << "Na igralistu ima " << igraliste.kolicina << " zrna pijeska!" << endl;

    Pijesak plaza(igraliste);
    cout << "plaza: " << plaza.kolicina << ", igraliste: " << igraliste.kolicina << endl;

    Pijesak kamion(move(plaza));
    cout << "kamion: " << kamion.kolicina << ", plaza: " << plaza.kolicina << endl;

    Pijesak kanta(10);
    kanta = igraliste;
    cout << "kanta: " << kanta.kolicina << ", igraliste: " << igraliste.kolicina << endl;

    Pijesak vrecica(5);
    vrecica = move(kanta);
    cout << "vrecica: " << vrecica.kolicina << ", kanta: " << kanta.kolicina << endl;

    return 0;
}
