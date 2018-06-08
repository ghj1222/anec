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
		fscanf(list,"%s",name[i]);
	fclose(list);
	list=0;
	for(int i=1;i<=nn;i++)
	{
		sprintf(tmp,"%s\\%s",name[i],timuname);
		fp=fopen(tmp,"r");
		if(fp==0)
		{
			fprintf(out,"Canout open %s\n",tmp);
			len[i]=-1;
		}
		else
		{
			while((code[i][++len[i]]=fgetc(fp))!=EOF);
			fclose(fp);
			fp=0;
			run(i);
		}
	}
	fprintf(out,"name,name,val,\n");
	tot=nn*(nn-1)/2,t=1;
	for(int i=1;i<=nn;i++)
		for(int j=i+1;j<=nn;j++)
		{
			system("cls");
			printf("name=%s\n",timuname);
			printf("process：%.3f%%\n",t/(double)tot*100.0);
			if(len[i]!=-1&&len[j]!=-1)
			{
				work(i,j);
				sprintf(tmp,"%s,%s,",name[i],name[j]);
				li.push_back((pa){f[len[i]][len[j]]*2/(double)(len[i]+len[j]),tmp});
			}
			t++;
		}
	std::sort(li.begin(),li.end(),std::greater<pa>());
	for(std::vector<pa>::iterator i=li.begin();i<li.end();i++)
		fprintf(out,"%s%f,\n",(*i).name.c_str(),(*i).p);
	fclose(out);
	out=0;
	system("cls");
	std::printf("name=%s\n",timuname);
	printf("done.\n");
	system("pause");
	return 0;
}
