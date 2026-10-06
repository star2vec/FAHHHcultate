--2. 

DESC EMPLOYEES;

--3.

SELECT * FROM DEPARTMENTS;

--4. Să se afişeze codul angajatului, numele, codul job-ului, data angajării. Salvati instructiunea
--SQL într-un fişier numit Laborator1.sql

SELECT employee_id, first_name, last_name, job_id, hire_date FROM EMPLOYEES;

--6.
SELECT last_name || ', ' || first_name || ', ' || job_id "Detalii Angajat"
FROM employees;

--7. 
SELECT last_name, salary FROM employees WHERE salary > 2850;

--8.
SELECT first_name || last_name, department_id FROM employees WHERE employee_id = 104;

--9.
SELECT last_name, salary FROM employees WHERE salary NOT BETWEEN 14000 AND 24000;

--9.1
SELECT last_name, first_name, salary FROM employees WHERE salary BETWEEN 3000 AND 7000;

--9.2
SELECT last_name, first_name, salary FROM employees WHERE salary >= 3000 AND salary <= 7000;


--10.
SELECT last_name, job_id, hire_date
FROM employees
WHERE hire_date BETWEEN '20-FEB-1987' AND '01-MAY-1989'
ORDER BY hire_date ASC;

--11.
SELECT first_name, last_name, department_id
FROM employees WHERE
department_id = 10 OR department_id = 30
ORDER BY lower(first_name||last_name) ASC;

-- alta varianta pentru 11:
SELECT last_name, department_id
FROM employees
WHERE department_id IN (10, 30)
ORDER BY last_name;


--12. 
SELECT last_name "Angajat", salary "Salariu lunar"
FROM employees
WHERE department_id IN (10, 30) AND salary>1500;

--13. 
SELECT SYSDATE
FROM dual;


--14. 

--var 1
SELECT last_name, hire_date
FROM employees
WHERE hire_date LIKE ('%87%');

--var 2
SELECT last_name, hire_date
FROM employees
WHERE TO_CHAR(hire_date, 'YYYY') = 1987;


--15.
SELECT last_name
FROM employees
WHERE last_name LIKE ('__a%');


--16. 
SELECT last_name, department_id, manager_id
FROM employees
WHERE (lower(last_name) LIKE ('%l%l%')) AND (department_id = 30 OR manager_id = 102);


--17.
SELECT last_name, salary, commission_pct
FROM employees
WHERE (JOB_ID like ('%CLERK%') OR JOB_ID like ('%REP%')) AND salary NOT in (1000, 2000, 3000);


--18. 
SELECT last_name, salary, commission_pct 
FROM employees
WHERE commission_pct IS NOT NULL 
ORDER BY salary DESC, commission_pct DESC;

--19. 
SELECT last_name, salary, commission_pct 
FROM employees
ORDER BY salary DESC, commission_pct DESC;

--20. 
SELECT first_name || ' ' || last_name "Nume complet", employee_id, salary, hire_date
FROM employees
WHERE (lower(first_name) LIKE ('a%') OR lower(first_name) LIKE ('m%')) 
        AND (MOD(TO_CHAR(hire_date, 'Y'), 2) = 1) 
        AND (TO_CHAR(hire_date, 'MON') = TO_CHAR(SYSDATE, 'MON'))
ORDER BY hire_date DESC;


--21. 
SELECT last_name, salary, JOB_ID, TO_CHAR(SYSDATE, 'YYYY')-TO_CHAR(hire_date, 'YYYY') "Ani lucrati", TO_CHAR(hire_date, 'YYYY') "Anul angajarii"
FROM employees
WHERE JOB_ID like ('%CLERK%');
--asta chiar are 45 de linii, e ok

--22.
SELECT first_name || last_name AS NumeComplet,
 salary AS Salariu,
 hire_date,
 MOD(TO_CHAR(hire_date, 'Y'), 2) AS ParitateAnAngajare,
 TO_CHAR(hire_date, 'YYYY') - TO_CHAR(SYSDATE, 'YYYY') AS AniLucrati
FROM employees
WHERE salary BETWEEN 5000 AND 12000
AND first_name LIKE('_a%')
AND department_id IN (80, 20, 100)
ORDER BY hire_date DESC;







