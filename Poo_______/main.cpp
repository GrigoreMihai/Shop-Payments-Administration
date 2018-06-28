#include <iostream>
#include <cstring>
#include <windows.h>
#include <string>


using namespace std;
class client
{
    char *nume;
    long long int cnp;
public:

    client(char *p="",string cn="")
    {
        try
        {

                   nume=new char[strlen(p)+1];
                  strcpy(nume,p);

        }
        catch (bad_alloc xa)
        {
            cout<<"Eroare la alocare\n";
            exit(EXIT_FAILURE);
        }
            cnp=0;
        long long int j=0;

        try
        {
            if (cn=="")
                throw 10;
            if (cn.size()!=13)
               {

                    throw 7;

               }
            for (int i=0;i<cn.size();i++)
            {
                   int x=cn[i]-'0';
                   if (x<10 && x>=0)
                     j=j*10+x;
                     else
                        throw 7;
            }
            cnp=j;
        }
        catch (int i)
        {
            if (i==7)
            cout<<"cnp invalid\n";

        }

    }
    client (const client & c)
    {
        try
        {
        nume=new char[strlen(c.nume)+1];
        strcpy(nume,c.nume);

        }
                catch (bad_alloc xa)
        {
            cout<<"Eroare la alocare\n";
            exit(EXIT_FAILURE);
        }
        cnp=c.cnp;
    }
    friend istream &operator >>(istream &in,client &c)
    {
        in.get();
        ll:
        string cn;

        cout<<"Introduceti numele \n";

        getline(in,cn);

        if (cn[0]<65 || cn[0]>93 || (cn.find_first_of("0123456789") != string::npos) )
        {
            cout<<"Ceea ce ati introdus nu este un nume(un nume incepe cu litera mare)\n";
            goto ll;
        }
        try
        {
        c.nume=new char[cn.size()+1];
        }
        catch (bad_alloc xa)
        {
            cout<<"nu avem suficient spatiu\n";
            exit(EXIT_FAILURE);
        }
        strcpy(c.nume,cn.c_str());
        tt:
        cout<<"\n Introduceti cnp ul\n";

        in>>cn;
       long long int j=0;

        try
        {
            if (cn=="")
                throw 10;
            if (cn.size()!=13)
               {

                    throw 7;

               }
            for (int i=0;i<cn.size();i++)
            {
                   int x=cn[i]-'0';
                   if (x<10 && x>=0)
                     j=j*10+x;
                     else
                        throw 7;
            }
            c.cnp=j;
        }
        catch (int i)
        {
            if (i==7)
            cout<<"cnp invalid\n";
            goto tt;

        }

        return in;
    }
    friend ostream &operator <<(ostream &out,const client &c)
    {
        out<<"Nume :"<<c.nume<<"\ncnp: "<<c.cnp<<endl;
    }
     client operator =(const client c)
     {
         try
         {
         nume =new char[strlen(c.nume)+1];


         strcpy(nume,c.nume);
         }
         catch (bad_alloc xa)
        {
            cout<<"Eroare la alocare\n";
            exit(EXIT_FAILURE);
        }

         cnp=c.cnp;
         return (*this);
     }
     virtual void afisare ()
     {
         cout<<"numele clientului : "<<nume<<"\ncnp : "<<cnp<<endl;
     }


    ~client()
    {

        delete []nume;
    }
    char* get_name()
    {
        return nume;
    }
};
int size (int a)
{
    if (a)
        return 1+size(a/10);
    else
        return 0;
}
class cash
{
    double amount;
public:
    cash(double x=0)
    {
        amount=x;
    }
    cash(const cash &c)
    {
        amount=c.amount;
    }
    friend istream &operator >>(istream &in,cash &c)
    {
        cout<<"Introduceti suma cu care platiti \n";
        in>>c.amount;
    }
    friend ostream &operator <<(ostream &out,const cash & c)
    {
        out<<c.amount;
    }
    cash &operator =(const cash &c)
    {
        amount = c.amount;
    }



    ~cash()
    {
    amount=0;
    };

    double get_amount()
    {
        return amount;
    }
};

