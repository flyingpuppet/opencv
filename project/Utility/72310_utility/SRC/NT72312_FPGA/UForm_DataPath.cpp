//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "UForm_DataPath.h"
#include <math.hpp>
#include <stdio.h>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "UMEMCForm"
#pragma link "RegLabeledEdit"
#pragma link "RegCheckBox"
#pragma resource "*.dfm"
TForm_DataPath *Form_DataPath;

static __S_Film_Mode _S_FilmMode[10] =
{
  {0, "video"},
  {1, "22"},
  {2, "32"},
  {3, "3223"},
  {4, "2224"},
  {5, "32322"},
  {6, "1123"},
  {7, "55"},
  {8, "64"},
  {9, "87"},
};

static int H_Active[] = {1366, 1920, 1280};
static int V_Active[] = {768, 1080, 720};
static int H_Total[] = {1560, 2200, 2220};
static int V_Total[] = {806, 1140, 1125};
static int _InVSync[] = {50, 60, 24, 25, 48, 100, 120, 30, 0};
static int _OutVSync[] = {50, 100, 200, 60, 120, 240, 75, 0};
static AnsiString VInName[] =
{
    "rb_In_50",
    "rb_In_60",
    "rb_In_24",
    "rb_In_25",
    "rb_In_48",
    "rb_In_100",
    "rb_In_120",
    "rb_In_30",
};
static AnsiString VOutName[] =
{
    "rb_Out_50",
    "rb_Out_100",
    "rb_Out_200",
    "rb_Out_60",
    "rb_Out_120",
    "rb_Out_240",
    "rb_Out_75",
};

static unsigned int OutFormatShutterGla[] =
{
    3, //count
// DataType    Address     Data
// 32bits:'D', 8bits:'B'
    'D',    0xE0001020,     0x00300000,
    'B',    0xE0001030,     0xB4,
    'B',    0xE0001031,     0xB4,
};


static unsigned int HVDelay_1280[] =
{
    5,
    0xE0000080,     0,          8,              0x2A,
    0xE0000082,     0,          8,              0x50,
    //0xE0000085,     0,          8,              0xF0,
    0xE000008A,     0,          8,              0x5A,
    0xE00000CA,     0,          8,              0x4C,
    0xE00000EC,     0,          32,             0x0FFF02D2,
};
static unsigned int HVDelay_1366[] =
{
    0,
};
static unsigned int HVDelay_1920[] =
{
    5,
    0xE0000080,     0,          8,              0x40,
    0xE0000082,     0,          8,              0x7C,
    //0xE0000085,     0,          8,              0xF0,
    0xE000008A,     0,          8,              0x87,
    0xE00000CA,     0,          8,              0x70,
    0xE00000EC,     0,          32,             0x05AA043A,
};

static unsigned int Window_1280[] =
{
    13,
    0xE0000A00,     0,          16,             0x5AA0,
    0xE0000048,     0,          16,             0x5AA0,
    0xE000051C,     0,          32,             0x5A00A000,
    0xE00000B8,     0,          32,             0x0166027E,
    0xE00000BC,     0,          32,             0x599F0000,
    0xE0001644,     0,          32,             0x0166027E,
    0xE0001648,     0,          32,             0x599F0000,
    0xE0000050,     0,          32,             0x02CF04FF,
    0xE0000058,     0,          32,             0x02CA04FA,
    0xE0001614,     0,          32,             0x02CF04FF,
    0xE000161C,     0,          32,             0x02CA04FA,
    0xE000041C,     0,          32,             0x0167027E,
    0xE000137C,     0,          16,             0x02D0,

};
static unsigned int Window_1366[] =
{
    0,
};
static unsigned int Window_1920[] =
{
    13,
    0xE0000A00,     0,          16,             0x87F0,
    0xE0000048,     0,          16,             0x87F0,
    0xE000051C,     0,          32,             0x8700F000,
    0xE00000B8,     0,          32,             0x021903BD,
    0xE00000BC,     0,          32,             0x86EF0000,
    0xE0001644,     0,          32,             0x021903BD,
    0xE0001648,     0,          32,             0x86EF0000,
    0xE0000050,     0,          32,             0x0437077F,
    0xE0000058,     0,          32,             0x0432077A,
    0xE0001614,     0,          32,             0x0437077F,
    0xE000161C,     0,          32,             0x0432077A,
    0xE000041C,     0,          32,             0x021B03BF,
    0xE000137C,     0,          16,             0x0438,
};

//1366 load H and V parameter
static unsigned int resolution_1366[] =
{
    23,    //count
// startAddress    startbit    bit length      Data
//(unit of 8 bits)
    0xE000010E,     0,           12,            H_Active[Reso_1366]/2,//0x02AB,  //HAct IP
    0xE000006E,     0,           12,            H_Active[Reso_1366]/2,//0x02AB,,  //HAct Timing Gen
    0xE0000B52,     0,           10,            H_Active[Reso_1366]/2,//0x02AB,,  //Y HAct MMU
    0xE0000B54,     0,           10,            H_Active[Reso_1366]/2,//0x02AB,,  //C HAct MMU
    0xE0000112,     0,           12,            V_Active[Reso_1366],  //0x0300,   //VAct IP
    0xE0000072,     0,           12,            V_Active[Reso_1366],  //0x0300, //VAct Timing Gen
    0xE0000B48,     0,           16,            H_Active[Reso_1366]/4,//0x0155,  //ME Y HActive MMU
    0xE0000B4A,     0,           16,            V_Active[Reso_1366]/2,//0x0180,  //ME Y VActive MMU
    0xE0000B56,     0,           11,            V_Active[Reso_1366],//0x300,  //VAct MMU
    0xE0000A13,     0,           12,            V_Active[Reso_1366],//0x0300,  //VAct ME3
    0xE000010C,     0,           12,            H_Total[Reso_1366]/2,//0x030C,  //HTotal IP
    0xE000006C,     0,           12,            H_Total[Reso_1366]/2,//0x030C,  //HTotal Timing Gen
    0xE0000070,     0,           12,            V_Total[Reso_1366],//0x0326,  //VTotal Timing Gen
    0xE0000D48,     0,           11,            H_Active[Reso_1366]/2,//0x02AB,  //Mute hmax IP2
    0xE0000D4A,     0,           11,            H_Active[Reso_1366]/2,//0x02AB,  //Mute hmin IP2
    0xE0000D4C,     0,           11,            V_Active[Reso_1366],//0x0300,  //Mute vmax IP2
    0xE0000D4E,     0,           11,            V_Active[Reso_1366],//0x0300,  //Mute vmin IP2
    0xE0000190,     0,           12,            0,       //cap_h0(start) IP
    0xE0000192,     0,           12,            0,       //cap_v0(start) IP
    0xE0000194,     0,           12,            H_Active[Reso_1366]/2,//0x02AB,  //cap_h_act IP
    0xE0000196,     0,           12,            V_Active[Reso_1366],//0x0300,  //cap_v_act IP
    0xE0000D6C,     0,           12,            H_Active[Reso_1366]/4,//0x0155,  //h_center  only use at 3D_TB in
    0xE0000D6E,     0,           12,            V_Active[Reso_1366]/2,//0x0180,  //v_center  onlu use at 3D_SBS in
    0xE0000064,     8,           24,            0x23366C,
    0xE0000069,     0,           8,             2,
};

static unsigned int resolution_640[] =
{
    //26,    //count
    26,
// startAddress    startbit    bit length      Data
//(unit of 8 bits)
    0xE000010E,     0,           12,            H_Active[Reso_1280]/2,//0x02AB,  //HAct IP
    0xE000006E,     0,           12,            H_Active[Reso_1280]/2,//0x02AB,,  //HAct Timing Gen
    0xE0000B52,     0,           10,            H_Active[Reso_1280]/2,//0x02AB,,  //Y HAct MMU
    0xE0000B54,     0,           10,            H_Active[Reso_1280]/2,//0x02AB,,  //C HAct MMU
    0xE0000112,     0,           12,            V_Active[Reso_1280],  //0x0300,   //VAct IP
    0xE0000072,     0,           12,            V_Active[Reso_1280],  //0x0300, //VAct Timing Gen         //
    0xE0000B48,     0,           16,            H_Active[Reso_1280]/4,//0x0155,  //ME Y HActive MMU
    0xE0000B4A,     0,           16,            V_Active[Reso_1280]/2,//0x0180,  //ME Y VActive MMU
    0xE0000B56,     0,           11,            V_Active[Reso_1280],//0x300,  //VAct MMU
    0xE0000A13,     0,           12,            V_Active[Reso_1280],//0x0300,  //VAct ME3
    0xE000010C,     0,           12,            H_Total[Reso_1280]/2,//0x030C,  //HTotal IP              //
    0xE000011A,     0,           12,            H_Total[Reso_1280]/2,//0x030C,  //HTotal IP              //
    0xE000006C,     0,           12,            H_Total[Reso_1280]/2,//0x030C,  //HTotal Timing Gen
    0xE0000070,     0,           12,            V_Total[Reso_1280],//0x0326,  //VTotal Timing Gen
    0xE0000D48,     0,           11,            H_Active[Reso_1280]/2,//0x02AB,  //Mute hmax IP2
    0xE0000D4A,     0,           11,            H_Active[Reso_1280]/2,//0x02AB,  //Mute hmin IP2
    0xE0000D4C,     0,           11,            V_Active[Reso_1280],//0x0300,  //Mute vmax IP2
    0xE0000D4E,     0,           11,            V_Active[Reso_1280],//0x0300,  //Mute vmin IP2
    0xE0000190,     0,           12,            0,       //cap_h0(start) IP
    0xE0000192,     0,           12,            0,       //cap_v0(start) IP
    0xE0000194,     0,           12,            H_Active[Reso_1280]/2,//0x02AB,  //cap_h_act IP
    0xE0000196,     0,           12,            V_Active[Reso_1280],//0x0300,  //cap_v_act IP
    0xE0000D6C,     0,           12,            H_Active[Reso_1280]/4,//0x0155,  //h_center  only use at 3D_TB in
    0xE0000D6E,     0,           12,            V_Active[Reso_1280]/2,//0x0180,  //v_center  onlu use at 3D_SBS in
    0xE0000064,     8,           24,            0x12804F,
    0xE0000069,     0,           8,             1,
    //0xE000162E,     0,           12,            0x43B,
    //0xE0001001,     0,           1,             1,                     //                     //
};

