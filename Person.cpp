#include "Person.h"
#include <iostream>

// Person Member Functions
Person::Person(std::string name, Gender gender, Person* Mom, Person* Dad){
    this->my_name = name;
    this->my_gender = gender;
    this->Mom = Mom;
    this->Dad = Dad;
}

const std::string& Person::name() const{
    return my_name;
};

Gender Person::gender() const{
    return my_gender;
}

Person* Person::mother(){
    if(Mom != nullptr){
        return Mom;
    }else{
        return nullptr;
    }
}

Person* Person::father(){
    if(Dad != nullptr){
        return Dad;
    }else{
        return nullptr;
    }
}











std::set<Person*> Person::ancestors(PMod pmod){
    std::set <Person*> ancestors;
    std::set <Person*> p_itr = parents(pmod);
    
    //Base case
    if(p_itr.empty() == false){
        for(Person* parents : p_itr){
            std::set<Person*> gp = parents->ancestors();
            ancestors.merge(gp);
        }
    }
    ancestors.merge(p_itr);
    return ancestors;
}

std::set<Person*> Person::aunts(PMod pmod, SMod smod){
    std::set <Person*> aunts;
    std::set <Person*> p_itr = parents(pmod);

    for(Person* parent : p_itr){
        std::set <Person*> s_itr = parent->siblings(pmod = PMod::ANY, smod);
        for(Person* sib : s_itr){
            if(sib->gender() == Gender::FEMALE && sib != nullptr){
                aunts.insert(sib);
            }
        }
    }

    return aunts;
}

std::set<Person*> Person::brothers(PMod pmod, SMod smod){
    std::set <Person*> brothers;
    std::set <Person*> b_itr = siblings(pmod, smod);

    for(Person* bro : b_itr){
        if(bro->gender() == Gender::MALE && bro != nullptr){
            brothers.insert(bro);
        }
    }
    return brothers;
}

//
std::set<Person*> Person::children(){
    return person_children;
}

std::set<Person*> Person::cousins(PMod pmod, SMod smod){
    std::set <Person*> cousins;
    std::set<Person*> a_itr = aunts(pmod, smod);
    std::set<Person*> u_itr = uncles(pmod, smod);

    for(Person* aunt : a_itr){
        for(Person* cousin : aunt->person_children){
            if(cousin != nullptr){
                cousins.insert(cousin);
            }
        }
    }

    for(Person* uncle : u_itr){
        for(Person* cousin : uncle->person_children){
            if(cousin != nullptr){
                cousins.insert(cousin);
            }
        }
    }

    return cousins;
}

//
std::set<Person*> Person::daughters(){
    std::set <Person*> daughters;
    for(Person* child : person_children){
        if(child->gender() == Gender::FEMALE){
            daughters.insert(child);
        }
    }

    return daughters;
}

std::set<Person*> Person::descendants(){
    std::set<Person*> descendants;
    std::set<Person*> children = person_children;
    
    if(person_children.empty() == false){
        for(Person* child : children){
            std::set <Person*> youth = child->descendants();
            descendants.merge(youth);
        }
    }
    descendants.merge(children);
    return descendants;
}

std::set<Person*> Person::grandchildren(){
    std::set <Person*> grandchildren;

    for(Person* child : person_children){
        std::set<Person*> grand_children = child->person_children;
        for(Person* gc : grand_children){
            if(gc != nullptr){
                grandchildren.insert(gc);
            }
        }
    }

    return grandchildren;
}

std::set<Person*> Person::granddaughters(){
    std::set <Person*> granddaughters;
    std::set <Person*> gd_itr = grandchildren();

    for(Person* gc : gd_itr){
        if(gc->gender() == Gender::FEMALE && gc != nullptr){
            granddaughters.insert(gc);
        }
    }

    return granddaughters;
}

std::set<Person*> Person::grandfathers(PMod pmod){
    std::set <Person*> grandfathers;
    std::set <Person*> gf_itr = grandparents(pmod);

    for(Person* gf : gf_itr){
        if(gf->gender() == Gender::MALE){
            if(gf != nullptr){
                grandfathers.insert(gf);
            }
        }
    }

    return grandfathers;
}

std::set<Person*> Person::grandmothers(PMod pmod){
    std::set <Person*> grandmothers;
    std::set <Person*> gm_itr = grandparents(pmod);

    for(Person* gm : gm_itr){
        if(gm->gender() == Gender::FEMALE){
            if(gm != nullptr){
                grandmothers.insert(gm);
            }
        }
    }
    
    return grandmothers;
}

