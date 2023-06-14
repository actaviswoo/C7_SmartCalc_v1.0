# all, install, uninstall, clean, dvi, dist, test, gcov_report.

CC=gcc
STDFLAGS=-Wall -Werror -Wextra -std=c11 
OS := $(shell uname -s)
FLAG_COV = --coverage
TEST_LIBS = -lcheck -lm -lpthread
VALGRIND_FLAGS=--trace-children=yes --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all --verbose
LINUX_FLAGS=-lsubunit -lrt -lpthread -lm
LIBS=-lcheck

all: install s21_smartcalc.a test

main: clean
	gcc s21_smartcalc.c s21_stack.c -o s21_test $(TEST_LIBS) $(STDFLAGS)
	./s21_test

clang:
	clang-format -i --style=google *.c *.h
	cp ../materials/linters/.clang-format ../src/.clang-format; \
	clang-format -style=Google -n *.c *.h; \
	rm .clang-format

clean:
	rm -rf *.o
	rm -rf *.a
	rm -rf *.gcno
	rm -rf *.gcda
	rm -rf *.gcov
	rm -rf *.info
	rm -rf *.css
	rm -rf s21_test
	rm -rf gcov_test
	rm -rf *.txt
	rm -rf *.log
	rm -rf unit_test
	rm -rf ./build
	rm -rf ./report
	rm -rf test

s21_smartcalc.a:
	$(CC) $(STDFLAGS) -c s21_stack.c s21_smartcalc.c
	ar rc s21_smartcalc.a *.o
	ranlib s21_smartcalc.a

s21_credit.a:
	$(CC) $(STDFLAGS) -c s21_credit.c
	ar rc s21_credit.a *.o
	ranlib s21_credit.a

valgrind: s21_smartcalc.a s21_credit.a
	$(CC) s21_smartcalc_test.c s21_credit.a s21_smartcalc.a -o test $(LIBS) $(LINUX_FLAGS)
	valgrind --log-file="s21_smartcalc.log" $(VALGRIND_FLAGS) ./test
	grep ERROR s21_smartcalc.log > error.txt
	grep -v "ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)" error.txt > __error.txt

test: s21_smartcalc.a s21_credit.a
ifeq ($(OS), Darwin)
	${CC} $(STDFLAGS) s21_smartcalc_test.c s21_smartcalc.a s21_credit.a -o unit_test $(LIBS)
else
	${CC} $(STDFLAGS) s21_smartcalc_test.c s21_smartcalc.a s21_credit.a -o unit_test $(LIBS) $(LINUX_FLAGS)
endif
	./unit_test

leaks: test
	leaks -atExit -- ./unit_test

gcov_report: clean s21_smartcalc.a s21_credit.a
	$(CC) $(STDFLAGS) $(FLAG_COV) s21_smartcalc_test.c s21_smartcalc.c s21_stack.c s21_credit.c s21_credit.a s21_smartcalc.a $(TEST_LIBS) -o gcov_test
	chmod +x *
	./gcov_test
	gcov s21_*.gcda
	lcov -t "gcovReport" -o gcov_test.info -c -d .
	genhtml -o report gcov_test.info
	open report/index.html

build:
	mkdir build
	cd ./build/ && qmake ../ && make

install: build
	@cp -rf build/smartcalculator.app $(HOME)/Desktop/smartcalculator.app
	make clean

uninstall:
	@rm -rf $(HOME)/Desktop/smartcalculator.app

dist:
	mkdir SmartCalc_v1.0/
	mkdir SmartCalc_v1.0/src
	cp Makefile *.c *.h *.pro *.cpp *.ui *.user SmartCalc_v1.0/src/
	tar cvzf SmartCalc_v1.0.tgz SmartCalc_v1.0/
	mv SmartCalc_v1.0.tgz $(HOME)/Desktop/
	rm -rf SmartCalc_v1.0/

dvi:
	open smartcalculator.html

start:
	open ~/Desktop/smartcalculator.app

valgrindmacos:
	cd ../materials/build/Valgrind && sh run.sh