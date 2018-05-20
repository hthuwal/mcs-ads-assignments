import sys


def editditance(x, y, cost, M):
    n = len(x)
    m = len(y)
    dp = [[0 for j in range(0, m+1)] for i in range(0, n+1)]

    for i in range(0, m+1):
        dp[0][i] = ((i % M)*(cost[1] % M) % M)

    for i in range(0, n+1):
        dp[i][0] = ((i % M)*(cost[3] % M) % M)

    for i in range(1, n+1):
        for j in range(1, m+1):
            a = (cost[1] % M + dp[i][j-1]) % M
            b = (cost[2] % M + dp[i-1][j-1]) % M
            c = (cost[3] % M + dp[i-1][j]) % M

            dp[i][j] = a if a < b else b
            dp[i][j] = dp[i][j] if dp[i][j] < c else c

            if x[i-1] == y[j-1]:
                d = (cost[0] % M + dp[i-1][j-1]) % M
                dp[i][j] = dp[i][j] if dp[i][j] < d else d

    return dp[n][m]

sys.stdin = open("/home/hthuwal/Downloads/in.txt", "r")
t = int(raw_input().strip())
while(t > 0):
    x = raw_input().strip()
    y = raw_input().strip()
    cost = raw_input().strip().split(',')
    cost = [int(c.strip()) for c in cost]
    print editditance(x, y, cost, 1000000007)
    t -= 1
