#ifndef MARCAPERSISTENCIA_H
#define MARCAPERSISTENCIA_H
#include<marca.h>
#include<crudgeral.h>
#include<QString>
#include<fstream>
#include<string>

namespace ar {



class MarcaPersistencia :public CRUDGeral<Marca>
{
private:
     QString nomeDoArquivoNoDisco;
public:
    MarcaPersistencia();
    MarcaPersistencia(QString nomeDoArquivo);
    void incluir(Marca &objeto,bool novo=true)const;
    void apagarPorId(Id id)const;
    std::list<Marca>* listagem()const;
    Marca buscarPorId(Id id)const;
};

}
#endif // MARCAPERSISTENCIA_H
