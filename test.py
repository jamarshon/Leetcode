# def solution(N, A):
#     ret = [0] * N
#     max_cnt = 0
#     pos_max_cnt = 0
    
#     for e in A:
#         if e == N + 1:
#             max_cnt = pos_max_cnt
#         else:
#             ret[e-1] = max(max_cnt, ret[e-1]) + 1
#             pos_max_cnt = max(pos_max_cnt, ret[e-1])
    
#     for i in range(len(ret)):
#         ret[i] = max(ret[i], max_cnt)
    
#     return ret

import math
def solution(N):
    # write your code in Python 3.6
    res = 0
    prev = -1
    while N:
        curr = math.log(N & ~(N-1), 2)
        print prev, curr
        if prev != -1:
            res = max(res, curr - prev)
        prev = curr
        N &= N - 1
    return int(res)

solution(1041)