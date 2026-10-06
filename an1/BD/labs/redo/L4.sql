-- LABORATOR 4 - SAPTAMANA 6 

DROP TABLE dept_est CASCADE CONSTRAINTS;
DROP TABLE emp_est CASCADE CONSTRAINTS;
DROP TABLE emp1_est CASCADE CONSTRAINTS;
DROP TABLE emp2_est CASCADE CONSTRAINTS;
DROP TABLE emp3_est CASCADE CONSTRAINTS;
DROP TABLE emp0_est CASCADE CONSTRAINTS;

1.	Să se creeze tabelele EMP_est, DEPT_est prin copierea structurii şi conţinutului 
tabelelor EMPLOYEES, respectiv DEPARTMENTS. 

-- în care şirul de caractere “est” ->
-- p reprezintă prima literă a prenumelui ->
-- iar nu reprezintă primele două litere ale numelui)


CREATE TABLE EMP_est AS SELECT * FROM employees;
CREATE TABLE DEPT_est AS SELECT * FROM departments;


2.	Listaţi structura tabelelor sursă şi a celor create anterior. Ce se observă?

-- listam structura

desc emp_est;
desc dept_est;


3.	Listaţi conţinutul tabelelor create anterior.

--listam continutul
select * from emp_est;
select * from dept_est;


-- COMENZILE LMD, LDD SI LCD 

LMD - SELECT, INSERT, UPDATE, DELETE, [MERGE] -> nu fac commit
implicit

LDD - CREATE, ALTER, DROP -> fac commit automat/implicit

LCD - ROLLBACK, COMMIT, SAVEPOINT

COMMIT - determină încheierea tranzacţiei curente şi permanentizarea
modificărilor care au intervenit pe parcursul acesteia

ROLLBACK - pentru a renunţa la modificările aflate în aşteptare
- se încheie tranzacţia, se anulează modificările asupra datelor,
- se restaurează starea lor precedentă



Ce se intampla daca executam in acest punct comanda ROLLBACK?
Ce se intampla daca executam comanda COMMIT?

-- EXEMPLE




4.	Pentru introducerea constrângerilor de integritate, 
executaţi instrucţiunile LDD indicate în continuare;

ALTER TABLE emp_est
ADD CONSTRAINT pk_emp_est PRIMARY KEY(employee_id);


ALTER TABLE dept_est
ADD CONSTRAINT pk_dept_est PRIMARY KEY(department_id);


ALTER TABLE emp_est
ADD CONSTRAINT fk_emp_dept_est FOREIGN KEY(department_id) REFERENCES dept_est(department_id);
   
   
Obs: Ce constrângere nu am implementat?

ALTER TABLE emp_est
ADD CONSTRAINT fk_emp_emp_est FOREIGN KEY(manager_id) REFERENCES emp_est(employee_id);

ALTER TABLE dept_est
ADD CONSTRAINT fk_dept_emp_est FOREIGN KEY(manager_id) REFERENCES emp_est(employee_id);


DESC EMP_est;
DESC DEPT_est;



-- APOI SE REZOLVA, IN CADRUL LABORATORULUI CURENT, URMATOARELE EXERCITII


5.	Să se insereze departamentul 300, cu numele Programare în DEPT_est.
Analizaţi cazurile, precizând care este soluţia corectă şi explicând erorile 
celorlalte variante. 
Pentru a anula efectul instrucţiunii(ilor) corecte, utilizaţi comanda ROLLBACK.
       
       
DESC DEPT_est;

SELECT * FROM dept_est;

--discutie tipuri de INSERT si erori posibile
--vezi laborator
                                                      
--a)	
INSERT INTO DEPT_est 
VALUES (300, 'Programare');


--b)	
INSERT INTO DEPT_est (department_id, department_name)
VALUES (300, 'Programare');

SELECT * FROM dept_est;


--c)	
INSERT INTO DEPT_est (department_name, department_id)
VALUES (300, 'Programare');


--d)	
INSERT INTO DEPT_est (department_id, department_name, location_id)
VALUES (300, 'Programare', null);	


-- varianta corecta
	
INSERT INTO dept_est(department_id, department_name, location_id)
VALUES (301, 'Programare', null);


SELECT * FROM dept_est;


--e)	
INSERT INTO DEPT_est (department_name, location_id)
VALUES ('Programare', null);


-- Ce se intampla daca executam rollback?

ROLLBACK;


-- Executati varianta corecta si permanentizati modificarile.

INSERT INTO dept_est(department_id, department_name)
VALUES (300, 'Programare');

COMMIT;


6. Să se insereze un angajat corespunzător departamentului introdus anterior 
în tabelul EMP_est, precizând valoarea NULL pentru coloanele a căror valoare 
nu este cunoscută la inserare (metoda implicită de inserare). 
Determinaţi ca efectele instrucţiunii să devină permanente.
Atenţie la constrângerile NOT NULL asupra coloanelor tabelului!


