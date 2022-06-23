#pragma once

#include "bigram-model.hpp"

void BigramModel::IncreaseBigramCount(string w_1, string w_2) {
  bigram_counts_[w_1][w_2] += 1;
  return;
}

void BigramModel::ReadText(string text_path) {
  // TODO: Have safer error checking for opening file!
  std::ifstream myfile; myfile.open("language-model/data/sample.txt");

  string curr_word;
  string prev_word = kBoundaryTag;

  // TODO: Have a better way of reading through file. (This works for now).
  while (myfile.good()) {
    myfile >> curr_word;
    IncreaseBigramCount(prev_word, curr_word);
    prev_word = curr_word;
  }

  IncreaseBigramCount(prev_word, kBoundaryTag);


  return;
}

size_t BigramModel::GetCount(string w) {
  // If the word w does not exist in our model, the count is equal to zero!
  if (bigram_counts_.count(w) == 0) return 0;

  // Otherwise, we get a map to all of the words that follow w, and their counts.
  map<string, size_t> counts = bigram_counts_.at(w);
  size_t total = 0;

  for (std::map<string,size_t>::iterator it=counts.begin(); it!=counts.end(); ++it) total += it->second;

  return total;
}
