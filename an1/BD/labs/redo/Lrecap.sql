-- EXERCITII DIVERSE:


1. Să se afişeze informaţii despre departamente, în formatul următor: 
"Departamentul <department_name> este condus de {<manager_id> | nimeni} 
şi {are numărul de salariaţi  <n> | nu are salariati}".

SELECT department_name, NVL(TO_CHAR(d.manager_id), 'nimeni'), 
    CASE 
        when count(employee_id) > 0 then to_char(count(employee_id))
        else 'nu are angajati'
        end
from departments d left join employees e on (e.department_id = d.department_id)
group by department_name, NVL(TO_CHAR(d.manager_id), 'nimeni');

2. Sa se afiseze salariatii care au fost angajati în aceeaşi zi a lunii 
în care cei mai multi dintre salariati au fost angajati 
(ziua lunii insemnand numarul zilei, indiferent de luna si an);

with nrangzi as (select count(employee_id) numar, to_char(hire_date, 'DD') zi
                from employees 
                group by to_char(hire_date, 'DD') 
                )
                
SELECT employee_id
from employees
where to_char(hire_date, 'DD') IN (SELECT zi
                                  from nrangzi
                                  where numar = (select max(numar)
                                                from nrangzi
                                                )
                                   );             
                

3. Sa se listeze pentru fiecare angajat orasul in care a lucrat cele mai multe zile. 


with joburiang as (select job_id, employee_id, nrzile, oras  
                  from (select job_id, employee_id, end_date - start_date as nrzile, city as oras
                        from job_history j join departments d on (j.department_id = d.department_id)
                                           join locations l on (d.location_id = l.location_id)
                        
                        UNION
                        
                        select job_id, employee_id, round(sysdate - hire_date) as nrzile, city as oras
                        from employees e join departments d on (e.department_id = d.department_id)
                                         join locations l on (d.location_id = l.location_id)
                        )
                    ),
                    
sumzile as (select employee_id, oras, sum(nrzile) as nrtot
            from joburiang
            group by oras, employee_id
            )
                        
SELECT employee_id, oras 
from sumzile s
where nrtot = (select max(nrtot) from sumzile  where s.employee_id = employee_id);
            

4. Să se listeze informaţii despre proiectele la care au participat toţi angajaţii 
care au deţinut alte 2 posturi în firmă.

with emp2posturi as (select employee_id
                    from job_history
                    group by employee_id
                    having count(job_id) = 2
                    )
                    
SELECT project_id, project_name
from project p
where not exists (
     (select employee_id 
      from emp2posturi
     )    
     MINUS
    (select employee_id
     from works_on
     where project_id = p.project_id
    )
                );               


5. Pentru fiecare ţară, să se afişeze numărul de angajaţi din cadrul acesteia.

with angtara as (select employee_id, country_name
                from employees e join departments d on (e.department_id = d.department_id)
                                 join locations l on (d.location_id = l.location_id)
                                 right join countries c on (c.country_id = l.country_id)
                )
                
select country_name, count(employee_id)
from angtara
group by country_name;

6. Cati subalterni are fiecare angajat? Se vor afisa codul, numele, 
prenumele si numarul de subalterni. Daca un angajat nu are subalterni, 
o sa se afiseze 0 (zero). 

select e1.employee_id, e1.last_name, e1.first_name, count(e2.employee_id)
from employees e1 left join employees e2 on (e1.employee_id = e2.manager_id)
group by e1.employee_id, e1.last_name, e1.first_name;