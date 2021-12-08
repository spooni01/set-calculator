Pre kompiláciu programu "gcc -std=c99 -Wall -Wextra -Werror setcal.c -o setcal" zadaj:
./gcc/make

<h1>Jak fungujou datove typy</h1>

Prvky vsech mnozin musi patrit do univerza, platna data tedy maji informace o vsech novych prvcich na prvnim radku v univerzu.
Na mnoziny se lze tedy divat jako na pouhe kombinace prvku z univerza a na relace jako kombinace vsech moznych dvojic prvku z univerza.

Do char **univerzum (pole pointeru na char-y) si tedy ulozime vsechny stringy.

Do structu set_t si ulozime mnozinu jako int *elements (pole int-u), ve kterem bude 1/0 v zavislosti, jestli se urcita polozka z univerza v mnozine nachazi ci nikoliv.

Do structy rel_t si ulozime relaci jako int **elements (pole pointeru na int, tedy 2d pole int-u), lze o tom premyslet jako o definici relace tabulkou - co je s cim v relaci.



PRIKLAD

U = {"a", "b", "c", "d", "e"}

Mnozinu {"a", "c"} bychom reprezentovali nasledovne: {1, 0, 1, 0, 0} - tedy ubsahuje 1. a 3. polozku z univerza

Mnozinu {"b", "c", "d", "e"} bychom reprezentovali nasledovne: {0, 1, 1, 1, 1} - tedy ubsahuje 2. 3. 4. a 5. polozku z univerza

Relace {(a,b), (b,a), (d,e), (c,d)} takto:

{{0 ,1, 0, 0, 0},
 {1, 0, 0, 0, 0},
 {0, 0, 0, 1, 0},
 {0, 0, 0, 0, 1},
 {0, 0, 0, 0, 0}}

Neboli v trochu citelnejsim tvaru:

