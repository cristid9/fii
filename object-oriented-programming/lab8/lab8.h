#ifndef LAB8_H__
#define LAB8_H__

#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <stdexcept>

using namespace std;

class Compare
{
    public:
        virtual int CompareElements(void* e1, void* e2) = 0;
};

template<class T>
class Array;

template<class T>
class ArrayIterator
{
    private:
        T** Current; 

    public:
        ArrayIterator(T** contReference);
        ArrayIterator& operator ++ ();
        ArrayIterator& operator -- ();
        bool operator= (ArrayIterator<T> &);
        bool operator!=(ArrayIterator<T> &);
        T* GetElement();
};

template<class T>
class Array
{
    private:
        T** List; // lista cu pointeri la obiecte de tipul T*

        int Capacity; // dimensiunea listei de pointeri

        int Size; // cate elemente sunt in lista

        // int _BinarySearch(const T& elem); 
    public:
        Array(); // Lista nu e alocata, Capacity si Size = 0
        ~Array(); // destructor
        Array(int capacity); // Lista e alocata cu 'capacity' elemente
        Array(const Array<T> &otherArray); // constructor de copiere


        T& operator[] (int index) const; // arunca exceptie daca index este out of range

        // adauga un element de tipul T la sfarsitul listei si returneaza this
        const Array<T>& operator+=(const T &newElem);        
        
        // adauga un element pe pozitia index, retureaza this. Daca index e invalid arunca o exceptie
        const Array<T>& Insert(int index, const T &newElem);         
        
        // adauga o lista pe pozitia index, retureaza this. Daca index e invalid arunca o exceptie
        const Array<T>& Insert(int index, const Array<T> otherArray);         
        
        // sterge un element de pe pozitia index, returneaza this. Daca index e invalid arunca o exceptie
        const Array<T>& Delete(int index);     
        
        bool operator=(const Array<T> &otherArray);

        // Aici trebuia sa implementez niste functii de sortare si cautare
        // dar cum nu asta era scopul laboratorului, n-am mai facut asta.
        
        int GetSize(); 
        int GetCapacity();
        
        ArrayIterator<T> GetBeginIterator();
        ArrayIterator<T> GetEndIterator();
};

template<class T>
class Comp : public Compare
{
    public:
        int CompareElements(void* e1, void* e2)
        {
            T* elem1 = (T*)e1;
            T* elem2 = (T*)e2;

            if (elem1 == elem2)
                return 0;

            return (elem1 < elem2) ? -1 : +1;
        }   
};

template <class T>
ArrayIterator<T>::ArrayIterator(T** baseIt) 
{
    Current = baseIt;
}

template <class T>
ArrayIterator<T>& ArrayIterator<T>::operator++()
{
    Current++;
    return *this;
}

template <class T>
ArrayIterator<T>& ArrayIterator<T>::operator--()
{
    Current--;
    return *this;
}

template <class T>
bool ArrayIterator<T>::operator= (ArrayIterator<T> &val)
{
    Current = val.Current;
    return true; // wtf? why do I even need a return value here?
}

template <class T>
bool ArrayIterator<T>::operator!=(ArrayIterator<T> &compVal)
{
    if (Current == compVal.Current)
        return false;
    return true;
}

template <class T>
T*  ArrayIterator<T>::GetElement()
{
    return *Current;
}

template <class T>
Array<T>::Array() // Lista nu e alocata, Capacity si Size = 0
{
    Capacity = 0;
    Size     = 0;
}

template <class T>
Array<T>::~Array() // destructor
{
    if (Capacity != 0)
        delete [] List;
}

template <class T>
Array<T>::Array(int capacity) // Lista e alocata cu 'capacity' elemente
{
    List     = new T*[capacity];
    Capacity = capacity;
    Size     = 0;
}

template <class T>
Array<T>::Array(const Array<T> &otherArray) // constructor de copiere
{
    Capacity = otherArray.Capacity;
    List     = new T*[Capacity];
    Size     = otherArray.Size;

    memcpy(List, otherArray.List, sizeof(T*) * otherArray.Size);   
}

// arunca exceptie daca index este out of range
template <class T>
T& Array<T>::operator[] (int index) const
{
    if (index < 0 || index >= Size)
        throw new range_error("Invalid index");

    return *(List[index]);   
}

// adauga un element de tipul T la sfarsitul listei si returneaza this
template <class T>
const Array<T>& Array<T>::operator+=(const T &newElem)
{
   if (Size == Capacity) 
       throw new length_error("Not enough space");

   List[Size] = (T *)&newElem;
   Size++;
   return *this;
}


// adauga un element pe pozitia index, retureaza this. Daca index e invalid 
// arunca o exceptie
template <class T>
const Array<T>& Array<T>::Insert(int index, const T &newElem) 
{
    if (index < 0 || index >= Capacity) 
        throw new range_error("Error at insertion");

    for (int idx = Size; idx >= index; idx--)
    {
        List[idx] = List[idx - 1];
    }

    List[index] = (T *)&newElem;
    Size++;

    return *this;
}

// adauga o lista pe pozitia index, retureaza this. Daca index e invalid 
// arunca o exceptie
template <class T>
const Array<T>& Array<T>::Insert(int index, const Array<T> otherArray)
{
    if (index < 0 || index >= Capacity)
        throw new range_error("Invalid range");
    
    if (Capacity < index + otherArray.Size)
        throw new length_error("Not enough storage");

    for (int idx = index + otherArray.Size - 1; idx >= index; idx--)
    {
        List[idx] = List[idx - index];
    }

    for (int idx = index; idx < index + otherArray.Size; idx++)
    {
        List[idx] = &(otherArray[idx - index]);
    }


    Size += otherArray.Size; 
    
    return *this;
}

// sterge un element de pe pozitia index, returneaza this. Daca index e invalid arunca o exceptie
template <class T>
const Array<T>& Array<T>::Delete(int index) 
{
    if (index < 0 || index >= Size)
        throw new range_error("Index not in range");

    for (int idx = index; idx < Size - 1; idx++)
    {
        List[idx] = List[idx + 1];
    }

    return *this;
}

template <class T>
bool Array<T>::operator=(const Array<T> &otherArray)
{
    if (otherArray.Size > Capacity)
        throw new length_error("Not enough storage");

    for (int idx = 0; idx < otherArray.Size; idx++)
    {
        List[idx] = &otherArray[idx];
    }

    Size = otherArray.Size;

    return true;
}

template <class T>
int Array<T>::GetSize()
{
    return Size;
}

template <class T>
int Array<T>::GetCapacity()
{
    return Capacity;
}

template <class T>
ArrayIterator<T> Array<T>::GetBeginIterator()
{
    return ArrayIterator<T>(List);
}

template <class T>
ArrayIterator<T> Array<T>::GetEndIterator()
{
    return ArrayIterator<T>(List + Size - 1);
}

#endif
