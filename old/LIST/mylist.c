#include"mylist.h"

int main(void)
{

	PNODE head=list_init();
	int i;
	for(i=0;i<10;i++)
	{
		list_add_tail(head,i);
	}
	list_pri(head);	
	list_del(head,5);
	list_pri(head);
	list_free(head);
	
	
	return 0;
}