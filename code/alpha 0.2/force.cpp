/*	
anec alpha 0.1
by ghj1222
		
*/
		
#include<bits/stdc++.h>
#define SRC_MAX 200
#define SRCNAME_MAX 200
#define LEN_MAX 1000
#define CODE_MAX 10000

struct pa
{
	double p;
	std::string name;
	bool operator>(const pa&x)const
	{
		return p>x.p;
	}
};

std::vector<pa>li;
char name[SRC_MAX][SRCNAME_MAX],tmp[LEN_MAX],code[SRC_MAX][CODE_MAX],timuname[LEN_MAX],outputname[LEN_MAX];
int f[CODE_MAX][CODE_MAX],len[SRC_MAX],nn,tot,t;
std::FILE*list,*out,*fp;

void run(int x)
{
	//这个函数是净化，暂时不会写。
}

void work(int x,int y)
{
	for(int i=1;i<=len[x];i++)
		for(int j=1;j<=len[y];j++)
		{
			f[i][j]=std::max(f[i-1][j],f[i][j-1]);
			if(code[x][i]==code[y][j])
				f[i][j]=std::max(f[i][j],f[i-1][j-1]+1);
		}
}

int main()
{
	list=std::fopen("list.txt","r");
	if(list==0)
	{
		std::fprintf(stderr,"Cannot open list.txt\n");
		std::system("pause");
		return 0;
	}
	std::fscanf(list,"%s",timuname);
	std::printf("name=%s\n",timuname);
	std::sprintf(outputname,"%s_res.csv",timuname);
	out=std::fopen(outputname,"w");
	std::fscanf(list,"%d",&nn);
	for(int i=1;i<=nn;i++)
	{
		std::fgets(name[i],sizeof(name[i]),list);
		int len=std::strlen(name[i]);
		if(name[i][len-1]=='\n') name[i][len-1]=0; 
	}
	std::fclose(list);
	list=0;
	for(int i=1;i<=nn;i++)
	{
		std::sprintf(tmp,"%s\\%s",name[i],timuname);
		fp=std::fopen(tmp,"r");
		if(fp==0)
		{
			std::fprintf(out,"Canout open %s\n",tmp);
			len[i]=-1;
		}
		else
		{
			while((code[i][++len[i]]=std::fgetc(fp))!=EOF);
			std::fclose(fp);
			fp=0;
			run(i);
		}
	}
	std::fprintf(out,"name,name,val,\n");
	tot=nn*(nn-1)/2,t=1;
	for(int i=1;i<=nn;i++)
		for(int j=i+1;j<=nn;j++)
		{
			std::system("cls");
			std::printf("name=%s\n",timuname);
			std::printf("process：%.3f%%\n",t/(double)tot*100.0);
			if(len[i]!=-1&&len[j]!=-1)
			{
			work(i,j);
			std::sprintf(tmp,"%s,%s,",name[i],name[j]);
			li.push_back((pa){f[len[i]][len[j]]*2/(double)(len[i]+len[j]),tmp});
			}
		t++;
		}
	std::sort(li.begin(),li.end(),std::greater<pa>());
	for(std::vector<pa>::iterator i=li.begin();i<li.end();i++)
		std::fprintf(out,"%s%f,\n",(*i).name.c_str(),(*i).p);
	std::fclose(out);
	out=0;
	std::system("cls");
	std::printf("name=%s\n",timuname);
	std::printf("done.\n");
	std::system("pause");
	return 0;
}
