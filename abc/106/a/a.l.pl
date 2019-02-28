#!/usr/bin/perl
use strict;

my ($a,$b)=glob<>;
my $ans = $a * $b - $a - $b + 1;
print "$ans\n";
