size = 0
while size < 1 or size > 8:
    try:
        size = int(input('Height: '))
    except:
        continue

if size == 1:
    print('#')
else:
    for h in range(size):
        if h < size - 1:
            print(' ' * (size - 2 - h), '#' * (h+1))
        else:
            print('#' * (h+1))
