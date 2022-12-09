CC=gcc
DIRECTORY=pwd
CFLAGS=-std=c11 -Wall -Werror -Wextra
FILE=s21_smartcalc
APP=SmartCalc
APPFILE=$(APP)
DIR=Smart_Calc_v1.0
TC_FLAGS=
LEAK_CHECK=
UNAME_S := $(shell uname -s)
TETEX=
QMAKE=

ifeq ($(UNAME_S),Linux)
    CC += -D LINUX -g
	QMAKE+=qmake6
	TETEX += /usr/bin/texi2dvi
	TC_FLAGS += -lcheck -lsubunit -lm -lrt -lpthread
	LEAK_CHECK +=CK_FORK=no valgrind --trace-children=yes --track-fds=yes --leak-check=yes --show-leak-kinds=all --track-origins=yes --verbose --log-file=valgrind_log.txt ./test.out
endif

ifeq ($(UNAME_S),Darwin)
	TETEX += /Library/TeX/texbin/latex
    CC += -D OSX
	QMAKE+=qmake
	APPFILE =$(APP).app
	TC_FLAGS += $(shell pkg-config --cflags check) $(shell pkg-config --libs check)
	LEAK_CHECK +=CK_FORK=no leaks -atExit -- ./test.out
endif

FLAG1=-I src
FLAG2=-c

default: all tests

all: clean $(FILE).a

tests: $(FILE).a
	$(CC) $(FILE)_test.c $(FILE).a -o test.out $(TC_FLAGS)
	./test.out

$(FILE).a: $(FILE).o
	ar rcs $(FILE).a $(FILE).o
	ranlib $(FILE).a

$(FILE).o: $(FILE).c
	$(CC) $(FLAG1) $(CFLAGS) $(FLAG2) $(FILE).c -o $(FILE).o

clean:
	rm -rf  *.a *.o *.out *.txt *.info *.gcno *.gcda report *.cfg build $(DIR) *.pdf *.log *.aux *.dvi .clang-format
check:
	cp ../materials/linters/.clang-format .clang-format
	clang-format -i *.c *.h  *.cpp
	clang-format -n *.c *.h *.cpp
	# cppcheck --enable=all --suppress=missingIncludeSystem *.h *.c
	# cp ../materials/linters/CPPLINT.cfg CPPLINT.cfg
	# python3 ../materials/linters/cpplint.py --extension=c *.c *.h
	$(LEAK_CHECK)

gcov_report:
	$(CC) --coverage $(FILE)_test.c $(FILE).c -o test.out $(TC_FLAGS)
	./test.out
	lcov -t test.out -o rep.info -c -d . --no-external
	genhtml -o report rep.info
	open report/index.html

build: clean
	mkdir build
	cd build; $(QMAKE) ../$(APP).pro CONFIG+=sdk_no_version_check 
	make  -C build

install: build
	-mkdir $(DIR)
	tar xvf bin.tgz
	make dvi
	cp -rf build/$(APPFILE) bin/. $(FILE).dvi $(DIR)/
	-rm -rf build bin $(FILE).dvi

uninstall:
	-rm -rf $(DIR)/

dist: install
	tar cvzf dist_$(APP).tgz $(DIR)/
	make uninstall

dvi: 
	$(TETEX) $(FILE).tex
	rm -rf *.aux *log
