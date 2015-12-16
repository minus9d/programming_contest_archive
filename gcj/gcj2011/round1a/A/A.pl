use strict;
use utf8;
use Data::Dumper;
use bignum;

&main();

# must $n1 > $n2
sub getGcd
{
	my ($n1, $n2) = @_;
	while ($n2)
	{
		my $tmp = $n1 % $n2;
		$n1 = $n2;
		$n2 = $tmp;
	}
	return $n1;
}

sub answer
{
	my ($N, $Pd, $Pg) = @_;

		my $gcd = getGcd(100, $Pd);
		my $leastD = 100 / $gcd;

		if ($leastD > $N)
		{
			return "Broken";
		}

		if ($Pg == 0 && $Pd != 0)
		{
			return "Broken";
		}
		elsif ($Pg == 100 && $Pd != 100)
		{
			return "Broken";
		}

		return "Possible";
}
sub main
{
	my $T = <STDIN>;
	for my $i (0..$T - 1)
	{
		my $line = <STDIN>;
		my ($N, $Pd, $Pg) = split(' ', $line);

		my $ans = answer($N, $Pd, $Pg);
		if ($ans eq "Broken")
		{
			print "Case #" . ($i + 1) . ": Broken\n";
		}
		else
		{
			print "Case #" . ($i + 1) . ": Possible\n";
		}
	}

}
