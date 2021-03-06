# Požadavky
- kompilátor podporující minimálně C++ 17
- vytvořit adresář ```lib``` v tomto adresáři pro následující knihovny
- knihovna pro práci s databází SQLite:
  - ke stažení [ZDE](https://github.com/SRombauts/SQLiteCpp/releases)
  - rozbalit do adresáře ```lib``` a složku přejmenovat na ```SQLiteCpp```
- knihovna pro práci s JSON soubory:
  - ke stažení [ZDE](https://github.com/nlohmann/json/releases)
  - stačí stáhnout hlavičkový soubor ```json.hpp``` a umístit ho do adresáře ```lib```
- knihovna Wt pro webové GUI:
  - ke stažení [ZDE](https://www.webtoolkit.eu/wt/download)
  - pro nějaké linuxové distibuce jsou dostupné balíčky, případně stáhnout z výše uvedeného odkazu a nainstalovat    
- pro sestavení lze využít skript ```build.sh```
- pro spuštění aplikace lze využít skript ```run.sh```, který spustí aplikaci lokálně na zabudovaném HTTP serveru (libwthttp)
