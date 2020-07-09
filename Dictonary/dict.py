# -*- coding: utf-8 -*-

import csv
import random

def read_cvs():
    with open("dict.csv") as csvfile:
        reader = csv.reader(csvfile, delimiter=";")
        Dictorany = list(reader)
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

def main():
    Dict = read_cvs()
    guees_artikel(Dict)

if __name__ == "__main__":
    main()
