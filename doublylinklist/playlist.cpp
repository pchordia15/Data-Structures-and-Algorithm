/**
 * @file playlist.cpp   Implementation of a Playlist for music.
 * 
 * @brief
 *    Implementation of a Playlist for music. A doubly linked list is
 *    used to store the song names.
 *
 * @author Priyanka Chordia
 * @date   2/1/15
 */

#include <iostream>
#include <string>
#include <sstream>

#include "playlist.h"
#include "doublylinkedlist.h"

using std::string;
using std::cin;
using std::cout;
using std::endl;
using std::stringstream;

/**
 * Process a playlist command.
 *
 * Gets an entire line from std::cin, extracts the first word as the command,
 * and calls the appropriate processing function. Invalid commands are
 * ignored.
 *
 */
void Playlist::processCommand() {
   string song,line;
   getline(cin,line);
   string command;
   stringstream ss(line);
   getline(ss, command, ' ');
   getline(ss, song);

   if(command.compare("appendSong") == 0)
   {
      dll.append(song);
   }
   else if(command.compare("insertBefore") == 0)
   {
      dll.insertBefore(song);
   }
   else if(command.compare("insertAfter") == 0)
   {
      dll.insertAfter(song);
   }
   else if(command.compare("gotoFirstSong") == 0)
   {
      dll.begin();
   }
   else if(command.compare("gotoLastSong") == 0)
   {
      dll.end();
   }
   else if(command.compare("playCurrent") == 0)
   {
      string currentsong = dll.getData();
      cout <<"\nplaying current: " <<currentsong;
      if(currentsong.compare("")!=0)
         cout<<endl;
   }
   else if(command.compare("removeSong") == 0)
   {
      dll.remove(song);
   }
   else if(command.compare("gotoSong") == 0)
   {
      dll.find(song);
   }
   else if(command.compare("nextSong") == 0)
   {
      if(!dll.empty())
         dll.next();
   }
   else if(command.compare("prevSong") == 0)
   {
      if(!dll.empty())
         dll.prev();
   }
   else if(command.compare("playForward") == 0)
   {
      cout<<"\nplaying forward: \n";
      if(!dll.empty())
      {
         do
         {
            cout<<dll.getData();
            cout<<"\n";
         }while((dll.next()) == true);
      }
   }
   else if(command.compare("playReverse") == 0)
   {
      cout<<"\nplaying reverse: \n";
      if(!dll.empty())
      {
         do
         {
            cout<<dll.getData();
            cout<<"\n";
         }while((dll.prev()) == true);
      }
   }
}

/**
 * The Playlist main loop will process command lines until eof.
 */  
void Playlist::mainLoop() {
   while (!cin.eof()) processCommand(); // process all commands
}

/**
 * The main entry point for the program.
 */
int main()
{
   Playlist myPlaylist;
   myPlaylist.mainLoop();
   return 0;
}

