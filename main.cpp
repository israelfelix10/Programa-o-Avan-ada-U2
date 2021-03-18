#include "sculptor.h"
#include <iostream>
#include <fstream>
#include <string>
#include <math.h>

using namespace std;

int main()
{
    FiguraGeometrica cruz(100,100,100);
    cruz.setColor(0.9999,0,0,0.9);
    cruz.putBox(0,20,00,20,0,2);
    cruz.cutBox(00,8,00,13,0,2);
    cruz.cutBox(12,20,00,13,0,2);
    cruz.cutBox(00,8,17,20,0,2);
    cruz.cutBox(12,20,17,20,0,2);
    cruz.writeOFF("C:/Users/Israel/Desktop/cruz.off");


}
