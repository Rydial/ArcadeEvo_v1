<!------------------------------ PRIMARY TASKS ------------------------------>

1. Screen Manager
    - Screen Manager holds vector of Panels
    - Each 'Screen' is an abstraction of a set of Panels
    - When initializing Screen specific unique Panels like 'Pacman Screen    
      Panel' or 'MainMenu Screen Panel', they should be passed the Screen Manager's vector of Panels to add and initialize all of their respective
      panels (like Pacman's Settings/Options Panel)
    - Panel IDs should be their respective index in the panel vector

1. Find a way to remove the try-catch blocks in the run() function for release
mode.

<!----------------------------- SECONDARY TASKS ----------------------------->

1. Use a try and catch block for the main engine cleanup function (just like
with the init function)
2. Fix the 'test' command in Makefile, where the test program should only be
run when the program compiles successfully
3. Tidy up Makefile with refactoring
