import cppstl

def test_vector_smoke():
    for cl in [
            cppstl.vector_uint32_t,
            cppstl.vector_double,
            ]:
        v = cl()
        for i in range(10):
            v.append(i)
        assert len(v) == 10
        assert v

        for i in range(10):
            assert v[i] == i
        assert v[-1] == 9
        v.clear()
        assert len(v) == 0
        assert not v

def test_np_conversion():
    import numpy as np

    v = cppstl.vector_double()

    for i in range(1024):
        v.append(i*i)

    va = np.array(v, dtype=np.double)
    assert np.all(va == np.arange(1024)**2)

    va = np.array(v, dtype=np.float64, copy=False)
    assert np.all(va == np.arange(1024)**2)
