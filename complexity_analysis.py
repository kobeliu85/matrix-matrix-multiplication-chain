def matrix_chain_order(p):
    n = len(p) - 1  # Number of matrices
    m = [[0] * n for _ in range(n)]  # Initialize a table to store optimal subproblem solutions
    s = [[0] * n for _ in range(n)]  # Initialize a table to store the split points

    for i in range(n):
        m[i][i] = 0

    for l in range(2, n + 1):
        for i in range(n - l + 1):
            j = i + l - 1
            m[i][j] = float('inf')
            for k in range(i, j):
                q = m[i][k] + m[k + 1][j] + p[i] * p[k + 1] * p[j + 1]
                if q < m[i][j]:
                    m[i][j] = q
                    s[i][j] = k

    return m, s

def print_optimal_parens(s, i, j):
    if i == j:
        print(f"A{i + 1}", end="")
    else:
        print("(", end="")
        print_optimal_parens(s, i, s[i][j])
        print_optimal_parens(s, s[i][j] + 1, j)
        print(")", end="")

dimx = 256
r = 10
dimy = 256
nrhs = 512

# Example usage:
matrix_dimensions = [dimx, r, r, dimy, nrhs]  # For 4 matrices
m, s = matrix_chain_order(matrix_dimensions)
print_optimal_parens(s, 0, len(matrix_dimensions) - 2)
