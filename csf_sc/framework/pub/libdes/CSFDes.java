package csf.util;
/*
��Ҫ�� run/framework/pub/libdes Ŀ¼�½�������Ĳ���
1. ���ȱ��� CSFDes.java:
	javac -d . CSFDes.java
2. ����ͷ�ļ�
	javah -classpath . csf.util.CSFDes
	
3. ���� libdesjni.so
	gcc -m64 -fPIC -I. -I`find /usr/lib/gcc -name jni.h|head -1|xargs dirname` -c CSFDes.cpp -o CSFDes.o
	gcc -m64 -shared -o libdesjni.so CSFDes.o libDesMac.a
   
4. ����java������Ҫͨ��-Djava.library.path=?? ��ָ�� libdesjni.so �ļ���λ��


���⣬ cbc_end.c ������������2�������� ���ڼӽ��ܵ�����û�г������ƣ� ���÷�ʽ���б仯�������ֹ��ͷŷ���ֵ���ڴ�
extern "C" {
	char * pubEncrypt(const char *src, const int inlen, int *outlen, char *key);
	char * pubDecrypt(const char *src, const int inlen, int *outlen, char *key);
}

*/
// /usr/bin/java -Djava.library.path=/crmpdpp/csf/csf_sc/run/framework/pub/libdes -cp . csf.util.CSFDes en kkkk 'hello worldasdlkfjadsfk'
// /usr/bin/java -Djava.library.path=/crmpdpp/csf/csf_sc/run/framework/pub/libdes -cp . csf.util.CSFDes de kkkk ???

public class CSFDes {

	static { System.loadLibrary("desjni"); }

	native public static byte[] encrypt(byte[] src, byte[] key);
	native public static byte[] decrypt(byte[] src, byte[] key);
	
	public static void main(String[] args){
		if(args.length < 3){
			System.out.println("Usage: CSFDes <en|de> <key> <src>\n");
			return;
		}
		byte[] key = args[1].getBytes();
		byte[] src = args[2].getBytes();
		byte[] out = null;
		if("en".equals(args[0])){
			out = encrypt(src, key);
		}else if("de".equals(args[0])){
			out = decrypt(src, key);
		}
		if(out != null){
			System.out.println(new String(out));
		}else{
			System.out.println("failed");
		}
	
	}

}
