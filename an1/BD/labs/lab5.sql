-- LABORATOR 5 - SAPTAMANILE 7 SI 8

-- Limbajul de definire a datelor (LDD) 

--COMENZI CARE FAC PARTE DIN LDD:

CREATE, ALTER, DROP, TRUNCATE, RENAME

--Ce comanda LCD se executa dupa instructiunile de tip LDD?

_____

-- Crearea tabelelor (vezi notiunile in laborator 5)


-- EXERCITII 


1. Să se creeze tabelul ANGAJATI_est 
(est se alcatuieşte din prima literă din prenume şi primele două din numele studentului) 
corespunzător schemei relaţionale:

ANGAJATI_est(cod_ang number(4), nume varchar2(20), prenume varchar2(20), email char(15), 
             data_ang date, job varchar2(10), cod_sef number(4), salariu number(8, 2), 
             cod_dep number(2)
            );
  
a) cu precizarea cheilor primare la nivel de coloană 
si a constrangerilor NOT NULL pentru coloanele nume şi salariu;
De asemenea, se presupune că valoarea implicită a coloanei data_ang este SYSDATE, 
iar adresa de e-mail trebuie sa aiba o valoare unica    

CREATE TABLE angajati_est
      ( cod_ang number(4) pk_ang_est PRIMARY KEY,
        nume varchar2(20) NOT NULL,
        prenume varchar2(20),
        email char(15) UNIQUE,
        data_ang date DEFAULT SYSDATE,
        job varchar2(10),
        cod_sef number(4),
        salariu number(8,2) NOT NULL,
        cod_dep number(2)
       );
 
SELECT * FROM angajati_est;
DESC angajati_est;
    

b) cu precizarea cheii primare la nivel de tabel 
si a constrângerilor NOT NULL pentru coloanele nume şi salariu.

DROP TABLE angajati_est;

CREATE TABLE angajati_est
      ( cod_ang number(4),
        nume varchar2(20) constraint nume_ang not null,
        prenume varchar2(20),
        email char(15) unique,
        data_ang date default sysdate,
        job varchar2(10),
        cod_sef number(4),
        salariu number(8, 2) constraint salariu_ang not null,
        cod_dep number(2),
        constraint pkey_ang primary key(cod_ang) --constrangere la nivel de tabel
       );
 



-- Rezolvati urmatoarele exercitii:


2. Adăugaţi următoarele înregistrări în tabelul ANGAJATI_est:

-- Analizati tabelul din Laborator 5

-- 1
-- metoda explicita (se precizeaza coloanele)
INSERT INTO angajati_est(cod_ang, nume, prenume, data_ang, job, salariu, cod_dep)
VALUES(100, 'nume1', 'prenume1', null, 'Director', 20000, 10);



-- DE CE NU SUNT TRECUTE, IN COMANDA INSERT INTO, TOATE COLOANELE DIN TABELUL ANGAJATI
-- (VEZI TABELUL DIN LABORATOR 5, EXERCITIUL 2)


DESC angajati_est;
SELECT * FROM angajati_est;



-- DE CE A FOST PRECIZATA COLOANA data_ang si nu a fost precizata coloana cod_sef?
--IN CADRUL METODEI EXPLICITE DE INSERARE
-- SE TREC, OBLIGATORIU, IN CLAUZA INSERT INTO
--COLOANELE CARE NU POT FI NULL
--COLOANELE CARE NU SUNT TRECUTE IN INSERT INTO
-- VOR FI COMPLETATE AUTOMAT CU NULL

-- 2           
-- metoda implicita de inserare (nu se precizeaza coloanele)
INSERT INTO angajati_est
VALUES(101, 'nume2', 'prenume2', 'nume2', TO_DATE('02-02-2004','dd-mm-yyyy'), 
       'Inginer', 100, 10000, 10);
   

-- 3          
INSERT INTO angajati_est
VALUES(102, 'nume3', 'prenume3', 'nume3', TO_DATE('05-06-2000','dd-mm-yyyy'), 
       'Analist', 101, 5000, 20);


-- 4             
INSERT INTO angajati_est(cod_ang, nume, prenume, data_ang, job, cod_sef, salariu, cod_dep)
VALUES(103, 'nume4', 'prenume4', null, 'Inginer', 100, 9000, 20);


