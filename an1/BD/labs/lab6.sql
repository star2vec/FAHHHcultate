-- LABORATOR 6 - SAPTAMANA 9 - Subcereri Necorelate


1. Folosind subcereri, să se afişeze numele şi data angajării pentru salariaţii 
care au fost angajaţi după Gates.

SELECT last_name, hire_date
FROM employees
WHERE hire_date > (SELECT hire_date
                   FROM employees
                   WHERE INITCAP(last_name)= 'Gates'
                   );


2. Folosind subcereri, scrieţi o cerere pentru a afişa numele şi salariul 
pentru toţi colegii (din acelaşi departament) lui Gates. Se va exclude Gates. 


SELECT last_name, salary
FROM employees
WHERE lower(last_name)!='gates'
      AND department_id = (SELECT department_id 
                            FROM employees 
                            WHERE INITCAP(last_name)= 'Gates');
                            


3. Scrieți o cerere pentru a afişa numele, codul departamentului și salariul angajaților 
al căror cod de departament și salariu coincid cu codul departamentului și salariul 
unui angajat care câștigă comision. 

SELECT last_name, department_id, salary
FROM employees
WHERE (department_id, salary) IN (SELECT department_id, salary
               FROM employees
               WHERE commission_pct IS NOT NULL
               );
           

                                                                       
4. Să se afișeze codul, numele și salariul tuturor angajaților al căror salariu 
este mai mare decât salariul mediu din companie.

SELECT employee_id, last_name, salary 
FROM employees 
WHERE salary > (SELECT AVG(salary) 
                FROM employees);




5. Scrieti o cerere pentru a afișa angajații care câștigă 
(castiga = salariul plus comision din salariu) 
mai mult decât oricare funcționar (job-ul functionarilor  conţine şirul "CLERK"). 
Sortați rezultatele dupa salariu, în ordine descrescătoare;

SELECT employee_id, last_name, salary, job_id
FROM employees
WHERE salary * (1+NVL(commission_pct, 0)) > (SELECT MAX(salary * (1+NVL(commission_pct, 0)))
                                            FROM employees
                                            WHERE UPPER(job_id) LIKE '%CLERK%')
ORDER BY salary DESC;


6. Scrieţi o cerere pentru a afişa numele angajatilor, numele departamentului 
şi salariul angajaţilor care câştigă comision, dar al căror şef direct nu câştigă comision.	

-- REZOLVATI IN ECHIPA DE 2 PERSOANE

-- CEREREA TREBUIE SA RETURNEZE 5 ANGAJATI
-- VEZI IMAGINEA ATASATA IN LABORATOR

SELECT e.last_name, d.department_name, salary
FROM employees e JOIN departments d on (e.department_id = d.department_id)
WHERE e.commission_pct IS NOT NULL
      AND e.manager_id IN (SELECT employee_id
                          FROM employees
                          WHERE commission_pct IS NULL
                          );


7. Să se afișeze numele și salariul angajaților care lucrează în departamente aflate în
locații din CANADA și care ocupă joburi ce aparțin unei liste de job_id-uri ce conțin cuvântul man. 
Se vor afișa – numele, prenumele, salariul și id-ul jobului. 

--Prima variantă – o să utilizeze doar subcereri nesincronizate
SELECT last_name, first_name, salary, job_id
FROM employees
WHERE  lower(job_id) LIKE '%man%' 
        AND department_id IN (SELECT department_id
                              FROM departments
                              WHERE location_id IN (SELECT location_id 
                                                    FROM locations
                                                    WHERE country_id = 'CA')
                              );

--A doua variantă – o să utilizeze doar operații JOIN
SELECT last_name, first_name, salary, e.job_id
FROM employees e LEFT JOIN departments d ON (e.department_id = d.department_id)
                 JOIN locations l ON (l.location_id = d.location_id)
WHERE lower(e.job_id) LIKE '%man%'
      AND upper(l.country_id) = 'CA';


8. Să se obțină codurile departamentelor în care nu lucreaza nimeni 
(nu este introdus nici un salariat în tabelul employees). Sa se utilizeze subcereri;

SELECT department_id 
FROM departments
WHERE department_id NOT IN (SELECT department_id
                            FROM employees 
                            WHERE department_id IS NOT NULL);


9. Sa se creeze tabelul SUBALTERNI care sa contina codul, numele si prenumele angajatilor 
care il au manager pe Steven King, alaturi de codul si numele lui King.
Coloanele se vor numi cod, nume, prenume, cod_manager, nume_manager.

DESC employees;

CREATE TABLE SUBALTERNI
    (
    cod NUMBER(6),
    nume VARCHAR2(25),
    prenume VARCHAR2(20),
    cod_manager NUMBER(6),
    nume_manager VARCHAR2(25)
    );
     

INSERT INTO SUBALTERNI (cod, nume, prenume, cod_manager, nume_manager)
        SELECT e.employee_id, e.last_name, e.first_name, m.employee_id, m.last_name
         FROM employees e 
         JOIN employees m ON (e.manager_id = m.employee_id)
         WHERE m.first_name = 'Steven' AND m.last_name = 'King';