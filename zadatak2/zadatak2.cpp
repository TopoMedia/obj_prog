#include <iostream>   // ukljucuje cout i endl za ispis
#include <string>     // ukljucuje tip string
#include <utility>    // ukljucuje funkciju move (za semantiku prijenosa)

using namespace std;  // da ne moramo pisati std:: ispred imena

class Zrno {          // klasa koja opisuje jedno zrno pijeska
public:               // javna polja
    string boja;      // boja zrna
    float promjer;    // promjer zrna
};                    // kraj klase Zrno

class Pijesak {       // klasa koja sadrzi dinamicki alocirano polje zrna
public:               // javna polja i metode
    int kolicina;     // broj zrna u polju
    Zrno* zrno;       // POKAZIVAC na prvi element dinamicki alociranog polja zrna

    // ---------- obicni konstruktor ----------
    Pijesak(int _kolicina) : kolicina(_kolicina) {    // inicijalizacijska lista postavlja kolicinu
        zrno = new Zrno[kolicina];                    // dinamicki alocira polje od 'kolicina' zrna na heapu
        for (int i = 0; i < kolicina; i++) {          // prolazi kroz sva zrna
            zrno[i].boja = "zuta";                    // postavlja pocetnu boju
            zrno[i].promjer = 0.5f;                   // postavlja pocetni promjer
        }                                             // kraj petlje
        cout << "Obicni konstruktor (" << kolicina << ")" << endl; // ispis radi pracenja
    }                                                 // kraj konstruktora

    // ---------- KONSTRUKTOR KOPIRANJA (semantika kopiranja) ----------
    Pijesak(const Pijesak& drugi) : kolicina(drugi.kolicina) { // prima referencu na postojeci objekt, kopira kolicinu
        zrno = new Zrno[kolicina];                    // alocira NOVO, vlastito polje iste velicine
        for (int i = 0; i < kolicina; i++) {          // prolazi kroz sva zrna
            zrno[i] = drugi.zrno[i];                  // kopira svako zrno (duboka kopija)
        }                                             // kraj petlje
        cout << "Konstruktor kopiranja" << endl;      // ispis radi pracenja
    }                                                 // kraj konstruktora kopiranja

    // ---------- KONSTRUKTOR PRIJENOSA (semantika prijenosa) ----------
    Pijesak(Pijesak&& drugi) : kolicina(drugi.kolicina), zrno(drugi.zrno) { // && = rvalue referenca; preuzima kolicinu i pokazivac
        drugi.kolicina = 0;                           // "isprazni" izvorni objekt
        drugi.zrno = nullptr;                         // izvor vise ne pokazuje na polje (da ga njegov destruktor ne obrise)
        cout << "Konstruktor prijenosa" << endl;      // ispis radi pracenja
    }                                                 // kraj konstruktora prijenosa

    // ---------- OPERATOR PRIDRUZIVANJA KOPIRANJEM ----------
    Pijesak& operator=(const Pijesak& drugi) {        // poziva se za a = b; gdje oba objekta vec postoje
        if (this != &drugi) {                         // zastita od samopridruzivanja (a = a)
            delete[] zrno;                            // oslobadja STARO polje ovog objekta
            kolicina = drugi.kolicina;                // kopira kolicinu
            zrno = new Zrno[kolicina];                // alocira novo polje
            for (int i = 0; i < kolicina; i++) {      // prolazi kroz sva zrna
                zrno[i] = drugi.zrno[i];              // kopira svako zrno
            }                                         // kraj petlje
        }                                             // kraj if
        cout << "Operator pridruzivanja kopiranjem" << endl; // ispis radi pracenja
        return *this;                                 // vraca referencu na sebe (omogucuje a = b = c)
    }                                                 // kraj operatora

    // ---------- OPERATOR PRIDRUZIVANJA PRIJENOSOM ----------
    Pijesak& operator=(Pijesak&& drugi) {             // poziva se za a = move(b); ili a = privremeni objekt
        if (this != &drugi) {                         // zastita od samopridruzivanja
            delete[] zrno;                            // oslobadja STARO polje ovog objekta
            kolicina = drugi.kolicina;                // preuzima kolicinu
            zrno = drugi.zrno;                        // preuzima pokazivac (polje se NE kopira)
            drugi.kolicina = 0;                       // "isprazni" izvor
            drugi.zrno = nullptr;                     // izvor vise ne posjeduje polje
        }                                             // kraj if
        cout << "Operator pridruzivanja prijenosom" << endl; // ispis radi pracenja
        return *this;                                 // vraca referencu na sebe
    }                                                 // kraj operatora

    // ---------- DESTRUKTOR ----------
    ~Pijesak() {                                      // poziva se automatski kad objekt nestaje
        delete[] zrno;                                // oslobadja polje (delete[] na nullptr je siguran)
        cout << "Destruktor (" << kolicina << ")" << endl; // ispis radi pracenja
    }                                                 // kraj destruktora
};                                                    // kraj klase Pijesak

int main() {                                          // glavna funkcija
    Pijesak igraliste(1000000);                       // obicni konstruktor - milijun zrna
    cout << "Na igralistu ima " << igraliste.kolicina << " zrna pijeska!" << endl; // ispis kolicine

    // 1) konstruktor kopiranja: novi objekt nastaje kao kopija postojeceg
    Pijesak plaza(igraliste);                         // poziva Pijesak(const Pijesak&)
    cout << "plaza: " << plaza.kolicina << ", igraliste: " << igraliste.kolicina << endl; // oba imaju 1000000

    // 2) konstruktor prijenosa: novi objekt "preuzima" polje od postojeceg
    Pijesak kamion(move(plaza));                      // move pretvara plaza u rvalue -> poziva Pijesak(Pijesak&&)
    cout << "kamion: " << kamion.kolicina << ", plaza: " << plaza.kolicina << endl; // kamion 1000000, plaza 0

    // 3) operator pridruzivanja kopiranjem: oba objekta vec postoje
    Pijesak kanta(10);                                // obicni konstruktor - 10 zrna
    kanta = igraliste;                                // poziva operator=(const Pijesak&)
    cout << "kanta: " << kanta.kolicina << ", igraliste: " << igraliste.kolicina << endl; // oba 1000000

    // 4) operator pridruzivanja prijenosom: oba objekta vec postoje
    Pijesak vrecica(5);                               // obicni konstruktor - 5 zrna
    vrecica = move(kanta);                            // poziva operator=(Pijesak&&)
    cout << "vrecica: " << vrecica.kolicina << ", kanta: " << kanta.kolicina << endl; // vrecica 1000000, kanta 0

    return 0;                                         // kraj programa - pozivaju se destruktori svih objekata
}                                                     // kraj main
