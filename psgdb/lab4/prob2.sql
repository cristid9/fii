SET SERVEROUTPUT ON;

DECLARE
  v_foo VARCHAR(255);
  v_bar VARCHAR(255);
BEGIN
  v_foo := 'BLOC 1';
  v_bar := 'BLOC 1';
  
  DECLARE
    v_foo VARCHAR(255);
  BEGIN
    v_foo := 'BLOC 2';
    v_bar := 'BLOC 2';
    
    DECLARE
      v_foo VARCHAR(255);
    BEGIN
      v_foo := 'BLOC 3';
      v_bar := 'BLOC 3';
      DBMS_OUTPUT.PUT_LINE(v_foo); -- BLOC 3
    END;
    
    DBMS_OUTPUT.PUT_LINE(v_foo); -- BLOC 2
  END;
  DBMS_OUTPUT.PUT_LINE(v_foo); -- BLOC 1
  DBMS_OUTPUT.PUT_LINE(v_bar); -- BLOC 3
END;

