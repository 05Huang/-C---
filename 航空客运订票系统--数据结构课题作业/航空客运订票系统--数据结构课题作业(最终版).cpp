
#include<iostream>
#include<string>
#include<windows.h>
#include <algorithm>
#include<bits/stdc++.h> 
using namespace std;

typedef struct CNode 
{
    char name[20];//����
    int num;//��Ʊ�� 
    char ID[20];//���֤
    char day[20];
    int dengji;//�յȼ�
    CNode *next;
} CNode, *CList;//�˿ͽڵ�

typedef struct HbNode 
{
    char name[20];//����
    char ID[20]; //���֤
    int num;//Ԥ������ 
    struct HbNode *next;
} QhbNode, *Phb;//�򲹶����еĽڵ�

typedef struct Queue 
{
    Phb front;//�Ⱥ��油�ͻ��������ͷָ��
    Phb rear;//�Ⱥ��油�ͻ��������βָ��
} LinkQueue;//�򲹶���

typedef struct hangban {
    char qidian[20];//���վ��
    char zhongdian[20];//�յ�վ��
    char hbID[20];//������ 
    char hbnum[20];//�ɻ���
    char day[20];//�������ڣ����ڼ���
    int maxnum;//��Ʊ��
    int less;//����Ʊ��
    int lessgrade1; //�ȼ�1ʣ����
    int lessgrade2; //�ȼ�2ʣ����
    hangban *next;
    CList cusLinkList;//��Ա������ָ���Ա���������ͷָ��
    LinkQueue wQgrade1;//�ȼ�1�򲹣��Ⱥ��油�Ŀͻ�������ָ��һ������
    LinkQueue wQgrade2;//�ȼ�2�򲹣��Ⱥ��油�Ŀͻ�������ָ��һ������
} hangban, *Phangban;//����ڵ�

//���ڴ�� 
int guanliyuanyemian();//����Աҳ�� 
int denglu(); //��¼ 
void initFlight(); //��ʼ����������
void sousuoflight();//������յ��������� 
void sousuoFace();// ��������
void printfall(hangban *pflight);//��ӡȫ��������Ϣ
int menu();// �˵����溯��
int zengjiaFlight();//���Ӻ��� 
int shanchuFlight();// ɾ������
void sousuoFlight();//�������յ�������Ӧ���� 
int Create(Phangban flight1);//��������Ϣ���뵽������ 
int duibiFlight(hangban *flight, char flightCodeID[]);// �ԱȲ��뺽���ţ���ֹ����ظ� 
//��ĩ��� 
hangban *find(); // �����ŷ��ض�Ӧ��Ϣ
int initQueue(LinkQueue &q);//��ʼ������
int initCusLinkList(CList &cusLinkList);//��ʼ����Ʊ�˿�����
void addlink(CList &head, int need, char name[], char id[],char day[], int grade);//����Ʊ�ɹ��ĳ˿ͽڵ���뵽�Ѷ�Ʊ���� 
void pricusInfo();//����Ѿ���Ʊ�ĺ��� 
void dingpiao();// ��Ʊ���� 
void fightinfo(hangban *p);//�����Ӧ�ڵ���Ϣ 
LinkQueue enqueue(LinkQueue &q, char name[], int need, char id[]);//���ȴ��Ŀͻ����
void tuipiao();// ��Ʊ
void dingpiaoFace();//  ��Ʊ����
void tuipiaoFace(); //��Ʊ����



hangban *pFlight;//ȫ�ֽڵ���� 
 //��ʼ����ĺ�����Ϣ 
hangban flight1[4] = {
        {"����", "�Ͼ�", "1", "A1185", "������", 400, 200, 100, 100},
        {"����", "����", "2", "B4521", "����һ", 300, 200, 100, 100},
        {"����", "�Ϻ�", "3", "C8541", "������", 500, 200, 100, 300},
        {"����", "��", "4", "D3652", "������", 600, 200, 100, 400},
};


