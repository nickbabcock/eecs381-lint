GTEST_BUILD_DIR = "gtest/build"
GTEST_DIR = $(GTEST_BUILD_DIR)/..

all: gtest vera
	-g++ -I$(GTEST_DIR)/include main.cpp libgtest.a libgtest_main.a -pthread --std=c++11 -o test

gtest:
	-mkdir $(GTEST_BUILD_DIR) 2>/dev/null
	cd $(GTEST_BUILD_DIR) && cmake ..
	$(MAKE) -C "$(GTEST_BUILD_DIR)" 
	cp $(GTEST_BUILD_DIR)/libgtest_main.a .
	cp $(GTEST_BUILD_DIR)/libgtest.a .

# for vera we must use the -"command" so that make continues after an error
# for some readon, running cmake three times does the trick
vera:
	-mkdir vera/build 2>/dev/null
	-cd vera/build && cmake ..
	-cd vera/build && cmake ..
	-cd vera/build && cmake ..
	$(MAKE) -C "vera/build"

.PHONY: gtest vera

clean: 
	$(MAKE) -C $(GTEST_BUILD_DIR) clean
	rm -r -f vera/build/*
	rm -f *.o
	rm -f *.a
	rm -f test

