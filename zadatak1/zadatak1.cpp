#include <iostream>
#include <string>
#include <vector>
#include <cctype>

using namespace std;

class Knjiga {
public:
    string autor;
    string naslov;
    string isbn;

    Knjiga(string _autor, string _naslov, string _isbn)
        : autor(_autor), naslov(_naslov), isbn(_isbn) {
        cout << "Knjiga constructor called" << endl;
    }

    ~Knjiga() {
        cout << "Knjiga destructor called" << endl;
    }

    void ispis() {
        cout << autor << " - " << naslov << " (ISBN: " << isbn << ")" << endl;
    }
};

class Knjiznica {
private:
    string adresa;
    string naziv;
    string kategorija;
    vector<Knjiga> knjige;

public:
    Knjiznica(string _adresa, string _naziv, string _kategorija) {
        setAdresa(_adresa);
        setNaziv(_naziv);
        setKategorija(_kategorija);
    }

    string getAdresa() { return adresa; }
    string getNaziv() { return naziv; }
    string getKategorija() { return kategorija; }

    void setAdresa(string _adresa) {
        adresa = _adresa;
    }

    void setNaziv(string _naziv) {
        if (_naziv.length() > 0 && isupper(_naziv[0])) {
            naziv = _naziv;
        } else {
            cout << "Greska: naziv mora pocinjati velikim slovom!" << endl;
        }
    }

    void setKategorija(string _kategorija) {
        if (_kategorija == "djecja" || _kategorija == "znanstvena" ||
            _kategorija == "citaonica" || _kategorija == "opcenito") {
            kategorija = _kategorija;
        } else {
            cout << "Greska: kategorija moze biti samo djecja, znanstvena, citaonica ili opcenito!" << endl;
        }
    }

    void dodajKnjigu1(Knjiga z) {
        knjige.push_back(z);
    }

    void dodajKnjigu2(Knjiga& z) {
        knjige.push_back(z);
    }

    void dodajKnjigu3(Knjiga* z) {
        knjige.push_back(*z);
    }

    void ispisSvihKnjiga() {
        cout << "--- Knjige u knjiznici " << naziv << " ---" << endl;
        for (int i = 0; i < knjige.size(); i++) {
            knjige[i].ispis();
        }
    }

    Knjiga nadjiKnjigu1(string isbn) {
        for (int i = 0; i < knjige.size(); i++) {
            if (knjige[i].isbn == isbn) {
                return knjige[i];
            }
        }
        return Knjiga("", "", "");
    }

    Knjiga* nadjiKnjigu2(string isbn) {
        for (int i = 0; i < knjige.size(); i++) {
            if (knjige[i].isbn == isbn) {
                return &knjige[i];
            }
        }
        return nullptr;
    }

    Knjiga& nadjiKnjigu3(string isbn) {
        for (int i = 0; i < knjige.size(); i++) {
            if (knjige[i].isbn == isbn) {
                return knjige[i];
            }
        }
        throw "Knjiga s tim ISBN-om ne postoji!";
    }
};

int main() {
    Knjiznica k("Ilica 1, Zagreb", "Gradska knjiznica", "opcenito");
    cout << k.getNaziv() << ", " << k.getAdresa() << ", " << k.getKategorija() << endl;

    k.setNaziv("mala knjiznica");
    k.setKategorija("strip");
    k.setKategorija("znanstvena");
    cout << k.getNaziv() << ", " << k.getKategorija() << endl;

    cout << endl << "=== Stvaranje knjiga ===" << endl;
    Knjiga a("Ivo Andric", "Na Drini cuprija", "111");
    Knjiga b("Miroslav Krleza", "Povratak Filipa Latinovicza", "222");
    Knjiga c("Marija Juric Zagorka", "Gricka vjestica", "333");

    cout << endl << "=== dodajKnjigu1 (po vrijednosti) ===" << endl;
    k.dodajKnjigu1(a);
    cout << endl << "=== dodajKnjigu2 (po referenci) ===" << endl;
    k.dodajKnjigu2(b);
    cout << endl << "=== dodajKnjigu3 (pokazivacem) ===" << endl;
    k.dodajKnjigu3(&c);

    cout << endl;
    k.ispisSvihKnjiga();

    cout << endl << "=== nadjiKnjigu1 (vraca kopiju) ===" << endl;
    Knjiga kopija = k.nadjiKnjigu1("111");
    kopija.naslov = "IZMIJENJENO 1";

    cout << endl << "=== nadjiKnjigu2 (vraca pokazivac) ===" << endl;
    Knjiga* pok = k.nadjiKnjigu2("222");
    if (pok != nullptr) {
        pok->naslov = "IZMIJENJENO 2";
    }

    cout << endl << "=== nadjiKnjigu3 (vraca referencu) ===" << endl;
    Knjiga& ref = k.nadjiKnjigu3("333");
    ref.naslov = "IZMIJENJENO 3";

    cout << endl;
    k.ispisSvihKnjiga();

    cout << endl << "=== Kraj programa ===" << endl;
    return 0;
}
