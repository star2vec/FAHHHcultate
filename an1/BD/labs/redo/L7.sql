-- LABORATOR 7 -- SAPTAMANA 10

--exemplu grupare

drop table grupare;
create table grupare (id number(5) primary key,
                      nume varchar2(10) not null,
                      salariu number(10) not null,
                      manager_id number(5) not null
                      );
                      
select * from grupare;

insert into grupare values (1, 'user1', 1000, 1);

insert into grupare values (2, 'user2', 1400, 1);

insert into grupare values (3, 'user3', 700, 2);

insert into grupare values (4, 'user4', 300, 2);

insert into grupare values (5, 'user5', 1600, 2);

insert into grupare values (6, 'user6', 1200, 2);

commit;

--exemplu folosind clauza where
select *
from grupare
where salariu < 1100;

--exemplu folosind where si grupare
select manager_id, salariu
from grupare
where salariu < 1100
group by manager_id, salariu;

--exemplu folosind where, iar gruparea realizata doar dupa coloana manager_id
select manager_id
from grupare
where salariu < 1100
group by manager_id;

--exemplu folosind having
select max(salariu)
from grupare
having max(salariu) < 10000;

--group by si having
select manager_id, min(salariu)
from grupare
group by manager_id
having min(salariu) <= 1000;

------------------------------------------------

1. 
a) Functiile grup includ valorile NULL in calcule?

EXEMPLU:

Să se calculeze comisionul mediu din firmă, luând în considerare toate 
liniile din tabel.

SELECT avg(commission_pct)
from employees;

SELECT sum(commission_pct)/count(*)
from employees;

-- avg+sum nu iau in considerare valorile null


b) Care este deosebirea dintre clauzele WHERE şi HAVING? 





2. Să se afişeze cel mai mare salariu, cel mai mic salariu, suma şi media salariilor 
tuturor angajaţilor. 
Etichetaţi coloanele Maxim, Minim, Suma, respectiv Media. 
Sa se rotunjeasca media salariilor. 

SELECT MAX(salary) Maxim, min(salary) Minim, sum(salary) Suma, avg(salary) Media
FROM employees;


3. Să se modifice problema 2 pentru a se afişa minimul, maximul, suma şi 
media salariilor pentru FIECARE job. 

SELECT MAX(salary) Maxim, min(salary) Minim, sum(salary) Suma, avg(salary) Media
FROM employees
GROUP BY job_id;


4. Să se afişeze numărul de angajaţi pentru FIECARE  departament.

SELECT COUNT(employee_id), d.department_id
FROM employees e right join departments d on (e.department_id = d.department_id)
GROUP BY d.department_id;


5. Să se determine numărul de angajaţi care sunt şefi. 
Etichetati coloana “Nr. manageri”.

SELECT COUNT(DISTINCT e2.employee_id) "Nr. manageri"
FROM employees e1 join employees e2 on (e1.manager_id = e2.employee_id);

--sau:
SELECT COUNT(DISTINCT manager_id) AS "Nr. manageri"
FROM employees;


6. Să se afişeze diferenţa dintre cel mai mare si cel mai mic salariu. 
Etichetati coloana “Diferenta”.

SELECT max(salary)-min(salary) Diferenta
FROM employees;


7. Scrieţi o cerere pentru a se afişa numele departamentului, locaţia, 
numărul de angajaţi şi salariul mediu pentru angajaţii din acel departament. 
Coloanele vor fi etichetate corespunzător.
Se vor afisa si angajatii care nu au departament

Observatie: În clauza GROUP BY se trec obligatoriu toate coloanele prezente 
în clauza SELECT, cu exceptia functiilor de agregare

SELECT department_name, location_id, count(employee_id), avg(salary)
FROM departments d right join employees e on (d.department_id = e.department_id)
GROUP BY department_name, location_id;