-- 5       
INSERT INTO angajati_est
VALUES(104, 'nume5', 'prenume5', 'nume5', null, 'Analist', 101, 3000, 30);



-- CE COMANDA SE EXECUTA, OBLIGATORIU, DUPA CE SE INSEREAZA DATE?

COMMIT;



SELECT * FROM angajati_est;



2. Modificarea (structurii) tabelelor (vezi notiunile din laborator - pagina 3)

ALTER TABLE NUME_TABEL
ADD -> COLUMN | CONSTRAINT
MODIFY -> COLUMN | CONSTRAINT
DROP -> COLUMN | CONSTRAINT


-- EXERCITII


3. Introduceti coloana comision in tabelul ANGAJATI. 
Coloana va avea tipul de date NUMBER(4,2).

DESC angajati_est;

ALTER TABLE angajati_est
ADD comision number(4,2);

SELECT * FROM angajati_est;


4. Este posibilă modificarea tipului coloanei salariu în NUMBER(6,2) – 6 cifre si 2 zecimale?

SELECT * FROM angajati_est;
DESC angajati_est;

ALTER TABLE angajati_est
MODIFY (salariu number(6,2));


5. Setaţi o valoare DEFAULT pentru coloana salariu.

SELECT * FROM angajati_est;
DESC angajati_est;

ALTER TABLE angajati_est
MODIFY (salariu number(8,2) default 100); 
                 -- atentie la tipul de date si dimensiunea coloanei


6. Modificaţi tipul coloanei comision în NUMBER(2, 2) 
şi al coloanei salariu la NUMBER(10,2), în cadrul aceleiaşi instrucţiuni.

DESC angajati_est;

SELECT * FROM angajati_est;

ALTER TABLE angajati_est
MODIFY (comision number(2,2),
        salariu number(10,2)
        );


7. Actualizati valoarea coloanei comision, setând-o la valoarea 0.1 
pentru salariaţii al căror job începe cu litera A. (UPDATE)

UPDATE angajati_est
SET comision = 0.1
WHERE upper(job) LIKE 'A%';


SELECT * FROM angajati_est;

-- Comanda anterioara executa commit implicit?
R: _NUH UH

COMMIT;


8. Modificaţi tipul de date al coloanei email în VARCHAR2.

DESC angajati_est;

ALTER TABLE angajati_est
MODIFY (email varchar2(15)); -- cititi observatiile din Laborator 5 - pagina 3


9. Adăugaţi coloana nr_telefon în tabelul ANGAJATI_est, setându-i o valoare implicită.

ALTER TABLE angajati_est
ADD (nr_telefon varchar2(10) default '0723111111');

SELECT * FROM angajati_est;


10. Vizualizaţi înregistrările existente. Suprimaţi coloana nr_telefon.

SELECT * FROM angajati_est;

ALTER TABLE angajati_est
DROP column nr_telefon;

ROLLBACK; -- ce efect are rollback?

R: nu are efect



11. Creaţi şi tabelul DEPARTAMENTE_est, corespunzător schemei relaţionale:

DEPARTAMENTE_est (cod_dep# number(2), nume varchar2(15), cod_director number(4))

specificând doar constrângerea NOT NULL pentru nume 
(nu precizaţi deocamdată constrângerea de cheie primară);


CREATE TABLE departamente_est
    (cod_dep number(2),
     nume varchar2(15) constraint nume_dep not null,
     cod_director number(4)
    );
    

DESC departamente_est;

SELECT * FROM departamente_est;


12. Introduceţi următoarele înregistrări în tabelul DEPARTAMENTE

INSERT INTO departamente_est
VALUES (10, 'Administrativ', 100);

INSERT INTO departamente_est
VALUES (20, 'Proiectare', 101);

INSERT INTO departamente_est
VALUES (30, 'Programare', null);


13. Se va preciza apoi cheia primara cod_dep, fără suprimarea şi recrearea tabelului 
(comanda ALTER);

ALTER TABLE departamente_est
ADD CONSTRAINT pkey_dep PRIMARY KEY(cod_dep);

DESC departamente_est;

-- In acest punct mai este nevoie de comanda commit 
-- pentru salvarea celor 3 inserari anterioare?

R: nuh uh


SELECT * FROM departamente_est;
SELECT * FROM angajati_est;

DESC departamente_est;
DESC angajati_est;


14. Să se precizeze constrângerea de cheie externă pentru coloana cod_dep din ANGAJATI_est:

a) fără suprimarea tabelului (ALTER TABLE);

