for i in fuzz-tests/*.cpp
do
	echo "********** Testing $i... **********"
	g++ --std=c++17 -Wall -Wshadow -Wfatal-errors -g $i || exit 1
	./a.out || exit 1 # stop when an assertion failed.
done
