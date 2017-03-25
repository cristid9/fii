/* Problema 1 */
set serveroutput on;

DECLARE
  v_user_input VARCHAR2(255);
  v_no_students NUMBER;
  v_random_index NATURAL;
  
  v_id NUMBER(10, 0);
  v_tmp_full_name VARCHAR(255);
  v_family_name VARCHAR(255);
  v_first_name VARCHAR(255);
  v_no_reported_questions NUMBER(10, 0);
  v_tmp NUMBER(10, 0);
  
BEGIN
  v_user_input := '&x';
 
  -- getting count
  SELECT COUNT(id) 
  INTO v_no_students
  FROM users
  WHERE lower(name) LIKE ('%' || lower(v_user_input) || '%');
  
  IF v_no_students = 0 THEN
    DBMS_OUTPUT.PUT_LINE('No matching result');
  
  ELSE
    -- generating the random number
    SELECT dbms_random.value(1, v_no_students) num
    INTO v_random_index 
    FROM dual;
    
    SELECT id, rownum
    INTO v_id, v_tmp
    FROM users
    WHERE lower(name) LIKE ('%' || lower(v_user_input) || '%')
    GROUP BY id, rownum
    HAVING rownum = v_random_index;
    
    -- retrieving the desired data from the db
    SELECT name, 
    (
      SELECT COUNT(q.id)
      FROM questions q
      WHERE q.user_id = v_id
    )
    INTO v_tmp_full_name, v_no_reported_questions
    FROM users
    WHERE id = v_id;
    
    v_first_name := INITCAP(regexp_substr(v_tmp_full_name, '[^ ]+ '));
    v_family_name := UPPER(regexp_substr(v_tmp_full_name, ' [^ ]+'));
    
    DBMS_OUTPUT.PUT_LINE('IDul este ' || v_id );  
    DBMS_OUTPUT.PUT_LINE('Numele de familie: ' || v_family_name);
    DBMS_OUTPUT.PUT_LINE('Prenumele: ' || v_first_name);
    DBMS_OUTPUT.PUT_LINE('Nr de intrebrai cu <5 reporturi: ' || v_no_reported_questions);
  END IF;
END;
