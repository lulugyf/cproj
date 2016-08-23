CREATE OR REPLACE FUNCTION decrypt_data (p_text VARCHAR2)
   RETURN varchar2
IS
   v_text   VARCHAR2 (200);
BEGIN

   RETURN RTRIM(substr(crypt_data(p_text,'0'),1,255), CHR (0));

   EXCEPTION
     WHEN NO_DATA_FOUND THEN  NULL;
END;
/
