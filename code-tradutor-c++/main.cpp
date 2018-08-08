#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <cassert>
#include <cstring>

/// R :: OP | RS | RT | RD | SHIFT | FUNC |
/// I :: OP | RS | RT | IMM |
/// J :: OP | ADDR |

using namespace std;

string ConvertBinToHex(string str_bin);
string ConvertBinToHex2(string str_bin);
string ConvertHexToBin(string str_hex);
string ConvertDecToBin(string str_dec, int num_bits);
string GetAddrReg(string reg);
string GetAddrReg(string reg1, string reg2);
string GetAddrReg(string regD, string regS, string regT);

int main()
{
    string const nome_code = "main.txt"; ///v2.0 raw
    string const nome_hex_4digi = "instructions_hex.hex";
    string const nome_bin_16bits = "instructions_bin_16bits.txt";
    string const nome_cabecalho = "v2.0 raw";

    ifstream arquivo_in_code; ///Ler um arquivo
    ofstream arquivo_out_hex; ///Escrever um arquivo
    ofstream arquivo_out_bin;

    string linha="";
    string command="";
    string instruction_in_binary="";
    string prmt[] = {"","",""};
    int c=0, p=0;
    int num_linha=0;

    arquivo_in_code.open(nome_code);
    if(arquivo_in_code.is_open())
    {
        arquivo_out_bin.open(nome_bin_16bits,ios::trunc);
        arquivo_out_hex.open(nome_hex_4digi,ios::trunc);

        arquivo_out_hex << nome_cabecalho << endl;

        while(getline(arquivo_in_code, linha))
        {
            c = 0;
            p = 0;
            prmt[0]="";
            prmt[1]="";
            prmt[2]="";
            command="";
            instruction_in_binary="";
            num_linha++;

            while(linha[c] != ' ')
            {
                command += linha[c];
                c++;
            }
            ///cout << endl << "command: " << command << endl;

            if(command == "add")
            {
                while(linha[c] != ';')
                {
                    if(linha[c] == ',')
                        p++;
                    else if(linha[c] != ' ')
                        prmt[p] += linha[c];
                    c++;
                }
                instruction_in_binary = "000" + GetAddrReg(prmt[1], prmt[2], prmt[0]) + "0000";
                ///cout << "instruction_in_binary: '" << instruction_in_binary << "'" << endl;
            }
            else if(command == "sub")
            {
                while(linha[c] != ';')
                {
                    if(linha[c] == ',')
                        p++;
                    else if(linha[c] != ' ')
                        prmt[p] += linha[c];
                    c++;
                }
                instruction_in_binary = "000" + GetAddrReg(prmt[1], prmt[2], prmt[0]) + "0001";
                ///cout << "instruction_in_binary: '" << instruction_in_binary << "'" << endl;
            }
            else if(command == "mult")
            {
                while(linha[c] != ';')
                {
                    if(linha[c] == ',')
                        p++;
                    else if(linha[c] != ' ')
                        prmt[p] += linha[c];
                    c++;
                }
                instruction_in_binary = "000" + GetAddrReg(prmt[1], prmt[2], prmt[0]) + "0010";
                ///cout << "instruction_in_binary: '" << instruction_in_binary << "'" << endl;
            }
            else if(command == "div")
            {
                while(linha[c] != ';')
                {
                    if(linha[c] == ',')
                        p++;
                    else if(linha[c] != ' ')
                        prmt[p] += linha[c];
                    c++;
                }
                instruction_in_binary = "000" + GetAddrReg(prmt[1], prmt[2], prmt[0]) + "0011";
                ///cout << "instruction_in_binary: '" << instruction_in_binary << "'" << endl;
            }
            else if(command == "and")
            {
                while(linha[c] != ';')
                {
                    if(linha[c] == ',')
                        p++;
                    else if(linha[c] != ' ')
                        prmt[p] += linha[c];
                    c++;
                }
                instruction_in_binary = "000" + GetAddrReg(prmt[1], prmt[2], prmt[0]) + "0100";
                ///cout << "instruction_in_binary: '" << instruction_in_binary << "'" << endl;
            }
            else if(command == "or")
            {
                while(linha[c] != ';')
                {
                    if(linha[c] == ',')
                        p++;
                    else if(linha[c] != ' ')
                        prmt[p] += linha[c];
                    c++;
                }
                instruction_in_binary = "000" + GetAddrReg(prmt[1], prmt[2], prmt[0]) + "0101";
                ///cout << "instruction_in_binary: '" << instruction_in_binary << "'" << endl;
            }
            else if(command == "not")   ///R :: RD = ~RS
            {
                while(linha[c] != ';')
                {
                    if(linha[c] == ',')
                        p++;
                    else if(linha[c] != ' ')
                        prmt[p] += linha[c];
                    c++;
                }
                instruction_in_binary = "000" + GetAddrReg(prmt[1]) + "000" + GetAddrReg(prmt[0]) + "0110";
                ///cout << "instruction_in_binary: '" << instruction_in_binary << "'" << endl;
            }
            else if(command == "shift") ///shift left <<
            {
                while(linha[c] != ';')
                {
                    if(linha[c] == ',')
                        p++;
                    else if(linha[c] != ' ')
                        prmt[p] += linha[c];
                    c++;
                }
                instruction_in_binary = "001" + ConvertDecToBin(prmt[2], 3) + GetAddrReg(prmt[1], prmt[0]) + "1111";
                ///cout << "instruction_in_binary: '" << instruction_in_binary << "'" << endl;
            }
            else if(command == "less")  ///<
            {
                while(linha[c] != ';')
                {
                    if(linha[c] == ',')
                        p++;
                    else if(linha[c] != ' ')
                        prmt[p] += linha[c];
                    c++;
                }
                instruction_in_binary = "010" + GetAddrReg(prmt[1], prmt[2], prmt[0]) + "0111";
                //cout << "instruction_in_binary: '" << instruction_in_binary << "'" << endl;
            }
            else if(command == "load")  ///I :: RT = M[IMM + RS] :: max 7f
            {
                while(linha[c] != ';')
                {
                    if(linha[c] == ',')
                        p++;
                    else if(linha[c] != ' ' && linha[c] != 'H' && linha[c] != 'h')
                        prmt[p] += linha[c];
                    c++;
                }
                instruction_in_binary = "011" + GetAddrReg(prmt[1], prmt[0]) + ConvertHexToBin(prmt[2]);
                ///cout << "instruction_in_binary: '" << instruction_in_binary << "'" << endl;
            }
            else if(command == "store") ///I :: M[IMM + RS] = RT :: max 7f
            {
                while(linha[c] != ';')
                {
                    if(linha[c] == ',')
                        p++;
                    else if(linha[c] != ' ' && linha[c] != 'H' && linha[c] != 'h')
                        prmt[p] += linha[c];
                    c++;
                }
                instruction_in_binary = "100" + GetAddrReg(prmt[1], prmt[0]) + ConvertHexToBin(prmt[2]);
                ///cout << "instruction_in_binary: '" << instruction_in_binary << "'" << endl;
            }
            else if(command == "equal") ///I :: IF(RS == RT) PC=IMM
            {
                while(linha[c] != ';')
                {
                    if(linha[c] == ',')
                        p++;
                    else if(linha[c] != ' ')
                        prmt[p] += linha[c];
                    c++;
                }
                instruction_in_binary = "101" + GetAddrReg(prmt[1], prmt[0]) + ConvertDecToBin(prmt[2], 7);
                ///cout << "instruction_in_binary: '" << instruction_in_binary << "'" << endl;
            }
            else if(command == "addi")  ///I :: RT = RS+IMM
            {
                while(linha[c] != ';')
                {
                    if(linha[c] == ',')
                        p++;
                    else if(linha[c] != ' ')
                        prmt[p] += linha[c];
                    c++;
                }
                instruction_in_binary = "110" + GetAddrReg(prmt[1], prmt[0]) + ConvertDecToBin(prmt[2], 7);
                ///cout << "instruction_in_binary: '" << instruction_in_binary << "'" << endl;
            }
            else if(command == "jump")  ///J :: JUMP ADDR :: (line)
            {
                while(linha[c] != ';')
                {
                    if(linha[c] != ' ')
                        prmt[p] += linha[c];
                    c++;
                }
                instruction_in_binary = "111" + ConvertDecToBin(prmt[0], 13);
                ///cout << "instruction_in_binary: '" << instruction_in_binary << "'" << endl;
            }
            else
            {
                cout << endl << "ERRO :::: linha: " << num_linha << " :::: comando invalido!!!" << endl << endl;
                assert(0);
            }
            arquivo_out_bin << instruction_in_binary << endl;
            ///cout << "INSTR HEX: " << ConvertBinToHex(instruction_in_binary) << endl;
            arquivo_out_hex << ConvertBinToHex(instruction_in_binary) << endl;
        }
        arquivo_in_code.close();
        arquivo_out_bin.close();
        arquivo_out_hex.close();

        cout << endl;
        cout << "===============COMPLETO===============" << endl;
        cout << "arquivo gerado: " << nome_hex_4digi << endl;
        cout << "======================================" << endl;
    }
    else
        cout << "ALERTA :::: Arquivo '" << nome_code << "' com o codigo em Assembly MIPS, NAO ENCONTRADO!!!" << endl;

    return 0;
}

