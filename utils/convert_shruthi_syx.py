#!/usr/bin/python2.5
#
# Copyright 2011 Emilie Gillet.
#
# Author: Emilie Gillet (emilie.o.gillet@gmail.com)
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.
#
# -----------------------------------------------------------------------------

"""Tool for converting a bunch of Shruthi-1 syx into a patch text file."""

import logging
import optparse
import os
import struct

def main(options, args):
  for f in args:
    data = file(f, 'rb').read()[8:-3]
    string = ''.join(map(lambda x: '0123456789abcdef'[x], map(ord, data)))
    name = ''
    for i in xrange(68, 76):
      name += chr(int(string[i * 2:i * 2 + 2], 16))
    print 'patch\t%s\t%s' % (name, string)


if __name__ == '__main__':
  parser = optparse.OptionParser()
  options, args = parser.parse_args()
  if not len(args):
    logging.fatal('Specify files')
  else:
    main(options, args)
