from sys import argv, exit
import csv


def veryfy_sequence(seq, k):
    max = 0
    count = 0
    size = len(k)
    length = len(seq)

    for i in range(0, length, size):
        if (size+i) < length:
            if seq[i:(size+i)] == k:
                count += 1
            else:
                if count > max:
                    max = count
                count = 0
        if count > max:
            max = count
    return max


def sequence_dna(k, sequence_dna):
    sequence_count = []
    length = len(sequence_dna)
    max = 0
    count = 0
    for j in range(len(k)):
        size = len(k[j])
        for i in range(length):
            if (size+i) < length:
                if sequence_dna[i:(size+i)] == k[j]:
                    seq = sequence_dna[i:]
                    count = veryfy_sequence(seq, k[j])
            if count > max:
                max = count
        sequence_count.append(max)
        max = 0
        count = 0
    return sequence_count


def compare_dna(seq, peoples):
    length = len(seq)
    cont = 0
    for people in peoples:
        n = []
        for p in people.values():
            n.append(p)
        del(n[0])

        n_arr = list(map(lambda x: int(x), n))

        for i in range(length):
            if seq[i] == n_arr[i]:
                cont += 1
        if cont == length:
            return people['name']
        cont = 0
    return 'No match'


if __name__ == "__main__":
    if len(argv) != 3:
        print('ERROR')
        exit(1)
    data = []
    with open(argv[1], 'r') as file:
        try:
            d = csv.DictReader(file, delimiter=',')
            if d == None:
                print('Arquivo vazio !')
                exit(1)
        except:
            print(f'Not found {argv[1]}')
            exit(1)

        for col in d:
            data.append(col)

    try:
        file_text = open(argv[2], 'r', encoding='utf-8')
        if file_text == None:
            print('ERRO')
            exit(1)
    except:
        print(f'Not found {argv[2]}')
        exit(1)

    keys = list()
    for i in data[0].keys():
        keys.append(i)
    del(keys[0])
    sequence = ''
    for i in file_text:
        sequence = i

    seq = sequence_dna(keys, sequence)

    result = compare_dna(seq, data)
    print(result)