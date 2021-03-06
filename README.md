# Information retrieval – Vektorový model

## Základní informace
Ve složce `data/Gutenberg/txt` jsou umístěny soubory, s nimiž jsme náš projekt testovali. Dále ve složce `data/persistence` jsou uloženy soubory, které se generují při preprocessingu a výpočtu vah termů (tj. je možné hned spustit aplikaci pro samotné dotazování).

## Struktura projektu
Projekt se skládá ze tří oddělených aplikací:
1) `preprocessing/` (základní zpracování dokumentů – odstranění nevýznamových slov, lematizace, uložení obsahu jednotlivých dokumentů do databáze)
2) `weight_calculation/` (výpočet vah termů v jednotlivých dokumentech)
3) `querying/` (dotazování na podobnost dokumentů z webového rozhraní)

## Požadavky na běh
Požadavky na běh jsou popsány u každé konkrétní aplikace v souboru `REQUIREMENTS.md` spolu s informacemi, odkud stáhnout a kam případně umístit knihovny třetích stran. Nachází se zde i informace, jakým způsobem lze danou aplikaci spustit.
