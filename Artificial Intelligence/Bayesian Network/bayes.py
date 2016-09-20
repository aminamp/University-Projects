# CSCI 561 - HW3
# By Amin Amiripour (amiripou@usc.edu)

import copy
import sys
from decimal import Decimal


class Network:
	def __init__(self):
		self.variables = []
		self.nodes = {}


	def add(self, label, parents, table):
		myNetwork = NetworkNodes(label,parents,table)
		self.nodes[label] = myNetwork
		self.variables.append(label)
		for i in myNetwork.parents:
			self.nodes[i].children[label] = myNetwork



class NetworkNodes:
	def __init__(self, label, parents, table):
		self.label = label
		self.parents = parents
		self.children = {}		
		self.table = table


	def prob(self, label, condition):
		probability = self.table[ match(condition, self.parents) ]
		if label:
			answer = probability
			return answer
		else:
			answer = 1 - probability
			return answer



class Probabilities:
	def __init__(self, query):
		self.variables =  [key for key in query]
		self.prob = {}		
		self.final = match(query, self.variables)
		self.permutation([], 0, len(self.variables) )


	def __init__(self, query, parents):
		self.variables = parents
		self.prob = {}
		self.final = match(query, self.variables)
		self.permutation([], 0, len(self.variables) )


	def permutation(self,  myList, index, length):
		if index >= length:
			self.prob[ tuple( myList ) ] = 0.0
			return;

		myList.append(True)
		self.permutation(myList, index+1, length)
		myList.pop()
		
		myList.append(False)
		self.permutation(myList,index+1, length)
		myList.pop()


	def normalizer(self):
		total = 0.00
		for i in self.prob:
			total = total + self.prob[i]
		
		if total < 0:
			return 0.0
		elif total == 0:
			return 0.0
		else:
			return self.prob[self.final] / total


def expand(myEvidence,variables,values):
	temp = copy.deepcopy(myEvidence)
	for i in range( len(variables) ):
		temp[variables[i]] = values[i]
	return temp


def match(condition, parents):
	if len(parents) != 0:
		temp = []
		for i in parents:
			temp.append(condition[i])
		return tuple(temp)
	else:
		return ()


def Dexpand(myEvidence,variables):
	temp = copy.deepcopy(myEvidence)
	for i in variables:
		temp[i] = variables[i]
	return temp


def enumeration(label, myEvidence, myNetwork):
	query = Probabilities(label,[i for i in label])
	for i in query.prob:
		query.prob[i] = enumAll(myNetwork.variables, expand(myEvidence, query.variables, i), myNetwork)
	return query.normalizer()



def enumAll(variables, myEvidence, myNetwork):
	if len(variables) == 0:
		return 1.0

	if not variables:
		return 1.0
	
	if variables[0] in myEvidence:
		return myNetwork.nodes[variables[0]].prob(myEvidence[variables[0]], myEvidence) * enumAll(variables[1:], myEvidence, myNetwork)
	else:
		temp = []
		temp.append(variables[0])
		return myNetwork.nodes[variables[0]].prob(True, myEvidence) * enumAll(variables[1:], expand(myEvidence, temp, (True,)), myNetwork) + myNetwork.nodes[variables[0]].prob(False, myEvidence) * enumAll(variables[1:], expand(myEvidence, temp, (False,)), myNetwork)



if __name__ == "__main__":

	inputFile = open(sys.argv[1], "r")
	number = int(inputFile.readline().strip())
	queries , evidences = [], []

	for i in range( 0, number ):

		readBuffer = inputFile.readline().strip()
		label = readBuffer.split("(")[0]
		variables = ((readBuffer.split("(")[1]).split(")")[0].strip()).split("|")
		
		if len( variables ) != 1:
			tempQuery, tempEvidence = {}, {}
			for temp in (variables[0].strip()).split(","):
				if (temp.strip()).split("=")[1].strip() == "-":
					tempQuery[(temp.strip()).split("=")[0].strip()] = False
				else:
					tempQuery[(temp.strip()).split("=")[0].strip()] = True
					

			for temp in (variables[1].strip()).split(","):
				if ((temp.strip()).strip()).split("=")[1].strip() == "-":
					tempEvidence[((temp.strip()).strip()).split("=")[0].strip()] = False
				else:
					tempEvidence[((temp.strip()).strip()).split("=")[0].strip()] = True
			queries.append( tempQuery )
			evidences.append( tempEvidence )

		else:
			tempQuery, tempEvidence = {}, {}
			for temp in (variables[0].strip()).split(","):
				if (temp.strip()).split("=")[1].strip() == "-":
					tempQuery[(temp.strip()).split("=")[0].strip()] = False
				else:
					tempQuery[(temp.strip()).split("=")[0].strip()] = True
			queries.append( tempQuery )
			evidences.append( tempEvidence )			
	
	myNetwork = Network()
	label = None
	readBuffer = "***"
	parent, table = [], {}
	while readBuffer:
		if readBuffer[0] != "*":
			readBuffer = readBuffer.strip()
			tempKey = []
			for i in readBuffer.split(" ")[1:]:
				if i == '-':
					tempKey.append(False)
				else:
					tempKey.append(True)
			table[tuple(tempKey)] = float(readBuffer.split(" ")[0])

		else:
			if label != None:
				myNetwork.add(label,parents,copy.deepcopy(table))
				table = {}
			readBuffer = inputFile.readline().strip()
			if len( readBuffer.split("|") ) > 1:
				label = readBuffer.split("|")[0].strip()
				parents = readBuffer.split("|")[1].strip().split(" ")
			else:
				label = readBuffer.split("|")[0].strip()
				parents = []

		readBuffer = inputFile.readline()

	myNetwork.add(label,parents,copy.deepcopy(table))
	inputFile.close()
	outputFile = open("output.txt", "w")

	for i in range( len(queries) ):
		result = enumeration( queries[i], evidences[i], myNetwork )
		convertedResult = Decimal( str( float (result) ) )
		outputFile.write( str( convertedResult.quantize( Decimal('.01') ) ) )
		if i != len(queries) -1:
			outputFile.write("\n")

	outputFile.close()





