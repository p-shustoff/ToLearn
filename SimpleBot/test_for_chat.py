import unittest
from chat import *

class BotTesting(unittest.TestCase):
    def test_init(self):
        bot = ChatBot("Ivan")
        self.assertEqual(bot.name, "Ivan")

    def test_greeting(self):
        bot = ChatBot("Ivan")
        bot.greetins()

if __name__ == '__main__':
    unittest.main()
