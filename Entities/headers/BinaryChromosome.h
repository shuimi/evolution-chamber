//
// Created by Vladimir on 15.05.2021.
//

#ifndef GENETIC_ALGS_BINARYCHROMOSOME_H
#define GENETIC_ALGS_BINARYCHROMOSOME_H

#include <vector>
#include <string>
#include <ostream>

class BinaryChromosome{
private:
    int uniqueIndex;
    std::vector<bool> genes;
public:

    BinaryChromosome(const std::vector<bool> &genesVector);

    BinaryChromosome(int genesDec);

    BinaryChromosome();

    virtual ~BinaryChromosome();

    const std::vector<bool> &get() const;

    void set(const std::vector<bool> &genSet);

    int getDecimal();

    void setDecimal(int genSetDec);

    std::string getBinaryString();

    int getUniqueIndex() const;

    void setUniqueIndex(int uniqueIndex);

    friend std::ostream &operator<<(std::ostream &os, const BinaryChromosome &chromosome);
};



#endif //GENETIC_ALGS_BINARYCHROMOSOME_H
