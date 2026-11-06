# Zadatak 2 – objašnjenje

Polje `zrno` je promijenjeno iz `Zrno zrno;` u `Zrno* zrno;` jer zadatak traži da se
**dinamički alocira polje** (`new Zrno[kolicina]`), a to se sprema u pokazivač.
Destruktor ga oslobađa s `delete[] zrno;`.

| Što | Kada se poziva | Što radi |
|---|---|---|
| Konstruktor kopiranja `Pijesak(const Pijesak&)` | `Pijesak plaza(igraliste);` – novi objekt iz postojećeg | alocira **novo** polje i kopira sva zrna (duboka kopija) |
| Konstruktor prijenosa `Pijesak(Pijesak&&)` | `Pijesak kamion(move(plaza));` | **preuzme pokazivač**, izvor postavi na `nullptr` i 0 – ništa se ne kopira |
| Operator `=` kopiranjem | `kanta = igraliste;` – oba objekta već postoje | obriše svoje staro polje, alocira novo, kopira zrna |
| Operator `=` prijenosom | `vrecica = move(kanta);` | obriše svoje staro polje, preuzme tuđi pokazivač, izvor isprazni |

Ispis programa:
```
Obicni konstruktor (1000000)
Na igralistu ima 1000000 zrna pijeska!
Konstruktor kopiranja
plaza: 1000000, igraliste: 1000000
Konstruktor prijenosa
kamion: 1000000, plaza: 0
Obicni konstruktor (10)
Operator pridruzivanja kopiranjem
kanta: 1000000, igraliste: 1000000
Obicni konstruktor (5)
Operator pridruzivanja prijenosom
vrecica: 1000000, kanta: 0
Destruktor (1000000)
Destruktor (0)
Destruktor (1000000)
Destruktor (0)
Destruktor (1000000)
```
Objekti se uništavaju obrnutim redom od stvaranja. `plaza` i `kanta` imaju 0 jer su
im zrna „premještena”.

**Zašto je potrebno sve ovo?** Bez vlastitog konstruktora kopiranja kompajler bi kopirao
samo pokazivač – dva objekta bi pokazivala na isto polje i oba bi ga u destruktoru
pokušala obrisati (greška). Prijenos je puno brži od kopiranja jer se ne kopira milijun
zrna, nego samo jedan pokazivač.
