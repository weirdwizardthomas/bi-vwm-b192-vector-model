import json
import os
import nltk

from nltk import WordNetLemmatizer

from src.preprocessing.document import Document
from src.preprocessing.document_encoder import DocumentEncoder
from src.preprocessing.word_prunner import WordPrunner


def preprocess_folder(input_folder_path: str, output_persistence_path):
    preprocessor = Preprocessor()
    documents = []
    for file in os.listdir(input_folder_path):
        if file.endswith(".txt"):
            documents.append(preprocessor.read_file(input_folder_path + file))

    with open(output_persistence_path, 'w') as file:
        json.dump(documents, file, cls=DocumentEncoder)


class Preprocessor:
    def __init__(self):
        self.words = {}
        self.lemmatiser = WordNetLemmatizer()
        self.prunner = WordPrunner()

    def read_file(self, path: str) -> Document:
        self.words = {}
        with open(path, 'r') as file:
            line = " "
            while line:
                line = file.readline()
                tokens = self.prunner.prune(nltk.word_tokenize(line))
                for word in tokens:
                    self.add_word(word)
        return Document(path, self.words)

    def add_word(self, term: str):
        # change case to lower
        word = self.lemmatiser.lemmatize(term)
        # add to words
        if word not in self.words:
            self.words[word] = 0
        self.words[word] += 1
