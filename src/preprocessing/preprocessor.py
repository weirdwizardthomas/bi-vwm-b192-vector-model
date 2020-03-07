import json
import os
import nltk

from nltk import WordNetLemmatizer
from src.preprocessing.word_prunner import WordPrunner


def preprocess_collection(input_folder_path: str, output_persistence_path):
    """
    Parses and saves all documents from input_folder_path to output_persistence_path
    :param input_folder_path: path to the document collection to parse
    :param output_persistence_path: path to the output persistence file
    :return: None
    """
    documents = __parse_collection(input_folder_path)

    with open(output_persistence_path, 'w') as file:
        json.dump(documents, file)


def __parse_collection(input_folder_path: str) -> dict:
    """
    Parses all text files in the input_folder_path
    :param input_folder_path: path to the document collection to parse
    :return: dictionary, where key: file path, value: dictionary of terms and their frequencies
    """
    preprocessor = Preprocessor()
    documents = {}
    for file in os.listdir(input_folder_path):
        if file.endswith(".txt"):
            path, words = preprocessor.process_file(input_folder_path + file)
            documents[path] = words

    return documents


def load_documents(path: str):
    """
    Loads processed documents from a persistence file
    :param path: Path to the persistence file
    :return: dictionary of documents, where key: file path, value: dictionary of terms and their frequencies
    """
    with open(path, 'r') as file:
        return json.load(file)


class Preprocessor:
    """A class that processes a document for analysis

    Attributes
    ----------
    words: dict
        Dictionary of terms and their frequencies in the parsed document
    lemmatiser: WordNetLemmatizer
        Tool that lemmatises the document
    prunner:WordPrunner
        Tool that removes stop words, punctuation & other redundant terms from the document

    Methods
    -------
    process_file(path: str) -> (str,dict)
        Loads the document defined by path and processes it into terms and their frequencies
    """

    def __init__(self):
        self.words = {}
        self.lemmatiser = WordNetLemmatizer()
        self.prunner = WordPrunner()

    def process_file(self, path: str) -> (str, dict):
        """
        Reads a document from file and processes it into terms and their frequencies
        :param path: path to the document to open
        :return: tuple of document path & dictionary of terms and their frequencies
        """
        self.words = {}  # reset
        with open(path, 'r') as file:
            line = " "
            while line:
                line = file.readline()
                tokens = self.prunner.prune(nltk.word_tokenize(line))
                for word in tokens:
                    self.__add_word(word)
        return path, self.words

    def __add_word(self, term: str):
        """
        Adds a term to the document's dictionary
        :param term: Term to be added
        :return: None
        """
        # change case to lower
        word = self.lemmatiser.lemmatize(term)
        # add to words
        if word not in self.words:
            self.words[word] = 0
        self.words[word] += 1
