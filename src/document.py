import json
from json import JSONEncoder


class Document:
    def __init__(self, path: str, terms: dict):
        self.path = path
        self.terms = terms

    def to_json(self):
        return json.dumps(self, default=lambda o: o.__dict__)


class Encoder(JSONEncoder):
    def default(self, o: Document):
        return o.__dict__