//��ʼ���������� 
void initFlight() 
{
    pFlight = new hangban;
    pFlight->next = NULL;
}


// �����к�����Ϣ��������
int Create(Phangban flight1) 
 {
    hangban *p = pFlight, *q;
    for (int i=0; i < 4; i++) {
        q = new hangban;
        if (q == NULL)
            return 0;
        strcpy(q->qidian, flight1[i].qidian);//���������ÿ����Ϣ¼�� 
        strcpy(q->zhongdian, flight1[i].zhongdian);
        strcpy(q->hbID, flight1[i].hbID);
        strcpy(q->hbnum, flight1[i].hbnum);
        strcpy(q->day, flight1[i].day);
        q->maxnum = flight1[i].maxnum;
        q->less = flight1[i].maxnum;
        q->lessgrade1 = flight1[i].lessgrade1;
        q->lessgrade2 = flight1[i].maxnum - flight1[i].lessgrade1;
        initCusLinkList(q->cusLinkList); //��ʼ���Ѿ���Ʊ�˿�����
        initQueue(q->wQgrade1);// �����ֵȼ���Ʊ��� ���������Ԥ���Ŷ� 
        initQueue(q->wQgrade2);
        q->next = p->next;
        p->next = q;
    }
    return 1;
}



//��ʼ���Ѷ�Ʊ�˿�ָ������
int initCusLinkList(CList &cusLinkList) 
{
    CList q = cusLinkList;
    cusLinkList = (CNode *) malloc(sizeof(CNode));
    cusLinkList->next = NULL;
}

//��ʼ����ͷ����������
int initQueue(LinkQueue &q) 
{
    QhbNode *p;
    p = new QhbNode;
    p->next = NULL;
    q.front = q.rear = p;//�ӿ� 
    return 1;
}

bool isValidID(const char id[]) 
{
    int length = strlen(id);
    // ������֤���볤���Ƿ�Ϊ18λ���� 
    return (length == 18) && all_of(id, id + length, ::isdigit); // ʹ�� C++11 �� all_of ������������ַ��Ƿ�Ϊ����
}

