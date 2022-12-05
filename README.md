# RuthSimu
Geant4 simulation for the Rutherford experiment@unipd

# Simulation
how to run it:  
-create a build directory (better if outside of the source folder)  
  ```cmake pathToTheSourceDir```  
  ```make -jN```   where N is the number of cores of your processor  
  ```./sim```

-after the first "cmake" one can conveniently use the bash scripts, automatically copied by cmake in the build directory

-it is not necessary to run cmake every time, so the
    ```. scripts/x.sh```
 comes in help, otherwise
       ```. scripts/make.sh``` script

# GitHub
how to send your modifications:  
 ```git add``` followed by the name of the file you want to add or modify  
 ```git commit -m "message"``` in order to assign an explanation of your modifications  
 ```git push``` to send the commit online
    
