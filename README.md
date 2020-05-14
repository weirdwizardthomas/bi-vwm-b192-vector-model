# Information retrieval – Vektorový model

## Struktura projektu
Projekt se skládá ze tří oddělených aplikací.
1) `preprocessing/` (základní zpracování dokumentů – odstranění nevýznamových slov, lematizace, uložení obsahu jednotlivých dokumentů do databáze)
2) `weight_calculation/` (výpočet vah termů v jednotlivých dokumentech)
3) `querying/` (dotazování na podobnost dokumentů z webového rozhraní)

## Požadavky na běh
Jsou popsány u každé konkrétní aplikace v souboru `REQUIREMENTS.md` spolu s informacemi, odkud stáhnout a kam případně umístit knihovny třetích stran.
