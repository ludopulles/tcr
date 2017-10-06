printf "set nu sw=4 ts=4 sts=4 noet ai hls shellcmdflag=-ic\nsy on | colo slate" > .vimrc
printf "\nalias gsubmit='g++ -Wall -Wshadow -std=c++11'" >> .bashrc
printf "\nalias g11='gsubmit -DLOCAL -g'" >> .bashrc
. .bashrc
mkdir contest; cd contest
