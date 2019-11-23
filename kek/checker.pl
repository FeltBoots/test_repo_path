my $a = 'MyTxt-.lol';
#if ($a =~ s/[A-Za-z0-9_\-.]//g) {
if ($a =~ /^((?!-)[\w,\s-]+\.[A-Za-z]{1,})$/) {
    print "All right";
} else {
    print "ERROR!!\n";
}
