
./cbuild build --settings-file=settings-linux.txt

if [ "$#" -eq "1" ]; then
    ./build/cbuild $1 --settings-file=settings-linux-run.txt
fi