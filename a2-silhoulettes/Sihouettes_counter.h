#ifndef SIHOUETTES_COUNTER_H
#define SIHOUETTES_COUNTER_H

#include <QImage>
#include <iostream>
#include <QColor>
#include <string>
#include <fstream>
#include <QPoint>
#include <map>
#include <queue>
using namespace std;

class Sihouettes_counter
{
public:
    Sihouettes_counter();
    int count(string filePath);
    void fillSihoulette(QPoint &point, int** imageLight, int height, int width,  int canvasColor);
};

#endif // SIHOUETTES_COUNTER_H
