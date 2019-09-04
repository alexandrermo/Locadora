#ifndef ID_H
#define ID_H
#include<fstream>
#include<string>
#include<itransformardados.h>

namespace ar {


class Id : public ITransformarDados
{
private:
    int numero;
public:
    Id():numero(0){}
    Id(int numero):numero(numero){}
    QString desmaterializar()const{return QString::number(numero);}
    void materializar(QString str){numero=str.toInt();}
    int getNumero()const{return numero;}
    void setNumero(int n){numero=n;}
    void definirId();
};

}

#endif // ID_H
