DEBUG ?= 0
DEBUG_FLAGS=-ggdb -D DEBUG=$(DEBUG) 
COMPILE_FLAGS=-Wall -I../curl/include
LIB_PATH =../curl/build/lib/libcurl.a
LIB_PATH +=../../gopro-sdk-contrib/zlib-1.2.8/libz.a
LIB_PATH +=../openssl/build/lib/libssl.a
LIB_PATH +=../openssl/build/lib/libcrypto.a -lrt -ldl
# OPTIMIZE_FLAGS=-O3

.PHONY: all clean test

all: build/universal-analytics.o build/http.o

test: build/testing.exe build/static-testing.exe

clean:
	@rm -fv build/*.exe build/*.o
	@rm -rfv *.exe.dSYM build


build/libanalytics.a: build/http.o build/universal-analytics.o
	ar -rs $@ $<

build/testing.exe: test.c build/universal-analytics.o build/http.o 
	mkdir -p `dirname $@`
	gcc $(COMPILE_FLAGS) $(OPTIMIZE_FLAGS) $(DEBUG_FLAGS) -o $@ $^ $(LIB_PATH)

build/static-testing.exe: test-static.c build/universal-analytics.o build/http.o 
	mkdir -p `dirname $@`
	gcc $(COMPILE_FLAGS) $(OPTIMIZE_FLAGS) $(DEBUG_FLAGS) -o $@ $^ $(LIB_PATH)

build/http.o: src/http.c src/http.h
	mkdir -p `dirname $@`
	gcc $(COMPILE_FLAGS) $(DEBUG_FLAGS) -o $@  -c $<

build/universal-analytics.o: src/universal-analytics.c src/universal-analytics.h
	mkdir -p `dirname $@`
	gcc $(COMPILE_FLAGS) $(DEBUG_FLAGS) -o $@ -c $<



#  vim: set nowrap tabstop=2 shiftwidth=2 softtabstop=0 noexpandtab textwidth=0 filetype=make foldmethod=syntax foldcolumn=4