-- inserare prin metoda IMPLICITA de inserare
-- dorim sa inseram un angajat in depart 300

DESC emp_est;
SELECT * FROM emp_est;


INSERT INTO emp_est
VALUES (250, NULL, 'nume250', 'email250', NULL, SYSDATE, 'IT_PROG', NULL, NULL, NULL, 300);

-- Cum permanentizam efectul actiunii anterioare?

COMMIT;

SELECT * FROM emp_est;


-- De ce varianta urmatoare nu functioneaza?

INSERT INTO emp_est
VALUES (250, NULL, 'nume251', 'email251', NULL, SYSDATE, 'IT_PROG', NULL, NULL, NULL, 300);


-- Se poate anula inserarea anterioara?

ROLLBACK;

SELECT * FROM emp_est;


-- De ce varianta urmatoare nu functioneaza?

INSERT INTO emp_est
VALUES (251, NULL, 'nume251', 'email251', NULL, '03-10-2023', 
       'IT_PROG', NULL, NULL, NULL, 300);
       
SELECT * FROM emp_est;

ROLLBACK;


-- De ce varianta urmatoare nu functioneaza?

INSERT INTO emp_est
VALUES (252, NULL, 'nume252', 'email252', NULL, SYSDATE, 
       'IT_PROG', NULL, NULL, NULL, 310);


-- IN CELE DIN URMA PASTRAM IN BAZA DE DATE ANGAJATUL CU ID-UL 250 IN DEPART. 300



7. Să se mai introducă un angajat corespunzător departamentului 300, 
precizând după numele tabelului lista coloanelor în care se introduc valori 
(metoda explicita de inserare). 
Se presupune că data angajării acestuia este cea curentă (SYSDATE). 
Salvaţi înregistrarea.

desc emp_est;

--inserare prin metoda EXPLICITA de inserare
INSERT INTO emp_est (hire_date, job_id, employee_id, last_name, email, department_id)
VALUES (sysdate, 'sa_man', 278, 'nume_278', 'email_278', 300);

COMMIT;

SELECT * FROM emp_est;


8. Creaţi un nou tabel, numit EMP1_est, care va avea aceeaşi structură ca şi EMPLOYEES, 
dar fara inregistrari. Copiaţi în tabelul EMP1_est salariaţii (din tabelul EMPLOYEES) 
al căror comision depăşeşte 25% din salariu (se accepta omiterea constrangerilor).


-- crearea tabelului
CREATE TABLE emp1_est AS SELECT * FROM employees;

select * from emp1_est;

-- eliminarea inregistrarilor
DELETE FROM emp1_est;

-- adaugarea noilor valori (inserarea randurilor)
INSERT INTO emp1_est
    SELECT *
    FROM employees
    WHERE commission_pct > 0.25;

SELECT * FROM emp1_est;


-- Ce se intampla daca executam un rollback? 

ROLLBACK;


-- SA SE ANALIZEZE EXERCITIILE 9, 10 SI 11 

9. Să se creeze un fişier (script file) care să permită introducerea de înregistrări 
în tabelul EMP_est în mod interactiv. 
Se vor cere utilizatorului: codul, numele, prenumele si salariul angajatului. 
Câmpul email se va completa automat prin concatenarea primei litere din prenume 
şi a primelor 7 litere din nume.    
Executati script-ul pentru a introduce 2 inregistrari in tabel.


INSERT INTO emp_est (employee_id, first_name, last_name, email, hire_date, job_id, salary)
VALUES(&cod, '&&prenume', '&&nume', substr('&prenume',1,1) || substr('&nume',1,7), 
       sysdate, 'it_prog', &sal);
       
UNDEFINE prenume;
UNDEFINE nume;

SELECT * FROM emp_est;


10. Creaţi 2 tabele emp2_est şi emp3_est cu aceeaşi structură ca tabelul EMPLOYEES, 
dar fără înregistrări (acceptăm omiterea constrângerilor de integritate). 
Prin intermediul unei singure comenzi, copiaţi din tabelul EMPLOYEES:

-  în tabelul EMP1_est salariaţii care au salariul mai mic decât 5000;
-  în tabelul EMP2_est salariaţii care au salariul cuprins între 5000 şi 10000;
-  în tabelul EMP3_est salariaţii care au salariul mai mare decât 10000.

Verificaţi rezultatele, apoi ştergeţi toate înregistrările din aceste tabele.

--VEZI INSERARI MULTI-TABEL IN LABORATORUL 4

CREATE TABLE emp1_est AS SELECT * FROM employees;

DELETE FROM emp1_est;

SELECT * FROM emp1_est; 

CREATE TABLE emp2_est AS SELECT * FROM employees;

