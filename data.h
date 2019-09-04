#ifndef DATA_H
#define DATA_H

#include<QString>
#include<QStringList>

namespace  ar{

class Data
{
private:
    int dia;
    int mes;
    int ano;
public:
    Data():dia(0),mes(0),ano(0){}
    Data(int dia,int mes,int ano);

    int getDia()const{return dia;}
    void setDia(int dia){this->dia=dia;}

    int getMes()const{return mes;}
    void setMes(int mes){this->mes=mes;}

    int getAno()const{return ano;}
    void setAno(int ano){this->ano=ano;}

    int operator-(Data objeto)const;

    QString getDataQString()const;

    QString desmaterializar()const;
    void materializar(QString str);

    bool operator<(Data objeto)const;
};

}


#endif // DATA_H
