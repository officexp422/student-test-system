#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define NULL 0
#define LEN sizeof(struct student)
#define LENS sizeof(struct stu)
struct student
{
	long num;//student's code
	char name[20];
	char sex[20];
	char add[20];
	int tel[20];
};
struct score
{
	int chinese;
	int math;
	int english;
};
struct grade
{
	struct score g0;
	int g1;//average score
	int g2;//score that students score each other
	int g3;//moral score
	int g4;//teacher's score
	int g5;//综合得分
	int r1;//exam rank
	int r2;//overall rank  综合排名
};
struct stu//linklist with student's information
{
	struct student inf;
	struct grade point;
	struct stu *next;//the address of next linklist
};
int n=0;//record the number of node
FILE *fp;//open file and read the data
struct stu *creat(char filename1[20])//create linklist,read the data from the file, and return head pointer
{
	struct stu *head;
	struct stu *p1,*p2;//pointer variable
	p1=p2=(struct stu *)malloc(LENS);
	memset(p1,0,LENS);
	memset(p2,0,LENS);
	if((fp=fopen(filename1,"wb"))==NULL)//if there is not the file ,then build it
	{
		printf("No information of students, NOW");
		fp=fopen(filename1,"wb");//build file
		fclose(fp);
		p1->next=NULL;//将新节点的指针置为空
		return(p1);//return the head pointer of linked list
	}
	else//read the file, and build a linklist
	{
		n=0;//no node, now
		head=p1;//assign the value of p1 to the head pointer
		while(fread((&p1->inf),LEN,1,fp))
		{
			if(n==0) 
				head=p1;//assign the value to the head pointer
			else 
			{
				p2->next=p1;//add new structure
				p2=p1;
				p1=(struct stu *)malloc(LENS);
				memset(p1,0,LENS);
				n++;
			}
		}
		fclose(fp);
		p2->next=NULL;//assign the pointer of last node NULL
		return(head);
	}
}
struct stu *open(char filename1[20])
{
	struct stu *head;
	struct stu *p1,*p2;
	fp=fopen(filename1,"rb");
	p1=p2=(struct stu *)malloc(LENS);
	memset(p1,0,LENS);
	memset(p2,0,LENS);
	head=p1;
	while(fread((&p1->inf),LEN,1,fp))
	{
		if(n==1) head=p1;
		else p2->next=p1;
		p2=p1;
		p1=(struct stu *)malloc(LENS);
		memset(p1,0,LENS);
	}
	fclose(fp);
	p2->next=NULL;
	return(head);
}
void save(struct stu *head, char filename[20])//save the information of linklist
{
	struct stu *p;
	p=head;
	fp=fopen(filename, "wb");//open the file with binary system
	while((p!=NULL)&&fwrite(&(p->inf),LEN,1,fp))//write in the file

	{
		p=p->next;
	}
	fclose(fp);
}
void txtsave(struct stu *head,char filename[20])//write in the file with text form
{
	FILE *fp;
	struct stu *p;
	p=head->next;
	fp=fopen(filename,"w");//open the file with text form
	while(p!=NULL)//do not stop until the linklist end
	{
		fprintf(fp,"ld",(p->inf).num);//write data
		fprintf(fp,"%10s",(p->inf).name);
		fprintf(fp,"%10s",(p->inf).sex);
		fprintf(fp,"%10s",(p->inf).add);
		fprintf(fp,"%20d",(p->inf).tel);
		p=p->next;
	}
}
void print1(struct stu *p)//output the information of single structure
{
	printf("\ncode:%d",(p->inf).num);
	printf("\nname:%s",(p->inf).name);
	printf("\nsex:%s",(p->inf).sex);
	printf("\naddress:%s",(p->inf).add);
	printf("\ntelephone:%d\n\n",(p->inf).tel);
}
void printall(struct stu *p)//输出某学生全体数据
{
	printf("\ncode:%d",(p->inf).num);
	printf("\nname:%s",(p->inf).name);
	printf("\nsex:%s",(p->inf).sex);
	printf("\naddress:%s",(p->inf).add);
	printf("\ntelephone:%d\n\n",(p->inf).tel);
	printf("\nChinese:%d\n",p->point.g0.chinese);
	printf("\nMath:%d\n",p->point.g0.math);
	printf("\nEnglish:%d\n\n",p->point.g0.english);
	printf("\n平均成绩:%d\n",p->point.g1);
	printf("\n同学互评：%d\n",p->point.g2);
	printf("\n品德成绩：%d\n",p->point.g3);
	printf("\n教师打分：%d\n",p->point.g4);
	printf("\n综合成绩：%d\n\n",p->point.g5);
	printf("\n考试排名：%d\n",p->point.r1);
	printf("\n综合排名：%d\n\n",p->point.r2);
}
struct stu *add(struct stu *);
struct stu *subadd(struct stu *);
struct stu *judge(struct stu *head,struct stu *p1)//判断学号是否重复
{
	struct stu *p;
	p=head;
	while(p->inf.num!=p1->inf.num)
	{
			p=p->next;
			if(p==NULL)
			{
				printf("学号不重复\n");
				return(p1);
			}
	}
	printf("学号重复，请重新输入\n");
	p1=subadd(head);
	return(p1);
}
struct stu *subadd(struct stu *head)//input=！0，且n！=0时的运行程序
{
	struct stu *p1;
	p1=(struct stu *)malloc(LENS);//input information
	memset(p1,0,LENS);
	printf("\ncode:");scanf("%d",&((p1->inf).num));
	/*printf("\nname:");scanf("%s",&((p1->inf).name));
	printf("\nsex:");scanf("%s",&((p1->inf).sex));
	printf("\nadress:");scanf("%s",&((p1->inf).add));
	printf("\ntelephone:");scanf("%d",&((p1->inf).tel));*/
	p1=judge(head,p1);
	return(p1);
}
struct stu *add(struct stu *head)//add information
{
	int input=1;//assign initial value for the input button
	struct stu *p1,*p2,*p;//build structure pointer
	while(input!=0)
	{
		printf("choose:\ninput 0 return menu\ninput1 continue\n");
		scanf("%d",&input);//assign initial value
		if(input==0)break;//judge whether to return to the menu
		if(n==0)//linklist has no node, assign data for *head
		{
			head->next=(struct stu *)malloc(LENS);//input information
			memset(head->next,0,LENS);
			p2=head->next;
			printf("\ncode:");scanf("%d",&((p2->inf).num));
			/*printf("\nname:");scanf("%s",&((p2->inf).name));
			printf("\nsex:");scanf("%s",&((p2->inf).sex));
			printf("\nadress:");scanf("%s",&((p2->inf).add));
			printf("\ntelephone:");scanf("%d",&((p2->inf).tel));*/

			n++;p2->next=NULL;continue;//add node,the number of nodes add 1, and then jump put this circle and go into next circle
		}
		if(n!=0)
		{
			p1=subadd(head);	
		}
		print1(head->next);
		if((head->next->inf).num>(p1->inf).num)
		{
			p2=head->next;
			p=p2;
			p2=p1;
			p2->next=p;
			head->next=p2;
			//如果p1比头指针小，那么将p1插到头指针head之前，并代替头指针
		}
		else
		{
			p2=head->next;
			if(p2->next!=NULL)
			{
				while((p2->next->inf).num<(p1->inf).num)
				{
					
					p2=p2->next;//遍历，在p2->next不为空的前提下，寻找p1.num介于p2.num和p2->next.num之间的位置
					if(p2->next==NULL)break;//第一遍while循环是成功的，且p2不为空，但第二遍走while循环时就卡在while这里
				}
			/*当p2->next.num大于p1.num*/
			}
			p=p2->next;
			p2->next=p1;
			p2->next->next=p;//在正确的位置插入新节点,但是这个算法无法将p1插到head之前
			}//逐个值输出检验，排序算法本身没有问题
			n++;//the number of node add 1
	}
	return(head);
}
struct stu *delet(struct stu *head)//delet information
{
	long snum=0;
	struct stu *p1,*p2;
	printf("please input the code that you want to delet:\n");
	scanf("%ld",&snum);
	p1=head;
	while(snum!=p1->inf.num&&p1->next!=NULL)//code that p1 point to is not what we want, where there is node behind
	{
		p2=p1;
		p1=p1->next;
	}//move the p1 back
	if(snum=p1->inf.num)//find the object
	{
		print1(p1);
		if(p1==head)
		{
			head=p1->next;
			printf("delet the information already");//if p1 point to head node, assign the second node's address to head
		}
		else p2->next=p1->next;//or assign the address of next node to the address of previous node
		n--;
	}
	else printf("the student does not exist\n");
	return(head);
}
void print(struct stu *head)//output all data
{
	struct stu *p;
	printf("the following are all students' data:\n");
	if(n==0)
	{
		printf("no student's information\n");
		return;
	}//if there is no node, return
	else
	{
		p=head->next;
		while(p!=NULL)//output circularly
		{
			printf("\ncode:%d",(p->inf).num);
			printf("\nname:%s",(p->inf).name);
			printf("\nsex:%s",(p->inf).sex);
			printf("\naddress:%s",(p->inf).add);
			printf("\ntelephone:%d",(p->inf).tel);
			p=p->next;
		}
	}
}
struct stu *isystem()//student information system
{
	struct stu *head;//define head pointer variable
	char filename1[20]="information.xls";//name system database
	char filename2[20]="student.txt";//name system text file
	int select;//choice variable in menu
	head=creat(filename1);//build system linked list
	do
	{
		printf("\n\n\n 欢迎进入学生信息管理系统\n*****************************");//title
		printf("\n\n1.add student\n2.scan student\n3.delet student\n4.exit\n\n\n");//menu
		scanf("%d",&select);
		switch(select)//select in menu and enter subprogram
		{
		case 1:add(head);break;//add
		case 2:print(head);break;//output
		case 3:head=delet(head);break;//delet, return
		case 4:break;//jump out the menu
		default:printf("ERROR");
		}
	}while(select!=4);
	printf("See you next time!\n");
	save(head,filename1);//save the information in system linked list
	txtsave(head,filename2);//save the information as text format
	return(head);
}
struct stu *numsearch(struct stu *head)//学号查询模块
{
	struct stu *p=head;
	int studentnum;//用来存放下面输入的学号
	printf("请输入学号：\n");
	scanf("%d",&studentnum);
	if(p==NULL)
		printf("无学生信息\n");
	else
	{
		while((p->inf).num!=studentnum)
		{
			p=p->next;
			if(p->next==NULL)//如果检索完毕
			{
				printf("没有该学生的信息，请重新输入\n");
				numsearch(head);break;
			}
		}
	}
	printf("学号存在\n");
	return(p);//返回该学号的指针
}
int rank1(struct stu *head,struct stu *p)//考试成绩排名模块
{
	struct stu *p1;
	int k=1;
	p1=head;
	while(p1->point.g1>p->point.g1&&p1!=NULL)//如果有分数比p同学高的，排名数加1
	{
		p1=p1->next;
		k++;
	}
	return(k);
}
struct stu *scoreinput(struct stu *head)//按考试科目录入学生成绩，并计算平均分和考试排名
{
	struct stu *p=numsearch(head);//学号查询模块，返回查询到的该学生指针
	printf("请输入语文成绩：\n");scanf("%d",&p->point.g0.chinese);
	printf("请输入数学成绩：\n");scanf("%d",&p->point.g0.math);
	printf("请输入英语成绩：\n");scanf("%d",&p->point.g0.english);
	p->point.g1=(p->point.g0.chinese+p->point.g0.math+p->point.g0.english)/3;//计算平均分
	printf("该学生的平均分是：%d\n",p->point.g1);
	printf("该学生成绩排名是：%d\n",p->point.r1=rank1(head,p));
	return(head);
}
int rank2(struct stu *head,struct stu *p)//综合排名模块
{
	struct stu *p1;
	int k=1;
	p1=head;
	while(p1->point.g5>p->point.g5&&p1!=NULL)//如果有分数比p同学高的，排名数加1
	{
		p1=p1->next;
		k++;
	}
	return(k);
}
struct stu *overallinput(struct stu *head)//学生数据测评输入，并计算综合排名
{
	struct stu *p=numsearch(head);//学号查询模块，返回查询到的该学生指针
	printf("请输入同学互评分：\n");scanf("%d",&p->point.g2);
	printf("请输入品德成绩：\n");scanf("%d",&p->point.g3);
	printf("请输入任课老师评分：\n");scanf("%d",&p->point.g4);
	p->point.g5=0.6*p->point.g1+0.1*p->point.g2+0.1*p->point.g3+0.2*p->point.g4;//计算综合得分
	printf("该学生的综合分是：%d\n",p->point.g5);
	printf("该学生综合排名是：%d\n",p->point.r2=rank2(head,p));
	return(head);
}
struct stu *datachange(struct stu *head)//学生数据管理，输入学号，修改学生信息
{
	int input=0;
	int button=0;
	int m=0;
	struct stu *p=numsearch(head);//学号查询模块，返回查询到的该学生指针
	printall(p);
	printf("修改？\n修改选1，不修改选0");
	scanf("%d",&input);
	if(input==0)
		return(head);
	else
	{
		printf("选1修改考试成绩\n选2修改综合成绩\n其他键退出\n");
		scanf("%d",&button);
		if(button==1)//修改考试成绩
		{
			printf("请输入语文成绩：\n");scanf("%d",&p->point.g0.chinese);
			printf("请输入数学成绩：\n");scanf("%d",&p->point.g0.math);
			printf("请输入英语成绩：\n");scanf("%d",&p->point.g0.english);
		}
		if(button==2)//修改综合成绩
		{
			printf("请输入同学互评分：\n");scanf("%d",&p->point.g2);
			printf("请输入品德成绩：\n");scanf("%d",&p->point.g3);
			printf("请输入任课老师评分：\n");scanf("%d",&p->point.g4);
		}
		if(button==1||button==2)
		{
			printall;
			printf("继续修改？\n选1继续\t选0退出\n");
			scanf("%d",&m);
			if(m==1)
			{
				datachange(head);
				return(head);
			}
			else
				return(head);
		}
		else
			return(head);
		
	}
}
void dsystem()//学生数据处理系统
{
	struct stu *head;
	int select;//choice variable in menu
	char filename1[20]="information.xls";//name system database
	head=open(filename1);//打开已有的链表
	do
	{
		printf("\n\n\n 欢迎进入学生数据管理系统m\n*****************************");//title
		printf("\n\n1.学生成绩录入\n2.综合成绩录入\n3.修改学生信息\n4.exit\n\n\n");//menu
		scanf("%d",&select);
		switch(select)//select in menu and enter subprogram
		{
		case 1:scoreinput(head);break;//进入学生信息处理系统
		case 2:overallinput(head);break;//进入学生数据处理系统
		case 3:datachange(head);break;//显示所有学生信息
		case 4:break;//jump out the menu
		default:printf("ERROR");
		}
	}while(select!=4);
}
void allscan()//一次性显示所有学生的所有信息
{
	struct stu *head,*p;
	char filename1[20]="information.xls";//name system database
	head=open(filename1);//打开已有的链表
	p=head;
	while(p!=NULL)
	{
		printall(p);
		p=p->next;
	}
	return;
}
void main()
{
	int select;//choice variable in menu
	do
	{
		printf("\n\n\n welcome to student management system\n*****************************");//title
		printf("\n\n1.学生信息处理\n2.学生数据处理\n3.显示所有学生信息\n4.exit\n\n\n");//menu
		scanf("%d",&select);
		switch(select)//select in menu and enter subprogram
		{
		case 1:isystem();break;//进入学生信息处理系统
		case 2:dsystem();break;//进入学生数据处理系统
		case 3:allscan();break;//显示所有学生信息
		case 4:break;//jump out the menu
		default:printf("ERROR");
		}
	}while(select!=4);
	system("PAUSE");
}