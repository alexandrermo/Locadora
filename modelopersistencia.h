#ifndef MODELOPERSISTENCIA_H
#define MODELOPERSISTENCIA_H
#include<modelo.h>
#include<crudgeral.h>
#include<QString>
#include<fstream>
#include<string>

namespace ar {



class ModeloPersistencia :public CRUDGeral<Modelo>
{
private:
     QString nomeDoArquivoNoDisco;
public:
    ModeloPersistencia();
    ModeloPersistencia(QString nomeDoArquivo);
    void incluir(Modelo &objeto,bool novo=true)const;
    void apagarPorId(Id id)const;
    std::list<Modelo>* listagem()const;
    Modelo buscarPorId(Id id)const;
    Modelo buscarPorDescricao(QString descricao)const;
};

}
#endif // MODELOPERSISTENCIA_H
