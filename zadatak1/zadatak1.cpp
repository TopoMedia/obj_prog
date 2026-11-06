#include <iostream>   // ukljucuje cout i endl za ispis na ekran
#include <string>     // ukljucuje tip string
#include <vector>     // ukljucuje spremnik vector
#include <cctype>     // ukljucuje funkciju isupper (provjera velikog slova)

using namespace std;  // da ne moramo pisati std:: ispred cout, string, vector...

// ======================= KLASA KNJIGA =======================
class Knjiga {                       // pocetak definicije klase Knjiga
public:                              // sve ispod je javno (dostupno izvan klase)
    string autor;                    // polje: ime autora knjige
    string naslov;                   // polje: naslov knjige
    string isbn;                     // polje: ISBN broj knjige (jedinstvena oznaka)

    // jedini konstruktor klase Knjiga - prima autora, naslov i ISBN
    Knjiga(string _autor, string _naslov, string _isbn)
        : autor(_autor), naslov(_naslov), isbn(_isbn) {   // inicijalizacijska lista postavlja polja
        cout << "Knjiga constructor called" << endl;      // ispis pri svakom pozivu konstruktora
    }                                                     // kraj konstruktora

    // destruktor - poziva se automatski kad objekt Knjiga prestane postojati
    ~Knjiga() {
        cout << "Knjiga destructor called" << endl;       // ispis pri svakom unistenju objekta
    }                                                     // kraj destruktora

    // pomocna metoda za ispis podataka o jednoj knjizi
    void ispis() {
        cout << autor << " - " << naslov << " (ISBN: " << isbn << ")" << endl; // ispisuje sva polja
    }                                                     // kraj metode ispis
};                                   // kraj klase Knjiga (obavezna tocka-zarez)

// ======================= KLASA KNJIZNICA =======================
class Knjiznica {                    // pocetak definicije klase Knjiznica
private:                             // privatna polja - izvana im se ne moze direktno pristupiti
    string adresa;                   // polje: adresa knjiznice
    string naziv;                    // polje: naziv knjiznice
    string kategorija;               // polje: kategorija knjiznice
    vector<Knjiga> knjige;           // polje: popis (vektor) knjiga u knjiznici

public:                              // javne metode - preko njih korisnik radi s objektom
    // konstruktor - provjere se rade tako da konstruktor poziva settere
    Knjiznica(string _adresa, string _naziv, string _kategorija) {
        setAdresa(_adresa);          // postavlja adresu preko settera
        setNaziv(_naziv);            // postavlja naziv preko settera (setter radi provjeru)
        setKategorija(_kategorija);  // postavlja kategoriju preko settera (setter radi provjeru)
    }                                // kraj konstruktora

    // ---------- GETTERI (citanje privatnih polja) ----------
    string getAdresa() { return adresa; }           // vraca adresu
    string getNaziv() { return naziv; }             // vraca naziv
    string getKategorija() { return kategorija; }   // vraca kategoriju

    // ---------- SETTERI (postavljanje polja uz provjeru pravila) ----------
    void setAdresa(string _adresa) {                // setter za adresu
        adresa = _adresa;                           // za adresu nema posebnog pravila, samo je postavimo
    }                                               // kraj settera

    void setNaziv(string _naziv) {                  // setter za naziv
        if (_naziv.length() > 0 && isupper(_naziv[0])) { // pravilo: naziv nije prazan i prvo slovo je veliko
            naziv = _naziv;                         // pravilo zadovoljeno -> postavi naziv
        } else {                                    // pravilo nije zadovoljeno
            cout << "Greska: naziv mora pocinjati velikim slovom!" << endl; // obavijesti korisnika
        }                                           // kraj if-else
    }                                               // kraj settera

    void setKategorija(string _kategorija) {        // setter za kategoriju
        if (_kategorija == "djecja" || _kategorija == "znanstvena" ||    // dopustene vrijednosti...
            _kategorija == "citaonica" || _kategorija == "opcenito") {   // ...samo ove cetiri
            kategorija = _kategorija;               // vrijednost je dopustena -> postavi je
        } else {                                    // vrijednost nije dopustena
            cout << "Greska: kategorija moze biti samo djecja, znanstvena, citaonica ili opcenito!" << endl; // poruka
        }                                           // kraj if-else
    }                                               // kraj settera

    // ---------- DODAVANJE KNJIGA ----------
    void dodajKnjigu1(Knjiga z) {    // prijenos PO VRIJEDNOSTI: z je nova KOPIJA predane knjige
        knjige.push_back(z);         // push_back u vektor sprema jos jednu kopiju od z
    }                                // ovdje z (lokalna kopija) nestaje -> poziva se destruktor

    void dodajKnjigu2(Knjiga& z) {   // prijenos PO REFERENCI: z je drugo ime za originalni objekt (nema kopije)
        knjige.push_back(z);         // push_back u vektor sprema kopiju originala
    }                                // nema lokalne kopije pa se za z ne poziva destruktor

    void dodajKnjigu3(Knjiga* z) {   // prijenos POKAZIVACEM: z sadrzi adresu originalnog objekta (nema kopije)
        knjige.push_back(*z);        // *z dohvaca objekt na toj adresi; vektor sprema njegovu kopiju
    }                                // kopira se samo pokazivac (adresa), ne knjiga -> nema lokalne kopije za unistiti

    // ---------- ISPIS ----------
    void ispisSvihKnjiga() {                         // ispisuje sve knjige iz knjiznice
        cout << "--- Knjige u knjiznici " << naziv << " ---" << endl; // naslov ispisa
        for (int i = 0; i < knjige.size(); i++) {    // prolazi kroz sve elemente vektora
            knjige[i].ispis();                       // ispisuje i-tu knjigu
        }                                            // kraj petlje
    }                                                // kraj metode

