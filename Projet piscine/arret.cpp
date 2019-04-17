#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include "arret.h"


/*
Arret::Arret(std::string idA, std::pair < double,double > poids): m_idA{idA},m_poids1{poids1},m_poids2{poids2}
{

}
*/
Arret::Arret(int idA, Sommet a, Sommet b, double poids1, double poids2): m_idA{idA},m_poids1{poids1},m_poids2{poids2}
{

}


void Arret::afficherDataA() const
{
    std::cout<<"  "<<m_idA<<" : "<<"Poids 1: "<<m_poids1<<" Poids 2:"<<m_poids2<<std::endl;
}

/*
void Arret::ajouterArret(const Arret* arrets)
{

    m_arrets.push_back(arrets);

}


void Arret::afficherArrets() const
{
    std::cout << "arret de poids :" <<std::endl;
        for(auto v:m_arrets)
        {
            v-> afficherDataA();
        }

}
*/
