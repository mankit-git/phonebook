#include "head.h"

char *errmsg = NULL;
sqlite3 *db; 

int create_table(sqlite3 *db)
{
	int ret;
	char *sql = "create table if not exists phone \
				(                     \
					name TEXT,    \
					telephone TEXT,   \
					photo TEXT,   \
					music TEXT   \
				);";
	ret = sqlite3_exec(db, sql, NULL, NULL, &errmsg);
	if(ret)
	{
		printf("%s\n", errmsg);
		perror("sqlite3_exec() failed");
		exit(0);
	}
	return 0;
}

int callback(void *data,int argc,char **cloumn_values, char **cloumn_name)
{
	printf("%s\n",(char *)data);
	
	int i;
	
	for(i=0; i<argc; i++)
	{
		printf("%s:%s\n",cloumn_name[i],cloumn_values[i]);
	}
	printf("callback test!\n");
	printf("============================\n");
	return 0;
}

int sqlite3_insert(sqlite3 *db, struct phone_info *ph)
{
	int ret;
	char insert[256]={0};
	printf("please input a name:\n");
	scanf("%s", ph->name);
	printf("please input a phone:\n");
	scanf("%s", ph->telephone);
	printf("please input a photo:\n");
	scanf("%s", ph->photo);
	printf("please input a music:\n");
	scanf("%s", ph->music);

	printf("%d\n", __LINE__);
	sprintf(insert,"INSERT INTO phone VALUES ('%s', '%s', '%s', '%s');",ph->name, ph->telephone, ph->photo, ph->music);
	printf("%d\n", __LINE__);
	ret = sqlite3_exec(db, insert, NULL, NULL, &errmsg);
	if(ret)
	{
		perror("sqlite3_exec");
		return -1;
	}
	
	return 0;

}

int display(sqlite3 *db)
{
	if(db == NULL)
		return 0;
	char *check = "select * from phone;";
	char **result = NULL;
	int nrow, ncolumn;

	int show = sqlite3_get_table(db, check, &result, &nrow, &ncolumn, &errmsg);
	if(show)
	{
		perror("sqlite3_get_table() failed");
		exit(0);
	}

	int i,j;
	for(i=0; i<=nrow; i++)
	{
		for(j=0; j<ncolumn; j++)
		{
			printf(" %s |", result[i*ncolumn+j]);
		}
		printf("\n");
	}
	sqlite3_free_table(result);
}

int sqlite3_del(sqlite3 *db, struct phone_info *ph)
{
	int ret;
	char insert[256]={0}; 
	char telephone[20];
	char *data = "sqlite callback";
	printf("请输入删除电话的号码\n");
	scanf("%s", telephone);
		
	sprintf(insert,"delete from  phone where telephone='%s';select * from phone;", telephone);
	
	ret = sqlite3_exec(db,insert, callback, (void *)data,&errmsg);
	if(ret)
	{
		printf("errmsg: %s\n", errmsg);
		perror("sqlite3_exec() failed");
		return -1;
	}

	return 0;	
}

int sqlite3_update(sqlite3 *db)
{
	char sql[256]={0};
	char searchname[20];
	bzero(searchname, 20);
	char newinfo[20];
	bzero(newinfo, 20);
	char oldinfo[20];
	bzero(oldinfo, 20);


	printf("输入名字:\n");
	scanf("%s", searchname);
	printf("要更新项的列名:\n");
	scanf("%s", oldinfo);
	printf("输入更新的信息:\n");
	scanf("%s", newinfo);

	sprintf(sql,"update phone set %s='%s' where name='%s';", oldinfo, newinfo, searchname);
	int ret = sqlite3_exec(db, sql, NULL, NULL, &errmsg);
	if(ret)
	{
		printf("%s\n", errmsg);
		perror("sqlite3_exec() failed");
		exit(0);
	}
	return 0;
}