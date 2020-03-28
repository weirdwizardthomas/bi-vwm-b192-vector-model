import json
import os
import nltk

from nltk import WordNetLemmatizer

from database.database import Database
from config import DATABASE_FILE, OUTPUT_PERSISTENCE_PATH, WORD_HIGHEST_FREQUENCY_FILE
from word_prunner import WordPrunner


def preprocess_collection(input_folder_path: str):
    """
    Parses and saves all documents from input_folder_path to output_persistence_path
    :param input_folder_path: path to the document collection to parse
    :param output_persistence_path: path to the output persistence file
    :return: None
    """
    Database(OUTPUT_PERSISTENCE_PATH + DATABASE_FILE).drop()
    frequencies = __parse_collection(input_folder_path)

    with open(OUTPUT_PERSISTENCE_PATH + WORD_HIGHEST_FREQUENCY_FILE, 'w') as file:
        json.dump(frequencies, file)


def __parse_collection(input_folder_path: str) -> dict:
    """
    Parses all text files in the input_folder_path
    :param input_folder_path: path to the document collection to parse
    :return: dictionary, where key: file path, value: dictionary of terms and their frequencies
    """
    preprocessor = Preprocessor()
    index = 1
    max_index = len(os.listdir(input_folder_path))
    for file in os.listdir(input_folder_path):
        print("[Processing file", index, "/", max_index, "]", file)
        index += 1
        if file.endswith(".txt"):
            preprocessor.process_file(input_folder_path + file)

    return preprocessor.get_most_frequent_words()


def load_documents(path: str) -> dict:
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
    terms: dict
        Dictionary of terms and their frequencies in the parsed document
    lemmatiser: WordNetLemmatizer
        Tool that lemmatises the document
    prunner:WordPrunner
        Tool that removes stop words, punctuation & other redundant terms from the document
    terms_highest_frequencies: dict
        Dictionary of terms and their highest frequency in the collection

    Methods
    -------
    process_file(path: str) -> (str,dict)
        Loads the document defined by path and processes it into terms and their frequencies
    """

    def __init__(self):
        self.terms = {}
        self.lemmatiser = WordNetLemmatizer()
        self.prunner = WordPrunner()
        self.terms_highest_frequencies = {}

    def process_file(self, path: str):
        """
        Reads a document from file and processes it into terms and their frequencies
        :param path: path to the document to open
        :return: tuple of document path & dictionary of terms and their frequencies
        """
        self.terms = {}  # reset
        try:
            self.__process_terms(path)
            self.__update_frequencies()
            self.__persist(path)
        except FileNotFoundError:
            pass

    def __process_terms(self, path):
        with open(path, 'r') as file:
            line = " "
            while line:
                try:
                    line = file.readline()
                    for word in self.prunner.prune(nltk.word_tokenize(line)):
                        self.__add_term(self.lemmatise(word))
                except UnicodeDecodeError:
                    pass

    def lemmatise(self, word):
        return self.lemmatiser.lemmatize(word)

    def get_most_frequent_words(self) -> dict:
        return self.terms_highest_frequencies

    def __add_term(self, term: str):
        """
        Adds a term to the document's dictionary
        :param term: Term to be added
        :return: None
        """
        # add to terms
        if term not in self.terms:  # is a new term
            self.terms[term] = 0
        self.terms[term] += 1

    def __update_frequencies(self):
        """
        Updates all frequencies to contain the highest current frequency of a given term
        If the frequency of a term in the currently processed document is higher than the current highest, replace it
        :return: None
        """
        for term in self.terms:
            if term not in self.terms_highest_frequencies:  # is a new word
                self.terms_highest_frequencies[term] = self.terms[term]

            if self.terms_highest_frequencies[term] < self.terms[term]:
                self.terms_highest_frequencies[term] = self.terms[term]

    def __persist(self, input_file):
        database = Database(OUTPUT_PERSISTENCE_PATH + DATABASE_FILE)
        database.execute('''INSERT OR IGNORE INTO Document(filename) VALUES (?)''', [input_file])
        database.commit()
        document_key = database.last_primary_key()
        for term in self.terms:
            database.execute('''INSERT OR IGNORE INTO Term(value) VALUES (?)''', [term])
            database.execute('''SELECT id FROM Term WHERE value = ?''', [term])
            term_key = database.fetchone()[0]
            if term_key is None:
                term_key = database.last_primary_key()
            database.execute('''INSERT INTO TermDocumentOccurrence(Term_id, Document_id, count) VALUES (?,?,?)''',
                             [term_key, document_key, self.terms[term]])
        database.commit()
