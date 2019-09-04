#include "id.h"
namespace ar {



void Id::definirId(){
    std::fstream arquivoId;
    arquivoId.open("ID.txt",std::ios::in);
    std::string str="";
    if(arquivoId.is_open()){
        getline(arquivoId,str);
        numero=std::stoi(str);
        arquivoId.close();
    }
    numero++;
    arquivoId.open("ID.txt",std::ios::out);
    if(!arquivoId.is_open())
    {
        throw QString ("ID txt não abriu, ao chamar definirID.");
    }
    arquivoId<<std::to_string(numero);
    arquivoId.close();
}

}
