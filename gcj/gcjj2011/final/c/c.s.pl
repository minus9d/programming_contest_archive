use strict;
use utf8;
use Data::Dumper;
# use bignum;

&main();

sub solve
{
	my ($qno) = @_;
	my $line = <STDIN>;
	chomp($line);
	my $astr = $line;
	
	$line = <STDIN>;
	chomp($line);
	my $bstr = $line;
	
	my @achs = split("", $astr);

	my @patterns = ($achs[0], ".*");
	my @anses;
	my $cont = 1;
	my $counter = 1;
	while(1) {
		for my $ptn (@patterns) {
			if (($astr =~ /^${ptn}$/) && ($bstr !~ /^${ptn}$/)) {
				my $tmp = $ptn;
				$tmp =~ s/\.//g;
				push(@anses, $tmp);
			}
		}
		
		if ($counter == scalar(@achs)) {
			last;
		}

		my @newPatters = ();
		for my $ptn (@patterns) {
			push(@newPatters, $ptn . $achs[$counter]);
			
			if (substr($ptn, -1, 1) ne "*") {
				push(@newPatters, $ptn . ".*");
			}
			else {
				push(@newPatters, $ptn);
			}
		}
		$counter++;
		@patterns = @newPatters;

#		print Dumper \@patterns; 
	}


	# find best ans
	@anses = sort { length($a) <=> length($b) } @anses ;

	my $asterNum = 100000;
	my @newAns;
	my $len = length($anses[0]);
	for my $ans (@anses) {
		if (length($ans) != $len) {
			next;
		}
		my $num = $ans =~ tr/\*/\*/;
		if ($num < $asterNum) {
			@newAns = ();
			push(@newAns, $ans);
			$asterNum = $num;
		}
		elsif ($num == $asterNum) {
			push(@newAns, $ans);
		}
	}
	
	@newAns = sort @newAns;
	$newAns[0] =~ s/\.//g;

	print "Case #$qno: " . $newAns[0] . "\n"
}
sub main
{
	my $T = <STDIN>;
	for my $i (0..$T - 1)
	{
		solve($i + 1);
	}

}
