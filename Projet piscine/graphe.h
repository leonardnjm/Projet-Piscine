#ifndef GRAPHE_H
#define GRAPHE_H
#include <string>
#include <unordered_map>
#include <unordered_set>
#include "arret.h"
#include "svgfile.h"
#include "algorithm"
#include <set>
#include <list>


class graphe
{
    public:

        graphe(std::string,std::string);
        ~graphe();
        void afficher() const;

        void parcoursKruskal(std::string) const;
        void affichageKruskal(std::string) const;

        std::vector<Arret*> Prim();
        void trieurpoid1();

        void dessiner(Svgfile &svgout);

        void bruteForce();
        void pareto();

       // int rechercher_afficherToutesCC() const;
        int getOrdre() const;
        int isEulerien()const;



    protected:

    private:

        std::vector<Sommet*> m_sommets;
        std::vector<Arret*> m_arret;

};

#endif // GRAPHE_H
