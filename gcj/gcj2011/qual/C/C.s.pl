use strict;
use utf8;
use Data::Dumper;

&main();

sub cantSolve
{
	my ($xorAll) = @_;

	while ($xorAll != 0)
	{
		if ((($xorAll & 0x1) % 2) != 0)
		{
			return 1;
		}
		$xorAll >>= 1;
	}
	return 0;
}

sub main
{
	my $T = <STDIN>;
	for my $i (0..$T - 1)
	{
		my $dummy = <STDIN>;
		my @vals = split(' ', <STDIN>);
		@vals = sort { $a <=> $b } (@vals);

		my $xorAll;
		my $sumAll;
		for my $i (0..$#vals)
		{
			$xorAll ^= $vals[$i];
			$sumAll += $vals[$i];
		}

		print "Case #" .  ($i + 1) , ": ";
		if (cantSolve($xorAll))
		{
			print "NO\n";
		}
		else
		{
			my @cases;
			for $i (0..$#vals)
			{
				if ($i == 0)
				{
					push (@cases, [$vals[0]]);
					push (@cases, []);
				}
				else
				{
					my @addCases;
					for my $case (@cases)
					{
						my @temp = @$case;
						push(@temp, $vals[$i]);
						push (@addCases, \@temp);
					}
					push(@cases, @addCases);
				}
			}

			my $sumMax;
			for my $case (@cases)
			{
				if (scalar(@$case) == 0 || scalar(@$case) == scalar(@vals))
				{
					next;
				}
				else
				{
					my ($xor1, $xor2, $sum1, $sum2);
					for my $val (@$case)
					{
						$xor1 ^= $val;
					}
					$xor2 = $xor1 ^ $xorAll;

					if ($xor1 == $xor2)
					{
						for my $val (@$case)
						{
							$sum1 += $val;
						}
						$sum2 = $sumAll - $sum1;

						if ($sum1 > $sumMax)
						{
							$sumMax = $sum1;
						}
						if ($sum2 > $sumMax)
						{
							$sumMax = $sum2;
						}
					}
				}
			}
			print "$sumMax\n";
		}
	}

}