# Descriere
Andrei are pasiunea de a citi multe carti.
Prietenii săi i-au dat foarte multe recomandări de cărți, iar el nu le poate reține pe toate. Așa că
vom crea un program în care Andrei își poate nota cărțile pe care vrea să le citească.
Fiecare carte va avea: un titlu unic, un autor, un rating (număr întreg, oferit de prietenul
lui Andrei odată cu recomandarea) și numărul de pagini.
Andrei trebuie să poată să introducă cărți noi și să caute după cărți deja introduse
într-un mod eficient. De asemenea, programul trebuie sa aibă o opțiune de auto-complete
pentru când Andrei nu își amintește în totalitate titlul sau autorul unei cărți.

# Implementare
Pentru gestionarea cărților, vom folosi următoarele structuri de date:
1. T1: un arbore de prefixe (trie), în care cheia este titlul cărții, iar informația reținută la
finalul căii este un pointer către o structură cu informațiile cărții;
2. T2: un alt arbore de prefixe (trie), în care cheia este un autor, iar informația reținută este
un alt arbore de prefixe (trie), în care sunt reținute cărțile scrise de acel autor, reținute
asemenea structurii 1.

## 2.1. Arbori de prefixe (Trie)
Este un arbore multi-căi (fiecare nod poate avea oricât descendenți).
Este un tip de arbore de căutare cu următoarele proprietăți:
● Fiecare nod poate avea între 0 și |Σ| descendenți (|Σ| reprezinta dimensiunea
alfabetului).
● Spre deosebire de un arbore binar de căutare, unde fiecărui nod i se asociază o
cheie, la arborele de prefixe cheile se asociază căii până la nod.

# Detalii comenzi

### Va trebui să gestionam cărțile adăugate de Andrei pe baza unui set de comenzi citite dintr-un fișier.

