#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <fstream>

using namespace std;

#include "dictionary.h"
#include "doublets.h"

/* You are pre-supplied with the functions below. Add your own 
   function definitions to the end of this file. */

/* Looks up a given word in the dictionary of approved words. 
   Returns true if the word is in the dictionary.
   Otherwise returns false. */

bool dictionary_search(const char *word) {
  static Dictionary dictionary("words.txt");
  return dictionary.search(word);
}

/* add your function definitions here */

bool valid_step(const char *cur_word, const char *next_word) {
  if (strlen(cur_word) != strlen(next_word) || !dictionary_search(next_word))
    return false;

  int changes = 0;

  for (int i = 0; cur_word[i] != '\0'; ++i) {
    if (cur_word[i] != next_word[i])
      ++changes;
  }

  if (changes > 1)
    return false;

  return true;
}

bool display_chain(const char *chain[], ostream &output) {
  output << chain[0] << endl;
  int i = 1;
  while (chain[i+1] != NULL) {
    for (int j = 0; chain[i][j] != '\0'; ++j)
      output << (char) tolower(chain[i][j]);
    
    output << endl;
    ++i;
  }

  output << chain[i] << endl;
  return true;
}

bool valid_chain(const char *chain[]) {
  for  (int i = 0; chain[i+1] != NULL; ++i) {
    if (!valid_step(chain[i], chain[i+1]))
      return false;

    for (int j = i+1; chain[j] != NULL; ++j) {
      if (!strcmp(chain[i], chain[j]))
        return false;
    }
  }
  
  return true;
}

bool find_chain(const char *start_word, const char *target_word, const char *answer_chain[], const int max_steps) {
  static int step_no = 0;

  if (step_no == 0) {
    for (int i = 0; answer_chain[i] != NULL; ++i) {
      answer_chain[i] = NULL;
    }
  }

  if (!strcmp(start_word, target_word))
    return true;

  if (step_no == max_steps)
    return  false;

  ++step_no;
  for (int i = 0; start_word[i] != '\0'; ++i) {
    for (char ch = 'A'; ch <= 'Z'; ++ch) {
      if (start_word[i] == ch)
        continue;

      char *new_word = new char[30];
      strcpy(new_word, start_word);
      new_word[i] = ch;

      answer_chain[step_no - 1] = new_word;
      answer_chain[step_no] = NULL;

      if (valid_chain(answer_chain)) {
        if (find_chain(new_word, target_word, answer_chain, max_steps)) {
          --step_no;
          return true;
        }
      }
      
      delete[] new_word;
    }
  }

  --step_no;
  answer_chain[step_no] = NULL;
  return false;
}