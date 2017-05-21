#ifndef EXTERNALVARS_H_INCLUDED
#define EXTERNALVARS_H_INCLUDED

#include <atomic>

namespace stride {
namespace util {
/// Interrupt variable. Stride will continue untill after the current checkpoint is saved if this variable is true.
extern std::atomic<bool> INTERRUPT;
extern std::atomic<unsigned int> INTERVAL;
extern std::atomic<bool> HDF5;
}
}
#endif