std::set<Person*> Person::grandparents(PMod pmod){
    std::set <Person*> grandparents;
    if(pmod == PMod::MATERNAL){
        if(mother() != nullptr){
            for(Person* parents : mother()->parents()){
                if(parents != nullptr){
                    grandparents.insert(parents);
                }
            }
        }
    }else if(pmod == PMod::PATERNAL){
        if(father() != nullptr){
            for(Person* parents : father()->parents()){
                if(parents != nullptr){
                    grandparents.insert(parents);
                }
            }
        }
    }else{
        if(father() != nullptr){
            for(Person* parents : father()->parents()){
                if(parents != nullptr){
                    grandparents.insert(parents);
                }
            }
        }
        if(mother() != nullptr){
            for(Person* parents : mother()->parents()){
                if(parents != nullptr){
                    grandparents.insert(parents);
                }
            }
        }
    }
    return grandparents;
}

std::set<Person*> Person::grandsons(){
    std::set <Person*> grandsons;
    std::set <Person*> gs_itr = grandchildren();

    for(Person* gc : gs_itr){
        if(gc->gender() == Gender::MALE && gc != nullptr){
            grandsons.insert(gc);
        }
    }

    return grandsons;
}

std::set<Person*> Person::nephews(PMod pmod, SMod smod){
    std::set<Person*> nephews;
    std::set<Person*> n_itr = siblings(pmod, smod);

    for(Person* sib : n_itr){
        for(Person* child : sib->person_children){
            if(child->gender() == Gender::MALE){
                if(child != nullptr){
                    nephews.insert(child);
                }
            }
        }
    }

    return nephews;
}

std::set<Person*> Person::nieces(PMod pmod, SMod smod){
    std::set<Person*> nieces;
    std::set<Person*> n_itr = siblings(pmod, smod);

    for(Person* sib : n_itr){
        for(Person* child : sib->person_children){
            if(child->gender() == Gender::FEMALE){
                if(child != nullptr){
                    nieces.insert(child);
                }
            }
        }
    }

    return nieces;

}

//
std::set<Person*> Person::parents(PMod pmod){
    std::set <Person*> parents;
    if(pmod == PMod::MATERNAL){
        if(mother() != nullptr){
            parents.insert(mother());
        }
    }else if (pmod == PMod::PATERNAL){
        if(father() != nullptr){
            parents.insert(father());
        }
    }else{
        if(father() != nullptr){
            parents.insert(father());
        }
        if(mother() != nullptr){
            parents.insert(mother());
        }
    }
    return parents;
}

std::set<Person*> Person::siblings(PMod pmod, SMod smod){
    std::set<Person*> siblings;
    std::set<Person*> s_itr = parents(pmod);
    SMod this_smod = smod;


    for(Person* p : s_itr){
        for(Person* parent_child : p->person_children){
            if(parent_child->mother() != nullptr || parent_child->father() != nullptr){
                if(this_smod == SMod::HALF){
                    if((parent_child->mother() == mother() && parent_child->father() != father()) ||
                    (parent_child->mother() != mother() && parent_child->father() == father())){
                        if(parent_child != nullptr && parent_child->name() != name()){
                            siblings.insert(parent_child);
                        }
                    }
                }else if(this_smod == SMod::FULL){
                    if(parent_child->mother() == mother() && parent_child->father() == father() && 
                    parent_child->mother() != nullptr && parent_child->father() != nullptr){
                        if(parent_child != nullptr && parent_child->name() != name()){
                            siblings.insert(parent_child);
                        }
                    }
                }else{
                    if((parent_child->mother() == mother() && parent_child->father() != father()) ||
                    (parent_child->mother() != mother() && parent_child->father() == father())){
                        if(parent_child != nullptr && parent_child->name() != name()){
                            siblings.insert(parent_child);
                        }
                    }else{
                        if(parent_child->mother() == mother() && parent_child->father() == father()){
                            if(parent_child != nullptr && parent_child->name() != name()){
                                siblings.insert(parent_child);
                            }
                        }
                    }
                }
            }
        }
    }



    return siblings;
}

std::set<Person*> Person::sisters(PMod pmod, SMod smod){
    std::set<Person*> sisters;
    std::set<Person*> sib_itr = siblings(pmod, smod);

    

    for(Person* sib : sib_itr){
        if(sib->gender() == Gender::FEMALE && sib != nullptr){
            sisters.insert(sib);
        }
    }

    return sisters;
}

//
std::set<Person*> Person::sons(){
    std::set<Person*> sons;
    for(Person* child : person_children){
        if(child->gender() == Gender::MALE){
            sons.insert(child);
        }
    }
    return sons;
}

std::set<Person*> Person::uncles(PMod pmod, SMod smod){
    std::set <Person*> uncles;
    std::set <Person*> p_itr = parents(pmod);

    for(Person* parent : p_itr){
        std::set <Person*> s_itr = parent->siblings(pmod = PMod::ANY, smod);
        for(Person* sib : s_itr){
            if(sib->gender() == Gender::MALE && sib != nullptr){
                uncles.insert(sib);
            }
        }
    }

    return uncles;
}



