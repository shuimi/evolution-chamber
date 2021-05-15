//
// Created by Vladimir on 15.05.2021.
//

#ifndef GENETIC_ALGS_CHROMOSOME_H
#define GENETIC_ALGS_CHROMOSOME_H

#include <vector>
#include <string>

class Chromosome{
private:
    std::vector<bool> genes;
public:

    Chromosome(const std::vector<bool> &genSet);

    Chromosome(int genSetDec);

    Chromosome();

    virtual ~Chromosome();

    const std::vector<bool> &get() const;

    void set(const std::vector<bool> &genSet);

    int getDecimal();

    void setDecimal(int genSetDec);

    std::string getBinaryString();

};



#endif //GENETIC_ALGS_CHROMOSOME_H
