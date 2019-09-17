//Recebe o valor do define e ve se é string,inteiro ou float
void VerifyValueDefineStringOrInt(string &temp)
{
    unsigned int i;
    bool exit=FALSE;
    string tempB;

    //cout<<"TEMP: "<<int(temp[0])<<endl;

    if(temp[0]!=39)
    {

        for(i=0; i<temp.length() && exit==FALSE; i++)
        {

            if(temp[i]!=',')
            {

                if(temp[i]<'0' || temp[i]>'9')
                {

                    tempB+='"';
                    tempB+=temp;
                    tempB+='"';
                    temp=tempB;
                    exit=TRUE;

                }

            }

        }

    }

}

//Pega uma linha com uma key define e substitui por o Value
void VerifyDefineWords(string Word,string Line,unsigned int l,int CurrentFile,Control *c,char LastChar,DefineList *d)
{
    unsigned int j,i;
    string temp;

    for(i=0; i<LengthD; i++)
    {

        if(Word==d[i].ReturnKeyValue())
        {

            for(j=0; j<l-Word.length(); j++)
            {

                temp+=Line[j];

            }

            temp+=d[i].ReturnValueValue();

            for(j=l; j<=Line.length(); j++)
            {

                temp+=Line[j];

            }
            WriteFile(temp,CurrentFile,c,LastChar);
            c[CurrentFile].ChangeWrite(FALSE);

        }

    }



}

//Verifica se tem define e separa as palavras
void TakeDefFunc(string Word,unsigned int CurrentFile,Control *c,DefineList *d)
{


    if(c[CurrentFile].ReturnTakeDef()==TRUE)
    {

        if(d[LengthD].ReturnKeyValue()=="")
        {

            d[LengthD].AddListDefine(Word,"");

        }
        else
        {
            VerifyValueDefineStringOrInt(Word);
            d[LengthD].AddListDefine("",Word);
            c[CurrentFile].ChangeTakeDef(FALSE);
            c[CurrentFile].ChangeWrite(FALSE);
            LengthD++;

        }


    }

    if(Word=="#define")
    {

        c[CurrentFile].ChangeTakeDef(TRUE);

    }



}

//Verifica se tem Include e separa as palavras
void TakeIncFunc(string Word,unsigned int CurrentFile,Control *c,DefineList *d)
{
    string FileLine;
    int ignore=1;

    if(c[CurrentFile].ReturnTakeInc()==TRUE)
    {



        for(unsigned int i=0; i<Word.length(); i++)
        {

            if(Word[i]=='.')
            {
                ignore=0;

            }

        }

        if(ignore==0)
        {

            if(readFile(Word.c_str(),CurrentFile+1,d))
            {

                c[CurrentFile].ChangeWrite(FALSE);

            }

        }
        c[CurrentFile].ChangeTakeInc(FALSE);

    }


    if(Word=="#include")
    {

        c[CurrentFile].ChangeTakeInc(TRUE);

    }

}
