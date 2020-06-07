my $k = Int(get);
my $ans = 0;
my @loop = 1..$k;
for @loop -> $a {
    for @loop -> $b {
        my $tmp = $a gcd $b;
        for @loop -> $c {
            $ans += $tmp gcd $c;
        }
    }
}
print "$ans\n";
