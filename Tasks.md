<!------------------------------ PRIMARY TASKS ------------------------------>


1. For the Input System, Do the Following:
    - Do all the input processing in inputSystem's update() function
    - For each element's input() lambda, they should call inputSystem's
      functions which returns whether an input was just clicked/pressed or
      released during that call.
    - The purpose of this format is to reduce time complexity to O(2n) = O(n),
      where input is iterated twice: first time during inputSystem's update(),
      second time during new FocusElement's or stored focusElement's input().
    - Realistically, only mouse button inputs should stored the focusElement.

1. Refactor 'utilities' such that opening and/or loading files should be its
   own function.


<!----------------------------- SECONDARY TASKS ----------------------------->


1. Find a way to remove the try-catch blocks in the run() function for release
mode.
2. Use a try and catch block for the main engine cleanup function (just like
with the init function)
3. Fix the 'test' command in Makefile, where the test program should only be
run when the program compiles successfully
4. Tidy up Makefile with refactoring
