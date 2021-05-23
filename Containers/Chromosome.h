//
// Created by Vladimir on 15.05.2021.
//

#ifndef GENETIC_ALGS_CHROMOSOME_H
#define GENETIC_ALGS_CHROMOSOME_H

#include <vector>
#include <string>
#include <ostream>
#include <iomanip>

class Chromosome{
private:
    int uniqueIdentifier;

    std::vector<bool> genes;

public:

    Chromosome();
    Chromosome(int genesDec);
    Chromosome(const std::vector<bool> &genesVector);

    virtual ~Chromosome();

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
    void glue(Chromosome* anotherChromosome);
    void reverse(int startIndex, int endIndex);
    void reverse();
    Chromosome* erase(int startIndex, int endIndex);
    void swap(int aIndex, int bIndex);
    static Chromosome* concatenate(Chromosome* a, Chromosome* b);
    Chromosome* getSubsequence(int startIndex, int endIndex);
    void insert(int startIndex, Chromosome* anotherChromosome);
    int size();

    int getUniqueIdentifier() const;

    static int getHammingDistance(Chromosome* A, Chromosome* B);

    static double getNormalizedHammingDistance(Chromosome* A, Chromosome* B);

    Chromosome* getCopy();

    static void addZeroes(Chromosome *A, int n);
    static std::vector<short> addZeroes(std::vector<short> &A, int n);
    static void complementChromosome(Chromosome *A, Chromosome *B);
    static void complementChromosome(std::vector<short> &A, std::vector<short> &B);

    std::vector<short> getBitwiseDecimal();

};



#endif //GENETIC_ALGS_CHROMOSOME_H