string ConvertBinToHex2(string str_bin)
{
    string str_hex = "";
    char str_hex_aux[4];
    int num_dec=0;
    int tam = str_bin.length();
    int aux = tam-1;

    for(int i=0; i<tam; i++)
    {
        if(str_bin[i] == '1')
        {
            num_dec += pow(2,aux);
        }
        aux--;
    }

    sprintf(str_hex_aux, "%x", num_dec); ///mascara um numero decimal para hexadecimal em uma string

    for(int i=0; i<4; i++)
        str_hex += str_hex_aux[i];

    return str_hex;
}

string ConvertBinToHex(string str_bin) /// 0000 0000 0000 0000 -> a=0 b=1 c=2 d=3
{
    string str_hex = "";
    string a="x",b="x",c="x",d="x";
    char x1[]="xxxx",x2[]="xxxx",x3[]="xxxx",x4[]="xxxx";
    int p=0;

    ///cout << "str_bin: " << str_bin << endl;

    for(int i=0; i<4; i++,p++)
        x1[i] = str_bin[p];
    for(int i=0; i<4; i++,p++)
        x2[i] = str_bin[p];
    for(int i=0; i<4; i++,p++)
        x3[i] = str_bin[p];
    for(int i=0; i<4; i++,p++)
        x4[i] = str_bin[p];

    /*
    cout << "x1: '" << x1 << "'" << endl;
    cout << "x2: '" << x2 << "'" << endl;
    cout << "x3: '" << x3 << "'" << endl;
    cout << "x4: '" << x4 << "'" << endl;
    */

    if(strcmp(x1,"0000")==0)
        a="0";
    else if(strcmp(x1,"0001")==0)
        a="1";
    else if(strcmp(x1,"0010")==0)
        a="2";
    else if(strcmp(x1,"0011")==0)
        a="3";
    else if(strcmp(x1,"0100")==0)
        a="4";
    else if(strcmp(x1,"0101")==0)
        a="5";
    else if(strcmp(x1,"0110")==0)
        a="6";
    else if(strcmp(x1,"0111")==0)
        a="7";
    else if(strcmp(x1,"1000")==0)
        a="8";
    else if(strcmp(x1,"1001")==0)
        a="9";
    else if(strcmp(x1,"1010")==0)
        a="a";
    else if(strcmp(x1,"1011")==0)
        a="b";
    else if(strcmp(x1,"1100")==0)
        a="c";
    else if(strcmp(x1,"1101")==0)
        a="d";
    else if(strcmp(x1,"1110")==0)
        a="e";
    else if(strcmp(x1,"1111")==0)
        a="f";

    if(strcmp(x2,"0000")==0)
        b="0";
    else if(strcmp(x2,"0001")==0)
        b="1";
    else if(strcmp(x2,"0010")==0)
        b="2";
    else if(strcmp(x2,"0011")==0)
        b="3";
    else if(strcmp(x2,"0100")==0)
        b="4";
    else if(strcmp(x2,"0101")==0)
        b="5";
    else if(strcmp(x2,"0110")==0)
        b="6";
    else if(strcmp(x2,"0111")==0)
        b="7";
    else if(strcmp(x2,"1000")==0)
        b="8";
    else if(strcmp(x2,"1001")==0)
        b="9";
    else if(strcmp(x2,"1010")==0)
        b="a";
    else if(strcmp(x2,"1011")==0)
        b="b";
    else if(strcmp(x2,"1100")==0)
        b="c";
    else if(strcmp(x2,"1101")==0)
        b="d";
    else if(strcmp(x2,"1110")==0)
        b="e";
    else if(strcmp(x2,"1111")==0)
        b="f";

    if(strcmp(x3,"0000")==0)
        c="0";
    else if(strcmp(x3,"0001")==0)
        c="1";
    else if(strcmp(x3,"0010")==0)
        c="2";
    else if(strcmp(x3,"0011")==0)
        c="3";
    else if(strcmp(x3,"0100")==0)
        c="4";
    else if(strcmp(x3,"0101")==0)
        c="5";
    else if(strcmp(x3,"0110")==0)
        c="6";
    else if(strcmp(x3,"0111")==0)
        c="7";
    else if(strcmp(x3,"1000")==0)
        c="8";
    else if(strcmp(x3,"1001")==0)
        c="9";
    else if(strcmp(x3,"1010")==0)
        c="a";
    else if(strcmp(x3,"1011")==0)
        c="b";
    else if(strcmp(x3,"1100")==0)
        c="c";
    else if(strcmp(x3,"1101")==0)
        c="d";
    else if(strcmp(x3,"1110")==0)
        c="e";
    else if(strcmp(x3,"1111")==0)
        c="f";

    if(strcmp(x4,"0000")==0)
        d="0";
    else if(strcmp(x4,"0001")==0)
        d="1";
    else if(strcmp(x4,"0010")==0)
        d="2";
    else if(strcmp(x4,"0011")==0)
        d="3";
    else if(strcmp(x4,"0100")==0)
        d="4";
    else if(strcmp(x4,"0101")==0)
        d="5";
    else if(strcmp(x4,"0110")==0)
        d="6";
    else if(strcmp(x4,"0111")==0)
        d="7";
    else if(strcmp(x4,"1000")==0)
        d="8";
    else if(strcmp(x4,"1001")==0)
        d="9";
    else if(strcmp(x4,"1010")==0)
        d="a";
    else if(strcmp(x4,"1011")==0)
        d="b";
    else if(strcmp(x4,"1100")==0)
        d="c";
    else if(strcmp(x4,"1101")==0)
        d="d";
    else if(strcmp(x4,"1110")==0)
        d="e";
    else if(strcmp(x4,"1111")==0)
        d="f";

    str_hex = a+b+c+d;
    return str_hex;
}

