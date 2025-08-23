
./cbuild build --settings-file=settings-linux.txt

if [ "$#" -eq "1" ]; then
    ./build/cbuild2 $1 --settings-file=run/settings.txt
fi