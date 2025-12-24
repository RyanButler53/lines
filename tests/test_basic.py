import nanobind_example as m

f = m.Fraction(4)
f2 = m.Fraction(5, 6)

print(f"f: {f}, f2; {f2}")
pt = m.Point(f, f2)
print(f"Point: {pt}")
