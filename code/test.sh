g++ $1.cpp
for i in $1/*.in
do
	j="${i/.in/.ans}"
	./a.out < $i > output
	diff output $j || echo "WA on $i"
done