string ConvertHexToBin(string str_hex)
{
    string str_bin="", a="XXXX";
    int tam = str_hex.length();

    for(int i=0; i<tam; i++)
    {
        if(i==0)
        {
            if(str_hex[i] == '0')
                a="000";
            else if(str_hex[i] == '1')
                a="001";
            else if(str_hex[i] == '2')
                a="010";
            else if(str_hex[i] == '3')
                a="011";
            else if(str_hex[i] == '4')
                a="100";
            else if(str_hex[i] == '5')
                a="101";
            else if(str_hex[i] == '6')
                a="110";
            else if(str_hex[i] == '7')
                a="111";
        }
        else
        {
            if(str_hex[i] == '0')
                a="0000";
            else if(str_hex[i] == '1')
                a="0001";
            else if(str_hex[i] == '2')
                a="0010";
            else if(str_hex[i] == '3')
                a="0011";
            else if(str_hex[i] == '4')
                a="0100";
            else if(str_hex[i] == '5')
                a="0101";
            else if(str_hex[i] == '6')
                a="0110";
            else if(str_hex[i] == '7')
                a="0111";
            else if(str_hex[i] == '8')
                a="1000";
            else if(str_hex[i] == '9')
                a="1001";
            else if(str_hex[i] == 'a')
                a="1010";
            else if(str_hex[i] == 'b')
                a="1011";
            else if(str_hex[i] == 'c')
                a="1100";
            else if(str_hex[i] == 'd')
                a="1101";
            else if(str_hex[i] == 'e')
                a="1110";
            else if(str_hex[i] == 'f')
                a="1111";
        }
        str_bin += a;
    }
    return str_bin;
}

