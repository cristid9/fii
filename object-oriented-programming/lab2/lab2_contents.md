Concepte
========
    * incapsulare
    * suprainacarcare 
    * suprascriere (strans legata de polimorfism)    
    * abstractizare (!)
    * modificatori de access:
        - `private`
        - `public`
        - `protected` (vedem mai multe cand ajungem la polimorfism)
    * `this` - pointer la instanta curenta

Snippets
========
    

```cpp
    // Nume.h
    class Nume {
     
        private:
            int v[100]; // va avea o valoare random pt. ca e o 
                        // locatie de pe stiva ce a fost reciclata.
            char x;
            int q;
        
        public:
            // exemplu de supraincarcare
            Nume(); // constructor implicit
            Nume(char e) {...}// constructor explicit
            ~Nume(); // destructor
            int Reset(int *value); // interfata intre lumea exterioara si clasa
    };

 ```

(bad practice)
```cpp
    Nume n;
    n.q = 5;
```

* format de implementare a metodelor
```cpp
    int Nume::Reset(int* value) {
        v[0] = 5;
        this->v[0] = 5;
    }

```
* format de implementare a constructorilor/destructorilor
```cpp
    Nume::Nume() { ... }
    Nume::Nume(char q) { ... }
    Nume::~Nume() { ... }
```
* 

Explicatii
==========
    * constructorii si destrucorii nu au return type 
    * separarea interfetei de implementare
    *

Snippets
========