class card :virtual public  client
{
    int nr_card;
    double sum;
public:
    card(char *nume="",string cnp="",int n=0,double s=0):client(nume,cnp)
    {
        nr_card=n;
        sum=s;
    }
    card (const card &c):client(c)
    {
        nr_card=c.nr_card;
        sum=c.sum;
    }
    void afisare()
    {
        ((client &)(*this)).afisare();
        cout<<"numar card :"<<nr_card<<"suma de bani :"<<sum<<endl;
    }
    friend istream &operator >>(istream &in,card &c)
    {
        client &cl=*dynamic_cast<client*>(&c);
        in>>cl;
         tt:
             cout<<"Introduceti numarul cardului(7 cifre)\n";
        try
        {

        in>>c.nr_card;
        if (size(c.nr_card)!=7)
            throw 7;
        }
        catch(int i)
        {
            if (i==7)
                cout<<"Numar card invalid invalid  \n";
                goto tt;
        }
        cout<<"Indroduceti suma pe care o adaugati pe card\n";

        in>>c.sum;
        return in ;
    }
    friend ostream &operator <<(ostream &out ,const card &c)
    {
       const  client &cl=*dynamic_cast<const client*>(&c);
        out<<cl;
        out<<"\nnr_card :"<<c.nr_card<<"\nsuma de pe card : "<<c.sum<<"\n ";
        return out;
    }
    card &operator = (const card &c)
    {
        const client &cl=c;
        client &clthis=(*this);
        clthis=c;
        nr_card=c.nr_card;
        sum=c.sum;
        return (*this);
    }

    ~card()
    {

        sum=0;
        nr_card=0;
    }
    double get_sum()
    {
        return sum;
    }
    int get_nr()
    {
        return nr_card;
    }
};
class cec :virtual public client
{
    double suma;
    int serie;
public:
    cec(char *nume="",string cnp="",double s=0,int se=0):client(nume,cnp)
    {
        suma=s;
        serie =se;
    }
    cec (const cec &c):client(c)
    {
        serie=c.serie;
        suma=c.suma;
    }
    void afisare()
    {

        ((cec &)(*this)).afisare();
        cout<<"serie :"<<serie<<"suma de bani :"<<suma<<endl;
    }
    friend istream &operator >>(istream &in,cec &c)
    {
          client &cl=*dynamic_cast<client*>(&c);
        in>>cl;
        cout<<"Introduceti seria(6 cifre) \n";
         tt:
        try
        {

        in>>c.serie;
        if (size(c.serie)!=6)
            throw 7;
        }
        catch(int i)
        {
            if (i==7)
                cout<<"Serie invalida,  \n";
                goto tt;
        }
        cout<<"Indroduceti valoarea cecului\n";
        in>>c.suma;
        return in ;
    }
    friend ostream &operator <<(ostream &out ,const cec &c)
    {
       const  client &cl=*dynamic_cast<const client*>(&c);
        out<<cl;
        out<<"\nsuma de pe cec : "<<c.suma<<"\n seria cecului :"<<c.serie<<" ";
        return out;
    }
    cec &operator = (const cec c)
    {
        const client &cl=c;
        client &clthis=(*this);
        clthis=c;
        serie=c.serie;
        suma=c.suma;
        return (*this);
    }
    ~cec()
    {

        suma=0;
        serie=0;
    }
    double get_sum()
    {
        return suma;
    }
};


class data
{
    int a,b,c;
public:
    data(int x=0,int y=0,int z=0)
    {
        a=x;
        b=y;
        c=z;

    }
    data(const data &d)
    {
        a=d.a;
        b=d.b;
        c=d.c;
    }
    friend istream &operator >>(istream &in,data &c)
    {
        tt:
        cout<<"Introduceti data in care s-a efectat plata(dd//mm//yyyy)(anul intre 1800-3000)\n";
        try
        {
        in>>c.a;

        in>>c.b;
        in>>c.c;
        if (size(c.a)>2 || size(c.b)>2 || size(c.c)>4 || size(c.a)==0 || size(c.b)==0 || size(c.c)==0 || c.a<=0 || c.b<=0 || c.a>31 || c.b>12 || c.c<1800 ||c.c>3000)
            throw 7;
        }
        catch (int i)
        {
            if (i==7)
                cout<<"data invalida \n";
                c.a=c.b=c.c=0;
                goto tt;
        }

        return in ;
    }
    friend ostream &operator <<(ostream &out ,const data &c)
    {
        out<<c.a<<" "<<c.b<<" "<<c.c<<" "<<endl;

        return out;
    }
    data &operator = (const data d)
    {
        a=d.a;
        b=d.b;
        c=d.c;
        return (*this);
    }
    ~data()
    {
        a=b=c=0;
    }
};

class Plata: public cash , public card ,public cec
{


    data n;
    double suma;
    int nr_card; //1 daca plateste cash 0 daca plateste cu cec else un numar de 7 cifre
public:


