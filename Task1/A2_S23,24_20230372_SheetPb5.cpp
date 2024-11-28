#include<bits/stdc++.h>
using namespace std;

void listProcesses(const char* Windows , const char* Linux) {

#if defined(_WIN32) || defined(_WIN64)
    const char* command = Windows;
#else
    const char* command = Linux;
#endif

    std::array<char, 128> buffer;
    std::string result;

    FILE* pipe = popen(command, "r");
    if (!pipe) {
        std::cerr << "Failed to run command.\n";
        return;
    }

    while (fgets(buffer.data(), buffer.size(), pipe) != nullptr) {
        result += buffer.data();
    }
    pclose(pipe);
    std::cout << result;
}

string clean(const string& input)
{
    string clean = "";
    for(int i = 0 ; i<input.length() ; i++)
    {
        if(input[i] != ' ')
        {
            clean += input[i];
        }
    }return clean;
}

void outPut()
{
    while(true)
    {
        string choice;
        cout<<"Choose how to show the out put\n1.Sort by name\n2.Sort by PID\n3.Sort by memory usage\n4.Exit\n";
        getline(cin,choice);
        choice = clean(choice);
        if(choice=="1")
        {
            listProcesses("tasklist | sort","ps -eo comm,pid,state,%mem --sort=comm");
            break;
        }else if(choice=="2")
        {
            listProcesses("tasklist | sort /+27","ps -eo comm,pid,state,%mem --sort=pid");
            break;
        }else if(choice=="3"){

            listProcesses("tasklist | sort /+66","ps -eo comm,pid,state,%mem --sort=%mem");
            break;
        }else if(choice=="4"){
            break;
        }else{
            cout<<"Your input is not nice, try again but be nice\n";
        }

    }
}


int main()
{
    outPut();
}
