#ifndef WORD_H
#define WORD_H
#include "chic.h"
Type Word { // The different perspectives of a word.
  Representation {
    perspective(Long l)        
    perspective(Short s1, s2)      
  };
  Word(Short, Short);
  Word();
  Property(Short hash);
};
#endif
