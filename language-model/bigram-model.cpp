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
