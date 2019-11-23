my $a = 'aaa';
if ($a =~ s/[A-Za-z0-9_\-.]//g) {
print "invalid file name\n";
} else {
print "valid file name\n";
}

