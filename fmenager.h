#ifndef FMENAGER_H
#define FMENAGER_H

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <QString>
#include <QFile>
#include <QTextStream>

class fmenager
{
public:
    fmenager();
    ~fmenager();

    std::vector<int> parseConfigFile(std::string _filename);
    void createConfigFile(std::string _filename, std::string _param, std::string _propert);
    QString readPathFile();
};

#endif // FMENAGER_H
