#include "mathematics.h"
#include <cmath>
#include <cassert>

sn_real_t sigmoid(sn_real_t x)
{
    return 1 / (1 + std::exp(-x));
}

sn_real_t d_sigmoid(sn_real_t x)
{
    return sigmoid(x) * (1 - sigmoid(x));
}

sn_real_t activationFunc(sn_real_t x)
{
    return sigmoid(x);
}

sn_real_t d_ActivationFunc(sn_real_t x) {
    return d_sigmoid(x);
}

/*!
 * \brief errorFunction
 * \param result
 * \param target
 * \return sum of (result - target)^2
 */
sn_real_t errorFunction(std::vector<sn_real_t> result, std::vector<sn_real_t> target)
{
    const size_t len = result.size();
    assert(len == target.size());
    sn_real_t res = 0;
    for (size_t i = 0; i < len; ++i)
    {
        sn_real_t t = result[i] - target[i];
        res = res + t * t;
    }
    return res;
}

/*!
 * \brief d_errorFunction
 * \param result
 * \param target
 * \return sum of 2(result - target)
 */
sn_real_t d_errorFunction(std::vector<sn_real_t> result, std::vector<sn_real_t> target)
{
    const size_t len = result.size();
    assert(len == target.size());
    sn_real_t res = 0;
    for (size_t i = 0; i < len; ++i)
    {
        sn_real_t t = result[i] - target[i];
        res = res + 2 * t;
    }
    return res;
}
