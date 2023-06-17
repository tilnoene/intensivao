from random import randint

def count(a, b):
    ans = 0
    
    for i in range(a, b+1):
        ans += sum([int(d) for d in list(str(i))])
    
    return ans

def solve():
    t = int(input())
    for i in range(t):
        a, b = map(int, input().split())
        
        print(count(a, b))

def gen():
    t = 100
    print(t)
    
    for i in range(t):
        a = randint(0, 1000)
        b = randint(a, 1000)
        
        print(f'{a} {b}')

# gen()
solve()
