# Zadatak 1 – odgovori na pitanja

## Gdje se rade provjere pravila?
U **setterima** (`setNaziv`, `setKategorija`) unutar klase `Knjiznica`. Konstruktor ne
postavlja polja direktno nego poziva iste settere, pa se pravila provjeravaju na
jednom mjestu – i kod stvaranja objekta i kod kasnije izmjene. Polja su `private`,
pa ih korisnik izvana ne može zaobići.

## Što se ispisuje kod dodajKnjigu1, 2 i 3?
Stvarni ispis programa:

```
=== dodajKnjigu1 (po vrijednosti) ===
Knjiga destructor called

=== dodajKnjigu2 (po referenci) ===
Knjiga destructor called

=== dodajKnjigu3 (pokazivacem) ===
Knjiga destructor called
Knjiga destructor called
```

- **dodajKnjigu1(Knjiga z)** – parametar je *po vrijednosti*, pa se pri pozivu stvara
  **nova kopija** (`z`). `push_back` stvara **još jednu kopiju** u vektoru. Na kraju
  metode `z` nestaje → ispiše se destruktor.
- **dodajKnjigu2(Knjiga& z)** – `z` je samo drugo ime za original, **nema kopije u
  parametru**. Novi objekt nastaje samo u vektoru (`push_back`).
- **dodajKnjigu3(Knjiga* z)** – kopira se samo adresa, **nema kopije knjige u
  parametru**. Novi objekt opet nastaje samo u vektoru (`push_back(*z)`).

**Zašto se ipak ispisuje destruktor kod 2 i 3?** Zbog vektora: kad vektor nema mjesta,
alocira veći komad memorije, **kopira** stare knjige tamo i **uništi** stare. Kod
drugog dodavanja premješta 1 knjigu (1 destruktor), kod trećeg 2 knjige (2 destruktora).

## Zašto se destruktor ispisuje više puta nego konstruktor?
Naš konstruktor (koji ispisuje poruku) poziva se samo 3 puta (`a`, `b`, `c`). Sve
ostale knjige nastaju **kopiranjem** – kompajler sam generira **konstruktor kopiranja**,
a on ništa ne ispisuje. Svaki objekt (i svaka kopija) se na kraju uništi, a destruktor
je samo jedan i uvijek ispisuje poruku. Zato je destruktora više.

## nadjiKnjigu1 / 2 / 3 – što zapažamo?
```
--- Knjige u knjiznici Gradska knjiznica ---
Ivo Andric - Na Drini cuprija (ISBN: 111)          <- NIJE promijenjeno (nadjiKnjigu1)
Miroslav Krleza - IZMIJENJENO 2 (ISBN: 222)        <- promijenjeno (nadjiKnjigu2)
Marija Juric Zagorka - IZMIJENJENO 3 (ISBN: 333)   <- promijenjeno (nadjiKnjigu3)
```
- `nadjiKnjigu1` vraća **kopiju** → mijenjamo kopiju, original u knjižnici ostaje isti.
- `nadjiKnjigu2` vraća **pokazivač** na original → izmjena preko `->` mijenja original.
- `nadjiKnjigu3` vraća **referencu** na original → izmjena mijenja original.

## Prednosti i nedostaci – kada koristiti koji način?

| Način | Prednosti | Nedostaci | Kada koristiti |
|---|---|---|---|
| **Po vrijednosti** (`Knjiga z`, vraća `Knjiga`) | original je siguran od izmjena; jednostavno | stvara kopiju → sporije i troši memoriju (veliki objekti) | mali objekti ili kad baš želimo zasebnu kopiju |
| **Po referenci** (`Knjiga& z`, vraća `Knjiga&`) | nema kopiranja → brzo; mijenja original; ne može biti „prazna” | funkcija može nenamjerno promijeniti original (zato `const Knjiga&` ako ne mijenjamo); vraćena referenca ne smije pokazivati na lokalnu varijablu; ne može izraziti „nije pronađeno” | kad treba mijenjati original ili za velike objekte (`const &` samo za čitanje) |
| **Pokazivačem** (`Knjiga* z`, vraća `Knjiga*`) | nema kopiranja; može biti `nullptr` → zgodno za „nije pronađeno” | mora se provjeravati `nullptr`; opasnost od pokazivača na nepostojeći objekt; nespretnija sintaksa (`*`, `->`, `&`) | kad objekt možda ne postoji (npr. pretraga) |

**Napomena:** pokazivač/referenca na element vektora postaje nevažeći ako se nakon
toga u vektor doda nova knjiga (vektor može premjestiti elemente u novu memoriju).
