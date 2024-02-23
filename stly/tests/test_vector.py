import stly

def test_vector_smoke():
    for cl in [
            stly.vector_uint32_t,
            stly.vector_double,
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

    v = stly.vector_double()

    for i in range(1024):
        v.append(i*i)

    va = np.array(v, dtype=np.double)
    assert np.all(va == np.arange(1024)**2)

    va = np.array(v, dtype=np.float64, copy=False)
    assert np.all(va == np.arange(1024)**2)
