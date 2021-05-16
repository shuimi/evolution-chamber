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

    void setGen(int index, bool gen);
    bool getGen(int index);
    void addGen(bool gen);
    void swap(int startIndex, int endIndex);

    int getUniqueIdentifier() const;

    static int getHammingDistance(BinaryChromosome* A, BinaryChromosome* B);

    static double normalizedDistance(BinaryChromosome* A, BinaryChromosome* B);

    int getSize();

    BinaryChromosome* getCopy();

    static BinaryChromosome* concatenate(BinaryChromosome* a, BinaryChromosome* b);

};



#endif //GENETIC_ALGS_BINARYCHROMOSOME_H
