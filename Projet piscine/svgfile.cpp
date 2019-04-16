#include "svgfile.h"
#include <iostream>
#include <sstream>

const std::string svgHeader =
    "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n"
    "<svg xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\" ";

const std::string svgEnding = "\n\n</svg>\n";

/// Effets "Boule en relief", voir données à la fin de ce fichier
extern const std::string svgBallGradients;

std::set<std::string> Svgfile::s_openfiles;

bool Svgfile::s_verbose = true;

Svgfile::Svgfile(std::string _filename, int _width, int _height) :
    m_filename{_filename}, m_width{_width}, m_height{_height}
{

    if (s_verbose)
        std::cout << "Opening SVG output file : "
                  << m_filename << std::endl;

    if ( s_openfiles.count(m_filename) )
        throw std::runtime_error( "File " + m_filename + " already open !" );

    m_ostrm.open(m_filename);
    s_openfiles.insert(m_filename);

    if (!m_ostrm)
    {
        std::cout << "Problem opening " << m_filename << std::endl;
        throw std::runtime_error("Could not open file " + m_filename );
    }

    /*if (s_verbose)
        std::cout << "OK" << std::endl;*/

    // Writing the header into the SVG file
    m_ostrm << svgHeader;
    m_ostrm << "width=\"" << m_width << "\" height=\"" << m_height << "\">\n\n";
}

Svgfile::~Svgfile()
{
    // Writing the ending into the SVG file
    m_ostrm << svgEnding;

    // Removing this file from the list of open files
    s_openfiles.erase(m_filename);

    // No need to explicitly close the ofstream object (automatic upon destruction)
}

// Helper templated function
template<typename T>
std::string attrib(std::string name, T val)
{
    std::ostringstream oss;
    oss << name << "=\"" << val << "\" ";
    return oss.str();
}

