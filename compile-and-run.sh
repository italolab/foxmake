VERSION=1.0
SO=linux
ARCH=x64


./foxmake $1 --script=FoxMakefile -var target=$2

if [ "$#" -gt "2" ]; then
    target="debug"
    if [ "$#" -gt "3" ]; then
        target=$4
    fi

    ./build/foxmake-$VERSION-$SO-$ARCH/foxmake $3 --script=run/FoxMakefile-Run -var target=$target
fi