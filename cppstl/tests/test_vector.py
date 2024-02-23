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