     Plata(char *nume,string cn,double amount,data d,double a):client(nume,cn),cash(amount)
     {
         n=d;
         suma=a;
         nr_card=1;
     }
     void afisare()
    {

         if (nr_card==1)
         {


             cout<<"Suma platita :"<<((cash &)(*this)).get_amount();

         }
         else
             if (nr_card==0)
              {
                   cec &c=*dynamic_cast<cec*>(this);
                   cout<<c<<endl;
                }
                else
                {
                        card &c=*dynamic_cast<card*>(this);
                   cout<<c<<endl;
                }
         cout<<"\ndata: "<<n<<"suma de plata: "<<suma<<endl;


    }
     Plata(char *nume,string cn,int nr_car,double su ,data d,double a):card(nume,cn,nr_car,su)
     {
         n=d;
         suma=a;
         nr_card= nr_car;
     }
      Plata(char *nume,string cn,double su,int ser ,data d,double a):cec(nume,cn,ser,su)
     {
         n=d;
         suma=a;
         nr_card= 0;
     }
     Plata(){};


    Plata(const Plata&p):card(p),cec(p),cash(p)
      {
          nr_card=p.nr_card;
          suma=p.suma;
          n=p.n;



      }
     friend istream &operator >>(istream &in,Plata &p)
     {

         in>>p.n;


          cout<<"Indroduceti suma de platit \n";
             in>>p.suma;
             tt:

         cout<<"\nPlatiti cu :\n";
         cout<<"1.Cash\n";
         cout<<"2.Card\n";
         cout<<"3.Cec:\n";
         int o;
         in>>o;
         if (o==1)
         {

             p.nr_card=1;
             cash &c=p;

             try
             {

             in>>c;
             if (c.get_amount()<p.suma)
                throw 7;

             cout<<"rest :\n";
             cout<<c.get_amount()-p.suma<<"\n";
             }
             catch(int i)
             {
                 if (i==7)
                    cout<<"Suma insuficienta pentru a plati \n";
                    goto tt;
             }


         }
         if (o==2)
         {
              card &c=p;

             try
             {

             in>>c;
             p.nr_card=c.get_nr();
             if (c.get_sum()<p.suma)
                throw 7;

                cout<<"Plata s-a efectuat cu succes\n";


             }
             catch(int i)
             {
                 if (i==7)
                    cout<<"Suma insuficienta pentru a plati \n";
                    goto tt;
             }
         }
         if (o==3)
         {
                           cec &c=p;

             try
             {

             in>>c;
             p.nr_card=0;
             if (c.get_sum()<p.suma)
                throw 7;

                cout<<"Plata s-a efectuat cu succes\n";


             }
             catch(int i)
             {
                 if (i==7)
                    cout<<"Suma insuficienta pentru a plati \n";
                    goto tt;
             }
         }

     }

    friend ostream &operator <<(ostream &out,Plata &p)
    {
        out<<"data :"<<p.n<<"\nsuma de plata : "<<p.suma<<endl;
        if (p.nr_card==1)
         {


             cash &c=p;
             out<<"suma platita :";
             out<<c<<endl;
             out<<"rest :"<<c.get_amount()-p.suma<<endl;

         }
         else
             if (p.nr_card==0)
              {
              cec &c=p;
              out<<c<<endl;
                }
                else
                {
                    card &c=p;
                    out<<c<<endl;
                }



     }

