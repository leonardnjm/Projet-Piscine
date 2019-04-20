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
      // Arret(int,Sommet,Sommet,double,double);
      Arret(int,int,int);
        void setpoids1(double poids1);
        void setpoids2(double poids2);

        int getS1();
        int getS2();

        double getPoids1();
        double getPoids2();


        void afficherDataA() const;

        ~Arret();


    protected:

    private:

        int m_idA;
       // std::vector <double> m_poids;
        double m_poids1, m_poids2;
        int m_idsommet1,m_idsommet2;

};


#endif // ARRET_H_INCLUDED
