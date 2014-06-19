import sys
import random
 
names = []
 
def read_names():
	global names
	with open("50names.txt", 'r') as names_file:
		for n in names_file:
			names.append(n.rstrip())
 
def get_num_candidates():
	can = input()
	return int(can)
 
def name_list_maker(num_candidates):
	global names
	candidates = [0] * num_candidates
	s = set()
	while (len(s) < num_candidates):
		s.add(random.randint(1,len(names)))
	count = 0
	for n in list(s):
		candidates[count] = names[n]
		count += 1
	return candidates
 
def ballots(num_candidates):
	weight = num_candidates * 25
	ballot_list = []
	while(weight > 0):
		s = set()
		while (len(s) < num_candidates):
			s.add(random.randint(1, num_candidates))
		s = random.sample(s, len(s))
		ballot_list.append(s)
		weight -= 1
	return ballot_list
 
def print_ballots(ballot_list):
	w = sys.stdout
	for s in ballot_list:
		for v in s:
			w.write(str(v) + " ")
		w.write("\n")
	print()
 
def election():
	global names
 
	read_names()
	num_candidates = get_num_candidates()
	name_list = name_list_maker(num_candidates)
	ballot_list = ballots(num_candidates)
	print(num_candidates)
	for n in name_list:
		print(n)
	print_ballots(ballot_list)
 
def main():
	num_elections = input()
	print(num_elections + "\n")
	num_elections = int(num_elections)
	while(num_elections > 0):
		election()
		num_elections -= 1
 
 
main()