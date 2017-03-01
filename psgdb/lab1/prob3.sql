set serveroutput on;

/*
   Gasiti userul cu cel mai mare numar de litere in componenta numelui de familie
 */

set serveroutput on; -- gen sa vezi rezultatul

declare 
    v_username users.username%type;
    v_m_intrebari int;
    v_reporturi int;
    v_name users.name%type;

-- vezi tema
/* <<bloc_principal>>
   declare
   v_name varchar2 := 'Gigi';
   begin
   dbms_output...
   <<subbloc>>
   delcare
   v_name varchar := 'Mihai';
   begin
   dbms....
 */

begin
    SELECT substr(name, instr(name, ' '))
    INTO v_name
    FROM users 
    WHERE length(substr(name, instr(name, ' '))) 
    IN (select max(length(substr(name, instr(name, ' '))))
            from users) and rownum = 1;

    dbms_output.put_line
    ('valoare este ' || v_name || ' ' ||length(v_name));
end;
