from random import choice, shuffle
import json


def get_data(file):
    temp = list()
    with open(file) as file_handle:
        for line in file_handle:
            line = line.rstrip()
            line = line.split(' ')
            if len(line) == 2:
                temp.append(line)
            else:
                temp.append(line[0])
    # for now has to be like this because
    # split is creating table
    return temp


def check_pesels(pesels):
    pesels_counter = 0
    for pesel in pesels:
        counter = 0
        for number in pesels:
            if pesel == number:
                counter += 1
        if counter != 1:
            print(f"{pesel} repeats!")
            exit(0)
        pesels_counter += 1


def main():
    pesels = get_data('source/random_pesel.txt')
    shuffle(pesels)
    males = get_data('source/random_males.txt')
    females = get_data('source/random_females.txt')
    people = dict()
    people['people'] = list()

    check_pesels(pesels)

    for pesel in pesels:
        data = dict()
        data['pesel'] = pesel
        sex_number = int(pesel[9])
        names = choice(males) if sex_number % 2 != 0 else choice(females)
        data['name'] = names[0]
        data['surname'] = names[1]
        people['people'].append(data)

    with open("../people.json", "w") as file_handle:
        json.dump(people, file_handle, indent=4, ensure_ascii=False)


if __name__ == "__main__":
    main()
