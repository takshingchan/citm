#!/usr/bin/perl
#
#  shares.pl
#
#  This script converts EsAC files into a shell archive.
#
#  Copyright (C) 2017 Tak-Shing Chan
#

use strict;
use warnings;

$/ = "";

# Look for KEY records
print "#!/bin/sh\n";
print "# This is a shell archive.\n";
while (<>) {
  chomp;
  if (/KEY\[(\w+)/) {
    print "echo x - $1\n";
    print "cat > $1 << EOF\n";
    print "$_\n";
    print "EOF\n";
  }
}
