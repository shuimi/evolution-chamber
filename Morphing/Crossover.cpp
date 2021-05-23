//
// Created by Vladimir on 15.05.2021.
//

#include "Crossover.h"
#include "../Service/Maths.h"


///service methods
///service methods
///service methods


std::vector<int> Crossover::getFibonacciVector(int numbersAmount) {
    std::vector<int> output;
    for (int i = 0; i < numbersAmount; i++) {
        output.push_back(Maths::fibonacci(i));
    }
    return output;
}

std::vector<std::vector<bool>> Crossover::makeBinaryNumbersTable(int n) {

    int rowsAmount = pow(2, n);
    std::vector<std::vector<bool>> table;

    for (int i = 0; i < rowsAmount; i++) {
        std::vector<bool> row;
        int temp_i = i;
        do {
            row.push_back(temp_i % 2);
            temp_i /= 2;
        } while (temp_i > 0);

        while (row.size() < n)
            row.push_back(0);

        std::reverse(row.begin(), row.end());
        table.push_back(row);
    }
    return table;
}

std::vector<Chromosome *> Crossover::makeParentParts(Chromosome *parent, int n) {
    int t = 1;
    while (n > Maths::fibonacci(t)) { t++; }
    std::vector<int> fibNumbers = getFibonacciVector(t);
    std::vector<Chromosome *> parentParts;

    //separately push first(left) part
    parentParts.push_back(new Chromosome(std::vector<bool>(1, parent->get().at(0))));

    for (int i = 0; i < fibNumbers.size() - 1; i++) {
        Chromosome *tempChromosome = parent->getSubsequence(fibNumbers.at(i), fibNumbers.at(i + 1) - 1);
        parentParts.push_back(tempChromosome);
    }

    //separately push last(right) part
    Chromosome *tempChromosome = parent->getSubsequence(fibNumbers.back(), parent->get().size() - 1);
    if (!tempChromosome->get().empty()) parentParts.push_back(tempChromosome);

    return parentParts;
}

int Crossover::getGoldenRatioSeparationPoint(int l, int r, double error) {
    for (int s = l; s <= r; s++) {
        double a = (double) s - (double) l;
        double b = (double) r - (double) s;
        double ratio = a / b;
        if (ratio < 1.61 + error && ratio > 1.61 - error) {
            return s;
        }
    }
}

short Crossover::indexOfValueInsideChromosome(int l, int r, std::vector<short> c, short valueToFind) {
    int valueInsideSwathIndex = -1;
    for (int j = l; j < r; ++j)
        if (c.size() == valueToFind) {
            valueInsideSwathIndex = j;
            break;
        }
    return valueInsideSwathIndex;
}

int Crossover::insertAppropriateValueChildA(
    std::vector<short> parentA,
    std::vector<short> parentB,
    int indexParentB,
    int separationPoint
) {
    short specialValueParentA = parentB.at(indexParentB);
    int locatedSameValueIndexParentB = indexOfValueInsideChromosome(
        0,
        parentB.size(),
        parentB,
        specialValueParentA
    );

    if (locatedSameValueIndexParentB >= 0 && locatedSameValueIndexParentB < separationPoint){
        insertAppropriateValueChildA(
                parentA,
                parentB,
                locatedSameValueIndexParentB,
                separationPoint
        );
    }

    else return indexParentB;
}

int Crossover::insertAppropriateValueChildB(
    std::vector<short> parentA,
    std::vector<short> parentB,
    int idxParentA,
    int separationPoint
) {
    short specialValueParentB = parentA.at(idxParentA);
    int locatedSameValueIndexParentA = indexOfValueInsideChromosome(0, parentB.size(), parentB, specialValueParentB);

    srand(time(NULL));
    if (locatedSameValueIndexParentA >= 0 && locatedSameValueIndexParentA < separationPoint && rand() % 100 < 5)
        insertAppropriateValueChildB(parentA, parentB, locatedSameValueIndexParentA, separationPoint);
    else return idxParentA;
}


/// crossovers
/// crossovers
/// crossovers


