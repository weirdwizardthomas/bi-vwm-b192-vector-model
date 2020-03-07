import json


class Document:
    def __init__(self, path: str, terms: dict):
        self.path = path
        self.terms = terms

    def to_json(self):
        return json.dumps(self, default=lambda o: o.__dict__)
