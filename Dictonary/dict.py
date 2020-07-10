# -*- coding: utf-8 -*-

import csv
import random

def read_cvs(filename):
    with open(filename) as csvfile:
        reader = csv.reader(csvfile, delimiter=";")
        Dictorany = []
        for row in reader:
            Dictorany.append(row)
        return Dictorany

def guees_artikel(Dictorany):
    random.shuffle(Dictorany)  # Sorts list randomly 
    counter = 0                # Setting counter for correct answers to 0
    for word in range(0, len(Dictorany)-1):
        answer = input("What's the Artikel for word {0} ? \n".format(Dictorany[word][1]))
        if answer == Dictorany[word][0]:
            print("Good! \n")
            counter += 1      # If answered correctly, increase counter
        elif answer == 0:     # Point of exit
            break
        else:
            print("Incorrect! The right atrikel ist {0}! \n".format(Dictorany[word][0]))
    print("You've got {0} of {1} words correct! \n".format(counter, len(Dictorany)))
    main()

def guess_patrizip(Partizip):
    random.shuffle(Partizip)
    counter = 0
    for word in range(0, len(Partizip)-1):
        answer1 = input("What's the Partizip 2 for word {0} ? \n".format(Partizip[word][0]))
        answer2 = input("Haben or Sein? \n")
        if answer1 == Partizip[word][1] and answer2 == Partizip[word][2]:
            print("Good! \n")
            counter += 1      # If answered correctly, increase counter
        elif answer1 == Partizip[word][1] and answer2 != Partizip[word][2]:
            print("Correct Partizip 2, but it used with {0} \n".format(Partizip[word][2]))
        elif answer1 != Partizip[word][1] and answer2 == Partizip[word][2]:
            print("Correct Haben/Sein, but Partizip 2 is {0} \n".format(Partizip[word][1]))
        elif answer == 0:     # Point of exit
            break
        else:
            print("Incorrect! The correct form is {0} and it's used with {1}! \n".format(Partizip[word][1], Partizip[word][2]))
    print("You've got {0} of {1} words correct! \n".format(counter, len(Partizip)))
    main()


def main():
    Answer = input("Please use one of the following options: \n 1. Artikel lernen \n 2. Partizip 2 lernen \n 0. Exit \n")
    if Answer == "1":
        Dict = read_cvs("dict.csv")
        guees_artikel(Dict)
    elif Answer == "2":
        Dict = read_cvs("patrizip2.csv")
        guess_patrizip(Dict)
    elif Answer == "0":
        pass
    else:
        print("Incorrect variant! Please choose 1 or 2! ")
        main()

if __name__ == "__main__":
    main()
