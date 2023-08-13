#ifndef GENEPOOL_H
#define GENEPOOL_H

#include "Person.h"

#include <istream>
#include <string>
#include <map>



class GenePool {
  // Member Variables
  std::map<std::string, Person*> my_map;
  std::string name;
  Person* father;
  Person* mother;
  std::string gender_str;
  Gender gender;

  //std::string child;
  // Helper Functions

public:
  // Build a database of people from a TSV file.
  GenePool(std::istream& stream);

  //Destructor
  ~GenePool();

  Person* find(const std::string& name) const;
};

#endif
