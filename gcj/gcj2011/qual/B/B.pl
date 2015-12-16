use strict;
use utf8;
use Data::Dumper;

&main();

sub doCombine
{
	my ($ans, $Cs) = @_;
	for my $i (0..@$Cs - 1)
	{
		my @splt = split('', $Cs->[$i]);
		my $before = $splt[0] . $splt[1];
		my $after = $splt[2];
		#$ans =~ s/$before/$after/;
		$ans =~ s/$before$/$after/;
		
		$before = $splt[1] . $splt[0];
		#$ans =~ s/$before/$after/;
		$ans =~ s/$before$/$after/;
	}
	return $ans;
}

sub doClear
{
	my ($ans, $Ds) = @_;
	for my $i (0..@$Ds - 1)
	{
		my ($front, $rear) = split('', @$Ds[$i]);
#		$ans =~ s/${front}.*${rear}//;
#		$ans =~ s/${rear}.*${front}//;
		if (($ans =~ /$front/) && ($ans =~ /$rear/))
		{
			$ans = "";
			last;
		}
	}
	return $ans;
}

sub main
{
	my $T = <STDIN>;
	for my $i (0..$T - 1)
	{
		my ($CNum, @Cs, $DNum, @Ds, @N);
		my $line = <STDIN>;
		my @vals = split(' ', $line);
		my $ptrIdx = 0;

		$CNum = $vals[$ptrIdx++];
		for my $j (0..$CNum - 1)
		{
			push (@Cs, $vals[$ptrIdx++]);
		}
		
		$DNum = $vals[$ptrIdx++];
		for my $j (0..$DNum - 1)
		{
			push (@Ds, $vals[$ptrIdx++]);
		}

		@N = split('', $vals[$ptrIdx + 1]);
#		print "Cs = (@Cs) Ds = (@Ds) N = (@N)\n";

		my $ans;
		for my $j (0..scalar(@N)-1)
		{
			$ans .= $N[$j];
#			print "ans = $ans, ";
			$ans = doCombine($ans, \@Cs);
#			print "$ans, ";
			$ans = doClear($ans, \@Ds);
#			print "$ans.\n"; 
		}
		print "Case #";
		print  $i+1 . ": [" . join(', ', split('', $ans)) . "]\n";
	}

}