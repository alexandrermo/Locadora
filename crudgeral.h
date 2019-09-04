#ifndef CRUDGERAL_H
#define CRUDGERAL_H

#include<QString>
#include<list>

namespace ar
{

template <class tipo>
class CRUDGeral
{
public:
    virtual void incluir(tipo &objeto, bool novo)const=0;
    //virtual void alterar(tipo objeto)const=0;
    virtual std::list<tipo>* listagem()const=0;
};

}


#endif // CRUDGERAL_H
