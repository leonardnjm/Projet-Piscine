#include <fstream>
#include <iostream>
#include "graphe.h"
#include "svgfile.h"
#include "arret.h"


graphe::graphe(std::string nomFichier,std::string nomFichierPoids)
{
    std::ifstream ifs{nomFichier};
    std::ifstream ifs1{nomFichierPoids};

    double indSommet1, indSommet2;
    Sommet* sommet1;
    Sommet* sommet2;
    Sommet Sommet1,Sommet2;


    if (!ifs)
        throw std::runtime_error( "Impossible d'ouvrir en lecture " + nomFichier );
    int ordre;
    ifs >> ordre;

    if ( ifs.fail() )
        throw std::runtime_error("Probleme lecture ordre du graphe");
    int id;
    double x,y;
    //lecture des sommets
    for (int i=0; i<ordre; ++i)
    {
        ifs>>id;
        if(ifs.fail())
            throw std::runtime_error("Probleme lecture donn�es sommet");
        ifs>>x;
        if(ifs.fail())
            throw std::runtime_error("Probleme lecture donn�es sommet");
        ifs>>y;
        if(ifs.fail())
            throw std::runtime_error("Probleme lecture donn�es sommet");
        m_sommets.push_back(new Sommet(id,x,y));
    }

    int taille;
    ifs >> taille;

    if ( ifs.fail() )
        throw std::runtime_error("Probleme lecture taille du graphe-Arret");
    int id_voisin;
    //lecture des aretes
    for (int i=0; i<taille; ++i)
    {
        int arret;
        ifs>>arret;

        //lecture des ids des deux extr�mit�s
        ifs>>id;
        if(ifs.fail())
            throw std::runtime_error("Probleme lecture arete sommet 1-Arret");
        ifs>>id_voisin;
        if(ifs.fail())
            throw std::runtime_error("Probleme lecture arete sommet 2-Arret");

        sommet1= m_sommets[indSommet1];
        Sommet1= *sommet1;
        sommet2= m_sommets[indSommet2];
        Sommet2= *sommet2;

    }

    if (!ifs1)
        throw std::runtime_error( "Impossible d'ouvrir en lecture -Arret " + nomFichierPoids );

        int nbArrets;
        ifs1>>nbArrets;

        int nbCond;
        ifs1>>nbCond;

    double poids1,poids2;
  //  int id1;

        std::vector <double> vec_Poids;

        for (int i=0; i<nbArrets; ++i)
    {


        int arret;
        ifs>>arret;

        ifs1>>poids1;

        ifs1>>poids2;

         m_arret.push_back({new Arret{arret,Sommet1,Sommet2,poids1,poids2}});

    }


}
int graphe:: getOrdre() const
{
    return (int)m_sommets.size();
}

void graphe::afficher() const
{
    std::cout<<"graphe : "<<std::endl<<std::endl;
    std::cout<<"  Ordre : "<< getOrdre()<<std::endl<<std::endl<<std::endl;

    for ( auto it : m_sommets)
    {
        std::cout <<"  Sommet : ";

        it->afficherData();

        std::cout<<" " <<std::endl;
    }

    for ( auto ab : m_arret)
    {

    //    ab->afficherDataA();

        std::cout<<" "<< std::endl;

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


/*
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
                    comp_connexe.insert(var);//on insert dans notre set de composante connexe les sommets deja visit�s
                    std::cout<<"    "<<var<<"   ";
                }
            }
        }
    }
    return i;
}

*/

void graphe::dessiner()
{

    Svgfile svgout;


}


graphe::~graphe()
{
    //dtor
}
