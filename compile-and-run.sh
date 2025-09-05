
echo $2
./cbuild $1 --cbuild-file=CBuildFile -var target=$2

if [ "$#" -gt "2" ]; then
    target="debug"
    if [ "$#" -gt "3" ]; then
        target=$4
    fi

    ./build/cbuild $3 --cbuild-file=run/CBuildFile-Run -var target=$target
fi