string ConvertDecToBin(string str_dec, int num_bits)
{
    int num_dec = stoi(str_dec); ///converte string para int
    int cociente=0, resto=0;
    string aux="";
    string str_bin="";
    string zeros="";

    cociente = num_dec;
    while(cociente >= 1)
    {
        resto = cociente%2;
        if(resto==0)
            aux += "0";
        else
            aux += "1";
        cociente /= 2;
    }

    int tam = aux.length();
    for(int i=tam-1; i>=0; i--) ///inverter a string
        str_bin += aux[i];

    int dif = num_bits-tam;
    if(tam < num_bits)
    {
        for(int i=0; i<dif; i++)
            zeros += "0";
        str_bin = zeros+str_bin;
    }

    return str_bin;
}

string GetAddrReg(string reg)
{
    string str_address="rrr";

    if(reg=="$0" || reg=="$zero") ///0
        str_address = "000";
    else if(reg=="$s0") ///..........1
        str_address = "001";
    else if(reg=="$s1") ///..........2
        str_address = "010";
    else if(reg=="$s2") ///..........3
        str_address = "011";
    else if(reg=="$t0") ///..........4
        str_address = "100";
    else if(reg=="$t1") ///..........5
        str_address = "101";
    else if(reg=="$d0") ///..........6
        str_address = "110";
    else if(reg=="$d1") ///..........7
        str_address = "111";

    return str_address;
}

