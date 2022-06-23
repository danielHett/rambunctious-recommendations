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

string BigramModel::EstimateNextWord(string previous_text) {
  istringstream sentence(previous_text);
  string last_word;

  do {
    sentence >> last_word;
  } while (sentence);

  // TODO: We need a way to deal with words we don't have in model (UNK token?).
  size_t denominator = GetCount(last_word);
  map<string, size_t> bigrams = bigram_counts_.at(last_word);
  string most_likely_token;
  double highest_probability = 0;

  for (std::map<string,size_t>::iterator it=bigrams.begin(); it!=bigrams.end(); ++it) {
    double probability = (double)it->second / (double)denominator;

    if (probability > highest_probability) {
      most_likely_token = it->first;
      highest_probability = probability;
    }
  }

  return most_likely_token;
}