## 3.1. Adăugare recomandare carte
```
Sintaxă: add_book <titlu>:<autor>:<rating>:<numar_pagini>
Mod de funcționare: cartea este adăugată atât în T1, cât și în arborele de cărți
corespunzător autorului său din T2. Dacă pentru autor nu există încă o cheie în T2, atunci va fi
adăugat.
Dacă în T1 și T2 deja există cartea, atunci structurile rămân nemodificate.
Exemplu: add_book Wuthering Heights:Emily Bronte:9:391 /* se
parcurge arborele T1 pe calea dată de titlul ”Wuthering Heights”. Dacă nodurile din această cale
nu existau deja, ele sunt create. În ultimul nod, se păstrează informația legată de carte; similar,
se parcurge arborele T2 pe calea dată de numele autorului ”Emily Bronte”, se crează arborele
corespondent cărților sale și apoi în acela se adaugă pe calea ”Wuthering Heights” informația
legată de carte. */
```
## 3.2. Căutare carte
```
Sintaxă: search_book <titlu>
Mod de funcționare: cartea este căutată în T1. Dacă nu există, va fi întors un mesaj
de forma:
Cartea <titlu> nu exista in recomandarile tale.
Altfel, dacă este găsită cartea, se va afișa un mesaj de forma:
Informatii recomandare: <titlu>, <autor>, <rating>, <numar_pagini>
Exemplu: search_book Wuthering Heights /* se caută în T1 calea ”Wuthering
Heights” */
Cartea Wuthering Heights nu exista in recomandarile tale. /* în caz că nu
se găsește în T1 */
Informatii recomandare: Wuthering Heights, Emily Bronte, 9, 391 /* în
caz că a fost găsită */
```
## 3.3. Auto-complete pentru căutare carte
```
Sintaxă: search_book <prefix_titlu>~
Mod de funcționare: se caută în T1 cărți al căror titlu începe cu <prefix_titlu>.
Se afișează pe câte un rând primele maxim 3 titluri de cărți care încep cu <prefix_titlu>
(primele din punct de vedere lexicografic).
<titlu_carte1>
<titlu_carte2>
<titlu_carte3>
Dacă nu există nicio carte care începe cu prefix_titlu, se afișează mesajul:
Nicio carte gasita.
Exemplu: search_book Wuthering~ /* caută în T1 calea ”Wuthering” și afișează
primele maxim 3 chei pană la un nod ce conține o carte */
Wuthering Heights
```
## 3.4. Afișare cărți autor
```
Sintaxă: list_author <autor>
Mod de funcționare: se va căuta în T2 după numele autorului. După vor fi afișate
toate cărțile din arborele de căutare corespondent lui, în ordine lexicografică:
<titlu_carte1>
<titlu_carte2>
<titlu_carte3>
…
Dacă autorul nu există în T2, atunci se va afișa un mesaj de forma:
Autorul <autor> nu face parte din recomandarile tale.
Exemplu: list_author Emily Bronte /* caută în T2 după cheia ”Emily Bronte” și
parcurge arborele corespondent cărților sale, afișând toate titlurile */
Wuthering Heights
```
## 3.5. Auto-complete pentru afișare cărți autor
```
Sintaxă: list_author <prefix_autor>~
Mod de funcționare: se caută în T2 autori al căror nume începe cu
<prefix_autor>. Se afișează pe câte un rând primii maxim 3 autori care încep cu
<prefix_autor> (primii din punct de vedere lexicografic).
<nume_autor1>
<nume_autor2>
<nume_autor3>
Dacă nu există niciun autor care începe cu <prefix_autor>, se va afișa mesajul:
Niciun autor gasit.
```
## 3.6. Căutare în cărțile unui autor
```
Sintaxă: search_by_author <autor>:<titlu>
Mod de funcționare: se caută în T2 după numele autorului, iar apoi în arborele de
căutare corespondent lui, după titlul cărții. Dacă autorul nu există, se afișează mesajul:
Autorul <autor> nu face parte din recomandarile tale.
Altfel, mesajele sunt aceleași ca pentru comanda search_book <titlu>.
Exemplu: search_by_author Emily Bronte:Wuthering Heights /* se
parcurge T2 pe calea ”Emily Bronte”, iar în arborele corespondent autoarei, se caută calea
”Wuthering Heights” */
```
## 3.7. Auto-complete pentru căutare în cărțile unui autor
```
Sintaxă: search_by_author <prefix_autor>~
Mod de funcționare: idem comanda list_author <prefix_autor>~.
Sintaxă: search_by_author <autor>:<prefix_titlu>~
Mod de funcționare: idem comanda search_book <prefix_titlu>~, doar că
se va căuta mai întâi în T2 după numele autorului, apoi în arborele de căutare corespondent lui,
după <prefix_titlu>.
Dacă autorul nu există în T2, atunci se va afișa un mesaj de forma:
Autorul <autor> nu face parte din recomandarile tale.
```
## 3.8. Ștergere recomandare
```
Sintaxă: delete_book <titlu>
Mod de funcționare: comanda șterge atât informațiile despre carte, cât și cheile din
T1 și din arborele aferent autorului din T2. Dacă nu mai există alte cărți pentru acel autor, atunci
trebuie să fie ștearsă și cheia autorului din T2, precum și eliberată memoria ocupată de arborele
de căutare corespondent cărților sale.
Dacă titlul nu există, atunci se va afișa un mesaj de forma:
Cartea <titlu> nu exista în recomandarile tale.
```

# 4. Restricții și precizări
● Titlul unei cărți este un șir de maxim 50 de caractere.


● Nu există două cărți cu același nume.

● Ordinea lexicografică este dată de următorul alfabet (fără ghilimele):
"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789.-'?! "

● Numele unui autor este un șir de maxim 40 de caractere. Pentru simplitate, vom
considera că toate caracterele din numele autorului aparțin alfabetului de mai sus.

● Programul va fi rulat astfel:
```
./tema3 input_file output_file.
```
● T1 și T2 respectă structura descrisă. Datele nu vor fi păstrate în niciun alt mod

# Descrierea functionalitatilor
## Functia ConstrNod1
- Initializeaza un nod al arborelui de tip T1: aloca memorie nodului, 
initializeaza cu 0 variabila frunza din structura si cu NULL toate nodurile 
copil al nodului curent

