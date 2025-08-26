
build=build
if [ "$#" -gt 1 ]; then
    if [ "$2" == "all" ]; then
        build=buildall
    fi
fi

if [ "$1" == "debug" ]; then
    ./cbuild $build --settings-file=settings-linux.txt -var target=debug
else
    ./cbuild $build --settings-file=settings-linux.txt -var target=release
fi

if [ "$#" -gt "1" ]; then
    build=build
    if [ "$2" == "all" ]; then
        if [ "$#" -gt "2" ]; then
            build=$3
        fi
    else
        build=$2
    fi

    ./build/cbuild $build --settings-file=settings-linux-run.txt -var target=debug
fi