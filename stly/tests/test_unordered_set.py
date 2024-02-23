import stly

def test_unordered_set_smoke():
    for cl in [
            stly.unordered_set_uint32_t,
            stly.unordered_set_double,
            ]:
        u = cl()
        for i in range(10):
            u.add(i)
        assert len(u) == 10
        assert u
        assert len(list(u)) == 10

        for i in range(10):
            assert i in u
        assert 10 not in u
        u.clear()
        for i in range(10):
            assert i not in u
        assert len(u) == 0
        assert not u


