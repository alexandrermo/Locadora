#include "telefone.h"

namespace ar {

    Telefone::Telefone(int ddi,int ddd,int numero):
        ddi(ddi),
        ddd(ddd),
        numero(numero)
        {
            if  (ddi==0) this->ddi=55;
            if  (ddd==0) this->ddd=62;
        }

    void Telefone::setTelefone(int ddi,int ddd,int numero)
    {
        if  (ddi==0) ddi=55;
        if  (ddd==0) ddd=62;

        this->ddi=ddi;
        this->ddd=ddd;
        this->numero=numero;
    }


    QString Telefone::getTelefone()const
    {
        QString saida;
        saida=QString::number(ddi);
        saida+="(";
        saida+=QString::number(ddd);
        saida+=")";
        saida+=QString::number(numero);

        return saida;
    }

    QString Telefone::desmaterializar() const
    {
        QString saida="";
        saida=QString::number(ddi);
        saida+=";";
        saida+=QString::number(ddd);
        saida+=";";
        saida+=QString::number(numero);

        return saida;
    }

    void Telefone::materializar(QString str)
    {
        QStringList dados=str.split(";");
        ddi=dados[0].toInt();
        ddd=dados[1].toInt();
        numero=dados[2].toInt();
    }
}

