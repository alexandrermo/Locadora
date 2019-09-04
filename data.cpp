#include "data.h"
namespace ar {

int Data::operator-(Data objeto) const
{
    if  (this->ano<objeto.ano) throw QString("Data de devolução anterior à data de locação.");
    else if(this->ano==objeto.ano)
    {
        if  (this->mes<objeto.mes) throw QString("Data de devolução anterior à data de locação.");
        else if (this->mes==objeto.mes)
        {
            if  (this->dia<objeto.dia) throw QString("Data de devolução anterior à data de locação.");
        }
    }

    int quantidadeDias=0;

    if  (this->mes==objeto.mes && this->ano==objeto.ano) return (this->dia-(objeto.dia-1));

    if  (objeto.mes==2) quantidadeDias=29-(objeto.dia-1);
    else if(objeto.mes<8)
    {
        if  ((objeto.mes)%2==0) quantidadeDias=30-(objeto.dia-1);
        else quantidadeDias=31-(objeto.dia-1);
    }else
    {
        if  ((objeto.mes)%2==0) quantidadeDias=31-(objeto.dia-1);
        else quantidadeDias=30-(objeto.dia-1);
    }

    int mesVar=(objeto.mes)+1;
    int anoVar=0;
    if  (mesVar<=12)anoVar=objeto.ano;
    else
    {
        anoVar=objeto.ano+1;
        mesVar=1;
    }

    while(mesVar!=this->mes || anoVar!=this->ano)
    {
        if  (mesVar==2) quantidadeDias+=29;
        else if(mesVar<8)
        {
            if  (mesVar%2==0) quantidadeDias+=30;
            else quantidadeDias+=31;
        }else
        {
            if  (mesVar%2==0) quantidadeDias+=31;
            else quantidadeDias+=30;
        }

        mesVar++;
        if  (mesVar>12)
        {
            mesVar=1;
            anoVar+=1;
        }
    }

    quantidadeDias+=this->dia;

    return quantidadeDias;
}

Data::Data(int dia,int mes,int ano):
    dia(dia),
    mes(mes),
    ano(ano)
{
    if  (dia>31) throw QString("Dia inválido");
    if  (mes>12) throw QString("Mês inválido");
}

QString Data::getDataQString()const
{
    QString saida="";

    saida+=QString::number(dia);
    saida+="/";
    saida+=QString::number(mes);
    saida+="/";
    saida+=QString::number(ano);

    return saida;
}

QString Data::desmaterializar()const
{
    QString saida="";

    saida+=QString::number(dia);
    saida+=";";
    saida+=QString::number(mes);
    saida+=";";
    saida+=QString::number(ano);

    return saida;
}

void Data::materializar(QString str)
{
    QStringList dados=str.split(";");
    dia=dados[0].toInt();
    mes=dados[1].toInt();
    ano=dados[2].toInt();
}

bool Data::operator<(Data objeto)const
{
    if  (this->ano!=objeto.ano) return (this->ano)<(objeto.ano);
    else if (this->mes!=objeto.mes) return (this->mes)<(objeto.mes);
    else return (this->dia)<(objeto.dia);
}

}

