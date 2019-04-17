#ifndef ARRET_H_INCLUDED
#define ARRET_H_INCLUDED
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include "sommet.h"


class Arret
{
    public:
       // Arret(std::string,std::pair < double,double > poids);
       Arret(int,Sommet,Sommet,double,double);

        void afficherDataA() const;
    //    void ajouterArret(const Arret* arrets);
    //   void afficherArrets() const;

        ~Arret();


    protected:

    private:
    //    std::vector<const Arret*> m_arrets;
        int m_idA;
        double m_poids1, m_poids2;

};


#endif // ARRET_H_INCLUDED
