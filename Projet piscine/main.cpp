#include <iostream>
#include "graphe.h"
#include "svgfile.h"

int main()
{
    std::string id_sommet;
    graphe g{"broadway.txt","broadway_weights_0.txt"};
    g.afficher();
  //  g.dessiner();
 //   g.afficherBFS("3");



    return 0;
}