DELETE FROM emp2_est;

CREATE TABLE emp3_est AS SELECT * FROM employees;

DELETE FROM emp3_est;

INSERT ALL
   WHEN salary < 5000 THEN
      INTO emp1_est					
   WHEN salary > = 5000 AND salary <= 10000 THEN
      INTO emp2_est
   ELSE 
      INTO emp3_est
SELECT * FROM employees;  


SELECT * FROM emp1_est;
SELECT * FROM emp2_est;
SELECT * FROM emp3_est;


11. Să se creeze tabelul EMP0_est cu aceeaşi structură ca tabelul EMPLOYEES 
(fără constrângeri), dar fără inregistrari. 
Copiaţi din tabelul EMPLOYEES:

-  în tabelul EMP0_est salariaţii care lucrează în departamentul 80;
-  în tabelul EMP1_est salariaţii care au salariul mai mic decât 5000;
-  în tabelul EMP2_est salariaţii care au salariul cuprins între 5000 şi 10000;
-  în tabelul EMP3_est salariaţii care au salariul mai mare decât 10000.

Dacă un salariat se încadrează în tabelul emp0_est, atunci acesta nu va mai fi inserat 
şi în alt tabel (tabelul corespunzător salariului său);

CREATE TABLE emp0_est AS SELECT * FROM employees;

DELETE FROM emp0_est;


INSERT FIRST
    WHEN department_id = 80 THEN
        INTO emp0_est
    WHEN salary < 5000 THEN
        INTO emp1_est
    WHEN salary > = 5000 AND salary <= 10000 THEN
        INTO emp2_est
    ELSE 
        INTO emp3_est
SELECT * FROM employees;

SELECT * FROM emp0_est;
SELECT * FROM emp1_est;
SELECT * FROM emp2_est;
SELECT * FROM emp3_est;


-- COMANDA UPDATE - VEZI LABORATOR (pentru notiunile teoretice)

12. Măriţi salariul tuturor angajaţilor din tabelul EMP_est cu 5%. 
Vizualizati, iar apoi anulaţi modificările.

UPDATE emp_est
SET salary = salary * 1.05;

SELECT * FROM emp_est;

ROLLBACK;

13. Schimbaţi jobul tuturor salariaţilor din departamentul 80 care au comision, în 'SA_REP'. 
Anulaţi modificările.

UPDATE emp_est
SET job_id = 'SA_REP'
WHERE department_id = 80 and commission_pct IS NOT NULL;

SELECT * FROM emp_est;

ROLLBACK;


14. Să se promoveze Douglas Grant la manager în departamentul 20 (tabelul dept_est), 
având o creştere de salariu cu 1000$. 


-- verificari

SELECT *
FROM emp_est
WHERE lower(last_name||first_name) = 'grantdouglas';

SELECT * FROM dept_est
WHERE department_id = 20;

-- solutia problemei

UPDATE dept_est
SET manager_id = 199
WHERE department_id = 20;

UPDATE emp_pnu
SET salary = salary + 1000
WHERE lower(last_name||first_name) = 'grantdouglas';


-- COMANDA DELETE - VEZI LABORATOR (pentru notiunile teoretice)

15.	Ştergeţi toate înregistrările din tabelul DEPT_est. 
Ce înregistrări se pot şterge? Anulaţi modificările. 

DELETE FROM dept_est; 

SELECT * FROM dept_est;

SELECT * FROM emp_est;



16.	Suprimaţi departamentele care nu au angajati. Anulaţi modificările.

-- prima data afisam departamentele care nu au angajati

SELECT department_id
from departments

minus

select department_id
from employees;


-- apoi stergem departamentele care nu au angajati

DELETE from dept_est
where department_id in (SELECT department_id
                        from departments
                        where department_id NOT IN (SELECT department_id
                                                    from employees
                                                    where department_id IS NOT NULL
                                                    )
                       );                             

ROLLBACK;

17. Să se mai introducă o linie in tabelul DEPT_est.

desc dept_est;

INSERT INTO dept_est
VALUES(320, 'dept_nou', NULL, NULL);

SELECT * FROM dept_est;


18. Să se marcheze un punct intermediar in procesarea tranzacţiei (SAVEPOINT p).

SAVEPOINT p;


19. Să se şteargă din tabelul DEPT_est departamentele care au codul de departament 
cuprins intre 160 si 200. Listaţi conţinutul tabelului.

DELETE FROM dept_est
WHERE department_id BETWEEN 160 AND 200; 

SELECT * FROM dept_est;


20. Să se renunţe la cea mai recentă operaţie de ştergere, fără a renunţa 
la operaţia precedentă de introducere. 
Determinaţi ca modificările să devină permanente;

SELECT * FROM dept_est;

ROLLBACK TO p;

COMMIT;
