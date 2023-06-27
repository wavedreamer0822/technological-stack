#include "mpi.h"
#include <stdio.h>
#include<iostream>
#include <iomanip>
#include<Windows.h>
using namespace std;
//double f(double);
//double f(double x)
//{
//    return (4.0 / (1.0 + x * x));
//}
//int main(int argc, char* argv[])
//{
//    int myid, numprocs;
//    int n, i;
//    double mypi, pi;
//    double h, sum, x;
//    MPI_Init(&argc, &argv);
//    MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
//    MPI_Comm_rank(MPI_COMM_WORLD, &myid);
//    printf("Process %d of %d.\n", myid, numprocs);
//    n = 100;
//    h = 1.0 / (double)n;
//    sum = 0.0;
//    for (i = myid + 1; i <= n; i += numprocs)
//    {
//        x = h * ((double)i - 0.5);
//        sum += f(x);
//    }
//    mypi = h * sum;
//    MPI_Reduce(&mypi, &pi, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
//    if (myid == 0)
//    {
//        printf("The result is %.10f.\n", pi);
//    }
//    MPI_Finalize();
//}






//对等模式
//int main(int argc, char* argv[])
//{
//	int steps = 10;                        // 迭代次数
//	const int totalsize = 16;              // 矩阵维度
//	const int mysize = 4;                  // MPI 分块数目, 4 个 processes
//	double A[totalsize][mysize + 2] = { 0 }; // all proc data matrix
//	double B[totalsize][mysize + 2] = { 0 }; // all proc buffer matrix
//	int begin_col = 1;                     // all proc 矩阵的起始列
//	int end_col = mysize + 1;              // all proc 矩阵的结束列
//	int myid = 0, numprocs = 0;
//	int left = 0, right = 0;
//	int tag1 = 3, tag2 = 4; // MPI 发送接收 tag
//	MPI_Status status;      // MPI 状态
//	cout << argc << endl;
//	cout << argv[0] << endl;
//	//cout << argc << endl;
//	MPI_Init(&argc, &argv);
//	double start = MPI_Wtime();
//	// MPI 初始化
//	//  int thread_support = 0;
//	// MPI_Init_thread(&argc, &argv, MPI_THREAD_MULTIPLE, &thread_support);
//	// 获取rank
//	MPI_Comm_rank(
//		MPI_COMM_WORLD /*MPI_Comm comm*/,
//		&myid /*int* size*/
//	);
//	//获取进程数
//	MPI_Comm_size(
//		MPI_COMM_WORLD, /*MPI_Comm comm*/
//		&numprocs       /* int* size */
//	);
//	// 打印进程信息
//	std::cout << "Process " << myid << " of " << numprocs << " is alive!" << std::endl;
//	// 4 proc 矩阵赋初值, 左右额外两列用于交换
//	if (myid == 0)
//	{
//		cout << "id==0" << endl;
//	}
//	for (int j = 0; j < mysize + 2; j++)
//	{
//		for (int i = 0; i < totalsize; i++)
//		{
//			A[i][j] = 0.0;
//		}
//	}
//	// proc 0 额外初值
//	if (myid == 0)
//		for (int i = 0; i < totalsize; i++)
//		{
//			A[i][1] = 8.0;
//		}
//	// proc 3 额外初值
//	if (myid == 3)
//		for (int i = 0; i < totalsize; i++)
//		{
//			A[i][mysize] = 8.0;
//		}
//	// proc all 赋初值
//	for (int i = 0; i < mysize + 2; i++)
//	{
//		A[0][i] = 8.0;
//		A[totalsize - 1][i] = 8.0;
//	}
//	// 计算相邻 proc 矩阵
//	if (myid > 0)
//	{
//		left = myid - 1;
//	}
//	else
//	{
//		left = MPI_PROC_NULL;
//	}
//	if (myid < 3)
//	{
//		right = myid + 1;
//	}
//	else
//	{
//		right = MPI_PROC_NULL;
//	}
//	// 雅可比迭代 整体步数
//	for (int i = 0; i < steps; i++)
//	{
//		// 绑定发送接收, proc:第4列  -> rihgt proc: 第0列
//		MPI_Sendrecv(
//			&A[0][mysize], // onst void *sendbuf; 最右侧数据, 要发送给下一个 proc
//			totalsize,     // int sendcount; 数据长度
//			MPI_DOUBLE,    // MPI_Datatype  sendtype; 数据类型
//			right,         // int dest
//			tag1,          // int sendtag,
//			//---------------------------------------
//			&A[0][0],       // void *recvbuf; 接收数据位置
//			totalsize,      // int recvcount; 接收长度
//			MPI_DOUBLE,     // MPI_Datatype  recvtype; 数据类型
//			left,           // int source; 接收源
//			tag1,           // int recvtag; 接收 tag
//			MPI_COMM_WORLD, // MPI_Comm comm; 通信域
//			&status         // MPI_Status *status; 发送或接收状态;
//		);
//		// 绑定发送接收, proc:第1列  -> left proc: 第5列
//		MPI_Sendrecv(
//			&A[0][1],   // onst void *sendbuf
//			totalsize,  // int sendcount
//			MPI_DOUBLE, // MPI_Datatype sendtype
//			left,       // int dest
//			tag2,       // int sendtag,
//			//---------------------------------------
//			&A[0][mysize + 1], // void *recvbuf,
//			totalsize,         // int recvcount,
//			MPI_DOUBLE,        // MPI_Datatype recvtype,
//			right,             // int source,
//			tag2,              // int recvtag,
//			MPI_COMM_WORLD,    // MPI_Comm comm,
//			&status            // MPI_Status *status
//		);
//		// proc 0
//		if (myid == 0)
//		{
//			begin_col = 2; // 0th 列是缓冲, 1st 列缺少左边, 所以从 2nd 开始
//		}
//		// proc 3
//		if (myid == 3)
//		{
//			end_col = mysize - 1; //类似上面
//		}
//		// 在每个 proc matrix 内部, 去除首位列, 迭代内部列
//		for (int j = begin_col; j < end_col; j++)
//		{
//			// in each proc matrix, 去除首位行, 迭代内部行
//			for (int i = 1; i < totalsize - 1; i++)
//			{
//				B[i][j] = (A[i][j + 1] + A[i][j - 1] + A[i + 1][j] + A[i - 1][j]) * 0.25;
//			}
//		}
//		// 将数据从缓冲变量 提取到 原变量
//		for (int j = begin_col; j < end_col; j++)
//		{
//			for (int i = 1; i < totalsize - 1; i++)
//			{
//				A[i][j] = B[i][j];
//			}
//		}
//	}
//	// 打印迭代结果
//	for (int row = 1; row < totalsize - 1; row++)
//	{
//		std::cout << "proc (" << myid << "):  ";
//		for (int col = begin_col; col < end_col; col++)
//		{
//			std::cout << std::setiosflags(std::ios_base::left)
//				<< std::setw(15) << A[row][col]
//				<< std::resetiosflags(std::ios_base::left);
//		}
//		std::cout << std::endl;
//	}
//	// MPI 收尾
//	double end = MPI_Wtime();
//	char name[] = "";
//	int result;
//	MPI_Get_processor_name(name, &result);
//	cout << name << "  " << result << endl;
//
//
//	MPI_Group worldGroup;
//	MPI_Comm_group(MPI_COMM_WORLD, &worldGroup);
//	MPI_Group group1, group2;
//	const int group1p[2] = { 0,1 };
//	const int group2p[2] = { 2,3 };
//	MPI_Group_incl(worldGroup, 2, &group1p[0], &group1);
//	MPI_Group_incl(worldGroup, 2, &group2p[0], &group2);
//	MPI_Comm comm1, comm2;
//	MPI_Comm_create(MPI_COMM_WORLD, group1, &comm1);
//	MPI_Comm_create(MPI_COMM_WORLD, group2, &comm2);
//
//	//MPI_Abort(comm2, 99);
//	if (myid == 0)
//	{
//		exit(0);
//	}
//	Sleep(10000000);
//	
//	MPI_Finalize();
//	system("pause");
//	return 0;
//}





