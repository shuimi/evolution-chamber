//
// Created by Vladimir on 17.05.2021.
//

#ifndef GENETIC_ALGS_FITNESSFUNCTIONCONSTRAINTS_H
#define GENETIC_ALGS_FITNESSFUNCTIONCONSTRAINTS_H

template <typename T>
class FitnessFunctionConstraints {
private:
    T leftBound;
    T rightBound;
public:
    FitnessFunctionConstraints(T leftBound, T rightBound) : leftBound(leftBound), rightBound(rightBound) {}

    T getLeftBound() const {
        return leftBound;
    }

    void setLeftBound(T leftBound) {
        FitnessFunctionConstraints::leftBound = leftBound;
    }

    T getRightBound() const {
        return rightBound;
    }

    void setRightBound(T rightBound) {
        FitnessFunctionConstraints::rightBound = rightBound;
    }

    T getMean(){
        return (rightBound + leftBound) / 2;
    }
};


#endif //GENETIC_ALGS_FITNESSFUNCTIONCONSTRAINTS_H