   ~Plata()
    {
        n.~data();
        suma=0;
        nr_card=0;
    }
    Plata operator = (const Plata &p)
    {


 if (p.nr_card==1)
         {


              const cash &cl=p;
        cash &clthis=(*this);
        clthis=p;

          this->nr_card=1;

         }
         else
             if (p.nr_card==0)
             {
              const cec &cl=p;
        cec &clthis=(*this);
        clthis=p;
        this->nr_card=0;
                }
                else
                {
                    const card &cl=p;
                   card &clthis=(*this);
                   clthis=p;
                   this->nr_card=p.nr_card;
                }
      this->n=p.n;
      this->suma=p.suma;
    }


};
template <class T> class Gestiune
{
    T * *v;
    int nrp; //dimensiunea pentru fiecare vector de plati
    static int nr_plati;
public:
    Gestiune(T **p={},int n=0)
    {
        nrp=n;
        nr_plati+=nrp;
        try
        {
        v=new T*[n];
        for (int i=0;i<nrp;i++)
        {
            v[i]=new T;
            v[i]=p[i];
        }
        }
         catch (bad_alloc xa)
        {
            cout<<"nu avem suficient spatiu\n";
            exit(EXIT_FAILURE);
        }
    }
    friend istream &operator >> (istream &in, Gestiune<T> & g)
    {
        cout<<"Introduceti numarul de plati \n";
        in>>g.nrp;
        try
        {
            g.v=new T*[g.nrp];
             for (int i=0;i<g.nrp;i++)
              {
                 g.v[i]=new T;
                 in>>(*g.v[i]);
              }
        }
        catch (bad_alloc xa)
        {
            cout<<"nu avem spatiu pentru a memora gestiunea \n";
        }
    }
    friend ostream &operator <<(ostream &out, Gestiune <T> & g)
    {
         if(g.nrp==0)
            out<<"nu avem plati memorate\n";
            else
            {
        out<<"Platile sunt :\n";
        for (int i=0;i<g.nrp;i++)
              {
                  cout<<"plata "<<i+1<<": \n";

                 out<<(*g.v[i]);
                 out<<endl;
              }
            }
    }
    Gestiune <T> &operator +=( T &p)
    {
        try
        {
        Plata **pp=new T*[this->nrp]; //copiez vectorul vechi
        for (int i=0;i<this->nrp;i++)
              {
                 pp[i]=new T;

                 (*pp[i])=(*this->v[i]);

              }


        this->v=new T*[this->nrp+1];


        for (int i=0;i<this->nrp;i++)
              {

                 v[i]=new T;
                (*this->v[i])= (*pp[i]);

              }

        v[nrp]=new T;
        }
         catch (bad_alloc xa)
        {
            cout<<"nu avem suficient spatiu\n";
            exit(EXIT_FAILURE);
        }

        (*this->v[nrp])=p;
        this->nrp++;

    }

    ~Gestiune()
    {
           for (int i=0;i<nrp;i++)
                 delete v[i];



              delete []v;
    }





};
template <class T> int Gestiune<T>::nr_plati=0;
template <>class Gestiune <card>                          //specializare pt carduri ,mai jos este specializare pentru char*(folosita pentru clienti)
{
     card * *v;
    int nrp; //dimensiunea pentru fiecare vector carduri
    static int nrc;
public:
    Gestiune(card **p={},int n=0)
    {
        nrp=n;
        nrc+=nrp;
        try
        {
        v=new card*[n];
        for (int i=0;i<nrp;i++)
        {
            v[i]=new card;
            v[i]=p[i];
        }
        }
         catch (bad_alloc xa)
        {
            cout<<"nu avem suficient spatiu\n";
            exit(EXIT_FAILURE);
        }
    }
    friend istream &operator >> (istream &in, Gestiune<card> & g)
    {
        cout<<"Introduceti numarul carduri\n";
        in>>g.nrp;
        try
        {
            g.v=new card*[g.nrp];
             for (int i=0;i<g.nrp;i++)
              {
                 g.v[i]=new card;
                 in>>(*g.v[i]);
              }
        }
        catch (bad_alloc xa)
        {
            cout<<"nu avem spatiu pentru a memora gestiunea \n";
            exit(EXIT_FAILURE);
        }
    }
    friend ostream &operator <<(ostream &out, Gestiune <card> & g)
    {
         if(g.nrp==0)
            out<<"nu avem carduri memorate\n";
            else
            {
        out<<"cardurile sunt :\n";
        for (int i=0;i<g.nrp;i++)
              {
                  cout<<"cardul  "<<i+1<<": \n";

                 out<<(*g.v[i]);
                 out<<endl;
              }
            }
    }
    Gestiune <card> &operator +=( card &p)
    {
        try
        {
        card **pp=new card*[this->nrp]; //copiez vectorul vechi
        for (int i=0;i<this->nrp;i++)
              {
                 pp[i]=new card;

                 (*pp[i])=(*this->v[i]);

              }


        this->v=new card*[this->nrp+1];


        for (int i=0;i<this->nrp;i++)
              {

                 v[i]=new card;
                (*this->v[i])= (*pp[i]);

              }

        v[nrp]=new card;
        }
         catch (bad_alloc xa)
        {
            cout<<"nu avem suficient spatiu\n";
            exit(EXIT_FAILURE);
        }

        (*this->v[nrp])=p;
        this->nrp++;

    }

    ~Gestiune()
    {
           for (int i=0;i<nrp;i++)
                 delete v[i];



              delete []v;
    }





};
template <> int Gestiune<card>::nrc=0;
template <>class Gestiune <char*>                                     //specializare pentru char*
{
     client * *v;
    int nrp; //dimensiunea pentru fiecare vector clienti
    static int nrc;
public:
    Gestiune(client **p={},int n=0)
    {
        nrp=n;
        nrc+=nrp;
        try
        {
        v=new client*[n];
        for (int i=0;i<nrp;i++)
        {
            v[i]=new client;
            v[i]=p[i];
        }
        }
         catch (bad_alloc xa)
        {
            cout<<"nu avem suficient spatiu\n";
            exit(EXIT_FAILURE);
        }
    }
    friend istream &operator >> (istream &in, Gestiune<char*> & g)
    {
        cout<<"Introduceti numarul de clienti\n";
        in>>g.nrp;
        try
        {
            g.v=new client*[g.nrp];
             for (int i=0;i<g.nrp;i++)
              {
                 g.v[i]=new client;
                 in>>(*g.v[i]);
              }
        }
        catch (bad_alloc xa)
        {
            cout<<"nu avem spatiu pentru a memora gestiunea \n";
            exit(EXIT_FAILURE);
        }
    }
    friend ostream &operator <<(ostream &out, Gestiune <char*> & g)
    {
        if(g.nrp==0)
            out<<"nu avem clienti memorati\n";
        else
        {
        out<<"clientii sunt :\n";
        for (int i=0;i<g.nrp;i++)
              {
                  cout<<"clientul  "<<i+1<<": \n";

                 out<<(*g.v[i]);
                 out<<"\n";
              }
        }
    }
    Gestiune <char*> &operator +=( client &p)
    {
        try
        {
        client **pp=new client*[this->nrp]; //copiez vectorul vechi
        for (int i=0;i<this->nrp;i++)
              {
                 pp[i]=new client;

                 (*pp[i])=(*this->v[i]);

              }


        this->v=new client*[this->nrp+1];


        for (int i=0;i<this->nrp;i++)
              {

                 v[i]=new client;
                (*this->v[i])= (*pp[i]);

              }

        v[nrp]=new client;
        }
         catch (bad_alloc xa)
        {
            cout<<"nu avem suficient spatiu\n";
            exit(EXIT_FAILURE);
        }

        (*this->v[nrp])=p;
        this->nrp++;

    }

    ~Gestiune()
    {
           for (int i=0;i<nrp;i++)
                 delete v[i];



              delete []v;
    }





};
template <> int Gestiune<char*>::nrc=0;

