#include "exercises.h"

int compare_files(const char *input_file_1, const char *input_file_2)
{
    ifstream file1;
    ifstream file2;

    file1.open(input_file_1, ios::binary | ios::in | ios::ate);
    file2.open(input_file_2, ios::binary | ios::in | ios::ate);

    streamsize file_size = file1.tellg();
    if (file_size != file2.tellg())
        return 0;

    file1.seekg(0, ios::beg);
    file2.seekg(0, ios::beg);

    while (file_size--)
    {
        char file_1_byte;
        char file_2_byte;

        file1.read(&file_1_byte, 1);
        file2.read(&file_2_byte, 1);

        if (file_1_byte != file_2_byte)
            return 0;
    }

    file1.close();
    file2.close();

    return 1;
}

static bool isVowel(char c)
{
    c = tolower(c);
    if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u')
        return true;
    return false;
}

void problema1(const char *input_file_name, const char *output_file_name)
{
    ifstream in(input_file_name);

    int vows = 0;
    int cons = 0;

    char c;

    while (in.get(c))
    {
        if (isalpha(c))
        {
            if (isVowel(c))
            {
                vows++;
            }
            else
            {
                cons++;
            }
        }
     }

     in.close();

     ofstream out(output_file_name);
     out << vows << "|" << cons;
     out.close();
}


// %todo% Find a good solution for tokenization
static bool isPunctuationMark(char c)
{
    switch (c)
    {
        case '?':
        case '!':
        case '.':
        case ',':
        case ';':
        case ':':
        case '"':
        case '\'':
        case '(':
        case ')':
        case '-':
            return true;
        default:
            return false;
    }
}

void problema2(const char *input_file_name, const char *output_file_name)
{
    ifstream in(input_file_name);

    int words        = 0;
    int marks        = 0;
    bool inside_word = false;
    char c;

    while (in.get(c))
    {
        if (isalpha(c) && !inside_word)
        {
            inside_word = true;
            words++;
            continue;
        }
        else if (!isalpha(c) && inside_word)
        {
            inside_word = false;
        }

        // This means that it could possibly be a punctuation mark.
        int second = in.get();
        int third  = in.get();

        if (c == '.'
            && second != EOF && second == '.'
            && third != EOF && third == '.')
        {
            // This means we have ...
            marks++;
            continue;
        }

        // Decrease the position in the file.
        in.unget();
        in.unget();

        if (isPunctuationMark(c))
        {
            marks++;
        }
    }

    in.close();

    ofstream out(output_file_name);
    out << words << endl;
    out << marks << endl;
    out.close();
}

void problema3(const char *input_file_name, const char *output_file_name)
{
    ifstream in(input_file_name);

    map<string, int> words;
    char c;
    bool inWord      = false;
    string word = "";

    while (in.get(c))
    {
        if (isalpha(c) && !inWord)
        {
            inWord = true;
            word   = "";
        }
        else if(!isalpha(c) && inWord)
        {
            inWord = false;
            if (words.find(word) != words.end())
            {
                words[word]++;
            }
            else
            {
                words[word] = 1;
            }
        }

        if (inWord)
        {
            word += c;
        }
    }

    if (inWord)
    {
        if (words.find(word) != words.end())
        {
            words[word]++;
        }
        else
        {
            words[word] = 1;
        }    
    }
    in.close();

    ofstream out(output_file_name);

    for (map<string, int>::iterator it = words.begin(); it != words.end(); 
         it++)
    {
        out << it->first << "***" << it->second << endl;
    }

    out.close();
}

static int _findDangerousPoint(string s)
{
    if (s.size() == 0)
        return -1;

    string tmp = s;

    string minForm = s;
    int minFormPos = 0;

    for (string::size_type i = 0; i < s.size(); i++)
    {
        string si = tmp;
        rotate(si.begin(), si.begin() + i, si.end());
        if (minForm.compare(si) > 0)
        {
            minForm    = si;
            minFormPos = i;
        }
    }

    return minFormPos;
}

static string getFileContent(ifstream& file, int limit)
{
    char c;
    string result = "";
    while (file >> c && limit >= 0)
    {
        if (isalnum(c))
        {
            result += c;
            limit--;
        }
    }

    return result;
}

int problema4(const char *input_file_name, int N)
{
    ifstream file(input_file_name);
    string content = getFileContent(file, N);
    file.close();

    return _findDangerousPoint(content);
}

