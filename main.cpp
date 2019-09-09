#include <JAYcreations.h>
    char temfilename[50], logfilename[50], accfilename[50], pasfilename[50], word[100];
    int logs, accounts, screen, previouscreen;
    ifstream filein;
    fstream file;
    ofstream fileout;

class Paclass
{
public:
    char word[100];
    bool allowed;
}password;
class Acclass
{
public:
    bool addtotal, hide;
    char name[100];
}accclass, accclass2;
class Loclass
{
public:
    long double newbalance;
    char details[35], account[100];
    TIMEstruct TIME;
    bool operator>(Loclass);
    bool operator<(Loclass);
    bool operator==(Loclass);
    bool operator=(Loclass);
    void refresh();
    void timeremod();
}logclass, logclass2;
void Loclass::refresh()
{
    newbalance=NULL;
    strcpy(TIME.TIME, "\0");
    strcpy(details, "\0");
    TIME.year=NULL;
    TIME.month=NULL;
    TIME.date=NULL;
    TIME.hour=NULL;
    TIME.minute=NULL;
    TIME.second=NULL;
}
void Loclass::timeremod()
{
    time_t bleh;
    bleh=time(0);
    strcpy(TIME.TIME, ctime(&bleh));
    switch (TIME.TIME[6])
    {
        case 'b':TIME.month =2; break;
        case 'y':TIME.month=5; break;
        case 'l':TIME.month=7; break;
        case 'g':TIME.month=8; break;
        case 'p':TIME.month=9; break;
        case 't':TIME.month =10; break;
        case 'v':TIME.month=11;break;
        case 'c':TIME.month=12; break;
        case 'n':if (TIME.TIME[5]=='a')
                    TIME.month=1;
                else TIME.month =6; break;
        case 'r':if (TIME.TIME[5]=='a')
                    TIME.month=3;
                else TIME.month =4; break;
    }
    TIME.year=0;
    for (int i=0; i<4; i++)
        TIME.year+=pow(10, 3-i)*(TIME.TIME[20+i]-'0');
    TIME.date=0;
    for (int i=0; i<2; i++)
        TIME.date+=pow(10, 1-i)*(TIME.TIME[8+i]-'0');
    TIME.hour=0;
    for (int i=0; i<2; i++)
        TIME.hour+=pow(10, 1-i)*(TIME.TIME[11+i]-'0');
    TIME.minute=0;
    for (int i=0; i<2; i++)
        TIME.minute+=pow(10, 1-i)*(TIME.TIME[14+i]-'0');
    TIME.second=0;
    for (int i=0; i<2; i++)
        TIME.second+=pow(10, 1-i)*(TIME.TIME[17+i]-'0');
}
bool Loclass::operator<(Loclass b)
{
    if (TIME.year<b.TIME.year)
        return true;
    else if (TIME.year==b.TIME.year)
        if (TIME.month<b.TIME.month)
            return true;
        else if (TIME.month==b.TIME.month)
            if (TIME.date<b.TIME.date)
                return true;
            else if (TIME.date==b.TIME.date)
                if (TIME.hour<b.TIME.hour)
                    return true;
                else if (TIME.hour==b.TIME.hour)
                    if (TIME.minute<b.TIME.minute)
                        return true;
                    else if (TIME.minute==b.TIME.minute)
                        if (TIME.second<b.TIME.second)
                            return true;
    return false;
}
bool Loclass::operator>(Loclass b)
{
    if (TIME.year>b.TIME.year)
        return true;
    else if (TIME.year==b.TIME.year)
        if (TIME.month>b.TIME.month)
            return true;
        else if (TIME.month==b.TIME.month)
            if (TIME.date>b.TIME.date)
                return true;
            else if (TIME.date==b.TIME.date)
                if (TIME.hour>b.TIME.hour)
                    return true;
                else if (TIME.hour==b.TIME.hour)
                    if (TIME.minute>b.TIME.minute)
                        return true;
                    else if (TIME.minute==b.TIME.minute)
                        if (TIME.second>b.TIME.second)
                            return true;
    return false;
}
bool Loclass::operator==(Loclass b)
{
    if ((TIME.year==b.TIME.year)&&(TIME.month==b.TIME.month)&&(TIME.date==b.TIME.date)&&(TIME.hour==b.TIME.hour)&&(TIME.minute==b.TIME.minute)&&(TIME.second==b.TIME.second))
        return true;
    else return false;
}
bool Loclass::operator=(Loclass b)
{
    newbalance=b.newbalance;
    strcpy(details, b.details);
    strcpy(account, b.account);
    strcpy(TIME.TIME,  b.TIME.TIME);
    TIME.date=b.TIME.date;
    TIME.hour=b.TIME.hour;
    TIME.minute=b.TIME.minute;
    TIME.month=b.TIME.month;
    TIME.second=b.TIME.second;
    TIME.year=b.TIME.year;
}
int daysinmonth(int month, int year)
{
    switch(month)
    {
    case 1:case 3:case 5:case 7:case 8:case 10:case 12:
        return 31;
    case 4:case 6:case 9:case 11:
        return 30;
    case 2:
        if (year%4==0)
            return 29;
        else return 28;
    }
}
//*
void instructions()/// ############################################
{
    system("Cls");
    cout<<"these are your instructions";
    getch();
}
bool authorized()
{
    password.allowed=true;
    file.open(pasfilename, ios::binary|ios::in);
    file.read((char*)&password, sizeof(password));
    file.close();
    if (password.allowed)
        return true;
    gotoxy(60-strlen("password : "), 18);
    cout<<"Password : ";
    getpass(word);
    system("cls");
    if (strcmp(word, password.word)==0)
        return true;
    return false;
}
int accountcount()
{
    Acclass X;
    int accounts=0;
    filein.open(accfilename, ios::binary);
    while (filein.read((char*)&X, sizeof(X)))
        accounts++;
    filein.close();
    return accounts;
}
int logcount()
{
    Loclass X;
    int lo=0;
    filein.open(logfilename, ios::binary);
    while (filein.read((char*)&X, sizeof(X)))
        lo++;
    filein.close();
    return lo;
}
int logcountspecific(char accname[100])
{
    Loclass X;
    int lo=0;
    filein.open(logfilename, ios::binary);
    while (filein.read((char*)&X, sizeof(X)))
        if (strcmp(X.account, accname)==0)
            lo++;
    filein.close();
    return lo;
}
void hidefile(char filename[50])
{
    char command[100];
    strcpy(command, "attrib +h ");
    strcat(command, filename);
    system(command);
}
int mainmenu()
{
    remove(temfilename);
    int width=15, choice=10, options=4, subchoice=4;
    for (int i=31; i<=89; i++)
    {
        gotoxy(i, 10);
        cout<<(char)196;
        gotoxy(i, 22);
        cout<<(char)196;
    }
    createbox(30, 10, 90, 22, true);
    gotoxy(58, 12); cout<<"MENU";
    gotoxy(58, width); cout<<"LOGS";
    gotoxy(56, width+1); cout<<"ACCOUNTS";
    gotoxy(56, width+2); cout<<"PASSWORD";
    gotoxy(57, width+3); cout<<"BACKUP";
    gotoxy(58, width+4); cout<<"EXIT";

    while (1)
    {
        xyz:
        if (choice==10) goto thekip;
        gotoxy(50, choice+width); cout<<"|";
        gotoxy(70, choice+width); cout<<"|";
        thekip:
        gotoxy(60, 30);

        if (choice==0)
        {
            gotoxy(65+4, width); cout<<(char)205<<(char)184<<"  Search";
            gotoxy(66+4, width+1); cout<<(char)179<<"  Yearly";
            gotoxy(66+4, width+2); cout<<(char)179<<"  Monthly";
            gotoxy(66+4, width+3); cout<<(char)179<<"  Daily";
            gotoxy(66+4, width+4); cout<<(char)179<<"  All";
            while (1)
            {
                gotoxy(80+4, subchoice+width); cout<<"|";
                gotoxy(60, 30);
                if (getch()=='\r')
                {
                    for (int i=30; i<=90; i++)for (int j=10; j<=22; j++)
                    {   gotoxy(i, j); cout<<" ";    }
                    return subchoice+6;
                }
                gotoxy(80+4, subchoice+width); cout<<" ";
                if (GetAsyncKeyState(VK_UP)&&(subchoice>0))
                {
                    getch();
                    subchoice--;
                }
                else if (GetAsyncKeyState(VK_DOWN)&&(subchoice<options+1))
                {
                    getch();
                    if (subchoice==options)
                    {
                        gotoxy(50, choice+width); cout<<" ";
                        choice++;
                        break;
                    }
                    subchoice++;
                }
                else if (GetAsyncKeyState(VK_ESCAPE))
                    continue;
            }
            gotoxy(65+4, width); cout<<"          ";
            gotoxy(66+4, width+1); cout<<"         ";
            gotoxy(66+4, width+2); cout<<"           ";
            gotoxy(66+4, width+3); cout<<"        ";
            gotoxy(66+4, width+4); cout<<"      ";
            goto xyz;
        }
        if (getch()=='\r')
        {
            for (int i=30; i<=90; i++) for (int j=10; j<=22; j++)
            {   gotoxy(i, j); cout<<" ";    }
            return choice+1;
        }
        if (choice==10) goto thekip2;
        gotoxy(50, choice+width); cout<<" ";
        gotoxy(70, choice+width); cout<<" ";
        thekip2:
        if (GetAsyncKeyState(VK_DOWN)&&(choice<options))
        {
            choice++;
            getch();
        }
        else if (GetAsyncKeyState(VK_UP))
        {
            if (choice==10)
                choice=4;
            else if (choice>0)
                choice--;
            getch();
        }
        else if (GetAsyncKeyState(VK_ESCAPE))
            continue;
    }
}
int lastdate(int month, int year)
{
    int lastdateofthemonth;
    switch (month)
    {
        case 1:lastdateofthemonth=31;break;
        case 2:if (year%4==0) lastdateofthemonth=29; else lastdateofthemonth=28; break;
        case 3:lastdateofthemonth=31;//th=31;break;
        case 4:lastdateofthemonth=30;break;
        case 5:lastdateofthemonth=31;break;
        case 6:lastdateofthemonth=30;break;
        case 7:lastdateofthemonth=31;break;
        case 8:lastdateofthemonth=31;break;
        case 9:lastdateofthemonth=30;break;//
        case 10:lastdateofthemonth=31;break;
        case 11:lastdateofthemonth=30;break;
        case 12:lastdateofthemonth=31;break;
    }
    return lastdateofthemonth;
}
void deleteaccount(char name[100])
{
    float time=0.1;
    int loc=15;
    strcpy(word, name);
    for (int i=0, j=0;i<accounts; i++)
    {
        filein.open(accfilename, ios::binary);
        filein.seekg(i*sizeof(accclass), ios::beg);
        filein.read((char*)&accclass, sizeof(accclass));
        filein.close();
        if ((strcmp(accclass.name, word))!=0)
        {
            if (j==0)
                file.open(temfilename, ios::binary|ios::out);
            else file.open(temfilename, ios::binary|ios::out|ios::app);
            file.write((char*)&accclass, sizeof(accclass));
            file.close();
            j++;
        }
    }
    gotoxy(60-strlen("temfile rewritten")/2, ++loc);
    coutput("temfile rewritten", time);
    remove(accfilename);
    gotoxy(60-strlen("accfile removed")/2, ++loc);
    coutput("accfile removed", time);
    rename(temfilename, accfilename);
    gotoxy(60-strlen("temfile renamed to accfile")/2, ++loc);
    coutput("temfile renamed to accfile", time);
    int l=logcount();
    for (int i=0, j=0; i<l; i++)
    {
        filein.open(logfilename, ios::binary);
        filein.seekg(i*sizeof(logclass), ios::beg);
        filein.read((char*)&logclass, sizeof(logclass));
        filein.close();
        if (strcmp(logclass.account, word)!=0)
        {
            if (j==0)
                file.open(temfilename, ios::binary|ios::out);
            else file.open(temfilename, ios::binary|ios::out|ios::app);
            file.write((char*)&logclass, sizeof(logclass));
            file.close();
            j++;
        }
    }
    gotoxy(60-strlen("temfile rewritten again")/2, ++loc);
    coutput("temfile rewritten again", time);
    remove(logfilename);
    gotoxy(60-strlen("logfile removed")/2, ++loc);
    coutput("logfile removed", time);
    rename(temfilename, logfilename);
    gotoxy(60-strlen("temfile renamed to logfile")/2, ++loc); loc+=2;
    coutput("temfile renamed to logfile", time);
    _sleep(500);
    gotoxy(60-(strlen(word)+strlen(" has been deleted"))/2, ++loc);
    coutput(word, time);
    coutput(" has been Deleted");
    _sleep(500);
}
void editaccount(int cursor)
{
    for (int i=21; i<100; i++)
    {
        gotoxy(i, 10); cout<<(char)196;
        gotoxy(i, 30); cout<<(char)196;
    }
    for (int i=11; i<30; i++)
    {
        gotoxy(20, i); cout<<(char)179;
        gotoxy(100, i); cout<<(char)179;
    }
    gotoxy(100, 10); cout<<(char)191;
    gotoxy(20, 30); cout<<(char)192;
    gotoxy(20, 10); cout<<(char)218;
    gotoxy(100, 30); cout<<(char)217;
    for (int i=21; i<100; i++)
        for (int j=11; j<=29; j++)
    {gotoxy(i, j); cout<<" ";}
    filein.open(accfilename, ios::binary);
    filein.seekg(cursor*sizeof(accclass), ios::beg);
    filein.read((char*)&accclass, sizeof(accclass));
    filein.close();
    gotoxy(60-strlen("edit account")/2, 12);
    cout<<"EDIT ACCOUNT";
    gotoxy(60-strlen("name : "), 20); cout<<"Name : "<<accclass.name;
    gotoxy(60-strlen("Status : "), 21); cout<<"Status : ";
    while(1)
    {
        gotoxy(60, 21);
        if (accclass.hide)
            cout<<"hidden  ";
        else cout<<"visible  ";
        if (getch()=='\r')
            break;
        if (GetAsyncKeyState(VK_UP)||GetAsyncKeyState(VK_DOWN))
        {   accclass.hide=!accclass.hide; getch();  }
    }
    gotoxy(60-strlen("Consideration in calculations : "), 22);
    cout<<"Consideration in Calculations : ";
    while(1)
    {
        gotoxy(60, 22);
        if (accclass.addtotal)
            cout<<"include  ";
        else cout<<"avoid  ";

        if (getch()=='\r')
            break;
        if (GetAsyncKeyState(VK_UP)||GetAsyncKeyState(VK_DOWN))
        {   accclass.addtotal=!accclass.addtotal; getch();   }
    }
    fileout.open(temfilename, ios::binary);
    fileout.close();
    filein.open(accfilename, ios::binary);
    for (int i=0; i<accounts; i++)
    {
        filein.seekg(i*sizeof(accclass2), ios::beg);
        filein.read((char*)&accclass2, sizeof(accclass2));
        if (i==cursor)
        {
            fileout.open(temfilename, ios::binary|ios::app);
            fileout.write((char*)&accclass, sizeof(accclass));
            fileout.close();
        }
        else
        {
            fileout.open(temfilename, ios::binary|ios::app);
            fileout.write((char*)&accclass2, sizeof(accclass2));
            fileout.close();
        }
    }
    filein.close();
    remove(accfilename);
    rename(temfilename, accfilename);
}
void recordnewaccount()
{
    char name[100];
    for (int i=21; i<100; i++)
    {
        gotoxy(i, 10); cout<<(char)196;
        gotoxy(i, 30); cout<<(char)196;
    }
    for (int i=11; i<30; i++)
    {
        gotoxy(20, i); cout<<(char)179;
        gotoxy(100, i); cout<<(char)179;
    }
    gotoxy(100, 10); cout<<(char)191;
    gotoxy(20, 30); cout<<(char)192;
    gotoxy(20, 10); cout<<(char)218;
    gotoxy(100, 30); cout<<(char)217;
    for (int i=21; i<=99; i++)
        for (int j=11; j<=29; j++)
    {gotoxy(i, j); cout<<" ";}
    gotoxy(60-strlen("create a new account")/2, 12);
    cout<<"CREATE A NEW ACCOUNT";
    gotoxy(60-strlen("name : "), 20);
    cout<<"Name : ";
    accname:
    gotoxy(60, 20);
    gets(accclass.name);
    for (int i=0; i<accounts; i++)
    {
        file.open(accfilename, ios::binary|ios::in);
        file.seekg(i*sizeof(accclass2), ios::beg);
        file.read((char*)&accclass2, sizeof(accclass2));
        file.close();
        if (strcmpi(accclass.name, accclass2.name)==0)
        {
            gotoxy(60-strlen("existence error")/2, 28);
            cout<<"EXISTENCE ERROR";
            getch();
            gotoxy(60-strlen("existence error")/2, 28);
            cout<<"               ";
            gotoxy(60, 20);
            for (int i=0; i<strlen(accclass.name); i++)
                cout<<" ";
            goto accname;
        }
    }
    gotoxy(60-strlen("Status : "), 21);
    cout<<"Status : ";
    while(1)
    {
        gotoxy(60, 21);
        if (accclass.hide)
            cout<<"hidden  ";
        else cout<<"visible  ";
        if (getch()=='\r')
            break;
        if (GetAsyncKeyState(VK_UP)||GetAsyncKeyState(VK_DOWN))
        {   accclass.hide=!accclass.hide; getch();  }
    }
    gotoxy(60-strlen("Consideration in calculations : "), 22);
    cout<<"Consideration in Calculations : ";
    while(1)
    {
        gotoxy(60, 22);
        if (accclass.addtotal)
            cout<<"include  ";
        else cout<<"avoid  ";

        if (getch()=='\r')
            break;
        if (GetAsyncKeyState(VK_UP)||GetAsyncKeyState(VK_DOWN))
        {   accclass.addtotal=!accclass.addtotal; getch();   }
    }
    fileout.open(accfilename, ios::binary|ios::app);
    fileout.write((char*)&accclass, sizeof(accclass));
    fileout.close();
    accounts++;
    system("cls");
}
void rewrite_tem_with_transactions(char[100], int&);
void pling(int space, Loclass X, Loclass logclass, char temp2filename[100])
{
    Loclass a;
    gotoxy(0,0);
    cout<<"log : ";
    ifstream x;
    x.open(logfilename, ios::binary);
    for (int i=0; x.read((char*)&a, sizeof(a)); i++)
        cout<<a.newbalance<<"-";
    x.close();
    cout<<"#\ntem : ";
    x.open(temfilename, ios::binary);
    for (int i=0; x.read((char*)&a, sizeof(a)); i++)
        cout<<a.newbalance<<"-";
    x.close();
    cout<<"#\ntem2: ";
    x.open(temp2filename, ios::binary);
    for (int i=0; x.read((char*)&a, sizeof(a)); i++)
        cout<<a.newbalance<<"-";
    x.close();
    cout<<"#";
    cout<<"\nspace : "<<space<<"\nlogs : "<<logs<<"\nX.bal : "<<X.newbalance<<"\nlogclass.bal : "<<logclass.newbalance;
    getch();
}//*/
void write(Loclass X, int i)
{
    if (i==0)
        file.open(logfilename, ios::binary|ios::out);
    else file.open(logfilename, ios::binary|ios::out|ios::app);
    file.write((char*)&X, sizeof(X));
    file.close();
}
void writelogswiththesameaccintotem(char[100]);
void insertlog(Loclass X)
{
bool editmode=false;
    writelogswiththesameaccintotem(X.account);
    int space=logs=logcountspecific(X.account);
if (editmode)pling(space, X, logclass, "log_accmanager_JAYcreations.dat");
    for (int i=0; i<logs; i++)//assigning space to insert new record
    {
        filein.open(temfilename, ios::binary);
        filein.seekg(i*sizeof(logclass), ios::beg);
        filein.read((char*)&logclass, sizeof(logclass));
        filein.close();
        if (X<logclass)
            {space=i; break;}
    }
if (editmode){cout<<"\nspace in tem : "<<space;getch();}
if (editmode)pling(space, X, logclass, "log_accmanager_JAYcreations.dat");gotoxy(0, 10);
    for (int i=logs-1; i>=space; i--)//all records after space converted to transactions
    {
        if (i!=0)
        {
            filein.open(temfilename, ios::binary);
            filein.seekg((i-1)*sizeof(logclass2), ios::beg);
            filein.read((char*)&logclass2, sizeof(logclass2));
if (editmode){cout<<"reading previous from "<<i-1<<", nb = "<<logclass2.newbalance; getch();}
        }
        else
        {
if (editmode){cout<<"lc2.nb=0"; getch();}
            logclass2.newbalance=0;
            filein.open(temfilename, ios::binary);
        }
        filein.seekg(i*sizeof(logclass), ios::beg);
        filein.read((char*)&logclass, sizeof(logclass));
        filein.close();
if (editmode){cout<<"\nlc read from "<<i<<", nb = "<<logclass.newbalance; getch();}
        logclass.newbalance-=logclass2.newbalance;
if (editmode){cout<<"\nlc updated to "<<logclass.newbalance<<" and written back"; getch();}
        file.open(temfilename, ios::binary|ios::in|ios::out);
        file.seekp(i*sizeof(logclass), ios::beg);
        file.write((char*)&logclass, sizeof(logclass));
        file.close();
    }
if (editmode)pling(space, X, logclass, "log_accmanager_JAYcreations.dat");
    for (int i=logs; i>space; i--)//to shift all records until space
    {
        filein.open(temfilename, ios::binary);
        filein.seekg((i-1)*sizeof(logclass), ios::beg);
        filein.read((char*)&logclass, sizeof(logclass));
        filein.close();
        if (i==logs)
            file.open(temfilename, ios::binary|ios::out|ios::app);
        else
        {
            file.open(temfilename, ios::binary|ios::in|ios::out);
            file.seekp(i*sizeof(logclass), ios::beg);
        }
        file.write((char*)&logclass, sizeof(logclass));
        file.close();
    }
if (editmode)pling(space, X, logclass, "log_accmanager_JAYcreations.dat");
    /*logclass.newbalance=0;//reassigning X balance
    for (int i=space-1; i>=0; i--)
    {
        filein.open(temfilename, ios::binary|ios::in);
        filein.seekg(i*sizeof(logclass2), ios::beg);
        filein.read((char*)&logclass2, sizeof(logclass2));
        filein.close();
        if (strcmp(logclass2.account, X.account)==0)
        {
            logclass.newbalance=logclass2.newbalance;
            break;
        }
    }
    X.newbalance-=logclass.newbalance;*/
    if (logs==0)
        file.open(temfilename, ios::binary|ios::out);
    else
    {
        file.open(temfilename, ios::binary|ios::in|ios::out);
        file.seekp(space*sizeof(X), ios::beg);
    }
    file.write((char*)&X, sizeof(X));//write X in position
    file.close();
if (editmode)pling(space, X, logclass, "log_accmanager_JAYcreations.dat");
    for (int i=space; i<=logs; i++)//rewriting tem with updated balances
    {
        filein.open(temfilename, ios::binary);
        if (i==0)
            logclass2.newbalance=0;
        else
        {
            filein.seekg((i-1)*sizeof(logclass2), ios::beg);
            filein.read((char*)&logclass2, sizeof(logclass2));
        }
        filein.seekg(i*sizeof(logclass), ios::beg);
        filein.read((char*)&logclass, sizeof(logclass));
        filein.close();
        logclass.newbalance+=logclass2.newbalance;
        file.open(temfilename, ios::binary|ios::in|ios::out);
        file.seekp(i*sizeof(logclass), ios::beg);
        file.write((char*)&logclass, sizeof(logclass));
        file.close();
    }
if (editmode)pling(space, X, logclass, "log_accmanager_JAYcreations.dat");
    int temlog=logs+1;
    logs=logcount();
    rename(logfilename, "log_accmanager_JAYcreations.dat");
if (editmode){cout<<"\nlog file renamed to temp2";getch();}
    int i=0, j=0, k=0;//j-temlog-logclass-tem and k-logs-logclass2-log
    while ((j<temlog)&&(k<logs))
    {
        filein.open(temfilename, ios::binary);
        filein.seekg(j*sizeof(logclass), ios::beg);
        filein.read((char*)&logclass, sizeof(logclass));
        filein.close();
        duh:if (k>=logs)
            break;
        filein.open("log_accmanager_JAYcreations.dat", ios::binary);
        filein.seekg(k*sizeof(logclass2), ios::beg);
        filein.read((char*)&logclass2, sizeof(logclass2));
        filein.close();
        if (strcmp(X.account, logclass2.account)==0)
            {k++; goto duh;}
        if (logclass<logclass2)
        {
            write(logclass, i++);
            j++;
        }
        else
        {
            write(logclass2, i++);
            k++;
        }
    }
    while (j<temlog)
    {
        filein.open(temfilename, ios::binary);
        filein.seekg(j*sizeof(logclass), ios::beg);
        filein.read((char*)&logclass, sizeof(logclass));
        filein.close();
        write(logclass, i++);
        j++;
    }
    duhh:
    while (k<logs)
    {
        filein.open("log_accmanager_JAYcreations.dat", ios::binary);
        filein.seekg(k*sizeof(logclass2), ios::beg);
        filein.read((char*)&logclass2, sizeof(logclass2));
        filein.close();
        if (strcmp(X.account, logclass2.account)==0)
            {k++; goto duhh;}
        write(logclass2, i++);
        k++;
    }//merged
if (editmode)pling(space, X, logclass, "log_accmanager_JAYcreations.dat");
    remove("log_accmanager_JAYcreations.dat");
    remove(temfilename);
}
void recordnewlog(int accursor=0)
{
    int maximum[4];
    char nostring[4], noostring[5];
    logclass.refresh();
    for (int i=0; i<4; i++)
        nostring[i]=NULL;
    for (int i=0; i<5; i++)
        noostring[i]=NULL;
    for (int i=21; i<100; i++)
    {
        gotoxy(i, 10); cout<<(char)196;
        gotoxy(i, 25); cout<<(char)196;
    }
    for (int i=11; i<25; i++)
    {
        gotoxy(20, i); cout<<(char)179;
        gotoxy(100, i); cout<<(char)179;
    }
    gotoxy(100, 10); cout<<(char)191;
    gotoxy(20, 25); cout<<(char)192;
    gotoxy(20, 10); cout<<(char)218;
    gotoxy(100, 25); cout<<(char)217;
    for (int i=21; i<=99; i++)
        for (int j=11; j<=24; j++)
    {gotoxy(i, j); cout<<" ";}
    gotoxy(60-strlen("create a new log")/2, 12);
    cout<<"CREATE A NEW LOG";
    gotoxy(50-strlen("transaction : "), 15); cout<<"Transaction : ";
    cin>>logclass.newbalance;
    if (logclass.newbalance==0)
    {   system("cls");return;}
    logclass.timeremod();
    for (int i=0; i<30; i++)
        logclass.TIME.TIME[i]=NULL;
    gotoxy(50-strlen("Account : "), 16); cout<<"Account : ";
    while (1)
    {
        filein.open(accfilename, ios::binary);
        filein.seekg(accursor*sizeof(accclass), ios::beg);
        filein.read((char*)&accclass, sizeof(accclass));
        filein.close();
        cout<<accclass.name;
        if (getch()=='\r')
        {
            strcpy(logclass.account, accclass.name);
            break;
        }
        for (int i=0; i<strlen(accclass.name); i++)
            cout<<"\b \b";
        if (GetAsyncKeyState(VK_UP)&&(accursor>0))
        {
            getch();
            accursor--;
        }
        else if (GetAsyncKeyState(VK_DOWN)&&(accursor<accounts-1))
        {
            getch();
            accursor++;
        }
    }

    gotoxy(43, 17);cout<<"Year : ";
    maximum[0]=logclass.TIME.year;
    cout<<logclass.TIME.year;
    while (getch()!='\r')
    {
        if (GetAsyncKeyState(VK_UP)&&(logclass.TIME.year<maximum[0]))
        {
            getch();
            logclass.TIME.year++;
            cout<<"\b\b\b\b";
        }
        else if(GetAsyncKeyState(VK_DOWN)&&(logclass.TIME.year>0))
        {
            getch();
            logclass.TIME.year--;
            cout<<"\b\b\b\b";
        }
        else continue;
        cout<<logclass.TIME.year;
    }

    gotoxy(42, 18); cout<<"Month : ";
    maximum[1]=logclass.TIME.month;
    cout<<logclass.TIME.month;
    while (getch()!='\r')
    {
        if (GetAsyncKeyState(VK_UP)&&((logclass.TIME.year<maximum[0])||((logclass.TIME.year==maximum[0])&&(logclass.TIME.month<maximum[1]))))
        {
            getch();
            cout<<"\b \b";
            if (logclass.TIME.month>9)
                cout<<"\b";
            logclass.TIME.month++;
            if (logclass.TIME.month==13)
            {
                gotoxy(50, 17); cout<<++logclass.TIME.year;
                gotoxy(50, 18);
                logclass.TIME.month=1;
            }
        }
        else if(GetAsyncKeyState(VK_DOWN))
        {
            getch();
            cout<<"\b \b";
            if (logclass.TIME.month>9)
                cout<<"\b";
            logclass.TIME.month--;
            if (logclass.TIME.month==0)
            {
                gotoxy(50, 17); cout<<--logclass.TIME.year;
                gotoxy(50, 18);
                logclass.TIME.month=12;
            }
        }
        else continue;
        cout<<logclass.TIME.month;
    }

    gotoxy(43, 19); cout<<"Date : ";
    cout<<logclass.TIME.date;
    while (getch()!='\r')
    {
        if (GetAsyncKeyState(VK_UP))
        {
            getch();
            cout<<"\b \b";
            if (logclass.TIME.date>9)
                cout<<"\b";
            if (logclass.TIME.date==lastdate(logclass.TIME.month, logclass.TIME.year))
                logclass.TIME.date=1;
            else logclass.TIME.date++;
            cout<<logclass.TIME.date;
        }
        else if (GetAsyncKeyState(VK_DOWN))
        {
            getch();
            cout<<"\b \b";
            if (logclass.TIME.date>9)
                cout<<"\b";
            if (logclass.TIME.date==1)
                logclass.TIME.date=lastdate(logclass.TIME.month, logclass.TIME.year);
            else logclass.TIME.date--;
            cout<<logclass.TIME.date;
        }
    }

    gotoxy(43, 20); cout<<"Hour : ";
    cout<<logclass.TIME.hour;
    while (getch()!='\r')
    {
        if (GetAsyncKeyState(VK_UP))
        {
            getch();
            cout<<"\b \b";
            if (logclass.TIME.hour>9)
                cout<<"\b";
            if (logclass.TIME.hour==23)
                logclass.TIME.hour=0;
            else logclass.TIME.hour++;
            cout<<logclass.TIME.hour;
        }
        else if (GetAsyncKeyState(VK_DOWN))
        {
            getch();
            cout<<"\b \b";
            if (logclass.TIME.hour>9)
                cout<<"\b";
            if (logclass.TIME.hour==0)
                logclass.TIME.hour=23;
            else logclass.TIME.hour--;
            cout<<logclass.TIME.hour;
        }
    }
    int f=returnday(logclass.TIME);
    //gotoxy(0, 0);cout<<"f : "<<f; getch();
    switch(f)
    {
    case 0:strcpy(logclass.TIME.TIME, "Sun "); break;
    case 1:strcpy(logclass.TIME.TIME, "Mon "); break;
    case 2:strcpy(logclass.TIME.TIME, "Tue "); break;
    case 3:strcpy(logclass.TIME.TIME, "Wed "); break;
    case 4:strcpy(logclass.TIME.TIME, "Thu "); break;
    case 5:strcpy(logclass.TIME.TIME, "Fri "); break;
    case 6:strcpy(logclass.TIME.TIME, "Sat "); break;
    }
    switch (logclass.TIME.month)
    {
    case 1:strcat(logclass.TIME.TIME, "Jan "); break;
    case 2:strcat(logclass.TIME.TIME, "Feb "); break;
    case 3:strcat(logclass.TIME.TIME, "Mar "); break;
    case 4:strcat(logclass.TIME.TIME, "Apr "); break;
    case 5:strcat(logclass.TIME.TIME, "May "); break;
    case 6:strcat(logclass.TIME.TIME, "Jun "); break;
    case 7:strcat(logclass.TIME.TIME, "Jul "); break;
    case 8:strcat(logclass.TIME.TIME, "Aug "); break;
    case 9:strcat(logclass.TIME.TIME, "Sep "); break;
    case 10:strcat(logclass.TIME.TIME, "Oct ");break;
    case 11:strcat(logclass.TIME.TIME, "Nov ");break;
    case 12:strcat(logclass.TIME.TIME, "Dec ");break;
    }
    //cout<<logclass.thetime; getch();
    if (logclass.TIME.date<10)
    {    nostring[0]='0'; nostring[1]=(char)(48+logclass.TIME.date);}
    else
    {   nostring[0]=(char)(48+(logclass.TIME.date/10)); nostring[1]=(char)(48+(logclass.TIME.date%10));}
    nostring[2]=' ';
    strcat(logclass.TIME.TIME, nostring);
    //cout<<logclass.thetime; getch();
    if (logclass.TIME.hour<10)
    {    nostring[0]='0'; nostring[1]=(char)(48+logclass.TIME.hour);}
    else
    {   nostring[0]=(char)(48+(logclass.TIME.hour/10)); nostring[1]=(char)(48+(logclass.TIME.hour%10));}
    nostring[2]=':';
    strcat(logclass.TIME.TIME, nostring);
    //cout<<logclass.thetime; getch();
    if (logclass.TIME.minute<10)
    {    nostring[0]='0'; nostring[1]=(char)(48+logclass.TIME.minute);}
    else
    {   nostring[0]=(char)(48+(logclass.TIME.minute/10)); nostring[1]=(char)(48+(logclass.TIME.minute%10));}
    nostring[2]=':';
    strcat(logclass.TIME.TIME, nostring);
    //cout<<logclass.thetime; getch();
    if (logclass.TIME.second<10)
    {    nostring[0]='0'; nostring[1]=(char)(48+logclass.TIME.second);}
    else
    {   nostring[0]=(char)(48+(logclass.TIME.second/10)); nostring[1]=(char)(48+(logclass.TIME.second%10));}
    nostring[2]=' ';
    strcat(logclass.TIME.TIME, nostring);

    noostring[0]=(char)(48+(logclass.TIME.year/1000));
    noostring[1]=(char)(48+((logclass.TIME.year%1000)/100));
    noostring[2]=(char)(48+((logclass.TIME.year%100)/10));
    noostring[3]=(char)(48+(logclass.TIME.year%10));
    strcat(logclass.TIME.TIME, noostring);//cout<<logclass.thetime; getch();

    gotoxy(40, 21); cout<<"Details : ";
    cin.ignore();
    autogets(logclass.details, "[       30 characters        ]");
    insertlog(logclass);
    system("cls");
}
void writelogswiththesameaccintotem(char acname[100])
{
    Loclass x;
    fileout.open(temfilename, ios::binary);
    fileout.close();
    logs=logcount();
    for (int j=0; j<logs; j++)
    {
        filein.open(logfilename, ios::binary);
        filein.seekg(j*sizeof(x), ios::beg);
        filein.read((char*)&x, sizeof(x));
        filein.close();
        if (strcmp(acname, x.account)==0)
        {
            fileout.open(temfilename, ios::binary|ios::app);
            fileout.write((char*)&x, sizeof(x));
            fileout.close();
            //gotoxy(0, 34); cout<<"x balance:"<<x.newbalance; getch();
        }
    }
}
void displayaccname(int thatacrecordthing)
{
    filein.open(accfilename, ios::binary);
    filein.seekg(thatacrecordthing*sizeof(accclass), ios::beg);
    filein.read((char*)&accclass, sizeof(accclass));
    filein.close();
    if (thatacrecordthing!=0)
        {gotoxy(60-strlen(accclass.name)/2-2, 1); cout<<"<";}
    gotoxy(60-strlen(accclass.name)/2, 1); cout<<accclass.name;
    if (thatacrecordthing!=accounts-1)
        {gotoxy(60+strlen(accclass.name)/2+1, 1); cout<<">";}
}
void rewrite_tem_with_transactions(char acname[100], int &logs)
{
    Loclass X, x;
    logs=logcountspecific(acname);
    fileout.open("bleh.dat", ios::binary);
    fileout.close();
    for (int j=0; j<logs; j++)
    {
        filein.open(temfilename, ios::binary);
        filein.seekg(j*sizeof(X), ios::beg);
        filein.read((char*)&X, sizeof(X));
        filein.close();
        //gotoxy(0, 34); cout<<"logi:"<<logclass.newbalance;
        if (j==0)
            x.newbalance=0;
        else
        {
            filein.open(temfilename, ios::binary);
            filein.seekg((j-1)*sizeof(x), ios::beg);
            filein.read((char*)&x, sizeof(x));
            filein.close();
        }//cout<<" logi-1:"<<logclass2.newbalance;
        X.newbalance-=x.newbalance;
        //cout<<" final:"<<logclass.newbalance;getch();
        fileout.open("bleh.dat", ios::binary|ios::app);
        fileout.write((char*)&X, sizeof(X));
        fileout.close();
    }
    remove(temfilename);
    rename("bleh.dat", temfilename);
}
int daycode(Loclass theclass)//gives back the code of the day in dlog
{
    int result=(((theclass.TIME.year-1)/4)*1461);
    result+=(((theclass.TIME.year+3)%4)*365);
    for (int i=1; i<theclass.TIME.month; i++)
        result+=daysinmonth(i, theclass.TIME.year);
    result+=theclass.TIME.date;
    return result;
}
int cursorconvert(int y, int m)
{
    int result=(((y-1)/4)*1461);
    result+=(((y+3)%4)*365);
    for (int i=1; i<m; i++)
        result+=daysinmonth(i, y);
    result+=1;
    return result;
}
int searchresult(int &acrecord)
{
bool editmode=false;
    logs=logcount();
    int choice=1, cursor[2];
    createbox(30, 10, 90, 22, true);
    gotoxy(34, 16);cout<<"SEARCH "<<(char)205<<(char)181<<" Amount";
    gotoxy(42, 15); cout<<(char)218<<" Time";
    gotoxy(42, 17); cout<<(char)192<<" Detail";
    while (1)
    {
        gotoxy(52, 15+choice); cout<<"|";
        gotoxy(119, 34);
        if (getch()=='\r')
            break;
        gotoxy(52, 15+choice); cout<<" ";
        if (GetAsyncKeyState(VK_UP)&&(choice>0))
        {
            getch();
            choice--;
        }
        else if (GetAsyncKeyState(VK_DOWN)&&(choice<2))
        {
            getch();
            choice++;
        }
        else if (GetAsyncKeyState(VK_ESCAPE))
            return -1;
    }
    gotoxy(52, 15);if (choice==0)cout<<(char)194;else cout<<(char)191;
    gotoxy(52, 16);if (choice==1)cout<<(char)195;else cout<<(char)179;
    gotoxy(52, 17);if (choice==2)cout<<(char)193;else cout<<(char)217;
    gotoxy(53, 15+choice); cout<<(char)196;
    TIMEstruct time;
    long double amount;
    char detail[35];
    switch(choice)
    {
    case 0:///Time
        break;
    case 1:///Amount
        gotoxy(54, 16); cout<<(char)194<<" Transaction";
        gotoxy(54, 17); cout<<(char)192<<" Amount";
        choice=0;
        while (1)
        {
            gotoxy(68, 16+choice); cout<<"|";
            gotoxy(119, 34);
            if (getch()=='\r')
                break;
            gotoxy(68, 16+choice); cout<<" ";
            if (GetAsyncKeyState(VK_UP)||GetAsyncKeyState(VK_DOWN))
                {getch();if (choice==0) choice=1;else choice=0;}
            else if (GetAsyncKeyState(VK_ESCAPE))
                return -1;
        }
        gotoxy(68, 16); cout<<(char)191;
        gotoxy(68, 17); cout<<(char)180;
        gotoxy(68, 18); cout<<(char)217;
        gotoxy(55, 18); for (int i=0; i<13; i++) cout<<(char)196;
        gotoxy(54, 18); cout<<(char)218;
        gotoxy(54, 19); cout<<(char)192<<" ";
        cin>>amount;

        createbox(30, 10, 90, 22, true);
        for (int i=0, j=0; i<logs; i++) // write required files into tem
        {
            filein.open(logfilename, ios::binary);
            filein.seekg(i*sizeof(logclass), ios::beg);
            filein.read((char*)&logclass, sizeof(logclass));
            filein.close();
if (editmode){gotoxy(0, 0); cout<<"read from pos "<<i<<"\nBalance : "<<logclass.newbalance;getch();}
            if (choice==0)// if transactions are checked
            {
                logclass2.newbalance=0;
if (editmode){gotoxy(0, 2); cout<<"transactions checked";getch();}
                if (i>0)//if previous records exist
                {
if (editmode){gotoxy(0, 3); cout<<"looking through previous records..."; getch();}
                    for (int k=i-1; k>=0; k--)
                    {
                        filein.open(logfilename, ios::binary);
                        filein.seekg(k*sizeof(logclass2), ios::beg);
                        filein.read((char*)&logclass2, sizeof(logclass2));
                        filein.close();
                        if (strcmp(logclass2.account, logclass.account)==0)
                            break;
                        else logclass2.newbalance=0;
                    }
                }
                logclass.newbalance-=logclass2.newbalance;
if (editmode){gotoxy(0, 4); cout<<"updated balance : "<<logclass.newbalance;getch();}
            }
if (editmode){gotoxy(0, 5); cout<<"search amount : "<<amount<<", lc.newbalance : "<<logclass.newbalance; getch();}
            if ((amount==logclass.newbalance)||(amount==-logclass.newbalance))
            {
if (editmode){gotoxy(0, 6); cout<<"values compard same !"; getch();}
                if (j==0)
                    file.open(temfilename, ios::binary|ios::out);
                else file.open(temfilename, ios::binary|ios::out|ios::app);
                file.write((char*)&logclass, sizeof(logclass));
                file.close();
                j++;
if (editmode){gotoxy(0, 7); cout<<"File written, present no of logs : "<<j<<", i : "<<i;getch();}
            }
            if (i==logs-1)
                logs=j; // break; removed.
        }
        cursor[0]=cursor[1]=0;
        if (logs!=0)
        {
            for (int i=12; i<=20; i++)
            {gotoxy(62, i); cout<<(char)179;}//divider line
            for (bool newscreen=true; ;)
            {
                if (newscreen)
                {
                    newscreen=false;
                    for (int i=0; ((i<9)&&(i<logs)); i++)
                    {
                        gotoxy(34, i+12);cout<<"                           ";
                        gotoxy(65, i+12);cout<<"                        ";
                    }
                    for (int i=cursor[0]; ((i<cursor[0]+9)&&(i<logs)); i++)
                    {
                        filein.open(temfilename, ios::binary);
                        filein.seekg(i*sizeof(logclass), ios::beg);
                        filein.read((char*)&logclass, sizeof(logclass));
                        filein.close();
                        gotoxy(34, i+12-cursor[0]); cout<<setw(27)<<logclass.newbalance;
                        gotoxy(65, i+12-cursor[0]); cout<<logclass.TIME.TIME;
                    }
                }
                gotoxy(32, 12+cursor[1]-cursor[0]); cout<<">";
                gotoxy(119, 34);
                if (getch()=='\r')
                {
                    filein.open(temfilename, ios::binary);
                    filein.seekg(cursor[1]*sizeof(logclass), ios::beg);
                    filein.read((char*)&logclass2, sizeof(logclass2));
                    filein.close();
                    remove(temfilename);
                    for (int i=0; i<accounts; i++)
                    {
                        filein.open(accfilename, ios::binary);
                        filein.seekg(i*sizeof(accclass), ios::beg);
                        filein.read((char*)&accclass, sizeof(accclass));
                        filein.close();
                        if (strcmp(accclass.name, logclass2.account)==0)
                        {acrecord=i; break;}
                    }
                    return daycode(logclass2);
                }
                gotoxy(32, 12+cursor[1]-cursor[0]); cout<<" ";
                if (GetAsyncKeyState(VK_ESCAPE))
                    return -1;
                else if (GetAsyncKeyState(VK_UP)&&(cursor[1]>0))
                {
                    getch();
                    cursor[1]--;
                    if (cursor[1]<cursor[0])
                    { cursor[0]--; newscreen=true;}
                }
                else if (GetAsyncKeyState(VK_DOWN)&&(cursor[1]<logs-1))
                {
                    getch();
                    cursor[1]++;
                    if (cursor[1]>cursor[0]+9)
                    {cursor[0]++; newscreen=true;}
                }
                else if (GetAsyncKeyState(VK_RIGHT)||GetAsyncKeyState(VK_LEFT))
                    getch();
            }
        }
        else
        {
            gotoxy(51, 16);
            cout<<"No such logs found";
        }
        getch();
        break;
    case 2:///Detail
        break;
    }
}
int main()
{
    signature(3);
    gotoxy(33, 14);
    coutput("EXPENSE MANAGER", 3);
    _sleep(200);
    gotoxy(36, 16);
    coutput("v17.12.29", 5);
    _sleep(800);
    system("mode 120, 35");

    int logcursor[2], accountcursor[2], acrecord=-1, maxx, minn, maxday, minday;
    long double sum1, sum2;
    bool jump=false, justjump=false;
    strcpy(logfilename, "logfiles_JAYcreations.dat");
    strcpy(accfilename, "accfiles_JAYcreations.dat");
    strcpy(pasfilename, "passfile_JAYcreations.dat");
    strcpy(temfilename, "temfiles_JAYcreations.dat");
    file.open(logfilename, ios::binary);
    file.close();
    file.open(accfilename, ios::binary);
    file.close();
    logs=logcount();
    accounts=accountcount();
    if (accounts==0)
    {
        instructions();
        recordnewaccount();
    }
    accountcursor[1]=accounts;
    accountcursor[0]=accountcursor[1]-25;//
    if (accountcursor[0]<0) accountcursor[0]=0;

    if (!authorized())
        return 0;
    system("cls");
    mainmenu:
    hidefile(logfilename);
    hidefile(accfilename);
    hidefile(pasfilename);
    screen=mainmenu();
    if (screen!=previouscreen)
    {
        if (screen!=4)
        {
            system("cls");
            previouscreen=screen;
        }
    }
    if (screen>=5)
    {
        if (acrecord<0)
            acrecord=0;
        if (accountcount()==0)
        {
            recordnewaccount();
            goto mainmenu;
        }
    }
    switch(screen)
    {
    case 2:account:///ACCOUNTS
        for (int i=0; i<120; i++)
        {
            gotoxy(i, 3); cout<<(char)196;
            gotoxy(i, 33); cout<<(char)196;
        }
        gotoxy(56, 1);
        cout<<"ACCOUNTS";
        gotoxy(0, 34);
        accounts=accountcount();
        cout<<"Account count - "<<accounts;

        for (bool newscreen=true; 1; )
        {
            if (newscreen)
            {
                newscreen=false;
                for (int i=accountcursor[0]; (i<accountcursor[0]+25)&&(i<=accounts); i++)
                {
                    if (i<accounts)
                    {
                        gotoxy(10, i-accountcursor[0]+6);
                        for (int j=0; j<100; j++) cout<<" ";
                    }
                    else
                    {
                        gotoxy(60-strlen("Add a new Account")/2, i+6-accountcursor[0]);
                        cout<<"                 ";
                    }
                }
                for (int i=accountcursor[0]; (i<accountcursor[0]+25)&&(i<accounts); i++)
                {
                    file.open(accfilename, ios::binary|ios::in);
                    file.seekg((i*sizeof(accclass)), ios::beg);
                    file.read((char*)&accclass, sizeof(accclass));
                    file.close();
                    //cout<<"\tx, y : "<<60-strlen(accclass.name)/2<<", "<<i-accountcursor[0]+6;getch();
                    gotoxy(60-strlen(accclass.name)/2, i-accountcursor[0]+6);
                    cout<<accclass.name;
                }
            }
            if (accountcursor[1]==accounts)
            {
                gotoxy(60-strlen("Add a new Account")/2, accountcursor[1]+6-accountcursor[0]);
                cout<<"ADD A NEW ACCOUNT";
            }
            gotoxy(20, 6+accountcursor[1]-accountcursor[0]); if (accountcursor[1]!=accounts)cout<<"DELETE <"; else cout<<"       <";
            gotoxy(120-28, 6+accountcursor[1]-accountcursor[0]); if (accountcursor[1]!=accounts)cout<<"> EDIT";else cout<<">";
            gotoxy(119, 34);
            if (getch()=='\r')
                if (accountcursor[1]==accounts)
                {
                    recordnewaccount();
                    previouscreen=-1;
                    goto account;
                }
                else
                {
                    createbox(20, 10, 100, 20, true);
                    gotoxy(59-strlen("account details")/2, 12);
                    cout<<"ACCOUNT DETAILS";
                    file.open(accfilename, ios::binary|ios::in);
                    file.seekg(accountcursor[1]*sizeof(accclass), ios::beg);
                    file.read((char*)&accclass, sizeof(accclass));
                    file.close();
                    gotoxy(60-7, 15); cout<<"Name : "<<accclass.name;
                    gotoxy(60-7, 16); cout<<"Hide : "; if (accclass.hide) cout<<"TRUE"; else cout<<"FALSE";
                    gotoxy(60-12, 17);cout<<"Add total : "; if (accclass.addtotal) cout<<"TRUE"; else cout<<"FALSE";
                    getch();
                    system("Cls");
                    goto account;
                }
            gotoxy(20, 6+accountcursor[1]-accountcursor[0]); cout<<"        ";
            gotoxy(120-28, 6+accountcursor[1]-accountcursor[0]); cout<<"      ";
            if (accountcursor[1]==accounts)
            {
                gotoxy(60-strlen("add a new account")/2, accountcursor[1]+6-accountcursor[0]);
                cout<<"                 ";
            }
            if (GetAsyncKeyState(VK_ESCAPE))
                goto mainmenu;
            if (GetAsyncKeyState(VK_DOWN)&&(accountcursor[1]<accounts))
            {
                getch();
                accountcursor[1]++;
                if (accountcursor[1]>=accountcursor[0]+25)
                {   accountcursor[0]++; newscreen=true;}
            }
            else if(GetAsyncKeyState(VK_UP)&&(accountcursor[1]>0))
            {
                getch();
                accountcursor[1]--;
                if (accountcursor[1]<accountcursor[0])
                {   accountcursor[0]--; newscreen=true;}
            }
            else if (GetAsyncKeyState(VK_LEFT))
            {
                getch();
                system("cls");
                if (accountcursor[1]!=accounts)
                    if (!authorized())
                        goto account;
                    else
                    {
                        filein.open(accfilename, ios::binary);
                        filein.seekg(accountcursor[1]*sizeof(accclass), ios::beg);
                        filein.read((char*)&accclass, sizeof(accclass));
                        filein.close();
                        gotoxy(60-(strlen("delete account    ?")+strlen(accclass.name))/2, 12);
                        cout<<"Delete Account \""<<accclass.name<<"\" ?";
                        gotoxy(58, 13);
                        gets(word);
                        if (no(word))
                        {
                            system("cls");
                            goto account;
                        }
                        else
                        {
                            deleteaccount(accclass.name);
                            acrecord=-1;
                            system("cls");
                            goto account;
                        }
                    }
            }
            else if (GetAsyncKeyState(VK_RIGHT))
            {
                getch();
                if (accountcursor[1]!=accounts)
                    if (!authorized())
                        goto account;
                    else
                    {
                        editaccount(accountcursor[1]);
                        system("cls");
                        goto account;
                    }
            }
        }
    case 3:///Password
        if (!authorized())
        {
            system("cls");
            gotoxy(60-strlen("unauthorized access")/2, 17);
            _sleep(300);
            cout<<("UNAUTHORIZED ACCESS");
            _sleep(800);
            gotoxy(60-strlen("terminating ...")/2, 18);
            coutput("TERMINATING ...", 3);
            return 0;
        }
        repass:
        gotoxy(60-strlen("new password : "), 17);
        cout<<"New Password : ";
        getpass(password.word);
        gotoxy(60-strlen("confirm password : "), 18);
        cout<<"Confirm Password : ";
        getpass(word);
        if (strcmp(word, password.word)!=0)
        {   gotoxy(60-strlen("mismatch")/2, 20); cout<<"MISMATCH"; _sleep(200); system("cls"); goto repass;      }
        if (strlen(word)<1)
        {   gotoxy(60-strlen("password removed")/2, 20); cout<<"Password Removed"; getch(); password.allowed=true; }
        else
        {   gotoxy(60-strlen("password changed")/2, 20); cout<<"Password Changed"; getch(); password.allowed=false;}
        remove(pasfilename);
        file.open(pasfilename, ios::binary|ios::out);
        file.write((char*)&password, sizeof(password));
        file.close();
        break;
    case 4:///BACKUP
        maxx=0;
        createbox(30, 10, 90, 22, true);
        gotoxy(60, 15); cout<<"SET";
        gotoxy(60, 16); cout<<"RESTORE";
        while (1)
        {
            gotoxy(58, 15+maxx); cout<<"|"; gotoxy(119, 34);
            if (getch()=='\r')
                break;
            gotoxy(58, 15+maxx); cout<<" ";
            if ((GetAsyncKeyState(VK_UP))||(GetAsyncKeyState(VK_DOWN)))
            {
                getch();
                if (maxx) maxx=0; else maxx=1;
            }
            else if (GetAsyncKeyState(VK_ESCAPE))
                goto mainmenu;
        }
        createbox(30, 10, 90, 22, true);
        if (maxx==0) //set backup
        {
            logs=logcount();
            filein.open(logfilename, ios::binary|ios::in);
            file.open("logfiles_JAYcreations.dat.backup", ios::binary|ios::out);
            for (int i=0; i<logs; i++)
            {
                filein.read((char*)&logclass, sizeof(logclass));
                file.write((char*)&logclass, sizeof(logclass));
            }
            filein.close();
            file.close();
            system("attrib +h logfiles_JAYcreations.dat.backup");
            accounts=accountcount();
            filein.open(accfilename, ios::binary|ios::in);
            file.open("accfiles_JAYcreations.dat.backup", ios::binary|ios::out);
            for (int i=0; i<accounts; i++)
            {
                filein.read((char*)&accclass, sizeof(accclass));
                file.write((char*)&accclass, sizeof(accclass));
            }
            filein.close();
            file.close();
            system("attrib +h accfiles_JAYcreations.dat.backup");
            gotoxy(55, 15); coutput("Backup Set");
            getch();
            goto mainmenu;
        }
        else // restore backup
        {
            if (authorized())
            {
                remove(logfilename);
                rename("logfiles_JAYcreations.dat.backup", logfilename);
                remove(accfilename);
                rename("accfiles_JAYcreations.dat.backup", accfilename);
                gotoxy(50, 15); coutput("Restoration Complete");
                getch();
            }
            goto mainmenu;
        }
        getch();
    case 5:///EXIT
        remove(temfilename);
        return 0;
    case 6:///SEARCH
        logcursor[1]=searchresult(acrecord);
        if (logcursor[1]==-1)
            goto mainmenu;
        jump=true;
        previouscreen=5;
        system("cls");
        goto dlog;
    case 7:ylog:///YEARLY LOG
        if (logcount()<=0)
            goto log;
        displayaccname(acrecord);
        writelogswiththesameaccintotem(accclass.name);
        rewrite_tem_with_transactions(accclass.name, logs);
        ///assign max and min year
        maxx=0; minn=2147483647;//maximum int value
        for (int i=0; i<logs; i++)
        {
            filein.open(temfilename, ios::binary);
            filein.seekg(i*sizeof(logclass), ios::beg);
            filein.read((char*)&logclass, sizeof(logclass));
            filein.close();
            if (maxx<logclass.TIME.year) maxx=logclass.TIME.year;
            if (minn>logclass.TIME.year) minn=logclass.TIME.year;
        }
        logcursor[1]=maxx;
        logcursor[0]=(maxx-minn>25)?(logcursor[1]-24):minn;
        ///display
        gotoxy(0, 4);
        for (int i=0; i<120; i++)
            cout<<(char)196;
        for (int i=5; i<35; i++)
        {
            gotoxy(10, i); cout<<(char)179;
            gotoxy(47, i); cout<<(char)179;
            gotoxy(83, i); cout<<(char)179;
        }
        gotoxy(101, 3); cout<<"-"; gotoxy(65, 3); cout<<"+"; gotoxy(28, 3); cout<<"NET";
        for (bool newscreen=true; 1; )
        {
            if (newscreen)
            {
                newscreen=false;
                for (int i=logcursor[0]; ((i<logcursor[0]+25)&&(i<=maxx)); i++)
                {
                    gotoxy(3, 6+i-logcursor[0]); cout<<"    ";
                    //display + and -
                    gotoxy(50, 6+i-logcursor[0]); cout<<"                              ";
                    gotoxy(87, 6+i-logcursor[0]); cout<<"                              ";
                    gotoxy(13, 6+i-logcursor[0]); cout<<"                               ";
                }
                for (int i=logcursor[0]; ((i<logcursor[0]+25)&&(i<=maxx)); i++)
                {
                    gotoxy(3, 6+i-logcursor[0]); cout<<i;
                    sum1=sum2=0;
                    for (int j=0; j<logs; j++)//loop through logs to find + and -
                    {
                        filein.open(temfilename, ios::binary);
                        filein.seekg(j*sizeof(logclass), ios::beg);
                        filein.read((char*)&logclass, sizeof(logclass));
                        filein.close();
                        if (logclass.TIME.year==i)
                            if (logclass.newbalance<0)
                                sum2-=logclass.newbalance;
                            else sum1+=logclass.newbalance;
                    }
                    //display + and -
                    gotoxy(13, 6+i-logcursor[0]); cout<<setw(30)<<abs(sum1-sum2); if (sum1-sum2<0) cout<<'-'; else cout<<'+';
                    gotoxy(50, 6+i-logcursor[0]); if (sum1>0) cout<<setw(30)<<sum1;
                    gotoxy(87, 6+i-logcursor[0]); if (sum2>0) cout<<setw(30)<<sum2;
                }
            }
            gotoxy(9, 6+logcursor[1]-logcursor[0]); cout<<"<";
            gotoxy(45, 6+logcursor[1]-logcursor[0]); cout<<"<";
            gotoxy(81, 6+logcursor[1]-logcursor[0]); cout<<"<";
            gotoxy(118, 6+logcursor[1]-logcursor[0]); cout<<"<";
            gotoxy(119, 34);
            if (getch()=='\r')
            {
                remove(temfilename);
                logcursor[0]=logcursor[1]*12+1;
                logcursor[1]=logcursor[0]+11;
                jump=true;
                previouscreen=6;
                system("cls");
                goto mlog;
            }
            gotoxy(9, 6+logcursor[1]-logcursor[0]); cout<<" ";
            gotoxy(45, 6+logcursor[1]-logcursor[0]); cout<<" ";
            gotoxy(81, 6+logcursor[1]-logcursor[0]); cout<<" ";
            gotoxy(118, 6+logcursor[1]-logcursor[0]); cout<<" ";
            if (GetAsyncKeyState(VK_ESCAPE))
            {
                remove(temfilename);
                goto mainmenu;
            }
            else if (GetAsyncKeyState(VK_UP)&&(logcursor[1]>minn))
            {
                getch();
                logcursor[1]--;
                if (logcursor[1]<logcursor[0])
                {   logcursor[0]--; newscreen=true;}
            }
            else if (GetAsyncKeyState(VK_DOWN)&&(logcursor[1]<maxx))
            {
                getch();
                logcursor[1]++;
                if (logcursor[1]>=logcursor[0]+25)
                {   logcursor[0]++; newscreen=true;}
            }
            else if (GetAsyncKeyState(VK_RIGHT)&&(acrecord<accounts-1))
            {
                getch();
                acrecord++;
                system("cls");
                goto ylog;
            }
            else if (GetAsyncKeyState(VK_LEFT)&&(acrecord>0))
            {
                getch();
                acrecord--;
                system("cls");
                goto ylog;
            }
        }
    case 8:mlog:///MONTHLY LOG
        if (logcount()<=0)
            goto log;
        ///display
        displayaccname(acrecord);
        writelogswiththesameaccintotem(accclass.name);
        rewrite_tem_with_transactions(accclass.name, logs);
        ///assigning max and minimum months.
        maxx=0; minn=2147483647;//maximum int value
        for (int i=0; i<logs; i++)
        {
            filein.open(temfilename, ios::binary);
            filein.seekg(i*sizeof(logclass), ios::beg);
            filein.read((char*)&logclass, sizeof(logclass));
            filein.close();
            if (minn>logclass.TIME.year*12+logclass.TIME.month) minn=logclass.TIME.year*12+logclass.TIME.month;
            if (maxx<logclass.TIME.year*12+logclass.TIME.month) maxx=logclass.TIME.year*12+logclass.TIME.month;
        }
        if (!jump)
        {
            logcursor[1]=maxx;
            logcursor[0]=(maxx-minn>25)?(logcursor[1]-24):minn;
        }
        else
        {
            jump=false;
            if (logcursor[1]>maxx)
                logcursor[1]=maxx;
        }
        ///display
        gotoxy(0, 4);
        for (int i=0 ;i<120; i++)
            cout<<(char)196;
        for (int i=5; i<35; i++)
        {
            gotoxy(12, i); cout<<(char)179;
            gotoxy(48, i); cout<<(char)179;
            gotoxy(84, i); cout<<(char)179;
        }
        gotoxy(28, 3); cout<<"NET"; gotoxy(66, 3); cout<<"+"; gotoxy(102, 3); cout<<"-";
        for (bool newscreen=true; 1; )
        {
            if (newscreen)
            {
                newscreen=false;
                for (int i=logcursor[0]; ((i<logcursor[0]+25)&&(i<=maxx)); i++)//erasing previous data
                {
                    gotoxy(1, 7+i-logcursor[0]); cout<<"    ";
                    gotoxy(14, 7+i-logcursor[0]); cout<<"                               ";
                    gotoxy(51, 7+i-logcursor[0]); cout<<"                               ";
                    gotoxy(86, 7+i-logcursor[0]); cout<<"                               ";
                }
                for (int i=logcursor[0]; ((i<logcursor[0]+25)&&(i<=maxx)); i++)
                {
                    if ((i==logcursor[0])||(i%12==1))
                    {
                        gotoxy(1, 7+i-logcursor[0]);//cout<<i; getch(); gotoxy(1, 7+i-logcursor[0]);
                        if (i%12==0)
                            cout<<i/12-1;
                        else cout<<i/12;//cout<<(i%12==0)?(i/12)-1:i/12;
                    }
                    gotoxy(7, 7+i-logcursor[0]);
                    switch(i%12)
                    {
                        case 0:cout<<"DEC"; break;
                        case 1:cout<<"JAN"; break;
                        case 2:cout<<"FEB"; break;
                        case 3:cout<<"MAR"; break;
                        case 4:cout<<"APR"; break;
                        case 5:cout<<"MAY"; break;
                        case 6:cout<<"JUN"; break;
                        case 7:cout<<"JUL"; break;
                        case 8:cout<<"AUG"; break;
                        case 9:cout<<"SEP"; break;
                        case 10:cout<<"OCT";break;
                        case 11:cout<<"NOV";break;
                    }
                }// different loop to make display less quirky
                for (int i=logcursor[0]; ((i<logcursor[0]+25)&&(i<=maxx)); i++)
                {
                    sum1=sum2=0;
                    for (int j=0; j<logs; j++)//loop through logs to find + and -
                    {
                        filein.open(temfilename, ios::binary);
                        filein.seekg(j*sizeof(logclass), ios::beg);
                        filein.read((char*)&logclass, sizeof(logclass));
                        filein.close();
                        if (i==logclass.TIME.year*12+logclass.TIME.month)
                            if (logclass.newbalance<0)
                                sum2-=logclass.newbalance;
                            else sum1+=logclass.newbalance;
                        logclass.refresh();
                    }
                    //display + and -
                    gotoxy(13, 7+i-logcursor[0]); cout<<setw(30)<<abs(sum1-sum2); if(sum1-sum2<0) cout<<'-'; else  cout<<'+';
                    gotoxy(50, 7+i-logcursor[0]); if (sum1>0) cout<<setw(30)<<sum1;
                    gotoxy(86, 7+i-logcursor[0]); if (sum2>0) cout<<setw(30)<<sum2;
                }
            }
            //gotoxy(0, 34); cout<<"logcursor[0]="<<logcursor[0]<<"logcursor[1]="<<logcursor[1]<<" max="<<maxx;
            gotoxy(11, 7+logcursor[1]-logcursor[0]); cout<<"<";
            gotoxy(45, 7+logcursor[1]-logcursor[0]); cout<<"<";
            gotoxy(81, 7+logcursor[1]-logcursor[0]); cout<<"<";
            gotoxy(117, 7+logcursor[1]-logcursor[0]); cout<<"<";
            gotoxy(119, 34);
            if (getch()=='\r')
            {
                remove(temfilename);
                logcursor[0]=cursorconvert(logcursor[1]/12, (logcursor[1]+11)%12+1);
                logcursor[1]=logcursor[0]+daysinmonth((logcursor[1]+11)%12+1, logcursor[1]/12)-1;
                if (daysinmonth((logcursor[1]+11)%12+1, logcursor[1]/12)>30)
                    logcursor[0]++;
                jump=true;
                previouscreen=7;
                system("cls");
                goto dlog;
            }
            gotoxy(11, 7+logcursor[1]-logcursor[0]); cout<<" ";
            gotoxy(45, 7+logcursor[1]-logcursor[0]); cout<<" ";
            gotoxy(81, 7+logcursor[1]-logcursor[0]); cout<<" ";
            gotoxy(117, 7+logcursor[1]-logcursor[0]); cout<<" ";
            if (GetAsyncKeyState(VK_ESCAPE))
            {
                remove(temfilename);
                goto mainmenu;
            }
            else if (GetAsyncKeyState(VK_UP)&&(logcursor[1]>minn))
            {
                getch();
                logcursor[1]--;
                if (logcursor[1]<logcursor[0])
                {   logcursor[0]--; newscreen=true;}
            }
            else if (GetAsyncKeyState(VK_DOWN)&&(logcursor[1]<maxx))
            {
                getch();
                logcursor[1]++;
                if (logcursor[1]>=logcursor[0]+25)
                {   logcursor[0]++; newscreen=true;}
            }
            else if (GetAsyncKeyState(VK_RIGHT)&&(acrecord<accounts-1))
            {
                getch();
                acrecord++;
                system("cls");
                goto mlog;
            }
            else if (GetAsyncKeyState(VK_LEFT)&&(acrecord>0))
            {
                getch();
                acrecord--;
                system("cls");
                goto mlog;
            }
        }
    case 9:dlog:///DAILY LOG
        if (logcount()<=0)
            goto log;
        ///display
        displayaccname(acrecord);
        writelogswiththesameaccintotem(accclass.name);
        rewrite_tem_with_transactions(accclass.name, logs);
        ///assigning max and minimum days
        maxx=0; minn=2147483647;//maximum int value
        for (int i=0; i<logs; i++)
        {
            filein.open(temfilename, ios::binary);
            filein.seekg(i*sizeof(logclass), ios::beg);
            filein.read((char*)&logclass, sizeof(logclass));
            filein.close();
            if (minn>daycode(logclass)) minn=daycode(logclass);
            if (maxx<daycode(logclass)) maxx=daycode(logclass);
        }
        if (!jump)
        {
            logcursor[1]=maxx;
            logcursor[0]=(maxx-minn>30)?(logcursor[1]-29):minn;
        }
        else
        {
            jump=false;
            if (logcursor[1]>maxx)
                logcursor[1]=maxx;
        }
        ///display
        gotoxy(0, 4);
        for (int i=0; i<120; i++)
            cout<<(char)196;
        for (int i=5; i<35; i++)
        {
            gotoxy(19, i); cout<<(char)179;
            gotoxy(53, i); cout<<(char)179;
            gotoxy(86, i); cout<<(char)179;
        }
        gotoxy(35, 3); cout<<"NET"; gotoxy(70, 3); cout<<"+"; gotoxy(103, 3); cout<<"-";
        for (bool newscreen=true; 1;)//entering menu
        {
            if (newscreen)
            {
                newscreen=false;
                for (int i=logcursor[0]; ((i<logcursor[0]+30)&&(i<=maxx)); i++)//erasing previsous data
                {
                    gotoxy(1, 5+i-logcursor[0]); cout<<"                 ";
                    gotoxy(21, 5+i-logcursor[0]); cout<<"                               ";
                    gotoxy(54, 5+i-logcursor[0]); cout<<"                               ";
                    gotoxy(88, 5+i-logcursor[0]); cout<<"                               ";
                }
                for (int i=logcursor[0]; ((i<logcursor[0]+30)&&(i<=maxx)); i++)
                {
                    if ((i==logcursor[0])||(i-1)%365==0)//(i%1461==1)||(i%1461==366)||(i%1461==731)||(i%1461==1096))
                    {
                        gotoxy(1, 5+i-logcursor[0]);
                        cout<<(i*4)/1461+1;
                    }
                    gotoxy(6, 5+i-logcursor[0]);
                    if (i==logcursor[0])
                    {
                        int randint;
                        randint=((i+1460)%1461)+1;
                        randint=randint+364;
                        if (randint==1461) goto jumpdec;
                        else if ((randint%365+1)<=31)
                            cout<<"JAN";
                        else if (((randint%365+1)<=59)||(randint-364==1155))
                            cout<<"FEB";
                        else if (((randint%365+1)<=90)||(randint-364==1186))
                            cout<<"MAR";
                        else if (((randint%365+1)<=120)||(randint-364==1216))
                            cout<<"APR";
                        else if (((randint%365+1)<=151)||(randint-364==1247))
                            cout<<"MAY";
                        else if (((randint%365+1)<=181)||(randint-364==1277))
                            cout<<"JUN";
                        else if (((randint%365+1)<=212)||(randint-364==1308))
                            cout<<"JUL";
                        else if (((randint%365+1)<=243)||(randint-364==1339))
                            cout<<"AUG";
                        else if (((randint%365+1)<=273)||(randint-364==1369))
                            cout<<"SEP";
                        else if (((randint%365+1)<=304)||(randint-364==1400))
                            cout<<"OCT";
                        else if (((randint%365+1)<=334)||(randint-364==1430))
                            cout<<"NOV";
                        else if ((randint%365+1)<=365)
                        {jumpdec:cout<<"DEC";}
                    }
                    else switch(i%1461)
                    {
                    case 1:case 366:case 731:case 1096: cout<<"JAN"; break;
                    case 32:case 397:case 762:case 1127: cout<<"FEB"; break;
                    case 60:case 425:case 790:case 1156: cout<<"MAR"; break;
                    case 91:case 456:case 821:case 1187: cout<<"APR"; break;
                    case 121:case 486:case 851:case 1217: cout<<"MAY"; break;
                    case 152:case 517:case 882:case 1248: cout<<"JUN"; break;
                    case 182:case 547:case 912:case 1278: cout<<"JUL"; break;
                    case 213:case 578:case 943:case 1309: cout<<"AUG"; break;
                    case 244:case 609:case 974:case 1340: cout<<"SEP"; break;
                    case 274:case 639:case 1004:case 1370: cout<<"OCT"; break;
                    case 305:case 670:case 1035:case 1401: cout<<"NOV"; break;
                    case 335:case 700:case 1065:case 1431: cout<<"DEC"; break;
                    }
                    gotoxy(11, 5+i-logcursor[0]);
                    for (int j=0; j<logs; j++)
                    {
                        filein.open(temfilename, ios::binary);
                        filein.seekg(j*sizeof(logclass), ios::beg);
                        filein.read((char*)&logclass, sizeof(logclass));
                        filein.close();
                        if (i==daycode(logclass))
                        {
                            cout<<logclass.TIME.TIME[0]<<logclass.TIME.TIME[1]<<logclass.TIME.TIME[2]<<" ";
                            if (logclass.TIME.date<10)
                                cout<<" ";
                            cout<<logclass.TIME.date;
                            break;
                        }
                    }
                }//different loop to make display less quirky

                for (int i=logcursor[0]; ((i<logcursor[0]+30)&&(i<=maxx)); i++)
                {
                    sum1=sum2=0;
                    for (int j=0; j<logs; j++)//loop through logs to find + and -
                    {
                        filein.open(temfilename, ios::binary);
                        filein.seekg(j*sizeof(logclass), ios::beg);
                        filein.read((char*)&logclass, sizeof(logclass));
                        filein.close();
                        if (i==daycode(logclass))
                            if (logclass.newbalance<0)
                                sum2-=logclass.newbalance;
                            else sum1+=logclass.newbalance;
                        logclass.refresh();
                    }
                    //display + and -
                    gotoxy(20, 5+i-logcursor[0]); cout<<setw(30)<<abs(sum1-sum2); if (sum1-sum2<0) cout<<'-'; else cout<<'+';
                    gotoxy(54, 5+i-logcursor[0]); if (sum1>0) cout<<setw(30)<<sum1;
                    gotoxy(88, 5+i-logcursor[0]); if (sum2>0) cout<<setw(30)<<sum2;
                }
            }//gotoxy(0, 34); cout<<"logcursor[0]="<<logcursor[0]<<"logcursor[1]="<<logcursor[1]<<" max="<<maxx;//gotoxy(0, 0); cout<<"cursor[0]-"<<logcursor[0]<<" cursor[1]-"<<logcursor[1];
            gotoxy(18, 5+logcursor[1]-logcursor[0]); cout<<"<";
            gotoxy(52, 5+logcursor[1]-logcursor[0]); cout<<"<";
            gotoxy(85, 5+logcursor[1]-logcursor[0]); cout<<"<";
            gotoxy(119, 5+logcursor[1]-logcursor[0]); cout<<"<";
            gotoxy(119, 34);
            if (getch()=='\r')
            {
                remove(temfilename);
                jump=true;
                previouscreen=8;
                system("cls");
                goto log;
            }
            gotoxy(18, 5+logcursor[1]-logcursor[0]); cout<<" ";
            gotoxy(52, 5+logcursor[1]-logcursor[0]); cout<<" ";
            gotoxy(85, 5+logcursor[1]-logcursor[0]); cout<<" ";
            gotoxy(119, 5+logcursor[1]-logcursor[0]); cout<<" ";
            if (GetAsyncKeyState(VK_ESCAPE))
            {
                remove(temfilename);
                goto mainmenu;
            }
            else if (GetAsyncKeyState(VK_UP)&&(logcursor[1]>minn))
            {
                getch();
                logcursor[1]--;
                if (logcursor[1]<logcursor[0])
                {   logcursor[0]--; newscreen=true;}
            }
            else if (GetAsyncKeyState(VK_DOWN)&&(logcursor[1]<maxx))
            {
                getch();
                logcursor[1]++;
                if (logcursor[1]>=logcursor[0]+30)
                {   logcursor[0]++; newscreen=true;}
            }
            else if (GetAsyncKeyState(VK_RIGHT)&&(acrecord<accounts-1))
            {
                getch();
                acrecord++;
                system("cls");
                goto dlog;
            }
            else if (GetAsyncKeyState(VK_LEFT)&&(acrecord>0))
            {
                getch();
                acrecord--;
                system("cls");
                goto dlog;
            }
        }
    case 10:log:///ALL LOGS
        ///display
        for (int i=0; i<120; i++)
        {
            gotoxy(i, 3); cout<<(char)196;
            gotoxy(i, 33); cout<<(char)196;
        }
        for (int i=4; i<33; i++)
        {
            gotoxy(44, i); cout<<(char)179;
            gotoxy(76, i); cout<<(char)179;
        }
        gotoxy(58, 1);
        cout<<"LOGS";
        if (justjump) goto stepskip1;
        filein.open(accfilename, ios::binary);
        filein.seekg(acrecord*sizeof(accclass), ios::beg);
        filein.read((char*)&accclass, sizeof(accclass));
        filein.close();
        logs=logcount();
        stepskip1:gotoxy(0, 34); cout<<"Log count - "<<logs;
        if (justjump) goto stepskip2;
        writelogswiththesameaccintotem(accclass.name);
        _sleep(200); logs=logcountspecific(accclass.name);
        stepskip2:gotoxy(0, 34); cout<<"Log count -                               \b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b"<<logs;
        if (justjump) goto stepskip3;
        if (!jump)
        {
            logcursor[1]=logs;
            logcursor[0]=(logcursor[1]>25)?(logcursor[1]-25):0;//depends on log screen components.
        }
        else
        {
            jump=false;//decodes daycode into logclass components
            logclass.TIME.year=((logcursor[1]/1461)*4)+(logcursor[1]%1461)/365+1;
            logcursor[1]%=1461;
            logcursor[1]%=365;
            logclass.TIME.month=1;
            for (logclass.TIME.date=1; logclass.TIME.date<=logcursor[1]; logclass.TIME.date++)
            {
                if (logclass.TIME.date>daysinmonth(logclass.TIME.month, logclass.TIME.year))
                {
                    logcursor[1]-=logclass.TIME.date-1;
                    logclass.TIME.date=0;
                    logclass.TIME.month++;
                }
            }
            logclass.TIME.date--;

            for (int i=0; i<logs; i++)//search for similar logclass
            {
                filein.open(temfilename, ios::binary);
                filein.seekg(i*sizeof(logclass2), ios::beg);
                filein.read((char*)&logclass2, sizeof(logclass2));
                filein.close();
                if (logclass.TIME.year==logclass2.TIME.year)
                    if (logclass.TIME.month==logclass2.TIME.month)
                        if (logclass.TIME.date==logclass2.TIME.date)
                        {
                            logcursor[1]=i;
                            logcursor[0]=(logcursor[1]>25)?(logcursor[1]-25):0;
                            break;
                        }
            }
        }
        stepskip3:justjump=false;gotoxy(21, 2);cout<<(char)192<<(char)191;
        gotoxy(98-strlen(accclass.name)/2, 2); if(acrecord!=0)cout<<"\b\b< "; cout<<accclass.name; if (acrecord<accounts-1) cout<<" >";
        for (bool newscreen=true; 1; )
        {
            if (newscreen)
            {
                newscreen=false;
                for (int i=logcursor[0]; (i<logcursor[0]+25)&&(i<=logs); i++)
                {
                    gotoxy(77, i-logcursor[0]+6);
                    cout<<"                              ";
                    gotoxy(11, i-logcursor[0]+6);
                    if (i>0)
                        cout<<"                               ";
                }
                for (int i=logcursor[0]; (i<logcursor[0]+25)&&(i<logs); i++)
                {
                    file.open(temfilename, ios::binary|ios::in);
                    file.seekg((i*sizeof(logclass)), ios::beg);
                    file.read((char*)&logclass, sizeof(logclass));
                    file.seekg(((i-1)*sizeof(logclass2)), ios::beg);
                    file.read((char*)&logclass2, sizeof(logclass2));
                    file.close();
                    gotoxy(77, i-logcursor[0]+6);
                    cout<<setw(30)<<logclass.newbalance;
                    gotoxy(11, i-logcursor[0]+6);
                    if (i>0)
                    {
                        cout<<setw(30)<<abs(logclass.newbalance-logclass2.newbalance);
                        if (logclass.newbalance-logclass2.newbalance<0)
                            cout<<"-";
                        else cout<<"+";
                    }
                }
            }
            if (logcursor[1]==logs)
            {
                gotoxy(60-strlen("add a new log")/2, logcursor[1]+6-logcursor[0]);
                cout<<"ADD A NEW LOG";
            }
            else
            {
                filein.open(temfilename, ios::binary);
                filein.seekg(logcursor[1]*sizeof(logclass), ios::beg);
                filein.read((char*)&logclass, sizeof(logclass));
                filein.close();
                gotoxy(48, 6+logcursor[1]-logcursor[0]);
                cout<<logclass.TIME.TIME;
            }
            gotoxy(43, 6+logcursor[1]-logcursor[0]); cout<<"<";
            gotoxy(108, 6+logcursor[1]-logcursor[0]); cout<<"<";
            gotoxy(119, 34);
            if (getch()=='\r')
                if (logcursor[1]==logs)
                {
                    recordnewlog(acrecord);
                    previouscreen=-1;
                    goto log;
                }
                else
                {
                    createbox(20, 10, 100, 20, true);
                    gotoxy(53, 12);
                    cout<<"LOG DETAILS";
                    gotoxy(60-10, 14); cout<<"Balance : "<<logclass.newbalance;
                    gotoxy(60-10, 15); cout<<"Account : "<<logclass.account;
                    gotoxy(60-7, 16); cout<<"Time : "<<logclass.TIME.TIME;
                    gotoxy(60-10, 17); cout<<"Details : "<<logclass.details;
                    getch();
                    newscreen=justjump=true;
                    system("cls");
                    goto log;
                }
            gotoxy(43, 6+logcursor[1]-logcursor[0]); cout<<" ";
            gotoxy(108, 6+logcursor[1]-logcursor[0]); cout<<" ";
            gotoxy(48, 6+logcursor[1]-logcursor[0]);
            if (logcursor[1]==logs)
            {
                gotoxy(60-strlen("add a new log")/2, logcursor[1]+6-logcursor[0]);
                cout<<"             ";
            }
            else cout<<"                         ";
            if (GetAsyncKeyState(VK_ESCAPE))
                goto mainmenu;
            else if (GetAsyncKeyState(VK_DOWN)&&(logcursor[1]<logs))
            {
                getch();
                logcursor[1]++;
                if (logcursor[1]>=logcursor[0]+25)
                {   logcursor[0]++; newscreen=true; }
            }
            else if (GetAsyncKeyState(VK_UP)&&(logcursor[1]>0))
            {
                getch();
                logcursor[1]--;
                if (logcursor[1]<logcursor[0])
                {   logcursor[0]--; newscreen=true;}
            }
            else if (GetAsyncKeyState(VK_RIGHT)&&(acrecord<accounts-1))
            {
                getch();
                acrecord++;
                system("cls");
                goto log;
            }
            else if (GetAsyncKeyState(VK_LEFT)&&(acrecord>0))
            {
                getch();
                acrecord--;
                system("cls");
                goto log;
            }
        }
    }
    goto mainmenu;
}//*/
/*
int main()
{
    for(int i=0; i<5; i++)
    {
        filein.open("logfiles_JAYcreations.dat", ios::binary);
        filein.seekg(i*sizeof(logclass), ios::beg);
        filein.read((char*)&logclass, sizeof(logclass));
        filein.close();
        if (i==0) file.open("bleh.dat", ios::binary|ios::out);
        else file.open("bleh.dat", ios::binary|ios::out|ios::app);
        file.write((char*)&logclass, sizeof(logclass));
        file.close();
    }
    remove("logfiles_JAYcreations.dat");
    rename("bleh.dat", "logfiles_JAYcreations.dat");
    return 0;
}//*/
//*/
/*
int main()
{
    char nostring[4], noostring[5];
    int x=10;
    for (int i=0; i<4; i++)
    {
        nostring[i]=NULL;
        noostring[i]=NULL;
    }
    noostring[4]=NULL;
    strcpy(logfilename, "logfiles_JAYcreations.dat");
    strcpy(logclass.account, "jitin's wallet");
    logclass.newbalance=0;
    int i=2017;
    for (int k=1; k<=12; k++)
        for (int j=1; j<=daysinmonth(k, i); j++)
        {
            logclass.timeremod();
            logclass.TIME.year=i;
            logclass.TIME.month=k;
            logclass.TIME.date=j;
            int f=returnday(logclass.TIME);
            cout<<"year:"<<logclass.TIME.year<<" : month:"<<logclass.TIME.month<<" : date:"<<logclass.TIME.date<<" : f:"<<f<<"\n";
            strcpy(logclass.TIME.TIME, "\0");
            switch(f)
            {
            case 0:strcpy(logclass.TIME.TIME, "Sun "); break;
            case 1:strcpy(logclass.TIME.TIME, "Mon "); break;
            case 2:strcpy(logclass.TIME.TIME, "Tue "); break;
            case 3:strcpy(logclass.TIME.TIME, "Wed "); break;
            case 4:strcpy(logclass.TIME.TIME, "Thu "); break;
            case 5:strcpy(logclass.TIME.TIME, "Fri "); break;
            case 6:strcpy(logclass.TIME.TIME, "Sat "); break;
            }
            switch (logclass.TIME.month)
            {
            case 1:strcat(logclass.TIME.TIME, "Jan "); break;
            case 2:strcat(logclass.TIME.TIME, "Feb "); break;
            case 3:strcat(logclass.TIME.TIME, "Mar "); break;
            case 4:strcat(logclass.TIME.TIME, "Apr "); break;
            case 5:strcat(logclass.TIME.TIME, "May "); break;
            case 6:strcat(logclass.TIME.TIME, "Jun "); break;
            case 7:strcat(logclass.TIME.TIME, "Jul "); break;
            case 8:strcat(logclass.TIME.TIME, "Aug "); break;
            case 9:strcat(logclass.TIME.TIME, "Sep "); break;
            case 10:strcat(logclass.TIME.TIME, "Oct ");break;
            case 11:strcat(logclass.TIME.TIME, "Nov ");break;
            case 12:strcat(logclass.TIME.TIME, "Dec ");break;
            }
            //cout<<logclass.thetime; getch();
            if (logclass.TIME.date<10)
            {    nostring[0]='0'; nostring[1]=(char)(48+logclass.TIME.date);}
            else
            {   nostring[0]=(char)(48+(logclass.TIME.date/10)); nostring[1]=(char)(48+(logclass.TIME.date%10));}
            nostring[2]=' ';
            strcat(logclass.TIME.TIME, nostring);
            //cout<<logclass.thetime; getch();
            if (logclass.TIME.hour<10)
            {    nostring[0]='0'; nostring[1]=(char)(48+logclass.TIME.hour);}
            else
            {   nostring[0]=(char)(48+(logclass.TIME.hour/10)); nostring[1]=(char)(48+(logclass.TIME.hour%10));}
            nostring[2]=':';
            strcat(logclass.TIME.TIME, nostring);
            //cout<<logclass.thetime; getch();
            if (logclass.TIME.minute<10)
            {    nostring[0]='0'; nostring[1]=(char)(48+logclass.TIME.minute);}
            else
            {   nostring[0]=(char)(48+(logclass.TIME.minute/10)); nostring[1]=(char)(48+(logclass.TIME.minute%10));}
            nostring[2]=':';
            strcat(logclass.TIME.TIME, nostring);
            //cout<<logclass.thetime; getch();
            if (logclass.TIME.second<10)
            {    nostring[0]='0'; nostring[1]=(char)(48+logclass.TIME.second);}
            else
            {   nostring[0]=(char)(48+(logclass.TIME.second/10)); nostring[1]=(char)(48+(logclass.TIME.second%10));}
            nostring[2]=' ';
            strcat(logclass.TIME.TIME, nostring);

            noostring[0]=(char)(48+(logclass.TIME.year/1000));
            noostring[1]=(char)(48+((logclass.TIME.year%1000)/100));
            noostring[2]=(char)(48+((logclass.TIME.year%100)/10));
            noostring[3]=(char)(48+(logclass.TIME.year%10));
            strcat(logclass.TIME.TIME, noostring);
            logclass.newbalance+=x;
            file.open(logfilename, ios::binary|ios::app|ios::out);
            file.write((char*)&logclass, sizeof(logclass));
            file.close();
            logclass.newbalance-=x;
            file.open(logfilename, ios::binary|ios::app|ios::out);
            file.write((char*)&logclass, sizeof(logclass));
            file.close();
            logclass.newbalance+=x;
            file.open(logfilename, ios::binary|ios::app|ios::out);
            file.write((char*)&logclass, sizeof(logclass));
            file.close();
            x++;
        }
    }
//*/
/*
int main()
{
    int logcursor[2];
    bool analyze=false;
    logcursor[1]=737621;//2020 06 30
    logclass.TIME.year=((logcursor[1]/1461)*4)+(logcursor[1]%1461)/365+1;
    if (analyze) {cout<<"Year : "<<logclass.TIME.year;}
    logcursor[1]%=1461;
    if (analyze) {cout<<"\nLC : "<<logcursor[1];}
    logcursor[1]%=365;
    if (analyze) {cout<<"\nLC : "<<logcursor[1];}
    logclass.TIME.month=1;
    if (analyze) {cout<<"\nMonth : "<<logclass.TIME.month;}
    if (analyze) {cout<<"\n\nEntering loop\n"; getch();}
    for (logclass.TIME.date=1; logclass.TIME.date<=logcursor[1]; logclass.TIME.date++)
    {
        if (analyze) {cout<<"\nLC : "<<logcursor[1]<<"\ti : "<<logclass.TIME.date<<"\tMonth : "<<logclass.TIME.month;getch();}
        if (logclass.TIME.date>daysinmonth(logclass.TIME.month, logclass.TIME.year))
        {
            if (analyze) {cout<<"\tCONDITION TRUE"; getch();}
            logcursor[1]-=logclass.TIME.date-1;
            logclass.TIME.date=0;
            logclass.TIME.month++;
        }
    }
    logclass.TIME.date--;
    cout<<"year : "<<logclass.TIME.year<<" month : "<<logclass.TIME.month<<" date : "<<logclass.TIME.date; getch();
}//*/
/*
int main()
{
    int x=logcount(), a=0;
    for (int i=0; 1; i++)
    {
        filein.open("logfiles_JAYcreations.dat", ios::binary);
        filein.seekg(i*sizeof(logclass), ios::beg);
        filein.read((char*)&logclass, sizeof(logclass));
        filein.close();
        if (strcmpi(logclass.account, "Noel")==0)
            gotoxy(0, a++);
        else gotoxy(10, a++);
        cout<<logclass.newbalance;
        getch();
        if (filein.eof())break;
    }
    return 0;
}//*/
