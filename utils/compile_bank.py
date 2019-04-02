#!/usr/bin/python2.5
#
# Copyright 2012 Emilie Gillet.
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

"""Tool for building a bank of Ambika patches."""

import optparse
import os

def main(options, args):
  for index, line in enumerate(file(args[0])):
    tokens = line.strip().split('\t')
    source, name = tuple(tokens)
    data = file(source, 'rb').read()
    data = data[:20] + ('%-15s' % name) + data[35:]
    destination = os.path.join(args[1], '%03d.PRO' % index)
    file(destination, 'wb').write(data)


if __name__ == '__main__':
  parser = optparse.OptionParser()
  options, args = parser.parse_args()
  main(options, args)
