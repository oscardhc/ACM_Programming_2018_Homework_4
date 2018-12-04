a = int(input())
b = int(input())
if a < b :
    t = a
    a = b
    b = t
while b > 0 :
    t = a
    a = b
    b = t % b
str = ''
while a > 0 :
    if a % 2 == 1 :
        str = '1' + str
    else :
        str = '0' + str
    a = int(a / 2)
print(str)