static unsigned int resolution_1920[] =
{
    25,    //count
// startAddress    startbit    bit length      Data
//(unit of 8 bits)
    0xE000010E,     0,           12,            H_Active[Reso_1920]/2,//0x02AB,  //HAct IP
    0xE000006E,     0,           12,            H_Active[Reso_1920]/2,//0x02AB,,  //HAct Timing Gen
    0xE0000B52,     0,           10,            H_Active[Reso_1920]/2,//0x02AB,,  //Y HAct MMU
    0xE0000B54,     0,           10,            H_Active[Reso_1920]/2,//0x02AB,,  //C HAct MMU
    0xE0000112,     0,           12,            V_Active[Reso_1920],  //0x0300,   //VAct IP
    0xE0000072,     0,           12,            V_Active[Reso_1920],  //0x0300, //VAct Timing Gen
    0xE0000B48,     0,           16,            H_Active[Reso_1920]/4,//0x0155,  //ME Y HActive MMU
    0xE0000B4A,     0,           16,            V_Active[Reso_1920]/2,//0x0180,  //ME Y VActive MMU
    0xE0000B56,     0,           11,            V_Active[Reso_1920],//0x300,  //VAct MMU
    0xE0000A13,     0,           12,            V_Active[Reso_1920],//0x0300,  //VAct ME3
    0xE000010C,     0,           12,            H_Total[Reso_1920]/2,//0x030C,  //HTotal IP
    0xE000006C,     0,           12,            H_Total[Reso_1920]/2,//0x030C,  //HTotal Timing Gen
    0xE0000070,     0,           12,            V_Total[Reso_1920],//0x0326,  //VTotal Timing Gen
    0xE0000D48,     0,           11,            H_Active[Reso_1920]/2,//0x02AB,  //Mute hmax IP2
    0xE0000D4A,     0,           11,            H_Active[Reso_1920]/2,//0x02AB,  //Mute hmin IP2
    0xE0000D4C,     0,           11,            V_Active[Reso_1920],//0x0300,  //Mute vmax IP2
    0xE0000D4E,     0,           11,            V_Active[Reso_1920],//0x0300,  //Mute vmin IP2
    0xE0000190,     0,           12,            0,       //cap_h0(start) IP
    0xE0000192,     0,           12,            0,       //cap_v0(start) IP
    0xE0000194,     0,           12,            H_Active[Reso_1920]/2,//0x02AB,  //cap_h_act IP
    0xE0000196,     0,           12,            V_Active[Reso_1920],//0x0300,  //cap_v_act IP
    0xE0000D6C,     0,           12,            H_Active[Reso_1920]/4,//0x0155,  //h_center  only use at 3D_TB in
    0xE0000D6E,     0,           12,            V_Active[Reso_1920]/2,//0x0180,  //v_center  onlu use at 3D_SBS in
    0xE0000064,     8,           24,            0x23366C,
    0xE0000069,     0,           8,             2,
};


static unsigned int Address_TOP[] =
{
    14,    //count
// startAddress    startbit    bit length      Data
    0xE0000000,     0,          32,             0x03800100,
    0xE0000004,     0,          32,             0x08800600,
    0xE0000008,     0,          32,             0x0D800B00,
    0xE000000C,     0,          32,             0x12801000,
    0xE0000010,     0,          32,             0x17801500,
    0xE0000014,     0,          32,             0x1C801A00,
    0xE0000018,     0,          32,             0x21801F00,
    0xE000001C,     0,          32,             0x26802400,
    0xE0000020,     0,          32,             0x2B802900,
    0xE0000024,     0,          32,             0x2F002E00,
    0xE0000028,     0,          32,             0x31003000,
    0xE000002C,     0,          32,             0x33003200,
    0xE0000030,     0,          32,             0x35003400,
    0xE0000034,     0,          32,             0x37003600,
    0xE0001004,     0,          32,             0x01400080,
    0xE0001008,     0,          32,             0x00800080,
};
/*unsigned int SBS1366[] =
{
    9,    //count
// startAddress    startbit    bit length      Data
//(unit of 8 bits)
    0xE000010E,     0,           12,            0x02AC,  //HAct IP         SBS HActive should be 1368
    0xE000006E,     0,           12,            0x02AC,  //HAct Timing Gen SBS HActive should be 1368
    0xE0000B48,     0,           16,            0x0156,
    0xE0000B4A,     0,           16,            0x0180,
    0xE0000B52,     0,           10,            0x0156,  //Y HAct MMU
    0xE0000B54,     0,           10,            0x0156,  //C HAct MMU
    0xE0000D48,     0,           11,            0x02AC,  //Mute hmax IP2
    0xE0000D4A,     0,           11,            0x02AC,  //Mute hmin IP2
    0xE0000194,     0,           12,            0x02AC,  //cap_h_act IP
};


/*unsigned int Else1366[] =
{
    9,    //count
// startAddress    startbit    bit length      Data
//(unit of 8 bits)
    0xE000010E,     0,           12,            0x02AB,
    0xE000006E,     0,           12,            0x02AB,
    0xE0000B48,     0,           16,            0x0155,
    0xE0000B4A,     0,           16,            0x0180,
    0xE0000B52,     0,           10,            0x02AB,
    0xE0000B54,     0,           10,            0x02AB,
    0xE0000D48,     0,           11,            0x02AB,
    0xE0000D4A,     0,           11,            0x02AB,
    0xE0000194,     0,           12,            0x02AB,
};                  */

