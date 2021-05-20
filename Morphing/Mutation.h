//
// Created by Vladimir on 20.05.2021.
//

#ifndef GENETIC_ALGS_MUTATION_H
#define GENETIC_ALGS_MUTATION_H


#include "../Entities/BinaryChromosome.h"

class Mutation {
private:

public:

    static std::pair<int, int> getRandIndexCouple(int chromosomeSize);

    /// [Service method].
    /// [description] Mutation operator kernel.
    /// Pure function.
    /// @return Mutated BinaryChromosome
    static BinaryChromosome* Mutation::simple(
        BinaryChromosome* individual,
        ///<[in] Source BinaryChromosome
        int index
        ///<[in] Gen position
    );

    /// [Service method].
    /// [description] Mutation operator kernel.
    /// Pure function.
    /// @return Mutated BinaryChromosome
    static BinaryChromosome* Mutation::inversion(
        BinaryChromosome* individual,
        ///<[in] Source BinaryChromosome
        int startIndex,
        ///<[in] Start position in chromosome
        int endIndex
        ///<[in] End position in chromosome
    );

    /// [Service method].
    /// [description] Mutation operator kernel.
    /// Pure function.
    /// Swap method wrapper.
    /// @return Mutated BinaryChromosome
    static BinaryChromosome *swap(
        BinaryChromosome* individual,
        ///<[in] Source BinaryChromosome
        int aGenIndex,
        ///<[in] First gen position
        int bGenIndex
        ///<[in] Second gen position
    );

    /// [Service method].
    /// [description] Mutation operator kernel.
    /// Pure function.
    /// @return Mutated BinaryChromosome
    static BinaryChromosome* transpose(
            BinaryChromosome* individual,
            ///<[in] Source BinaryChromosome
            int startIndex,
            ///<[in] First gen position
            int endIndex
            ///<[in] Second gen position
    );

    /// [description] Mutation operator based on Fibonacci numbers.
    /// Based on rand().
    /// @return Mutated BinaryChromosome
    static BinaryChromosome *swapFibonacci(
        BinaryChromosome *individual
        ///<[in] Source BinaryChromosome
    );

    /// [description] Inversion Mutation operator.
    /// Based on rand().
    /// @return Mutated BinaryChromosome
    static BinaryChromosome *inversion(
        BinaryChromosome *individual
        ///<[in] Source BinaryChromosome
    );

    /// [description] Simple Mutation operator.
    /// Based on rand().
    /// @return Mutated BinaryChromosome
    static BinaryChromosome *simple(
        BinaryChromosome *individual
        ///<[in] Source BinaryChromosome
    );

    /// [description] Mutation operator based on transpose.
    /// Based on rand().
    /// @return Mutated BinaryChromosome
    static BinaryChromosome *transpose(
        BinaryChromosome *individual
        ///<[in] Source BinaryChromosome
    );

};


#endif //GENETIC_ALGS_MUTATION_H
