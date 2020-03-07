from json import JSONEncoder

from src.preprocessing.document import Document


class DocumentEncoder(JSONEncoder):
    def default(self, o: Document):
        return o.__dict__
