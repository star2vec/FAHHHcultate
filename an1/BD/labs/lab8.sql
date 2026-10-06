-- LABORATOR 8 - SAPTAMANA 11

1. Scrieţi o cerere pentru a afişa job-ul, salariul total pentru job-ul respectiv 
pe departamente si salariul total pentru job-ul respectiv pe departamentele 30, 50, 80. 
Se vor eticheta coloanele corespunzător. Rezultatul va apărea sub forma de mai jos:

Job	   Dep30   Dep50   Dep80	Total
---------------------------------------

--forma generala;
-- DECODE(value, if1, then1, if2, then2, … , ifN, thenN, else);

-- METODA 1
SELECT job_id, SUM(DECODE(department_id, 30, salary)) Dep30,
               SUM(DECODE(department_id, 50, salary)) Dep50,
               SUM(DECODE(department_id, 80, salary)) Dep80,
               SUM(salary) Total
FROM employees
GROUP BY job_id;


-- METODA 2: (cu subcereri corelate în clauza SELECT)
SELECT job_id, (SELECT SUM(salary)
                FROM employees
                WHERE department_id = 30
                AND job_id = e.job_id
               ) Dep30,
               
               (SELECT SUM(salary)
                FROM employees
                WHERE department_id = 50
                AND job_id = e.job_id
               ) Dep50,
                
               (SELECT SUM(salary)
                FROM employees
                WHERE department_id = 80
                AND job_id = e.job_id
               ) Dep80,
               
              SUM(salary) Total
              
FROM employees e
GROUP BY job_id;


2.	Să se afişeze codul, numele departamentului şi suma salariilor pe departamente.

-- Varianta fara subcerere
SELECT d.department_id, department_name, sum(salary)
FROM departments d join employees e ON (d.department_id = e.department_id)
GROUP BY d.department_id, department_name
ORDER BY d.department_id;


-- Varianta cu subcerere in from
SELECT d.department_id, department_name, a.suma
FROM departments d, (SELECT department_id ,SUM(salary) suma 
                     FROM employees
                     GROUP BY department_id
                     ) a
WHERE d.department_id = a.department_id; 
 

3. a) Să se afişeze numele, salariul, codul departamentului si salariul mediu 
din departamentul respectiv.

-- Varianta fara subcerere -> discutati rezultatul
select last_name, salary, department_id, avg(salary)
from employees join departments using(department_id)
group by department_id,salary,last_name;




b) Să se afişeze informaţii (numele, salariul si codul departamentului) 
despre angajaţii al căror salariu depăşeşte valoarea medie a salariilor 
tuturor colegilor din companie.

select last_name, salary, department_id
from employees 
WHERE salary > (SELECT AVG(salary)
                FROM employees);


c) Să se afişeze informaţii (numele, salariul si codul departamentului) 
despre angajaţii al căror salariu depăşeşte valoarea medie a salariilor 
colegilor săi de departament.

select last_name, salary, department_id
from employees emp
WHERE salary > (SELECT AVG(salary)
                FROM employees e
                where e.department_id = emp.department_id);



d) Analog cu cererea precedentă, afişându-se şi numele departamentului 
şi media salariilor acestuia şi numărul de angajaţi.

-- De ce varianta aceasta este gresita?
-- Argumentati

select last_name, salary, e.department_id, department_name, 
       round(avg(salary)), count(employee_id)
from employees e join departments d on (e.department_id = d.department_id)
group by last_name, salary, e.department_id, department_name;  


--Soluţia 1 (subcerere necorelată în clauza FROM)

select last_name, salary, e.department_id, salmediu "salariu mediu", nrang "nr de ang"
from employees e join departments d on (e.department_id = d.department_id)
                 join (select avg(salary) as salmediu, count(employee_id) nrang, department_id
                 FROM employees
                 group by department_id
                 )ac
                 on (ac.department_id = e.department_id)
                 
WHERE salary > salmediu;


--Soluţia 2 (subcerere corelată în clauza SELECT)

SELECT last_name, salary, e.department_id, department_name, 
        (select avg(salary)
         from employees
         where department_id = e.department_id
         ) "sal mediu", 
        (select count(employee_id)
        from employees
        where department_id = e.department_id
        ) "nr ang"
from employees e join departments d on (e.department_id = d.department_id) 
WHERE salary > (SELECT AVG(salary)
                FROM employees
                WHERE department_id = e.department_id
                );
                

4.	Să se afişeze numele şi salariul angajaţilor al căror salariu 
este mai mare decât salariile medii din toate departamentele. 
Se cer 2 variante de rezolvare: cu operatorul ALL sau cu funcţia MAX.

-- Varianta cu ALL
SELECT last_name, salary 
FROM employees 
WHERE salary > all (select round(avg(salary))
                    from employees 
                    group by department_id
                    ); -- subcererea calculeaza salariul mediu pentru fiecare departament


