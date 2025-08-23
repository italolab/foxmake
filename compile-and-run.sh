
./cbuild build --settings-file=settings-linux.txt

if [ "$#" -eq "1" ]; then
    ./build/cbuild2 $1 --settings-file=settings-test/settings.txt
fi