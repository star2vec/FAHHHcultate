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
 
                 
-- EXERCITII DIVISION:
  
                 
8.	Să se afişeze lista angajaţilor care au lucrat numai pe proiecte 
conduse de managerul de proiect având codul 102.

select * from project;  -- managerul 102 conduce doua proiecte => p1 si p3

select * from works_on; 
-- angajatii care lucreaza NUMAI pe proiecte coduse de 102 => 
                        -- 136, 140, 150, 162, 176

SELECT employee_id
FROM works_on 
where project_id in (select project_id
                    from project
                    where project_manager = 102)
MINUS

SELECT employee_id
from works_on
where project_id not in (select project_id
                        from project
                        where project_manager = 102);



9.	a) Să se obţină numele angajaţilor care au lucrat 
cel puţin pe aceleaşi proiecte ca şi angajatul având codul 200.

select * from works_on; -- ang 200 lucreaza la p2 si p3

select e.last_name
from employees e join works_on w on (e.employee_id = w.employee_id)
where project_id IN (select project_id
                    from works_on 
                    where employee_id = 200)
AND w.employee_id != 200
group by w.employee_id, e.last_name
HAVING count(project_id) = (SELECT count(project_id)
                            from works_on
                            where employee_id = 200);


b) Să se obţină numele angajaţilor care au lucrat cel mult pe aceleaşi proiecte 
ca şi angajatul având codul 200.

select * from works_on; -- ang 200 lucreaza la p2 si p3

=> 101 (la ambele)
   145 (la ambele) 
   148 (la ambele)
   150 (doar p3)
   162 (doar p3)
   176 (doar p3)
   
   
select employee_id
from works_on
where project_id IN (select project_id 
                     from works_on
                     where employee_id = 200) 

MINUS 

select employee_id
from works_on
where project_id NOT IN (select project_id 
                     from works_on
                     where employee_id = 200);


10. Să se obţină angajaţii care au lucrat exact pe aceleaşi proiecte 
ca şi angajatul având codul 200.


(select employee_id
from works_on
where project_id IN (select project_id 
                     from works_on
                     where employee_id = 200) 

MINUS 

select employee_id
from works_on
where project_id NOT IN (select project_id 
                     from works_on
                     where employee_id = 200))
                     
INTERSECT

(
select employee_id
from works_on
where project_id IN (select project_id
                    from works_on 
                    where employee_id = 200)
AND employee_id != 200
group by employee_id
HAVING count(project_id) = (SELECT count(project_id)
                            from works_on
                            where employee_id = 200));




