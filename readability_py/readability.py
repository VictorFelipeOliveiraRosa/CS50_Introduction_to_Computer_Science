import re


def count_letters(text):
    text = text.lower()
    rep = [' ', '.', ',', '!', '?', ';', "'", '"', ':', '-', '`']
    for l in range(len(rep)):
        text = text.replace(rep[l], '')
    return len(text)


def count_words(text):
    text = text.lower()
    rep = ['.', ',', '!', '?', ';', "'", '"', ':']
    for l in range(len(rep)):
        text = text.replace(rep[l], '')
    number_words = text.split()
    return len(number_words)


def count_sentence(text):
    text = text.lower()
    rep = [',', ';', "'", '"', ':', '`', '-']
    for l in range(len(rep)):
        text = text.replace(rep[l], '')
    text = text[:-1]
    number_sentence = re.split('[?.!]', text)
    return len(number_sentence)


text = input('Text: ')
number_l = count_letters(text)
number_w = count_words(text)
number_s = count_sentence(text)

l = 0.0588 * number_l / number_w * 100
s = 0.296 * number_s / number_w * 100
index = round(l - s - 15.8)

if index <= 1:
    print(f'Before Grade {index}')
elif index > 1 and index <= 15:
    print(f'Grade {index}')
elif index >= 16:
    print(f'Grade 16+')