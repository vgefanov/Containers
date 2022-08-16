CC = gcc
CFLAGS =-Wall -Wextra -Werror -lstdc++ -std=c++17
CFLAGS_TEST =-lgtest
CFLAGS_GCOV =--coverage -fkeep-inline-functions
CPPCHECK_FLAGS =--enable=all --suppress=missingIncludeSystem
OUTFILE = s21_containers
OUTFILE_TEST = $(OUTFILE)_test
SOURCES = $(OUTFILE).cpp
SOURCES_TEST = $(OUTFILE_TEST).cpp
CHECK_FILES = *.cpp classes/*.hpp classes/*.inl tests/*.cpp

all: s21_containers.a test

clean:
	-rm -rf ./lcov_report 2>/dev/null
	-rm *.o *.a *.gcno *.gcda *.gcov *.info $(OUTFILE) $(OUTFILE_TEST) 2>/dev/null

test:
	$(CC) $(CFLAGS) $(CFLAGS_TEST) $(SOURCES) $(SOURCES_TEST) -o $(OUTFILE_TEST)
	./$(OUTFILE_TEST)

s21_containers.a:
	$(CC) $(CFLAGS) -c $(SOURCES) -o $(OUTFILE).o
	ar rc $(OUTFILE).a $(OUTFILE).o

# checks

check_all: style check leaks

style:
	cp ../materials/linters/CPPLINT.cfg .
	python3 ../materials/linters/cpplint.py --filter=-runtime/references --extensions=cpp,hpp,inl $(CHECK_FILES)

check:
	cppcheck --std=c++17 --language=c++ $(CPPCHECK_FLAGS) $(CHECK_FILES)

leaks: test
	CK_FORK=no leaks --atExit -- ./$(OUTFILE_TEST)

valgrind:
	# brew tap LouisBrunner/valgrind
	# brew install --HEAD LouisBrunner/valgrind/valgrind
	valgrind ./$(OUTFILE_TEST) --leak-check=full

gcov_report:
	$(CC) $(CFLAGS) $(CFLAGS_TEST) $(CFLAGS_GCOV) $(SOURCES) $(SOURCES_TEST) -o $(OUTFILE_TEST)
	./$(OUTFILE_TEST)
	gcov $(OUTFILE)
	gcov -f $(OUTFILE).gcda
	lcov --no-external --capture --directory . --output-file main_coverage.info
	genhtml main_coverage.info --output-directory lcov_report
	open lcov_report/index.html
