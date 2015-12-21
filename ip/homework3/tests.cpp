#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Homework3
#include <boost/test/unit_test.hpp>
#include "exercises.h"

BOOST_AUTO_TEST_CASE(test1_compare_files)
{
    BOOST_CHECK(compare_files("test_files/pr0/test_image1.jpeg",
                              "test_files/pr0/test_image2.jpeg") == 1);

    BOOST_CHECK(compare_files("test_files/pr0/test_image1.jpeg",
                              "test_files/pr0/test_image3.jpeg") == 0);

    BOOST_CHECK(compare_files("test_files/pr0/test_image1.jpeg",
                              "test_files/pr0/test_doc1.txt") == 0);

    BOOST_CHECK(compare_files("test_files/pr0/test_doc1.txt",
                              "test_files/pr0/test_doc2.txt") == 1);
}

BOOST_AUTO_TEST_CASE(test_problem1)
{
    char results[][10] = {"8|7", "6|6", "11|16", "21|21", "19|55", "190|295",
                          "0|0"};
    for (int i = 1; i <= 7; i++)
    {
        stringstream in_file;
        in_file << "test_files/pr1/test" << i << ".in";

        stringstream out_file;
        out_file << "test_files/pr1/test" << i << ".out";

        problema1(in_file.str().c_str(), out_file.str().c_str());
        ifstream in(out_file.str().c_str());
        string expected;
        in >> expected;
        in.close();

        BOOST_CHECK(expected == results[i - 1]);
    }
}

BOOST_AUTO_TEST_CASE(test_problem2)
{
    ifstream in;
    int expected[][2] = {{128, 12}, {19, 5}, {3, 9}, {0, 60}, {10, 5},
                         {137, 25}, {0, 0}};

    for (int i = 1; i <= 6; i++)
    {
        stringstream in_file;
        in_file << "test_files/pr2/test" << i << ".in";

        stringstream out_file;
        out_file << "test_files/pr2/test" << i << ".out";

        problema2(in_file.str().c_str(), out_file.str().c_str());
        in.open(out_file.str().c_str());
        int words;
        int marks;

        in >> words;
        in >> marks;
        in.close();

        BOOST_CHECK(words == expected[i - 1][0] && marks == expected[i - 1][1]);
    }
}

BOOST_AUTO_TEST_CASE(test_problem3)
{

    char words[][100][100] =
    {
        {
            "Ana***1",
            "Ciresel***1",
            "are***1",
            "cele***1",
            "din***1",
            "doua***2",
            "el***1",
            "galben***1",
            "mere***2",
            "nici***1",
            "nu***1",
            "rosu***1",
            "si***1",
            "unul***4",
            "verde***1",
            "vrea***2"
        },
        {
            "AB***1",
            "Ab***1",
            "aB***1",
            "ab***5",
        },
        {
            "Arm***1",
            "Milky***1",
            "Oort***1",
            "Orion***1",
            "Solar***1",
            "Sun***1",
            "System***1",
            "The***4",
            "Way***1",
            "a***4",
            "also***1",
            "as***1",
            "at***2",
            "be***1",
            "believed***1",
            "bubble***1",
            "center***1",
            "charged***1",
            "cloud***1",
            "comets***1",
            "creates***1",
            "disc***1",
            "distance***1",
            "edge***1",
            "equal***1",
            "exist***1",
            "extends***1",
            "flowing***1",
            "for***1",
            "from***3",
            "further***1",
            "heliopause***1",
            "heliosphere***2",
            "in***2",
            "interstellar***2",
            "is***4",
            "it***1",
            "known***1",
            "light***1",
            "like***1",
            "located***1",
            "long***1",
            "may***1",
            "medium***1",
            "of***4",
            "opposing***1",
            "out***1",
            "outwards***1",
            "particles***1",
            "period***1",
            "point***1",
            "pressure***2",
            "region***1",
            "roughly***1",
            "scattered***1",
            "solar***2",
            "source***1",
            "stream***1",
            "than***1",
            "the***13",
            "thousand***1",
            "times***1",
            "to***3",
            "which***2",
            "wind***3",
            "years***1",
        },
        {
        }
    };

    ifstream in;
    string entry;

    for (int i = 1; i <= 4; i++)
    {
        stringstream in_file;
        in_file << "test_files/pr3/test" << i << ".in";

        stringstream out_file;
        out_file << "test_files/pr3/test" << i << ".out";

        problema3(in_file.str().c_str(), out_file.str().c_str());
        in.open(out_file.str().c_str());
        for (int j = 0; in >> entry; j++)
        {
            BOOST_CHECK(!strcmp(entry.c_str(), words[i - 1][j]));
        }
    }
}

