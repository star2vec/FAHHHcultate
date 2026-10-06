--2. 

DESC EMPLOYEES;

-- 3. 

SELECT *
FROM EMPLOYEES;

-- 4.

SELECT employee_id, last_name, job_id, hire_date
from employees;

-- 5. 
SELECT UNIQUE job_id FROM employees;
SELECT DISTINCT job_id from employees;


-- 6. 

SELECT last_name || ', ' || first_name || ', ' || job_id AS "Detalii Angajat"
FROM employees;

-- 7. 
SELECT last_name, salary
FROM employees
WHERE salary > 2850;


-- 8.
SELECT employee_id, department_id
FROM employees
WHERE employee_id = 104;


-- 9.
SELECT last_name, salary
FROM employees
WHERE salary NOT between 14000 AND 24000;

SELECT last_name, salary
FROM employees
WHERE salary between 3000 AND 7000;

SELECT last_name, salary
FROM employees
WHERE salary>=3000 AND salary<=7000;


-- 10. 
SELECT last_name, job_id, hire_date
FROM employees
WHERE hire_date BETWEEN '20-02-1987' AND '01-05-1989'
ORDER BY hire_date ASC;


-- 11. 
SELECT last_name, department_id
FROM employees
WHERE department_id IN (10, 30)
ORDER BY last_name;


-- 12.
SELECT last_name Angajat, salary "Salariu lunar"
FROM employees
WHERE department_id IN (10, 30) AND salary>1500
ORDER BY last_name;


-- 13. 
SELECT SYSDATE
FROM dual;


-- 14.
SELECT last_name, hire_date 
from employees 
where hire_date like ('%87'); 

SELECT last_name, hire_date
from employees
where TO_CHAR(hire_date, 'YYYY') = 1987;


--15. 
SELECT last_name 
from employees
where lower(last_name) like ('__a%');


--16.
SELECT last_name 
from employees
where (lower(last_name) like ('%l%l%') AND manager_id = 30) OR department_id = 30;


--17. 
SELECT last_name, job_id, salary 
from employees
where (lower(job_id) like ('%clerk%') OR lower(job_id) like ('%rep%')) AND salary NOT IN (1000, 2000, 3000);


-- 18. 
SELECT last_name, salary, commission_pct 
from employees
where commission_pct IS NOT NULL
ORDER BY salary desc, 
         
         
-- 19.
SELECT last_name, salary, commission_pct 
from employees
ORDER BY salary desc, 
         commission_pct DESC;
         
         
-- 20.
SELECT last_name || ' ' || first_name "Nume Complet", salary, hire_date 
from employees
where (salary BETWEEN 5000 and 9000) 
AND (lower(first_name) like ('a%') OR lower(first_name) like ('m%'))
AND MOD(TO_CHAR(hire_date, 'YY'), 2) = 1
AND TO_CHAR(hire_date, 'MON') = TO_CHAR(SYSDATE, 'MON')
ORDER BY hire_date DESC;


-- 21. 
SELECT last_name, salary, job_id, TO_CHAR(SYSDATE, 'YYYY') - TO_CHAR(hire_date, 'YYYY') as "Ani lucrati", TO_CHAR(hire_date, 'YYYY') as "Anul angajarii"
FROM employees
WHERE lower(job_id) like ('%clerk%');


-- 22. 
SELECT first_name || last_name AS NumeComplet, salary AS Salariu, 
hire_date, MOD(TO_CHAR(hire_date, 'YYYY'), 2) AS ParitateAnAngajare, TO_CHAR(SYSDATE, 'YYYY') - TO_CHAR(hire_date, 'YYYY') AS AniLucrati
FROM employees
WHERE salary BETWEEN 5000 AND 12000
AND first_name LIKE ('_a%')
AND department_id IN (80, 20, 100)
ORDER BY hire_date DESC;


