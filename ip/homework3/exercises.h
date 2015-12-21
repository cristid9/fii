#ifndef exercises_h
#define exercises_h

/*
Fisierul header pentru tema 3

Pentru orice nelamurire legata de enunt,
va rugam sa trimiteti un email profesorului de laborator.
*/
#include <cstring>
#include <fstream>
#include <string>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <sstream>


using namespace std;                                                                                                                              


// problema 0
//
// compara continutul a doua fisiere, daca este identic returneaza 0, daca este diferit returneaza 1
// continutul fisierelor este binar, adica orice tip de fisier, nu neaparat text ASCII.
//
int compare_files(const char *input_file_1, const char *input_file_2);


// problema 1
// Vocalele sunt 'doar' cele clasice: ('a', 'e','i', 'o', 'u', 'A', 'E', 'I', 'O', 'U')
// Consoanele sunt tot doar cele clasice, cele din intervalele ['a' - 'z'] ['A' - 'Z']
//
// Nu se ia in considerare encoding-ul pentru fisierul de intrare (e.g. UTF-8, latin1, UTF-16, etc)
// Fisierul de intrare se considera o secventa de bytes, fiecare byte avand 8 biti.
// Printre acesti bytes poate fi orice 'caracter', inclusiv caracterul NULL, oriunde in fisier.
// Size-ul fisierelor de intrare poate depasi 1MB dar nu poate depasi 1GB.
//
// Cand fisierul de intrare nu poate fi citit, programul
// nu trebuie sa dea eroare sau sa intre in bucla infinita,
// trebuie sa scrie ca a gasit 0 vocale si 0 consoane.
//
// Format-ul pentru fisierul de iesire:
// <nr_vocale>|<nr_consoane>, e.g. "213|1234".
// fara alte caractere la sfarsit de linie.
//	
void problema1(const char *input_file_name, const char *output_file_name);


/*
Problema 2

Să se scrie o functie C++ care să determine numărul de semne de punctuatie si numărul de cuvinte
dintr-un fisier dat

Fisierul de intrare: 
 * va contine o serie de paragrafe
 * paragrafele nu sunt neaparat lipite (pot exista si linii goale, continand doar caracterul \n sau/si spatiu).
 * fisierul se va incheia cu un ultim newline.
 * semne de punctuatie ce vor fi luate in calcul:  .  ,  -  ;  :  '  "  (  )  ...  ?  !

Fisierul de iesire:
 * va contine 2 linii
 * pe prima linie va fi numarul de cuvinte
 * pe a doua linie va fi numarul semnelor de punctuatie
 * fiecare linie se va finaliza cu caracterul \n


*/
void problema2(const char *input_file_name, const char *output_file_name);


/*
Problema 3

Pentru un fisier de intrare si unul de iesire date, sa se scrie in fisierul de iesire lista tuturor cuvintelor care apar in fisierul de intrare, ordonate lexicografic, fiecare pe
cate un rand in care, separat prin ”***”, se va indica si frecventa de aparitie a cuvantului respectiv.

Exemplu:

Fisier intrare:
__________________________________________
Ana are doua mere, unul verde si unul rosu.
Ciresel nu vrea nici unul din cele doua mere, el vrea unul galben.
__________________________________________

Fisier iesire:
__________________________________________
Ana***1
Ciresel***1
are***1
cele***1
din***1
doua***2
el***1
galben***1
mere***2
nici***1
nu***1
rosu***1
si***1
unul***4
verde***1
vrea***2
__________________________________________


Important!!!
- literele mari (majuscule) sunt mai mici lexicografic ca literele mici (asa este by default)
- cuvintele care sunt la inceput de propozitie si incep cu litera mare sunt numerotate separat de apartiile lor in text 
(ex, "El" si "el" vor fi numerotate separat)
- fisierul NU va contine cuvinte separate prin cratima (ex: n-am, intr-un, etc.)
- fisierul poate contine doar urmatorele semne de punctuatie: ,.?!:;
- atentie la extragerea cuvintelor din text:
	-  poate contine mai multe spatii adiacente
	-  poate contine linii goale
	-  semnele de punctuatie pot fi separate de spatii: ex. "Atentie!" sau "Atentie !"
	-  semnele de punctuatie pot fi in grupuri: ex. "...", "!?"

*/

void problema3(const char *input_file_name, const char *output_file_name);




/*
Problema 4

Pentru un fisier de intrare dat, si un numãr de caractere N, sã se determine cel mai periculos punct al sirului
circular format prin concatenarea primelor N caractere alfanumerice din fisierul de intrare.


In sirul a0,a1,a2,...,aN spunem cã punctul i este mai periculos decat punctul j dacã sirul care incepe cu pozitia i

i: ai,ai+1,...,aN,a0,a1,a2,...,ai-1 

este mai mic lexicografic decat sirul care incepe cu pozitia j

j: aj,aj+1,...,aN,a0,a1,a2,...,aj-1.


Exemplu punct punct periculor:

Pentru sirul: autocar
Avem urmatorele subsiruri circulare: autocar, utocara, tocarau, ocaraut, carauto, arautoc, rautoca
Punctul cel mai periculos este 5 deoarce subsirul care incepe de la pozitia respectiva (arautoc) este cel mai mic lexicografic.

Exemplu input: (fisier_intrare, 15)

Fisier intrare:
___________________
ana are 15 mere
ciresel vine si cere
___________________

Functia va returna: 6 (de la pozitia 6 incepe cel mai periculos subsir "15mereciranaare")

Important!!!
- numerotarea in fisier incepe de la pozitia 0
- se iau in considerare doare primele N carctere alfanumerice, celelalte sunt ignorate (spatii, newline, semne de punctuatie, etc.)
- in cazul in care in fisier nu sunt N carcatere alfanumerice se vor citi cate sunt
- daca fisierul nu contine niciun caracter alfanumeric se va returna -1

*/

