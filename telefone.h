#ifndef TELEFONE_H
#define TELEFONE_H
#include<QString>
#include<QStringList>
namespace ar {


class Telefone
{private:
    int ddd;
    int ddi;
    int numero;
public:
    Telefone():ddd(0),ddi(0),numero(0){}
    Telefone(int ddi,int ddd,int numero);
    QString getTelefone()const;
    void setTelefone(int ddi,int ddd,int numero);
    QString desmaterializar()const;
    void materializar(QString str);

    QString getDDI()const{return QString::number(ddi);}
    QString getDDD()const{return QString::number(ddd);}
    QString getNumero()const{return QString::number(numero);}
};
}
#endif // TELEFONE_H
