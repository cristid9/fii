SET SERVEROUTPUT ON;

DECLARE
  v_id1 VARCHAR(255) := 3;
  v_id2 VARCHAR(255) := 4;
  
  v_q_user1 NUMBER(10, 0);
  v_q_user2 NUMBER(10, 0);
  v_a_user1 NUMBER(10, 0);
  v_a_user2 NUMBER(10, 0);
  
BEGIN
  -- collecting num of questions for each user
  SELECT COUNT(id)
  INTO v_q_user1
  FROM questions
  WHERE user_id = v_id1;
  
  SELECT COUNT(id)
  INTO v_q_user2
  FROM questions
  WHERE user_id = v_id2;
  
  IF ( v_q_user1 = v_q_user2 )
  THEN
  
    -- collectng number of answers for each user
    SELECT COUNT(id)
    INTO v_a_user1
    FROM answers
    WHERE user_id = v_id1;
      
    SELECT COUNT(id)
    INTO v_a_user2
    FROM answers
    WHERE user_id = v_id2;
    
    IF ( v_a_user1 > v_a_user2 ) 
    THEN
      DBMS_OUTPUT.PUT_LINE('USERUL 1  A RASPUNS LA MAI MULTE PROBLEME');
    ELSIF ( v_a_user1 < v_a_user2 ) 
    THEN
      DBMS_OUTPUT.PUT_LINE('USERUL 2 A RASPUNS LA MAI MULTE PROBLEME');
    ELSE
      DBMS_OUTPUT.PUT_LINE('AMBII UTILIZATORI AU RASPUNS L ACELASI NR DE INTREBARI');
    END IF;
    
  ELSIF ( v_q_user1 > v_q_user2 )
  THEN
    DBMS_OUTPUT.PUT_LINE('USERUL 1 A PUS MAI MULTE INTREBARI');
  ELSE
    DBMS_OUTPUT.PUT_LINE('USERUL 2 A PUS MAI MULTE INTREBARI');
  END IF;
END;
