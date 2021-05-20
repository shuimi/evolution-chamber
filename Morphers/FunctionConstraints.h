//
// Created by Vladimir on 17.05.2021.
//

#ifndef GENETIC_ALGS_FUNCTIONCONSTRAINTS_H
#define GENETIC_ALGS_FUNCTIONCONSTRAINTS_H

template <typename T>
class FunctionConstraints {
private:
    T leftBound;
    T rightBound;
public:
    FunctionConstraints(T leftBound, T rightBound) : leftBound(leftBound), rightBound(rightBound) {}

    T getLeftBound() const {
        return leftBound;
    }

    void setLeftBound(T leftBound) {
        FunctionConstraints::leftBound = leftBound;
    }

    T getRightBound() const {
        return rightBound;
    }

    void setRightBound(T rightBound) {
        FunctionConstraints::rightBound = rightBound;
    }

    T getMean(){
        return (rightBound + leftBound) / 2;
    }

    Generation* reduceGenerationToInterval(Generation* generation);

};

template<typename T>
Generation *FunctionConstraints<T>::reduceGenerationToInterval(Generation *generation) {
    Generation* output = generation->copy();
    output->reduce([this](BinaryChromosome* chromosome){
        return !(chromosome->getDecimal() >= leftBound && chromosome->getDecimal() <= rightBound);
    });
    return output;
}


#endif //GENETIC_ALGS_FUNCTIONCONSTRAINTS_H
