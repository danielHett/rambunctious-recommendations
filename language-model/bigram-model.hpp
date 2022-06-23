#pragma once

#define BOUNDARY_CONST "<s>"

#include <iostream>
#include <map>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

class BigramModel {
public:
  // This is the bigram counts map. The key is the first word in a bigram, and the value is
  // another map. This new map has the second word in a bigram as the key, and the value is
  // the count of that bigram.
  map<string, map<string,size_t> > bigram_counts_;

  // This is the constant for the beginning and end of a document.
  const string kBoundaryTag = "<s>";

  // This function takes the provided bigram and updates the model.
  void IncreaseBigramCount(string w_1, string w_2);

  // This function loops through provided training data and extracts
  // each bigram to train the model. Successive calls don't reset the
  // model, but rather update it.
  void ReadText(string text_path);

  // This function gets the total count of the given word in the model.
  size_t GetCount(string w);

//public:

  //BigramModel();

  /**
  * This function accesses the /language-model/data/ directory
  * and trains on all text files found inside.
  */
  void TrainModel();

  /**
  * This function takes a given string and returns the token
  * that is most likely to follow.
  */
  string EstimateNextWord(string previous_text);
};