8. Pentru fiecare şef, să se afişeze codul său şi salariul celui mai prost 
platit subordonat. Se vor exclude cei pentru care codul managerului nu este cunoscut. 
De asemenea, se vor exclude grupurile în care salariul minim este mai mic de 1000$. 
Sortaţi rezultatul în ordine descrescătoare a salariilor.

SELECT mgr.employee_id, min(ang.salary)
from employees ang join employees mgr on (ang.manager_id = mgr.employee_id)
GROUP BY mgr.employee_id
HAVING min(ang.salary) >= 1000
ORDER BY min(ang.salary) DESC;


--sau:
SELECT manager_id, MIN(salary)
FROM employees
WHERE manager_id IS NOT NULL
GROUP BY manager_id
HAVING MIN(salary) >= 1000
ORDER BY MIN(salary) DESC;


9. Pentru departamentele in care salariul maxim depăşeşte 3000$, să se obţină codul, 
numele acestor departamente şi salariul maxim pe departament.

SELECT department_id, department_name, MAX(salary)
FROM departments JOIN employees USING(department_id)
GROUP BY department_id,department_name
HAVING MAX(salary) >= 3000;


10. Care este salariul mediu minim al job-urilor existente? 
Salariul mediu al unui job va fi considerat drept media aritmetică a 
salariilor celor care îl practică.

SELECT min(avg(salary))
FROM employees 
GROUP BY job_id;



12. Sa se obtina codul, titlul şi salariul mediu al job-ului pentru care 
salariul mediu este minim. 

SELECT e.job_id, job_title, avg(salary)
from employees e join jobs j on (e.job_id = j.job_id)
group by e.job_id, job_title
having avg(salary) = (SELECT min(avg(salary))
                        FROM employees 
                        GROUP BY job_id
                     );


13. Să se afişeze salariul mediu din firmă doar dacă acesta este mai mare decât 2500.
(clauza HAVING fără GROUP BY);

SELECT ROUND(AVG(salary), 2)
FROM employees
HAVING AVG(salary) > 2500;


14. Să se afişeze suma salariilor pe departamente şi, în cadrul acestora, pe job-uri.

SELECT department_id, job_id, SUM(salary)
FROM employees
GROUP BY department_id, job_id; 

15. Sa se afiseze codul, numele departamentului si numarul de angajati 
care lucreaza in acel departament pentru:

a) departamentele in care lucreaza mai putin de 4 angajati;

SELECT e.department_id, d.department_name, count(e.employee_id)
FROM employees e JOIN departments d ON (d.department_id = e.department_id )
GROUP BY e.department_id, d.department_name
having count(e.employee_id) < 4;


b) departamentul care are numarul maxim de angajati.

select e.department_id, department_name, count(employee_id)
FROM employees e JOIN departments d ON (d.department_id = e.department_id )
GROUP BY e.department_id, d.department_name
having count(e.employee_id) = (select max(count(employee_id))
                                from employees
                                group by department_id
                                );


16. Să se obţină numărul departamentelor care au cel puţin 15 angajaţi.

SELECT count(department_id)
FROM employees
where department_id IN (SELECT department_id
                        from employees
                        group by department_id
                        having count(employee_id) >= 15
                        );
                        
-- sau: 
select count(count(employee_id))
from employees
group by department_id
having count(employee_id) >= 15;


17. Să se obţină codul departamentelor şi suma salariilor angajaţilor care 
lucrează în acestea, în ordine crescătoare. Se consideră departamentele care 
au mai mult de 10 angajaţi şi al căror cod este diferit de 30.

-- Cand utilizand where? Cand se foloseste having?

SELECT department_id, SUM(salary)
FROM employees 
WHERE department_id!=30
GROUP BY department_id
HAVING COUNT(employee_id)>10
ORDER BY 2;


18. Care sunt angajatii care au mai avut cel putin doua joburi?

select employee_id
from job_history
group by employee_id
having count(job_id)>=2;
