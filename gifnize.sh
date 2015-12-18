#! /bin/bash

indir="."
outdir="."
i=0
indir=$1
outdir=$2
i=$3

echo "from anime $i, \"$indir\" -> \"$outdir\""

fps=24
while [ -f $(printf "%s/anime-%03d-000.png" $indir $i) ];do
	echo "Now: $i"
	#files=$(find . -name "anime-$i-*.png")
	#mogrify -resize 360x $(printf "anime-%03d-*.png" $i)
	convert -delay $(expr 100 / $fps) $(printf "%s/anime-%03d-*.png" $indir $i) $outdir/anime_$i.gif
	test $? -ne 0 && exit -1
	i=$(expr $i \+ 1)
done
echo "all done, have fun"
