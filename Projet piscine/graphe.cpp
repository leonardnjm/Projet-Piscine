#include <fstream>
#include <iostream>
#include "graphe.h"
#include "svgfile.h"

graphe::graphe(std::string nomFichier,std::string nomFichierPoids)
{
    std::ifstream ifs{nomFichier};
    std::ifstream ifs1{nomFichierPoids};
    if (!ifs)
        throw std::runtime_error( "Impossible d'ouvrir en lecture " + nomFichier );
    int ordre;
    ifs >> ordre;

    if ( ifs.fail() )
        throw std::runtime_error("Probleme lecture ordre du graphe");
    std::string id;
    double x,y;
    //lecture des sommets
    for (int i=0; i<ordre; ++i)
    {
        ifs>>id;
        if(ifs.fail())
            throw std::runtime_error("Probleme lecture données sommet");
        ifs>>x;
        if(ifs.fail())
            throw std::runtime_error("Probleme lecture données sommet");
        ifs>>y;
        if(ifs.fail())
            throw std::runtime_error("Probleme lecture données sommet");
        m_sommets.insert({id,new Sommet{id,x,y}});
    }

    int taille;
    ifs >> taille;

    if ( ifs.fail() )
        throw std::runtime_error("Probleme lecture taille du graphe-Arret");
    std::string id_voisin;
    //lecture des aretes
    for (int i=0; i<taille; ++i)
    {
        int arret;
        ifs>>arret;

        //lecture des ids des deux extrémités
        ifs>>id;
        if(ifs.fail())
            throw std::runtime_error("Probleme lecture arete sommet 1-Arret");
        ifs>>id_voisin;
        if(ifs.fail())
            throw std::runtime_error("Probleme lecture arete sommet 2-Arret");

        (m_sommets.find(id))->second->ajouterVoisin((m_sommets.find(id_voisin))->second);
        (m_sommets.find(id_voisin))->second->ajouterVoisin((m_sommets.find(id))->second);
    }

    ///POUR POIDS DES ARRETS

    if (!ifs1)
        throw std::runtime_error( "Impossible d'ouvrir en lecture -Arret " + nomFichierPoids );

        int nbArret;
        ifs1>>nbArret;

        int nbCond;
        ifs1>>nbCond;

    double poids1,poids2;
    int id1;

        for (int i=0; i<nbArret; ++i)
    {
        int arret;
        ifs>>arret;


        //lecture des ids des deux extrémités
     //   ifs>>id1;
     //   if(ifs.fail())
     //       throw std::runtime_error("Probleme lecture arete sommet 1-Arret");


        /*
        ifs>>id_voisin;
        if(ifs.fail())
            throw std::runtime_error("Probleme lecture arete sommet 2-Arret");
        //ajouter chaque extrémité à la liste des voisins de l'autre (graphe non orienté)
        (m_sommets.find(id))->second->ajouterVoisin((m_sommets.find(id_voisin))->second);
        (m_sommets.find(id_voisin))->second->ajouterVoisin((m_sommets.find(id))->second);//remove si graphe orienté
        */

        ifs1>>poids1;


        ifs1>>poids2;

    }


}
int graphe:: getOrdre() const
{
    return (int)m_sommets.size();
}

void graphe::afficher() const
{
    std::cout<<"graphe : "<<std::endl;
    std::cout<<"  Ordre : "<< getOrdre()<<std::endl;

    for ( auto it = m_sommets.begin(); it != m_sommets.end(); ++it)
    {
        std::cout <<"  Sommet : ";
        it->second->afficherData();
        it->second->afficherVoisins();
        std::cout<<"" <<std::endl;
    }
}
/*
void graphe::parcoursKruskal(std::string id) const
{
    Sommet*s0=(m_sommets.find(id))->second;
    std::unordered_map<std::string,std::string> l_pred;
    l_pred=s0->parcoursKruskal();

}
*/

void graphe::parcoursBFS(std::string id) const
{
    Sommet*s0=(m_sommets.find(id))->second;
    std::unordered_map<std::string,std::string> l_pred;
    l_pred=s0->parcoursBFS();
}
void graphe::afficherBFS(std::string id) const
{
    Sommet*s0=(m_sommets.find(id))->second;
    std::unordered_map<std::string,std::string> l_pred;
    std::cout<<"parcoursBFS a partir de "<<id<<" :"<<std::endl;
    l_pred=s0->parcoursBFS();
    for(auto s:l_pred)
    {
        std::cout<<s.first<<" <--- ";
        std::pair<std::string,std::string> pred=s;
        while(pred.second!=id)
        {
            pred=*l_pred.find(pred.second);
            std::cout<<pred.first<<" <--- ";
        }
        std::cout<<id<<std::endl;
    }
}

void graphe::parcoursDFS(std::string id) const
{
    Sommet*s0=(m_sommets.find(id))->second;
    std::unordered_map<std::string,std::string> l_pred;
    l_pred=s0->parcoursDFS();
}
void graphe::afficherDFS(std::string id) const
{
    Sommet*s0=(m_sommets.find(id))->second;
    std::unordered_map<std::string,std::string> l_pred;
    std::cout<<"parcoursDFS a partir de "<<id<<" :"<<std::endl;
    l_pred=s0->parcoursDFS();
    for(auto s:l_pred)
    {
        std::cout<<s.first<<" <--- ";
        std::pair<std::string,std::string> pred=s;
        while(pred.second!=id)
        {
            pred=*l_pred.find(pred.second);
            std::cout<<pred.first<<" <--- ";
        }
        std::cout<<id<<std::endl;
    }
}
int graphe::rechercher_afficherToutesCC() const
{
    int i=0;
    std::cout<<"composantes connexes :"<<std::endl;
    std::unordered_set<std::string> comp_connexe;
    std::unordered_map<std::string,Sommet*> mes_sommets;
    mes_sommets=m_sommets;

    while(comp_connexe.size()!= getOrdre())//on parcours la liste tant que l'on a pas fait tout les sommets
    {
        for(auto it : mes_sommets)//On parcours nos sommets
        {
            if(comp_connexe.count(it.first)==0)//condition pour savoir si on a deja acceder a ce sommet
            {
                Sommet* mon_sommet=(mes_sommets.find(it.first))->second; //decalration du sommet
                auto ma_comp = mon_sommet->rechercherCC();//on recherche les composantes connexes du sommet
                ma_comp.insert(it.first);//et on insert dans notre set
                std::cout<<""<< std::endl;
                ++i;
                std::cout<<"cc"<<i<< std::endl;
                for(auto var:ma_comp)
                {
                    comp_connexe.insert(var);//on insert dans notre set de composante connexe les sommets deja visités
                    std::cout<<"    "<<var<<"   ";
                }
            }
        }
    }
    return i;
}



void graphe::dessiner()
{

    Svgfile svgout;


}


graphe::~graphe()
{
    //dtor
}
