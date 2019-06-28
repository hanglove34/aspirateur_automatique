#include "Aspirateur.hpp"

aspirateur::aspirateur()
{
    _yMap = 0;
    _xMap = 0;
    _positionX = 0;
    _positionY = 0;
    _orientation = NC::N;
    _stop = 0;
}

aspirateur::~aspirateur()
{
}


void aspirateur::Droite()
{
    int orien = getOrientationEnumToDigit(_orientation);
    orien += 1;
    if (orien > 3)
        _orientation = NC::N;
    else
        _orientation = getOrientationDigitToEnum(orien);
}

void aspirateur::Gauche()
{
    int orien = getOrientationEnumToDigit(_orientation);
    orien -= 1;
    if (orien < 0)
        _orientation = NC::W;
    else
        _orientation = getOrientationDigitToEnum(orien);
}

void aspirateur::Avance()
{
    if (_orientation == NC::N)
        _positionY += 1;
    if (_orientation == NC::E)
        _positionX += 1;
    if (_orientation == NC::S)
        _positionY -= 1;
    if (_orientation == NC::W)
        _positionX -= 1;
}

void aspirateur::setX(int x)
{
    _xMap = x;
}

void aspirateur::setY(int y)
{
    _yMap = y;
}

std::string aspirateur::getOrientation()
{
    if (_orientation == 0)
        return ("N");
    if (_orientation == 1)
        return ("E");
    if (_orientation == 2)
        return ("S");
    return ("W");
}

void aspirateur::getResult()
{
    std::cout << _positionX << " " << _positionY << " " << getOrientation() << std::endl;
}

bool aspirateur::checkDigit(std::string data)
{
    for (size_t nb = 0; nb != data.size(); nb++)
    {
        if (std::isdigit(data[nb]) == false)
            return (false);
    }
    return (true); 
}

bool aspirateur::checkIfOrientation(std::string data)
{
    if (data == "N" || data == "W" || data == "E" || data == "S")
        return (true);
    return (false);
}

int aspirateur::getOrientationLetterToDigit(std::string data)
{
    if (data == "N")
        return (0);
    if (data == "E")
        return (1);
    if (data == "S")
        return (2);
    return (3);
}

int aspirateur::getOrientationEnumToDigit(NC data)
{
    if (data == NC::N)
        return (0);
    if (data == NC::E)
        return (1);
    if (data == NC::S)
        return (2);
    return (3);
}

NC aspirateur::getOrientationDigitToEnum(int data)
{
    if (data == 0)
        return (NC::N);
    if (data == 1)
        return (NC::E);
    if (data == 2)
        return (NC::S);
    return (NC::W);
}

std::vector<int> aspirateur::parsInput(std::string data)
{
    std::vector<int> result;
    std::string delimiter = " ";
    while (data.size() != 0)
    {
        if (data.find(delimiter) != std::string::npos)
        {
            std::string save = data;
            std::string token = save.substr(0, save.find(delimiter));
            data.erase(0, data.find(delimiter) + 1);
            if (checkDigit(token) == true)
                result.push_back(std::atoi(token.c_str()));
            else {
                return (std::vector<int>());
            }
        } else {
            if (checkDigit(data) == true)
                result.push_back(std::atoi(data.c_str()));
            else if (checkIfOrientation(data) == true) {
                result.push_back(getOrientationLetterToDigit(data));
            } else
                return (std::vector<int>());
            break;
        }
    }
    return (result);
}

void aspirateur::printHelper()
{
    std::cout << std::endl << "\t\t\tAIDE" << std::endl;
    std::cout << "Les coordonées de la map sont des int et il s'écrivent comme cela : '10 10'" << std::endl; 
    std::cout << "Les coordonées de l'apirateur sont des int, l'orientation est une lettre majuscule et il s'écrivent comme cela : '10 10 N/E/S/W'" << std::endl; 
    std::cout << "Les ordres de directions sont G/D/A (gauche, droite : sur place / avance : avance d'une case) et elles s'écrivent : 'DDAGADA'" << std::endl;
    std::cout << "Si vous souhaitez arréter le programme taper : 'stop'" << std::endl; 
    std::cout << std::endl;
}

int aspirateur::getFirstLine()
{
    std::cout << "Enter la taille de la carte svp (2 paramètres): "; 
    std::string val1;
    std::string val2;
    std::vector<int> vec;
    std::cin >> val1;
    if (val1 == "help") {
        printHelper();
        return (getFirstLine());
    }
    if (val1 == "stop")
        return (1);
    std::cin >> val2;
    vec = parsInput(val1 + " " + val2);
    if (vec.size() != 2) {
        std::cout << "Mauvaise information, regarder l'aide si vous le souhaité en tapant 'help'" << std::endl;
        return (getFirstLine());
    }
    _xMap = vec[0];
    _yMap = vec[1];
    return (0);
}

int aspirateur::getSecondArgument()
{
    std::cout << "Entrer les positions de l'aspirateur svp (3 paramètres): "; 
    std::string val1;
    std::string val2;
    std::string val3;
    std::vector<int> vec;
    std::cin >> val1;
    if (val1 == "help") {
        printHelper();
        return (getSecondArgument());
    }
    if (val1 == "stop")
        return (1);
    std::cin >> val2;
    std::cin >> val3;
    vec = parsInput(val1 + " " + val2 + " " + val3);
    if (vec.size() != 3 || vec[0] > _xMap || vec[1] >_yMap) {
        std::cout << "Mauvaise information, regarder l'aide si vous le souhaité en tapant 'help'" << std::endl;
        return (getSecondArgument());
    }
    _positionX = vec[0];
    _positionY = vec[1];
    _orientation = getOrientationDigitToEnum(vec[2]);
    return (0);
}

bool aspirateur::checkChemin(std::string data)
{
    for (size_t nb = 0; nb != data.size(); nb++)
        if (data[nb] != 'D' && data[nb] != 'G' && data[nb] != 'A')
            return (false);
    return (true);
}

int aspirateur::aspirateurAction(std::string data)
{
    int x = _positionX;
    int y = _positionY;
    for (size_t nb = 0; nb != data.size(); nb++)
    {
        if (data[nb] == 'D') {
            Droite();
        } else if (data[nb] == 'G') {
            Gauche();
        } else {
            Avance();
        }
    }
    if (_positionX < 0 || _positionY < 0 || _positionX > _xMap || _positionY > _yMap) {
        _positionX = x;
        _positionY = y;
        return (84);
    }
    return (0);
}

int aspirateur::getChemin()
{
    std::cout << "Entrer le parcours (1 paramètre): "; 
    std::string val1;
    std::cin >> val1;
    if (val1 == "help") {
        printHelper();
        return (getChemin());
    } if (val1 == "stop")
        return (1);
    if (checkChemin(val1) == false || aspirateurAction(val1) != 0) {
        std::cout << "Mauvaise information, regarder l'aide si vous le souhaité en tapant 'help'" << std::endl;
        return (getChemin());
    }
    return (0);
}

void aspirateur::boucle()
{
    if (getFirstLine() == 1)
        return;
    while (1)
    {
        if (getSecondArgument() == 1)
            break;
        if (getChemin() == 1)
            break;
        getResult();
    }
}