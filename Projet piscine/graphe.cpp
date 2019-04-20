#include <fstream>
#include <iostream>
//#include <cmath.h>
#include <math.h>
#include "graphe.h"
#include "svgfile.h"
#include "arret.h"
#include <bitset>
#include "algorithm"

graphe::graphe(std::string nomFichier,std::string nomFichierPoids)
{
    std::ifstream ifs{nomFichier};
    std::ifstream ifs1{nomFichierPoids};

//   double indSommet1, indSommet2;

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
            throw std::runtime_error("Probleme lecture données sommet");

        ifs>>x;
        if(ifs.fail())
            throw std::runtime_error("Probleme lecture données sommet");

        ifs>>y;
        if(ifs.fail())
            throw std::runtime_error("Probleme lecture données sommet");

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

        //lecture des ids des deux extrémités
        ifs>>id;
        if(ifs.fail())
            throw std::runtime_error("Probleme lecture arete sommet 1-Arret");

        ifs>>id_voisin;
        if(ifs.fail())
            throw std::runtime_error("Probleme lecture arete sommet 2-Arret");

        m_arret.push_back({new Arret{arret,id,id_voisin}});

    }

    if (!ifs1)
        throw std::runtime_error( "Impossible d'ouvrir en lecture -Arret " + nomFichierPoids );

    int nbArrets;
    ifs1>>nbArrets;

    int nbCond;
    ifs1>>nbCond;

    double poids1,poids2;


    //  std::vector <double> vec_Poids;

    for (int i=0; i<nbArrets; ++i)
    {

        int arret;
        ifs1>>arret;

        ifs1>>poids1;

        ifs1>>poids2;

        m_arret[arret]->setpoids1(poids1);

        m_arret[arret]->setpoids2(poids2);

    }

    Prim();

}

int graphe:: getOrdre() const
{
    return (int)m_sommets.size();
}

/*
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

    for(int i=0;i<(int)m_arret.size();i++)
    {
        m_arret[i]->afficherDataA();
    }
}
*/


void graphe::afficher() const
{
    std::cout<<"                                            Graphe entier "<<std::endl<<std::endl;
    std::cout<<" Ordre : "<< getOrdre()<<std::endl<<std::endl;

    for ( auto it : m_sommets)
    {
        std::cout <<"  Sommet: ";

        it->afficherData();

        std::cout<<" " <<std::endl;
    }

    std::cout<<" Sommets du fichier avec poids: "<<std::endl<<std::endl;

    for(int i=0; i<m_arret.size(); i++)
    {
        m_arret[i]->afficherDataA();
    }
    std::cout<<std::endl;
}



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
                    comp_connexe.insert(var);//on insert dans notre set de composante connexe les sommets deja visités
                    std::cout<<"    "<<var<<"   ";
                }
            }
        }
    }
    return i;
}

*/


bool compare_poid1(Arret* first, Arret* second)
{
    return (first->getPoids1() < second->getPoids1());
}
bool compare_poid2(Arret* first, Arret* second)
{
    return (first->getPoids2() < second->getPoids2());
}


std::vector<Arret*> graphe::Prim()
{
    std::vector<Arret*> vecteur_prim;
    std::vector<Arret*> Transit;
    std::set<Sommet*> sommet_visite;
    Sommet* som_select;
    std::list<Arret*> list_prio;

    std::cout<<std::endl<<std::endl;

    std::cout<<"                                    Sommets de l'arbre couvrant"<<std::endl<<std::endl;
    std::cout<<"nombre de sommets decouvert:"<<std::endl<<std::endl;

    while(sommet_visite.size()!= m_sommets.size())
    {

        if (sommet_visite.empty() == true)
        {
            som_select = m_sommets[0];
        }

        for(int i=0; i<m_arret.size(); i++)
        {
            if(m_arret[i]->getS1()== som_select->getId() || m_arret[i]->getS2()== som_select->getId())
            {
                list_prio.push_back(m_arret[i]);
            }
        }
        list_prio.sort(compare_poid1);
        std::cout << "Nombre de sommet visite : " << sommet_visite.size() << std::endl;
        while(sommet_visite.count(m_sommets[list_prio.front()->getS1()])==true && sommet_visite.count(m_sommets[list_prio.front()->getS2()])==true )     // m_sommet[0]
        {
            list_prio.pop_front();
        }

        // if (vecteur_prim.front() != list_prio.front())
        vecteur_prim.push_back(list_prio.front());

        if(sommet_visite.count(m_sommets[list_prio.front()->getS1()])== true)
        {
            som_select = m_sommets[list_prio.front()->getS2()];
        }
        else
        {
            som_select = m_sommets[list_prio.front()->getS1()];
        }

        if(sommet_visite.count(som_select)==false)
        {
            sommet_visite.insert(som_select);
        }
    }
    vecteur_prim.erase(vecteur_prim.begin());

    std::cout<<std::endl;
    std::cout<<"Pour poids 1:"<<std::endl;
    for(auto i : vecteur_prim)
    {
        std::cout << "Sommet 1 : " << i->getS1() << " Sommet 2 : " << i->getS2() << std::endl;
    }
    std::cout<<std::endl;

    return vecteur_prim;
}


