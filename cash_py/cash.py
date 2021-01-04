cash = 0
while cash <= 0:
    try:
        cash = float(input('Change owed: '))
    except:
        continue
count = 0
cash = round(cash * 100)
while cash > 0:
    if cash >= 25:
        cash -= 25
    elif cash >= 10:
        cash -= 10
    elif cash >= 5:
        cash -= 5
    elif cash >= 1:
        cash -= 1
    count += 1
print(count)

