#ifndef SOMMET_H
#define SOMMET_H
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>

class Sommet
{
    public:
        Sommet(std::string,double,double);
        void ajouterVoisin(const Sommet*);
        void afficherData() const;
        void afficherVoisins() const;
        int getDegre() const;


        std::unordered_map<std::string,std::string> parcoursBFS() const;
        std::unordered_map<std::string,std::string> parcoursDFS() const;
        std::unordered_set<std::string> rechercherCC() const;

        ~Sommet();

    protected:

    private:
        std::vector<const Sommet*> m_voisins;
        std::string m_id;
        double m_x, m_y;

};

#endif // SOMMET_H
