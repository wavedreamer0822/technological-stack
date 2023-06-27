openMP
- 通过线程实现并行化
- 统一内存访问（openMP、Pthread）、非统一（MPI）
- fork：主线程创建一组并行化线程
- Join：同步与终止
- #pragma omp 指令 子句 子句 子句。。。
- #pragma omp parallel
```c
#include<omp.h>
#include<iostream>
using namespace std;
int main()
{
#pragma omp parallel
	{
		cout << "Hello, world!" << endl;
	}
}
```
- #pragma omp parallel num_threads(5) //控制线程个数
```c
#include<omp.h>
#include<iostream>
using namespace std;
int main()
{	
#pragma omp parallel num_threads(5)
	{
		
		cout << "Hello, world!" << endl;
	}
}
//或者用函数控制
#include<omp.h>
#include<iostream>
using namespace std;
int main()
{
	omp_set_num_threads(2);
#pragma omp parallel
	{
		
		cout << "Hello, world!" << endl;
	}
}
```
- #pragma omp for
```c
#include<omp.h>
#include<iostream>
using namespace std;
int main()
{
	omp_set_num_threads(2);
#pragma omp parallel
	{
#pragma omp for
		for(int i=0;i<4;i++)
		 cout << omp_get_thread_num() << endl;
	}
}

//直接把for 写在parallel后面
#pragma omp parallel for   //注意变量的使用！！！是否是全局变量
```
```c
#include <iostream>
#include <omp.h>
int main(){
    int sum = 0;
    int a[10] = {1,2,3,4,5,6,7,8,9,10};
    int coreNum = omp_get_num_procs();//获得处理器个数
    int* sumArray = new int[coreNum];//对应处理器个数，先生成一个数组
    for (int i=0;i<coreNum;i++)//将数组各元素初始化为0
        sumArray[i] = 0;
#pragma omp parallel for
    for (int i=0;i<10;i++)
    {
        int k = omp_get_thread_num();//获得每个线程的ID
        sumArray[k] = sumArray[k]+a[i];
    }
    for (int i = 0;i<coreNum;i++)
        sum = sum + sumArray[i];
    std::cout<<"sum: "<<sum<<std::endl;
    return 0;
}
```

- schedule子句进行for循环调度(schedule(type,size))
- type:static,dynamic,guided,runtime


- sections指令
- 用sections把不同区域交给不同的线程执行
```c
#include<omp.h>
#include<iostream>
using namespace std;
int main()
{
	omp_set_num_threads(3);
#pragma omp parallel sections
	{
#pragma omp section
		{
			cout <<omp_get_thread_num();
		}
#pragma omp section
		{
			cout << omp_get_thread_num();
		}
#pragma omp section
		{
			cout << omp_get_thread_num();
		}
	}
}
```

- Single指令
```c
int main()
{
	omp_set_num_threads(4);
#pragma omp parallel
	{
#pragma omp single
		{
			cout << "single thread=" << omp_get_thread_num()<<endl;
		}
		cout << omp_get_thread_num() << endl;
	}
		
}
```
- Private
```c++
int i;
float *a,*b,*c,tmp;
#pragma omp parallel for private(tmp)
for(int i=0;i<N;i++)
{
	tmp=a[i]/b[i];
	c[i]=tmp*tmp;
}
```
- firstprivate  每个线程第一个循环继承共享变量的值
- lastprivate  私有变量会在**负责最后一个iterator的线程离开循环**出去的时候赋值给共享变量
- Single 代码只有一个线程执行 不使用nowait时，其他线程会等待
- sections选项 每个section被一个线程执行，一个线程可能执行多个section
```c
#pragma omp parallel sections
	{
#pragma omp section
		{
			cout << omp_get_thread_num() << endl;
			//ofstream ofs("")
		}
#pragma omp section
		{
			cout << omp_get_thread_num() << endl;
		}
#pragma omp section
		{
			cout << omp_get_thread_num() << endl;
		}
#pragma omp section
		{
			cout << omp_get_thread_num() << endl;
		}
#pragma omp section
		{
			cout << omp_get_thread_num() << endl;
		}
	}
```
- reduction（归并） 提供一个私有变量拷贝并且初始化该变量，最后出口会根据规则更新，计算成一个共享变量，**不是覆盖，会根据原有共享变量的值**
```c
#pragma omp parallel num_threads(5) reduction(+:j)
{
	# pragma omp sections
	{
		# pragma omp section
		{
			int my_rank=omp_get_thread_num();
			int thread_count=omp_get_num_threads();
			j=j+10;
			print...
		}
		# pragma omp section
		{
			int my_rank=omp_get_thread_num();
			int thread_count=omp_get_num_threads();
			j=j+20;
			print...
		}
	} 
}
printf("j=%d\n",j);
```

- 同步与互斥
- Barrier # pragma omp barrier  **for和single自带barrier，nowait可以破坏**
```c
#pragma omp parallel num_threads(2)
	{
		int my_rank = omp_get_thread_num();
		int thread_count = omp_get_num_threads();
		printf("hi from %d\n", my_rank);
#pragma omp barrier
		{
			//if (my_rank == 0)
			//{
			//	printf("%d threads say hi\n", thread_count);
			//}
			cout << "111" << endl;
		}

	}
```
- 竞争
- #pragma omp critical 接下来一段代码同一时间段只有一个线程执行
- 一般用来修改共享变量
- atomic 特殊情况下使用，只会应用于一条指令
- 1、自增或者自减的情况下使用j++ j--
- 2、在二元操作数的情况下使用a+b 
- Schedule
[***OpenMP总览***](https://zhuanlan.zhihu.com/p/399591700) 
[***OpenMP官方教程***](https://www.hz-bin.cn/OpenMP)


[***OpenMPI官方文档***](https://www.open-mpi.org/doc/current/)


[***MPI教程***](https://www.codingame.com/playgrounds/349/introduction-to-mpi/hello-world)