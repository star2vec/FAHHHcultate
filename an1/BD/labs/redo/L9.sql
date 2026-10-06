-- LABORATOR 9 - SAPTAMANA 12


EX: Să se obţină codurile salariaţilor ataşaţi tuturor proiectelor 
pentru care s-a alocat un buget egal cu 10000.

SELECT * FROM PROJECT; -- p2 si p3 proiecte cu buget de 10k
SELECT * FROM WORKS_ON; -- 101, 145, 148, 200 
                   --> angajatii care lucreaza la TOATE proiectele cu buget de 10k

!!! Toate proiectele inseamna ca angajatii sa lucreze OBLIGATORIU 
la TOATE proiectele cu buget de 10k (la toate - p2 si p3), 
dar si la alte proiecte cu un alt buget.

--Metoda 1 (utilizând de 2 ori NOT EXISTS):

SELECT	DISTINCT employee_id
FROM works_on a -- preluam toti employee_id din tabela works_on, 
                -- dar numai pe aceia pentru care NU exista niciun proiect             
                -- cu buget de 10 000 la care să nu lucreze
                
WHERE NOT EXISTS   -- primul NOT EXISTS (relatia universala)
                   -- aceasta conditie filtreaza toti angajatii care lucreaza 
                   -- la toate proiectele cu buget de 10000
                   -- Daca exista macar un proiect cu buget 10000 
                   -- la care angajatul nu lucreaza, acel angajat este exclus
         (SELECT 1
          FROM	project p
          WHERE	budget = 10000
          AND NOT EXISTS   -- are loc verificarea efectiva
                           -- se verifica daca angajatul curent a.employee_id 
                           -- este atasat proiectului p.project_id
                           -- Daca nu este, inseamna ca acel proiecti il descalifica 
                           -- deci excludem acel angajat din afisare
                (SELECT	'x'
                 FROM works_on b
                 WHERE p.project_id = b.project_id
                 AND b.employee_id = a.employee_id
                 ) 
          ); 
          
---------------------------------------------------
DIVISION - succesiune de 2 operatori not exists => 
         => Impartim in doua relatii:

angajati lucreaza la proiecte
proiectele au buget de 10k
----------------------------------------------------


   
--Metoda 2 (simularea diviziunii cu ajutorul funcţiei COUNT):

SELECT employee_id
FROM works_on
WHERE project_id IN
                (SELECT	project_id
                 FROM  	project
                 WHERE	budget = 10000
                 )
GROUP BY employee_id
HAVING COUNT(project_id)=
                (SELECT COUNT(*)
                 FROM project
                 WHERE budget = 10000
                 );
 
 -- metoda 3:
 
 select employee_id
 from works_on
 
 MINUS 
 
 select employee_id
 from (select employee_id, project_id
       from (select distinct employee_id from works_on) t1,
            (select project_id from project where budget = 10000) t2
            
        MINUS
        
        select employee_id, project_id from works_on
        ) t3;
        
-- metoda 4:
select distinct employee_id
from works_on a
where not exists(
        (select project_id
        from project p
        where budget = 10000
        )
        MINUS
        (select p.project_id
        from project p, works_on b
        where p.project_id = b.project_id
        and b.employee_id = a.employee_id
        )
                );
 
 
 
                 
-- EXERCITII DIVISION:
  
                 
8.	Să se afişeze lista angajaţilor care au lucrat numai pe proiecte 
conduse de managerul de proiect având codul 102.

select * from project;  -- managerul 102 conduce doua proiecte => p1 si p3

select * from works_on; -- angajatii care lucreaza NUMAI pe proiecte coduse de 102 => 
                        -- 136, 140, 150, 162, 176



9.	a) Să se obţină numele angajaţilor care au lucrat 
cel puţin pe aceleaşi proiecte ca şi angajatul având codul 200.

select * from works_on; -- ang 200 lucreaza la p2 si p3



b) Să se obţină numele angajaţilor care au lucrat cel mult pe aceleaşi proiecte 
ca şi angajatul având codul 200.

select * from works_on; -- ang 200 lucreaza la p2 si p3

=> 101 (la ambele)
   145 (la ambele) 
   148 (la ambele)
   150 (doar p3)
   162 (doar p3)
   176 (doar p3)



