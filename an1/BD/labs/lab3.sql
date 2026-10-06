--EXERCITII JOIN


--1. 

SELECT e.job_id, j.job_title
FROM employees e JOIN jobs j on (e.job_id = j.job_id)
WHERE e.department_id = 30;

--2.

SELECT e.last_name, d.department_name, d.location_id
FROM employees e JOIN departments d on (e.department_id = d.department_id)
WHERE e.commission_pct IS NOT NULL;

--3.

--var 1
SELECT e.last_name, j.job_title, d.department_name
FROM employees e, jobs j, departments d, locations l
WHERE e.job_id = j.job_id 
    AND e.department_id = d.department_id 
    AND d.location_id = l.location_id 
    AND upper(l.city) = 'OXFORD';
    
--var 2
SELECT e.last_name, j.job_title, d.department_name
FROM employees e 
JOIN jobs j ON (e.job_id = j.job_id)
JOIN departments d ON (e.department_id = d.department_id)
JOIN locations l ON (d.location_id = l.location_id)
WHERE UPPER(l.city) = 'OXFORD';


--4.

SELECT ang.employee_id "Cod Angajat", ang.last_name "Nume Angajat",
        mgr.employee_id "Cod Manager", mgr.last_name "Nume Manager"
FROM employees ang JOIN employees mgr
    ON (ang.manager_id = mgr.employee_id);
    
    
--5.

SELECT ang.employee_id "Cod Angajat", ang.last_name "Nume Angajat",
        mgr.employee_id "Cod Manager", mgr.last_name "Nume Manager"
FROM employees ang LEFT JOIN employees mgr
    ON (ang.manager_id = mgr.employee_id);
    
    
    
--6.

SELECT ang.last_name "Nume angajat", ang.department_id "Cod departament", coleg.last_name "Nume coleg"
FROM employees ang JOIN employees coleg ON (ang.department_id = coleg.department_id) 
WHERE lower(ang.first_name||ang.last_name) != lower(coleg.first_name||coleg.last_name);


--7. 

--fara join
SELECT last_name, j.job_id, job_title, department_name, salary
FROM employees e, departments d, jobs j
WHERE e.department_id = d.department_id (+)
 AND j.job_id = e.job_id;
 
--cu join
SELECT last_name, j.job_id, job_title, department_name, salary
FROM employees e LEFT JOIN departments d ON (e.department_id = d.department_id)
                 JOIN jobs j ON (e.job_id = j.job_id);


--8.

SELECT e.last_name, e.hire_date
FROM employees e LEFT JOIN employees g ON (e.hire_date > g.hire_date)
WHERE lower(g.last_name) = 'gates';


--9.
Scrieți o cerere pentru a afișa numele salariatului, luna (în litere), anul
angajării și valoarea comisionului pentru toți salariații din același departament
cu Gates (last_name este Gates) – se verifică numele scris cu prima literă mare
și restul literelor mici, al căror nume conţine litera “a”. Se va exclude Gates. Se
vor utiliza aliasuri pentru numele coloanelor din output. În cazul în care un
angajat nu câștigă comision, se va scrie în output, pe coloana respectivă,
mesajul “Nu câștigă comision”. Rezultatul se va ordona alfabetic după numele
salariaților. 

SELECT e.last_name AS "nume", TO_CHAR(e.hire_date, 'MONTH') "luna", 
TO_CHAR(e.hire_date, 'YYYY') "an", NVL(TO_CHAR(e.commission_pct), 'Nu castiga comision') "comision"
FROM employees e JOIN employees g ON (e.department_id = g.department_id)
WHERE lower(g.last_name) = 'gates' 
      AND lower(e.last_name) LIKE ('%a%') AND lower(e.last_name) != 'gates'
ORDER BY e.last_name;

--10.
SELECT e.last_name, e.salary, l.city, l.country_id
FROM employees e JOIN employees king ON (e.manager_id = king.employee_id)
                 LEFT JOIN departments d ON (e.department_id = d.department_id)
                 LEFT JOIN locations l ON (d.location_id = l.location_id)
WHERE lower(king.last_name) = 'king';


--11.
SELECT d.department_id, department_name, job_id, last_name, to_char(salary,'$99,999.00')
FROM employees e JOIN departments d ON (e.department_id = d.department_id)
WHERE lower(department_name) like '%ti%'
ORDER BY department_name ASC, e.last_name ASC;


--12.
---- uhh idk??? VAD CA NU EXISTA RASPUNS SA TE UITI CAND TE MAI UITI PE ASTEA!!!




-- EXERCITII CU MULTIMI!!!!!!

--1.

SELECT department_id "Cod departament"
FROM employees
WHERE UPPER(job_id)='SA_REP'

UNION

SELECT department_id
FROM departments
WHERE LOWER(department_name) LIKE '%re%';


--2.

SELECT department_id "Cod departament"
FROM employees
WHERE UPPER(job_id)='SA_REP'

UNION ALL

SELECT department_id
FROM departments
WHERE LOWER(department_name) LIKE '%re%';


--3.

--var 1
SELECT department_id 
FROM departments
MINUS
SELECT department_id 
FROM employees;

--var 2
SELECT d.department_id
FROM departments d LEFT JOIN employees e ON (d.department_id = e.department_id)
WHERE e.department_id IS NULL;
      