//---------------------------------------------------------------------------
void __fastcall TForm_DataPath::TrimList(TStringList * sl)
{
    int count;
    count = sl->Count;
    for(int i=count-1; i>=0;i--)
    {
        if(sl->Strings[i] == "")
        {
            sl->Delete(i);
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall TForm_DataPath::Set2D3DResoPara(InputFormat in, OutputFormat out, InputResolution re)
{
    if(re != Reso_1280)
    {

        switch(in)
        {
            case In_3D_SBS:
                WriteFormatPara(0xE0000B52,0,10,H_Active[re]/4);
                WriteFormatPara(0xE0000B54,0,10,H_Active[re]/4);
                WriteFormatPara(0xE0000B56,0,11,V_Active[re]);
            break;
            case In_3D_TB:

                WriteFormatPara(0xE0000B52,0,10,H_Active[re]/2);
                WriteFormatPara(0xE0000B54,0,10,H_Active[re]/2);
                switch(out)
                {
                    //Vact should be changed when output frame packet changed
                    case Out_3D_Passive:
                        WriteFormatPara(0xE0000B56,0,11,V_Active[re]);
                    break;
                    default:
                        WriteFormatPara(0xE0000B56,0,11,V_Active[re]/2);
                    break;
                }
                break;
            default :
                WriteFormatPara(0xE0000B52,0,10,H_Active[re]/2);
                WriteFormatPara(0xE0000B54,0,10,H_Active[re]/2);
                WriteFormatPara(0xE0000B56,0,11,V_Active[re]);
            break;
        }
    }

    if(b_ChangedSam)
    {
        if(CB_Samsung->Enabled && CB_Samsung->Checked)
        {
            Word d;
            if(eInputType == PC)
            {
                d = 0x0000;
            }
            else
            {
                d = 0x3000;
            }
            WriteFormatPara(0xE0000D50,0,16,d|(V_Active[re]/2));
            WriteFormatPara(0xE0000B5B,0,1,1);
            WriteFormatPara(0xE00002FE,0,1,1);
            WriteFormatPara(0xE0001379,1,1,1);
            WriteFormatPara(0xE000130B,0,8,(Byte)(V_Active[re]/2));
            WriteFormatPara(0xE000130C,4,4,((V_Active[re]/2)>>8));
            WriteFormatPara(0xE0000D51,4,2,3);
        }
        else
        {
            WriteFormatPara(0xE0000D50,0,16,0x01B0);
            WriteFormatPara(0xE0000B5B,0,1,0);
            WriteFormatPara(0xE00002FE,0,1,0);
            WriteFormatPara(0xE0001379,1,1,0);
            WriteFormatPara(0xE000130B,0,8,(Byte)(V_Active[re]/2));
            WriteFormatPara(0xE000130C,4,4,0x0E|((V_Active[re]/2)>>8));
            WriteFormatPara(0xE0000D51,4,2,0);
        }
    }
    
    unsigned int val_ip2_a4, val_mc00, val_ip_A0;
    Byte ip_98;

    GetDevice()->AllReadDWord(0xE0000DA4, val_ip2_a4);
    GetDevice()->AllReadDWord(0xE0000200, val_mc00);
    GetDevice()->AllReadByte(0xE0000198, ip_98);
    GetDevice()->AllReadDWord(0xE00001A0, val_ip_A0);
    ip_98 &= 0xBF;
    val_mc00 &= 0x000000FF;
    val_ip2_a4 &= 0xFFFF0000;
    val_ip_A0 &= 0xFF000000;
    switch(re)
    {

        case Reso_1366:
            val_ip2_a4 |= 0x00001003;
            val_mc00 |= 0x01071000;
            val_ip_A0 |= 0x0012AB80;
            if(in == In_3D_LR)
            {
                ip_98 |= 0x40;
            }
            GetDevice()->AllWriteByte(0xE0000198, ip_98);
            GetDevice()->AllWriteDWord(0xE0000DA4, val_ip2_a4);
            GetDevice()->AllWriteDWord(0xE0000200, val_mc00);
            GetDevice()->AllWriteByte(0xE00000107, 0x07);

            if(in == In_3D_SBS)
            {
                if(cb_logoOn->Checked)  //on
                {
                    GetDevice()->AllWriteDWord(0xE0000DA0, 0x0503040A);
                }
                else               //off
                {
                    GetDevice()->AllWriteDWord(0xE0000DA0, 0x0803060A);
                }
            }
            else
            {
                if(cb_logoOn->Checked)   //on
                {
                    GetDevice()->AllWriteDWord(0xE0000DA0, 0x05020205);
                }
                else                //off
                {
                    GetDevice()->AllWriteDWord(0xE0000DA0, 0x08020305);
                }
            }
        break;
        case Reso_1920:
            val_ip2_a4 |= 0x00001003;
            val_mc00 |= 0x01071000;
            val_ip_A0 |= 0x0023C01C;
            if(in == In_3D_LR)
            {
                ip_98 |= 0x40;
            }
            GetDevice()->AllWriteByte(0xE0000198, ip_98);
            GetDevice()->AllWriteDWord(0xE0000DA4, val_ip2_a4);
            GetDevice()->AllWriteDWord(0xE0000200, val_mc00);
            GetDevice()->AllWriteByte(0xE00000107, 0x07);

            if(in == In_3D_SBS)
            {
                if(cb_logoOn->Checked)  //on
                {
                    GetDevice()->AllWriteDWord(0xE0000DA0, 0x0500000F);
                }
                else               //off
                {
                    GetDevice()->AllWriteDWord(0xE0000DA0, 0x0800000F);
                }
            }
            else
            {
                if(cb_logoOn->Checked)   //on
                {
                    GetDevice()->AllWriteDWord(0xE0000DA0, 0x05020307);
                }
                else                //off
                {
                    GetDevice()->AllWriteDWord(0xE0000DA0, 0x08020407);
                }
            }
        break;
    }
    /*switch(re)
    {
        case Reso_1366:
            switch(in)
            {
                case In_3D_SBS:
                    WriteFormatPara(0xE0000B52,0,10,H_Active[re]/4);
                    WriteFormatPara(0xE0000B54,0,10,H_Active[re]/4);
                    WriteFormatPara(0xE0000B56,0,10,V_Active[re]);
                break;
                case In_3D_TB:

                    WriteFormatPara(0xE0000B52,0,10,H_Active[re]/2);
                    WriteFormatPara(0xE0000B54,0,10,H_Active[re]/2);
                    switch(out)
                    {
                        //Vact should be changed when output frame packet changed
                        case Out_3D_Passive:
                            WriteFormatPara(0xE0000B56,0,10,V_Active[re]);
                        break;
                        default:
                            WriteFormatPara(0xE0000B56,0,10,V_Active[re]/2);
                        break;
                    }
                    break;
                default :
                    WriteFormatPara(0xE0000B52,0,10,H_Active[re]/2);
                    WriteFormatPara(0xE0000B54,0,10,H_Active[re]/2);
                    WriteFormatPara(0xE0000B56,0,10,V_Active[re]);
                break;
            }
        break;
        case Reso_1280:

        break;
        case Reso_1920:
        break;
    }*/        
}
//---------------------------------------------------------------------------
void __fastcall TForm_DataPath::SetInputType(InputType in)
{
    Byte val, vcsc, vicsc;
    Byte value_ip5B, value_mmu17, value_post60, value_Ip251, value_me380, value_mc00, value_dep8C, value_ipFB;

    GetDevice()->AllReadByte(0xE000003A, val);
    GetDevice()->AllReadByte(0xE0000158, vcsc);
    GetDevice()->AllReadByte(0xE0001360, vicsc);
    GetDevice()->AllReadByte(0xE0000D51, value_Ip251);
    val &= 0xFE;
    vcsc &= 0xFE;
    vicsc &= 0xFE;
    value_Ip251 &= 0xCF;
    switch(in)
    {
        case PC:
            val |= 0x00;
            vcsc |= 0x00;
            vicsc |= 0x00;
            //value_post60 = 0x00;
            value_ip5B = 0x78;
            value_mmu17 = 0x27;
            value_me380 = 0xDf;
            value_mc00 = 0x01;
            value_dep8C = 0x03;
            //value_Ip251 |= 0x00;
            value_ipFB = 0x20;
            GetDevice()->AllWriteDWord(0xE0000000, 0x02DA0100);
            GetDevice()->AllWriteDWord(0xE0000004, 0x068E04B4);
            GetDevice()->AllWriteDWord(0xE000000C, 0x0A420868);
            GetDevice()->AllWriteDWord(0xE0000010, 0x0DF60C1C);
            GetDevice()->AllWriteDWord(0xE0000018, 0x11AA0FD0);
            GetDevice()->AllWriteDWord(0xE000001C, 0x155E1384);
            GetDevice()->AllWriteDWord(0xE0001004, 0x00ED0080);
            GetDevice()->AllWriteDWord(0xE0001008, 0x00800080);
        break;
        case VD:
            val |= 0x01;
            vcsc |= 0x01;
            vicsc |= 0x01;
            value_ip5B = 0x00;
            value_mmu17 = 0x00;
            value_me380 = 0xC0;
            value_mc00 = 0x00;
            value_dep8C = 0x00;
            value_ipFB = 0x00;
            if(eInputFormat == In_3D_TB && eOutputFormat == Out_3D_Active && CB_Samsung->Checked)
            {
                value_Ip251 |= 0x30;
            }
            else
            {
                value_Ip251 |= 0x00;
            }
            GetDevice()->AllWriteDWord(0xE0000000, 0x02960100);
            GetDevice()->AllWriteDWord(0xE0000004, 0x05C2042C);
            GetDevice()->AllWriteDWord(0xE0000008, 0x08EE0758);
            GetDevice()->AllWriteDWord(0xE000000C, 0x0C1A0A84);
            GetDevice()->AllWriteDWord(0xE0000010, 0x0F460DB0);
            GetDevice()->AllWriteDWord(0xE0000014, 0x127210DC);
            GetDevice()->AllWriteDWord(0xE0000018, 0x14D41408);
            GetDevice()->AllWriteDWord(0xE000001C, 0x166C15A0);
            GetDevice()->AllWriteDWord(0xE0000020, 0x18041738);
            GetDevice()->AllWriteDWord(0xE0000024, 0x199C18D0);
            GetDevice()->AllWriteDWord(0xE0000028, 0x1B341A68);
            GetDevice()->AllWriteDWord(0xE000002C, 0x1D781C56);
            GetDevice()->AllWriteDWord(0xE0000030, 0x1EB81E38);
            GetDevice()->AllWriteDWord(0xE0000034, 0x1F421F38);
            GetDevice()->AllWriteDWord(0xE0001138, 0x1F561F4C);
            WriteFormatPara(0xE0000038, 0, 16, 0x00CB);
            GetDevice()->AllWriteDWord(0xE0001004, 0x01400080);
            GetDevice()->AllWriteDWord(0xE0001008, 0x00800080);
        break;
    }
    GetDevice()->AllWriteByte(0xE0000D51, value_Ip251);
    GetDevice()->AllWriteByte(0xE000003A, val);
    GetDevice()->AllWriteByte(0xE0000158, vcsc);
    GetDevice()->AllWriteByte(0xE0001360, vicsc);
    //GetDevice()->AllWriteByte(0xE0000201, vicsc);
    GetDevice()->AllWriteByte(0xE000015B, value_ip5B);
    GetDevice()->AllWriteByte(0xE0000B17, value_mmu17);
    //GetDevice()->AllWriteByte(0xE0000A80, value_me380);
    GetDevice()->AllWriteByte(0xE0000200, value_mc00);
    GetDevice()->AllWriteByte(0xE000118C, value_dep8C);
    //GetDevice()->AllWriteByte(0xE00001FB, value_ipFB);
}
//---------------------------------------------------------------------------
void __fastcall TForm_DataPath::SetInputFormat(InputFormat in)
{
    Byte val;
    GetDevice()->AllReadByte(0xE0001000, val);
    val &= 0xF0;
    val |= in & 0x0F;
    GetDevice()->AllWriteByte(0xE0001000, val);
    if(in == In_3D_SBS)
    {
        GetDevice()->AllWriteByte(0xE000011D, 0x60);
    }
    else
    {
        GetDevice()->AllWriteByte(0xE000011D, 0x40);    
    }
    if(in == In_3D_LR)
    {
        NToM_Input_Index = 1;
    }
    else
    {
        NToM_Input_Index = 0;
    }
    if(in == In_3D_TB && eOutputFormat == Out_3D_Active)
    {
        CB_Samsung->Enabled = true;
        if(CB_Samsung->Checked)
        {
            b_ChangedSam = true;
        }
        else
        {
            b_ChangedSam = true;
        }
    }
    else
    {
        if(CB_Samsung->Enabled)
        {
            if(CB_Samsung->Checked)
            {
                b_ChangedSam = true;
            }
            else
            {
                b_ChangedSam = true;
            }
        }
        else
        {
            b_ChangedSam = true;
        }
        CB_Samsung->Enabled = true;
    }

}
//---------------------------------------------------------------------------
void __fastcall TForm_DataPath::SetOutputFormat(OutputFormat out)
{
    Byte val;
    GetDevice()->AllReadByte(0xE0001000, val);
    val &= 0x0F;
    val |= out<<4;
    GetDevice()->AllWriteByte(0xE0001000, val);
    if(out == Out_3D_Active && eInputFormat == In_3D_TB)
    {
        LoadPara(OutFormatShutterGla);
        CB_Samsung->Enabled = true;
        if(CB_Samsung->Checked)
        {
            b_ChangedSam = true;
        }
        else
        {
            b_ChangedSam = true;
        }
    }
    else
    {
        if(CB_Samsung->Enabled)
        {
            if(CB_Samsung->Checked)
            {
                b_ChangedSam = true;
            }
            else
            {
                b_ChangedSam = true;
            }
        }
        else
        {
            b_ChangedSam = true;
        }
        CB_Samsung->Enabled = true;
    }
}
//---------------------------------------------------------------------------
void __fastcall TForm_DataPath::SetInputResolution(InputResolution in)
{
    switch(in)
    {
        case Reso_1366:
            LoadFormatPara(resolution_1366);
            LoadFormatPara(Window_1366);
            LoadFormatPara(HVDelay_1366);
            VScaler15(false);
            WriteFormatPara(0xC00D0020, 0 , 1, 1);
            WriteFormatPara(0xE0001001, 5 , 1, 0);
        break;
        case Reso_1280:
            LoadFormatPara(resolution_640);
            LoadFormatPara(Window_1280);
            LoadFormatPara(HVDelay_1280);
            VScaler15(true);
            WriteFormatPara(0xC00D0020, 0 , 1, 0);
            WriteFormatPara(0xE0001001, 5 , 1, 1);
        break;
        case Reso_1920:
            LoadFormatPara(resolution_1920);
            LoadFormatPara(Window_1920);
            LoadFormatPara(HVDelay_1920);
            VScaler15(false);
            WriteFormatPara(0xC00D0020, 0 , 1, 1);
            WriteFormatPara(0xE0001001, 5 , 1, 0);
        break;
    }
}
//---------------------------------------------------------------------------
void __fastcall TForm_DataPath::SetInputVSync(InputVSync in)
{

}
//---------------------------------------------------------------------------
void __fastcall TForm_DataPath::SetOutputVSync(OutputVSync out)
{
    
}
//---------------------------------------------------------------------------
void __fastcall TForm_DataPath::SetFilmMode(FilmMode film)
{
    
}
//---------------------------------------------------------------------------
void __fastcall TForm_DataPath::SetInputBits(InputBits bits)
{
    Byte val;
    GetDevice()->AllReadByte(0xE000003A, val);
    val &= 0xF3;
    switch(bits)
    {
        case Bits_101010:
        break;
        case Bits_888:
            val |= 0x0C;
        break;
        case Bits_1088:
            val |= 0x04;
        break;
    }
    GetDevice()->AllWriteByte(0xE000003A, val);
}
//---------------------------------------------------------------------------
void __fastcall TForm_DataPath::SetME_Y_DCMode(ME_Y_DCMode mey)
{
    Byte val,val_IP;
    
    GetDevice()->AllReadByte(0xE0000B58, val);
    GetDevice()->AllReadByte(0xE00001F7, val_IP);
    val_IP &= 0xF8;
    val_IP |= mey;
    val &= 0x8F;
    val |= mey<<4;
    GetDevice()->AllWriteByte(0xE00001F7, val_IP);
    GetDevice()->AllWriteByte(0xE0000B58, val);
}
//---------------------------------------------------------------------------
void __fastcall TForm_DataPath::SetMC_Y_DCMode(MC_Y_DCMode mcy)
{
    Byte val,val_IP;
    
    GetDevice()->AllReadByte(0xE0000B59, val);
    GetDevice()->AllReadByte(0xE00001F5, val_IP);
    val_IP &= 0xF8;
    val_IP |= mcy;
    val &= 0x8F;
    val |= mcy<<4;
    GetDevice()->AllWriteByte(0xE00001F5, val_IP);
    GetDevice()->AllWriteByte(0xE0000B59, val);
}
//---------------------------------------------------------------------------
void __fastcall TForm_DataPath::SetMC_C_DCMode(MC_C_DCMode mcc)
{
    Byte val,val_IP;
    
    GetDevice()->AllReadByte(0xE0000B5A, val);
    GetDevice()->AllReadByte(0xE00001F6, val_IP);
    val_IP &= 0xF8;
    val_IP |= mcc;
    val &= 0x8F;
    val |= mcc<<4;
    GetDevice()->AllWriteByte(0xE00001F6, val_IP);
    GetDevice()->AllWriteByte(0xE0000B5A, val);
}
//---------------------------------------------------------------------------
void __fastcall TForm_DataPath::SetME_Y_Bypass(bool b)
{
    Byte IP_F4, MMU_58;
    GetDevice()->AllReadByte(0xE00001F4, IP_F4);
    GetDevice()->AllReadByte(0xE0000B58, MMU_58);
    IP_F4 &= N_BIT_2;
    MMU_58 &= N_BIT_0;
    if(b)
    {
        IP_F4 |= BIT_2;
        MMU_58 |= BIT_0;
    }
    GetDevice()->AllWriteByte(0xE00001F4, IP_F4);
    GetDevice()->AllWriteByte(0xE0000B58, MMU_58);
}
//---------------------------------------------------------------------------
void __fastcall TForm_DataPath::SetMC_Y_Bypass(bool b)
{
    Byte IP_F4, MMU_59;
    GetDevice()->AllReadByte(0xE00001F4, IP_F4);
    GetDevice()->AllReadByte(0xE0000B59, MMU_59);
    IP_F4 &= N_BIT_0;
    MMU_59 &= N_BIT_0;
    if(b)
    {
        IP_F4 |= BIT_0;
        MMU_59 |= BIT_0;
    }
    GetDevice()->AllWriteByte(0xE00001F4, IP_F4);
    GetDevice()->AllWriteByte(0xE0000B59, MMU_59);
}
//---------------------------------------------------------------------------
void __fastcall TForm_DataPath::SetMC_C_Bypass(bool b)
{
    Byte IP_F4, MMU_5A;
    GetDevice()->AllReadByte(0xE00001F4, IP_F4);
    GetDevice()->AllReadByte(0xE0000B5A, MMU_5A);
    IP_F4 &= N_BIT_1;
    MMU_5A &= N_BIT_0;
    if(b)
    {
        IP_F4 |= BIT_1;
        MMU_5A |= BIT_0;
    }
    GetDevice()->AllWriteByte(0xE00001F4, IP_F4);
    GetDevice()->AllWriteByte(0xE0000B5A, MMU_5A);
}
//---------------------------------------------------------------------------
void __fastcall TForm_DataPath::SetME_Y_Lastline(bool b)
{
    Byte IP_F4, MMU_58;
    GetDevice()->AllReadByte(0xE00001F4, IP_F4);
    GetDevice()->AllReadByte(0xE0000B58, MMU_58);
    IP_F4 &= N_BIT_6;
    MMU_58 &= N_BIT_1;
    if(b)
    {
        IP_F4 |= BIT_6;
        MMU_58 |= BIT_1;
    }
    GetDevice()->AllWriteByte(0xE00001F4, IP_F4);
    GetDevice()->AllWriteByte(0xE0000B58, MMU_58);
}
//---------------------------------------------------------------------------
void __fastcall TForm_DataPath::SetMC_Y_Lastline(bool b)
{
    Byte IP_F4, MMU_59;
    GetDevice()->AllReadByte(0xE00001F4, IP_F4);
    GetDevice()->AllReadByte(0xE0000B59, MMU_59);
    IP_F4 &= N_BIT_4;
    MMU_59 &= N_BIT_1;
    if(b)
    {
        IP_F4 |= BIT_4;
        MMU_59 |= BIT_1;
    }
    GetDevice()->AllWriteByte(0xE00001F4, IP_F4);
    GetDevice()->AllWriteByte(0xE0000B59, MMU_59);
}
//---------------------------------------------------------------------------
void __fastcall TForm_DataPath::SetMC_C_Lastline(bool b)
{
    Byte IP_F4, MMU_5A;
    GetDevice()->AllReadByte(0xE00001F4, IP_F4);
    GetDevice()->AllReadByte(0xE0000B5A, MMU_5A);
    IP_F4 &= N_BIT_5;
    MMU_5A &= N_BIT_1;
    if(b)
    {
        IP_F4 |= BIT_5;
        MMU_5A |= BIT_1;
    }
    GetDevice()->AllWriteByte(0xE00001F4, IP_F4);
    GetDevice()->AllWriteByte(0xE0000B5A, MMU_5A);
}
//---------------------------------------------------------------------------
void __fastcall TForm_DataPath::SetME_Y_Diagonal(bool b)
{
    Byte val,val_IP;
    
    GetDevice()->AllReadByte(0xE0000B58, val);
    GetDevice()->AllReadByte(0xE00001F7, val_IP);
    val &= N_BIT_7;
    val_IP &= N_BIT_3;
    if(b)
    {
        val |= BIT_7;
        val_IP |= BIT_3;
    }
    GetDevice()->AllWriteByte(0xE00001F7, val_IP);
    GetDevice()->AllWriteByte(0xE0000B58, val);
}
//---------------------------------------------------------------------------
void __fastcall TForm_DataPath::SetMC_Y_Diagonal(bool b)
{
    Byte val,val_IP;
    
    GetDevice()->AllReadByte(0xE0000B59, val);
    GetDevice()->AllReadByte(0xE00001F5, val_IP);
    val &= N_BIT_7;
    val_IP &= N_BIT_3;
    if(b)
    {
        val |= BIT_7;
        val_IP |= BIT_3;
    }
    GetDevice()->AllWriteByte(0xE00001F5, val_IP);
    GetDevice()->AllWriteByte(0xE0000B59, val);
}
//---------------------------------------------------------------------------
void __fastcall TForm_DataPath::SetMC_C_Diagonal(bool b)
{
    Byte val,val_IP;
    
    GetDevice()->AllReadByte(0xE0000B5A, val);
    GetDevice()->AllReadByte(0xE00001F6, val_IP);
    val &= N_BIT_7;
    val_IP &= N_BIT_3;
    if(b)
    {
        val |= BIT_7;
        val_IP |= BIT_3;
    }
    GetDevice()->AllWriteByte(0xE00001F6, val_IP);
    GetDevice()->AllWriteByte(0xE0000B5A, val);
}
//---------------------------------------------------------------------------





//---------------------------------------------------------------------------

/*InputType __fastcall TForm_DataPath::GetInputType()
{
    return 0;
}
InputFormat __fastcall TForm_DataPath::GetInputFormat()
{
    return 0;
}
OutputFormat __fastcall TForm_DataPath::GetOutputFormat()
{
    return 0;
}
InputResolution __fastcall TForm_DataPath::GetInputResolution()
{
    return 0;
}
InputVSync __fastcall TForm_DataPath::GetInputVSync()
{
    return 0;
}
OutputVSync __fastcall TForm_DataPath::GetOutputVSync()
{
    return 0;
}
FilmMode __fastcall TForm_DataPath::GetFilmMode()
{
    return 0;
}
InputBits __fastcall TForm_DataPath::GetInputBits()
{
    return 0;
}
ME_Y_DCMode __fastcall TForm_DataPath::GetME_Y_DCMode()
{
    return 0;
}
MC_Y_DCMode __fastcall TForm_DataPath::GetMC_Y_DCMode()
{
    return 0;
}
MC_C_DCMode __fastcall TForm_DataPath::GetMC_C_DCMode()
{
    return 0;
} */

//---------------------------------------------------------------------------





//---------------------------------------------------------------------------

void __fastcall TForm_DataPath::LoadAddrLut(TStringList * sl)
{
    int realCount,mod;
    realCount = Ceil((double)sl->Count / 2);

    addr_lut = (__Addr_UN *)malloc(realCount*sizeof(__Addr_UN));
    mod = sl->Count % 2;
    for(int i=0;i<2-mod;i++)
    {
        if(mod==0)  break;
        sl->Add("0");
    }
    for(int i=0;i<realCount;i++)
    {
        addr_lut[i].addr.d0 = ("0x"+sl->Strings[i*2]).ToInt();
        addr_lut[i].addr.d1 = ("0x"+sl->Strings[i*2+1]).ToInt();
    }
}
//---------------------------------------------------------------------------
void __fastcall TForm_DataPath::LoadDataLut(TStringList * sl)
{
    int realCount, mod;
    AnsiString str,tmpstr;
    unsigned __int64 val;
    unsigned __int64 hi, lo;
    realCount = Ceil((double)sl->Count / 2);
    data_lut = (__Data_UN *)malloc(realCount*sizeof(__Data_UN));
    mod = sl->Count % 2;
    for(int i=0;i<2-mod;i++)
    {
        if(mod==0)  break;
        sl->Add("0000000000");
    }
    int i;
    for(i=0;i<realCount;i++)
    {
        str = sl->Strings[i*2];

        tmpstr = "0x"+str.SubString(1,2);
        hi = tmpstr.ToInt();
        tmpstr = "0x"+str.SubString(3,8);
        lo = tmpstr.ToInt();

        val = (hi<<32 )| (lo & 0x00000000FFFFFFFF);
        data_lut[i].data.d0 = val;

        str = sl->Strings[i*2+1];
        
        tmpstr = "0x"+str.SubString(1,2);
        hi = tmpstr.ToInt();
        tmpstr = "0x"+str.SubString(3,8);
        lo = tmpstr.ToInt();

        val = (hi<<32 )| (lo & 0x00000000FFFFFFFF);
        data_lut[i].data.d1 = val;
    }
}
//---------------------------------------------------------------------------
void __fastcall TForm_DataPath::LoadMeLut(TStringList * sl)
{
    int realCount, mod;
    realCount = Ceil((double)sl->Count / 8);
    me_inc = (__ME_UN *)malloc(realCount*sizeof(__ME_UN));
    mod = sl->Count % 8;
    for(int i=0;i<8-mod;i++)
    {
        if(mod==0)  break;
        sl->Add("0");
    }
    for(int i=0;i<realCount;i++)
    {
        me_inc[i].me_inc.byte0.d0 = sl->Strings[i*8].ToInt();
        me_inc[i].me_inc.byte0.d1 = sl->Strings[i*8+1].ToInt();
        me_inc[i].me_inc.byte1.d0 = sl->Strings[i*8+2].ToInt();
        me_inc[i].me_inc.byte1.d1 = sl->Strings[i*8+3].ToInt();
        me_inc[i].me_inc.byte2.d0 = sl->Strings[i*8+4].ToInt();
        me_inc[i].me_inc.byte2.d1 = sl->Strings[i*8+5].ToInt();
        me_inc[i].me_inc.byte3.d0 = sl->Strings[i*8+6].ToInt();
        me_inc[i].me_inc.byte3.d1 = sl->Strings[i*8+7].ToInt();
    }
}
//---------------------------------------------------------------------------
void __fastcall TForm_DataPath::LoadMcLut(TStringList * sl)
{
    int realCount, mod;
    realCount = Ceil((double)sl->Count / 16);
    mc_inc = (__MC_UN *)malloc(realCount*sizeof(__MC_UN));
    mod = sl->Count % 16;
    for(int i=0;i<16-mod;i++)
    {
        if(mod==0)  break;
        sl->Add("0");
    }
    for(int i=0;i<realCount;i++)
    {
        mc_inc[i].mc_inc.byte0.d0 = sl->Strings[i*16].ToInt();
        mc_inc[i].mc_inc.byte0.d1 = sl->Strings[i*16+1].ToInt();
        mc_inc[i].mc_inc.byte0.d2 = sl->Strings[i*16+2].ToInt();
        mc_inc[i].mc_inc.byte0.d3 = sl->Strings[i*16+3].ToInt();
        mc_inc[i].mc_inc.byte1.d0 = sl->Strings[i*16+4].ToInt();
        mc_inc[i].mc_inc.byte1.d1 = sl->Strings[i*16+5].ToInt();
        mc_inc[i].mc_inc.byte1.d2 = sl->Strings[i*16+6].ToInt();
        mc_inc[i].mc_inc.byte1.d3 = sl->Strings[i*16+7].ToInt();
        mc_inc[i].mc_inc.byte2.d0 = sl->Strings[i*16+8].ToInt();
        mc_inc[i].mc_inc.byte2.d1 = sl->Strings[i*16+9].ToInt();
        mc_inc[i].mc_inc.byte2.d2 = sl->Strings[i*16+10].ToInt();
        mc_inc[i].mc_inc.byte2.d3 = sl->Strings[i*16+11].ToInt();
        mc_inc[i].mc_inc.byte3.d0 = sl->Strings[i*16+12].ToInt();
        mc_inc[i].mc_inc.byte3.d1 = sl->Strings[i*16+13].ToInt();
        mc_inc[i].mc_inc.byte3.d2 = sl->Strings[i*16+14].ToInt();
        mc_inc[i].mc_inc.byte3.d3 = sl->Strings[i*16+15].ToInt();
    }
}
//---------------------------------------------------------------------------
void __fastcall TForm_DataPath::LoadFilmLut(TStringList * sl)
{
    int realCount, mod;
    realCount = Ceil((double)sl->Count / 32);
    film_end = (__Film_UN *)malloc(realCount*sizeof(__Film_UN));
    mod = sl->Count % 32;
    for(int i=0;i<32-mod;i++)
    {
        if(mod==0)  break;
        sl->Add("0");
    }
    for(int i=0;i<realCount;i++)
    {
        film_end[i].film_end.byte0.d0 = sl->Strings[i*32].ToInt();
        film_end[i].film_end.byte0.d1 = sl->Strings[i*32+1].ToInt();
        film_end[i].film_end.byte0.d2 = sl->Strings[i*32+2].ToInt();
        film_end[i].film_end.byte0.d3 = sl->Strings[i*32+3].ToInt();
        film_end[i].film_end.byte0.d4 = sl->Strings[i*32+4].ToInt();
        film_end[i].film_end.byte0.d5 = sl->Strings[i*32+5].ToInt();
        film_end[i].film_end.byte0.d6 = sl->Strings[i*32+6].ToInt();
        film_end[i].film_end.byte0.d7 = sl->Strings[i*32+7].ToInt();

        film_end[i].film_end.byte1.d0 = sl->Strings[i*32+8].ToInt();
        film_end[i].film_end.byte1.d1 = sl->Strings[i*32+9].ToInt();
        film_end[i].film_end.byte1.d2 = sl->Strings[i*32+10].ToInt();
        film_end[i].film_end.byte1.d3 = sl->Strings[i*32+11].ToInt();
        film_end[i].film_end.byte1.d4 = sl->Strings[i*32+12].ToInt();
        film_end[i].film_end.byte1.d5 = sl->Strings[i*32+13].ToInt();
        film_end[i].film_end.byte1.d6 = sl->Strings[i*32+14].ToInt();
        film_end[i].film_end.byte1.d7 = sl->Strings[i*32+15].ToInt();

        film_end[i].film_end.byte2.d0 = sl->Strings[i*32+16].ToInt();
        film_end[i].film_end.byte2.d1 = sl->Strings[i*32+17].ToInt();
        film_end[i].film_end.byte2.d2 = sl->Strings[i*32+18].ToInt();
        film_end[i].film_end.byte2.d3 = sl->Strings[i*32+19].ToInt();
        film_end[i].film_end.byte2.d4 = sl->Strings[i*32+20].ToInt();
        film_end[i].film_end.byte2.d5 = sl->Strings[i*32+21].ToInt();
        film_end[i].film_end.byte2.d6 = sl->Strings[i*32+22].ToInt();
        film_end[i].film_end.byte2.d7 = sl->Strings[i*32+23].ToInt();
        
        film_end[i].film_end.byte3.d0 = sl->Strings[i*32+24].ToInt();
        film_end[i].film_end.byte3.d1 = sl->Strings[i*32+25].ToInt();
        film_end[i].film_end.byte3.d2 = sl->Strings[i*32+26].ToInt();
        film_end[i].film_end.byte3.d3 = sl->Strings[i*32+27].ToInt();
        film_end[i].film_end.byte3.d4 = sl->Strings[i*32+28].ToInt();
        film_end[i].film_end.byte3.d5 = sl->Strings[i*32+29].ToInt();
        film_end[i].film_end.byte3.d6 = sl->Strings[i*32+30].ToInt();
        film_end[i].film_end.byte3.d7 = sl->Strings[i*32+31].ToInt();
    }
}
//---------------------------------------------------------------------------
void __fastcall TForm_DataPath::LoadPointer(TStringList * sl)
{
    if(sl->Count > 0)
    {
        ph_pointer = (__S_Phase_Poiter *)malloc(sl->Count * sizeof(__S_Phase_Poiter));
        for(int i=0;i<sl->Count;i++)
        {
            sscanf(sl->Strings[i].c_str(),"%d, %d, %d, %d",&ph_pointer[i].lut_offset,
                &ph_pointer[i].ip_offset, &ph_pointer[i].film_offset, &ph_pointer[i].top44_control);
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall TForm_DataPath::LoadN2M(TStringList * sl)
{
    int bN, bM;
    if(sl->Count > 0)
    {
        sscanf(sl->Strings[0].c_str(), "%d, %d", &bN, &bM);
        GetDevice()->AllWriteByte(0xE0000069, bN);
        GetDevice()->AllWriteByte(0xE00000D5, bM);
    }
}
//---------------------------------------------------------------------------
void __fastcall TForm_DataPath::WritePointer(__S_Phase_Poiter ptr)
{
    GetDevice()->AllWriteByte(0xE000030D, ptr.lut_offset);
    GetDevice()->AllWriteByte(0xE000030E, ptr.ip_offset);
    GetDevice()->AllWriteByte(0xE000030F, ptr.film_offset);
    GetDevice()->AllWriteByte(0xE0000044, ptr.top44_control);
}
//---------------------------------------------------------------------------


void __fastcall TForm_DataPath::SaveAddrLut(__Addr_UN * addr, TStringList * sl, int count)
{
    int realCount;

    sl->Add("unsigned int Addr_Lut{");
    realCount = Ceil((double)count / 2);
    for(int i=0;i<realCount;i++)
    {
        sl->Add("0x"+IntToHex((int)addr[i].reg0,8)+",");
    }
    sl->Add("};");
    sl->Add("");
    sl->Add("");
}
//---------------------------------------------------------------------------
void __fastcall TForm_DataPath::SaveDataLut(__Data_UN * data, TStringList * sl, int count)
{
    int realCount;

    sl->Add("unsigned int Data_Lut{");
    realCount = Ceil((double)count / 2);
    for(int i=0;i<realCount;i++)
    {
        data[i].reg.reg1 &=0x0000FFFF;
        data[i].reg.reg1 |= data[i].reg.reg2<<16;
        data[i].reg.reg2 >>= 16;
        data[i].reg.reg2 |= data[i].reg.reg3<<16;

        sl->Add("0x"+IntToHex((int)data[i].reg.reg0,8)+",");
        sl->Add("0x"+IntToHex((int)data[i].reg.reg1,8)+",");
        sl->Add("0x"+IntToHex((int)data[i].reg.reg2,8)+",");
    }
    sl->Add("};");
    sl->Add("");
    sl->Add("");
}
//---------------------------------------------------------------------------
void __fastcall TForm_DataPath::SaveMeInc(__ME_UN * me, TStringList * sl, int count)
{
    int realCount;

    sl->Add("unsigned int Me_Lut{");
    realCount = Ceil((double)count / 8);
    for(int i=0;i<realCount;i++)
    {
        sl->Add("0x"+IntToHex((int)me[i].reg0,8)+",");
    }
    sl->Add("};");
    sl->Add("");
    sl->Add("");
}
//---------------------------------------------------------------------------
void __fastcall TForm_DataPath::SaveMcInc(__MC_UN * mc, TStringList * sl, int count)
{
    int realCount;

    sl->Add("unsigned int Mc_Lut{");
    realCount = Ceil((double)count / 16);
    for(int i=0;i<realCount;i++)
    {
        sl->Add("0x"+IntToHex((int)mc[i].reg0,8)+",");
    }
    sl->Add("};");
    sl->Add("");
    sl->Add("");
}
//---------------------------------------------------------------------------
void __fastcall TForm_DataPath::SaveFilmEnd(__Film_UN * film, TStringList * sl, int count)
{
    int realCount;

    sl->Add("unsigned int Film_Lut{");
    realCount = Ceil((double)count / 32);
    for(int i=0;i<realCount;i++)
    {
        sl->Add("0x"+IntToHex((int)film[i].reg0,8)+",");
    }
    sl->Add("};");
    sl->Add("");
    sl->Add("");
}


//---------------------------------------------------------------------------

void __fastcall TForm_DataPath::WriteAddrLut(__Addr_UN * addr, unsigned int start, int count)
{
    int realCount;
    realCount = Ceil((double)count / 2);
    for(int i=0;i<realCount;i++)
    {
        GetDevice()->AllWriteDWord(start+i*4, addr[i].reg0);
    }
}
//---------------------------------------------------------------------------
void __fastcall TForm_DataPath::WriteDataLut(__Data_UN * data, unsigned int start, int count)
{
    int realCount;
    realCount = Ceil((double)count / 2);
    for(int i=0;i<realCount;i++)
    {
        data[i].reg.reg1 &=0x0000FFFF;
        data[i].reg.reg1 |= data[i].reg.reg2<<16;
        data[i].reg.reg2 >>= 16;
        data[i].reg.reg2 |= data[i].reg.reg3<<16;

        GetDevice()->AllWriteDWord(start+i*12, data[i].reg.reg0);
        GetDevice()->AllWriteDWord(start+i*12+4, data[i].reg.reg1);
        GetDevice()->AllWriteDWord(start+i*12+8, data[i].reg.reg2);
    }
}
//---------------------------------------------------------------------------
void __fastcall TForm_DataPath::WriteMeInc(__ME_UN * me, unsigned int start, int count)
{
    int realCount;
    realCount = Ceil((double)count / 8);
    for(int i=0;i<realCount;i++)
    {
        GetDevice()->AllWriteDWord(start+i*4, me[i].reg0);
    }
}
//---------------------------------------------------------------------------
void __fastcall TForm_DataPath::WriteMcInc(__MC_UN * mc, unsigned int start, int count)
{
    int realCount;
    realCount = Ceil((double)count / 16);
    for(int i=0;i<realCount;i++)
    {
        GetDevice()->AllWriteDWord(start+i*4, mc[i].reg0);
    }
}
//---------------------------------------------------------------------------
void __fastcall TForm_DataPath::WriteFilmEnd(__Film_UN * film, unsigned int start, int count)
{
    int realCount;
    realCount = Ceil((double)count / 32);
    for(int i=0;i<realCount;i++)
    {
        GetDevice()->AllWriteDWord(start+i*4, film[i].reg0);
    }
}
//---------------------------------------------------------------------------

/*__Addr_UN * __fastcall TForm_DataPath::ReadAddrLut( int count)
{
    __Addr_UN * pointer;
    return pointer;
}
__Data_UN * __fastcall TForm_DataPath::ReadDataLut( int count)
{
    __Data_UN * pointer;
    return pointer;
}
__ME_UN * __fastcall TForm_DataPath::ReadMeInc( int count)
{
    __ME_UN * pointer;
    return pointer;
}
__MC_UN * __fastcall TForm_DataPath::ReadMCInc( int count)
{
    __MC_UN * pointer;
    return pointer;
}
__Film_UN * __fastcall TForm_DataPath::ReadFilmEnd( int count)
{
    __Film_UN * pointer;
    return pointer;
}*/

void __fastcall TForm_DataPath::btnLoadTblClick(TObject *Sender)
{
    TStringList * sl;
    AnsiString slFileName;
    AnsiString slPath;

    sl = new TStringList;
    slPath = GetFilePath();

    slFileName = slPath + "\\PhaseTxt\\Addr"+IntToHex(eInputVSync,2)+IntToHex(eOutputVSync,2)+IntToHex(eOutputFormat,2)+".txt";
    //ShowMessage(slFileName);
    sl->Clear();
    try
    {
        sl->LoadFromFile(slFileName);
    }
    catch(...)
    {
        delete sl;
        throw Exception("Can not open "+slFileName);
    }
    TrimList(sl);
    LoadAddrLut(sl);
    WriteAddrLut(addr_lut, 0xE0001400, sl->Count);
    free(addr_lut);

    if(cb_newtable->Checked)
    {
        slFileName = slPath + "\\PhaseTxt\\new_Data"+IntToHex(eInputVSync,2)+IntToHex(eOutputVSync,2)+IntToHex(eOutputFormat,2)+".txt";
    }
    else
    {
        slFileName = slPath + "\\PhaseTxt\\Data"+IntToHex(eInputVSync,2)+IntToHex(eOutputVSync,2)+IntToHex(eOutputFormat,2)+".txt";
    }
    //ShowMessage(slFileName);
    sl->Clear();
    try
    {
        sl->LoadFromFile(slFileName);
    }
    catch(...)
    {
        delete sl;
        throw Exception("Can not open "+slFileName);
    }
    TrimList(sl);
    LoadDataLut(sl);
    WriteDataLut(data_lut, 0xE0001600, sl->Count);
    free(data_lut);

    slFileName = slPath + "\\PhaseTxt\\ME"+IntToHex(eInputVSync,2)+IntToHex(eOutputVSync,2)+IntToHex(eOutputFormat,2)+".txt";
    //ShowMessage(slFileName);
    sl->Clear();
    try
    {
        sl->LoadFromFile(slFileName);
    }
    catch(...)
    {
        delete sl;
        throw Exception("Can not open "+slFileName);
    }
    TrimList(sl);
    LoadMeLut(sl);
    WriteMeInc(me_inc, 0xE0000320, sl->Count);
    free(me_inc);

    slFileName = slPath + "\\PhaseTxt\\MC"+IntToHex(eInputVSync,2)+IntToHex(eOutputVSync,2)+IntToHex(eOutputFormat,2)+".txt";
    //ShowMessage(slFileName);
    sl->Clear();
    try
    {
        sl->LoadFromFile(slFileName);
    }
    catch(...)
    {
        delete sl;
        throw Exception("Can not open "+slFileName);
    }
    TrimList(sl);
    LoadMcLut(sl);
    WriteMcInc(mc_inc, 0xE0000310, sl->Count);
    free(mc_inc);

    slFileName = slPath + "\\PhaseTxt\\Film"+IntToHex(eInputVSync,2)+IntToHex(eOutputVSync,2)+IntToHex(eOutputFormat,2)+".txt";
    //ShowMessage(slFileName);
    sl->Clear();
    try
    {
        sl->LoadFromFile(slFileName);
    }
    catch(...)
    {
        delete sl;
        throw Exception("Can not open "+slFileName);
    }
    TrimList(sl);
    LoadFilmLut(sl);
    WriteFilmEnd(film_end, 0xE0000340, sl->Count);
    free(film_end);

    slFileName = slPath + "\\PhaseTxt\\Offset"+IntToHex(eInputVSync,2)+IntToHex(eOutputVSync,2)+IntToHex(eOutputFormat,2)+".txt";
    sl->Clear();
    try
    {
        sl->LoadFromFile(slFileName);
    }
    catch(...)
    {
        delete sl;
        throw Exception("Can not open "+slFileName);
    }
    TrimList(sl);
    LoadPointer(sl);

    slFileName = slPath +"\\PhaseTxt\\N2M"+IntToHex(NToM_Input_Index,1)+IntToHex(eInputVSync, 2)+IntToHex(eOutputVSync, 2)+IntToHex(eOutputFormat,2)+".txt";
    sl->Clear();
    try
    {
        sl->LoadFromFile(slFileName);
    }
    catch(...)
    {

        delete sl;
        throw Exception("Can not open "+slFileName);
    }
    TrimList(sl);
    LoadN2M(sl);

    delete sl;

    ShowMessage("load table OK!");

}
//---------------------------------------------------------------------------
__fastcall TForm_DataPath::TForm_DataPath(TComponent* Owner)
    : TMEMCForm(Owner)
{
    eInputResolution = Reso_1920;
}
//---------------------------------------------------------------------------
void __fastcall TForm_DataPath::rb_PCClick(TObject *Sender)
{
    TRadioButton * rb;

    rb = (TRadioButton *)Sender;
    
    eInputType = (InputType)rb->Tag;
    SetInputType(eInputType);
}
//---------------------------------------------------------------------------

void __fastcall TForm_DataPath::RadioButton20Click(TObject *Sender)
{
    TRadioButton * rb;

    rb = (TRadioButton *)Sender;

    eInputResolution = (InputResolution)rb->Tag;
    SetInputResolution(eInputResolution);

    //Set2D3DResoPara(eInputFormat, eOutputFormat, eInputResolution);
}
//---------------------------------------------------------------------------
void __fastcall TForm_DataPath::VScaler15(bool b)
{
    if(b)
    {
        WriteFormatPara(0xE0001001,0,1,1);
        WriteFormatPara(0xE000162E,0,16,0x0438);
    }
    else
    {
        WriteFormatPara(0xE0001001,0,1,0);
        WriteFormatPara(0xE000162E,0,16,0x0000);
    }
}
//---------------------------------------------------------------------------

void __fastcall TForm_DataPath::rb_In_2DClick(TObject *Sender)
{
    TRadioButton * rb;

    rb = (TRadioButton *)Sender;

    eInputFormat = (InputFormat)rb->Tag;
    SetInputFormat(eInputFormat);
    Set2D3DResoPara(eInputFormat, eOutputFormat, eInputResolution);
}
//---------------------------------------------------------------------------

void __fastcall TForm_DataPath::rb_Out_3DActiveClick(TObject *Sender)
{
    TRadioButton * rb;

    rb = (TRadioButton *)Sender;

    eOutputFormat = (OutputFormat)rb->Tag;
    SetOutputFormat(eOutputFormat);
    Set2D3DResoPara(eInputFormat, eOutputFormat, eInputResolution);
}
//---------------------------------------------------------------------------

void __fastcall TForm_DataPath::RB_MeY_DC_mode0Click(TObject *Sender)
{
    TRadioButton * rb;

    rb = (TRadioButton *)Sender;

    eME_Y_DCMode = (ME_Y_DCMode)rb->Tag;
    SetME_Y_DCMode(eME_Y_DCMode);
}
//---------------------------------------------------------------------------

void __fastcall TForm_DataPath::RB_McY_DC_mode4Click(TObject *Sender)
{
    TRadioButton * rb;

    rb = (TRadioButton *)Sender;

    eMC_Y_DCMode = (MC_Y_DCMode)rb->Tag;
    SetMC_Y_DCMode(eMC_Y_DCMode);
}
//---------------------------------------------------------------------------

void __fastcall TForm_DataPath::RB_McC_DC_mode0Click(TObject *Sender)
{
    TRadioButton * rb;

    rb = (TRadioButton *)Sender;

    eMC_C_DCMode = (MC_C_DCMode)rb->Tag;
    SetMC_C_DCMode(eMC_C_DCMode);  
}
//---------------------------------------------------------------------------

void __fastcall TForm_DataPath::rb_1088Click(TObject *Sender)
{
    TRadioButton * rb;

    rb = (TRadioButton *)Sender;

    eInputBits = (InputBits)rb->Tag;
    SetInputBits(eInputBits);
}
//---------------------------------------------------------------------------

void __fastcall TForm_DataPath::rb_In_50Click(TObject *Sender)
{
    TRadioButton * rb;

    rb = (TRadioButton *)Sender;

    eInputVSync = (InputVSync)rb->Tag;
    SetInputVSync(eInputVSync);
}
//---------------------------------------------------------------------------

void __fastcall TForm_DataPath::rb_Out_240Click(TObject *Sender)
{
    TRadioButton * rb;

    rb = (TRadioButton *)Sender;

    eOutputVSync = (OutputVSync)rb->Tag;
    SetOutputVSync(eOutputVSync);
}
//---------------------------------------------------------------------------

void __fastcall TForm_DataPath::rb_videoClick(TObject *Sender)
{
    TRadioButton * rb;

    rb = (TRadioButton *)Sender;

    eFilmMode = (FilmMode)rb->Tag;
    SetFilmMode(eFilmMode);
}
//---------------------------------------------------------------------------

void __fastcall TForm_DataPath::CB_MeY_DC_BypassClick(TObject *Sender)
{
    TCheckBox * cb;

    cb = (TCheckBox *)Sender;

    SetME_Y_Bypass(cb->Checked);
}
//---------------------------------------------------------------------------
void __fastcall TForm_DataPath::CB_McY_DC_BypassClick(TObject *Sender)
{
    TCheckBox * cb;

    cb = (TCheckBox *)Sender;

    SetMC_Y_Bypass(cb->Checked);
}
//---------------------------------------------------------------------------

void __fastcall TForm_DataPath::CB_McC_DC_BypassClick(TObject *Sender)
{
    TCheckBox * cb;

    cb = (TCheckBox *)Sender;

    SetMC_C_Bypass(cb->Checked);
}
//---------------------------------------------------------------------------

void __fastcall TForm_DataPath::CB_MeY_LastLine_BypassClick(
      TObject *Sender)
{
    TCheckBox * cb;

    cb = (TCheckBox *)Sender;

    SetME_Y_Lastline(cb->Checked);
}
//---------------------------------------------------------------------------

void __fastcall TForm_DataPath::CB_McY_LastLine_BypassClick(
      TObject *Sender)
{
    TCheckBox * cb;

    cb = (TCheckBox *)Sender;

    SetMC_Y_Lastline(cb->Checked);
}
//---------------------------------------------------------------------------

void __fastcall TForm_DataPath::CB_McC_LastLine_BypassClick(
      TObject *Sender)
{
    TCheckBox * cb;

    cb = (TCheckBox *)Sender;

    SetMC_C_Lastline(cb->Checked);
}
//---------------------------------------------------------------------------



void __fastcall TForm_DataPath::Button1Click(TObject *Sender)
{
    TRegLabeledEdit * rle;
    TRegCheckBox * cb;
    AnsiString str;
    Byte film;
    Byte bval;
    unsigned int val;

    for(int i=0;i<GB_ReadBack->ControlCount;i++)
    {
        if(GB_ReadBack->Controls[i]->ClassNameIs("TRegLabeledEdit"))
        {
            rle = (TRegLabeledEdit *)GB_ReadBack->Controls[i];
            //ShowMessage(rle->Name);
            rle->Refresh();
        }
    }
    for(int i=0;i<GB_Scalar->ControlCount;i++)
    {
        if(GB_Scalar->Controls[i]->ClassNameIs("TRegCheckBox"))
        {
            cb = (TRegCheckBox *)GB_Scalar->Controls[i];
            //ShowMessage(cb->Name);
            cb->Refresh();
        }
    }
    GetDevice()->AllReadByte(0xE0000480,film);
    le_FilmMode->Text = _S_FilmMode[film].Name;
    str = "rb_"+le_FilmMode->Text;
    ((TRadioButton *)FindComponent(str))->Checked = true;

    GetDevice()->AllReadByte(0xE000003A, bval);
    if((bval & 0x01) == 0x01)
    {
        rb_VD->Checked = true;
    }
    else
    {
        rb_PC->Checked = true;
    }

    if((bval & 0x0C) == 0x00)
    {
        rb_101010->Checked = true;
    }
    else if((bval & 0x0C) == 0x0C)
    {
        rb_888->Checked = true;
    }
    else if((bval & 0x0C) == 0x08)
    {
        rb_1088->Checked = true;
    }

    GetDevice()->AllReadDWord(0xE00001F4, val);
    if((val & 0x01) == 0x01)
    {
        CB_McY_DC_Bypass->Checked = true;
    }
    else
    {
        CB_McY_DC_Bypass->Checked = false;
    }

    if((val & 0x02) == 0x02)
    {
        CB_McC_DC_Bypass->Checked = true;
    }
    else
    {
        CB_McC_DC_Bypass->Checked = false;
    }

    if((val & 0x04) == 0x04)
    {
        CB_MeY_DC_Bypass->Checked = true;
    }
    else
    {
        CB_MeY_DC_Bypass->Checked = false;
    }

    if((val & 0x10) == 0x10)
    {
        CB_McY_LastLine_Bypass->Checked = true;
    }
    else
    {
        CB_McY_LastLine_Bypass->Checked = false;
    }

    if((val & 0x20) == 0x20)
    {
        CB_McC_LastLine_Bypass->Checked = true;
    }
    else
    {
        CB_McC_LastLine_Bypass->Checked = false;
    }

    if((val & 0x40) == 0x40)
    {
        CB_MeY_LastLine_Bypass->Checked = true;
    }
    else
    {
        CB_MeY_LastLine_Bypass->Checked = false;
    }

    //GetDevice()->ReadByte(ADDR_BYPass+1,bval);
    switch((val>>8) & 0x07)
    {
        case 0:
            RB_McY_DC_mode0->Checked = true;
            break;
        case 1:
            RB_McY_DC_mode1->Checked = true;
            break;
        case 2:
            RB_McY_DC_mode2->Checked = true;
            break;
        case 3:
            RB_McY_DC_mode3->Checked = true;
            break;
        case 4:
            RB_McY_DC_mode4->Checked = true;
            break;
    }
    switch(((val>>8) & BIT_3)>>3)
    {
        case 0:
            CB_McY_Diagonal->Checked = false;
            break;
        case 1:
            CB_McY_Diagonal->Checked = true;
            break;
    }

    //GetDevice()->ReadByte(ADDR_BYPass+2,bval);
    switch((val>>16) & 0x07)
    {
        case 0:
            RB_McC_DC_mode0->Checked = true;
            break;
        case 1:
            RB_McC_DC_mode1->Checked = true;
            break;
        case 2:
            RB_McC_DC_mode2->Checked = true;
            break;
        case 3:
            RB_McC_DC_mode3->Checked = true;
            break;
        case 4:
            RB_McC_DC_mode4->Checked = true;
            break;
    }
    switch(((val>>16) & BIT_3)>>3)
    {
        case 0:
            CB_McC_Diagonal->Checked = false;
            break;
        case 1:
            CB_McC_Diagonal->Checked = true;
            break;
    }
    
    //GetDevice()->ReadByte(ADDR_BYPass+3,bval);
    switch((val>>24) & 0x07)
    {
        case 0:
            RB_MeY_DC_mode0->Checked = true;
            break;
        case 1:
            RB_MeY_DC_mode1->Checked = true;
            break;
        case 2:
            RB_MeY_DC_mode2->Checked = true;
            break;
        case 3:
            RB_MeY_DC_mode3->Checked = true;
            break;
        case 4:
            RB_MeY_DC_mode4->Checked = true;
            break;
    }
    switch(((val>>16) & BIT_3)>>3)
    {
        case 0:
            CB_MeY_Diagonal->Checked = false;
            break;
        case 1:
            CB_MeY_Diagonal->Checked = true;
            break;
    }

    GetDevice()->AllReadByte(0xE0001000, bval );
    eInputFormat = (InputFormat)(bval & 0x0F);
    switch(eInputFormat)
    {
        case In_2D:
            rb_In_2D->Checked = true;
        break;
        case In_3D_LR:
            rb_In_3DLR->Checked = true;
        break;
        case In_3D_SBS:
            rb_In_3DSBS->Checked = true;
        break;
        case In_3D_TB:
            rb_In_3DTB->Checked = true;
        break;
    }
    eOutputFormat = (OutputFormat)(bval>>4);
    switch(eOutputFormat)
    {
        case Out_2D:
            rb_Out_2D->Checked = true;
        break;
        case Out_3D_Active:
            rb_Out_3DActive->Checked = true;
        break;
        case Out_3D_Passive:
            rb_Out_3DPassive->Checked = true;
        break;    
    }
    if(rb_In_3DTB->Checked && rb_Out_3DActive->Checked)
    {
        CB_Samsung->Enabled = true;
    }

    CalVSync();
    
}
//---------------------------------------------------------------------------


void __fastcall TForm_DataPath::btnSetPtrClick(TObject *Sender)
{
    Byte val, film;
    TStringList * sl;
    AnsiString slPath;
    AnsiString slFileName;

    sl = new TStringList;

    slPath = GetFilePath();
    slFileName = slPath + "\\PhaseTxt\\Offset"+IntToHex(eInputVSync,2)+IntToHex(eOutputVSync,2)+IntToHex(eOutputFormat,2)+".txt";
    sl->Clear();
    sl->LoadFromFile(slFileName);
    LoadPointer(sl);
    delete sl;

    if(this->ph_pointer == NULL)
    {
        return;
    }
    if(!CB_HW->Checked)
    {
        GetDevice()->AllReadByte(0xE0000300, val);
        val |= BIT_0;
        GetDevice()->AllWriteByte(0xE0000300, val);
        while(1)
        {
            if(!CB_AutoDet->Checked)
            {
                film = eFilmMode;
            }
            else
            {
                GetDevice()->AllReadByte(0xE0000480, film);
            }
            if(film == 0)
            {                                              
                val &= N_BIT_1;
            }
            else
            {
                val |= BIT_1;
            }
            GetDevice()->AllWriteByte(0xE0000300, val);
            WritePointer(ph_pointer[film]);
            if(!CB_Polling->Checked) return;
            else
            {
                Application->ProcessMessages();
            }
        }
    }
    else
    {
        while(1)
        {
            GetDevice()->AllReadByte(0xE0000300, val);
            GetDevice()->AllReadByte(0xE0000480, film);
            val &= N_BIT_0;
            GetDevice()->AllWriteByte(0xE0000300, val);
            GetDevice()->AllWriteByte(0xE000030C, film);
            WritePointer(this->ph_pointer[film]);
            if(!CB_Polling->Checked) return;
            else
            {
                Application->ProcessMessages();
            }
        }
    }
}
//---------------------------------------------------------------------------

void __fastcall TForm_DataPath::btn_CreateTableClick(TObject *Sender)
{
    TStringList * sl;
    TStringList * sl_save;
    AnsiString slFileName;

    sl = new TStringList;
    sl_save = new TStringList;

    slFileName = ".\\PhaseTxt\\Addr"+IntToHex(eInputVSync,2)+IntToHex(eOutputVSync,2)+IntToHex(eOutputFormat,2)+".txt";
    //ShowMessage(slFileName);
    sl->Clear();
    sl->LoadFromFile(slFileName);
    LoadAddrLut(sl);
    SaveAddrLut(addr_lut, sl_save, sl->Count);
    free(addr_lut);

    slFileName = ".\\PhaseTxt\\Data"+IntToHex(eInputVSync,2)+IntToHex(eOutputVSync,2)+IntToHex(eOutputFormat,2)+".txt";
    //ShowMessage(slFileName);
    sl->Clear();
    sl->LoadFromFile(slFileName);
    LoadDataLut(sl);
    SaveDataLut(data_lut, sl_save, sl->Count);
    free(data_lut);

    slFileName = ".\\PhaseTxt\\ME"+IntToHex(eInputVSync,2)+IntToHex(eOutputVSync,2)+IntToHex(eOutputFormat,2)+".txt";
    //ShowMessage(slFileName);
    sl->Clear();
    sl->LoadFromFile(slFileName);
    LoadMeLut(sl);
    SaveMeInc(me_inc, sl_save, sl->Count);
    free(me_inc);

    slFileName = ".\\PhaseTxt\\MC"+IntToHex(eInputVSync,2)+IntToHex(eOutputVSync,2)+IntToHex(eOutputFormat,2)+".txt";
    //ShowMessage(slFileName);
    sl->Clear();
    sl->LoadFromFile(slFileName);
    LoadMcLut(sl);
    SaveMcInc(mc_inc, sl_save, sl->Count);
    free(mc_inc);

    slFileName = ".\\PhaseTxt\\Film"+IntToHex(eInputVSync,2)+IntToHex(eOutputVSync,2)+IntToHex(eOutputFormat,2)+".txt";
    //ShowMessage(slFileName);
    sl->Clear();
    sl->LoadFromFile(slFileName);
    LoadFilmLut(sl);
    SaveFilmEnd(film_end, sl_save, sl->Count);
    free(film_end);

    sl_save->SaveToFile(".\\PhaseTable\\Phase"+IntToHex(eInputVSync,2)+IntToHex(eOutputVSync,2)+IntToHex(eOutputFormat,2)+".c");

    ShowMessage("save table OK!");

}
//---------------------------------------------------------------------------




void __fastcall TForm_DataPath::Button2Click(TObject *Sender)
{
    LoadFormatPara(Address_TOP);
}
//---------------------------------------------------------------------------


void __fastcall TForm_DataPath::CB_MeY_DiagonalClick(TObject *Sender)
{
    TCheckBox * cb;

    cb = (TCheckBox * )Sender;
    SetME_Y_Diagonal(cb->Checked);
}
//---------------------------------------------------------------------------

void __fastcall TForm_DataPath::CB_McY_DiagonalClick(TObject *Sender)
{
    TCheckBox * cb;

    cb = (TCheckBox * )Sender;
    SetMC_Y_Diagonal(cb->Checked);    
}
//---------------------------------------------------------------------------

void __fastcall TForm_DataPath::CB_McC_DiagonalClick(TObject *Sender)
{
    TCheckBox * cb;

    cb = (TCheckBox * )Sender;
    SetMC_C_Diagonal(cb->Checked);
}
//---------------------------------------------------------------------------   
void __fastcall TForm_DataPath::CalVSync()
{
    int frame, N, M, clk;
    double vsync,ov;
    AnsiString str;
    int i;

    if(le_Clk->Text == "")   return;
    if(rle_Frame->Text == "")   return;
    if(rle_N->Text == "")   return;
    if(rle_M->Text == "")   return;

    try
    {
        clk = le_Clk->Text.ToInt()* 1E6;
        frame = rle_Frame->Text.ToInt();
        N = rle_N->Text.ToInt();
        M = rle_M->Text.ToInt()==0? 1: rle_M->Text.ToInt();
        vsync = ((double)clk  / (double)frame ) / (double)M;
        ov = vsync * (double)N;
        str.sprintf("%2.2f\n",vsync);
        rle_VSync->Text=str;
        str.sprintf("%2.2f\n",ov);
        rle_ovsync->Text=str;
        i = 0;
        while(_InVSync[i]!=0)
        {
            if( (abs(vsync - _InVSync[i]) / (double)_InVSync[i]) < 0.01)
            {
                ((TRadioButton *)FindComponent( VInName[i]))->Checked = true;
            }
            i++;
        }
        i = 0;
        while(_OutVSync[i]!=0)
        {
            if( (abs(ov - _OutVSync[i]) / (double)_OutVSync[i]) < 0.01)
            {
                ((TRadioButton *)FindComponent( VOutName[i]))->Checked = true;
            }
            i++;
        }
    }
    catch(...)
    {
    }
}
//---------------------------------------------------------------------------

void __fastcall TForm_DataPath::rle_ip2A5KeyPress(TObject *Sender,
      char &Key)
{
    Byte val;

    if(Key == 13)
    {
        val = ("0x"+rle_ip2A5->Text).ToInt();
        GetDevice()->AllWriteByte(0xE0000201, val);
        val = val/2-1;
        GetDevice()->AllWriteByte(0xE0000107, val);
        GetDevice()->AllWriteByte(0xE0000202, val);
    }
}
//---------------------------------------------------------------------------

void __fastcall TForm_DataPath::rle_ip03KeyPress(TObject *Sender,
      char &Key)
{
    Byte val;

    if(Key == 13)
    {
        val = ("0x"+rle_ip03->Text).ToInt();
        GetDevice()->AllWriteByte(0xE0000203, val);
    }
}
//---------------------------------------------------------------------------

void __fastcall TForm_DataPath::cb_logoOnClick(TObject *Sender)
{
    Set2D3DResoPara(eInputFormat, eOutputFormat, eInputResolution);
}
//---------------------------------------------------------------------------




void __fastcall TForm_DataPath::CB_SamsungClick(TObject *Sender)
{
    b_ChangedSam = true;
    Set2D3DResoPara(eInputFormat, eOutputFormat, eInputResolution); 
}
//---------------------------------------------------------------------------



void __fastcall TForm_DataPath::btnTestClick(TObject *Sender)
{
    for(int i=0; i<1000; i++)
    {
        rb_PC->Checked = true;

        Sleep(5000);
        rb_VD->Checked = true;
        Sleep(5000);
    }
}
//---------------------------------------------------------------------------

