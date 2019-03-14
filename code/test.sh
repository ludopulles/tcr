g++ -Wall -Wshadow -Wfatal-errors -Wpedantic -std=c++17 $1.cc || exit
for i in $1/*.in
do
	j="${i/.in/.ans}"
	./a.out < $i > output
	diff output $j || echo "!!WA on $i!!"
done
