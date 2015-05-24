use strict;
use utf8;
use Data::Dumper;

&main();

sub solve
{
	my ($X, $S, $R, $t, $walkways) = @_;
	my $ans = 0;

	my $noWalkway = $X;
	for my $w (@$walkways)
	{
		my $length = $w->{Ei} - $w->{Bi};
		$noWalkway -= $length;
	}
	push(@$walkways, { wi => 0, Bi => 0, Ei => $noWalkway });

	
	my @sorted = sort{ $a->{wi} <=> $b->{wi} } @$walkways;
		
	for my $w (@sorted)
	{
		my $vel;
		if ($t > 0)
		{
			my $time = ($w->{Ei} - $w->{Bi}) / ($w->{wi} + $R);
			if ($time < $t)
			{
				$t -= $time;
				$ans += $time;
			}
			else
			{
				$ans += $t;
				my $short = ($w->{Ei} - $w->{Bi})
						  - (($w->{wi} + $R)) * $t;
				$t = 0;
				$ans += $short / ($w->{wi} + $S);
			}
		}
		else
		{
			$ans += ($w->{Ei} - $w->{Bi}) / ($w->{wi} + $S);
		}
	} 
	
	return $ans;
}


sub main
{
	my $T = <STDIN>;
	for my $i (0..$T - 1)
	{
		my @walkways;
		my $line = <STDIN>;
		my ($X, $S, $R, $t, $N) = split(' ', $line);
		for my $j (0..$N-1)
		{
			my $line = <STDIN>;
			my ($Bi, $Ei, $wi) =  split(' ', $line);
			push(@walkways, { Bi => $Bi, Ei => $Ei, wi => $wi });
		}
		
		print "Case #" . ($i+1) . ": ";
		printf("%10.9f\n", solve($X, $S, $R, $t, \@walkways));
	}
}
