#include <iostream>
#include "graphe.h"
#include "svgfile.h"

int main()
{
    Svgfile svgout;

    std::string id_sommet;
    graphe g{"broadway.txt","broadway_weights_0.txt"};
    g.afficher();

    g.dessiner(svgout);
 //   g.afficherBFS("3");


    g.bruteForce();


    return 0;
}
