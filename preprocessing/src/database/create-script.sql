CREATE TABLE Document
(
    id       INTEGER PRIMARY KEY AUTOINCREMENT,
    filename TEXT NOT NULL UNIQUE
);

CREATE TABLE Term
(
    id    INTEGER PRIMARY KEY AUTOINCREMENT,
    value TEXT NOT NULL UNIQUE
);

CREATE TABLE TermDocumentOccurrence
(
    id          INTEGER PRIMARY KEY AUTOINCREMENT,
    Term_id     INTEGER UNSIGNED NOT NULL,
    Document_id INTEGER UNSIGNED NOT NULL,
    count       INTEGER UNSIGNED NOT NULL,
    weight      DOUBLE,
    FOREIGN KEY (Document_id) REFERENCES Document (id),
    FOREIGN KEY (Term_id) REFERENCES Term (id),
    UNIQUE (Term_id, Document_id) ON CONFLICT REPLACE
);
