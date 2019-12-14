//
//  Random.hpp
//  QueueSystem
//

#ifndef Random_hpp
#define Random_hpp

#include <cstdlib>
#include <cmath>

//class Random {
//public:
//    // [0, 1) 之间的服从均匀分布的随机值
//    static double uniform(double max = 1) {
//        return ((double)std::rand() / (RAND_MAX))*max;
//    }
//};

enum RandomType {
    UNIFORM,
    EXPONENTAIL,
    POISSON,
};

class Random {
public:
    static double getRandom(RandomType type, double parameter){ // 给定分布类型和参数，获得随机值
        switch (type) {
        case UNIFORM:
            return uniform(parameter);
            break;
        case EXPONENTAIL:
            return exponentail(parameter);
        case POISSON:
            return poisson(parameter);
        default:
            return 0;
            break;
        }
    }
    static double uniform(double max = 1){ // [0, 1) 之间的服从均匀分布的随机值
        return ((double)std::rand() / (RAND_MAX))*max;
    }
    static double exponentail(double lambda){  // 服从 lambda-指数分布的随机值
        return -log(1 - uniform()) / lambda;
    }
    static double poisson(double lambda){ // 服从 lambda-泊松分布的随机值
        int t = 0;
        double p = exp(-lambda);
        double f = p;
        double u = uniform();
        while (true) {
            if (f > u)
                break;
            t++;
            p = p*lambda / t;
            f += p;
        }
        return t;
    }
};
#endif /* Random_hpp */