-- Varianta cu functia MAX
SELECT last_name, salary 
FROM employees 
WHERE salary > (select ROUND(max(avg(salary)))
                from employees 
                group by department_id
                );


5.	Sa se afiseze numele si salariul celor mai prost platiti angajati 
din fiecare departament.

-- Soluţia 1 (cu sincronizare):
SELECT last_name, salary, department_id
FROM employees e
WHERE salary = (select min(salary)
                from employees
                where department_id = e.department_id 
                );


-- Soluţia 2 (fără sincronizare):
SELECT last_name, salary, department_id  
FROM employees
WHERE (salary, department_id) IN (SELECT min(salary), department_id 
                 FROM employees 
                 GROUP BY department_id
                 );


-- Soluţia 3: Subcerere în clauza FROM 
               
SELECT last_name, salary, department_id  
FROM employees emp join (SELECT min(salary) minsal, department_id dept
                        FROM employees
                        group by department_id) ON (emp.department_id = dept and salary = minsal);


6.	Sa se obtina numele si salariul salariatilor care lucreaza intr-un departament 
in care exista cel putin 1 angajat cu salariul egal cu 
salariul maxim din departamentul 30.


-- METODA 1 - IN

SELECT last_name, salary
FROM employees
WHERE department_id IN (SELECT department_id
                        FROM employees
                        WHERE salary = (SELECT MAX(salary)
                                        FROM employees
                                        WHERE department_id = 30)
                        );


-- METODA 2 - EXISTS

select last_name, salary
FROM employees emp
WHERE EXISTS (select 1 
              from employees 
              where emp.department_id = department_id
              AND salary in (SELECT MAX(salary)
                                        FROM employees
                                        WHERE department_id = 30)
              );



7. a) Să se afişeze codul, numele şi prenumele angajaţilor 
care au cel puţin doi subalterni. 

select employee_id, last_name, first_name
from employees emp
WHERE employee_id IN (select manager_id
                      from employees
                      group by manager_id
                      having count(employee_id) >= 2);


b) Cati subalterni are fiecare angajat? Se vor afisa codul, numele, 
prenumele si numarul de subalterni. Daca un angajat nu are subalterni, 
o sa se afiseze 0 (zero). 


select employee_id, last_name, first_name, (SELECT count(employee_id)
                                            FROM employees
                                            WHERE manager_id = emp.employee_id) as "nr subalterni"
from employees emp;


8.	Să se determine locaţiile în care se află cel puţin un departament.

-- IN (care este echivalent cu  = ANY )         
select location_id
from locations loc
where location_id IN (select location_id
                      from departments
                      where location_id = loc.location_id
                      );  

-- EXIST
select location_id
from locations loc
where EXISTS(select department_id
             from departments
             where location_id = loc.location_id
             );


9.	Să se determine departamentele în care nu există niciun angajat.

-- REZOLVATI
-- CEREREA TREBUIE SA RETURNEZE 16 DEPARTAMENTE
-- VEZI IMAGINEAZA ATASATA IN LABORATOR

-- METODA 1 - UTILIZAND NOT IN 

select department_id
from departments
where department_id NOT IN (select department_id
                            from employees
                            where department_id is not null);
--sau asa:

SELECT department_id, department_name
FROM departments d
WHERE department_id NOT IN (SELECT nvl(department_id, -1)
                            FROM employees
                            );

-- METODA 2 - UTILIZAND NOT EXISTS
SELECT department_id, department_name
FROM departments d
WHERE NOT EXISTS (SELECT employee_id 
                    FROM employees
                    WHERE department_id = d.department_id);


-- CLAUZA WITH
-- DISCUTIE EX 10

10.	Utilizând clauza WITH, să se scrie o cerere care afişează numele 
departamentelor şi valoarea totală a salariilor din cadrul acestora. 
Se vor considera departamentele a căror valoare totală a salariilor 
este mai mare decât media valorilor totale ale salariilor tuturor angajatilor.

WITH val_dep AS (SELECT department_name, SUM(salary) AS total
                 FROM departments d join employees e ON (d.department_id = e.department_id)
                 GROUP BY department_name
                 ),         

val_medie  AS (SELECT SUM(total)/COUNT(*) AS medie
               FROM val_dep)     

SELECT *
FROM val_dep
WHERE total > (SELECT medie
               FROM val_medie)
ORDER BY department_name;


11. Să se afişeze codul, prenumele, numele şi data angajării, pentru angajatii 
condusi de Steven King care au cea mai mare vechime dintre subordonatii lui Steven King. 
Rezultatul nu va conţine angajaţii din anul 1970. 

WITH subalterni AS (
    SELECT e1.employee_id, e1.first_name, e1.last_name, e1.hire_date
    FROM employees e1 JOIN employees e2 ON (e1.manager_id = e2.employee_id)
    WHERE LOWER(e2.first_name || e2.last_name) = 'stevenking'
      AND TO_CHAR(e1.hire_date, 'YYYY') != '1970'
)
SELECT employee_id, first_name, last_name, hire_date
FROM subalterni
WHERE hire_date = (SELECT MIN(hire_date) FROM subalterni);

