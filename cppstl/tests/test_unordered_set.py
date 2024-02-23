import cppstl

def test_unordered_set_smoke():
    for cl in [
            cppstl.unordered_set_uint32_t,
            cppstl.unordered_set_double,
            ]:
        v = cl()
        for i in range(10):
            v.add(i)
        assert len(v) == 10
        assert v

        for i in range(10):
            assert i in v
        assert 10 not in v
        v.clear()
        for i in range(10):
            assert i not in v
        assert len(v) == 0
        assert not v

