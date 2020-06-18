#include <iostream>
#include <vector>
#include <random>
#include <math.h>

#include "lib_v1/malib.h"

ml::matrix<float>& randomizeMatrix(ml::matrix<float>& ma);
ml::matrix<float>& sigmoid(ml::matrix<float>& ma);
ml::matrix<float> sigmoidD(ml::matrix<float>& ma);

int main() {
    srand(time(nullptr));

    const int epochs = 10000;
    const int inputSize = 2;
    const int hiddenSize = 4;
    const int outputSize = 1;
    const float learnRate = 0.3;

    ml::matrix<float> inp = {
        {1, 0},
        {1, 1},
        {0, 0},
        {0, 1}
    };

    ml::matrix<float> outp = {
        {1},
        {0},
        {0},
        {1}
    };

    ml::matrix<float> weightsIH = {hiddenSize, inputSize};
    ml::matrix<float> weightsHO = {outputSize, hiddenSize};

    randomizeMatrix(weightsIH);
    randomizeMatrix(weightsHO);

    for(int e = 0; e < epochs; e++){
        for(int ex = 0; ex < inp.height(); ex++){
            ml::matrix<float> currInp = {{inp(0, ex), inp(1, ex)}};
            ml::matrix<float> currRes = {{outp(0, ex)}};

            ml::matrix<float> hidden = currInp % weightsIH;
            sigmoid(hidden);
            ml::matrix<float> out = hidden % weightsHO;
            sigmoid(out);

            if(e == epochs - 1) {
                std::cout << currRes(0, 0) << " -> " << out(0, 0) << std::endl;
            }

            ml::matrix<float> err = currRes - out;

            ml::matrix<float> deltaOut = err * sigmoidD(out);
            ml::matrix<float> deltaH = deltaOut % weightsHO.t() * sigmoidD(hidden);

            ml::matrix<float> weightDHO = deltaOut % hidden * learnRate;
            ml::matrix<float> weightsDIH = deltaH.t() % currInp * learnRate;

            weightsIH += weightsDIH.t();
            weightsHO += weightDHO.t();
        }
    }

    return 0;
}

ml::matrix<float>& randomizeMatrix(ml::matrix<float>& ma) {
    for(float& f : ma){
        f = (float) rand() / RAND_MAX;
    }
    return ma;
}

ml::matrix<float>& sigmoid(ml::matrix<float>& ma) {
    for(float& f : ma) {
        f = 1 / (float)(1 + pow(M_E, -f));
    }
    return ma;
}

ml::matrix<float> sigmoidD(ml::matrix<float>& ma) {
    ml::matrix<float> c {ma};
    for(float& f : c) {
        f = f * (1 - f);
    }
    return c;
}