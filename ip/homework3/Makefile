CC = g++
CPPFLAGS = -Wall
CPPFILES = tema3_1.cpp
OUTPUT = -o source
TESTS_OUTPUT = -o tests
TESTS_LIBS = -lboost_unit_test_framework
TEST_FILES = tests.cpp tema3_1.cpp

all:
	$(CC) $(CPPFLAGS) $(CPPFILES) $(OUTPUT)

test:
	$(CC) $(CPPFLAGS) $(TEST_FILES) $(TESTS_OUTPUT) $(TESTS_LIBS)

clean:
	rm -r test_files/*/*.out
	rm -r test_files/*/*.in~