![Výstřižek](https://user-images.githubusercontent.com/80490096/143857554-4d9e6cf9-a66b-4fc8-a894-97f3f5eaa37e.PNG)


<hr>
<!-- wikipage start -->
<h1>Zadanie projektu</h1><div class="toc"><table class="toc"><tbody><tr><th colspan="8">Obsah</th></tr>
<tr><td nowrap="" width="10">1</td><td colspan="7"> <a class="internal" href="#Projekt_2_-_Práce_s_datovými_strukturami">Projekt 2 - Práce s datovými strukturami</a></td></tr><tr><td>&nbsp;</td><td nowrap="" width="10">1.1</td><td colspan="6"> <a class="internal" href="#Motivace_projektu">Motivace projektu</a></td></tr><tr><td>&nbsp;</td><td nowrap="" width="10">1.2</td><td colspan="6"> <a class="internal" href="#Popis_projektu">Popis projektu</a></td></tr><tr><td>&nbsp;</td><td nowrap="" width="10">1.3</td><td colspan="6"> <a class="internal" href="#Detailní_specifikace">Detailní specifikace</a></td></tr><tr><td>&nbsp;</td><td>&nbsp;</td><td nowrap="" width="10">1.3.1</td><td colspan="5"> <a class="internal" href="#Překlad_a_odevzdání_zdrojového_souboru">Překlad a odevzdání zdrojového souboru</a></td></tr><tr><td>&nbsp;</td><td>&nbsp;</td><td nowrap="" width="10">1.3.2</td><td colspan="5"> <a class="internal" href="#Syntax_spuštění">Syntax spuštění</a></td></tr><tr><td>&nbsp;</td><td>&nbsp;</td><td nowrap="" width="10">1.3.3</td><td colspan="5"> <a class="internal" href="#Formát_vstupního_souboru">Formát vstupního souboru</a></td></tr><tr><td>&nbsp;</td><td>&nbsp;</td><td>&nbsp;</td><td nowrap="" width="10">1.3.3.1</td><td colspan="4"> <a class="internal" href="#Univerzum">Univerzum</a></td></tr><tr><td>&nbsp;</td><td>&nbsp;</td><td>&nbsp;</td><td nowrap="" width="10">1.3.3.2</td><td colspan="4"> <a class="internal" href="#Množiny">Množiny</a></td></tr><tr><td>&nbsp;</td><td>&nbsp;</td><td>&nbsp;</td><td nowrap="" width="10">1.3.3.3</td><td colspan="4"> <a class="internal" href="#Relace">Relace</a></td></tr><tr><td>&nbsp;</td><td>&nbsp;</td><td>&nbsp;</td><td nowrap="" width="10">1.3.3.4</td><td colspan="4"> <a class="internal" href="#Příkazy">Příkazy</a></td></tr><tr><td>&nbsp;</td><td>&nbsp;</td><td nowrap="" width="10">1.3.4</td><td colspan="5"> <a class="internal" href="#Příkazy_nad_množinami">Příkazy nad množinami</a></td></tr><tr><td>&nbsp;</td><td>&nbsp;</td><td nowrap="" width="10">1.3.5</td><td colspan="5"> <a class="internal" href="#Příkazy_nad_relacemi">Příkazy nad relacemi</a></td></tr><tr><td>&nbsp;</td><td>&nbsp;</td><td nowrap="" width="10">1.3.6</td><td colspan="5"> <a class="internal" href="#Implementační_detaily">Implementační detaily</a></td></tr><tr><td>&nbsp;</td><td nowrap="" width="10">1.4</td><td colspan="6"> <a class="internal" href="#Příklady_použití">Příklady použití</a></td></tr><tr><td>&nbsp;</td><td>&nbsp;</td><td nowrap="" width="10">1.4.1</td><td colspan="5"> <a class="internal" href="#Tipy_pro_implementaci">Tipy pro implementaci</a></td></tr><tr><td>&nbsp;</td><td>&nbsp;</td><td nowrap="" width="10">1.4.2</td><td colspan="5"> <a class="internal" href="#Neočekávané_chování">Neočekávané chování</a></td></tr><tr><td>&nbsp;</td><td nowrap="" width="10">1.5</td><td colspan="6"> <a class="internal" href="#Hodnocení">Hodnocení</a></td></tr><tr><td>&nbsp;</td><td nowrap="" width="10">1.6</td><td colspan="6"> <a class="internal" href="#Prémiové_hodnocení">Prémiové hodnocení</a></td></tr><tr><td>&nbsp;</td><td>&nbsp;</td><td>&nbsp;</td><td nowrap="" width="10">1.6.1.1</td><td colspan="4"> <a class="internal" href="#Pokročilé_příkazy">Pokročilé příkazy</a></td></tr></tbody></table></div>

<p>

<b>Legenda:</b>
</p>

<p>

<span style="color:red">Červeně označený text</span> značí změnu zadání. Na změnu zadání bude upozorněno na fóru.<br>

<span style="color:blue">Modře označený text</span> upřesňuje zadání. Takto označené fráze nebudou mít na hodnocení téměř žádný vliv.<br>

</p>

<h1><span><a class="anchor" name="Projekt_2_-_Práce_s_datovými_strukturami">Projekt 2 - Práce s datovými strukturami</a></span></h1>

<p>

Na projektu lze pracovat v týmu 3-5 členů. V týdnu 1.-5.11. se seznamte se zadáním projektu a zformujte si tým, ve kterém chcete na projektu pracovat. Členové týmu musí patřit do stejné skupiny laboratorního cvičení.
</p>

<h2><span><a class="anchor" name="Motivace_projektu">Motivace projektu</a></span></h2>

<p>

V prvním projektu jsme si vyzkoušeli jednoduché práce s textovými řetězci a základními cykly. V tomto projektu spojíme znalosti programování a diskrétní matematiky. Projekt zahrnuje zpracování vstupu, dynamickou alokaci a algoritmy pro průchody v datových strukturách.
</p>

<h2><span><a class="anchor" name="Popis_projektu">Popis projektu</a></span></h2>

<p>

Cílem projektu je vytvořit program, který bude implementovat základní matematické operace nad množinami a binárními relacemi. Vstupem programu budou textová data reprezentující množiny a relace a zadání operací. Výsledek zpracování bude program tisknout na standardní výstup.
</p>

<h2><span><a class="anchor" name="Detailní_specifikace">Detailní specifikace</a></span></h2>

<p>

Program implementujte ve zdrojovém souboru <i>setcal.c</i> (Set Calculator). Vstupní data budou čtena ze souboru, jehož jméno bude zadáno argumentem příkazové řádky. Program provádí operace zadané v souboru po řádcích jedním průchodem. Výsledek zpracování každého řádku program tiskne na standardní výstup (tedy počet řádků na výstupu odpovídá počtu řádků vstupního souboru).
</p>

<h3><span><a class="anchor" name="Překlad_a_odevzdání_zdrojového_souboru">Překlad a odevzdání zdrojového souboru</a></span></h3>

<p>

Odevzdání: Odevzdejte zdrojový soubor <i>setcal.c</i> prostřednictvím informačního systému.
</p>

<p>

Překlad: Program překládejte s následujícími argumenty
</p>
<pre>$ gcc -std=c99 -Wall -Wextra -Werror setcal.c -o setcal</pre>

<h3><span><a class="anchor" name="Syntax_spuštění">Syntax spuštění</a></span></h3>

<p>

Program se spouští v následující podobě: (./setcal značí umístění a název programu):
</p>
<pre>./setcal FILE</pre>

<h3><span><a class="anchor" name="Formát_vstupního_souboru">Formát vstupního souboru</a></span></h3>

<p>

Textový soubor se skládá ze tří po sobě následujících částí:
</p>

<ol>
<li class="level1">Definice univerza - jeden řádek začínající "U " a pokračující mezerou oddělenými prvky,</li>
<li class="level1">Definice množin a relací - jeden nebo více řádků začínající "S " nebo "R " a pokračující mezerou oddělenými prvky (řádek začínající "S" indikuje definici množiny, "R" slouží pro definici relace),</li>
<li class="level1">Příkazy nad množinami a relacemi - jeden nebo více řádků začínající "C " a pokračující identifikátorem příkazu.</li>
</ol>

<h4><span><a class="anchor" name="Univerzum">Univerzum</a></span></h4>

<p>

Prvky univerza <del>mohou být</del><span style="color:red">jsou</span> řetězce obsahující malá a velká písmena anglické abecedy. Délka řetězce je maximálně 30 znaků. Prvky univerza nesmí obsahovat identifikátory příkazů (viz níže) a klíčová slova true a false. Všechny prvky v množinách a relacích musí patřit do univerza. Příklad:
</p>
<pre>U Apple Lemon Orange Banana Peach</pre>

<h4><span><a class="anchor" name="Množiny">Množiny</a></span></h4>

<p>

Každá množina je definovaná na jednom řádku mezerou oddělenými prvky z univerza. Identifikátorem množiny je číslo řádku, na kterém je množina definovaná (vzhledem k tomu, že na prvním řádku souboru je univerzum, identifikátory množin tedy začínají číslem 2). Identifikátory množin jsou použity v operacích (viz níže). Příklad definice množiny:
</p>
<pre>S Apple Banana Peach</pre>

<h4><span><a class="anchor" name="Relace">Relace</a></span></h4>

<p>

Každá relace je definována výčtem dvojic. Dvojice je ohraničená kulatými závorkami, první a druhý prvek dvojice jsou oddělené mezerou. Jednotlivé dvojice jsou oddělené mezerou. Příklad:
</p>
<pre>R (Apple Banana) (Apple Peach) (Apple Apple)</pre>

<h4><span><a class="anchor" name="Příkazy">Příkazy</a></span></h4>

<p>

Každý příkaz je definován na jednom řádku, začíná identifikátorem příkazu a argumenty příkazu jsou oddělené mezerou (od identifikátoru i mezi sebou). Argumenty příkazu jsou číselné identifikátory množin a relací (celá kladná čísla, číslo 1 identifikuje množinu univerza). Příklad:
</p>
<pre>C minus 1 2</pre>

<h3><span><a class="anchor" name="Příkazy_nad_množinami">Příkazy nad množinami</a></span></h3>

<p>

Příkaz pracuje nad množinami a jeho výsledkem je buď množina (v tom případě tiskne množinu ve stejném formátu jako se očekává ve vstupním souboru, tj. začíná "S " a pokračuje mezerou oddělenými prvky) nebo je výsledkem pravdivostní hodnota (v tom případě tiskne true nebo false na samostatný řádek) nebo je výsledkem přirozené číslo (které se tiskne na samostatný řádek).
</p>

<ul>
<li class="level1"><tt>empty A</tt> - tiskne true nebo false podle toho, jestli je množina definovaná na řádku A prázdná nebo neprázdná.</li>
<li class="level1"><tt>card A</tt> - tiskne počet prvků v množině A (definované na řádku A).</li>
<li class="level1"><tt>complement A</tt> - tiskne doplněk množiny A.</li>
<li class="level1"><tt>union A B</tt> - tiskne sjednocení množin A a B.</li>
<li class="level1"><tt>intersect A B</tt> - tiskne průnik množin A a B.</li>
<li class="level1"><tt>minus A B</tt> - tiskne rozdíl množin A \ B.</li>
<li class="level1"><tt>subseteq A B</tt> - tiskne true nebo false podle toho, jestli je množina A podmnožinou množiny B.</li>
<li class="level1"><tt>subset A B</tt> - tiskne true nebo false, jestli je množina A vlastní podmnožina množiny B.</li>
<li class="level1"><tt>equals A B</tt> - tiskne true nebo false, jestli jsou množiny rovny.</li>
</ul>

<h3><span><a class="anchor" name="Příkazy_nad_relacemi">Příkazy nad relacemi</a></span></h3>

<p>

Příkaz pracuje nad relacemi a jeho výsledkem je buď pravdivostní hodnota (tiskne true nebo false), nebo množina (tiskne množinu ve formátu jako ve vstupnímu souboru).
</p>

<ul>
<li class="level1"><tt>reflexive R</tt> - tiskne true nebo false, jestli je relace reflexivní.</li>
<li class="level1"><tt>symmetric R</tt> - tiskne true nebo false, jestli je relace symetrická.</li>
<li class="level1"><tt>antisymmetric R</tt> - tiskne true nebo false, jestli je relace antisymetrická.</li>
<li class="level1"><tt>transitive R</tt> - tiskne true nebo false, jestli je relace tranzitivní.</li>
<li class="level1"><tt>function R</tt> - tiskne true nebo false, jestli je relace R funkcí.</li>
<li class="level1"><tt>domain R</tt> - tiskne definiční obor funkce R (lze aplikovat i na relace - první prvky dvojic).</li>
<li class="level1"><tt>codomain R</tt> - tiskne obor hodnot funkce R (lze aplikovat i na relace - druhé prvky dvojic).</li>
<li class="level1"><tt>injective R <span style="color:red">A B</span></tt> - tiskne true nebo false, jestli je funkce R injektivní. <span style="color:red">A a B jsou množiny; a∈A, b∈B, (a,b)∈R.</span></li>
<li class="level1"><tt>surjective R <span style="color:red">A B</span></tt> - tiskne true nebo false, jestli je funkce R surjektivní. <span style="color:red">A a B jsou množiny; a∈A, b∈B, (a,b)∈R.</span></li>
<li class="level1"><tt>bijective R <span style="color:red">A B</span></tt> - tiskne true nebo false, jestli je funkce R bijektivní. <span style="color:red">A a B jsou množiny; a∈A, b∈B, (a,b)∈R.</span></li>
</ul>

<h3><span><a class="anchor" name="Implementační_detaily">Implementační detaily</a></span></h3>

<ul>
<li class="level1">Maximální podporovaný počet řádků je 1000.</li>
<li class="level1">Na pořadí prvků v množině a v relaci na výstupu nezáleží.</li>
<li class="level1">Všechny prvky množin a v relacích musí patřit do univerza. Pokud se prvek v množině nebo dvojice v relaci opakuje, jedná se o chybu.</li>
</ul>

<h2><span><a class="anchor" name="Příklady_použití">Příklady použití</a></span></h2>
<pre>$ cat sets.txt
U a b c x y z
S a b c x
S x y z
C intersect 2 3
C minus 2 3</pre>
<pre>$ ./setcal sets.txt
U a b c x y z
S a b c x
S x y z
S x
S a b c</pre>
<pre>$ cat rel.txt
U dad mom girl boy man woman
R (dad boy) (dad girl) (mom boy) (mom girl)
R (dad man) (boy man) (mom woman) (girl woman)
C codomain 2
C function 3</pre>
<pre>$ ./setcal rel.txt
U dad mom girl boy man woman
R (dad boy) (dad girl) (mom boy) (mom girl)
R (dad man) (boy man) (mom woman) (girl woman)
S boy girl
true</pre>

<h3><span><a class="anchor" name="Tipy_pro_implementaci">Tipy pro implementaci</a></span></h3>

<ul>
<li class="level1">Vytvořte datový typ pro množinu. Uvažujte předem neznámý počet prvků. Každý prvek (řetězec) by měl být dynamicky alokován.</li>
<li class="level1">Implementujte funkci pro tisk množiny.</li>
<li class="level1">Implementujte funkci pro načtení množiny ze souboru do paměti.</li>
<li class="level1">Vytvořte základní (unární operace) nad množinou.</li>
<li class="level1">Vytvořte datový typ pro načtení více množin. Implementujte další operace nad množinami.</li>
<li class="level1">Vytvořte datový typ pro relaci.</li>
<li class="level1">Vytvořte funkci pro načtení relace ze souboru do paměti.</li>
<li class="level1">Implementujte operace nad relacemi.</li>
</ul>

<h3><span><a class="anchor" name="Neočekávané_chování">Neočekávané chování</a></span></h3>

<p>

Na chyby za běhu programu reagujte obvyklým způsobem: Na neočekávaná vstupní data, formát vstupních dat nebo chyby při zpracování operací reagujte přerušením programu se stručným a výstižným chybovým hlášením na příslušný výstup a odpovídajícím návratovým kódem. Hlášení budou v kódování ASCII česky nebo anglicky. Všechna alokovaná paměť musí být uvolněna a otevřené soubory uzavřené.
</p>

<h2><span><a class="anchor" name="Hodnocení">Hodnocení</a></span></h2>

<p>

Na výsledném hodnocení mají hlavní vliv následující faktory:
</p>

<ol>
<li class="level1">přeložitelnost zdrojového souboru,
<ol>
<li class="level2">zdrojový soubor musí být přeložitelný a běžet na GNU/Linux, například na serveru merlin.fit.vutbr.cz (pozn. Kód má být napsán v jazyku C podle standardu ISO C 99, který má fungovat stejně na všech platformách. Jestliže kód nebude fungovat na stroji merlin, nebude fungovat na spoustě dalších platformách).</li>
</ol>
</li>
<li class="level1">dekompozice problému na podproblémy (vhodné funkce, vhodná délka funkcí a parametry funkcí),</li>
<li class="level1">správná volba datových typů, tvorba nových typů,</li>
<li class="level1">správná funkcionalita (bodové hodnocení rostoucí v následujícím pořadí):
<ol>
<li class="level2">s možným omezením na velikost množin nebo jejich počet (bez dynamické alokace)</li>
<li class="level2">neomezené množiny a relace</li>
<li class="level2">podpora pouze množinových operací</li>
<li class="level2">podpora relací nad množinami</li>
</ol>
</li>
<li class="level1">ošetření chybových stavů.</li>
</ol>

<h2><span><a class="anchor" name="Prémiové_hodnocení">Prémiové hodnocení</a></span></h2>

<p>

Prémiové hodnocení je dobrovolné a lze za něj získat bonusové body. Podmínkou pro udělení prémiových bodů je úspěšná obhajoba projektu a výborné vypracování standardního zadání. Výsledné hodnocení je plně v kompetenci vyučujícího, kterému bude projekt obhajován a který bude projekt hodnotit. Výše prémiových bodů závisí také na sofistikovanosti řešení. Prémiová implementace by měla zahrnovat pokročilé příkazy.
</p>

<h4><span><a class="anchor" name="Pokročilé_příkazy">Pokročilé příkazy</a></span></h4>

<p>

Pokud je výsledkem příkazu relace, tiskne příkaz relaci ve stejném formátu jako ve vstupním souboru (začíná "R ").
</p>

<ul>
<li class="level1"><tt>closure_ref R</tt> - tiskne reflexivní uzávěr relace R</li>
<li class="level1"><tt>closure_sym R</tt> - tiskne symetrický uzávěr relace R</li>
<li class="level1"><tt>closure_trans R</tt> - tiskne tranzitivní uzávěr relace R</li>
<li class="level1">Rozšíření všech příkazů, jejichž výsledkem je množina nebo relace, definuje novou množinu nebo relaci identifikovanou číslem řádku, na kterém se nachází daná operace.</li>
<li class="level1">Rozšíření všech příkazů, které tisknou true nebo false o další argument N. V případě, že operace končí s výsledkem false, následující řádek, který se zpracovává, bude na řádku N (nikoliv bezprostředně následující). </li>
<li class="level1"><tt>select A N</tt> - vybere náhodný prvek z množiny nebo relace A a tiskne ho. V případě, že je množina A prázdná, přeskočí vykonávání příkazu na řádek N vstupního souboru. N v takovém případě musí označovat existující řádek ve vstupním souboru.</li>
</ul>