--var 2:
SELECT employee_id, first_name, last_name, hire_date
FROM employees
WHERE manager_id = (SELECT employee_id 
                    FROM employees 
                    WHERE LOWER(first_name || last_name) = 'stevenking')
  AND TO_CHAR(hire_date, 'YYYY') != '1970'
  AND hire_date = (SELECT MIN(hire_date)
                   FROM employees
                   WHERE manager_id = (SELECT employee_id 
                                       FROM employees 
                                       WHERE LOWER(first_name || last_name) = 'stevenking')
                     AND TO_CHAR(hire_date, 'YYYY') != '1970');


12. Sa se obtina numele angajaților care au cele mai mari 10 salarii din companie. 
Rezultatul se va afişa în ordine crescătoare a salariilor.

-- Solutia 1: subcerere sincronizată

-- numaram cate salarii sunt mai mari decat linia la care a ajuns

SELECT last_name, salary
FROM employees e1
WHERE (SELECT COUNT(DISTINCT salary) 
       FROM employees e2 
       WHERE e2.salary > e1.salary) < 10
ORDER BY salary ASC;

--solutia 2 top n

-- ESTE VARIANTA GRESITA DEOARECE TREBUIE SA SORTAM
INAINTE DE A PUNE CONDITIA DIN WHERE
SELECT employee_id, last_name, salary, rownum
FROM employees
WHERE ROWNUM <= 10
ORDER BY salary DESC;

-- VARIANTA CORECTA
SELECT *
FROM (SELECT employee_id, last_name, salary
        FROM employees
        ORDER BY salary desc
    )
WHERE ROWNUM <= 10
ORDER BY salary;

-- VARIANTA CU FETCH
-- FETCH FIRST X ROWS ONLY.
SELECT employee_id, last_name, salary
FROM employees
ORDER BY salary DESC
FETCH FIRST 10 ROWS ONLY;



-- DAR IN CADRUL EXERCITIULUI NOSTRU TREBUIE SA SORTAM CRESCATOR DUPA SALARII(IN FINAL)
SELECT employee_id, last_name, salary
FROM (SELECT employee_id, last_name, salary
        FROM employees
        ORDER BY salary desc
        FETCH FIRST 10 ROWS ONLY
        )
ORDER BY salary;

13.	Să se afişeze informaţii despre departamente, în formatul următor: 
"Departamentul <department_name> este condus de {<manager_id> | nimeni} 
şi {are numărul de salariaţi  <n> | nu are salariati}".

        
        
WITH nrsal AS (SELECT department_id, COUNT(employee_id) AS total_ang
                FROM employees
                GROUP BY department_id
                )
SELECT 'Departamentul ' || d.department_name || ' este condus de ' || 
       NVL(TO_CHAR(d.manager_id), 'nimeni') || ' şi ' || 
       CASE 
           WHEN NVL(s.total_ang, 0) > 0 THEN 'are numărul de salariaţi ' || s.total_ang
           ELSE 'nu are salariati'
       END AS "Informatii Departamente"
FROM departments d 
LEFT JOIN nrsal s ON (d.department_id = s.department_id);


--15.	Sa se afiseze salariatii care au fost angajati în aceeaşi zi a lunii 
--în care cei mai multi dintre salariati au fost angajati 
--(ziua lunii insemnand numarul zilei, indiferent de luna si an). 


with datanr as (SELECT count(employee_id) as nr, TO_CHAR(hire_date, 'DD') AS zi
                FROM employees
                GROUP BY TO_CHAR(hire_date, 'DD'))
SELECT employee_id, last_name, hire_date
from employees
where TO_CHAR(hire_date, 'DD') IN (SELECT zi
                                from datanr
                                where nr >= ALL (SELECT nr
                                                 from datanr)
                                );


16.	Sa se listeze pentru fiecare angajat orasul in care a lucrat cele mai multe zile. 

--de la gemini

WITH zile_orase AS (
    -- Pasul 1 & 2: Calculam totalul de zile petrecute de fiecare om in fiecare oras
    SELECT j.employee_id, 
           l.city, 
           SUM(j.end_date - j.start_date) AS total_zile
    FROM job_history j
    JOIN departments d ON (j.department_id = d.department_id)
    JOIN locations l ON (d.location_id = l.location_id)
    GROUP BY j.employee_id, l.city
)
-- Pasul 3: Extragem orasul castigator pentru fiecare angajat
SELECT z1.employee_id, 
       e.last_name, 
       z1.city AS "Oras", 
       z1.total_zile AS "Zile Lucrate"
FROM zile_orase z1
JOIN employees e ON (z1.employee_id = e.employee_id) -- Aducem si numele omului
WHERE z1.total_zile = (SELECT MAX(total_zile)
                       FROM zile_orase z2
                       WHERE z1.employee_id = z2.employee_id);


