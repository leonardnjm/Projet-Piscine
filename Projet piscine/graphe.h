#ifndef GRAPHE_H
#define GRAPHE_H
#include <string>
#include <unordered_map>
#include <unordered_set>
#include "sommet.h"
#include "arret.h"

class graphe
{
    public:

        graphe(std::string,std::string);
        ~graphe();
        void afficher() const;
        void parcoursBFS(std::string) const;
        void afficherBFS(std::string) const;
        void parcoursDFS(std::string) const;
        void afficherDFS(std::string) const;

        void parcoursKruskal(std::string) const;
        void affichageKruskal(std::string) const;

        void dessiner();

        int rechercher_afficherToutesCC() const;
        int getOrdre() const;
        int isEulerien()const;



    protected:

    private:

        std::vector<Sommet*> m_sommets;
        std::vector<Arret*> m_arret;

};

#endif // GRAPHE_H
