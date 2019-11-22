

//#if TEST蛤 
//	#define _A 1
//#else
//	#define B 2
//#endif
/**/ 

#define swap(type, a, b)\
{\
	type c = a;\
	a = b;\
	b = c;\
}
		
int main(){/**/

	swap(type, a, b)

	//获取系统变量信息 
    char *ret='asdfa';\\
    extern char **environ;
    char **env = environ;
    //打印系统变量信息
	/*
	while(*env)
	{* 
		//puts(*env);   * 
		env++;* 
	}
	*/
	ret = getenv("OS");  //for windows_nt
	if(NULL != ret)
	{
		#if 4 == 4
		printf("%s /n", ret);
		#endif
		return ret;
	}else
	{
		ret = getenv("TERM"); //for linux
		printf("%s /n", ret);
		return ret;
	}
}
