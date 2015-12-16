use strict;
use utf8;
use Data::Dumper;
use bignum;

&main();

sub getPrimes
{
	my ($N, $primes) = @_;

#	my %no;
	my @no;
	
	#ignore 1
	for my $i (2..$N)
	{
		if ($i == 2)
		{
			push (@$primes, $i);
		}
		elsif ($i % 2 != 0 && !defined $no[$i])
		{
			push(@$primes, $i);
			my $num = $i;
			while($num <= $N)
			{
				$no[$i] = 1;
				$num += $i;
			}
		}
	}
}

sub main
{
	my $max = 1000000;
	my $Nmax = $max * $max;
	my @primes;
	getPrimes($max, \@primes);

	my %clues;
	$clues{2} = 1;
	for my $prime (@primes)
	{
#		print "prime = $prime.\n";
		my $num = $prime * $prime;
		while($num < $Nmax)
		{
			$clues{$num} = 1;
			$num *= $prime;
		}
	}
	
	my @sorted = sort keys %clues;

	my %rank;
	for my $i (0..$#sorted)
	{
		$rank{$sorted[$i]} = $i;
	}

	my $T = <STDIN>;
	for my $i (0..$T - 1)
	{
		my ($N) = split(' ', <STDIN>);
		print "Case #" . ($i + 1) . ": ";

		
	}

}
