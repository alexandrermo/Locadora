#ifndef VEICULOPERSISTENCIA_H
#define VEICULOPERSISTENCIA_H

#include<veiculo.h>
#include<crudgeral.h>
#include<QString>
#include<fstream>
#include<string>


namespace ar
{
class VeiculoPersistencia
{
private:
    QString nomeDoArquivoNoDisco;

public:
    VeiculoPersistencia(QString nomeDoArquivo);
    void incluir(Veiculo &objeto,bool novo=true)const;
    void apagarPorPlaca(QString id)const;
    std::list<Veiculo>* listagem()const;
    Veiculo buscarPorPlaca(QString cpf)const;
};
}
#endif // VEICULOPERSISTENCIA_H
