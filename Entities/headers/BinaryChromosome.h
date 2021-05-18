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

    std::vector<bool> &get();
    void set(const std::vector<bool> &genSet);

    int getDecimal();
    void setDecimal(int genSetDec);

    std::string getBinaryString();

    void invert();
    void printout();

    void setGen(int index, bool gen);
    bool getGen(int index);
    void addGen(bool gen);
    void addGen(int number);
    void addGenDecimalBitwise(int number);
    void glue(BinaryChromosome* anotherChromosome);
    void reverse(int startIndex, int endIndex);
    void reverse();
    BinaryChromosome* erase(int startIndex, int endIndex);
    void swap(int aIndex, int bIndex);
    static BinaryChromosome* concatenate(BinaryChromosome* a, BinaryChromosome* b);
    BinaryChromosome* getSubsequence(int startIndex, int endIndex);
    void insert(int startIndex, BinaryChromosome* anotherChromosome);
    int getSize();

    int getUniqueIdentifier() const;

    static int getHammingDistance(BinaryChromosome* A, BinaryChromosome* B);

    static double getNormalizedHammingDistance(BinaryChromosome* A, BinaryChromosome* B);

    BinaryChromosome* getCopy();

    static BinaryChromosome addZeroes(BinaryChromosome *A, int n);
    static std::vector<short> addZeroes(std::vector<short> &A, int n);
    static void complementChromosome(BinaryChromosome *A, BinaryChromosome *B);
    static void complementChromosome(std::vector<short> &A, std::vector<short> &B);

    std::vector<short> getBitwiseDecimal();

};



#endif //GENETIC_ALGS_BINARYCHROMOSOME_H
