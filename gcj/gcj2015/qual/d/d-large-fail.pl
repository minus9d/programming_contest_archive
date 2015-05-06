#!/usr/bin/env perl
use strict;
use utf8;

&main();

# @retval 0: can't fill (Richard)
# @retval 1: can fill (Gabriel)
sub solve
{
    my ($X, $S, $B) = @_;

    # always S <= B
    ($B, $S) = ($S, $B) if ($B < $S);

    if ($X == 1) {
        return 1;
    }
    elsif ($X == 2) {
        return 0 if ($B == 1);
        return 1 if (($B * $S) % 2 == 0);
        return 0;
    }
    elsif ($X == 3) {
        return 0 if ($B <= 2);
        return 0 if ($S == 1);
        return 1 if (($B * $S) % 3 == 0);
        return 0;
    }
    elsif ($X == 4) {
        return 0 if ($B <= 3);
        return 0 if ($S <= 2);
        return 1 if (($B * $S) % 4 == 0);
        return 0;
    }
    elsif ($X == 5) {
        return 0 if ($B <= 4);
        return 0 if ($S <= 3);
        return 1 if (($B * $S) % 5 == 0);
        return 0;
    }
    elsif ($X == 6) {
        return 0 if ($B <= 5);
        return 0 if ($S <= 3);
        return 1 if (($B * $S) % 6 == 0);
        return 0;
    }
    else {
        return 0;
    }
}

sub main
{
    # for my $x (1..8) {
    #     for my $s (1..8) {
    #         for my $b ($s..8) {
    #             printf("x, s, b, result = %d, %d, %d, %d\n", $x, $s, $b, solve($x, $s, $b))
    #         }
    #     }
    # }

    my $T = <STDIN>;
    for my $t (0..$T-1)
    {
        my ($X, $S, $B);
        my $line = <STDIN>;
        chomp($line);
        ($X, $S, $B) = split(' ', $line);
        printf("Case #%d: %s\n", ($t+1), (solve($X, $S, $B) ?  "GABRIEL" : "RICHARD"));
    }
}
