#ifndef ITRANSFORMARDADOS_H
#define ITRANSFORMARDADOS_H
#include<QString>
namespace ar
{
class ITransformarDados
{
    virtual QString desmaterializar()const=0;
    virtual void materializar(QString str)=0;
};
}
#endif // ITRANSFORMARDADOS_H
