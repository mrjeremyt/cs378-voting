// --------------------------------
// projects/Voting/Voting.h
// Copyright (C) 2014
// Jeremy Thompson
// Daniel Durbin
// --------------------------------


#ifndef Voting_h
#define Voting_h

// --------
// includes
// --------
#include <iostream>
#include <utility>

void run_elections(std::istream&, std::ostream&);

int read_num_candidates(std::istream&);

void read_candidates(std::istream& in, int num_candidates);

#endif // Voting_h