// ��Ʊ����
void dingpiao()  
{
    hangban *info;
    int need, grade;
    int num;//ʣ��ĵȼ�1��Ŀ���ߵȼ�2��Ŀ
    char name[20];
    char id[20];
    char day[20];
    info = find();//�����붩�ĺ��࣬���Ƿ��п�λ�ã������ظ��ƽڵ� 
    srand(time(0));// ��ʼ�����������
    int seatCount = 0; // �ѷ�����λ������
    if (info == NULL)
	{
        cout<<"�����ڸú���"<<endl;
        dingpiao();
    }
  	cout<<"����������Ҫ��Ʊ��"<<endl;
    while(1)
	{
    	cin>>need;
    	if(need<=0) 
		{
    		cout<<"��������ȷ�Ķ�Ʊ��"<<endl;
			continue;
		}
    	else break;
	} 
    cout<<"����������Ҫ����λ�ȼ�"<<endl; 
    while(1)
	{
    	cin>>grade;
    	if(grade!=1&&grade!=2) 
		{
    		cout<<"��������ȷ����λ�յȼ�"<<endl;
			continue;
		}
    	else break;
	} 
    if (grade == 1)
        num = info->lessgrade1;
    else
        num = info->lessgrade2;
    if (need <= num) //��Ʊ��С��ʣ���� 
	{
		vector<int> allocatedSeats;
        int i;
        cout<<"��������������"<<endl;
    	cin>>name;
       	cout << "�������������֤����: ";
	    while (true) 
		{
	        cin>>id;
	        if (!isValidID(id)) 
			{
	            cout << "���֤�����ʽ����ȷ��������18λ������: ";
	            continue;
	        } 
			else 
			{
	            break;
	        }
	    }
        cout<<"��������ķ���ʱ�䣺"<<endl;
		cin>>day; 
        CList head = info->cusLinkList; 
        addlink(head, need, name, id,day,grade);//��Ʊ�ɹ��������Ա��������
		int seatStatus[info->maxnum] = {0}; // 0��ʾ��λδ��ռ�ã�1��ʾ�ѱ�ռ��
        // ѭ��������λ��
        for (int i = 0; i < need; ++i) 
		{
            int seatNumber;
            do {
                seatNumber = rand() % info->maxnum + 1; 
            } while (seatStatus[seatNumber - 1]); // �����λ���Ƿ��ѱ�ռ�� 
            seatStatus[seatNumber - 1] = 1; // �����λ��Ϊ��ռ��
            cout << name << "����λ����" << seatNumber << endl;
        }
        info->less -= need;
        if (grade == 1)
            info->lessgrade1 -= need;
        else
            info->lessgrade2 -= need;
        cout<<"��Ʊ�ɹ�"<<endl; 
    } 
	else
        {
            char r;
            cout<<"�õȼ���Ʊ���㣬����Ϊ�ú���˿���Ϣ"<<endl;
            fightinfo(info);//����ú���Ķ�Ʊ��Ϣ 
           	cout<<"�Ƿ�ı䶩Ʊ�ƻ���Y/N"<<endl;
            cin>>r;
            if (r == 'Y' || r == 'y') //�ı�ƻ�������ѡ�񺽰�
			{
                dingpiao();//���ض�Ʊ��ҳ�� 
            } 
			else 
			{
               cout<<"����Ҫ�ŶӵȺ���?(Y/N)"<<endl;
            	cin>>r;
                if (r == 'Y' || r == 'y') 
				{
				//���ı�ƻ����ŶӺ�Ʊ
                cout<<"�����������������ŶӶ�Ʊ��:"<<endl;
                cin>>name;
                cout<<"�������������֤"<<endl; 
                cin>>id;
                if (grade == 1) //����1�Ȳ��ŶӶ���
				{
                    info->wQgrade1 = enqueue(info->wQgrade1, name, need, id);
                } 
				else //����2�Ȳ��ŶӶ���
				{
                    info->wQgrade2 = enqueue(info->wQgrade2, name, need, id);
                }
                cout<<"�Ŷӳɹ�"<<endl; 
            } 	
        }
    }

}



//�����Լ�����ĺ����Ų�ѯ�Ƿ���ڲ����ؽڵ�
hangban *find() 
{
    char number[10];
    int i = 0;
    cout<<"�����뺽����"<<endl; 
    cin>>number;
    hangban *p = pFlight->next; //ͷ������һ���ڵ㿪ʼ����
    while (p != NULL) 
	{
        if (!strcmp(number, p->hbID))
            return p;
        p = p->next;
    }
    return NULL;
}


void addlink(CList &head, int need, char name[], char id[],char day[],int grade)
//���뵽�Ѿ���Ʊ�ͻ����� 
{
    CList new1;//����һ���½ڵ� 
    new1 = (CNode *) malloc(sizeof(CNode));
    strcpy(new1->name, name);
    strcpy(new1->ID, id);
    strcpy(new1->day,day);
    new1->num = need;
    new1->dengji = grade;
    new1->next = head->next;//ͷ���뷨�����Ա������
    head->next = new1;
    return;
}


void fightinfo(hangban *p) 
{
    cout << "���  �յ�  ���  �ɻ���  ��������  ���ؿ�  ��Ʊ��  1������  2������" << endl;
    cout << p->qidian << "  " << p->zhongdian << "  " << p->hbID << "     " << p->hbnum << "     " << p->day << "     "
                      << p->maxnum << "     " << p->less << "     " << p->lessgrade1 << "     " << p->lessgrade2 << endl;
}



