
./cbuild $1 --script=CBuildFile -var target=$2

if [ "$#" -gt "2" ]; then
    target="debug"
    if [ "$#" -gt "3" ]; then
        target=$4
    fi

    ./build/cbuild $3 --script=run/CBuildFile-Run -var target=$target
fi