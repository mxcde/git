#include <iostream>
using namespace std;

#include<fstream>
#include<string>
#include<iomanip>
#include<stdlib.h>
#include<vector>
#include<io.h>



void getfilename(string filePath);
void getFiles( string path, vector<string>& files );
void openfile(string filename,string newfilename);
void SplitString(const string& s, vector<string>& v, const string& c);


vector<string> files;  //log下文件名

//#define   folder   "C:\\Users\\ZhuQiang\\Documents\\log20171221\\log"
//#define    object_file  "C:\\Users\\ZhuQiang\\Documents\\log20171221\\newlog.txt"

vector<string>  conf;

void config();
int main()
{

    config();
    getfilename(conf[0]);

    for(unsigned int i=0;i<files.size();i++)
    {
    openfile(files[i],conf[1]);
     }
  cout<<"end"<<endl;
   getchar();
   return 0;
}



void config()
{
    fstream file;
    file.open("config.ini");
    if(file.fail())
    {
        cout<<"file open"<<endl;
    }
    string line;
    vector<string> tmp;
    while(getline(file,line))
    {
        if(line[0] != '[')
        {
        SplitString(line,tmp,"=");
        conf.push_back(tmp[tmp.size()-1]);
        }
    }

}


void openfile(string filename,string newfilename)
{
    fstream readfile;
    ofstream writefile;
    string line;
    int flag =0;

    readfile.open(filename);
    writefile.open(newfilename,ios::app);
    if(writefile.fail())
    {
        cout<<"write open"<<endl;
    }


   //cout<<filename<<":"<<i++<<endl;



    if(readfile.fail())
    {
        cout<<"read open file fail\n";
        return ;
    }
    else
    {
        while(getline(readfile,line))
        {

            vector<string> tmp;
            SplitString(line,tmp,"  ");
            int tmpint = atoi(tmp[2].c_str());
            if(tmpint >=atoi(conf[2].c_str()))
            {
                if(flag == 0)
                {
                vector<string>   tmp0;
                SplitString(filename,tmp0,"\\");
                writefile<<tmp0[tmp0.size()-1].c_str()<<":"<<endl;
                flag++;
                }


                writefile<<line.c_str()<<endl;
            }

        }
        if(flag!=0)
        {
            writefile<<endl;
        }

    }




   writefile.close();
   readfile.close();
}







void getfilename(string filePath)
{

    ////获取该路径下的所有文件
    getFiles(filePath, files );

    //char str[30];
    //int size = files.size();
}

void getFiles( string path, vector<string>& files )
{
    //文件句柄
    long   hFile   =   0;
    //文件信息
    struct _finddata_t fileinfo;
    string p;
    if((hFile = _findfirst(p.assign(path).append("\\*").c_str(),&fileinfo)) !=  -1)
    {
        do
        {
            //如果是目录,迭代之
            //如果不是,加入列表
            if((fileinfo.attrib &  _A_SUBDIR))
            {
                if(strcmp(fileinfo.name,".") != 0  &&  strcmp(fileinfo.name,"..") != 0)
                    getFiles( p.assign(path).append("\\").append(fileinfo.name), files );
            }
            else
            {
                files.push_back(p.assign(path).append("\\").append(fileinfo.name) );
            }
        }while(_findnext(hFile, &fileinfo)  == 0);
        _findclose(hFile);
    }
}



void SplitString(const string& s, vector<string>& v, const string& c)

{

    string::size_type pos1, pos2;

    pos2 = s.find(c);

    pos1 = 0;

    while(string::npos != pos2)

    {

        v.push_back(s.substr(pos1, pos2-pos1));



        pos1 = pos2 + c.size();

        pos2 = s.find(c, pos1);

    }

    if(pos1 != s.length())

        v.push_back(s.substr(pos1));

}
