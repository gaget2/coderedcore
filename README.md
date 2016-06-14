# Code Red Core
Provides the template file heriarchy and engine behind the applications created by the Code Red team

This is a non-commercial WIP project by the Code Red Team.

Instructions for compiling:

1. Open makefile and add new targets to any new .cpp files created. These should be added below the message "ADD NEW OBJECT FILES HERE." Adding new targets should follow this pattern:
      For adding targets in the CRE directory:
      $(BIN)/ClassObject.o: $(SRC)/ClassObject.cpp $(INC)/ClassObject.hpp
          $(CC) $(CFLAGS) $(SRC)/ClassObject.cpp -o $(BIN)/ClassObject.o

      For adding targets in the App directory:
      $(BIN)/ClassObject.o: $(APPSRC)/ClassObject.cpp $(APPINC)/ClassObject.hpp
          $(CC) $(CFLAGS) $(APPSRC)/ClassObject.cpp -o $(BIN)/ClassObject.o
2. Save the makefile and direct the terminal to the directory in which the makefile exists
3. Type "make" into the terminal to compile and link
4. The object files and out file are placed in the App/bin directory

Some make commands explained:
- Typing "make run" into the terminal executes the application created by the makefile
- Typing "make clean" removes all object files and the out file
- Typing "make clean-o" removes all object files but not the out file
- Typing "make help" outputs all the files the makefile knows about. New files are automatically found by the makefile. If your new file is not listed when you run this command, make sure the file is in the correct directory and has the correct file extention. Currently the makefile can only detect .cpp files and .hpp files. The object file list when running "make help" lists the object files it WILL create and not neccessarily the object files that already exist.
