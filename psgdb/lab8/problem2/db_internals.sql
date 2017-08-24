CREATE TABLE masinaRepository (
    id number,
    v_masina TMasina
);

/

CREATE OR REPLACE TYPE TMasina AS OBJECT (
    culoare varchar(255),
    marca varchar(255)
);

/

create or replace function factoryMasina(culoare varchar, marca varchar) return number IS
PRAGMA AUTONOMOUS_TRANSACTION;
    v_masina TMasina;
begin
    v_masina := TMasina(culoare, marca);
    
    insert into masinaRepository values (1, v_masina);
    
    commit;
    
    return 1;
end;

/

create or replace function getColor return varchar as 
    vv_masina TMasina;
begin
    select v_masina into vv_masina from masinaRepository where id = 1;

    return vv_masina.culoare;
end;

/


create or replace function getMarca return varchar as 
    vv_masina TMasina;
begin
    select v_masina into vv_masina from masinaRepository where id = 1;

    return vv_masina.marca;
end;
