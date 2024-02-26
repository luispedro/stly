#include <pybind11/pybind11.h>
#include <pybind11/stl_bind.h>

#include <stdint.h>
#include <map>
#include <unordered_set>

namespace py = pybind11;
using string = std::string;

#define EXPOSE_FOR_ALL_NUMS \
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

#define EXPOSE_FOR_ALL \
    EXPOSE_FOR_ALL_NUMS \
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

template <typename T>
struct UnorderedSet {
    std::unordered_set<T> raw_;
    bool __contains__(T x) const {
        return raw_.find(x) != raw_.end();
    }
    bool __bool__() const {
        return !raw_.empty();
    }
    size_t __len__() const {
        return raw_.size();
    }
    void insert(T x) {
        raw_.insert(x);
    }
    void clear() {
        raw_.clear();
    }
};

#define EXPOSE(t) \
    PYBIND11_MAKE_OPAQUE(UnorderedSet<t>);
    EXPOSE_FOR_ALL
#undef EXPOSE

PYBIND11_MODULE(_stly, m) {

// reserve and capacity are not exposed by default
// we expose them here because they can still be useful
#define EXPOSE(t) \
    py::bind_vector<std::vector<t>>(m, "vector_" #t, py::buffer_protocol()) \
      .def("reserve",  &std::vector<t>::reserve,  "reserves storage") \
      .def("capacity", &std::vector<t>::capacity, "returns the number of elements that can be held in currently allocated storage") \
      ;
    EXPOSE_FOR_ALL_NUMS
#undef EXPOSE
    py::bind_vector<std::vector<std::string>>(m, "vector_string") \
      .def("reserve",  &std::vector<std::string>::reserve,  "reserves storage") \
      .def("capacity", &std::vector<std::string>::capacity, "returns the number of elements that can be held in currently allocated storage") \
      ;

#define EXPOSE(t) \
    py::class_<UnorderedSet<t>>(m, "unordered_set_" #t) \
        .def(py::init<>()) \
        .def("clear", &UnorderedSet<t>::clear) \
        .def("add", &UnorderedSet<t>::insert) \
        .def("__contains__", &UnorderedSet<t>::__contains__) \
        .def("__len__", &UnorderedSet<t>::__len__) \
        .def("__bool__", &UnorderedSet<t>::__bool__) \
        .def("__iter__", [](const UnorderedSet<t> &s) { return py::make_iterator(s.raw_.begin(), s.raw_.end()); }, py::keep_alive<0, 1>()) \
        ;
    EXPOSE_FOR_ALL
#undef EXPOSE

#define EXPOSE2(t0, t1) \
    py::bind_map< std::map <t0, t1> >(m, "map_" #t0 "_" #t1);
    EXPOSE2_FOR_ALL
#undef EXPOSE2

    m.doc() = "pybind11 example plugin"; // optional module docstring
}