LinkQueue enqueue(LinkQueue &q, char name[], int need, char id[])
//��ӣ������ŶӵȺ�Ŀͻ�������
{
    Phb new1;
    new1 = (Phb) malloc(sizeof(QhbNode));
    strcpy(new1->name, name);
    strcpy(new1->ID, id);
    new1->num = need;
    new1->next = NULL;
    q.rear->next = new1;
    q.rear = new1;
    return q;
}

void tuipiao() //��Ʊ���� 
{
    hangban *info;
    int grade;
    CNode *p1, *p2, *head;//p1Ϊ����ָ�룬p2ָ��p1��ǰ��
    char name[20];//�ͻ�����
    char id[20];//�ͻ����֤
    char day[20];
    info = find();//���ƽڵ���Ϣ��info��find�������ݺ����ŷ��ظú���ڵ��ָ��
    while (info == NULL)
	{
        cout<<"û��������࣬����������"<<endl; 
        tuipiao();
    }
    head = info->cusLinkList;//headΪ�ú���ĵĳ�Ա�������ͷָ��
    p1 = head->next;    //��ͷ����ָ�룬head->next ��ʼ����
    cout<<"�������������: "<<endl;
    cin>>name;
    cout<<"������������֤����:"<<endl; 
    cin>>id;
    cout<<"���������ʱ��"<<endl; 
    cin>>day;
    p2 = head;
    while (p1 != NULL) 
	{
		//�Ա����������֤ 
        if ((strcmp(name, p1->name) == 0) && (strcmp(id, p1->ID) == 0)&&(strcmp(day, p1->day) == 0)) break;
        p2 = p1;
        p1 = p1->next;
    }
    if (p1 == NULL) 
	{
        cout<<"�Բ�����û�ж���Ʊ�����������֤,��������ڲ���Ӧ"<<endl;
        return;
    } 
	else 
	{//��Ʊ�ɹ�
        //�ӳ˿����������Ƴ��ýڵ�
        grade = p1->dengji;
        p2->next = p1->next;
        //�ӻظú����ʣ��Ʊ
        info->less += p1->num;
        if (grade == 1) 
		{
            info->lessgrade1 += p1->num;
        } 
		else 
		{
            info->lessgrade2 += p1->num;
        }
        cout<<name<<"��Ʊ�ɹ�"<<endl; 
    }
}


int zengjiaFlight() 
{
    hangban *q;
    hangban *p = pFlight;
    int y = 1;
	cout << "������������������" << endl;
    system("pause");
    while (y != 0) 
	{
        q = new hangban;
        if (q == NULL)
            return 0;
        cout << "�����뺽����" << endl;
        cin >> q->hbID;
        int t = duibiFlight(pFlight, q->hbID);
        if (t == 0) 
		{
            cout << "�ú������Ѿ����ڣ����������뺽����" << endl;
            continue;
        }
        cout << "���������վ��" << endl;
        cin >> q->qidian;
        cout << "�������յ�վ��" << endl;
        cin >> q->zhongdian;
        cout << "�������ͺ�" << endl;
        cin >> q->hbnum;
        cout << "�������������" << endl;
        cin >> q->day;
        cout << "������˿Ͷ���" << endl;
        cin >> q->maxnum;
        q->less = q->maxnum;
        cout << "������1��Ʊ��Ŀ" <<endl;
        cin >> q->lessgrade1;
        q->lessgrade2 = q->maxnum - q->lessgrade1;
        q->next = p->next;
        p->next = q;
        cout << "�Ƿ����¼�뺽����Ϣ���������ּ�����0��ʾֹͣ����\n";
        cout << "�����룺";
        cin >> y;
    }
    return 0;
}


int shanchuFlight() 
{
    string ID;
    cout << "�����뺽��ID" << endl;
    cin >> ID;
    hangban *pre = pFlight;
    hangban *p = pre->next;
    while (p != NULL) 
	{
        if (ID == p->hbID) 
		{
            pre->next = p->next;
            delete p;
            return 1;
        }
        pre = p;
        p = p->next;
    }
    return 0;
}


