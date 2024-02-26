# STLY : C++ STL accessible from Python

Access the C++ STL from Python, specialized to the basic types (numeric types, and string)

```python
import stly

v = stly.vector_double()

v.append(1.0)
v.append(2.0)
v.append(3.0)

print(v[1]) # 2.0
print(len(v)) # 3
```

These are specialized types. `vector_double` in Python corresponds to
`std::vector<double>`. Avoid the extra memory requirements of a Python list is
a big advantage of using `stly`


### Converting to numpy


Vectors of numeric types support the buffer protocol, so you can easily convert
to a numpy array:

```python
import stly
import numpy as np

v = stly.vector_double()

for i in range(1024):
    v.append(i*i)

va = np.array(v, dtype=np.double)
```

### Converting to numpy (unsafe mode)

A numpy array can share memory with a stly vector

```python
import stly
import numpy as np

v = stly.vector_int32_t()

v.append(0)
v.append(1)
v.append(2)

va = np.array(v, dtype=np.int32, copy=False)

print(va) # [0 1 2]
print(v) # vector_int32_t[0, 1, 2]

v[0] = -1
print(va) # [-1  1  2]
print(v) # vector_int32_t[-1, 1, 2]
```

This thus creates the numpy array as a _view_ into the same memory and it will
work well **if you do not change the shape of the vector** after creating the
array view.

## Currently supported

- `std::vector`. Use types like `vector_uint32_t`
- `std::map`. Use types like `map_string_uint32_t`
- `std::unordered_set`. Use type like `unordered_set_uint32_t`


## Building stly

The following should work if you have installed `scikit-build`.

```bash
pip install .
```

**IMPORTANT**: As of Feb 2024, `stly` requires the `master` branch of `pybind11`!

Note that compilation can be very slow due to the need to specialize all the
types and conversions.


### Author

- [Luis Pedro Coelho](https://luispedro.org) (Queensland University of Technology). [luis@luispedro.org](mailto:luis@luispedro.org)

