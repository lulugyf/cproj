CREATE OR REPLACE function crypt_data(src in varchar2, ende in varchar2) return varchar2 is
  ret varchar2(255);
  i   number;
  len number;
  j   number;
  key number;
begin
  ret := '++';
  len := length(src);
  key := 13;

  if ende = '1' then
  	if substrb(src,1,2) <> '++' then
       -- encode
       i := 0;
       while i < len loop
           j := ascii(substr(src,i+1,1))+key;
           if j > 127 and j < 256 then
              j := j - 128;
           end if;
           ret := concat(ret, chr(j));
           i := i+1;
       end loop;
    else
    	  ret := src;
    end if;
  else
  	if substrb(src,1,2) = '++' then
        -- decode
        i := 0;
        ret := '';
        while i < len loop
            j := ascii(substr(src,i+3,1));
            if j <= key then
               j := j - key + 128;
            else
               j := j - key;
            end if;
            ret := concat(ret, chr(j));
            i := i+1;
        end loop;
    else
    	  ret := src;
    end if;
  end if;
  return(trim(substr(ret,1,255)));
end crypt_data;
/