Generation *Crossover::doublePoint(
Chromosome* parentA,
Chromosome* parentB
) {

    Chromosome::complementChromosome(parentA, parentB);
    if(parentA->size() <= 2){
        auto result = new Generation(-1);
        result->add(parentA);
        result->add(parentB);
        return result;
    }

    int parentsSize = parentA->size();

    int leftBound = rand() % (parentsSize - 2);
    int rightBound = rand() % (parentsSize - 1);

    while (rightBound <= leftBound)
        rightBound = rand() % parentA->get().size();

    std::vector<bool> childA, childB, childC, childD, childE, childF;

    for (int i = 0; i < leftBound; i++) {
        childA.push_back(parentA->getGen(i));
        childB.push_back(parentA->getGen(i));
        childC.push_back(parentA->getGen(i));
        childD.push_back(parentB->getGen(i));
        childE.push_back(parentB->getGen(i));
        childF.push_back(parentB->getGen(i));
    }
    for (int i = leftBound; i < rightBound; i++) {
        childA.push_back(parentA->getGen(i));
        childB.push_back(parentB->getGen(i));
        childC.push_back(parentB->getGen(i));
        childD.push_back(parentA->getGen(i));
        childE.push_back(parentA->getGen(i));
        childF.push_back(parentB->getGen(i));
    }
    for (int i = rightBound; i < parentsSize; i++) {
        childA.push_back(parentB->getGen(i));
        childB.push_back(parentA->getGen(i));
        childC.push_back(parentB->getGen(i));
        childD.push_back(parentA->getGen(i));
        childE.push_back(parentB->getGen(i));
        childF.push_back(parentA->getGen(i));
    }

    std::vector<Chromosome*> children = {
            new Chromosome(childA), new Chromosome(childB), new Chromosome(childC),
            new Chromosome(childD), new Chromosome(childE), new Chromosome(childF)
    };
    return new Generation(children);
}

Generation *Crossover::fibonacci(
Chromosome *parentA,
Chromosome *parentB
) {

    Chromosome::complementChromosome(parentA, parentB);

    std::vector<int>
            fibNumbers = getFibonacciVector(parentA->size());
    std::vector<std::vector<bool>>
            binaryTable = makeBinaryNumbersTable(parentA->size()); //A->0, B->1

    std::vector<Chromosome *>
            partsParentA = makeParentParts(parentA, fibNumbers.size());
    std::vector<Chromosome *>
            partsParentB = makeParentParts(parentB, fibNumbers.size());

    std::vector<Chromosome *> children;

    for (int i = 1; i < binaryTable.size() - 1; i++) {
        Chromosome *child = new Chromosome();

        for (int j = 0; j < parentA->size() - 1; j++) {
            if (!binaryTable[i][j]) child->glue(partsParentA.at(j));
            else child->glue(partsParentB.at(j));
        }

        if (children.empty()) children.push_back(child);

        bool childAdded = false;

        for (int k = 0; k < children.size(); k++) {
            for (int j = 0; j < child->size(); j++) {

                if (children.at(k)->getGen(j) != child->getGen(j)) {
                    children.push_back(child);
                    childAdded = true;
                    break;
                }

            }
            if (childAdded) break;
        }
    }

    return new Generation(children);
}

Generation *Crossover::goldenRatio_(
Chromosome *parentA,
Chromosome *parentB,
double errorThreshold
) {

    Chromosome::complementChromosome(parentA, parentB);
    std::vector<bool> childA, childB;
    int separationPoint = Crossover::getGoldenRatioSeparationPoint(0, parentA->size(), errorThreshold);

    for (int i = 0; i < separationPoint; i++) {
        childA.push_back(parentA->get().at(i));
        childB.push_back(parentB->get().at(i));
    }
    for (int i = separationPoint; i < parentA->get().size(); i++) {
        childA.push_back(parentB->get().at(i));
        childB.push_back(parentA->get().at(i));
    }

    std::vector<Chromosome *> children = {
            new Chromosome(childA), new Chromosome(childB)
    };
    return new Generation(children);
}