ALTER TABLE angajati_est
ADD CONSTRAINT fk_ang_dep_est FOREIGN KEY (cod_dep) REFERENCES departamente_est(cod_dep);


b) prin suprimarea şi recrearea tabelului, cu precizarea noii constrângeri la nivel de coloană 
({DROP, CREATE} TABLE). 

De asemenea, se vor mai preciza constrângerile (la nivel de coloană, dacă este posibil):
- PRIMARY KEY pentru cod_ang;
- FOREIGN KEY pentru cod_sef;
- UNIQUE pentru combinaţia nume + prenume;
- UNIQUE pentru email;
- NOT NULL pentru nume;
- verificarea cod_dep >0;
- verificarea ca salariul sa fie mai mare decat comisionul*100.

DROP TABLE angajati_est;

CREATE TABLE angajati_est
    (cod_ang number(4) constraint pkey_ang primary key,
     nume varchar2(20) constraint nume_ang not null,
     prenume varchar2(20),
     email char(15) UNIQUE,
     data_ang date default sysdate,
     job varchar2(10),
     cod_sef number(4) constraint sef_ang references angajati_est(cod_ang), -- cheie externa
     salariu number(8, 2) constraint salariu_ang not null,
     cod_dep number(2) constraint fk_ang_dep_est references departamente_est(cod_dep),
                       constraint ck_cod_dep_est check (cod_dep > 0),
     comision number(2,2),
     
     constraint uq_nume_prenume_est unique(nume, prenume),        
     constraint ck_salariu_comision_est check(salariu > 100 * comision)
     );
     

15. Suprimaţi şi recreaţi tabelul, specificând toate constrângerile la nivel de tabel (în măsura în care este posibil).


CREATE TABLE ANGAJATI_est
    (cod_ang number(4),
    nume varchar2(20) constraint nume_est not null,
    prenume varchar2(20),
    email char(15),
    data_ang date default sysdate,
    job varchar2(10),
    cod_sef number(4),
    salariu number(8, 2) constraint salariu_est not null,
    cod_dep number(2),
    comision number(2,2),
    constraint nume_prenume_unique_est unique(nume,prenume),
    constraint verifica_sal_est check(salariu > 100*comision),
    constraint pk_angajati_est primary key(cod_ang),
    constraint email_unic unique(email),
    constraint sef_est foreign key(cod_sef) references angajati_est(cod_ang),
    constraint fk_dep_est foreign key(cod_dep) references departamente_est (cod_dep),
    constraint cod_dep_poz check(cod_dep > 0)
    );


16. Reintroduceţi date în tabel, utilizând (şi modificând, dacă este necesar) comenzile salvate anterior.

INSERT INTO angajati_est
VALUES(100, 'nume1', 'prenume1', 'email1', sysdate, 'Director', null, 20000, 10, 0.1);

INSERT INTO angajati_est
VALUES(101, 'nume2', 'prenume2', 'email2', to_date('02-02-2004','dd-mm-yyyy'), 'Inginer', 100, 10000, 10, 0.2);

INSERT INTO angajati_est
VALUES(102, 'nume3', 'prenume3', 'email3', to_date('05-06-2000','dd-mm-yyyy'), 'Analist', 101, 5000, 20, 0.1);

INSERT INTO angajati_est
VALUES(103, 'nume4', 'prenume4', 'email4', sysdate, 'Inginer', 100, 9000, 20, 0.1);

INSERT INTO angajati_est
VALUES(104, 'nume5', 'prenume5', 'email5', sysdate, 'Analist', 101, 3000, 30, 0.1);


-- Ce comanda trebuie executata?

COMMIT;



19. Introduceţi constrângerea NOT NULL asupra coloanei email.

desc angajati_est;

ALTER TABLE angajati_est
MODIFY(email not null);


