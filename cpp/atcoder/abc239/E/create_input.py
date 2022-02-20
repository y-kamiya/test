N = 200000
Q = 1

with open("input.txt.test", "w") as f:
    f.write(f"{N} {Q}\n")

    for n in range(1, N+1):
        f.write(f"{n} ")

    f.write(f"\n")

    for n in range(1, N):
        f.write(f"{n} {n+1}\n")

    f.write(f"1 2\n")
