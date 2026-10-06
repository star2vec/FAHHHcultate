
----- TEORIE: EXERCITII SUB



-- LABORATOR 3
-- RECAPITULARE JOIN

-- Join-ul este operaţia de regăsire a datelor din două sau mai multe tabele, 
-- pe baza valorilor comune ale unor coloane. De obicei, aceste coloane reprezintă 
-- cheia primară, respectiv cheia externă a tabelelor. 
-- Reamintim că pentru a realiza un join între n tabele
-- o sa fie nevoie de cel puţin n – 1 condiţii de join


--TIPURI DE JOIN:

-- NONEQUIJOIN – condiţia de join conţine alţi operatori decât operatorul de egalitate
--Exemplu Nonequijoin:

SELECT last_name, salary, grade_level, lowest_sal, highest_sal
FROM employees, job_grades
WHERE salary BETWEEN lowest_sal AND highest_sal;

SELECT * FROM job_grades;


-- INNER JOIN (equijoin, join simplu) 
-- corespunde situaţiei în care valorile de pe coloanele ce apar în condiţia 
-- de join trebuie să fie egale

--EXEMPLE (folosind atat join-ul in WHERE cat si cel din standardul SQL3):

-- VARIANTA 1 - Condiția de Join este scrisă în clauza WHERE a instrucțiunii SELECT 

-- Să se afişeze codul si numele angajaților, dar si numele si codul departamentelor 
-- pentru toţi angajaţii care lucrează în departamente.

SELECT employee_id, last_name, department_name, e.department_id
FROM employees e, departments d 
WHERE e.department_id = d.department_id;

-- VARIANTA 2 - --JOIN SCRIS IN FROM (standardul SQL3) - folosind ON
SELECT employee_id, last_name, department_name, e.department_id
FROM employees e join departments d on (e.department_id = d.department_id);
     

-- JOIN SCRIS IN FROM (standardul SQL3) - folosind USING
-- USING SE UTILIZEAZA dacă există coloane având acelasi nume
-- in acest caz coloanele referite nu trebuie sa contina calificatori 
-- adica sa nu fie precedate de nume de tabele sau alias-uri

SELECT employee_id, last_name, department_name, department_id
FROM employees JOIN departments USING(department_id);

-- Cele doua variante (join in where si join in from) sunt echivalente.


-- OUTER JOIN

-- Să se afişeze codul angajaților, numele acestora, numele departamentului si codul departamentului 
-- pentru toţi angajaţii. 
-- Să se afișeze toti angajatii, chiar dacă au sau nu departament (se vor afișa atât angajatii care 
-- lucrează intr-un departament, cât și angajatii care nu au departament).

-- pentru a afisa si angajatii care nu au departament se utilizeaza 
-- simbolul (+) in partea deficitara de informatie

-- deficit de informatie -> angajati FARA departament 

SELECT employee_id, last_name, d.department_id, department_name
FROM employees e, departments d
WHERE e.department_id = d.department_id (+);


-- Să se afişeze codul angajaților, numele acestora, numele departamentului si codul departamentului 
-- pentru toţi angajaţii. 
-- Să se afișeze toate departamentele, chiar dacă au sau nu angajați (se vor afișa atât departamentele în care 
-- lucrează angajați, cât și departamentele care nu au angajați).

-- deficit de informatie -> departamente FARA angajati 

SELECT employee_id, last_name, d.department_id, department_name
FROM employees e, departments d
WHERE e.department_id (+) = d.department_id;


-- In cazul standardului SQL3 se utilizeaza LEFT, RIGHT şi FULL OUTER JOIN
-- DISCUTIE!


-- CROSS JOIN - produs cartezian
SELECT employee_id, last_name, e.department_id, department_name
FROM employees e CROSS JOIN departments d;


-- NATURAL JOIN 
SELECT last_name, job_id, job_title                       
FROM employees NATURAL JOIN jobs;   

SELECT last_name, e.job_id, job_title 
FROM employees e, jobs j 
WHERE e.job_id = j.job_id;


-- 1.
SELECT j.job_id, job_title
FROM jobs j join employees e on (e.job_id = j.job_id)
            join departments d on (e.department_id = d.department_id)
