import string

from nltk.corpus import stopwords


class WordPrunner:
    def __init__(self):
        self.stop_words = set(stopwords.words('english'))

    def prune(self, tokens: list) -> list:
        # remove stop words and punctuation
        tokens = [tokens.lower() for tokens in tokens]
        return [term for term in tokens if term.isalpha() and term not in self.stop_words]