int duibiFlight(hangban *flight, char ID[])
//�ԱȺ���ı�ţ���ֹ���Ӻ���ʱ�������ظ� 
{
    hangban *p = flight;
    while (p != NULL)
	{
        if (!strcmp(ID, p->hbID)) 
		{
            return 0;//����ID�ظ�
        }
        p = p->next;
    }
    //ID���ظ�
    return 1;

}


void sousuoFace() 
{
    int i;
    cout<<endl<<endl<<endl<<endl<<endl;
        cout<<"                                                    ";
        cout<<"��������"<<endl; 
        cout<<"                                  ";
        cout<<"-----------------------------------------------"<<endl;
        cout<<"                                  ";
        cout<<"|"<<"                                             "<<"|"<<endl;
		cout<<"                                  ";
		cout<<"|"<<"             1.��������                      "<<"|"<<endl;
		cout<<"                                  ";
		cout<<"|"<<"                                             "<<"|"<<endl;
		cout<<"                                  ";
		cout<<"|"<<"             2.������һ��                    "<<"|"<<endl;
		cout<<"                                  ";
		cout<<"|"<<"                                             "<<"|"<<endl;
		cout<<"                                  ";
		cout<<"-----------------------------------------------"<<endl;
		cout<<"                                  ";
		cout<<"����������ѡ��(1-2,������Ч��)"<<endl; 
		cout<<"                                  ";
		cout<<"����ѡ����:";    
    cin >> i;
    switch (i) {
        case 1:
            sousuoflight();
            system("pause");
            sousuoFace();
            break;
        case 2:
            menu();
            break;
        default:
            sousuoFace();
    }
}


void sousuoflight() 
{
    string qidian, zhongdian;
    int flag = 0;
    cout << "���������վ��:";
    cin >> qidian;
    cout << "�������յ�վ��:";
    cin >> zhongdian;
    hangban *p = pFlight->next;
    cout << "���  �յ�  ���  �ɻ���  ��������  ���ؿ�  ��Ʊ��  1������  2������" << endl;
    while (p != NULL) {
        if (qidian == p->qidian && zhongdian == p->zhongdian) 
		{
            flag = 1;  
            cout << p->qidian << "  " << p->zhongdian << "  " << p->hbID << "     " << p->hbnum << "     " << p->day << "     "
                      << p->maxnum << "     " << p->less << "     " << p->lessgrade1 << "     " << p->lessgrade2 << endl;
        }
        p = p->next;
    }
    cout <<endl <<endl;
    if (flag == 0)
        cout << "��Ǹ�������ڸú��࣡" << endl;
}


void dingpiaoFace() 
{
    int i;
    cout<<endl<<endl<<endl<<endl<<endl;
        cout<<"                                                    ";
        cout<<"��Ʊ����"<<endl; 
        cout<<"                                  ";
        cout<<"-----------------------------------------------"<<endl;
        cout<<"                                  ";
        cout<<"|"<<"             1.ȷ�϶�Ʊ                      "<<"|"<<endl;
		cout<<"                                  ";
		cout<<"|"<<"             2.��������                      "<<"|"<<endl;
		cout<<"                                  ";
		cout<<"|"<<"             3.�������                      "<<"|"<<endl;
		cout<<"                                  ";
		cout<<"|"<<"             4.�����ϼ��˵�                  "<<"|"<<endl;
		cout<<"                                  ";
		cout<<"|"<<"                                             "<<"|"<<endl;
		cout<<"                                  ";
		cout<<"-----------------------------------------------"<<endl;
		cout<<"                                  ";
		cout<<"����������ѡ��(1-4,������Ч��)"<<endl; 
		cout<<"                                  ";
		cout<<"����ѡ����:";    
    cin >> i;
    switch (i) {
        case 1:
            dingpiao();
            system("pause");
            dingpiaoFace();
            break;
        case 2:
            sousuoflight();
            system("pause");
            dingpiaoFace();
            break;
        case 3:
            printfall(pFlight);
            system("pause");
            dingpiaoFace();
            break;
        case 4:
            menu();
            break;
        default:
            dingpiaoFace();
    }
}



