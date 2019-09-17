
bool Control::ReturnDoubleQuotesValue(){

return DoubleQuotes;

}

void Control::CheckDoubleQuotes(char temp){

if(temp=='"'){

    if(DoubleQuotes==FALSE){

        DoubleQuotes=TRUE;

    }else{
    DoubleQuotes=FALSE;

    }

}

}

void Control::SetValues(){

DoubleQuotes=FALSE;

}

void Control::ChangeTakeDef(bool temp){

TakeDef=temp;

}

bool Control::ReturnTakeDef(){

return TakeDef;

};

void Control::ChangeTakeInc(bool temp){

TakeInc=temp;

}

void Control::ChangeWrite(bool temp){

Write=temp;

}

bool Control::ReturnTakeInc(){

return TakeInc;

};

bool Control::ReturnWrite(){

return Write;

};

void Control::ChangeComUni(bool temp){

UniCom=temp;


}

void Control::ChangeComExt(bool temp){

ExtCom=temp;


}

bool Control::ReturnComUni(){

return UniCom;

};

bool Control::ReturnComExt(){

return ExtCom;

};

void Control::ResetControlClass()
{


    SetValues();
    ChangeTakeDef(FALSE);
    ChangeTakeInc(FALSE);
    ChangeWrite(TRUE);
    ChangeComUni(FALSE);
    ChangeComExt(FALSE);



}

void DefineList::AddListDefine(string KeyT,string ValueT)
{

    if(KeyT!="")
    {
        Key=KeyT;
    }
    if(ValueT!="")
    {
        Value=ValueT;
    }


}

void DefineList::ShowDefineList()
{


    cout<<"Key: "<<Key<<endl;
    cout<<"Value: "<<Value<<endl;

}

string DefineList::ReturnKeyValue()
{

    return Key;

}

string DefineList::ReturnValueValue()
{

    return Value;

}