WHERE d.department_id = 30;


-- 2. 
SELECT last_name, department_name, location_id
FROM employees e, departments d
WHERE e.department_id = d.department_id AND commission_pct IS NOT NULL;


--3. 
SELECT last_name, job_title, department_name
FROM employees e join departments d on (e.department_id = d.department_id)
                 join locations l on (d.location_id = l.location_id)
                 join jobs j on (e.job_id = j.job_id)
WHERE lower(city) = 'oxford';       


-- 4. 
SELECT ang.employee_id "Cod Angajat", ang.last_name "Nume Angajat",
 mgr.employee_id "Cod Manager", mgr.last_name "Nume Manager"
FROM employees ang JOIN employees mgr
 ON (ang.manager_id = mgr.employee_id);


-- 5.
SELECT ang.employee_id "Cod Angajat", ang.last_name "Nume Angajat",
 mgr.employee_id "Cod Manager", mgr.last_name "Nume Manager"
FROM employees ang left JOIN employees mgr
 ON (ang.manager_id = mgr.employee_id);
 
 
-- 6.
SELECT e2.last_name Angajat, e1.department_id Departament, e1.last_name Coleg
FROM employees e1 join employees e2 on (e1.department_id = e2.department_id)
WHERE e1.employee_id != e2.employee_id;


-- 7.
SELECT last_name, j.job_id, job_title, department_name, salary
FROM employees e join jobs j on (e.job_id = j.job_id)
                 left join departments d on (e.department_id = d.department_id);


-- 8.
SELECT e1.last_name, e1.hire_date 
FROM employees e1 join employees e2 on (e1.hire_date > e2.hire_date)
AND lower(e2.last_name) = 'gates';


-- 9. 
SELECT e1.last_name as "Nume angajat", TO_CHAR(e1.hire_date, 'MONTH') || ' ' ||  TO_CHAR(e1.hire_date, 'MONTH') as "Luna si an",
e1.department_id as "Departament Angajat", Initcap(e2.last_name) As "Nume gates", e2.department_id as "Departament Gates", 
NVL(TO_CHAR(e1.commission_pct), 'Nu castiga comision')
FROM employees e1 join employees e2 on (e1.department_id = e2.department_id)
WhERE Initcap(e2.last_name) = 'Gates'
AND (initcap(e1.last_name) like ('%a%') OR initcap(e1.last_name) like ('A%'))
AND lower(e1.last_name) != 'gates'
ORDER BY e1.last_name ASC;


-- 10. 
SELECT e1.last_name, e1.salary, job_title, city, country_name
from employees e1 join employees e2 on (e1.manager_id = e2.employee_id)
                  join jobs j on (e1.job_id = j.job_id) 
                  join departments d on (e1.department_id = d.department_id)
                  join locations l on (d.location_id = l.location_id)
                  join countries c on (l.country_id = c.country_id)
WHERE e2.last_name = 'King';


-- 11.
SELECT d.department_id, department_name, job_id, last_name,
to_char(salary,'$99,999.00')
FROM employees e JOIN departments d ON (e.department_id =
d.department_id)
WHERE lower(department_name) like '%ti%'
ORDER BY department_name ASC,
         last_name ASC;



----- operatori pe multimi


-- 1. 
SELECT department_id
from departments
WHERE lower(department_name) like ('%re%')

UNION 

SELECT department_id
FROM employees
WHERE job_id = 'SA_REP' 
AND department_id IS NOT NULL;


--2.
SELECT department_id
from departments
WHERE lower(department_name) like ('%re%')

UNION ALL

SELECT department_id
FROM employees
WHERE job_id = 'SA_REP' 
AND department_id IS NOT NULL;


--3. 

--var 1
SELECT department_id
from departments

MINUS

SELECT department_id
FROM employees;

-- var 2
SELECT d.department_id
from departments d left join employees e on (d.department_id = e.department_id)
WHERE e.department_id IS NULL;


-- 4.
SELECT department_id "Cod departament"
FROM employees
WHERE UPPER(job_id)='HR_REP'
INTERSECT
SELECT department_id
FROM departments
WHERE LOWER(department_name) LIKE '%re%'; 

