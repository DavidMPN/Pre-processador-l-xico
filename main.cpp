#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#define TRUE 1
#define FALSE 0
#define TAMD 30

using namespace std;

//Armazena Variaveis de Controle de cada arquivo lido
class Control

{

    bool DoubleQuotes;
    bool TakeDef;
    bool TakeInc;
    bool UniCom;
    bool ExtCom;
    bool Write;

public:
    bool ReturnDoubleQuotesValue();
    bool ReturnTakeDef();
    bool ReturnTakeInc();
    bool ReturnComUni();
    bool ReturnComExt();
    bool ReturnWrite();


    void ChangeTakeDef(bool temp);
    void ChangeTakeInc(bool temp);
    void ChangeWrite(bool temp);
    void CheckDoubleQuotes(char temp);
    void ChangeComUni(bool temp);
    void ChangeComExt(bool temp);
    void ResetControlClass();
    void SetValues();

};

//Armazena as chaves e os valores de todos os defines de todos os arquivos
class DefineList
{

    /*

    EX:  #define TAM 20
           Key=TAM;
           Value=20;

    */

    string Key;
    string Value;

public:
    void AddListDefine(string KeyT,string ValueT);
    void ShowDefineList();
    string ReturnKeyValue();
    string ReturnValueValue();


};

unsigned int LengthD=0;

ifstream fl[TAMD];
ofstream out;

void WriteFile(string &Word,unsigned int CurrentFile,Control *c,char &LastChar);

bool readFile(const char *NameFileInput,unsigned int CurrentFile,DefineList *d);

#include "ClassFunctions.h"
#include "DefineAndInclude.h"
#include "ClearLineFunctions.h"

//Remove caracteres inválidos.
string RemoveInvalidChar(string Word,char &LastChar)
{

    string temp;

    for(unsigned int i=0; i<Word.length(); i++)
    {

        if(int(Word[i])>=32)
        {
            temp+=Word[i];


        }
    }

    LastChar=temp[temp.length()-1];
    return temp;

}

//Escreve um espaço no arquivo ou uma quebra de linha
void WriteSpaceOrBreakLineIfNecessary(string Word,char LastChar,bool &BreakLine)
{

    if(LastChar!=';' && LastChar!='}' && LastChar!='{' && LastChar!=')' && LastChar!='(' && LastChar!='\n')
    {
        out<<" ";

    }

    if(Word[0]=='#')
    {

        if(LastChar!='\n')
        {

            out<<"\n";

        }
        BreakLine=TRUE;

    }

}

//Escreve no arquivo.
void WriteFile(string &Word,unsigned int CurrentFile,Control *c,char &LastChar)
{
    unsigned int i;
    bool BreakLine=FALSE;

    if(c[CurrentFile].ReturnWrite()==TRUE && Word!="")
    {

        WriteSpaceOrBreakLineIfNecessary(Word,LastChar,BreakLine);
        Word=RemoveInvalidChar(Word,LastChar);
        out<<Word;

    }
    else
    {

        c[CurrentFile].ChangeWrite(TRUE);

    }

    if(BreakLine==TRUE)
    {

        out<<"\n";
        LastChar='\n';
    }


}

//Decide se vai pegar um caracterer para dividir em uma palavra.
void TakeCharOrNot(bool &DonTake,string &temp,string &FileLine,unsigned int i)
{

    if(DonTake==FALSE)
    {

        temp+=FileLine[i];

    }
    else
    {

        DonTake=FALSE;

    }


}

//Divide a linha em palavras e envia para verificar se � include ou define.
string DivideWords(string Line,Control *c,unsigned int CurrentFile,char &LastChar,DefineList *d)
{

    const char KeyCharacters[200]= {' ','"',')','(','>','<','+','-','*','&',';','/','=','}','{',']','[','!',':',','};
    unsigned int j,i;
    bool DonTake=FALSE;
    string temp,TempLine="";


    for(i=0; i<=Line.length(); i++)
    {

        c[CurrentFile].CheckDoubleQuotes(Line[i]);

        if(c[CurrentFile].ReturnDoubleQuotesValue()==FALSE || c[CurrentFile].ReturnTakeInc()==TRUE || c[CurrentFile].ReturnTakeDef()==TRUE)
        {

            for(j=0; j<strlen(KeyCharacters); j++)
            {

                if(Line[i]==KeyCharacters[j] || i==Line.length())
                {

                    if(temp!="")
                    {

                        TakeDefFunc(temp,CurrentFile,c,d);
                        TakeIncFunc(temp,CurrentFile,c,d);
                        VerifyDefineWords(temp,Line,i,CurrentFile,c,LastChar,d);
                        temp="";
                    }
                    DonTake=TRUE;

                }

            }

        }
        else
        {

            DonTake=TRUE;

        }

        TakeCharOrNot(DonTake,temp,Line,i);

    }

    return Line;

}

//L� o Arquivo,filtra linhas,manda gravar e retorna False se nao conseguiu ler o arquivo.
bool readFile(const char *NameFileInput,unsigned int CurrentFile,DefineList *d)
{
    Control *c;
    string FileLine,temp;
    char LastChar='\n';

    c=new Control;
    c[CurrentFile].ResetControlClass();
    fl[CurrentFile].open(NameFileInput);

    if(!fl[CurrentFile])
    {
        return FALSE;

    }

    while(getline(fl[CurrentFile],FileLine))
    {

        FileLine=RemoveSpace(FileLine);
        FileLine=RemoveUniqueComent(FileLine,c,CurrentFile);
        FileLine=RemoveExtenseComent(FileLine,c,CurrentFile);
        FileLine=DivideWords(FileLine,c,CurrentFile,LastChar,d);
        WriteFile(FileLine,CurrentFile,c,LastChar);

    }

    fl[CurrentFile].close();
    return TRUE;
}

//Main recebe por parâmetro o nome do arquivo que vai ler e o arquivo de saida.
int main(int argc,char *argv[])
{

    DefineList d[TAMD];
    unsigned int CurrentFile=0;

    out.open(argv[2]);

    if(readFile(argv[1],CurrentFile,d)==FALSE)
    {

        cout<<"Arquivo Nao Lido\n";

    }

    out.close();

}
