package test.a;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;

/**
 * Created by guanyf on 5/3/2017.
 */
public class Exec {
    static class Proc{
        Process p;
        BufferedReader in;
        BufferedWriter out;
        void close() {
            try{out.write("quit\n");
            }catch(Exception ex){}

            try{out.close();
            }catch(Exception ex){}
            try{in.close();
            }catch(Exception ex){}
            try{p.destroy();
            }catch(Exception ex){}
            p = null;
            in = null;
            out = null;
        }
        private String pipe(String msg) {
            if(out == null)
                return "ERROR: terminated";
            String ret;
            try {
                out.write( msg + "\n" );
                out.flush();
                ret = in.readLine();
                return ret;
            }
            catch (Exception err) {
                err.printStackTrace();
            }
            return "";
        }
        String encrypt(String key, String src) {
            String ret = pipe("en "+key+" " + src);
            if(ret.startsWith("OUT: "))
                return ret.substring(5).trim();
            else if(ret.startsWith("ERROR: ")) {
                //throw new Exception(ret.substring(7).trim());
                System.err.println(ret);
                return "";
            }else
                return null;
        }
        String decrypt(String key, String src) {
            String ret = pipe("de "+key+" " + src);
            if(ret.startsWith("OUT: "))
                return ret.substring(5).trim();
            else if(ret.startsWith("ERROR: ")) {
                //throw new Exception(ret.substring(7).trim());
                System.err.println(ret);
                return "";
            }else
                return null;
        }
    }
    private String cmd;
    private Proc p;
    public Exec(String cmd){
        this.cmd = cmd;
    }

    private Proc makeProc() {
        Proc e = new Proc();
        try {
            Process p = Runtime.getRuntime().exec(cmd);
            BufferedReader in = new BufferedReader(new InputStreamReader(p.getInputStream()));
            BufferedWriter out = new BufferedWriter(new OutputStreamWriter(p.getOutputStream()));
            e.p = p;
            e.in = in;
            e.out = out;
        }catch(Exception ex){
            ex.printStackTrace();
            return null;
        }
        return e;
    }

    public String en(String key, String src) {
        if(p == null)
            p = makeProc();
        String ret = p.encrypt(key, src);
        if(ret == null){
            p.close();
            p = null;
        }
        return ret;
    }
    public String de(String key, String src) {
        if(p == null)
            p = makeProc();
        String ret = p.decrypt(key, src);
        if(ret == null){
            p.close();
            p = null;
        }
        return ret;
    }
    public void close() {
        if(p != null) {
            p.close();
            p = null;
        }
    }

    public static void main(String[] args) {
        String key = "bossboss";
        String plain = "123321";
        String out = null;
        int count = 1;

        if(args.length > 0){
            count = Integer.parseInt(args[0]);
        }

        Exec e = new Exec("./enPasswd");

        long t1 = System.currentTimeMillis();
        for(int i=0; i<count; i++) {
            String cipher = e.en(key, plain);
            out = e.de(key, cipher);
        }
        long t2 = System.currentTimeMillis();
        System.out.println("done, time: " + ((t2-t1)/1000) + " s");

        e.close();
    }


}


/*

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include "des.h"

extern char * pubEncrypt(const char *src, const int inlen, int *outlen, char *key);
extern char * pubDecrypt(const char *src, int inlen, int *outlen, char *key);

int main(int argc, char **argv) {
    char line[1024], tag[32], key[32], source[128], *out;
    int r, outlen;
    while(1) {
        fgets(line, sizeof(line), stdin);
        if(strncmp(line, "quit", 4) == 0)
            break;
        r = sscanf(line, "%s %s %s", tag, key, source);
        if(r != 3){
            printf("ERROR: invalid input\n");
            fflush(stdout);
            continue;
        }
        if(strcmp(tag, "en") == 0){
            out = pubEncrypt(source, strlen(source), &outlen, key);
            if(out == NULL){
                printf("ERROR: encrypt failed\n");
            }else{
                printf("OUT: %s\n", out);
                free(out);
            }
            fflush(stdout);
        }else if(strcmp(tag, "de") == 0){
            out = pubDecrypt(source, strlen(source), &outlen, key);
            if(out == NULL){
                printf("ERROR: decrypt failed\n");
            }else{
                printf("OUT: %s\n", out);
                free(out);
            }
            fflush(stdout);
        }
    }
    return 0;
}


 */