void problema5(const char *input_file_name, const char *output_file_name)
{
    ifstream in(input_file_name);
    string word1;
    string word2;

    in >> word1;
    in >> word2;

    string prefix = "";
    vector<std::string> validPrefixes;

    for (string::reverse_iterator it = word1.rbegin(); it != word1.rend(); it++)
    {
        prefix.insert(0, 1, *it);
        if (!word2.compare(0, prefix.size(), prefix))
        {
            validPrefixes.push_back(prefix);
        }
    }

    in.close();
    ofstream out(output_file_name);

    if (validPrefixes.size() == 0)
        out << "0" << endl;

    for (vector<string>::reverse_iterator it = validPrefixes.rbegin();
        it != validPrefixes.rend(); it++)
    {
        out << (*it) << endl;
    }
    out.close();
}

bool rimes(char* first_word, char* second_word, int n)
{
    int word1_size = strlen(first_word);
    int word2_size = strlen(second_word);

    if (word1_size < n || word2_size < n)
        return false;

    word1_size--;
    word2_size--;

    while (first_word[word1_size] == second_word[word2_size] && n--)
    {
        word1_size--;
        word2_size--;
    }

    if (n > 0)
        return false;
    return true;
}

static char* last_word(char* verse)
{
    int len = strlen(verse);
    char* last = new char[101];
    char* beg = last;
    bool in_word = false;

    for (len--; len >= 0; len--)
    {
        if (isalpha(verse[len]) && !in_word)
        {
            in_word = true;
        }

        if (!isalpha(verse[len]) && in_word)
            break;

        if (in_word)
        {
            *last = verse[len];
            last++;
        }
    }
    *last = '\0';
    last--;

    for (char* tmp = beg; tmp <= last; tmp++, last--)
    {
        swap(*tmp, *last);
    }

    return beg;
}

void problema6(const char *input_file, const char *output_file)
{
    ifstream in(input_file);

    int n;
    in >> n;
    in.get(); // get rid of the '\n'
    char tmp[101];
    vector<char*> last_words;

    for (int i = 0; i < 4; i++)
    {
        in.getline(tmp, 101);
        last_words.push_back(last_word(tmp));
    }
    in.close();

    ofstream out(output_file);

    if (rimes(last_words[0], last_words[1], n)
        && rimes(last_words[0], last_words[2], n)
        && rimes(last_words[0], last_words[3], n))
    {
        out << "D" << endl;
    }
    else if (rimes(last_words[0], last_words[1], n)
        && rimes(last_words[2], last_words[3], n))
    {
        out << "A" << endl;
    }
    else if (rimes(last_words[0], last_words[2], n)
             && rimes(last_words[1], last_words[3], n))
    {
        out << "B" << endl;
    }
    else if (rimes(last_words[0], last_words[3], n)
             && rimes(last_words[1], last_words[2], n))
    {
        out << "C" << endl;
    }
    else
    {
        out << "E" << endl;
    }

    for(vector<char*>::iterator it = last_words.begin(); it != last_words.end();
        it++)
    {
        delete *it;
    }

    out.close();
}

static vector<string> getWords(ifstream& file)
{
    bool inWord = false;
    char c;
    string word = "";
    vector<string> words;

    while (file.get(c))
    {
        if (isalpha(c) && !inWord)
        {
            inWord = true;
            word   = "";
        }
        else if (!isalpha(c) && inWord)
        {
            inWord = false;
            words.push_back(word);
        }

        if (inWord)
        {
            word += c;
        }
    }

    if (isalpha(c) && !inWord)
    {
        inWord = true;
        word   = "";
    }
    else if (!isalpha(c) && inWord)
    {
        inWord = false;
        words.push_back(word);
    }

    return words;
}

struct Cmp
{
    bool operator()(const vector<string>& lhs, const vector<string>& rhs)
    {
        if (lhs.size() > rhs.size())
        {
            return true;
        }
        else if (lhs.size() == rhs.size() && lhs[0].compare(rhs[0]) < 0)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
} cmp;

void problema7(const char *input_file_name, const char *output_file_name)
{
    ifstream in(input_file_name);
    vector<string> words = getWords(in);
    in.close();
    map<string, vector<string> > table;

    for (vector<string>::size_type i = 0; i < words.size(); i++)
    {
        string key = words[i];
        sort(key.begin(), key.end());
        table[key].push_back(words[i]);
    }

    ofstream out(output_file_name);

    vector<vector<string> > result;
    for (map<string, vector<string> >::iterator it = table.begin();
         it != table.end(); it++)
    {
        sort(it->second.begin(), it->second.end());
        result.push_back(it->second);
    }

    sort(result.begin(), result.end(), cmp);

    for (vector<vector<string> >::iterator it = result.begin();
         it != result.end(); it++)
    {
        for (vector<string>::iterator it2 = it->begin(); it2 != it->end();
             it2++)
        {
            out << *it2 << " ";
        }
        out << endl;
    }

    out.close();
}