Generation *Crossover::PMX(
Chromosome *parentA,
Chromosome *parentB
) {
    std::vector<short> A = parentA->getBitwiseDecimal();
    std::vector<short> B = parentB->getBitwiseDecimal();
    Chromosome::complementChromosome(A, B);

    int separationPoint = rand() % parentA->size();
    while (separationPoint <= 0 || separationPoint >= A.size() - 1) {
        srand(time(NULL));
        separationPoint = rand() % parentA->size();
    }

    std::vector<short> childA, childB;
    for (int i = 0; i < separationPoint; i++) {
        childA.push_back(A.at(i));
        childB.push_back(B.at(i));
    }

    //-----------------------------------------------------------CHILD A
    //search for unique values in swath's indexes in parentB
    std::vector<short> uniqueIndexesParentB;
    for (short i = 0; i < separationPoint; i++) {
        if (indexOfValueInsideChromosome(0, separationPoint, childA, B.at(i)) < 0)
            uniqueIndexesParentB.push_back(i);
    }

    //making special inserts
    for (int i = 0; i < uniqueIndexesParentB.size(); ++i) {
        if (childA.size() < B.size()) {
            int indexToInsert = insertAppropriateValueChildA(A, B, uniqueIndexesParentB.at(i), separationPoint);
            childA.push_back(B.at(indexToInsert) + rand() % 2);
        }
    }
    //remained inserts
    for (int i = childA.size(); i < B.size() && childA.size() < B.size();) {
        childA.push_back(B.at(i));
    }

    //-----------------------------------------------------------CHILD B
    //search for unique values in swath's indexes in parentB
    std::vector<short> uniqueIndexesParentA;
    for (short i = 0; i < separationPoint; i++) {
        if (indexOfValueInsideChromosome(0, separationPoint, childB, A.at(i)) < 0)
            uniqueIndexesParentA.push_back(i);
    }

    //making special inserts
    for (int i = 0; i < uniqueIndexesParentA.size(); ++i) {
        if (childB.size() < A.size()) {
            int indexToInsert = insertAppropriateValueChildB(A, B, uniqueIndexesParentA.at(i), separationPoint);
            childB.push_back(A.at(indexToInsert));
        }
    }
    //remained inserts
    for (int i = childB.size(); i < A.size() && childB.size() < A.size();) {
        childB.push_back(A.at(i));
    }

    Chromosome *a = new Chromosome();
    Chromosome *b = new Chromosome();

    for (int i = 0; i < childA.size() && i < childB.size(); ++i) {
        a->addGenDecimalBitwise((int) childA.at(i));
        b->addGenDecimalBitwise((int) childB.at(i));
    }
    std::vector<Chromosome *> children = {a, b};
    return new Generation(children);
}

Generation *Crossover::OX(
Chromosome *parentA,
Chromosome *parentB
) {
    Chromosome::complementChromosome(parentA, parentB);

    int separationPoint = rand() % parentA->size();
    while (separationPoint == 0 || separationPoint == parentA->size()) {
        srand(time(NULL));
        separationPoint = rand() % parentA->size();
    }

    std::vector<bool> childA, childB;

    for (int i = 0; i < separationPoint; i++) {
        childA.push_back(parentA->getGen(i));
        childB.push_back(parentB->getGen(i));
    }

    //remains
    int i = 0;
    while (childA.size() < parentA->size()) {
        childA.push_back(parentB->getGen(i + separationPoint));
        childB.push_back(parentA->getGen(i + separationPoint));
        i++;
    }

    std::vector<Chromosome *> children = {
            new Chromosome(childA),
            new Chromosome(childB)
    };
    return new Generation(children);
}

Generation *Crossover::CX(
Chromosome *parentA,
Chromosome *parentB
) {

    std::vector<short> A = parentA->getBitwiseDecimal();
    std::vector<short> B = parentB->getBitwiseDecimal();

    Chromosome::complementChromosome(A, B);

    Chromosome *fullSequence = new Chromosome();
    Generation *out = new Generation(0);

    std::vector<bool> parentAMarked;
    parentAMarked.assign(A.size(), false);

    bool flagOfTurn = false;
    for (int i = 0; i < A.size() && fullSequence->getBitwiseDecimal().size() < A.size();) {

        int startPoint = i;
        if (!flagOfTurn) fullSequence->addGenDecimalBitwise((int) A.at(i));
        flagOfTurn = false;

        if (parentAMarked.at(i)) {
            i++;
        } else {

            fullSequence->addGenDecimalBitwise((int) B.at(i));
            parentAMarked.at(i) = true;

            for (int j = i + 1; j < A.size(); j++) {
                if (A.at(j) == B.at(i)) {
                    i = j;
                    flagOfTurn = true;
                    break;
                }
                if (j == A.size() - 1) j = 0;
                if (j == startPoint) {
                    i++;
                    parentAMarked.assign(A.size(), false);
                    break;
                }
            }
        }
    }

    out->add(fullSequence);
    return out;
}

Generation *Crossover::goldenRatio(Chromosome *parentA, Chromosome *parentB) {
    return goldenRatio_(parentA, parentB, Crossover::STANDARD_GOLDEN_RATIO_ERROR_THRESHOLD);
}

