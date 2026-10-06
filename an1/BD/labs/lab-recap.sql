-- EXERCITII DIVERSE:


1. Să se afişeze informaţii despre departamente, în formatul următor: 
"Departamentul <department_name> este condus de {<manager_id> | nimeni} 
şi {are numărul de salariaţi  <n> | nu are salariati}".



SELECT 'Departamentul ' || department_name || ' este condus de ' || NVL(TO_CHAR(d.manager_id), 'nimeni') 
    || ' si ' || CASE WHEN count(employee_id) > 0 THEN ' are numarul de salariati ' || count(employee_id) 
                      ELSE 'nu are salariati' END
FROM departments d LEFT JOIN employees e ON (d.department_id = e.department_id)  
GROUP BY d.manager_id, department_name;



--2. Sa se afiseze salariatii care au fost angajati în aceeaşi zi a lunii 
în care cei mai multi dintre salariati au fost angajati 
(ziua lunii insemnand numarul zilei, indiferent de luna si an);

WITH countzile AS (SELECT TO_CHAR(hire_date, 'DD') as zi, count(employee_id) as numar
                   FROM employees
                   GROUP BY TO_CHAR(hire_date, 'DD')
                   )
SELECT last_name, hire_date
FROM employees
WHERE TO_CHAR(hire_date, 'DD') IN (SELECT zi 
                                   FROM countzile
                                   WHERE numar = (SELECT max(numar)
                                                  FROM countzile));

3. Sa se listeze pentru fiecare angajat orasul in care a lucrat cele mai multe zile.

WITH zileoras AS (SELECT employee_id, city, sum(nrzile) as numar 
                 from (SELECT employee_id, city, round(sysdate-hire_date) as nrzile
                       FROM employees e join departments d on (e.department_id = d.department_id)
                                        join locations l on (l.location_id = d.location_id)
                 
                       UNION ALL
                        
                       SELECT employee_id, city, round(end_date-start_date) as nrzile
                       FROM job_history j join departments d on (j.department_id = d.department_id)
                                          join locations l on (l.location_id = d.location_id)
                       )
                       group by employee_id, city
                  )
SELECT employee_id, city
FROM zileoras z 
WHERE numar = (select max(numar)
               from zileoras
               where employee_id = z.employee_id
               )
group by employee_id, city;               
                        

4. Să se listeze informaţii despre proiectele la care au participat toţi angajaţii 
care au deţinut alte 2 posturi în firmă.

SELECT *
from project
where project_id = (SELECT project_id 
                    FROM works_on
                    WHERE employee_id in (SELECT employee_id
                                          FROM job_history
                                          GROUP BY employee_id
                                          HAVING count(job_id) = 2)
                    GROUP BY project_id 
                    having count(*) = (select count(count(*))
                                       FROM job_history
                                       GROUP BY employee_id
                                       having count(job_id) = 2 
                                       )
                    );


5. Pentru fiecare ţară, să se afişeze numărul de angajaţi din cadrul acesteia.

WITH emptara AS (SELECT count(e.employee_id) as numar, country_id
                 FROM employees e join departments d on (e.department_id = d.department_id)
                                  join locations l on (d.location_id = l.location_id)
                 GROUP BY country_id)
SELECT numar, country_id 
FROM emptara;


6. Cati subalterni are fiecare angajat? Se vor afisa codul, numele, 
prenumele si numarul de subalterni. Daca un angajat nu are subalterni, 
o sa se afiseze 0 (zero). 

WITH subs AS (SELECT manager_id, count(employee_id) as nrsub
              FROM employees
              GROUP BY manager_id)
SELECT e.employee_id, last_name, first_name, NVL(nrsub, 0)
FROM subs s right join employees e on (e.employee_id = s.manager_id);

