#include <pybind11/pybind11.h>
#include <pybind11/stl_bind.h>

#include <stdint.h>
#include <map>
#include <set>

namespace py = pybind11;
using string = std::string;

#define EXPOSE_FOR_ALL \
    EXPOSE(  int8_t) \
    EXPOSE( uint8_t) \
    EXPOSE( int16_t) \
    EXPOSE(uint16_t) \
    EXPOSE( int32_t) \
    EXPOSE(uint32_t) \
    EXPOSE( int64_t) \
    EXPOSE(uint64_t) \
    \
    EXPOSE(float) \
    EXPOSE(double) \
    \
    EXPOSE(string)

#define EXPOSE2_FOR_ALL \
    EXPOSE2_FOR_ALL_0(  int8_t) \
    EXPOSE2_FOR_ALL_0( uint8_t) \
    EXPOSE2_FOR_ALL_0( int16_t) \
    EXPOSE2_FOR_ALL_0(uint16_t) \
    EXPOSE2_FOR_ALL_0( int32_t) \
    EXPOSE2_FOR_ALL_0(uint32_t) \
    EXPOSE2_FOR_ALL_0( int64_t) \
    EXPOSE2_FOR_ALL_0(uint64_t) \
    \
    EXPOSE2_FOR_ALL_0(float) \
    EXPOSE2_FOR_ALL_0(double) \
    \
    EXPOSE2_FOR_ALL_0(string)

#define EXPOSE2_FOR_ALL_0(t0) \
    EXPOSE2(t0,  int8_t) \
    EXPOSE2(t0, uint8_t) \
    EXPOSE2(t0,  int16_t) \
    EXPOSE2(t0, uint16_t) \
    EXPOSE2(t0,  int32_t) \
    EXPOSE2(t0, uint32_t) \
    EXPOSE2(t0,  int64_t) \
    EXPOSE2(t0, uint64_t) \
    \
    EXPOSE2(t0, float) \
    EXPOSE2(t0, double) \
    \
    EXPOSE2(t0, string)


#define EXPOSE(t) \
    PYBIND11_MAKE_OPAQUE(std::vector<t>);
EXPOSE_FOR_ALL
#undef EXPOSE

#define EXPOSE2(t0, t1) \
    PYBIND11_MAKE_OPAQUE(std::map<t0, t1>);
EXPOSE2_FOR_ALL
#undef EXPOSE2

PYBIND11_MODULE(cppstl, m) {

#define EXPOSE(t) \
    py::bind_vector< std::vector <t> >(m, "vector_" #t);
    EXPOSE_FOR_ALL
#undef EXPOSE

#define EXPOSE2(t0, t1) \
    py::bind_map< std::map <t0, t1> >(m, "map_" #t0 "_" #t1);
    EXPOSE2_FOR_ALL
#undef EXPOSE2

    m.doc() = "pybind11 example plugin"; // optional module docstring
}
