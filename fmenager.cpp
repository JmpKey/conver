#include "fmenager.h"

fmenager::fmenager() {}

fmenager::~fmenager() {}

std::vector<int> fmenager::parseConfigFile(std::string _filename)
{
    std::vector<int> configValues; // for storing integer values
    std::ifstream file(_filename);
    std::string line;

    if (!file)
    {
        std::cerr << "File error" << _filename << std::endl;
        return configValues; // returning an empty vector
    }

    while (std::getline(file, line))
    {
        size_t pos = line.find('=');

        if (pos != std::string::npos)
        {
            std::string valueStr = line.substr(pos+1);

            // removing the spaces at the beginning and end of the line
            valueStr.erase(0, valueStr.find_first_not_of(" \t\r\n"));
            valueStr.erase(valueStr.find_last_not_of(" \t\r\n") + 1);

            // converting a string to an integer and adding it to a vector
            int value = std::stoi(valueStr);
            configValues.push_back(value);
        }
    }

    file.close();
    return configValues;
}

void fmenager::createConfigFile(std::string _filename, std::string _param, std::string _propert)
{
    std::ofstream file(_filename,  std::ios_base::app);

    if (!file)
    {
        std::cerr << "File error" << _filename << std::endl;
        return;
    }

    file << _param << "=" << _propert << "\n";

    file.close();
}

QString fmenager::readPathFile() {
    QString fileName = "ffmpeg_path.cap";
    QFile file(fileName);
    QString line;

    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);

        while (!in.atEnd()) {
            line = in.readLine();
        }

        file.close();
    } else {
        std::cout << "Unable to open file: " << fileName.toStdString() << std::endl;
    }

    return line;
}
