#include <unistd.h>     
#include <sys/types.h>  
#include <sys/wait.h>  
#include <signal.h>  
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <string.h>
using namespace std;


int main()
{
    while (1)
    {
        cout << getcwd(NULL, 0) << " $ " << flush; //couts the current working directory
        
        char line[128];
        cin.getline(line, 128);
    
        vector<char*> args;
        
        char* prog = strtok( line, " " );
        char* tmp = prog;
        
        while ( tmp != NULL )
        {
          args.push_back( tmp );
          tmp = strtok( NULL, " " );
        }
    
        char** argv = new char*[args.size()+1];
        
        for ( int k = 0; k < args.size(); k++ )
          argv[k] = args[k];
    
        argv[args.size()] = NULL;
    
        if (strcmp(argv[0], "exit") == 0)
          exit(0);
          
        pid_t child = fork();
        if (child == 0)
        {
          execvp(prog, argv);
          return 0;
        }
        else if ( child < 0 )
        {
          perror("Fork failed");
          return 0;
        }
        else if ( waitpid( child, 0, 0 ) < 0 )
        {
            //this would mean that the parent could not wait for child
            perror("Parent wait failed");
            return 0;
        }
    }
}
