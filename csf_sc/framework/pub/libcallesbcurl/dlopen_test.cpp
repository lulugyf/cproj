#include <iostream>
#include <stdio.h>
#include <dlfcn.h>
#include <sys/time.h>

/*
readme :
代码 通过 dlopen 直接打开 调用函数
编译办法:
g++ -g -o dlopen_test dlopen_test.cpp -ldl -L/tp/esb/csf/run/solib  -lutype  


xlC_r -g -q64 -brtl -G -o libCallESBWS.so  demo.cpp soapsDynSvcSoap11BindingProxy.cpp soapC.cpp stdsoap2.cpp
xlC_r -g -q64 -brtl -o dlopen_test dlopen_test.cpp -ldl 
*/


//using namespace std;
int main()
{
    double t1,t2;
	
   
    using std::cout;
    using std::cerr;

    void* handle = dlopen("./libCallESBWS.so", RTLD_LAZY);

    if (NULL == handle)
    {
        cerr << "Cannot open library: " << dlerror() << '\n';
        return 1;
    }

    typedef void (*func_ptr)();
    dlerror();
    func_ptr hello = (func_ptr) dlsym(handle, "hello");
    const char *dlsym_error = dlerror();
    
    if (dlsym_error)
    {
        cerr << "Cannot load symbol 'hello': " << dlsym_error <<'\n';
        dlclose(handle);
        return 1;
    }

    hello();
    dlclose(handle);
    cout << "OK"<<"\n";
    return 0;
    
}
