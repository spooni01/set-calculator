Pre spustenie testu zadaj:
python ./test/test.py setcal.c

Pre kompiláciu programu "gcc -std=c99 -Wall -Wextra -Werror setcal.c -o setcal" zadaj:
./gcc/make

JAK FUNGUJOU DATOVE TYPY

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

