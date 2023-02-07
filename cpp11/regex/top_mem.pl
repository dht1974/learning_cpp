#!/usr/bin/perl -w

use strict;

# "MiB Mem : 64029.29+total, 61226.17+free, 2407.867 used, 1423.922 buff/cache"

while (<>) {
	if (/(.+)\s+Mem\s+:\s+(\d+\.\d+)\+*total,\s+(\d+\.\d+)\+*free,\s+(\d+\.\d+)\+*\s*used,\s+(\d+\.\d+)\+*\s*buff/) {
		printf ("$1 --> $2 --> $3 --> $4 --> $5\n");
	}
}
