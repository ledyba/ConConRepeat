#! /bin/bash

indir="."
i=0
if [ ! -z "$1" ]; then
	i=$1
fi
if [ ! -z "$2" ]; then
	indir=$2
fi
echo "from $i anime, dir: $indir"
fps=24
while [ -f $(printf "%s/anime-%03d-000.png" $indir $i) ];do
	echo "Now: $i"
	#files=$(find . -name "anime-$i-*.png")
	#mogrify -resize 360x $(printf "anime-%03d-*.png" $i)
	convert -delay $(expr 100 / $fps) $(printf "%s/anime-%03d-*.png" $indir $i) anime_$i.gif
	test $? -ne 0 && exit -1
	i=$(expr $i \+ 1)
done
echo "all done, have fun"
