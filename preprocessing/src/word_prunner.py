from nltk.corpus import stopwords


class WordPrunner:
    """A class that removes stop words, numbers & punctuation from a collection of strings.

    Attributes
    ----------
    stop_words : set
        set of stop word strings


    Methods
    -------
    prune(tokens: list) -> list
        removes all stop words, numbers & punctuation from tokens

    """

    def __init__(self):
        self.stop_words = set(stopwords.words('english'))

    def prune(self, tokens: list) -> list:
        """
        Removes all stop words, numbers & punctuation from tokens
        :param tokens: list of strings to be parsed
        :return: list of strings not containing any stop words, numbers, or punctuation
        """
        # remove stop words and punctuation
        tokens = [tokens.lower() for tokens in tokens]
        return [term for term in tokens if term.isalpha() and term not in self.stop_words]
