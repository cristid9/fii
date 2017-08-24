set serveroutput on;

CREATE OR REPLACE TYPE StudentOfGradeN AS OBJECT 
(
    v_username VARCHAR(255),
    v_userId NUMBER(10, 0),
    v_definingMark NUMBER(10, 0),
    v_wasBuiltSuccessfully NUMBER(10, 0),
    v_definigMark NUMBER(10, 0),
    
    CONSTRUCTOR FUNCTION StudentOfGradeN(p_username VARCHAR, p_definingMark NUMBER)
        RETURN SELF AS RESULT,
    MEMBER FUNCTION getNumberOfLowReportQ RETURN NUMBER,
    MEMBER FUNCTION getBuiltStatus RETURN NUMBER,
    MEMBER FUNCTION getTopAnswerer RETURN VARCHAR,
    ORDER MEMBER FUNCTION compare (against StudentOfGradeN) RETURN NUMBER
) NOT FINAL;

/

CREATE OR REPLACE TYPE BODY StudentOfGradeN AS
    CONSTRUCTOR FUNCTION StudentOfGradeN(p_username VARCHAR, p_definingMark NUMBER)
    RETURN SELF AS RESULT AS
        v_answers NUMBER(10, 0);
    BEGIN
        IF p_definingMark < 5 THEN
            self.v_wasBuiltSuccessfully := 0;
            return;
        END IF;
    
        select id into v_userId from users where username = p_username;
        
        select count(id) 
        into v_answers 
        from answers 
        where 
            solved = 1 and
            user_id = v_userId;
            
        IF (p_definingMark = 10 AND v_answers >= 24) THEN
            self.v_wasBuiltSuccessfully := 1;
        ELSIF (p_definingMark = 9 AND v_answers >= 18) THEN
            self.v_wasBuiltSuccessfully := 1;
        ELSIF (p_definingMark = 8 AND v_answers >= 15) THEN
            self.v_wasBuiltSuccessfully := 1;
        ELSIF (p_definingMark = 7 AND v_answers >= 13) THEN
            self.v_wasBuiltSuccessfully := 1;
        ELSIF (p_definingMark = 6 AND v_answers >= 12) THEN
            self.v_wasBuiltSuccessfully := 1;
        ELSIF (p_definingMark = 5 AND v_answers >= 5) THEN
            self.v_wasBuiltSuccessfully := 1;
        ELSE
            self.v_wasBuiltSuccessfully := 0;
        END IF;
        
        self.v_definingMark := p_definingMark;
        
        return;
    END;
    
    MEMBER FUNCTION getBuiltStatus RETURN NUMBER AS 
    BEGIN
        RETURN v_wasBuiltSuccessfully;
    END;
    
    MEMBER FUNCTION getNumberOfLowReportQ RETURN NUMBER AS
        v_retval NUMBER;
    BEGIN
    
        IF (self.v_wasBuiltSuccessfully = 0) THEN
            RETURN -1;
        END IF;
    
        --  get number of valid questions put by this user in the system
        SELECT COUNT(*) 
        INTO v_retval
        FROM QUESTIONS
        WHERE USER_ID = self.v_userId 
            AND REPORTED < 10;
    
        return v_retval;
    END;

    MEMBER FUNCTION getTopAnswerer RETURN VARCHAR AS
        v_answererId NUMBER(10, 0);
        v_answererUsername VARCHAR(255);
    BEGIN
    
        IF (self.v_wasBuiltSuccessfully  = 0) THEN
            return 'build failed'; -- exception should be thrown, I know
        END IF;
    
        select user_id 
        into v_answererId
        from answers
        where 
            solved = 1 AND
            question_id IN (select id from questions where user_id = self.v_userId)
        group by user_id
        having count(user_id) = (
            select max(count(user_id))
            from answers 
            where 
                question_id IN (select id from questions where user_id = self.v_userId) AND 
                solved=1
            group by user_id
        );
        
        select username into v_answererUsername from users where id = v_answererId;
        
        return v_answererUsername;
    END;

    ORDER MEMBER FUNCTION compare (against StudentOfGradeN) RETURN NUMBER AS
    BEGIN
        IF against.getBuiltStatus = 0 THEN
            return 1;
        END IF;
        
        IF self.v_definingMark < against.v_definingMark THEN
            return -1;
        ELSIF self.v_definingMark = against.v_definingMark THEN
            return 0;
        END IF;

        return 1;
    END;
END;

/

CREATE or replace TYPE SOGNContainingInName UNDER StudentOfGradeN (
    v_substring VARCHAR(255),
    overriding member FUNCTION getNumberOfLowReportQ RETURN NUMBER,
    member procedure setSubstring(fragment varchar),
    member procedure printN(dummy varchar),
    member procedure printN(dummy number)
);

/

create or replace type body SOGNContainingInName as
    member procedure printN(dummy varchar) as
    begin
        dbms_output.put_line('un string');
    end;
    
    member procedure printN(dummy number) as 
    begin
        dbms_output.put_line('un numar');
    end;


    overriding member function getNumberOfLowReportQ return number AS
        v_answererId NUMBER(10, 0);
        v_answererUsername VARCHAR(255);
    BEGIN
    
        select user_id 
        into v_answererId
        from answers
        where 
            solved = 1 AND
            question_id IN (select id from questions where user_id = self.v_userId)
        group by user_id
        having count(user_id) = (
            select max(count(user_id))
            from answers 
            where 
                question_id IN (select id from questions where user_id = self.v_userId) AND 
                solved=1
            group by user_id
        );
        
        select username into v_answererUsername from users where id = v_answererId and username like ('%' || self.v_substring|| '%');
        
        return v_answererUsername;
    END;
    
    member procedure setSubstring(fragment varchar) as
    begin
        self.v_substring := fragment;
    end;
    
end;

/

declare
    danila StudentOfGradeN;
    lowQ NUMBER;
    builtStatus NUMBER;
    topAnswerer VARCHAR(255);
    
BEGIN
    danila := StudentOfGradeN('marius.danila', 7);
    
    topAnswerer := danila.getTopAnswerer;
    lowQ := danila.getNumberOfLowReportQ;
    builtStatus := danila.getBuiltStatus;

    DBMS_OUTPUT.PUT_LINE('The build status of this object is ' || builtStatus);
    DBMS_OUTPUT.PUT_LINE('The top answerer for this user is ' || topAnswerer);
    DBMS_OUTPUT.PUT_LINE('The lowest report question for this user is ' || lowQ);
END;
