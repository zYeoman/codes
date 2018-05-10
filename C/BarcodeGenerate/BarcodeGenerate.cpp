#include<iostream>
#include<fstream>
using namespace std;
int main()
{
	char *bi[3][10]=
	{
		"0001101","0011001","0010011","0111101","0100011","0110001","0101111","0111011","0110111","0001011",
		"0100111","0110011","0011011","0100001","0011101","0111001","0000101","0010001","0001001","0010111",
		"1110010","1100110","1101100","1000010","1011100","1001110","1010000","1000100","1001000","1110100"
	};
	//数字对应二进制
	int flag[10][6]=
	{
		0,0,0,0,0,0,
		0,0,1,0,1,1,
		0,0,1,1,0,1,
		0,0,1,1,1,0,
		0,1,0,0,1,1,
		0,1,1,0,0,1,
		0,1,1,1,0,0,
		0,1,0,1,0,1,
		0,1,0,1,1,0,
		0,1,1,0,1,0
	};
	//代码与字符集对应关系
	int n[13];						//存储十进制值
	char B[120];					//存储二进制值
	int i=0;char c;

	while(1)						//读入十进制条码值
	{
		while((c=getchar())>'9' ||c < '0')
			;
		for(i = 0;c<='9'&& c >= '0';i++)
		{
			n[i] = c-'0';
			c=getchar();
		}
		while(c !='\n')
			c=getchar();
		if (i != 13)
			cout<<"输入错误！请输入13个数字"<<endl;
		else if (i==0)
			break;
		else if ((10-((n[1]+n[3]+n[5]+n[7]+n[9]+n[11])*3+n[0]+n[2]+n[4]+n[6]+n[8]+n[10])%10)%10 != n[12])
			cout<<"输入错误！校验码不对"<<endl;
		else break;
	}

	strcat(B,"00000000000101");
	for (int i = 0; i < 6; ++i)
		strcat(B,bi[flag[n[0]][i]][n[i+1]]);
	strcat(B,"01010");
	for (int i = 0; i < 6; ++i)
		strcat(B,bi[2][n[i+7]]);
	strcat(B,"1010000000");
	cout<<B<<endl;
	ofstream outfile;
	outfile.open("out.html");
	outfile<<"<html><body>";
	char temp;
	for (int i = 0; i < 113; ++i)
	{
		temp=B[i];
		if(temp=='1') outfile<<"<img src=\"1.jpg\" border=\"0\" />";
		if(temp=='0') outfile<<"<img src=\"0.jpg\" border=\"0\" />";
	}
	outfile<<"</body></html>";
	outfile.close();
	system("pause");
	return 0;
}