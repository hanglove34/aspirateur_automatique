#ifndef ASPIRATEUR
#define ASPIRATEUR

#include <iostream>
#include <vector>

enum NC{
    N = 0,
    E = 1,
    S = 2,
    W = 3
};

class aspirateur
{
private:
    int _xMap;
    int _yMap;
    int _positionX;
    int _positionY;
    NC _orientation;
    int _stop;
public:
    aspirateur();
    ~aspirateur();
    void Droite();
    void Gauche();
    void Avance();
    void setX(int x);
    void setY(int y);
    void getResult();
    std::string getOrientation();
    void boucle();
    int getFirstLine();
    bool checkDigit(std::string data);
    bool checkIfOrientation(std::string data);
    int getOrientationLetterToDigit(std::string data);
    std::vector<int> parsInput(std::string data);
    void printHelper();
    int getSecondArgument();
    NC getOrientationDigitToEnum(int data);
    int getChemin();
    bool checkChemin(std::string data);
    int getOrientationEnumToDigit(NC data);
    int aspirateurAction(std::string data);
};

#endif