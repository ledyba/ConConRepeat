#!/bin/bash

if [[ $# < 2 ]]; then
	echo "usage: bash run.sh anime.mkv output-dir <skip-duration-in-ms>"
	exit -1
fi

if [ ! -f "./ConConRepeat" ]; then
	echo "please build:"
	echo "    $ cmake . && make"
	exit -1
fi

tdir=`mktemp -d`
trap "rm -rf ${tdir}" EXIT

echo ./ConConRepeat \"$1\" \"$tdir\" \"$3\"
./ConConRepeat "$1" "$tdir" "$3"
echo bash ../gifnize.sh 0 "$tdir"
bash gifnize.sh "$tdir" "$2" 0
