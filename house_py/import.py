from sys import argv, exit
import cs50
import csv


def get_args_verify():
    if len(argv) != 2:
        print("Argument ... ?")
        exit(1)
    return argv[1]


def csv_save(csv_name):
    data = []
    with open(csv_name, 'r') as file:
        try:
            d = csv.DictReader(file, delimiter=',')
            if d == None:
                print('Arquivo vazio !')
                exit(1)
        except:
            print(f'Not found {csv_name}')
            exit(1)

        for row in d:
            data.append(row)
    return data


def connection_db():
    db = cs50.SQL("sqlite:///students.db")
    return db


def query(db_conn, data):
    db_conn.execute("INSERT INTO students (first, middle, last, house, birth) VALUES(?, ?, ?, ?, ?)",
                    data['first'], data['middle'], data['last'], data['house'], data['birth'])


def mount_obj(array_name, house, birth):
    obj_student = {}
    length = len(array_name)

    obj_student['first'] = array_name[0]
    obj_student['middle'] = array_name[1] if length == 3 else None
    obj_student['last'] = array_name[2] if length == 3 else array_name[1]

    obj_student['house'] = house
    obj_student['birth'] = birth

    return obj_student


def data_insert(datas, db):
    length = len(datas)
    for row in range(length):
        name = datas[row]['name'].split()
        house = datas[row]['house']
        birth = datas[row]['birth']
        student_obj = mount_obj(name, house, birth)
        query(db, student_obj)


def main():
    csv_name = get_args_verify()
    data = csv_save(csv_name)
    db = connection_db()

    data_insert(data, db)


if __name__ == "__main__":
    main()
