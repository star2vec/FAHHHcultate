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


select last_name, salary, department_id, a.medie 
from employees join departments using(department_id)
               join (SELECT avg(salary) as medie, department_id
                    from employees
                    group by department_id
                    ) a using (department_id);

b) Să se afişeze informaţii (numele, salariul si codul departamentului) 
despre angajaţii al căror salariu depăşeşte valoarea medie a salariilor 
tuturor colegilor din companie.

SELECT last_name, salary, department_id
from employees
where salary > ALL (SELECT avg(salary)
                     from employees);


c) Să se afişeze informaţii (numele, salariul si codul departamentului) 
despre angajaţii al căror salariu depăşeşte valoarea medie a salariilor 
colegilor săi de departament.

SELECT last_name, salary, department_id
from employees e
where salary > ALL (SELECT avg(salary)
                     from employees
                     where department_id = e.department_id
                     group by department_id
                     );


d) Analog cu cererea precedentă, afişându-se şi numele departamentului 
şi media salariilor acestuia şi numărul de angajaţi.

-- De ce varianta aceasta este gresita?
-- Argumentati

select last_name, salary, e.department_id, department_name, 
       round(avg(salary)), count(employee_id)
from employees e join departments d on (e.department_id = d.department_id)
group by last_name, salary, e.department_id, department_name;  


--Soluţia 1 (subcerere necorelată în clauza FROM)

select last_name, salary, department_id, department_name, a.medie, a.numar 
from employees join departments using(department_id)
               join (SELECT avg(salary) as medie, count(employee_id) as numar, department_id
                    from employees
                    group by department_id
                    ) a using (department_id);


--Soluţia 2 (subcerere corelată în clauza SELECT)

select last_name, salary, e.department_id, department_name, 
(SELECT avg(salary)
from employees
where department_id = e.department_id
group by department_id) as medie, 
(SELECT count(employee_id)
from employees
where department_id = e.department_id
group by department_id) as numar
from employees e join departments d on (e.department_id = d.department_id);


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
WHERE salary = (SELECT min(salary)
                from employees 
                where department_id = e.department_id
                group by department_id);


-- Soluţia 2 (fără sincronizare):
SELECT last_name, salary, department_id  
FROM employees
WHERE (salary, department_id) IN (SELECT min(salary), department_id
                 FROM employees 
                 GROUP BY department_id
                 );


-- Soluţia 3: Subcerere în clauza FROM 
               
SELECT e.last_name, e.salary, e.department_id  
FROM employees e join (SELECT min(salary) minim, department_id
                    FROM employees 
                    GROUP BY department_id
                    ) a  on (e.salary = a.minim)
WHERE a.department_id = e.department_id;


6.	Sa se obtina numele si salariul salariatilor care lucreaza intr-un departament 
in care exista cel putin 1 angajat cu salariul egal cu 
salariul maxim din departamentul 30.


-- METODA 1 - IN

SELECT last_name, salary
from employees
where department_id IN (select distinct department_id
                        from employees
                        where salary = (SELECT max(salary)
                                        from employees
                                        where department_id = 30
                                        )
                        );                


-- METODA 2 - EXISTS
select last_name, salary
from employees emp
where exists (select 1 
              from employees 
              where emp.department_id = department_id
              and salary = (SELECT max(salary)
                            from employees
                            where department_id = 30
                            )
              );

7. a) Să se afişeze codul, numele şi prenumele angajaţilor 
care au cel puţin doi subalterni. 

SELECT employee_id, first_name, last_name
FROM employees 
WHERE employee_id IN (SELECT manager_id 
                      FROM employees 
                      WHERE manager_id IS NOT NULL
                      GROUP BY manager_id
                      HAVING COUNT(employee_id) >= 2);


b) Cati subalterni are fiecare angajat? Se vor afisa codul, numele, 
prenumele si numarul de subalterni. Daca un angajat nu are subalterni, 
o sa se afiseze 0 (zero). 


SELECT employee_id, 
       last_name, 
       first_name, 
       (SELECT COUNT(employee_id) 
        FROM employees 
        WHERE manager_id = e.employee_id) AS numar_subalterni
FROM employees e;

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
SELECT department_id, department_name
FROM departments d
WHERE department_id NOT IN (SELECT nvl(department_id, -1)
                            FROM employees
                            );

-- METODA 2 - UTILIZAND NOT EXISTS
SELECT department_id, department_name
FROM departments d
WHERE NOT EXISTS (SELECT department_id
           FROM employees
           where department_id = d.department_id
          );


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


WITH angking AS (select employee_id, first_name, last_name, hire_date
                 from employees
                 where manager_id IN (select employee_id 
                                      from employees
                                      where lower(last_name||first_name) = 'kingsteven'
                                      )
                )

SELECT * 
from angking
where hire_date = (select MIN(hire_date)
                  from angking)
and TO_CHAR(hire_date, 'YYYY') != 1970;

12. Sa se obtina numele angajaților care au cele mai mari 10 salarii din companie. 
Rezultatul se va afişa în ordine crescătoare a salariilor.

-- Solutia 1: subcerere sincronizată

-- numaram cate salarii sunt mai mari decat linia la care a ajuns

select last_name, salary
from employees e;


-- Solutia 2: analiza top-n 
-- ANALIZATI VARIANTA URMATOARE?
select employee_id, last_name, salary, rownum
from employees
where rownum <= 10
order by salary desc;


13.	Să se afişeze informaţii despre departamente, în formatul următor: 
"Departamentul <department_name> este condus de {<manager_id> | nimeni} 
şi {are numărul de salariaţi  <n> | nu are salariati}".

SELECT 'Departamentul ' || department_name || ' este condus de ' || NVL(TO_CHAR(d.manager_id), 'nimeni') 
    || ' si ' || CASE WHEN count(employee_id) > 0 THEN ' are numarul de salariati ' || count(employee_id) 
                      ELSE 'nu are salariati' END
FROM departments d LEFT JOIN employees e ON (d.department_id = e.department_id)  
GROUP BY d.manager_id, department_name;

15.	Sa se afiseze salariatii care au fost angajati în aceeaşi zi a lunii 
în care cei mai multi dintre salariati au fost angajati 
(ziua lunii insemnand numarul zilei, indiferent de luna si an);

WITH angzi AS (select employee_id, TO_CHAR(hire_date, 'DD') as zi
               from employees
               ),
               
numarzi AS (select count(employee_id) numar, TO_CHAR(hire_date, 'DD') as zi
               from employees
               group by TO_CHAR(hire_date, 'DD')
               )
               
SELECT employee_id
FROM angzi
WHERE zi IN (SELECT zi
            from angzi
            group by zi
            having count(employee_id) IN (select max(numar)
                                        from numarzi
                                        )
            );

16.	Sa se listeze pentru fiecare angajat orasul in care a lucrat cele mai multe zile;

with oraszile as (select employee_id, city, sum(nrzile) as numar 
                 from (select employee_id, city, round(sysdate-hire_date) as nrzile
                      from employees e join departments d on (e.department_id = d.department_id)
                                       join locations l on (d.location_id = l.location_id)
                                       
                       UNION ALL
                       
                       select employee_id, city, round(end_date-start_date) as nrzile
                       from job_history j join departments d on (j.department_id = d.department_id)
                                          join locations l on (d.location_id = l.location_id)
                       )
                 group by employee_id, city
                 )
                 
SELECT employee_id, city
from oraszile o
WHERE numar = (select max(numar)
                from oraszile
                where employee_id = o.employee_id
                )
group by employee_id, city;
            

                        
                                
