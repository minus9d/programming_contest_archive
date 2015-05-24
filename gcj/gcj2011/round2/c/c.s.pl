use strict;
use utf8;
use Data::Dumper;

&main();



sub getPrimes
{
	my ($N, $primes, $noPrimes) = @_;
	
	#ignore 1
	for my $i (2..$N)
	{
		if ($i == 2)
		{
			push (@$primes, $i);
		}
		else
		{
			my $isPrime = 1;
			for my $p (@$primes)
			{
				if ($i % $p == 0)
				{
					$isPrime = 0;
					last;
				}
			}
			if ($isPrime)
			{
				push(@$primes, $i);
			}
			else
			{
				push(@$noPrimes, $i);
			}
		}
	}
}

sub solve
{
	my ($N) = @_;
	if ($N == 1)
	{
		return 0;
	}

	my @primes;
	my @noPrimes;
	getPrimes($N, \@primes, \@noPrimes);

	my %comp;
	for my $i (@primes)
	{
		$comp{$i}{$i} = 1;
	}
	for my $i (@noPrimes)
	{
		for my $p (@primes)
		{
			my $num = $i;
			while($num % $p == 0)
			{
				$comp{$i}{$p}++;
				$num /= $p;
			}
		}
	}
	
	my $best = scalar(@primes);
	my $worst;
	for my $prime (@primes)
	{
		my $highest;
		for my $key (keys %comp)
		{
			if ($comp{$key}{$prime} > $highest)
			{
				$highest = $comp{$key}{$prime};
			}
		}
		$worst += $highest;
	}
	$worst++; # think about 0
	return $worst - $best;
}

sub main
{
	my $T = <STDIN>;
	for my $i (0..$T - 1)
	{
		my ($N) = split(' ', <STDIN>);
		print "Case #" . ($i + 1) . ": ". solve($N) . "\n";
	}

}