20. (Incercaţi să) adăugaţi o nouă înregistrare în tabelul ANGAJATI_est, 
care să corespundă codului de departament 50. Se poate?

INSERT INTO angajati_est
VALUES(105, 'nume6', 'prenume6', 'email6', sysdate, 'Analist', 101, 3000, 50, 0.1);

-- De ce nu se poate insera?

R: ____



SELECT * FROM angajati_est;



21. Adăugaţi un nou departament, cu numele Analiza, codul 60 şi 
directorul null în DEPARTAMENTE_est. Salvati inregistrarea. 

INSERT INTO departamente_est
VALUES (60, 'Analiza', null);

SELECT * FROM departamente_est;

COMMIT;



22. (Incercaţi să) ştergeţi departamentul 20 din tabelul DEPARTAMENTE. Comentaţi.

DELETE FROM departamente_est
WHERE cod_dep = 20;

-- De ce nu se poate sterge?

R: exista angajati in dep 20



23. Ştergeţi departamentul 60 din DEPARTAMENTE. ROLLBACK;

DELETE FROM departamente_est
WHERE cod_dep = 60;  

-- De ce putem sterge departamentul 60?
R: _____


SELECT * FROM departamente;

ROLLBACK;



24. Se doreşte ştergerea automată a angajaţilor dintr-un departament, odată cu 
suprimarea departamentului. Pentru aceasta, este necesară introducerea clauzei 
ON DELETE CASCADE în definirea constrângerii de cheie externă. 

Suprimaţi constrângerea de cheie externă asupra tabelului ANGAJATI_est 
şi reintroduceţi această constrângere, specificând clauza ON DELETE CASCADE.


SELECT * 
FROM USER_CONSTRAINTS
WHERE TABLE_NAME = 'ANGAJATI_est'; -- dorim sa aflam numele constrangerii


-- stergem constrangerea 

ALTER TABLE angajati_est
DROP CONSTRAINT FK_DEP_est;


--adaugam constrangerea utilizand clauza ON DELETE CASCADE

ALTER TABLE angajati_est
ADD CONSTRAINT FK_DEP_est FOREIGN KEY(cod_dep)
REFERENCES departamente_est(cod_dep) ON DELETE CASCADE;



25. Ştergeţi departamentul 20 din DEPARTAMENTE. Ce se întâmplă? Rollback;

-- Inainte de stergere analizati datele, atat din angajati, cat si din departamente

DELETE FROM departamente_est
Where cod_dep = 20;

SELECT * FROM angajati_est; 

-- Cati angajati lucreaza in departamentul 20?

R: _____


-- Ce este cod_dep in angajati_est?

R: ____


SELECT * FROM departamente_est;


-- Ce este cod_dep in departamente_est?

R: ____



-- Stergeti departamentul din departamente_est si analizati din nou datele din BD

DELETE FROM departamente_est
WHERE cod_dep = 20; 


SELECT * FROM departamente_est;


SELECT * FROM angajati_est; 


-- Ce se intampla daca executam ROLLBACK?

R: ____


ROLLBACK;


26. Introduceţi constrângerea de cheie externă asupra coloanei cod_director 
a tabelului DEPARTAMENTE. 
Se doreşte ca ştergerea unui angajat care este director de departament să atragă după sine 
setarea automată a valorii coloanei cod_director la null.

DESC departamente_est;

____ 



27. Actualizaţi tabelul DEPARTAMENTE, astfel încât angajatul având codul 102 
să devină directorul departamentului 30. 

Ştergeţi angajatul având codul 102 din tabelul ANGAJATI_est. 
Analizaţi efectele comenzii. Rollback;


UPDATE departamente_est
SET cod_director = 102
WHERE cod_dep = 30;


SELECT * FROM departamente_est;

SELECT * FROM angajati_est;

DELETE FROM angajati_est
WHERE cod_ang = 102; 
      -- avand constrangerea on delete set null pe cheia externa cod_director din departamente
      -- observam ca stergerea angajatului 102 din angajati, 
      -- care era sef de departament in tabelul departamente
      -- a dus la setarea valorii cod_director din tabelul departamente la null



-- Cititi notiunile din Laborator 5 - paginile 4 si 5
-- Studiati exercitiile rezolvate in laborator - exercitiile 28 si 29