## Functia ConstrNod2
- Analogic ConstrNod1 dat pentru arbore de tip T2

## Functia add_book_T1
- Adauga in arbore de tip T1 cartea primita parametru pe calea corespunzatoare 
titlului cartii, deasemenea adauga la finalul caii structura cu informatii 
despre carte

## Functia add_book_T2
- Adauga in arbore de tip T2 autorul parametru pe calea corespunzatoare 
numelui sau, deasemenea adauga/completeaza la finalul caii arborele de tip 
T1 cu informatia despre cartea primita parametru folosind functia add_book_T1

## Functia afisare_T1
- Afiseaza numele cartilor din arborele tip T1 primit parametru.
Pentru valoarea 0/1 a variabilei autocomplete primita parametru va afisa 
titlul tuturor cartilor/primelor 3 carti a caror nume coincide/se incepe cu 
numele/prefixul primit parametru.Folosesc o variabila globala nr pentru 
a sti cand am afisat deja 3 carti(pentru autocomplete = 1)

## Functia afisare_T2
- Afiseaza numele primilor 3 autori a caror nume se incepe cu prefixul primit 
parametru. Stringul autor parametru va fi folosit pentru a construi treptat 
numele autorului fara prefix(stringul autor va fi gol, dar alocat inainte 
sa fie dat ca parametru).AM folosit variabila globala nr pentru a afisa doar 
primii 3 autori

## Functia search_book
- Primeste parametru titlu complet a cartii sau un prefix cu caracterul ~ la final
Daca parametrul e un prefix atunci apeleaza functia search_book_auto
Altfel auta cartea dupa titlu in arbore T1 primit parametru si afiseaza informatii 
despre aceasta daca a fost gasita

## Functia search_author
- Cauta in arbore T1 cartea dupa titlul primit parametru si returneaza numele 
autorului daca aceasta este gasita, altfel returneaza NULL;

## Functia list_author
- Primeste parametru nume complet sau prefix al autorului.
Daca parametrul e prefix apeleaza functia list_author_auto
Altfel cauta autorul dupa nume si daca e gasit afiseaza titlul tuturor cartilor
scrise de acesta(folosind functia afisare_T1)

## Functia search_by_author
- Cauta in arbore T2 autorul primit parametru si daca il gaseste cauta in 
arborele T1 aferent autorului cartea primita parametru folosind functia 
search_book afisand informatii despre carte daca e gasita

## Functia search_book_auto
- Primeste parametru prefix al numelui unei carti si parcurge arborele T1 
pina la nodul corespunzator ultimului caracter din prefix dupa care se 
apeleaza functia afisare_T1 cu parametru autocomplete = 1 pentru a afisa doar 
primele 3 titluri gasite(functiei afisare_T1 i se pune parametru subarborele 
aferent nodului la care am ajuns)

## Functia list_author_auto
- Primeste parametru prefix al numelui unui autor, parcurge arborele T2 
pina la nodul corespunzator ultimului caracter din prefix si afiseaza primii 
3 autori a caror nume incepe cu prefixul respectiv folosind functia afisare_T2 
dandui parametru subarborele aferent nodului la care am ajuns

## Functia nodGol_T1
- Verifica daca nodul are vre-un nod copil si returneaza 1 daca are cel putin 
un nod copil, altfel returneaza 0

## Functia nodGol_T2
- Analogic functiei nodGol_T2 dar pentru arbore tip T2

## Functia delete_book_T1
- Cauta recursiv in arbore T1 dupa numele cartii si elimina treptat cheia 
corespunzatoare numelui atita timp cit o litera din cheie nu defineste cale 
spre o alta carte.

## Functia delete_book_T2
- Analogic functiei delete_book_T1, cauta dupa numele autorului si elimina din 
arborele T1 aferent cartea primita parametru dupa care verifica daca arborele cu carti
este gol. Daca nu mai exista carti in acesta atunci elimina autorul similar 
functiei delete_book_T1 si elibereaza arborele T1

---
Drepturile de autor fata de crearea checkerului si conditiei apartin echipei de Structuri de Date 2021 UPB

Implementarea codului: Calmis Liviu