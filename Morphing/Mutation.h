//
// Created by Vladimir on 20.05.2021.
//

#ifndef GENETIC_ALGS_MUTATION_H
#define GENETIC_ALGS_MUTATION_H


#include <functional>
#include "../Containers/Chromosome.h"

class Mutation {
private:

public:

    static std::pair<int, int> getRandIndexCouple(int chromosomeSize);

    /// static Chromosome* XXX(Chromosome*) is standard declaration
    /// which is required to use Mating

    /// [description] Mutation operator based on Fibonacci numbers.
    /// Based on rand().
    /// @return Mutated Chromosome
    static Chromosome *swapFibonacci(
        Chromosome *individual
        ///<[in] Source Chromosome
    );

    /// [description] Inversion Mutation operator.
    /// Based on rand().
    /// @return Mutated Chromosome
    static Chromosome *inversion(
        Chromosome *individual
        ///<[in] Source Chromosome
    );

    /// [description] Simple Mutation operator.
    /// Based on rand().
    /// @return Mutated Chromosome
    static Chromosome *simple(
        Chromosome *individual
        ///<[in] Source Chromosome
    );

    /// [description] Mutation operator based on transpose_.
    /// Based on rand().
    /// @return Mutated Chromosome
    static Chromosome *transpose(
        Chromosome *individual
        ///<[in] Source Chromosome
    );

    /// [Service method].
    /// [description] Mutation operator kernel.
    /// Pure function.
    /// @return Mutated Chromosome
    static Chromosome* Mutation::simple_(
            Chromosome* individual,
            ///<[in] Source Chromosome
            int index
            ///<[in] Gen position
    );

    /// [Service method].
    /// [description] Mutation operator kernel.
    /// Pure function.
    /// @return Mutated Chromosome
    static Chromosome* Mutation::inversion_(
            Chromosome* individual,
            ///<[in] Source Chromosome
            int startIndex,
            ///<[in] Start position in chromosome
            int endIndex
            ///<[in] End position in chromosome
    );

    /// [Service method].
    /// [description] Mutation operator kernel.
    /// Pure function.
    /// Swap method wrapper.
    /// @return Mutated Chromosome
    static Chromosome *swap(
            Chromosome* individual,
            ///<[in] Source Chromosome
            int aGenIndex,
            ///<[in] First gen position
            int bGenIndex
            ///<[in] Second gen position
    );

    /// [Service method].
    /// [description] Mutation operator kernel.
    /// Pure function.
    /// @return Mutated Chromosome
    static Chromosome* transpose_(
            Chromosome* individual,
            ///<[in] Source Chromosome
            int startIndex,
            ///<[in] First gen position
            int endIndex
            ///<[in] Second gen position
    );

};


#endif //GENETIC_ALGS_MUTATION_H
