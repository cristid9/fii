set serveroutput on;

-- functiile din temele precedente
CREATE INDEX u_id_idx ON answers(user_id);

CREATE OR REPLACE FUNCTION is_hardworking_student(p_student_id USERS.ID%TYPE) 
RETURN CHAR  AS
  v_total_answers NUMBER(10, 0);
  v_right_answers NUMBER(10, 0);
BEGIN
  v_total_answers := 0;
  v_right_answers := 0;

  FOR v_row IN (select * FROM answers WHERE user_id=p_student_id) LOOP
    IF v_row.solved = 1 THEN
      v_right_answers := v_right_answers + 1;
    END IF;
    
    v_total_answers := v_total_answers + 1;
  END LOOP;

  IF (v_total_answers / 2) > v_right_answers THEN
    RETURN 0;
  ELSE
    RETURN 1;
  END IF;
END;
/
CREATE INDEX q_id_idx ON answers(question_id, solved);
/
CREATE OR REPLACE FUNCTION get_relevance(p_question_id QUESTIONS.ID%TYPE)
RETURN ANSWERS.ID%TYPE AS
  v_num_displays ANSWERS.ID%TYPE;
  v_right_answers_count ANSWERS.ID%TYPE;
  v_answers_count ANSWERS.ID%TYPE;
BEGIN

  v_right_answers_count := 0;
  v_answers_count := 0;

  SELECT asked INTO v_num_displays FROM questions 
    WHERE id=p_question_id;
    
  FOR v_row IN (SELECT * FROM ANSWERS WHERE question_id=p_question_id 
    AND is_hardworking_student(user_id)=1) LOOP
    
    IF v_row.solved = 1 THEN
      v_right_answers_count := v_right_answers_count + 1;
    END IF;
    
    v_answers_count := v_answers_count + 1;
  
  END LOOP;
  
  IF v_num_displays < 20 THEN
    RETURN 0;
  END IF;
  
  IF v_right_answers_count < (0.3 * v_num_displays) THEN
    RETURN 0;
  END IF;
  
  IF v_right_answers_count > (0.9 * v_num_displays) THEN
    RETURN 0;
  END IF;
  
  RETURN v_num_displays;
END;
/
begin
  dbms_output.put_line('marius.danilas value is: ' || is_hardworking_student(250));
end;


/
--drop table feature_questions;

CREATE TABLE feature_questions ( 
    ID NUMBER(10, 0),
    CHAPTER_ID NUMBER(10, 0),
    USER_ID NUMBER(10, 0),
    QUESTION CLOB,
    ANSWER CLOB,
    ASKED NUMBER(10, 0),
    SOLVED NUMBER(10, 0),
    REPORTED NUMBER(10, 0),
    REPORT_RESOLVED NUMBER(10, 0),
    CREATED_AT TIMESTAMP(6),
    UPDATED_AT TIMESTAMP(6)
);
/
CREATE OR REPLACE PACKAGE homework2 AS
    null_relevance exception;
    PRAGMA EXCEPTION_INIT (null_relevance, -20001);

    FUNCTION handle_new_question(p_id NUMBER) RETURN NUMBER;
    FUNCTION populate_new_table RETURN NUMBER;
END homework2;
/
CREATE OR REPLACE PACKAGE BODY homework2 AS
    FUNCTION handle_new_question(p_id NUMBER)
    RETURN NUMBER AS
        retval NUMBER;
    BEGIN
    
    
        retval := get_relevance(p_id);
        IF retval = 0 THEN
            raise_application_error(-20001, 
                'Intrebarile cu relvanta nula nu sunt suportate!');
        ELSE 
            INSERT INTO feature_questions 
                (
                    ID,
                    CHAPTER_ID,
                    USER_ID,
                    QUESTION,
                    ANSWER,
                    ASKED,
                    SOLVED,
                    REPORTED,
                    REPORT_RESOLVED,
                    CREATED_AT, 
                    UPDATED_AT 
                )
            SELECT 
                ID,
                CHAPTER_ID,
                USER_ID,
                QUESTION,
                ANSWER,
                ASKED,
                SOLVED,
                REPORTED,
                REPORT_RESOLVED,
                CREATED_AT, 
                UPDATED_AT 
            FROM questions q WHERE q.id = p_id;  
        END IF;
        
        return 1; -- intrebarea inserata
    END;
    
    FUNCTION populate_new_table RETURN NUMBER AS 
        idx NUMBER(10, 0) := 0;
        q_counter NUMBER(10, 0) := 1;
        temp NUMBER;
    BEGIN
        LOOP
            BEGIN
                temp := homework2.handle_new_question(q_counter);
                IF temp = 1 THEN 
                    idx := idx + 1;
                END IF;
                
            EXCEPTION 
                WHEN null_relevance THEN
                    dbms_output.put_line('ERR1');
                WHEN OTHERS THEN
                    dbms_output.put_line('ERR2');
            END;
            
            q_counter := q_counter + 1;
           
            EXIT WHEN idx = 1000;
        END LOOP;
        
        return 1;
    END;
END homework2;
/
DECLARE
    tmp NUMBER;
BEGIN
    tmp := homework2.populate_new_table();
END;
/
select count(*) from feature_questions;