int main()
{
      Gestiune<Plata> p;
      Gestiune<card> cc;
      Gestiune<char*> ci;
int      ok=1; char c;
      while (ok)
     {

    cout<<"Alegeti una din optunile de mai jos \n";
    cout<<"Tot ceea ce cititi este disponibil pe tot parcursul programului,se poate adauga si doar cate o instanta din fiecare obiect\n";
    cout<<"a.Cititi mai multe plati\n";
     cout<<"(pentru o plata se citesc si date despre client si (card sau cec)) \n";
    cout<<"b.Afisati toate platile citite\n";
     cout<<"c.Cititi mai multi clienti\n";
     cout<<"d.Afisati toti clientii cititi\n";
     cout<<"e.Cititi mai multe carduri(pentru un card se citesc si datele despre client)\n";
     cout<<"f.Afisati toate cardurile citite\n";
     cin>>c;
     switch (c)
     {
       case 'a':
       {
            system("cls");
            cout<<"Cate plati doriti sa cititi\n";
            int n;
            cin>>n;
            for (int i=0;i<n;i++)
            {
                Plata g;
                cin>>g;
                p+=g;
            }
       }
        break;
       case 'b':
       {
            system("cls");
            cout<<p;
       }
       break;
       case 'c':
        {
            system("cls");
            cout<<"Cati clienti doriti sa cititi\n";
            int n;
            cin>>n;
            for (int i=0;i<n;i++)
            {
                client g;
                cin>>g;
                ci+=g;
            }
        }break;
       case 'd':
        {
            system("cls");
            cout<<ci;
        }break;
       case 'e':
        {
            system("cls");
            cout<<"Cate carduri doriti sa cititi\n";
            int n;
            cin>>n;
            for (int i=0;i<n;i++)
            {
                card g;
                cin>>g;
                cc+=g;
            }
        }
        break;
       case 'f':
        {
            system("cls");
            cout<<cc;
            }
        break;

      default:cout<<"optiune invalida\n";
     }
     cout<<"\ndoriti sa mai alegeti alta optiune 0 sau 1 ";cin>>ok;
     loop:
     if(ok!=1)
     if(ok)
     {
           cout<<"Optiune invalida\n";
           cout<<"Introduceti 0 daca vreti sa ichideti 1 daca vreti sa continuati rularea programului apoi apasati 'Enter'";
           cin>>ok;
           goto loop;
     }

     system("cls");
     }
     cout<<"Executia programului s-a terminat\nO zi frumoasa in continuare";

}






































