#ifndef MATHEMATICS_H
#define MATHEMATICS_H

#include "types.h"
#include <vector>

sn_real_t activationFunc(sn_real_t);

sn_real_t d_ActivationFunc(sn_real_t);

sn_real_t errorFunction(std::vector<sn_real_t>, std::vector<sn_real_t>);

sn_real_t d_errorFunction(std::vector<sn_real_t>, std::vector<sn_real_t>);

#endif // MATHEMATICS_H
