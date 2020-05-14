# Požadavky
- Python verze 3.6 a vyšší
- knihovna pro práci s lidským jazykem NLTK:
  - ke stažení [ZDE](https://www.nltk.org/install.html)
  - návod, jak provést instalaci, je též k dispozici na stránce uvedené výše
  - pokud nebudou balíčky stopwords, punkt a wordnet staženy automaticky, tak je nutné ještě provést následující sekvenci příkazů:
    1) python3
    2) import nltk
    3) nltk.download('stopwords')
    4) nltk.download('punkt')
    5) nltk.download('wordnet')
- nejdříve je potřeba spustit create skript pro vytvoření SQLite databáze s potřebnými tabulkami, poté je možné spustit samotný skript na preprocessing
  - v našem případě lze toto provést z této složky pomocí příkazu:
    - `sqlite3 ./../data/persistence/docs_and_terms.db < src/database/create-script.sql`
- skript na preprocessing se spouští se třemi parametry – cestou ke složce s dokumenty k preprocessingu (přepínač -i), cestou kde je uložena databáze (přepínač -o) a cestou kam má být uložen soubor s nejvyššími výskyty termů (přepínač -f)
  - z této složky by šel například spustit následovně:
    - `python3 -m src.main.py -i ./../data/Gutenberg/txt/ -o ./../data/persistence/docs_and_terms.db -f ./../data/persistence/most_frequent_words.json`
