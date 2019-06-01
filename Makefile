all: testbst

testbst: intbst.cpp testbst.cpp intbst.h
	g++ intbst.cpp testbst.cpp -o testbst

clean:
	rm testbst
