#include <iostream>   // ukljucuje cout i endl za ispis
using namespace std;  // da ne moramo pisati std::

class Slika {                            // pocetak klase Slika
private:                                 // privatni clanovi
    double cijena;                       // OBICNO polje: svaka slika ima SVOJU cijenu

    static double ukupnaCijena;          // STATICKO polje: JEDNO za cijelu klasu, zbroj cijena svih slika
    static int brojSlika;                // STATICKO polje: JEDNO za cijelu klasu, koliko je slika stvoreno

public:                                  // javne metode
    Slika(double _cijena) : cijena(_cijena) {   // konstruktor: postavlja cijenu ove slike
        ukupnaCijena += cijena;          // dodaje cijenu ove slike u zajednicki zbroj
        brojSlika++;                     // povecava zajednicki brojac slika
    }                                    // kraj konstruktora

    double getCijena() { return cijena; } // getter za cijenu jedne slike

    static double ProsjecnaCijena() {    // STATICKA metoda: poziva se preko klase (Slika::), bez objekta
        if (brojSlika == 0) {            // ako jos nema nijedne slike...
            return 0;                    // ...vrati 0 (izbjegavamo dijeljenje s nulom)
        }                                // kraj if
        return ukupnaCijena / brojSlika; // prosjek = zbroj cijena / broj slika
    }                                    // kraj staticke metode
};                                       // kraj klase Slika

double Slika::ukupnaCijena = 0;          // definicija i pocetna vrijednost statickog polja (IZVAN klase, obavezno)
int Slika::brojSlika = 0;                // definicija i pocetna vrijednost statickog polja (IZVAN klase, obavezno)

int main() {                             // glavna funkcija
    Slika Slika1(2000);                  // 2000 eura -> zbroj 2000, broj 1
    Slika Slika2(3000);                  // 3000 eura -> zbroj 5000, broj 2
    Slika Slika3(1800);                  // 1800 eura -> zbroj 6800, broj 3

    cout << Slika::ProsjecnaCijena() << " eura" << endl; // 6800 / 3 = 2266.67 eura
    return 0;                            // kraj programa
}                                        // kraj main
