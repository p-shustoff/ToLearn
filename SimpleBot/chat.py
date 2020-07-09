class ChatBot():

    def __init__(self, name):
        self.name = name

    def greetins(self):
        print("Hello, nice to meet you! Mein name ist {0} Please tell me what's your name ?".format(self.name))

    def run(self):
        while True:
            Answer = input()
            small = Answer.lower()
            if small.startswith('bye') or small.startswith('goodbye'):
                print("Goodbye")
                break
            elif small.startswith('p') or small.startswith('m'):
                print("Oh, i like your name, let me check how many letters in your name \n")
                print("There are {0} letters in name {1} \n".format(len(small), Answer))
                print("Okay, give another name!")
            else:
                print("Get outta here {0}!".format(Answer))
                break

def main():
    bot = ChatBot("Igor")
    bot.greetins()
    bot.run()

if __name__ == '__main__':
    main()