/*
void Svgfile::addGradient(std::string color1, std::string color2 )
{
    m_ostrm << "<defs>\n"
            "<linearGradient id=\"grad\" x1=\"0%\" y1=\"0%\" x2=\"0%\" y2=\"100%\">\n"
            "<stop offset= \"0%\" style=\"stop-color:" + color1 + ";stop-opacity:1\" />\n"
            "<stop offset= \"25%\" style=\"stop-color:" + color2 + ";stop-opacity:1\" />\n"
            "</linearGradient>\n"
            "</defs>;\n";

}

void Svgfile::addGradient2(std::string color1, std::string color2, std::string color3)
{
    m_ostrm << "<defs>\n"
            "<linearGradient id=\"grad1\" x1=\"0%\" y1=\"0%\" x2=\"0%\" y2=\"100%\">\n"
            "<stop offset= \"0%\" style=\"stop-color:" + color1 + ";stop-opacity:1\" />\n"
            "<stop offset= \"20%\" style=\"stop-color:" + color2 + ";stop-opacity:1\" />\n"
            "<stop offset= \"70%\" style=\"stop-color:" + color3 + ";stop-opacity:1\" />\n"
            "</linearGradient>\n"
            "</defs>;\n";

}

void Svgfile::addGradient3(std::string color1, std::string color2)
{
    m_ostrm << "<defs>\n"
            "<linearGradient id=\"grad2\" x1=\"0%\" y1=\"0%\" x2=\"100%\" y2=\"100%\">\n"
            "<stop offset= \"0%\" style=\"stop-color:" + color1 + ";stop-opacity:1\" />\n"
            "<stop offset= \"40%\" style=\"stop-color:" + color2 + ";stop-opacity:1\" />\n"
            "</linearGradient>\n"
            "</defs>;\n";

}

void Svgfile::addGradient4(std::string color1, std::string color2, std::string color3)
{
    m_ostrm << "<defs>\n"
            "<linearGradient id=\"grad4\" x1=\"0%\" y1=\"0%\" x2=\"0%\" y2=\"100%\">\n"
            "<stop offset= \"0%\" style=\"stop-color:" + color1 + ";stop-opacity:1\" />\n"
            "<stop offset= \"5%\" style=\"stop-color:" + color2 + ";stop-opacity:1\" />\n"
            "<stop offset= \"25%\" style=\"stop-color:" + color3 + ";stop-opacity:1\" />\n"
            "</linearGradient>\n"
            "</defs>;\n";

}

void Svgfile::addGradientRad(std::string color1, std::string color2)
{
  m_ostrm <<   "<defs>\n"
            "<radialGradient id=\"gradR\" cx=\"50%\" cy=\"50%\" r=\"50%\" fx=\"50%\" fy=\"50%\">\n"
            "<stop offset=\"0%\" style=\"stop-color:"+color1+";stop-opacity:0.6\" />\n"
            "<stop offset=\"100%\" style=\"stop-color:"+color2+";stop-opacity:0.2\" />\n"
            "</radialGradient>\n"
            "</defs>;\n";

}

void Svgfile::addGradientRad2(std::string color1, std::string color2)
{
  m_ostrm <<   "<defs>\n"
            "<radialGradient id=\"gradR2\" cx=\"50%\" cy=\"50%\" r=\"50%\" fx=\"50%\" fy=\"50%\">\n"
            "<stop offset=\"0%\" style=\"stop-color:"+color1+";stop-opacity:1\" />\n"
            "<stop offset=\"100%\" style=\"stop-color:"+color2+";stop-opacity:0\" />\n"
            "</radialGradient>\n"
            "</defs>;\n";
}

void Svgfile::addGradientRad3(std::string color1, std::string color2)
{
  m_ostrm <<   "<defs>\n"
            "<radialGradient id=\"gradR3\" cx=\"50%\" cy=\"50%\" r=\"50%\" fx=\"50%\" fy=\"50%\">\n"
            "<stop offset=\"40%\" style=\"stop-color:"+color1+";stop-opacity:1\" />\n"
            "<stop offset=\"100%\" style=\"stop-color:"+color2+";stop-opacity:1\" />\n"
            "</radialGradient>\n"
            "</defs>;\n";
}

void Svgfile::addGradientRad4(std::string color1, std::string color2)
{
  m_ostrm <<   "<defs>\n"
            "<radialGradient id=\"gradR4\" cx=\"50%\" cy=\"50%\" r=\"50%\" fx=\"50%\" fy=\"50%\">\n"
            "<stop offset=\"0\" style=\"stop-color:"+color1+";stop-opacity:1\" />\n"
            "<stop offset=\"1\" style=\"stop-color:"+color2+";stop-opacity:0\" />\n"
            "</radialGradient>\n"
            "</defs>;\n";
}

void Svgfile::addGradientAEC(std::string color1, std::string color2, std::string color3, std::string color4, std::string color5, std::string color6, std::string color7)
{
  m_ostrm <<   "<defs>\n"
            "<radialGradient id=\"gradAEC\" cx=\"50%\" cy=\"50%\" r=\"50%\" fx=\"50%\" fy=\"50%\">\n"
            "<stop offset=\"0.70\" style=\"stop-color:"+color1+";stop-opacity:0\" />\n"
            "<stop offset=\"0.75\" style=\"stop-color:"+color2+";stop-opacity:0.4\" />\n"
            "<stop offset=\"0.80\" style=\"stop-color:"+color3+";stop-opacity:0.3\" />\n"
            "<stop offset=\"0.85\" style=\"stop-color:"+color4+";stop-opacity:0.3\" />\n"
            "<stop offset=\"0.90\" style=\"stop-color:"+color5+";stop-opacity:0.3\" />\n"
            "<stop offset=\"0.95\" style=\"stop-color:"+color6+";stop-opacity:0.3\" />\n"
            "<stop offset=\"0.99\" style=\"stop-color:"+color7+";stop-opacity:0.4\" />\n"
            "</radialGradient>\n"
            "</defs>;\n";
}

void Svgfile::addGradientSol(std::string color1, std::string color2)
{
    m_ostrm << "<defs>\n"
            "<linearGradient id=\"gradSol\" x1=\"0%\" y1=\"100%\" x2=\"0%\" y2=\"0%\">\n"
            "<stop offset= \"90%\" style=\"stop-color:" + color1 + ";stop-opacity:1\" />\n"
            "<stop offset= \"100%\" style=\"stop-color:" + color2 + ";stop-opacity:1\" />\n"
            "</linearGradient>\n"
            "</defs>;\n";

}

*/

void Svgfile::addDisk(double x, double y, double r, std::string color)
{
    m_ostrm << "<circle "
            << attrib("cx", x)
            << attrib("cy", y)
            << attrib("r",  r)
            << attrib("fill", color )
            << "/>\n";
}

void Svgfile::addCircle(double x, double y, double r, double ep, std::string color)
{
    m_ostrm << "<circle "
            << attrib("cx", x)
            << attrib("cy", y)
            << attrib("r",  r)
            << attrib("fill", "none")
            << attrib("stroke", color )
            << attrib("stroke-width", ep )
            << "/>\n";
}

/// <polygon points="200,10 250,190 160,210" style="fill:lime;stroke:purple;stroke-width:1" />
void Svgfile::addTriangle(double x1, double y1, double x2, double y2,
                          double x3, double y3, std::string colorFill,
                          double thickness, std::string colorStroke)
{

    m_ostrm << "<polygon points=\" "
            << x1 << "," << y1 << " "
            << x2 << "," << y2 << " "
            << x3 << "," << y3
            << "\" style=\"fill:" << colorFill
            << ";stroke:" << colorStroke
            << ";stroke-width:" << thickness
            << "\" />\n";
}

void Svgfile::addRectangle(double x, double y, double lenght, double hight, std::string colorFill)
{
           m_ostrm << "<polygon points=\" "
            << x << "," << y << " "
            << x << "," << y-hight << " "
            << x+lenght << "," << y-hight << " "
            << x+lenght << "," << y
            << "\" style=\"fill:" << colorFill
            << "\" />\n";
}

