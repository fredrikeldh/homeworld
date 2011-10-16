#!/usr/bin/env python

import os, sys, subprocess

#def which(cmd):
#	return subprocess.check_output('which ' + cmd, executable='/bin/bash',shell=True).rstrip('\n\r')

args = list(sys.argv)
del args[0] # Remove our exec name
compiler = args[0] 
del args[0] # Remove the compile name

#compiler = which(compiler)
#compiler = which.which(compiler)

compileArguments = [compiler]
outputFile = ''

foundFile = False

for arg in args:
	if arg.startswith('-o'):
		foundFile = True
	elif foundFile:
		outputFile = arg
		foundFile = False
		arg = "/dev/stdout"

	compileArguments.append(arg)

#compileArguments.append('-S')

#print compileArguments

compileProcess = subprocess.Popen(compileArguments, stdout=subprocess.PIPE)
#print outputFile
asbin = '/home/andreas/bin/llvm-as'

#asbin = which(asbin)
#print asbin
#asbin = which.which(asbin)

ir2bcProcess = subprocess.Popen([asbin, '-f', '-o=' + outputFile], stdin=compileProcess.stdout)

#stdout, stderr = compileProcess.communicate()
stdout, stderr = ir2bcProcess.communicate()

#if stdout != None:
#	print "OUT START"
#	print stdout
#	print "OUT END"

#if stderr != None:
#	print "ERR START"
#	print stderr
#	print "ERR END"

compileProcess.wait()

if compileProcess.returncode is not 0:
	os.remove(outputFile)
	sys.exit(compileProcess.returncode)

ir2bcProcess.wait()
if ir2bcProcess.returncode is not 0:
	os.remove(outputFile)
	sys.exit(ir2bcProcess.returncode)


#print data
#(stdoutdata, stderrdata)

