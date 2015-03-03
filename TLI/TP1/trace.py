#!/usr/bin/env python
# -*- coding: utf-8 -*-

import sys
from math import *
from subprocess import call


def trace(function, xmin, xmax, nstep, output):
	output.write("x, %s\n" % function)
	function = eval("lambda x:" + function)
	
	step = 1.*(xmax-xmin)/nstep
	for i in range(nstep+1):
		x = xmin + i*step
		try:
			y = function(x)
		except:
			print("La fonction mathématique n'est pas definie sur %d" % x)
			continue
		output.write("%s, %s\n" % (x, y))
		
		
def dessiner(function, xmin, xmax, nstep):
	output = file("dessiner.ps", "w")
	print("Ecriture dans le fichier :")
	fun = function
	function = eval("lambda x:" + function)
	
	#mise en page
	output.write("280 420 translate \n")
	output.write("90 rotate \n")
	
	#texte
	output.write("/Times-Roman findfont \n")
	output.write("20 scalefont \n")
	output.write("setfont \n")
	output.write("newpath \n")
	output.write("275 -275 moveto \n")
	output.write("(Fonction : " + fun + ") \n")
	output.write("show \n")
	
	#courbe
	output.write("newpath \n")
	step = 1.*(xmax-xmin)/nstep
	for i in range(nstep+1):
		x = xmin + i*step
		try:
			y = function(x)
		except:
			print("Indefinis")
			continue
		if i == 0:
			ymin = y;
			ymax = y;
			output.write("%s %s moveto \n" % (x*100, y*100))
		else :
			if ymin > y :
				ymin = y
			if ymax < y :
				ymax = y
			output.write("%s %s lineto \n" % (x*100, y*100))
	output.write("1 0 0 setrgbcolor	\n");
	output.write("[] 0 setdash \n")	
	output.write("stroke \n")
	
	#axes
	output.write("newpath \n")
	output.write("0 400 moveto \n")
	output.write("0 -400 lineto \n")
	output.write("800 0 moveto \n")
	output.write("-800 0 lineto \n")
	output.write("0 0 0 setrgbcolor	\n");
	output.write("stroke \n")	
	
	#pointillés
	output.write("newpath \n")
	for i in range( (int(ymin)-1)*2, (int(ymax)+1)*2+1):
		if i != 0 :
			output.write("-400 %s moveto \n" % (i*50))
			output.write("400 %s lineto \n" % (i*50))
	for i in range( int(xmin)*2, (int(xmax)+1)*2):
		if i != 0 :
			output.write("%s -100 moveto \n" % (i*50))
			output.write("%s 100 lineto \n" % (i*50))
	output.write("[4 4] 0 setdash \n")
	output.write("stroke \n")
	
	#graduation
	output.write("/Times-Roman findfont \n")
	output.write("10 scalefont \n")
	output.write("setfont \n")
	for i in range( (int(ymin)-1)*2, (int(ymax)+1)*2+1):
		if i != 0 :
			output.write("newpath \n")
			output.write("0 %d moveto \n" % (int(i)*50+2) )
			output.write("(%s) \n" % (int(i)*0.5) )
			output.write("show \n")
	for i in range( int(xmin)*2, (int(xmax)+1)*2):
		output.write("newpath \n")
		output.write("%d 0 moveto \n" % (int(i)*50+2) )
		output.write("(%s) \n" % (int(i)*0.5) )
		output.write("show \n")
	
	print("Complete")
	output.close()
	call (["ghostscript", "dessiner.ps"] )
	
	

		

def main(argv=None):
	if argv is None:
		argv = sys.argv
	
	import getopt
	try:
		options, argv = getopt.getopt(argv[1:], "o:d", ["output="])
	except getopt.GetoptError as message:
		sys.stderr.write("%s\n" % message)
		sys.exit(1)
	
	if len(argv) == 1 :
		function = argv[0]
		output = sys.stdout
		xmin, xmax = -2., 2.
		nstep = 10
	elif len(argv) == 4 :
		try:
			function = argv[0]
			xmin = float(argv[1])
			xmax = float(argv[2])
			nstep = int(argv[3])
			output = sys.stdout
		except ValueError as message:
			sys.stderr.write("%s\n" % message)
			print("Rappel : \"fonction\" float float int")
			sys.exit(1)
	else :
		print("Erreur lors de l'utilisation de la fonction !!")
		print("")
		print("Utilisation possible : ")
		print("")
		print("-> Veuillez entrer un argument valide : une fonction mathématique valide entre guillemets.")
		print("		Exemple d'utilisation : ./trace.py \"sin(x)\" ")
		print("")
		print("-> Vous pouvez aussi entrer la valeur de départ, la valeur maximale à atteindre et le nombre d'etapes :")
		print("		Exemple d'utilisation : ./trace.py \"sin(x)\" 0.0 1.0 10 ")
		print("")
		print("-> Il est possible de spécifier un fichier de sortie: ./trace.py [-o | --output, fichier] \"sin(x)\" [arguments] ")
		print("")
		print("-> Il est egalement possible de sortir le resultat sous la forme d'un graphiques")
		print("		Exemples d'utilisation : ./trace.py -d \"cos(x)\" ")
		print("-> Vous pouvez aussi entrer la valeur de départ, la valeur maximale à atteindre et le nombre d'etapes :")
		print("		Exemples d'utilisation : ./trace.py -d \"cos(x)\" -4, 4, 1000")
		sys.exit(1)
	
	for option, value in options:
		if option in ["-o", "--output"]:
			print("Ecriture realisée dans le fichier : %s\n" % value)
			output = file(value, "w")
		elif option in ["-d"] :
			dessiner(function, -4, 4, 1000)
			sys.exit(1)
		elif option in ["-dd"] :
			dessiner(function, xmin, xmax, nstep, output)
			sys.exit(1)
		else:
			assert False, "unhandled option"
			
	trace(function, xmin, xmax, nstep, output)


if __name__ == "__main__":
	sys.exit(main())
