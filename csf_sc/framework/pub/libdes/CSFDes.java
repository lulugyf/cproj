package csf.util;
/*
需要在 run/framework/pub/libdes 目录下进行下面的操作
1. 首先编译 CSFDes.java:
	javac -d . CSFDes.java
2. 生成头文件
	javah -classpath . csf.util.CSFDes
	
3. 编译 libdesjni.so
	gcc -m64 -fPIC -I. -I`find /usr/lib/gcc -name jni.h|head -1|xargs dirname` -c CSFDes.cpp -o CSFDes.o
	gcc -m64 -shared -o libdesjni.so CSFDes.o libDesMac.a
   
4. 运行java程序需要通过-Djava.library.path=?? 来指定 libdesjni.so 文件的位置


另外， cbc_end.c 中新增了下面2个函数， 对于加解密的内容没有长度限制， 调用方式上有变化，必须手工释放返回值的内存
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