string GetAddrReg(string reg1, string reg2)
{
    string str_address="";
    string reg[] = {reg1, reg2};

    for(int i=0; i<2; i++)
    {
        if(reg[i]=="$0" || reg[i]=="$zero") ///0
            str_address += "000";
        else if(reg[i]=="$s0") ///..........1
            str_address += "001";
        else if(reg[i]=="$s1") ///..........2
            str_address += "010";
        else if(reg[i]=="$s2") ///..........3
            str_address += "011";
        else if(reg[i]=="$t0") ///..........4
            str_address += "100";
        else if(reg[i]=="$t1") ///..........5
            str_address += "101";
        else if(reg[i]=="$d0") ///..........6
            str_address += "110";
        else if(reg[i]=="$d1") ///..........7
            str_address += "111";
    }

    return str_address;
}

string GetAddrReg(string regD, string regS, string regT)
{
    string str_address="";
    string reg[] = {regD, regS, regT};

    for(int i=0; i<3; i++)
    {
        if(reg[i]=="$0" || reg[i]=="$zero") ///0
            str_address += "000";
        else if(reg[i]=="$s0") ///..........1
            str_address += "001";
        else if(reg[i]=="$s1") ///..........2
            str_address += "010";
        else if(reg[i]=="$s2") ///..........3
            str_address += "011";
        else if(reg[i]=="$t0") ///..........4
            str_address += "100";
        else if(reg[i]=="$t1") ///..........5
            str_address += "101";
        else if(reg[i]=="$d0") ///..........6
            str_address += "110";
        else if(reg[i]=="$d1") ///..........7
            str_address += "111";
    }

    return str_address;
}

