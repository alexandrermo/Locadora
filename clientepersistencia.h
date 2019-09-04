#ifndef CLIENTEPERSISTENCIA_H
#define CLIENTEPERSISTENCIA_H

#include<cliente.h>
#include<crudgeral.h>
#include<QString>
#include<fstream>
#include<string>


namespace ar
{
class ClientePersistencia:public CRUDGeral<Cliente>
{
private:
    QString nomeDoArquivoNoDisco;

public:
    ClientePersistencia(QString nomeDoArquivo);
    void incluir(Cliente &objeto,bool novo=true)const;
    void apagarPorCpf(QString id)const;
    std::list<Cliente>* listagem()const;
    Cliente buscarPorCpf(QString cpf)const;
};
}
#endif // CLIENTEPERSISTENCIA_H
