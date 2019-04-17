#include <iostream>
#include <queue>
#include <stack>
#include<unordered_map>
#include<unordered_set>
#include "sommet.h"

Sommet::Sommet(int id,double x,double y):m_id{id},m_x{x},m_y{y}
{
}
Sommet::Sommet()
{

}
void Sommet::ajouterVoisin(const Sommet* voisin)
{
    m_voisins.push_back(voisin);
}
void Sommet::afficherData() const
{
    std::cout<<"    "<<m_id<<" : "<<"(x,y)=("<<m_x<<","<<m_y<<")"<<std::endl;
}
void Sommet::afficherVoisins() const
{
    std::cout<<"  voisins :"<<std::endl;

    for(auto v:m_voisins)
    {
        v->afficherData();
    }
}

int Sommet:: getDegre() const
    {
        return (int)m_voisins.size();
    }

/*
std::unordered_set<std::string> Sommet::rechercherCC() const
{
    std::unordered_set<std::string> cc;//set que l'on return
    auto l_pred=parcoursBFS();//initialisation avec le parcours bfs de notre unordered map
    for(auto it : l_pred)
    {
        cc.insert(it.first);// on insert dans notre set
    }
    return cc;
}
*/

Sommet::~Sommet()
{
    //dtor
}
