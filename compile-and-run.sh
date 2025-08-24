
./cbuild build --settings-file=settings-linux.txt

if [ "$#" -eq "1" ]; then
    ./build/cbuild $1 --working-dir=run --no-resume
fi