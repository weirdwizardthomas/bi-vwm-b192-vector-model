import sqlite3


class Database:
    # reference: https://stackoverflow.com/a/38078544
    def __init__(self, name):
        self._conn = sqlite3.connect(name, detect_types=sqlite3.PARSE_DECLTYPES | sqlite3.PARSE_COLNAMES)
        self._cursor = self._conn.cursor()

    def __enter__(self):
        return self

    def __exit__(self, exc_type, exc_val, exc_tb):
        self.commit()
        self.connection.close()

    @property
    def connection(self):
        return self._conn

    @property
    def cursor(self):
        return self._cursor

    def commit(self):
        self.connection.commit()

    def execute(self, sql, params=None):
        self.cursor.execute(sql, params or ())

    def executemany(self, sql, params=None):
        self.cursor.executemany(sql, params or ())

    def fetchall(self):
        return self.cursor.fetchall()

    def fetchone(self):
        return self.cursor.fetchone()

    def query(self, sql, params=None):
        self.cursor.execute(sql, params or ())
        return self.fetchall()

    def last_primary_key(self):
        return self.cursor.lastrowid

    def drop(self):
        """
        Deletes all data from tables
        :return: None
        """
        self.execute('DELETE FROM TermDocumentOccurrence')
        self.execute('DELETE FROM Term')
        self.execute('DELETE FROM Document')
        self.connection.commit()