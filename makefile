all: gtest vera
    g++ -Igtest/include/ main.cpp -pthread gtest/make/gtest_main.a --std=c++11 -o test

gtest: 
    $(MAKE) -C "gtest/make"

# for vera we must use the -"command" so that make continues after an error
# for some readon, running cmake three times does the trick
vera:
    -cd vera/build && cmake ..
    -cd vera/build && cmake ..
    -cd vera/build && cmake ..
    $(MAKE) -C "vera/build"

.PHONY: gtest vera

clean: 
    $(MAKE) -C "gtest/make" clean
    rm -r -f vera/build/*
    rm -f *.o
    rm -f test

