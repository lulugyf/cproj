
import cx_Oracle

def main():
    co = cx_Oracle.connect('offon/Crmpd!06@onoffdb')
    cur = co.cursor()

    cur.execute('SELECT command_code,order_code,order_type,serial FROM ccmdtoorder WHERE hlr_code=:v1 ORDER BY command_code,serial', ('hbp',))
    f = file('ccmdtoorder.txt', 'w')
    while 1:
        r = cur.fetchone()
        if r is None:
            break
        f.write('%s %s %c %d\n'%(r[0].strip(), r[1].strip(), r[2][0], r[3]) )
    cur.close()
    f.close()
    co.close()

main()