void graphe::bruteForce()
{

    int tailleA = m_arret.size();   //nb d'arrets
    int ordre= m_sommets.size();    //nb sommets

    int ab= ordre-1;

    int j;

    int arretPos;       //arret possible
    arretPos= pow(2,getOrdre())-1;


    std::vector<std::vector<bool>>combP;    //combinaisons possibles
    std::vector<bool> temp (tailleA,true);


    std::vector<int> triageCon; // vecteur des sommets trier

    std::cout<<"                     =Filtrage cyclique="<<std::endl<<std::endl;

    for (int i=0; i< tailleA-ab ; ++i)
    {
        temp[i]=false;
    }
    do
    {
        combP.push_back(temp);

    }
    while(std::next_permutation(temp.begin(),temp.end()));

    for(int i=0; i< combP.size(); ++i)
    {
        for (j=0; j< temp.size(); ++j)
        {
            std::cout<<combP[i][j];

        }
        std::cout<<std::endl;
    }

    std::cout<<std::endl<<"                      =Filtrage connexe="<<std::endl<<std::endl;

    std::vector<int> tabConnexe(m_sommets.size(),0);
    int valS1,valS2;
    int valPrec;
    std::vector<std::vector<bool>> abc;
    int k=0;

    // //verification de connexite


    for(int i=0; i < combP.size(); ++i)
    {
        for(int x=0; x<m_sommets.size(); ++x)
        {
            tabConnexe[x]=x;
        }

        for (int j=0; j<m_arret.size(); ++j)
        {
            k=0;

            if(combP[i][j]==1)
            {

                valS1 = m_arret[j]->getS1();
                valS2 = m_arret[j]->getS2();


                valPrec = tabConnexe[valS2];
                tabConnexe[valS2] = tabConnexe[valS2];

                for(int y = 0; y < m_sommets.size(); ++y)
                {
                    if (tabConnexe[y]== valPrec)
                    {

                        tabConnexe[y]=tabConnexe[valS1];


                    }

                }

            }

        }


        for(int i= 0; i < m_sommets.size()-1; ++i)
        {

            if(tabConnexe[i]==tabConnexe[i+1])
            {
                k++;
            }


        }
        if(k == m_sommets.size()-1)
        {
            abc.push_back(combP[i]);
        }
    }



    for(int i=0; i< abc.size(); ++i)
    {
        for (j=0; j< temp.size(); ++j)
        {
            std::cout<<abc[i][j];

        }
        std::cout<<std::endl;
    }

    //  std::cout<<abc.size();  //nombre de solutions possible

}


/*

    for(int i=0; i< combP.size(); ++i)      //stockage de tout les sommets
{

    for (j=0; j< temp.size(); ++j)
    {

        if(combP[i][j]==1)
        {


                for ( int i= 0; i< j; ++i)
                {

                      //  m_arret[i]->getS1();
                      //  m_arret[i]->getS2();

                        compteur1=0;                                            //verification si le sommet est deja dans le vector
                        compteur2=0;
                       for(int y=0; y<triageCon.size(); y++)
                        {
                            if(triageCon[y]!=m_arret[i]->getS1());
                               {
                                   compteur1++;
                               }
                            if(triageCon[y]!=m_arret[i]->getS2());
                               {
                                   compteur2++;
                               }
                            if(compteur1==triageCon.size())
                            {
                                triageCon.push_back(m_arret[i]->getS1());
                            }
                            if(compteur2==triageCon.size())
                            {
                                triageCon.push_back(m_arret[i]->getS2());
                            }
                        }

                }
        }

    }



   // std::cout<<std::endl;
}
*/


/*
        for ( int i= 0; i< j; ++i)
        {

            if(triageCon.size() != m_sommets.size())
                triageCon.erase(triageCon.begin()+i);

        //      std::cout<<triageCon[i];
        }

for (auto it =triageCon.begin(); it! = triageCon.end();)
{
    if(it != m_sommets.size())
       {
           it= triageCon.erase(it);
       }
    else
        {
            ++it;
        }

}

       // std::cout<<std::endl;

*/


void graphe::pareto()
{

}



void graphe::dessiner(Svgfile &svgout)
{
    for(int i=0; i< (int)m_arret.size(); i++) //affichage sommet
    {
        svgout.addLine(m_sommets[m_arret[i]->getS1()]->getX(),m_sommets[m_arret[i]->getS1()]->getY(),m_sommets[m_arret[i]->getS2()]->getX(),m_sommets[m_arret[i]->getS2()]->getY(),Svgfile::makeRGB(52, 104, 237));
        svgout.addText((m_sommets[m_arret[i]->getS1()]->getX()+ m_sommets[m_arret[i]->getS2()]->getX())/2,(m_sommets[m_arret[i]->getS1()]->getY()+ m_sommets[m_arret[i]->getS2()]->getY())/2,m_arret[i]->getPoids1(),Svgfile::makeRGB(160, 33, 11));
    }


    for(int i=0; i<(int)m_sommets.size(); i++) //affichage arets
    {
        svgout.addDisk(m_sommets[i]->getX(),m_sommets[i]->getY(),10,Svgfile::makeRGB(70, 15, 142));
        svgout.addText(m_sommets[i]->getX()-5,m_sommets[i]->getY()+5,m_sommets[i]->getId(),Svgfile::makeRGB(237, 63, 33));
    }
}


graphe::~graphe()
{
    //dtor
}
