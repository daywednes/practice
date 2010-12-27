import sys

def read_ints(f):
  return [int(x) for x in f.readline().split()]

def init(next, d, k, N):
  for i in range(N):
    total = 0
    for j in range(N):
      if(total + d[(i+j)%N] > k):
        next[(i, 1)] = ((i+j)%N, total)
        break
      total += d[(i+j)%N]
    else:
      next[(i, 1)] = (i, total)

def find(next, i, R):
  if (i, R) in next:
    return next[(i, R)]
  _i = i
  _R = R

  cost = 0
  if R&1:
    _i, cost=next[(_i, 1)]
    _R -= 1
  _i, cost1 = find(next, _i, _R/2)
  _i, cost2 = find(next, _i, _R/2) 
  cost += cost1
  cost += cost2
  next[(i, R)] = _i, cost
  return (_i, cost)


def main():
  with open('input.txt') as fin:
    with open('output.txt', 'w') as fout:
      [T] = read_ints(fin)
      for testid in range(1, T+1):
        [R, k, N] = read_ints(fin)
        d = read_ints(fin)
        next = {}
        init(next, d, k, N)
        print('Case #{0}: {1}'.format(testid, find(next,0,int(R))[1]), file = fout)

if __name__ == '__main__':
  main()