    // ---------- TRAZENJE KNJIGA ----------
    Knjiga nadjiKnjigu1(string isbn) {               // vraca KOPIJU pronadjene knjige
        for (int i = 0; i < knjige.size(); i++) {    // prolazi kroz sve knjige
            if (knjige[i].isbn == isbn) {            // ako se ISBN podudara...
                return knjige[i];                    // ...vrati kopiju te knjige
            }                                        // kraj if
        }                                            // kraj petlje
        return Knjiga("", "", "");                   // nije pronadjena -> vrati "praznu" knjigu
    }                                                // kraj metode

    Knjiga* nadjiKnjigu2(string isbn) {              // vraca POKAZIVAC (adresu) na knjigu u vektoru
        for (int i = 0; i < knjige.size(); i++) {    // prolazi kroz sve knjige
            if (knjige[i].isbn == isbn) {            // ako se ISBN podudara...
                return &knjige[i];                   // ...vrati adresu originalne knjige u vektoru
            }                                        // kraj if
        }                                            // kraj petlje
        return nullptr;                              // nije pronadjena -> vrati prazan pokazivac
    }                                                // kraj metode

    Knjiga& nadjiKnjigu3(string isbn) {              // vraca REFERENCU na knjigu u vektoru
        for (int i = 0; i < knjige.size(); i++) {    // prolazi kroz sve knjige
            if (knjige[i].isbn == isbn) {            // ako se ISBN podudara...
                return knjige[i];                    // ...vrati referencu na originalnu knjigu
            }                                        // kraj if
        }                                            // kraj petlje
        // referenca ne moze biti "prazna" (kao nullptr), zato ako knjiga ne postoji
        throw "Knjiga s tim ISBN-om ne postoji!";    // bacamo iznimku (prekida program ako se ne uhvati)
    }                                                // kraj metode
};                                                   // kraj klase Knjiznica

// ======================= MAIN =======================
int main() {                                         // glavna funkcija - ovdje program pocinje
    // ---------- 1. dio: kreiranje knjiznice i provjera pravila ----------
    Knjiznica k("Ilica 1, Zagreb", "Gradska knjiznica", "opcenito"); // ispravni podaci
    cout << k.getNaziv() << ", " << k.getAdresa() << ", " << k.getKategorija() << endl; // ispis podataka

    k.setNaziv("mala knjiznica");                    // POGRESNO: malo pocetno slovo -> ispisuje gresku
    k.setKategorija("strip");                        // POGRESNO: nepostojeca kategorija -> ispisuje gresku
    k.setKategorija("znanstvena");                   // ispravno -> kategorija se mijenja
    cout << k.getNaziv() << ", " << k.getKategorija() << endl; // naziv ostao isti, kategorija promijenjena

    // ---------- 2. dio: dodavanje knjiga ----------
    cout << endl << "=== Stvaranje knjiga ===" << endl; // naslov dijela
    Knjiga a("Ivo Andric", "Na Drini cuprija", "111");         // poziva konstruktor
    Knjiga b("Miroslav Krleza", "Povratak Filipa Latinovicza", "222"); // poziva konstruktor
    Knjiga c("Marija Juric Zagorka", "Gricka vjestica", "333"); // poziva konstruktor

    cout << endl << "=== dodajKnjigu1 (po vrijednosti) ===" << endl; // naslov
    k.dodajKnjigu1(a);                               // kopija u parametar + kopija u vektor
    cout << endl << "=== dodajKnjigu2 (po referenci) ===" << endl;   // naslov
    k.dodajKnjigu2(b);                               // samo kopija u vektor
    cout << endl << "=== dodajKnjigu3 (pokazivacem) ===" << endl;    // naslov
    k.dodajKnjigu3(&c);                              // &c je adresa objekta c; samo kopija u vektor

    // ---------- 3. dio: ispis ----------
    cout << endl;                                    // prazan red
    k.ispisSvihKnjiga();                             // ispis svih knjiga

    // ---------- 4. dio: trazenje i izmjena knjiga ----------
    cout << endl << "=== nadjiKnjigu1 (vraca kopiju) ===" << endl; // naslov
    Knjiga kopija = k.nadjiKnjigu1("111");           // u varijablu 'kopija' dobivamo KOPIJU knjige
    kopija.naslov = "IZMIJENJENO 1";                 // mijenjamo kopiju, original u knjiznici ostaje isti

    cout << endl << "=== nadjiKnjigu2 (vraca pokazivac) ===" << endl; // naslov
    Knjiga* pok = k.nadjiKnjigu2("222");             // pok pokazuje na ORIGINALNU knjigu u vektoru
    if (pok != nullptr) {                            // provjera je li knjiga pronadjena
        pok->naslov = "IZMIJENJENO 2";               // -> pristupa polju preko pokazivaca; mijenja original
    }                                                // kraj if

    cout << endl << "=== nadjiKnjigu3 (vraca referencu) ===" << endl; // naslov
    Knjiga& ref = k.nadjiKnjigu3("333");             // ref je drugo ime za ORIGINALNU knjigu u vektoru
    ref.naslov = "IZMIJENJENO 3";                    // mijenja original

    cout << endl;                                    // prazan red
    k.ispisSvihKnjiga();                             // promijenjene su samo 2. i 3. knjiga, 1. nije!

    cout << endl << "=== Kraj programa ===" << endl; // nakon ovoga se unistavaju svi lokalni objekti
    return 0;                                        // uspjesan zavrsetak programa
}                                                    // kraj main - pozivaju se destruktori
