#!/usr/bin/python

"""
Output lines selected randomly from a file

Copyright 2005, 2007 Paul Eggert.
Copyright 2010 Darrell Benjamin Carbajal.

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

Please see <http://www.gnu.org/licenses/> for a copy of the license.

$Id: randline.py,v 1.4 2010/04/05 20:04:43 eggert Exp $
"""

import random, sys
from optparse import OptionParser

class randline:
    def __init__(self, filename):
        f = open(filename, 'r')
        self.lines = f.readlines()
        f.close()
    def makeUnique(self):
        self.lines = list(set(self.lines))

    def nLines(self):
        return len(self.lines)
        
    def chooseline(self,notReplaceable):
        tempChoice=random.choice(self.lines)
        if(notReplaceable==1):
            self.lines.remove(tempChoice)
        return tempChoice

def main():
    version_msg = "%prog 2.0"
    usage_msg = """%prog [OPTION]... FILE...

Output randomly selected lines from selected FILE(s)."""

    parser = OptionParser(version=version_msg,
                          usage=usage_msg)
    parser.add_option("-n", "--numlines",
                      action="store", dest="numlines", default=1,
                      help="output NUMLINES lines (default 1)")
    parser.add_option("-u", "--unique",
                      action="store_true", dest="unique", default=False,
                      help="allows for each different line to have same prob")
    parser.add_option("-w", "--without-replacement",
                      action="store_true", dest="without", default=False,
                      help="outputs wihout replacing the string in the list")
    options, args = parser.parse_args(sys.argv[1:])

    try:
        numlines = int(options.numlines)
    except:
        parser.error("invalid NUMLINES: {0}".
                     format(options.numlines))
    if numlines < 0:
        parser.error("negative count: {0}".
                     format(numlines))
    if len(args) < 1:
        parser.error("wrong number of operands")

    for n in args:
        try:
            gen=randline(n)
        except IOError as halp:
            errno,strerror=halp.args
            parser.error("I/O error({0}): {1}".
                         format(halp.args[0], halp.args[1]))

        
    setup=open("temp.txt",'w')
    setup.write("")
    setup.close()
    
    for x in args:
        tempFile=open(x,'r')
        tempLines=tempFile.readlines()
        length=len(tempLines)
        if tempLines[length-1][-1]!='\n':
            tempLines[length-1]=tempLines[length-1]+'\n'
        newFile=open("temp.txt",'a')
        newFile.writelines(tempLines)
        newFile.close()
        
    input_file = "temp.txt"

    try:
        generator = randline(input_file)
        if(options.unique==True):
            generator.makeUnique()
        if(numlines>generator.nLines()):
            parser.error("Not enough lines in file")
        for index in range(numlines):
            if(options.without==True):
                sys.stdout.write(generator.chooseline(1))
            else:
                sys.stdout.write(generator.chooseline(0))
    except IOError as halp:
        errno,sterror=halp.args
        parser.error("I/O error({0}): {1}".
                     format(halp.args[0], halp.args[1]))

if __name__ == "__main__":
    main()
