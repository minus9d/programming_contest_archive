use strict;
use Data::Dumper;
use utf8;

&main();

sub debugPrint
{
	my ($currentLs) = @_;
	for my $currentL (@$currentLs)
	{
		print join('', @{$currentL->{ans}}) . "\t" . join('', @{$currentL->{cur}})
			    . "\t" . $currentL->{scr} . "\t" . $currentL->{end} . "\n";
	}
}

sub solve
{
	my ($Ls, $Ms) = @_;
	my @answer;
	my @currentLsOrig;

#	 Dumper \@currentLsOrig;

	for my $M (@$Ms)
	{
		my @currentLs;
		for my $L (@$Ls)
		{
			my $replaced = "_" x length($L);
			push(@currentLs,
			     { ans => [ split('', $L) ],
			       cur => [ split('', $replaced) ], 
				   len => length($L),
				   scr => 0,
				   end => 0,
				   endScore => 0,
				   candidates => {},
				 });
		}

		my @Mchars = split('', $M);
		for my $Mchar (@Mchars)
		{
			for my $i (0..$#currentLs - 1)
			{
				my $curI = join('', @{$currentLs[$i]->{cur}});
				for my $j (1..$#currentLs)
				{
					my $curJ = join('', @{$currentLs[$j]->{cur}});
					if ($curI eq $curJ)
					{
						$currentLs[$i]->{candidates}{$j};
						$currentLs[$j]->{candidates}{$i};
					}
				}
			}

#			print "Mchar = $Mchar\n";
			my $isEnd = 1;
			for my $currentL (@currentLs)
			{
				if ($currentL->{end} == 0)
				{
					$isEnd = 0;
					last;
				}
			}
			if ($isEnd == 1)
			{
				last;
			}

			for my $currentL (@currentLs)
			{
				my $foundFlag = 0;
				for my $i (0..$currentL->{len} - 1)
				{
					if ($currentL->{ans}[$i] eq $Mchar)
					{
						$currentL->{cur}[$i] = $Mchar;
						$foundFlag = 1;
					}
				}
				if ($foundFlag == 0)
				{
					my $doesCandidateHasTheChar = 0;
					for my $j (keys %{$currentL->{candidates}})
					{
						for my $c (@{$currentLs[$j]->{ans}})
						{
							if ($c eq $Mchar)
							{
								$doesCandidateHasTheChar = 1;
							}
						}
					}
					if ($doesCandidateHasTheChar == 1)
					{
						$currentL->{scr}++;
					}
				}
			}

			my %sameStringFinder;
			for my $i (0..$#currentLs)
			{
				my $cur = join('', @{$currentLs[$i]->{cur}});
				$sameStringFinder{ $cur }->{count}++;
				push (@{$sameStringFinder{ $cur }->{index}}, $i);
			}
			print Dumper \%sameStringFinder;

			for my $key (keys %sameStringFinder)
			{
				if ($sameStringFinder{$key}{count} == 1)
				{
					my $index = $sameStringFinder{$key}{index}[0];
					if ($currentLs[$index]->{end} == 0)
					{
						$currentLs[$index]->{end} = 1;
						$currentLs[$index]->{endScore} = $currentLs[$index]->{scr};
					}
				}
			}
#			print debugPrint(\@currentLs);
		}

		my $highScore = 0;
		my $highIndex = 0;
		for my $i (0..$#currentLs)
		{
			if ($currentLs[$i]->{endScore} > $highScore)
			{
				$highIndex = $i;
				$highScore = $currentLs[$i]->{endScore};
			}
		}
		push(@answer, join('', @{$currentLs[$highIndex]->{ans}}));
	}

	return @answer;
}

sub main
{
	my $T = <STDIN>;
	for my $i (0..$T - 1)
	{
		my ($N, $M) = split(' ', <STDIN>);
		my @Ls;
		for my $i (0..$N-1)
		{
			my $line = <STDIN>;
			chomp($line);
			push(@Ls, $line);
		}
		my @Ms;
		for my $i (0..$M-1)
		{
			my $line = <STDIN>;
			chomp($line);
			push(@Ms, $line);
		}

		my @answer = solve(\@Ls, \@Ms);
		print "Case #" . ($i + 1) . ": " . join(' ', @answer) . "\n";
	}
	

}
