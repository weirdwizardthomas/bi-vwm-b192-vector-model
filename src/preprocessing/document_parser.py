from src.preprocessing.preprocessor import preprocess_folder, load_documents

preprocess_folder("./data/sample/", "./data/persistence/documents.json")
documents = load_documents("./data/persistence/documents.json")
