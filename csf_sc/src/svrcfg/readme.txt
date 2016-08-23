本工具使用python解析配置文件， 自动生成server代码并编译生成
by guanyf 2013-8-2


工具由两个文件组成：
1. makeserver.py:  工具主程序， python脚本， 用法如下：
	python makeserver.py server1 server2 ...
2. makeserver.mk:  通用的编译server的makefile文件， makeserver.py 使用


Server配置文件， 文件名格式： ${ServerName}.yaml， 一个配置文件对应一个Server程序

配置文件使用yaml格式，包括  SERVICE，  LIBS， EXTRA(可选) 项， 格式参考 如下:
#######  example config file begin
SERVICE:
 #servicename  bpname    DBLabel     ConnectType
 # 注意: 列间不能使用 <tab> 分隔
 - sQDual     cQDual    LABELDBCHANGE   1
 - sDynSvc    pDynSvc   LABELDBCHANGE   1

LIBS:
 - -ltestbp1
 - -ltestbp2

EXTRA:  #下面是代码片段， 直接放到server.cpp中的， 注意不要在内容中使用<tab>符号，>之后， 使用空格开始的都属于本配置项， 不能使用<tab>开头
>
  #include "libstaticorder.h"
  
  int tpsvrinit(int argc, char *argv[])
  {
      return BOrderTuxInit(argc, argv, LABELDBCHANGE, "RJ605");
  }
  
  void tpsvrdone()
  {
      BOrderTuxDone(LABELDBCHANGE);
  }

############### example config file end

注： 
  1. Server中调用的 bp/bc 会自动生成对应的函数申明， 无需额外编写头文件
  2. 生成的 Server源代码中， 只加了一个头文件 #include "allBCP.h"
  3. ConnectType参数， 1为长连接；  0为短连接
  4. EXTRA配置项内容可选， 代码直接读入到server.cpp文件中， 不做额外处理
  5. 配置文件如果不是utf-8编码， 不能有中文字符, 配置内容中不要有<tab>字符



