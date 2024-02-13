#!/bin/bash

set -u

for i in {0..9}; do
	base_dir="level$i"
	mkdir "$base_dir"
	touch "$base_dir/flag"
	touch "$base_dir/source"
	touch "$base_dir/walkthrough"
done

for i in {0..3}; do
	base_dir="bonus$i"
	mkdir "$base_dir"
	touch "$base_dir/flag"
	touch "$base_dir/source"
	touch "$base_dir/walkthrough"
done
