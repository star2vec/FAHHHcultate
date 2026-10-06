CREATE TABLE CLIENTI (
    ID_CLIENT NUMBER PRIMARY KEY,
    NUME VARCHAR2(50),
    PRENUME VARCHAR2(50),
    EMAIL VARCHAR2(100),
    TELEFON VARCHAR2(15)
);

CREATE TABLE MENIU (
    ID_MENIU NUMBER PRIMARY KEY,
    TITLU VARCHAR2(100)
);

CREATE TABLE PRODUSE_ALIMENTARE (
    ID_PRODUS NUMBER PRIMARY KEY,
    NUME VARCHAR2(100),
    DESCRIERE VARCHAR2(255),
    PRET NUMBER(8,2),
    TIMP_PREPARARE NUMBER,
    ID_MENIU NUMBER REFERENCES MENIU(ID_MENIU)
);

CREATE TABLE COMENZI (
    ID_COMANDA NUMBER PRIMARY KEY,
    DATA DATE,
    ORA VARCHAR2(10),
    PRET_TOTAL NUMBER(8,2),
    STATUS VARCHAR2(50),
    ID_CLIENT NUMBER REFERENCES CLIENTI(ID_CLIENT)
);

CREATE TABLE PRODUS_COMANDA (
    ID_PRODUS NUMBER REFERENCES PRODUSE_ALIMENTARE(ID_PRODUS),
    ID_COMANDA NUMBER REFERENCES COMENZI(ID_COMANDA),
    CANTITATE NUMBER,
    PRIMARY KEY (ID_PRODUS, ID_COMANDA)
);

CREATE TABLE RECENZIE_PRODUS (
    ID_RECENZIE NUMBER PRIMARY KEY,
    SCOR NUMBER,
    COMENTARIU VARCHAR2(255),
    DATA DATE,
    ID_CLIENT NUMBER REFERENCES CLIENTI(ID_CLIENT),
    ID_PRODUS NUMBER REFERENCES PRODUSE_ALIMENTARE(ID_PRODUS)
);

INSERT INTO CLIENTI VALUES (1, 'Popescu', 'Ion', 'ion@test.ro', '0700000001');
INSERT INTO CLIENTI VALUES (2, 'Ionescu', 'Maria', 'maria@test.ro', '0700000002');
INSERT INTO CLIENTI VALUES (3, 'Georgescu', 'Andrei', 'andrei@test.ro', '0700000003');

-- Meniuri
INSERT INTO MENIU VALUES (10, 'Mic Dejun Clasic');
INSERT INTO MENIU VALUES (20, 'Pranz Business');

-- Produse Alimentare
INSERT INTO PRODUSE_ALIMENTARE VALUES (101, 'Oua Ochiuri', 'Doua oua', 15.50, 10, 10);
INSERT INTO PRODUSE_ALIMENTARE VALUES (102, 'Paine Prajita', 'Feliata', 5.00, 5, 10);
INSERT INTO PRODUSE_ALIMENTARE VALUES (103, 'Ciorba de burta', 'Cu smantana', 25.00, 15, 20);
INSERT INTO PRODUSE_ALIMENTARE VALUES (104, 'Friptura Vita', 'Medium rare', 65.00, 30, 20);

-- Comenzi
INSERT INTO COMENZI VALUES (1001, TO_DATE('2023-10-01', 'YYYY-MM-DD'), '09:00', 20.50, 'Finalizat', 1);
INSERT INTO COMENZI VALUES (1002, TO_DATE('2023-10-02', 'YYYY-MM-DD'), '13:30', 90.00, 'Finalizat', 2);
INSERT INTO COMENZI VALUES (1003, TO_DATE('2023-10-03', 'YYYY-MM-DD'), '08:45', 15.50, 'Finalizat', 1);

-- Produse Comandate
-- Comanda 1001 are 2 produse (Mic dejun complet)
INSERT INTO PRODUS_COMANDA VALUES (101, 1001, 1);
INSERT INTO PRODUS_COMANDA VALUES (102, 1001, 1);
-- Comanda 1002 are 2 produse (Pranz)
INSERT INTO PRODUS_COMANDA VALUES (103, 1002, 1);
INSERT INTO PRODUS_COMANDA VALUES (104, 1002, 1);
-- Comanda 1003 are 1 produs (Doar oua)
INSERT INTO PRODUS_COMANDA VALUES (101, 1003, 1);

-- Recenzii
INSERT INTO RECENZIE_PRODUS VALUES (1, 5, 'Excelent!', TO_DATE('2023-10-01', 'YYYY-MM-DD'), 1, 101);
INSERT INTO RECENZIE_PRODUS VALUES (2, 4, 'Bunicel', TO_DATE('2023-10-02', 'YYYY-MM-DD'), 2, 104);

