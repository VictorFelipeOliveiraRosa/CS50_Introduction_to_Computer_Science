from sys import argv, exit
import cs50
import csv


def get_args_verify():
    if len(argv) != 2:
        print("Argument ... ?")
        exit(1)
    return argv[1]


def connection_db():
    db = cs50.SQL("sqlite:///students.db")
    return db


def query(db, house):
    try:
        select_query = f"SELECT first, middle, last, house, birth \
                           FROM students \
                          WHERE house = {'?'} \
                       ORDER BY last, first ASC"
        select = db.execute(select_query, house)
    except:
        print('Query ERROR')
        return None
    return select


def view_students(students):
    for row in students:
        string = row['first'] + ' '
        string += row['middle'] + ' ' if row['middle'] != None else ''
        string += row['last']
        string += ' born ' + str(row['birth'])
        print(string)


def main():
    house = get_args_verify()
    conn_db = connection_db()

    select = query(conn_db, house)
    if select == None:
        exit(1)
    else:
        view_students(select)


if __name__ == "__main__":
    main()