#include "tools.h"

#include "socklib.hpp"

using namespace std;

void save(const std::string &s, int fd){
    ssize_t ecrit = 0, tmp = 0;
    unsigned int str_size = s.size();
    while(ecrit < str_size)
    {
        tmp = write(fd,s.data() + ecrit,str_size - ecrit);
        if(tmp == 0)
            break;
        ecrit += tmp;

    }
}

std::string read_line(int fd,const char stop){
    std::string res = "";
    char buff;
    int data_lu = 0;
    do{
        data_lu = read(fd,&buff,1);
        if(data_lu)
            res += buff;

    }while(buff != stop || data_lu == 0);
    return res;
}

bool get_fd(int &fd){
    bool is_serveur = false;
    int tmp_fd = -1;


    fd = tmp_fd;
    return is_serveur;
}

void send_close(int fd,const std::string &msg)
{   
    save(msg, fd);
}
void verif_reciv(const std::string &msg)
{
    if(msg == "CLOSE\n")
    {
        cout<<"la partie est termine\nvous avez perdu\n";
        exit(EXIT_SUCCESS);
    }
}