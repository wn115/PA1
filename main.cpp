// program1
// This program is used to determine whether a URL is valid and output the URL by part
// This prgram has a make file

#include <iostream>
#include <string>
#include <iomanip>
#include "version.h"


using namespace std;

bool validProtocol(string str);
bool validDomain(string str);
bool validPort(string str);
bool validFilePath(string str);
bool valildParameter(string str);
void displayCorrect(string protocol, string domain, string port, string filePath, string parameter, int pos1, int pos2);
void displayError(bool, bool, bool, bool, string, string, string, string, string, int);

static const double VERSION=1.2;

int main()
{
	displayVersion();
    bool isValidProtocol = false;
    bool isValidDomain = false;
    bool isValidPort = false;
    bool isValidFilePath = false;
    string inputURL;

    // prompt user to enter a URL
    cout << "Input a URL: ";
    getline(cin, inputURL);

    int pos1, pos2;
    pos1 = inputURL.find(":");
    pos2 = inputURL.find("/", pos1+3);

    // extract protocol from input URL
    string protocol;
    protocol = inputURL.substr(0, pos1);
    isValidProtocol = validProtocol(protocol);

    string str;
    str = inputURL.substr(pos1+3,(pos2-pos1-3));

    int pos = str.find(":");
    string domain,port;

    if (pos!= -1)
    {
        domain = str.substr(0,pos);
        isValidDomain = validDomain(domain);

        port = str.substr(pos+1,pos2);
        isValidPort = validPort(port);
    } // end case of user put a port
    else
    {
        domain = str.substr(0,pos2-1);
        isValidDomain = validDomain(domain);
    } // end case of user did not input port

    string str1;
    str1 = inputURL.substr(pos2);

    int posParameter = str1.find("?");
    string filePath, parameter;
    if (posParameter!= -1)
    {
        filePath = str1.substr(0, posParameter);
        isValidFilePath = validFilePath(filePath);
        parameter = str1.substr(posParameter+1);
    } // end case of user put a parameter
    else
    {
        filePath = str1;
        isValidFilePath = validFilePath(filePath);
    } // end case of user did not put a parameter


    if ((isValidProtocol==0)||(isValidDomain==0)||(isValidPort==0)||(isValidFilePath==0))
    {
       displayError(isValidProtocol, isValidDomain, isValidPort, isValidFilePath, protocol, domain, port, filePath, parameter, pos);
    } // end case of user put a valid URL
    else
    {
       displayCorrect(protocol, domain, port, filePath, parameter, pos, posParameter);
    }  // end case of user did not put a valid URL

    return 0;
}

// function to check whether protocol is valid or not
bool validProtocol(string str)
{
    if ((str=="http")||(str=="https")||(str=="ftp")||(str=="ftps"))
    {
        return true;
    }
    else
        return false;
}

// function to check whether domain is valid or not
bool validDomain(string str)
{
    int pos1, pos2;
    string str1;
    pos1 = str.find(".");
    if (pos1==-1)
    {
        return false;
    }
    else
    {
        pos2 = str.find(".",pos1+1);
        if (pos2==-1)
        {
            return false;
        }
        else
        {
            str1 = str.substr(pos2+1);
            if ((str1=="com")||(str1=="net")||(str1=="edu")||(str1=="biz")||(str1=="gov"))
            {
                return true;
            }
            else
                return false;
        }
    }
}

// function to check whether port is valid or not
bool validPort(string str)
{
    int portNum;
    portNum = stoi(str);
    if ((portNum<1)||(portNum>65535))
    {
        return false;
    }
    else
        return true;
}

// function to check whether file path is valid or not
bool validFilePath(string str)
{
    int pos;
    string str1;
    pos = str.find(".");
    if (pos == -1)
    {
        return false;
    }
    else
    {
        str1 = str.substr(pos+1);
        if ((str1=="html")||(str1=="htm"))
            return true;
        else
            return false;
    }

}

// display function for the case that user entered a valid value
void displayCorrect(string protocol, string domain, string port, string filePath, string parameter, int pos1, int pos2)
{
    cout << "Protocol: 	" << protocol << endl;
    cout << "Domain: 	" << domain << endl;
    if (pos1!=-1)
    {
       cout << "Port:		" << port << endl;
    }
    cout << "File path:	" << filePath << endl;
    if (pos2!=-1)
    {
       cout << "Parameters:	" << parameter << endl;
    }

}

// display function for the case that user entered an invalid URL
void displayError(bool isValidProtocol, bool isValidDomain, bool isValidPort, bool isValidFilePath,
                  string protocol, string domain, string port, string filePath, string parameter, int pos1)
{
   cout << "Invalid URL with following erroneous components:" << endl;
   if (isValidProtocol==0)
   {
      cout << "Protocol: 	" << protocol << " is not a valid protocol." << endl;
   }
   if (isValidDomain == 0)
   {
      cout << "Domain: 	" << domain << " is an invalid domain name." << endl;
   }
   if ((pos1!=-1)&&(isValidPort==0))
   {
      cout << "Port:		" << "port number must be between 1 and 65535" << endl;
   }
   if (isValidFilePath == 0)
   {
      cout << "File path:	" << filePath << " is an invalid file path." << endl;
   }
}


