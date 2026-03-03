#!/bin/zsh
LL="./bin/gnole_hemisphere -order 0"
flag_sets=(
    "-drapl 0.5 -drapr 0.5 -out data/asym_sliceLL05_05.dat"
    "-drapl 0.0 -drapr 0.5 -out data/asym_sliceLL0_05.dat"
    "-drapl 0.0 -drapr 1.0 -out data/asym_sliceLL0_1.dat"
    "-drapl 0.0 -drapr 2.0 -out data/asym_sliceLL0_2.dat"
    "-drapl 0.0 -drapr 3.0 -out data/asym_sliceLL0_3.dat"
    "-drapl 0.0 -drapr 4.0 -out data/asym_sliceLL0_4.dat"
    "-drapl 0.0 -drapr 5.0 -out data/asym_sliceLL0_5.dat"
)
pids=()
for flags in "${flag_sets[@]}"; do
    echo "launching: $LL $flags"
    ${=LL} ${=flags} > /dev/null 2>&1 &
    pids+=($!)
done
echo "\nwaiting for ${#pids[@]} jobs to finish...\n"
failed=0
for pid in "${pids[@]}"; do
    wait "$pid"
    rc=$?
    if [[ $rc -eq 0 ]]; then
        echo "pid $pid succeeded"
    else
        echo "pid $pid failed [exit $rc]"
        ((failed++))
    fi
done
total=${#pids[@]}
echo "$(( total - failed ))/$total runs succeeded"
exit $failed