COMMIT;



-- 1.

select co.id_comanda, cl.id_client, co.data, cl.nume, pa.nume, pa.pret
from comenzi co join produs_comanda pc on (co.id_comanda = pc.id_comanda)
                join produse_alimentare pa on (pc.id_produs = pa.id_produs)
                right join clienti cl on (co.id_client = cl.id_client)
ORDER BY co.id_comanda ASC,
        pa.pret desc;
        
        
-- 2.
select co.id_comanda, co.data, co.ora, co.pret_total, sum(pc.cantitate)
from comenzi co join produs_comanda pc on (co.id_comanda = pc.id_comanda)
                join produse_alimentare pa on (pc.id_produs = pa.id_produs)
group by co.id_comanda, co.data, co.ora, co.pret_total
having sum(pc.cantitate) > 1;


-- 3.
with nrcomcl as (select cl.id_client idc, count(distinct id_comanda) as numar
                 from clienti cl join comenzi co on (cl.id_client = co.id_client)
                 group by cl.id_client
                 ),
                 
com1prod as (select co.id_comanda
            from comenzi co join produs_comanda pc on (co.id_comanda = pc.id_comanda)
            group by co.id_comanda
            having count(id_produs) = 1
            )

select cl.id_client, nume, sum(pret_total)
from clienti cl left join comenzi co on (cl.id_client = co.id_client)
where cl.id_client IN (select idc
                    from nrcomcl
                    where numar = (select max(numar) from nrcomcl) 
                    )
AND co.id_comanda IN (select id_comanda 
                   from com1prod
                   where id_comanda is not null
                   )
group by cl.id_client, nume;


-- 4.

--identificam toate produsele din ala cu mic dejun clasic

with prodmicdejun as (select id_produs
                     from produse_alimentare pa join meniu m on (pa.id_meniu = m.id_meniu)
                     where titlu = 'Mic Dejun Clasic'
                     )
                     
SELECT id_client, nume
from clienti maincl
where not exists (
    --produsele comandate
    (select id_produs
    from produs_comanda pc join comenzi co on (co.id_comanda = pc.id_comanda)
                           join clienti cl on (co.id_client = cl.id_client)
    where cl.id_client = maincl.id_client
    )          
    MINUS 
    --produsele din meniul cautat
    (select id_produs
    from prodmicdejun
    )
                 );
                 
                 
-- 5.

CREATE TABLE COMENZI_CLIENTI_PREMIUM AS
WITH top3 as (select id_comanda, data, ora, pret_total, id_client
              from comenzi
              order by pret_total desc
              fetch first 3 rows only
              )
              
SELECT t.id_comanda,
       t.data, 
       t.ora, 
       t.pret_total, 
       t.id_client, 
       cl.nume as nume_client, 
       cl.prenume as prenume_client,
       pa.nume as nume_produs
from top3 t join comenzi co on (t.id_comanda = co.id_comanda)
            join clienti cl on (co.id_client = cl.id_client)
            join produs_comanda pc on (pc.id_comanda = co.id_comanda)
            join produse_alimentare pa on (pa.id_produs = pc.id_produs);


-- 6.

with clcom as (select id_client, count(id_comanda) nrcom, sum(pret_total) prettot
              from comenzi
              group by id_client
              ),
              
clprod as (select id_client, sum(pc.cantitate) as nrprod, count(distinct id_meniu) as nrmen
           from comenzi co join produs_comanda pc on (co.id_comanda = pc.id_comanda)
                           join produse_alimentare pa on (pa.id_produs = pc.id_produs)
            group by id_client
            )

select cl.id_client, nume, prenume, nrprod, prettot, nrmen
from clienti cl join clcom cc on (cl.id_client = cc.id_client)
                join clprod cp on (cl.id_client = cp.id_client)
where prettot > (select avg(pret_total) from comenzi)
and nrcom >= 2;


-- 7.

with dateprod as (select  pa.id_produs idp, nume, pret, count(id_recenzie) nrrec, avg(scor) medie
                 from recenzie_produs r join produse_alimentare pa on (r.id_produs = pa.id_produs)
                 group by pa.id_produs, nume, pret
                 ),
                 
prodcl as (select count(distinct id_client) nrcl, id_produs
           from comenzi co join produs_comanda pc on (co.id_comanda = pc.id_comanda)
           group by id_produs
           )
                
select d.idp, nume, pret, nrrec, medie, nrcl
from dateprod d join prodcl pcl on (d.idp = pcl.id_produs)
where nrrec = (select max(nrrec) from dateprod);
                
                
                    