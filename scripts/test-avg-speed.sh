#!/usr/bin/env bash

WD=${WD:-`pwd`/}
AVG=${AVG:-$WD/../libavg/}
BASELINE=${BASELINE:-2.71}

main() {
    run_client &
    run_server
}

run_client() {
    cd $AVG/src/test
    LD_PRELOAD=$WD/build/libdgl.so ./Test.py player |& test_time
}

run_server() {
    $WD/build/dgl-server
}

test_time() {
    local time=`grep 'Ran 30 tests in ' | grep -oP '\d+\.\d+'`
    local too_big=`echo "$time > $BASELINE" | bc`
    if [ $too_big == 0 ]; then
        echo "$time is good (<= $BASELINE)"
    else
        echo "$time is too slow (> $BASELINE)"
    fi
}

main
