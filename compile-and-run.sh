
./cbuild $1 --settings-file=settings-linux.txt -var target=$2

if [ "$#" -gt "2" ]; then
    target="debug"
    if [ "$#" -gt "3" ]; then
        target=$4
    fi

    ./build/cbuild $3 --settings-file=run/settings-linux-run.txt -var target=$target
fi