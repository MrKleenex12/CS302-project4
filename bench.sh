#!/bin/bash

sizes=(10 20 50 100 200 500 1000)
trials=5

pids=()
for size in ${sizes[@]}; do
	mkdir -p benchdata
	./src/generate_map $size > benchdata/input$size.txt
	for ((i = 0; i < trials; i++)); do
		echo "Testing size $size trial $((i+1))"
		(time valgrind --tool=memcheck ./src/dijkstras < benchdata/input$size.txt) 2>benchdata/output${size}${i}.txt &
		pids[${size}${i}]=$!
	done
done

for pid in ${pids[*]}; do
	wait $pid
done