10. Să se obţină angajaţii care au lucrat exact pe aceleaşi proiecte 
ca şi angajatul având codul 200.





-- 1.
select distinct employee_id
from works_on a
where not exists (SELECT 1
                  from project p
                  where TO_CHAR(start_date, 'MM') IN ('01', '02', '03', '04', '05', '06')
                  AND NOT EXISTS (select 1
                                 from works_on b
                                 where p.project_id = b.project_id
                                 AND b.employee_id = a.employee_id
                                 )
                   );              


-- 2.
select project_name, project_id
from project p
where not exists (
    (select employee_id
    from job_history 
    group by employee_id
    having count(job_id) = 2
    )
    MINUS
    (select employee_id
    from works_on w
    where w.project_id = p.project_id
    )
                  );
                                    

-- 3.
with alljobs as (
    (select job_id, employee_id
    from employees
    )
    UNION
    (select job_id, employee_id
    from job_history
    )   
                ),
                
nrjobang as (select count(job_id) numar, employee_id
            from alljobs
            group by employee_id
            )
            
SELECT count(employee_id)
from nrjobang
where numar >= 3;


-- 4.
with angtara as (select employee_id, country_name
                from employees e join departments d on (e.department_id = d.department_id)
                                 join locations l on (d.location_id = l.location_id)
                                 right join countries c on (l.country_id = c.country_id)
                ),
nrtara as (select country_name, count(employee_id)
           from angtara
           group by country_name
           )
           
select *
from nrtara;


-- 5.
select e.employee_id, project_id
from employees e left join works_on w on (e.employee_id = w.employee_id);
            
            
-- 6.
with mandep as (select project_manager, department_id
                from employees e join project p on (e.employee_id = p.project_manager)
                )
                
select employee_id
from employees
where department_id in (select department_id
                        from mandep
                        where department_id is not null
                        );
                        
-- 7.
with mandep as (select project_manager, department_id
                from employees e join project p on (e.employee_id = p.project_manager)
                )
                
select employee_id, last_name, department_id
from employees
where department_id not in (select department_id
                        from mandep
                        where department_id is not null
                        );
                

-- 8.

select project_id
from project
where project_manager = 102;


-- var 1
select employee_id, project_id
from works_on a
where not exists (
    (select project_id
    from works_on
    where employee_id = a.employee_id
    )
    minus 
    (select project_id
    from project 
    where project_manager = 102
    )
                 );
    
-- var 2
select employee_id
from works_on
where project_id IN (select project_id
                     from project
                     where project_manager = 102
                     )
                     
MINUS

select employee_id
from works_on
where project_id not in (select project_id
                        from project
                        where project_manager = 102
                        );
                        

-- 9.

-- a.
select project_id
from works_on
where employee_id = 200;

with proj200 as (select project_id
                 from works_on
                 where employee_id = 200
                )
                
select employee_id, last_name
from employees e
where not exists (
    (select project_id
    from proj200
    )
    MINUS
    (select project_id
    from works_on
    where employee_id = e.employee_id
    )
                );
    
-- b.
with proj200 as (select project_id
                 from works_on
                 where employee_id = 200
                )
                
select employee_id, last_name
from employees e
where not exists (
    (select project_id
    from works_on
    where employee_id = e.employee_id
    )
    MINUS
    (select project_id
    from proj200
    )
                );
                
                
-- 10.

with proj200 as (select project_id
                 from works_on
                 where employee_id = 200
                )

select employee_id, last_name
from employees e
where not exists (
    (select project_id
    from works_on
    where employee_id = e.employee_id
    )
    MINUS
    (select project_id
    from proj200
    )
                )
                
INTERSECT

select employee_id, last_name
from employees e
where not exists (
    (select project_id
    from proj200
    )
    MINUS
    (select project_id
    from works_on
    where employee_id = e.employee_id
    )
                );

-- sau:

with proj200 as (select project_id
                 from works_on
                 where employee_id = 200
                )

select employee_id, last_name
from employees e
where not exists (
    (select project_id
    from works_on
    where employee_id = e.employee_id
    )
    MINUS
    (select project_id
    from proj200
    )
                )
and not exists (
    (select project_id
    from proj200
    )
    MINUS
    (select project_id
    from works_on
    where employee_id = e.employee_id
    )
                );









