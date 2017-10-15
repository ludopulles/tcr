g++ -std=c++11 -O2 $1.cpp
for i in $1/*.in
do
	j="${i/.in/.ans}"
	./a.out < $i > output
	diff output $j || exit
	echo "$i is correct"
done
echo "You may submit!"
