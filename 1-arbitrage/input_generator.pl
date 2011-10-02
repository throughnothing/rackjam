#!/usr/bin/env perl
use v5.14;

my $n = $ARGV[0] or die "Must provide a dimension n";
open my $out, '>generated_input.txt';

sub disp{ 
    print $out $_[0];
    print $_[0];
};

disp("$n\n");
for(1 .. $n){
    for(1 .. $n-1){
        disp(rand() + .03 . ' ');
    }
    disp("\n");
}