void tuipiaoFace()//��Ʊģ�����
{
	int i;
    cout<<endl<<endl<<endl<<endl<<endl;
        cout<<"                                                    ";
        cout<<"��Ʊ����"<<endl; 
        cout<<"                                  ";
        cout<<"-----------------------------------------------"<<endl;
        cout<<"                                  ";
        cout<<"|"<<"                                             "<<"|"<<endl;
		cout<<"                                  ";
		cout<<"|"<<"             1.������Ʊ                      "<<"|"<<endl;
		cout<<"                                  ";
		cout<<"|"<<"                                             "<<"|"<<endl;
		cout<<"                                  ";
		cout<<"|"<<"             2.�����ϼ��˵�                  "<<"|"<<endl;
		cout<<"                                  ";
		cout<<"|"<<"                                             "<<"|"<<endl;
		cout<<"                                  ";
		cout<<"-----------------------------------------------"<<endl;
		cout<<"                                  ";
		cout<<"����������ѡ��(1-2,������Ч��)"<<endl; 
		cout<<"                                  ";
		cout<<"����ѡ����:";    
        cin >> i;
    switch (i) 
	{
        case 1:
            tuipiao();
            system("PAUSE");
            tuipiaoFace();
            break;
        case 2:
            menu();
            break;
        default:
            tuipiaoFace();
    }
}


void pricusInfo() 
{
    CList p;
    hangban *info;
    info = find();
    if (info == NULL) 
	{
        cout << "û���������" << endl;
        return;
    }
    // ͷ������һ���ڵ㿪ʼ����
    p = info->cusLinkList->next;
    if (p != NULL) 
	{
        cout << "�ͻ�����   ��Ʊ����   ��λ�ȼ�       ���֤��  " << endl;
        while (p) 
		{
            cout << p->name << "\t\t" << p->num << "\t" << p->dengji << "\t" <<p->ID<< endl;
            p = p->next;
      	}
    } 
	else 
	{
        cout << "�ú���û�пͻ���Ϣ!!" << endl;
    }
}

void printfall(hangban *pflight) 
{
    hangban *p;
    p = pflight->next;
    cout << "���  �յ�  ���  �ɻ��ͺ�  ��������  ���ؿ�  ��Ʊ��  1������  2������ " << endl;
    while (p != NULL) 
	{
        cout << p->qidian << "  " << p->zhongdian << "  " << p->hbID << "      " << p->hbnum << "     " << p->day << "   "
                  << p->maxnum << "     " << p->less << "     " << p->lessgrade1 << "      " << p->lessgrade2 <<"      "<< endl;
        p = p->next;
    }
    cout << endl << endl;
}

int yonghudenglu()
{
		string account1="����";
		string passwords1="239007045";
		string account2="����";
		string passwords2="239007038";
		string account3="�˺���";
		string passwords3="239007049";
		string account4="�¼ǵ�";
		string passwords4="239007037";
		string account5="��γ�";
		string passwords5="239007036";
		string account;
		string passwords;
		cout<<endl<<endl<<endl<<endl<<endl;
        cout<<"                                                  ";
        cout<<"�û���¼ҳ��"<<endl; 
        cout<<"                                  ";
        cout<<"-----------------------------------------------"<<endl;
        cout<<"                                  ";
        cout<<"|"<<"                                             "<<"|"<<endl;
		cout<<"                                  ";
		cout<<"|"<<"                                             "<<"|"<<endl;
		cout<<"                                  ";
		cout<<"|"<<"      ��������ȷ���˺��������Խ���ϵͳ       "<<"|"<<endl;
		cout<<"                                  ";
		cout<<"|"<<"          (������ҳ������exit)               "<<"|"<<endl;
		cout<<"                                  ";
		cout<<"|"<<"                                             "<<"|"<<endl;
		cout<<"                                  ";
		cout<<"-----------------------------------------------"<<endl;
		cout<<"                                  ";
		cout<<"�������˺�:"<<endl;
		cout<<"                                  ";
		cout<<"account:"; 
		cin>>account;
		cout<<"                                  ";
		if(account=="exit")
		{
			denglu();
		 } 
		cout<<"����������:"<<endl;
		cout<<"                                  ";
		cout<<"password:"; 
		cin>>passwords;
		if((account==account1&&passwords==passwords1)||(account==account2&&passwords==passwords2)||
		(account==account3&&passwords==passwords3)||(account==account4&&passwords==passwords4)||
		 (account==account5&&passwords==passwords5))
		{
			menu();
		}
		else
		{
			cout<<"                                  ";
			cout<<"������󣬰��������������"<<endl; 
		}
} 



