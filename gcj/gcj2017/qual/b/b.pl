#!/usr/bin/env perl
use strict;
use utf8;
use bigint;

sub is_tidy
{
    my ($n) = @_;
    my $prev = -1;
    for my $i (0..length($n)-1) {
        my $ch = substr($n, $i, 1);
        if (int($ch) < $prev) {
            return 0;
        } else {
            $prev = int($ch);
        }
    }
    return 1;
}

sub to_string
{
    my ($n) = @_;
    return sprintf("%d", $n);
}

sub solve
{
    my ($n) = @_;
    while (1) {
        my $prev = -1;
        my $str_n = $n + "";

        if (is_tidy($n)) {
            return $n;
        }
        for my $i (0..length($n)-1) {
            my $digit = int(substr($n, $i, 1));
            if ($digit < $prev) {
                for my $j ($i..length($n)-1) {
                    substr($n, $j, 1) = '9';
                }
                substr($n, $i-1, 1) = to_string(int(substr($n, $i-1, 1)) - 1);
                last;
            }
            else {
                $prev = $digit;
            }
        }
        $n = to_string(int($n));
    }
}

sub main
{
    my $T = <STDIN>;
    for my $t (0..$T-1)
    {
        my ($X, $S, $B);
        my $line = <STDIN>;
        chomp($line);
        printf("Case #%d: %s\n", ($t+1), solve($line));
    }
}

&main();