BOOST_AUTO_TEST_CASE(test_problem4)
{
    int results[] = {6, -1, 14, 10, 0, -1};
    int ns[]      = {15, 15, 15, 15, 7, 15};

    for (int i = 1; i <= 6; i++)
    {
        stringstream in_file;
        in_file << "test_files/pr4/test" << i << ".in";
        BOOST_CHECK(problema4(in_file.str().c_str(),
                    ns[i - 1]) == results[i - 1]);
    }
}

BOOST_AUTO_TEST_CASE(test_problem5)
{
    char expected[][100][100] =
    {
        {"ele", "e"},
        {"0"},
        {"3AVEMa"},
        {"121212", "1212", "12"},
        {"jkawebfgsdkgfasotbjgsg"},
        {"0"}
    };
    ifstream in;

    for (int i = 1; i <= 6; i++)
    {
        stringstream in_file;
        in_file << "test_files/pr5/test" << i << ".in";

        stringstream out_file;  
        out_file << "test_files/pr5/test" << i << ".out";

        problema5(in_file.str().c_str(), out_file.str().c_str());
        in.open(out_file.str().c_str());

        string entry;
        for (int j = 0; in >> entry; j++)
        {
            BOOST_CHECK(entry == expected[i - 1][j]);
        }
        in.close();
    }
}

BOOST_AUTO_TEST_CASE(test_rimes)
{
    char s1[] = "gigel";
    char s2[] = "angel";
    char s3[] = "au";
    char s4[] = "bau";

    BOOST_CHECK(rimes(s1, s2, 3) == true);
    BOOST_CHECK(rimes(s3, s4, 3) == false);
    BOOST_CHECK(rimes(s3, s4, 2) == true);
}

BOOST_AUTO_TEST_CASE(test_problem6)
{
    char expected[] = {'D', 'A', 'B', 'C', 'E'};
    ifstream in;
    for (int i= 1; i <= 5; i++)
    {
        stringstream in_file;
        in_file << "test_files/pr6/test" << i << ".in";

        stringstream out_file;
        out_file << "test_files/pr6/test" << i << ".out";

        problema6(in_file.str().c_str(), out_file.str().c_str());

        in.open(out_file.str().c_str());
        char type;
        in >> type;
        in.close();

        BOOST_CHECK(type == expected[i - 1]);
     }
}

BOOST_AUTO_TEST_CASE(test_problem7)
{
    problema7("test_files/pr7/test1.in", "test_files/pr7/test1.out");

    char tests[][5] =
    {
        "ab", "ab", "ba",
        "arc", "car", "rac",
        "amam", "mama",
        "are", "era",
        "cd", "dc",
        "erem", "mere",
        "a",
        "b",
        "c",
        "d",
        "e",
        "f",
        "g",
    };

    ifstream in("test_files/pr7/test1.out");
    string entry;

    for (int i = 0; in >> entry; i++)
    {
        BOOST_CHECK(entry == tests[i]);
    }
    in.close();

    problema7("test_files/pr7/test2.in", "test_files/pr7/test2.out");
}