int guanliyuandenglu()
{
	string passwords="123456";
	string shuru;
		cout<<endl<<endl<<endl<<endl<<endl;
        cout<<"                                                 ";
        cout<<"����Ա��¼ҳ��"<<endl; 
        cout<<"                                  ";
        cout<<"-----------------------------------------------"<<endl;
        cout<<"                                  ";
        cout<<"|"<<"                                             "<<"|"<<endl;
		cout<<"                                  ";
		cout<<"|"<<"                                             "<<"|"<<endl;
		cout<<"                                  ";
		cout<<"|"<<"        ���������Ա��������֤���           "<<"|"<<endl;
		cout<<"                                  ";
		cout<<"|"<<"          (������ҳ������exit)               "<<"|"<<endl;
		cout<<"                                  ";
		cout<<"|"<<"                                             "<<"|"<<endl;
		cout<<"                                  ";
		cout<<"-----------------------------------------------"<<endl;
		cout<<"                                  ";
		cout<<"����������:"<<endl;
		cout<<"                                  ";
		cout<<"password:"; 
		cin>>shuru;
		if(shuru==passwords)
		{
			cout<<"                                  ";
			cout<<"����Ա�����֤�ɹ���"<<endl; 
			guanliyuanyemian();
		}
		else if(shuru=="exit") 
		{
			denglu();
		} 
		else
		{
			cout<<"                                  ";
			cout<<"�����֤ʧ�ܣ����������������"<<endl; 
			system("pause");
			guanliyuandenglu(); 
		 } 
} 



int guanliyuanyemian()
{
	    int i;
	    do{
	    cout<<endl<<endl<<endl<<endl<<endl;
        cout<<"                                                    ";
        cout<<"����Աҳ��"<<endl; 
        cout<<"                                  ";
        cout<<"-----------------------------------------------"<<endl;
        cout<<"                                  ";
        cout<<"|"<<"                                             "<<"|"<<endl;
		cout<<"                                  ";
		cout<<"|"<<"             1.���뺽��                      "<<"|"<<endl;
		cout<<"                                  ";
		cout<<"|"<<"             2.ɾ������                      "<<"|"<<endl;
		cout<<"                                  ";
		cout<<"|"<<"             3.�������                      "<<"|"<<endl;
		cout<<"                                  ";
		cout<<"|"<<"             4.��ѯ�ͻ���Ϣ                  "<<"|"<<endl;
		cout<<"                                  ";
		cout<<"|"<<"             5.������ҳ                      "<<"|"<<endl;
		cout<<"                                  ";
		cout<<"-----------------------------------------------"<<endl;
		cout<<"                                  ";
		cout<<"����������ѡ��(1-2,������Ч��)"<<endl; 
		cout<<"                                  ";
		cout<<"����ѡ����:";    
        cin >> i;
        switch (i) {
            case 1:
                zengjiaFlight();
                guanliyuanyemian();
            break;
                break;
            case 2:
                if (1 == shanchuFlight()) 
				{
                	cout << "ɾ���ɹ�" << endl;
                } 
				else 
				{
                	cout << "û��������࣬ɾ��ʧ�ܣ�" << endl;
                }
                system("pause");
            	guanliyuanyemian();
                break;
            case 3:
            	printfall(pFlight); 
                system("pause");
                guanliyuanyemian(); 
                break;
	        case 4:
	        	pricusInfo();
	        	system("pause");
	        	guanliyuanyemian(); 
	        	break;
			case 5:
        		denglu();
	            break; 
            default:
                guanliyuanyemian(); 
        }
    } while (true); 
}



