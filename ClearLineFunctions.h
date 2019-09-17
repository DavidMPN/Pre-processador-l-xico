//Remove o excesso de espaços
string RemoveSpace(string FileLine)
{

    unsigned int i;
    bool Remove=FALSE;
    string temp;

    for(i=0; i<FileLine.length(); i++)
    {

        if(FileLine[i]==' ' && Remove==FALSE)
        {

            Remove=TRUE;
            if(i!=0)
            {

                temp+=FileLine[i];
            }


        }
        else
        {

            if(FileLine[i]!=' ')
            {

                Remove=FALSE;
                temp+=FileLine[i];
            }

        }
    }

    return temp;

}

//Procura e remove os comentarios unicos
string RemoveUniqueComent(string Line,Control *c,unsigned int CurrentFile)
{
    unsigned int i;
    string temp;

    for(i=0; i<Line.length(); i++)
    {

        if(Line[i]=='/' && Line[i+1]=='/')
        {

            c[CurrentFile].ChangeComUni(TRUE);

        }
        else
        {

            if(c[CurrentFile].ReturnComUni()==FALSE)
            {

                temp+=Line[i];

            }

        }

    }
    c[CurrentFile].ChangeComUni(FALSE);
    return temp;

}

//Procura e remove os comentarios extensos
string RemoveExtenseComent(string Line,Control *c,unsigned int CurrentFile)
{
    unsigned int i;
    string temp;

    for(i=0; i<Line.length(); i++)
    {

        if(Line[i]=='/' && Line[i+1]=='*')
        {

            c[CurrentFile].ChangeComExt(TRUE);

        }

        if(c[CurrentFile].ReturnComExt()==FALSE)
        {

            temp+=Line[i];

        }

        if(Line[i]=='*' && Line[i+1]=='/')
        {

            c[CurrentFile].ChangeComExt(FALSE);
            i++;

        }

    }

    return temp;

}
