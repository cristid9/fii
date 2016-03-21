#include <stack>
#include <queue>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <iostream>
#include <vector>
#include <deque>
#include "lab6.h"

#define WORD_SIZE 100

using namespace std;

const char* getLongestWord(vector<const char *> words)
{
    int maxSize = strlen(words[0]);
    const char* ptrMax = words[0];
    for (auto it = words.begin(); it != words.end(); it++)
    {
        if (strlen(*it) > maxSize)
        {
            maxSize = strlen(*it);
            ptrMax = *it;
        }
    }

    return ptrMax;
}

static size_t countVowels(const char *str)
{
    size_t vowels= 0;
    while (*str != '\0')
    {
        if (strchr("aeiou", *str) != NULL)
            vowels++;
        str++;
    }

    return vowels;
}

size_t countWordsWith4Vowels(vector<const char *> words)
{
    size_t counter = 0;
    for (auto it = words.begin(); it != words.end(); it++)
    {
        size_t vowels = countVowels(*it);
        if (vowels > 4)
            counter++;
    }

    return counter;
}

deque<const char *> buildDeque(vector<const char *> words)
{
    deque<const char *> dq;
    for (auto it = words.begin(); it != words.end(); it++)
    {
        if (strchr("aeiou", (*it)[0]) == NULL)
            dq.push_back(*it);
    }

    return dq;
}

vector<const char *> eraseWords(vector<const char *> words, int limit)
{
    for (auto it = words.begin(); it != words.end(); it++)
    {
        if (strlen(*it) > limit)
        {
            words.erase(it);
            it--;
        }
    }

    return words;
}

class Comp
{
public:
    bool operator()(const char *str1, const char *str2)
    {
        return (strcmp(str1, str2) == 0);
    }
};

priority_queue<const char *, vector<const char *>, Comp>
buildPQ(vector<const char *> words)
{
    priority_queue<const char *, vector<const char *>, Comp> pq;
    for (auto it = words.begin(); it != words.end(); it++)
    {
        pq.push(*it);
    }

    return pq;
}

vector<const char *> buildReversed(vector<const char *> words)
{
    stack<const char *> st;
    for (auto it = words.begin(); it != words.end(); it++)
    {
        st.push(*it);
    }

    vector<const char *> reversed;
    while (!st.empty())
    {
        reversed.push_back(st.top());
        st.pop();
    }

    return reversed;
}

void printVector(vector<const char *> words)
{
    for (auto it = words.begin(); it != words.end(); it++)
    {
        printf("%s", *it);
    }
}

int main()
{
    FILE *handle = fopen("input.in", "r");

    vector<const char *> words;

    while (!feof(handle))
    {
        char *tmp = new char[WORD_SIZE];

        fgets(tmp, WORD_SIZE, handle);
        
        words.push_back(tmp);
    }
    
    printf("%d\n", countWordsWith4Vowels(words));

    deque<const char *> dq = buildDeque(words);

    vector<const char *> filtered = eraseWords(words, 3);

    // printVector(filtered);

    priority_queue<const char *, vector<const char *>, Comp> pq = buildPQ(words);

    while (!pq.empty())
    {
        printf("%s\n", pq.top());
        pq.pop();
    }

    vector<const char *> reversed = buildReversed(words);
    printVector(reversed);

    // release the memory now
    for (auto it = words.begin(); it != words.end(); it++)
    {
        delete *it;
    }

    fclose(handle);

    return 0;
}