int denglu() 
{
    int i;
    do {
    	cout<<endl<<endl<<endl;
    	cout<<"title�����տ��˶�Ʊϵͳ-����ʦ����ѧ���ݽṹ������ҵ-24.5"<<endl;
		cout<<"author�����ѣ����棬��γ�,�˺���¼ǵ�"; 
		cout<<endl<<endl<<endl;
        cout<<"                                                     ";
        cout<<"��¼ҳ��"<<endl; 
        cout<<"                                  ";
        cout<<"-----------------------------------------------"<<endl;
        cout<<"                                  ";
        cout<<"|"<<"                                             "<<"|"<<endl;
		cout<<"                                  ";
		cout<<"|"<<"             1.�û���¼                      "<<"|"<<endl;
		cout<<"                                  ";
		cout<<"|"<<"                                             "<<"|"<<endl;
		cout<<"                                  ";
		cout<<"|"<<"             2.����Ա��¼                    "<<"|"<<endl;
		cout<<"                                  ";
		cout<<"|"<<"                                             "<<"|"<<endl;
		cout<<"                                  ";
		cout<<"-----------------------------------------------"<<endl;
		cout<<"                                  ";
		cout<<"����������ѡ��(1-2,������Ч��)"<<endl; 
		cout<<"                                  ";
		cout<<"����ѡ����:";    
        cin >> i;
        switch (i) {
            case 1:
                yonghudenglu();
                system("pause");
                break;
            case 2:
                guanliyuandenglu();
                system("pause");
                break;
            default:
                denglu();
        }
    } while (true); 
}


int menu() 
{
    int i;
    do {
		cout<<endl<<endl<<endl<<endl<<endl;
        cout<<"                                             ";
        cout<<"��ӭ�������տ��˶�Ʊϵͳ"<<endl; 
        cout<<"                                  ";
        cout<<"-----------------------------------------------"<<endl;
        cout<<"                                  ";
        cout<<"|"<<"             1.��ѯ����                      "<<"|"<<endl;
		cout<<"                                  ";
		cout<<"|"<<"             2.��������                      "<<"|"<<endl;
		cout<<"                                  ";
		cout<<"|"<<"             3.��Ʊ                          "<<"|"<<endl;
		cout<<"                                  ";
		cout<<"|"<<"             4.��Ʊ                          "<<"|"<<endl;
		cout<<"                                  ";
		cout<<"|"<<"             5.�˳�ϵͳ                      "<<"|"<<endl;
		cout<<"                                  ";
		cout<<"-----------------------------------------------"<<endl;
		cout<<"                                  ";
		cout<<"����������ѡ��(1-5,������Ч��)"<<endl; 
		cout<<"                                  ";
		cout<<"����ѡ����:";    
        cin >> i;
        switch (i) {
            case 1:
                printfall(pFlight); 
                system("pause");
                menu();
                break;
            case 2:
                sousuoFace();
                system("pause");
                menu();
                break;
            case 3:
                dingpiaoFace();  // ��Ʊ����
                system("pause");
                menu();
                break; 
            case 4:
                tuipiaoFace();
				system("pause");
                menu();
                break; 
            case 5:
                denglu();
            default:
                menu(); 
        }
    } while (true); 
}

int main() 
{
	system("color F1");
    initFlight();//��ʼ���������� 
    Create(flight1);//��������Ϣ�������� 
    denglu();    //�˵�
    return 0;
}