void Svgfile::addSquare(double x1, double y1, double lenght, std::string colorFill)
{
           m_ostrm << "<polygon points=\" "
            << x1 << "," << y1 << " "
            << x1 << "," << y1-lenght << " "
            << x1+lenght << "," << y1-lenght << " "
            << x1+lenght << "," << y1
            << "\" style=\"fill:" << colorFill
            << "\" />\n";
}

void Svgfile::addRibbon(double x, double y, double lenght, std::string colorFill)
{
    m_ostrm << "<polygon points=\" "
            << x << "," << y << " "
            << x-(lenght/2) << "," << y-(lenght/2) << " "
            << x-(lenght/2) << "," << y+(lenght/2) << " "
            << x+(lenght/2) << "," << y-(lenght/2) << " "
            << x+(lenght/2) << "," << y+(lenght/2)
            << "\" style=\"fill:" << colorFill
            << "\" />\n";
}

void Svgfile::addEllipse(double cx, double cy, double rx, double ry, std::string color)
{
    m_ostrm << "<ellipse "
            << attrib("cx", cx)
            << attrib("cy", cy)
            << attrib("rx",  rx)
            << attrib("ry",  ry)
            << attrib("fill", color )
            << "/>\n";
}


void Svgfile::addTriangle(double x1, double y1, double x2, double y2,
                          double x3, double y3, std::string colorFill)
{
    m_ostrm << "<polygon points=\" "
            << x1 << "," << y1 << " "
            << x2 << "," << y2 << " "
            << x3 << "," << y3
            << "\" style=\"fill:" << colorFill
            << "\" />\n";
}



void Svgfile::addLine(double x1, double y1, double x2, double y2, std::string color)
{
    m_ostrm << "<line "
            << attrib("x1", x1)
            << attrib("y1", y1)
            << attrib("x2", x2)
            << attrib("y2", y2)
            << attrib("stroke", color)
            << "/>\n";
}

void Svgfile::addCross(double x, double y, double span, std::string color)
{
    addLine(x-span, y-span, x+span, y+span, color);
    addLine(x-span, y+span, x+span, y-span, color);
}

void Svgfile::addText(double x, double y, std::string text, std::string color)
{
    /// <text x="180" y="60">Un texte</text>
    m_ostrm << "<text "
            << attrib("x", x)
            << attrib("y", y)
            << attrib("fill", color)
            << ">" << text << "</text>\n";
}

void Svgfile::addText(double x, double y, double val, std::string color)
{
    std::ostringstream oss;
    oss << val;
    addText(x, y, oss.str(), color);
}

void Svgfile::addGrid(double span, bool numbering, std::string color)
{
    double y=0;
    while (y<=m_height)
    {
        addLine(0, y, m_width, y, color);
        if (numbering)
            addText(5, y-5, y, color);
        y+=span;
    }

    double x=0;
    while (x<=m_width)
    {
        addLine(x, 0, x, m_height, color);
        if (numbering)
            addText(x+5, 15, x, color);
        x+=span;
    }
}

/*
void Svgfile::addGradientEch(std::string color1, std::string color2 )   //gradient echarpe
{
    m_ostrm << "<defs>\n"
            "<linearGradient id=\"gradEch\" x1=\"0%\" y1=\"0%\" x2=\"0%\" y2=\"100%\">\n"
            "<stop offset= \"0%\" style=\"stop-color:" + color1 + ";stop-opacity:1\" />\n"
            "<stop offset= \"80%\" style=\"stop-color:" + color2 + ";stop-opacity:1\" />\n"
            "</linearGradient>\n"
            "</defs>;\n";

}

void Svgfile::addGradientRadBDN(std::string color1, std::string color2) //bonhomme de neige
{
  m_ostrm <<   "<defs>\n"
            "<radialGradient id=\"gradRBon\" cx=\"50%\" cy=\"50%\" r=\"50%\" fx=\"50%\" fy=\"0%\">\n"
            "<stop offset=\"0.7\" style=\"stop-color:"+color1+";stop-opacity:1\" />\n"
            "<stop offset=\"1\" style=\"stop-color:"+color2+";stop-opacity:1\" />\n"
            "</radialGradient>\n"
            "</defs>;\n";
}

void Svgfile::addGradientRadBDN2(std::string color1, std::string color2) //bonhomme de neige
{
  m_ostrm <<   "<defs>\n"
            "<radialGradient id=\"gradRBon2\" cx=\"50%\" cy=\"50%\" r=\"50%\" fx=\"50%\" fy=\"0%\">\n"
            "<stop offset=\"0.9\" style=\"stop-color:"+color1+";stop-opacity:1\" />\n"
            "<stop offset=\"1\" style=\"stop-color:"+color2+";stop-opacity:1\" />\n"
            "</radialGradient>\n"
            "</defs>;\n";
}

*/


std::string Svgfile::makeRGB(int r, int g, int b)
{
    std::ostringstream oss;
    oss << "rgb(" << r << "," << g << "," << b << ")";
    return oss.str();
}