//主从模式
#include <algorithm>

// 全局变量初始化
const int rows = 100;
const int cols = 100;
double a[rows][cols] = { 0 }; //矩阵 [rows,cols]
double b[cols] = { 0 };       // 列矩阵
double c[rows] = { 0 };       // 存储结果矩阵
double buffer[cols] = { 0 };  //缓冲变量
int numsent = 0;            // 已发送行数
int numprocs = 0;           //设置进程数
const int m_id = 0;         // 主进程 id
const int end_tag = 0;      // 标志发送完成的 tag
MPI_Status status;          // MPI 状态

// 主进程主要干三件事: 定义数据, 发送数据和接收计算结果
void master()
{
    // 1准备数据
    for (int i = 0; i < cols; i++)
    {
        b[i] = i;
        for (int j = 0; j < rows; j++)
        {
            a[i][j] = i + 1;
        }
    };
    // 2 每个从进程都接收相同的矩阵b,
    // 考虑使用广播操作, 即主进程将矩阵b向通信域内所有进程广播一下矩阵b,
    // 然后从进程就可以都接收到矩阵b这一变量了.
    MPI_Bcast(
        b,             // void* buffer
        cols,          // int count
        MPI_DOUBLE,    // MPI_Datatype datatype
        m_id,          // int root,
        MPI_COMM_WORLD // MPI_Comm comm
    );
    // 矩阵A采用了之前提到过的 MPI_SEND, 发送每行的数据
    // 实际的子进程数是 numprocs - 1 个
    for (int i = 0; i < min(numprocs - 1, rows); i++)
    {
        for (int j = 0; j < cols; j++)
        {
            buffer[j] = a[i][j];
        }
        //发送矩阵A 的行数据, 使用矩阵行数作为 tag MPI_DOUBLE,
        MPI_Send(
            buffer,        // const void* buf,
            cols,          // int count,
            MPI_DOUBLE,    // MPI_Datatype datatype,
            i + 1,         // int dest, 0 列发给 rank 1, 以此类推
            i + 1,         // int tag, row number +1
            MPI_COMM_WORLD // MPI_Comm comm
        );
        numsent = numsent + 1; // 记录已发送的行数
    };
    // 3 在执行完发送步骤后, 需要将计算结果收回
    double ans = 0.0;           // 存储结果的元素
    for (int i = 0; i < rows; i++)
    {
        MPI_Recv(
            &ans,           // void* buf,
            1,              // int count,
            MPI_DOUBLE,     // MPI_Datatype datatype,
            MPI_ANY_SOURCE, // int source,
            MPI_ANY_TAG,    // int tag,
            MPI_COMM_WORLD, // MPI_Comm comm,
            &status         // MPI_Status * status
        );
        // sender 用于记录已经将结果发送回主进程的从进程号
        int sender = status.MPI_SOURCE;
        //在发送时, 所标注的 tag = 矩阵的行号+1,
        int rtag = status.MPI_TAG - 1;
        c[rtag] = ans; //用 c(rtag)=ans来在对应位置存储结果
        // numsent 是已发送行, 用于判断是否发送完所有行
        // 因其已经发送回主进程, 即可代表该从进程已经处于空闲状态
        // 在之后的发送中, 就向空闲的进程继续发送计算任务
        if (numsent < rows)
        {
            // 获取下一列
            for (int j = 0; j < cols; j++)
            {
                buffer[j] = a[numsent][j];
            }
            MPI_Send(
                buffer, cols, MPI_DOUBLE,
                sender, numsent + 1, MPI_COMM_WORLD);
            numsent = numsent + 1;
        }
        //当都发送完之后, 向从进程发送一个空信息,
        //从进程接收到空信息时, 即执行MPI_FINALIZE来结束.
        else
        {
            int tmp = 1.0;
            MPI_Send(
                &tmp, 0, MPI_DOUBLE,
                sender, end_tag, MPI_COMM_WORLD);
        }
    };
}
//
//// 子进程
void slave()
{
    //从进程首先需要接收主进程广播的矩阵b
    MPI_Bcast(b, cols, MPI_DOUBLE, m_id, MPI_COMM_WORLD);
    while (1)
    {
        MPI_Recv(
            buffer, cols, MPI_DOUBLE,
            m_id, MPI_ANY_TAG, MPI_COMM_WORLD,
            &status);
        //直到矩阵A的所有行都计算完成后, 主进程会发送 tag 为 end_tag 的空消息,
        if (status.MPI_TAG != end_tag)
        {
            int row = status.MPI_TAG;
            double ans = 0.0;
            for (int i = 0; i < cols; i++)
            {
                ans = ans + buffer[i] * b[i];
            }
            MPI_Send(
                &ans, 1, MPI_DOUBLE,
                m_id, row, MPI_COMM_WORLD);
        }
        else {
            break;
        }
    }
}

int main(int argc, char* argv[])
{
    //----------------------------------
    // MPI 初始化
    MPI_Init(&argc, &argv);
    //获取进程总数
    MPI_Comm_size(
        MPI_COMM_WORLD, // MPI_Comm comm
        &numprocs       // int* size
    );
    // 获取rank
    int myid = 0; // rank number
    MPI_Comm_rank(
        MPI_COMM_WORLD, // MPI_Comm comm,
        &myid           // int* size
    );
    // 打印进程信息
    std::cout << "Process " << myid << " of " << numprocs << " is alive!" << std::endl;
    //----------------------------------
    if (myid == m_id)
    {
        master(); //主进程的程序代码
    }
    else
    {
        slave(); //从进程的程序代码
    }
    // 打印结果
    if (myid == m_id) {
        for (int i = 0; i < rows; i++)
        {
            std::cout << "the ele (" << i << "): "
                << std::setiosflags(std::ios_base::right)
                << std::setw(15) << c[i]
                << std::resetiosflags(std::ios_base::right)
                << std::endl;
        }
    }
    // MPI 收尾
    MPI_Finalize();
}