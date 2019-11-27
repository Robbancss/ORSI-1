# ORSI-1

# ORSI - 1. beadandó

Class: ORSI - Assigment
Created: Oct 31, 2019 9:31 AM
Reviewed: No

# **A megoldandó probléma a következő:**

Feladatunk alapvetően a Freivalds algoritmus implementálása lesz. Ennek működése:

Legyenek `A, B, C` mátrixok adottak, mind a három `N x N`-es méretű. Célunk annak eldöntése, hogy `A x B = C` teljesül e anélkül, hogy az `A x B` szorzatot explicit kiszámolnánk (azaz mátrix-mátrix szorzás nélkül). Válasszunk ehhez egy véletlenszerű, `{0,1}` halmaz fölötti, `N` dimenziós vektort (legyen `alpha`), majd számítsuk ki a `beta = A x (B x alpha)` és a `gamma = C x alpha` vektorokat. Ha `beta = gamma`, akkor az algoritmus válasza, hogy `A x B = C`, különben pedig `A x B =/= C`.

Megmutatható, hogy ha `A x B = C`, akkor az algoritmus helyes eredményt ad, egyéb esetben pedig legfeljebb 50% eséllyel téved (bizonyítását lásd: `Algoritmusok tervezése és elemzése` tárgyon.)

Ha az algoritmust más és más `alpha` vektorokat választva újra és újra lefuttatjuk, a tévedés valószínűsége tetszőlegesen kicsivé tehető.

Feladatunk ennek az implementálása lesz.

Tekintve, hogy egy-egy ilyen számítás sok időt is igénybe vehet, ezért a megoldást *párhuzamos* módon készítjük el, melyben az egyes “próbálkozásokat” külön szálon, egyszerre fogjuk futtatni!

---

Az inputfájl felépítése az alábbi:

A bemeneti fájlban (`input.txt`) első sorában két egész számot találhatunk, először a mátrixok méretének értéke (`N >= 1` egész), ezt követi annak a száma, hány próbálkozást fogunk végrehajtani (`tryCount >= 1` egész).

Az ezt következő `3N` sorban sorra az `A, B, C` mátrixokat olvashatjuk (egy sor a mátrix egy sorának felel meg, szóközökkel tagolva).

Feltehetjük, hogy az input fájl a fent leírtaknak megfelelően van kitöltve, és nem található benne pl. negatív méret, valós vagy olyan szám, ami nem felel meg a fenti elvárásoknak, pontosan annyi érték van mindenhol felsorolva, hogy a mátrixokat be lehessen olvasni stb., ezekre külön ellenőrzést nem kell végezni.

---

A program olvassa be az adatokat, majd `tryCount` folyamatot (párhuzamosan) indítva számítsa ki a Freivalds algoritmus által adott megoldásokat. Az így kapott megoldásokat a következő módon értelmezzük: Ha az összes folyamat igaz eredményt ad, akkor elfogadjuk a szorzás eredményét, ellenkező esetben elutasítjuk azt. Az output fájlba (`output.txt`) emiatt az `accepted` vagy `rejected` szó kerüljön (és egy új sor karakter utána). A fő szál semmilyen szorzáshoz kapcsolódó számítást ne végezzen! Az egyes folyamatoknak három adatot kell megkapnia - a három mátrixot.

Egy példa bemenet (`input.txt`):

    3 10
    4 5 2
    3 6 8
    7 1 9
    1 6 3
    9 2 5
    8 4 7
    65 42 51
    121 62 95
    88 80 89

Az ehhez tartozó elvárt kimenet (`output.txt`):

    accepted

# **Implementációs követelmények**

A feladatot C++ nyelvben implementálva, a C++11 által biztosított thread/future lib segítségével kell megvalósítani. Ha még nem találkoztál ezzel, a lenti oldalon találsz egy cpp fájlt, ami segíthet elindulni ezzel. A követelmények / guideline szintén megtalálható ott.

Random számok thread-safe generálásához (egyedi seedekkel) az alábbi kód-részlet használható:

    ...
    #include <chrono>
    #include <random>
    ...
    
    int randomNumber(int min, int max)
    {
       static thread_local std::mt19937 generator(std::chrono::system_clock::now().time_since_epoch().count());
       std::uniform_int_distribution<int> distribution(min, max);
       return distribution(generator);
    }

Ez a kód még egyáltalán nem hatékony, ezt felhasználva érdemes az egyes szálakon futtatott függvénybe ezt beépíteni valahogy.

# **Általános elvárások:**

Fokozottan kérünk mindenkit, hogy a beadandó határidejét (november 3, 23:59) vegye figyelembe! Kérjük osszátok be az időtöket, hogy ne csússzatok le a határidőről semmi esetben sem! Ez után nem áll módunkban elfogadni megoldásokat, kifogástól és indoklástól függetlenül! (Szült a halam, nem tudtam beadni, de elküldöm emailben; pont feltöltöttem volna, de lezárt a BEAD, jó lesz facebookon?; Késett a vonat de majd behozom pendriveon úgy jó? Nem, nem lesz jó egyik esetben sem.)

Kérünk mindenkit, hogy olvassa el a BEAD-on a hozzászólásokat, amiket írunk neki, mielőtt újra és újra feltölti a megoldást, így elkerülhető, hogy feleslegesen terheljétek a szervert, és egy körben lehet a legtöbb hibát javítani.

A megoldásaitokat egyetlen ZIP fájlba tömörítve töltsétek fel! Kérünk benneteket, hogy csak a szükséges forrásfájl(oka)t rakjátok bele az állomány gyökerébe, teljes projektet, solutiont (.cbp, .sln, illetve az ezekhez tartozó többi fájl), object fájlokat, vagy közvetlenül futtatható állományt (a.exe, a.out, etc..) semmiképp sem!

A beadandót **binárisan értékeljük**, de ettől függetlenül fogtok kapni (valószínűleg) megjegyzéseket a megoldásotokra vonatkozóan.

Javítani bármennyiszer lehet, de a határidő szoros közeledtével egyre kisebb az esély rá, hogy lesz időnk megnézni azt.

Szeretnénk mindenkit megkérni, hogy az alábbiak vegye figyelembe a feltöltés során:

- A forrásfájlokat a ZIP gyökerébe helyezzétek el, tehát ne mappát tömörítsetek, csupán a fájlokat!

Értékelési megjegyzés: Az automata tesztelő elutasítja a megoldást, ha az nem fordult le (ennek okát is jelezni fogja). Amennyiben fordítható, lefuttatja több különböző inputra, és összeveti a megoldásodat az elvárt kimenetekkel. Ha mindegyik egyezik (a whitespacek között nem tesz különbséget, így mindegy, hogy a sorok végén van -e plusz szóköz vagy nincs, illetve sorvégi enter az utolsó bejegyzés után), akkor a BEADon átment a megoldásod. Ez után még valamelyik oktató is ellenőrzi a megoldást - a kódot átnézve, megjegyzéseket fűzve hozzá. Ha ez is rendben van, akkor elfogadottnak minősítjük a beadandót. Ha valami problémába ütközünk (vagy a BEADon nem megy át), akkor elutasításra kerül a megoldásod. Ennek okát részletezni fogjuk.

Egyéb segítség: [https://people.inf.elte.hu/mykeesg/index.php?page=orsi&year=19_20_1](https://people.inf.elte.hu/mykeesg/index.php?page=orsi&year=19_20_1)

Az értékelési / kódolási guide szintén az előbbi linken érhető el (FAQ és követelmények).

Az automatikus tesztelés BEAD által működik!
