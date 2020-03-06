import nltk
from nltk import WordNetLemmatizer

from src.preprocessing.word_prunner import WordPrunner


class Preprocessor:
    def __init__(self):
        self.words = {}
        self.lemmatiser = WordNetLemmatizer()
        self.prunner = WordPrunner()

    def read_file(self, path):
        with open(path, 'r') as file:
            line = " "
            while line:
                line = file.readline()
                for word in self.prunner.prune(nltk.word_tokenize(line)):
                    self.add_word(word)

    def add_word(self, term: str):
        # change case to lower
        term = self.lemmatiser.lemmatize(term.lower())
        # add to words
        if term not in self.words:
            self.words[term] = 0
        self.words[term] += 1
