#include "GenePool.h"
#include <iostream>
#include <sstream>
#include <string>


// GenePool Member Functions

GenePool::GenePool(std::istream& stream){
    std::string line;
    std::string token;
    
    while(std::getline(stream, line)){
        if(line[0] == '#' || line.empty() == true){
            continue;
        }else{
            std::istringstream token_stream(line);
            getline(token_stream, token, '\t');
            name = token;
            getline(token_stream, token, '\t');
            gender_str = token;
            if(gender_str == "female"){
                gender = Gender::FEMALE;
            }else{
                gender = Gender::MALE;
            }
            getline(token_stream, token, '\t');
            mother = find(token);
            getline(token_stream, token, '\t');
            father = find(token);

            Person* new_Person = new Person(name, gender, mother, father);
            my_map.insert({name, new_Person});
            if(mother != nullptr){
                mother->person_children.insert(new_Person);
            }

            if(father != nullptr){
                father->person_children.insert(new_Person);
            }
        }
    }
}

GenePool::~GenePool(){
    for(auto itr = my_map.begin(); itr != my_map.end(); itr++){
        delete itr->second;
    }
}

Person* GenePool::find(const std::string& name) const{
    auto itr = my_map.find(name);
    if(itr != my_map.end()){
        return itr->second;
    }else{
        return nullptr;
    }
}