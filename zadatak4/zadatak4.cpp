#include <iostream>   // ukljucuje cout, endl i ostream
using namespace std;  // da ne moramo pisati std::

class TimeSpan {                                   // klasa koja mjeri protok vremena
private:                                           // privatna polja
    int sati;                                      // broj sati (moze biti i vise od 24)
    int minute;                                    // broj minuta (0 - 59)
    int sekunde;                                   // broj sekundi (0 - 59)

public:                                            // javni dio
    TimeSpan(int _sati, int _minute, int _sekunde) {   // konstruktor s parametrima
        int ukupno = _sati * 3600 + _minute * 60 + _sekunde; // sve pretvori u sekunde
        sati = ukupno / 3600;                      // cijeli sati
        minute = (ukupno % 3600) / 60;             // ostatak nakon sati -> minute
        sekunde = ukupno % 60;                     // ostatak nakon minuta -> sekunde
    }                                              // kraj konstruktora

    operator int() {                               // operator pretvorbe u int: (int)a
        return sati * 3600 + minute * 60 + sekunde; // vraca ukupan broj sekundi
    }                                              // kraj operatora pretvorbe

    TimeSpan operator+(TimeSpan drugi) {           // operator zbrajanja: a + b
        return TimeSpan(sati + drugi.sati,         // zbroji sate...
                        minute + drugi.minute,     // ...minute...
                        sekunde + drugi.sekunde);  // ...i sekunde; konstruktor sredi prijelaze (60 s -> 1 min)
    }                                              // kraj operatora +

    bool operator<(TimeSpan drugi) {               // operator usporedbe: a < b
        return (int)*this < (int)drugi;            // usporedjuje ukupne sekunde oba objekta
    }                                              // kraj operatora <

    bool operator==(TimeSpan drugi) {              // operator jednakosti: a == b
        return (int)*this == (int)drugi;           // jednaki su ako imaju isti broj sekundi
    }                                              // kraj operatora ==

    friend ostream& operator<<(ostream& izlaz, TimeSpan t); // prijateljska funkcija za cout << t
};                                                 // kraj klase TimeSpan

ostream& operator<<(ostream& izlaz, TimeSpan t) {  // definicija operatora ispisa (izvan klase)
    izlaz << t.sati << ":" << t.minute << ":" << t.sekunde << endl; // ispis u obliku h:m:s i novi red
    return izlaz;                                  // vraca tok da radi ulancavanje (cout << a << b)
}                                                  // kraj operatora <<

int main()                                         // glavna funkcija (iz zadatka)
{
    TimeSpan a(1, 0, 0);                           // a = 1 sat
    TimeSpan x(24, 0, 0);                          // x = 24 sata (granica petlje)

    while (a < x)                                  // operator < : vrti dok je a manje od 24 h
    {
        if (a == TimeSpan(1, 0, 0))                // operator == : je li a tocno 1 sat
            a = a + TimeSpan(10, 6, 7);            // operator + : dodaj 10:6:7
        else if (a < TimeSpan(12, 0, 0))           // operator < : je li a manje od 12 h
            a = a + TimeSpan(0, 37, 14);           // dodaj 0:37:14
        else                                       // inace (12 h ili vise)
            a = a + TimeSpan(9, 11, 57);           // dodaj 9:11:57

        cout << a;                                 // operator << : ispis vremena
    }

    cout << "Ukupno sekundi: " << (int)a << endl;  // operator int : ukupne sekunde

    return 0;                                      // kraj programa
}
