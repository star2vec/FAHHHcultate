-- LABORATOR 6 - SAPTAMANA 9 - Subcereri Necorelate


1. Folosind subcereri, să se afişeze numele şi data angajării pentru salariaţii 
care au fost angajaţi după Gates.

SELECT last_name, hire_date
FROM employees
WHERE hire_date > (SELECT hire_date
                   FROM employees
                   WHERE INITCAP(last_name)= 'Gates'
                   );


2. Folosind subcereri, scrieţi o cerere pentru a afişa numele şi salariul 
pentru toţi colegii (din acelaşi departament) lui Gates. Se va exclude Gates. 


SELECT last_name, salary
from employees e
where department_id = (SELECT department_id
                        FROM employees
                        WHERE employee_id != e.employee_id
                        AND lower(last_name) = 'gates');


--Se va inlocui Gates cu King;


3. Scrieți o cerere pentru a afişa numele, codul departamentului și salariul angajaților 
al căror cod de departament și salariu coincid cu codul departamentului și salariul 
unui angajat care câștigă comision. 

SELECT last_name, department_id, salary
FROM employees
WHERE (department_id, salary) IN (SELECT department_id, salary
                                  FROM employees
                                  WHERE commission_pct IS NOT NULL
                                );

                                                                       
4. Să se afișeze codul, numele și salariul tuturor angajaților al căror salariu 
este mai mare decât salariul mediu din companie.

SELECT employee_id, last_name, salary 
FROM employees 
WHERE salary > (SELECT AVG(salary) 
                FROM employees);




5. Scrieti o cerere pentru a afișa angajații care câștigă 
(castiga = salariul plus comision din salariu) 
mai mult decât oricare funcționar (job-ul functionarilor  conţine şirul "CLERK"). 
Sortați rezultatele dupa salariu, în ordine descrescătoare;

SELECT employee_id
FROM employees 
WHERE salary * (1 + NVL(commission_pct, 0)) >= (SELECT MAX(salary * (1 + NVL(commission_pct, 0))) 
                                                FROM employees
                                                WHERE lower(job_id) like ('%clerk%'))
ORDER BY salary * (1 + NVL(commission_pct, 0)) desc;




6. Scrieţi o cerere pentru a afişa numele angajatilor, numele departamentului 
şi salariul angajaţilor care câştigă comision, dar al căror şef direct nu câştigă comision.	

-- REZOLVATI IN ECHIPA DE 2 PERSOANE

-- CEREREA TREBUIE SA RETURNEZE 5 ANGAJATI
-- VEZI IMAGINEA ATASATA IN LABORATOR

SELECT last_name, department_name, salary
FROM employees e join departments d on (e.department_id = d.department_id)
WHERE commission_pct IS NOT NULL
and e.manager_id IN (select employee_id
                    from employees
                    where commission_pct IS NULL);


7. Să se afișeze numele și salariul angajaților care lucrează în departamente aflate
în locații din CANADA și care ocupă joburi ce aparțin unei liste de job_id-uri ce 
conțin cuvântul man. Se vor afișa – numele, prenumele, salariul și id-ul jobului. 

Prima variantă – o să utilizeze doar subcereri nesincronizate

A doua variantă – o să utilizeze doar operații JOIN


--VARIANTA 1
SELECT first_name, last_name, salary, job_id
FROM employees 
where lower(job_id) like ('%man%') 
AND department_id IN (SELECT department_id 
                      FROM departments 
                      WHERE location_id IN (SELECT location_id
                                            FROM locations
                                            WHERE country_id = 'CA'
                                            )
                      );                      

--VARIANTA 2
SELECT first_name, last_name, salary, job_id
FROM employees e join departments d on (e.department_id = d.department_id)
                 join locations l on (d.location_id = l.location_id)
WHERE lower(job_id) like ('%man%')
AND country_id = 'CA';


8. Să se obțină codurile departamentelor în care nu lucreaza nimeni 
(nu este introdus nici un salariat în tabelul employees). Sa se utilizeze subcereri;

SELECT department_id
from departments
where department_id NOT IN (SELECT department_id
                            from employees
                            where department_id IS NOT NULL);
                    

9. Sa se creeze tabelul SUBALTERNI care sa contina codul, numele si prenumele angajatilor 
care il au manager pe Steven King, alaturi de codul si numele lui King.
Coloanele se vor numi cod, nume, prenume, cod_manager, nume_manager.

DESC employees;

CREATE TABLE SUBALTERNI
(cod number(6) constraint pkey_sub primary key,
nume varchar2(25) constraint nume_sub not null,
prenume varchar2(20),
cod_manager number(6),
nume_manager varchar2(25) constraint nume_man not null
);

INSERT INTO SUBALTERNI (cod, nume, prenume, cod_manager, nume_manager)
        (SELECT sub.employee_id, sub.last_name, sub.first_name, sub.manager_id, man.last_name
         FROM employees sub join employees man ON (sub.manager_id = man.employee_id)
         WHERE sub.manager_id = (SELECT employee_id
                                 FROM employees
                                 WHERE lower(first_name||last_name) = 'stevenking'
                                )
        );