class IntList {

    private:

        int Elements[1000];

        int Count;

    public:

        IntList(); // Constructor implicit

        bool Add(int element); // returneaza false daca lista este plina (s-au adaugat 1000 de elemente)

        bool Insert(int index,int element);

        bool Delete(int index);

        void Clear();

        int  IndexOf(int valoare, int startPosition); // indexul pozitiei unei valori sau "-1" in caz contrar

        void RemoveDuplicates();

        void Intersection(IntList* withList,IntList * resultList);

        void Reunion(IntList* withList,IntList * resultList);

        void Sort();

        void Reverse();

        int  Get(int index); // returneaza elementul de pe pozitia index sau -1 in caz contrar

        int  GetCount();
};
