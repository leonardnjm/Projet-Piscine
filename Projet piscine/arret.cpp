#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include "arret.h"
#include "graphe.h"


Arret::Arret(int idA,int idSommeta,int idSommetb): m_idA{idA},m_idsommet1{idSommeta},m_idsommet2{idSommetb}
{

}



void Arret::setpoids1(double poids1)
{
    m_poids1=poids1;
}

void Arret::setpoids2(double poids2)
{
    m_poids2=poids2;
}

int Arret::getS1()
{
   return m_idsommet1;
}

int Arret::getS2()
{
    return m_idsommet2;
}

double Arret::getPoids1()
{
    return m_poids1;
}

double Arret::getPoids2()
{
    return m_poids2;
}


void Arret::afficherDataA() const
{

    std::cout<<" Identifiant de l'arete  : "<< m_idA <<"     " << "sommet initial:  " << m_idsommet1 << "     sommet final:  " << m_idsommet2 <<"     " << "Poids 1:   " << m_poids1 << "   Poids 2: " << m_poids2 << std::endl;
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
