DEBUG ?= 0
DEBUG_FLAGS=-ggdb -D DEBUG=$(DEBUG) 
COMPILE_FLAGS=-Wall -stdlib=libstdc++
DEPEND_FLAGS=-l curl
# OPTIMIZE_FLAGS=-O3

.PHONY: all clean test

all: build/universal-analytics.o build/http.o

test: build/testing.exe build/static-testing.exe

clean:
	@rm -fv build/*.exe build/*.o
	@rm -rfv *.exe.dSYM build

build/libanalytics.a: build/http.o build/universal-analytics.o
	ar -rs $@ $<


build/testing.exe: test.c build/universal-analytics.o build/http.o build/dispatcher.o build/events.o build/datalayer.o build/storage.o

build/static-testing.exe: test-static.c build/universal-analytics.o build/http.o build/dispatcher.o build/events.o build/datalayer.o build/storage.o

build/http.o: src/http.c src/http.h

build/universal-analytics.o: src/universal-analytics.c src/universal-analytics.h src/dispatcher.h src/http.h

build/dispatcher.o: src/dispatcher.c src/dispatcher.h src/http.h

build/events.o: src/events/src/events.c src/events/src/events.h

build/datalayer.o: src/datalayer.c src/datalayer.h

build/storage.o: src/storage.c src/storage.h



build/%.exe:
	mkdir -p `dirname $@`
	gcc $(COMPILE_FLAGS) $(OPTIMIZE_FLAGS) $(DEBUG_FLAGS) $(DEPEND_FLAGS) -o $@ $^

build/%.o:
	mkdir -p `dirname $@`
	gcc $(COMPILE_FLAGS) $(DEBUG_FLAGS) -o $@ -c $<

#  vim: set nowrap tabstop=2 shiftwidth=2 softtabstop=0 noexpandtab textwidth=0 filetype=make foldmethod=syntax foldcolumn=4