int problema4(const char *input_file_name, int N);




//	problema 5
//	Primul cuvant se gaseste pe prima linie din fisierul de intrare.
//	Al doilea cuvant se gaseste pe a doua linie din fisierul de intrare.
//	In fisierul de iesire, sirurile care indeplinesc proprietatea din enunt se vor gasi fiecare pe cate o linie incepand cu prima.
//	Cuvintele vor contine doar litere mici din alfabetul englez. ([a - z])
//	"Sufix" reprezinta un subsir nevid ramas prin eliminarea a 0 sau mai multe litere aflate pe pozitii consecutive incepand cu prima litera.
//	"Prefix" reprezinta un subsir nevid ramas prin eliminarea a 0 sau mai multe litere aflate pe pozitii consecutive incepand cu ultima litera.
//
//	Exemplu:
//
//	fisier de intrare:

//	fetele
//	elefant

//	fisier de iesire:

//	ele
//	e

//	Dacă nu există astfel de sufixe, se afiseaza valoarea 0.
//  Tot timpul va fi un '\n' folosit pentru sfarsit de linie, ultima linie din fisier are doar un '\n'.

void problema5(const char *input_file_name, const char *output_file_name);


/**
 * Functia rimes face parte din problema 6
 *
 * Completati codul pentru aceasta functie astfel incat sa returneze true daca cele doua cuvinte rimeaza
 * si false altfel.
 * Spunem ca doua cuvinte rimeaza daca ultimele n litere coincid.
 * Aceasta functie va returna false in cazul in care un cuvant este mai scurt de n litere si celalalt nu.
 * Ex: gigel, angel, n = 3 => functia returneaza true
 * au, bau, n = 3 => functia returneaza false
 * au, bau, n = 2 => functia returneaza true
 */
bool rimes(char* first_word, char* second_word, int n);

/**
 * Completati aceasta functie astfel incat sa citeasca din fisierul de intrare parametrul n (necesar functiei de mai sus)
 * si o catrena, si scrie in fisierul de iesire litera corespunzatoare rimei catrenei.
 * Rima impercheata: A -> (a, a, b, b)
 * Rima incrusicata: B -> (a, b, a, b)
 * Rima imbratisata: C -> (a, b, b, a)
 * Rima inbratisata: D -> (a, a, a, a)
 * Rima alba: E -> in cazul in care niciuna din rimele de mai sus nu se potriveste.
 *
 * Fisierul de intrare va avea urmatorul format:
 * Pe prima linie se afla numarul natural n (1 <= n <= 5)
 * Pe urmatoarele 4 linii se afla versurile catrenei. Fiecare vers poate avea maxim 100 de caractere. Cuvintele din versuri
 * vor fi separate prin urmatorii separatori: .(Punct) ,(Virgula) !(Semnul exclamarii) ?(Semnul intrebarii)  (Spatiu)
 *
 * Fisierul de iesire va avea urmatorul format:
 * Pe prima linie se va scrie caracterul corespunzator tipului de rima urmat de caracterul NEWLINE (\n).
 *
 * Atentie: Nu uitati de caracterul NEWLINE de la finalul fisierului de iesire.
 * Fisierul de intrare contine litere mici din alfabetul englez, litere mari din alfabetul englez si separatorii mentionati mai sus.
 */
void problema6(const char *input_file, const char *output_file);



/*
 Problema 7
 
 Sa se scrie o functie C++ care primeste 2 cuvinte si determina daca acestea sunt anagrame.
 Doua cuvinte se numesc anagrame daca au acelasi litere dar in alta ordine.
 Exemplul 1: rac, arc, car
 Exemplul 2: mama, amma, maam
 
 Sa se determine daca intr-un fisier de intrare dat exista anagrame, caz in care se vor returna intr-un fisier de iesire, in urmatorul format:
	- grupurile de anagrame relative (formate cu aceleasi litere) in ordine descrescatoare a lungimii acestora (numarul de cuvinte din grup)
	- pe un rand se vor afisa toate anagramele unui grup ordonate lexicografic si separate printr-un spatiu
	- daca doua grupuri de anagrame au aceeasi lungime (acelasi numar de cuvinte) se vor ordona lexicografic dupa primul cuvant din grup
 
 Exemplu:
 
 Input:
 -----------------------
 rac arc car
 mama are mere amam
 erem
 
 era
 
 a b c d e f g
 
 ab ba
 
 cd
 dc
 ab
 -----------------------
 Output:
 ab ab ba     | ambele au cate 3 cuvinte in grup
 arc car rac  | dar "ab" este mai mic lexicografic ca "arc"
 amam mama
 are era
 cd dc
 erem mere
 a            | toate au cate un singur cuvant in grup
 b            | deci se ordoneaza lexicografic dupa primul cuvant din grup
 c            |
 d            |
 e            |
 f            |
 g            |
 -----------------------
 */

void problema7(const char *input_file_name, const char *output_file_name);


#endif /* exercises_h */
