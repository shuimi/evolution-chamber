//
// Created by Vladimir on 15.05.2021.
//

#ifndef GENETIC_ALGS_BINARYCHROMOSOME_H
#define GENETIC_ALGS_BINARYCHROMOSOME_H

#include <vector>
#include <string>
#include <ostream>
#include <iomanip>

class BinaryChromosome{
private:
    int uniqueIdentifier;
    std::vector<bool> genes;
public:

    BinaryChromosome();
    BinaryChromosome(int genesDec);
    BinaryChromosome(const std::vector<bool> &genesVector);

    virtual ~BinaryChromosome();

    const std::vector<bool> &get() const;
    void set(const std::vector<bool> &genSet);

    int getDecimal();
    void setDecimal(int genSetDec);

    std::string getBinaryString();

    void invert();

    void printout();

    int getUniqueIdentifier() const;
};



#endif //GENETIC_ALGS_BINARYCHROMOSOME_H
